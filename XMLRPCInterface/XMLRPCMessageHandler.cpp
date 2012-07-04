#include "XMLRPCMessageHandler.h"

#include "../Core/EntityPool.h"

XMLRPCMessageHandler::XMLRPCMessageHandler(EntityPool* EntityPool)
:
mEntityPool(EntityPool),
mRequestType("")
{}

XMLRPCMessageHandler::~XMLRPCMessageHandler()
{}

int XMLRPCMessageHandler::HandleMessage( const std::string& Message, HTTPReply& Reply )
{
    std::string strHeader = OVISE::GetHTTPHeader(Message);
    std::string strContent = OVISE::GetHTTPContent(Message);

    std::string msg = "";
    int res = HandleMessageRPC(strContent, msg);

    if(res == 0)
        Reply.Status = HTTPReply::ok;
    else
        Reply.Status = HTTPReply::bad_request;

    Reply.Content = msg;

    return res;
}

int XMLRPCMessageHandler::HandleMessageRPC( const std::string& Content, std::string& Message )
{
    std::string methodName;
    std::list< std::vector< std::string > > param_list;

    try
    {
        mDocument.parse< 0 >(const_cast< char* >((char*)(Content.c_str())));

        rapidxml::xml_node<>* rootNode = mDocument.first_node("methodCall");
        if(!rootNode)
        {
            Message = mRPCMesAPI.ErrorResponseMsg("No rootnode found in xmlrpc-message");
            return -1;
        }

        rapidxml::xml_node<>* node = rootNode->first_node("methodName");
        if(!node)
        {
            Message = mRPCMesAPI.ErrorResponseMsg("No node 'methodName' found in xmlrpc-message");
            return -1;
        }

        methodName = OVISE::Trim(node->value());

        rapidxml::xml_node<>* param_node = node->next_sibling("params")->first_node("param");

        while(param_node)
        {
            node = param_node->first_node();
            if(!node)
            {
                mRPCMesAPI.ErrorResponseMsg("Could not find parameternode in xmlrpc-message");
                return -1;
            }

            std::string strDataType = OVISE::Trim(node->name());
            std::vector< std::string > param_vec;
            
            if(!strDataType.compare("value"))
            {
                strDataType = OVISE::Trim(node->first_node()->name());
                if(!strDataType.compare("array"))
                {
                    rapidxml::xml_node<>* array_val_node = node->first_node()->first_node()->first_node();

                    std::string strType = OVISE::Trim(array_val_node->first_node()->name());

                    while(array_val_node)
                    {
                        if(OVISE::Trim(array_val_node->first_node()->name()).compare(strType))
                        {
                            Message = mRPCMesAPI.ErrorResponseMsg("Type change in scope of array in xmlrpc-message");
                            return -1;
                        }

                        std::string strVal = OVISE::Trim(array_val_node->first_node()->value());  // get data
                        param_vec.push_back(strVal);
                        array_val_node = array_val_node->next_sibling("value");
                    }
                    param_list.push_back(param_vec);
                }
                else
                {
                    std::string strDataValue = OVISE::Trim(node->first_node()->first_node()->value());
                    
                    param_vec.push_back(strDataType);
                    param_vec.push_back(strDataValue);

                    param_list.push_back(param_vec);
                }
            }
            else
            {
                Message = mRPCMesAPI.ErrorResponseMsg("Unknown node in xmlrpc-message");
                return -1;
            }

            param_node = param_node->next_sibling("param");
        }
    }
    catch(rapidxml::parse_error _pe)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not parse xmlrpc-message");
        return -1;
    }

    return CallMethod(methodName, param_list, Message);
}

int XMLRPCMessageHandler::CallMethod( const std::string& MethodName,
                    const std::list< std::vector< std::string > >& ParamList, std::string& Message )
{
    if( !(MethodName.compare("InsertEntity")) )
    {
        return InsertEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("RemoveEntity")) )
    {
        return RemoveEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("RemoveEntitiesByAttribute")) )
    {
        return RemoveEntitiesByAttribute(ParamList, Message);
    }
    else if( !(MethodName.compare("AddAttribute")) )
    {
        return AddAttributeToEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("GetAttribute")) )
    {
        return GetAttributeFromEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("GetAttributeNames")) )
    {
        return GetAttributeNamesFromEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("RemoveAttribute")) )
    {
        return RemoveAttributeFromEntity(ParamList, Message);
    }
    else if( !(MethodName.compare("GetAllEntityNames")) )
    {
        return GetAllEntityNames(Message);
    }
    else if( !(MethodName.compare("ChangeAttribute")) )
    {
        return ChangeAttributeOfEntity(ParamList, Message);
    }
    else
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Method doesn't exist");
        return -1;
    }

    return 0;
}

int XMLRPCMessageHandler::GetAllEntityNames(std::string& Message) const
{
    std::vector< std::string > names = mEntityPool->GetEntityNames();
    Message = mRPCMesAPI.AllEntityNamesResponseMsg(names);
    return 0;
}

int XMLRPCMessageHandler::InsertEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message )
{
    if(ParamList.size() == 0 || ParamList.size() > 2)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist has an incorrect size (maybe it's empty or greater than 2)");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    if(ParamList.size() == 1)
    {
        std::vector< std::string > param_vec = *it;
        if( !((param_vec.at(0)).compare("i4")) )        // check datatype for id
        {
            int id = OVISE::StrToInt( param_vec.at(1) );
            mEntityPool->InsertEntity(new Entity(id));     // create and insert new entity in entity-pool
        }
        else if( !((param_vec.at(0)).compare("string")) )   // check datatype for name
        {
            std::string name = param_vec.at(1);
            Entity* e = new Entity();               // create new entity
            e->SetName(name);                       // give entity the name
            mEntityPool->InsertEntity(e);          // insert entity in entity-pool
        }
        else
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Could not insert entity");
            return -1;
        }
    }
    else
    {
        if( (*it).at(0).compare("string") )     // check datatype for name
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype for entity name");
            return -1;
        }

        std::string name = (*it).at(1);
        it++;

        if( (*it).at(0).compare("i4") && (*it).at(0).compare("int") )   // check datatype for id
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype for an entity id");
            return -1;
        }

        int id = OVISE::StrToInt( (*it).at(1) );

        Entity* e = new Entity(id);
        e->SetName(name);
        mEntityPool->InsertEntity(e);
    }

    Message = mRPCMesAPI.StatusResponseMsg("Entity inserted");
    return 0;
}

int XMLRPCMessageHandler::RemoveEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message )
{
    if(ParamList.size() != 1)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();
    std::vector< std::string > param_vec = *it;

    if(param_vec.at(0) == "i4" || param_vec.at(0) == "int")     // check datatype for id
    {
        int id = OVISE::StrToInt( param_vec.at(1) );
        Entity* e = mEntityPool->GetEntityById(id);

        if(CAppContext::instance().GetSelected() == e)
            CAppContext::instance().ClearSelection();

        if(e == NULL)
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity by id");
            return -1;
        }
        mEntityPool->RemoveEntity(e);
    }
    else if(param_vec.at(0) == "string")    // check datatype for name
    {
        std::string name = param_vec.at(1);
        Entity* e = mEntityPool->GetEntityByName(name);
        
        if(CAppContext::instance().GetSelected() == e)
            CAppContext::instance().ClearSelection();

        if(e == NULL)
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity by name");
            return -1;
        }
        mEntityPool->RemoveEntity(e);  // remove entity
    }
    else
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Wrong parameters");
        return -1;
    }

    Message = mRPCMesAPI.StatusResponseMsg("Entity removed");
    return 0;
}


int XMLRPCMessageHandler::RemoveEntitiesByAttribute( const std::list< std::vector< std::string > >& ParamList,
                                                    std::string& Message )
{
    if(ParamList.size() < 1)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    CAppContext::instance().ClearSelection();

    mEntityPool->RemoveEntitiesByAttribute((*it).at(1));

    Message = mRPCMesAPI.StatusResponseMsg("Entities removed by attribute");
    return 0;
}

int XMLRPCMessageHandler::AddAttributeToEntity( const std::list< std::vector< std::string > >& ParamList,
                                                std::string& Message )
{
    if(ParamList.size() < 2)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();
    std::string name = (*it).at(1);
    it++;
    std::string attrName = (*it).at(1);
    it++;

    size_t vec_size = (*it).size();

    // get entity by name
    Entity* e = mEntityPool->GetEntityByName(name);
    if(e == NULL)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if(ParamList.size() == 3)    // if value is of standard type then use this branch
    {
        std::string valueType = (*it).at(0);
        std::string value = (*it).at(1);

        if( !(valueType.compare("i4")) || !(valueType.compare("int")) )     // check for datatype int
        {
            e->Set<int>( attrName, OVISE::StrToInt( value ) );
        }
        else if( !(valueType.compare("boolean")) )                          // check for datatype boolean
        {
            bool val = ( !(value.compare("false")) || !(value.compare("False")) || !(value.compare("FALSE")) || !(value.compare("0")) ) ? 0 : 1;
            e->Set<bool>(attrName, val);
        }
        else if( !(valueType.compare("double")) )                           // check for datatype double
        {
            e->Set<double>( attrName, OVISE::StrToFloat( value ) );
        }
        else if( !(valueType.compare("string")) )                           // check for datatype string
        {
            e->Set<std::string>(attrName, value);
        }
        else
        {
            switch( (*it).size())
            {
                case 2:
                {
                    double x = OVISE::StrToFloat((*it).at(0));
                    double y = OVISE::StrToFloat((*it).at(1));

                    vec2 v(x, y);
                    e->Set<vec2>(attrName, v);
                    break;
                }
                case 3:
                {
                    double x = OVISE::StrToFloat((*it).at(0));
                    double y = OVISE::StrToFloat((*it).at(1));
                    double z = OVISE::StrToFloat((*it).at(2));

                    vec3 v(x, y, z);
                    e->Set<vec3>(attrName, v);
                    break;
                }
                case 4:
                {
                    double x = OVISE::StrToFloat((*it).at(0));
                    double y = OVISE::StrToFloat((*it).at(1));
                    double z = OVISE::StrToFloat((*it).at(2));
                    double w = OVISE::StrToFloat((*it).at(3));

                    vec4 v(x, y, z, w);
                    e->Set<vec4>(attrName, v);
                    break;
                }
                default:
                {
                    Message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute with given datatype");
                    return -1;
                }
            }
        }
    }
    else    // no standard type
    {
        /*std::string type = (*it).at(1);
        it++;
        std::string value = (*it).at(1);*/

        // todo: set attribute

        Message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute with given datatype");
        return -1;
    }

    Message = mRPCMesAPI.StatusResponseMsg("Attribute added to entity");
    return 0;
}

int XMLRPCMessageHandler::RemoveAttributeFromEntity( const std::list< std::vector< std::string > >& ParamList,
                                                    std::string& Message )
{
    if(ParamList.size() < 2)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    e->RemoveAttribute(attributeName);

    Message = mRPCMesAPI.StatusResponseMsg("Attribute removed from entity");

    return 0;
}

int XMLRPCMessageHandler::GetAttributeNamesFromEntity(
                            const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const
{
    if(ParamList.size() < 1)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    std::string entityName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    std::vector< std::string > attrNames = e->GetAttributeNames();

    if(attrNames.size() == 0)
        Message = mRPCMesAPI.StatusResponseMsg("Entity doesn't have any attributes");
    else
        Message = mRPCMesAPI.AllAttributeNamesResponseMsg(attrNames);

    return 0;
}

int XMLRPCMessageHandler::GetAttributeFromEntity( const std::list< std::vector< std::string > >& ParamList,
                                                std::string& Message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)   // if there's no entity with given entityName return error -1
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if( !(attributeName.compare("id")) )
    {
        Message = mRPCMesAPI.AttributeResponseMsg(e->GetId());
    }
    else
    {
        const EntityVariantType* vt = e->GetAttribute(attributeName);

        if(vt == NULL)
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Could not find attribute");
            return -1;
        }

        Message = mRPCMesAPI.AttributeResponseMsg(boost::apply_visitor(EntityVisitor(), *vt));
    }

    return 0;
}

int XMLRPCMessageHandler::GetAttributeFromEntityId(
                                const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    int entityId = OVISE::StrToInt((*it).at(1));
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityById(entityId);

    std::stringstream res;

    if(e == NULL)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity with given id");
        return -1;
    }

    if( !(attributeName.compare("name")) )
    {
        Message = mRPCMesAPI.AttributeResponseMsg(e->GetName());
    }
    else
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find attribute");
        return -1;
    }

    return 0;
}

int XMLRPCMessageHandler::ChangeAttributeOfEntity( const std::list< std::vector< std::string > >& ParamList,
                                                std::string& Message ) const
{
    if(ParamList.size() < 2)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
        return -1;
    }

    std::list< std::vector< std::string > >::const_iterator it = ParamList.begin();

    std::string entityName = (*it).at(1);
    it++;

    if( it == ParamList.end() || (*it).size() == 0)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Wrong parameterlist-size");
        return -1;
    }

    std::string attributeName = (*it).at(1);
    it++;

    if( it == ParamList.end() || (*it).size() == 0)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Wrong parameterlist-size");
        return -1;
    }

    std::string attributeType = (*it).at(0);
    std::string attributeValue = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;
    if(e == NULL)
    {
        Message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if( !attributeType.compare("int") || !attributeType.compare("i4") )
    {
        e->Set(attributeName, OVISE::StrToInt(attributeValue));
    }
    else if( !attributeType.compare("boolean") )
    {
        if( !attributeValue.compare("true") || !attributeValue.compare("True")
            || !attributeValue.compare("TRUE") || !attributeValue.compare("1") )
        {
            e->Set(attributeName, true);
        }
        else if( !attributeValue.compare("false") || !attributeValue.compare("False")
            || !attributeValue.compare("FALSE") || !attributeValue.compare("0") )
        {
            e->Set(attributeName, false);
        }
        else
        {
            Message = mRPCMesAPI.ErrorResponseMsg("Wrong value for type boolean");
            return -1;
        }
    }
    else if( !attributeType.compare("double") )
    {
        e->Set(attributeName, OVISE::StrToFloat(attributeValue));
    }
    else if( !attributeType.compare("string") && (*it).size() < 3)
    {
        e->Set(attributeName, attributeValue);
    }
    else
    {
        switch((*it).size())
        {
            case 2:
            {
                vec2 v;
                v[0] = OVISE::StrToFloat((*it).at(0));
                v[1] = OVISE::StrToFloat((*it).at(1));

                e->Set(attributeName, v);
                break;
            }
            case 3:
            {
                vec3 v;
                v[0] = OVISE::StrToFloat((*it).at(0));
                v[1] = OVISE::StrToFloat((*it).at(1));
                v[2] = OVISE::StrToFloat((*it).at(2));

                e->Set(attributeName, v);
                break;
            }
            case 4:
            {
                quat q;
                q[0] = OVISE::StrToFloat((*it).at(0));
                q[1] = OVISE::StrToFloat((*it).at(1));
                q[2] = OVISE::StrToFloat((*it).at(2));
                q[3] = OVISE::StrToFloat((*it).at(3));

                e->Set(attributeName, q);
                break;
            }
            default:
            {
                Message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype");
                return -1;
            }
        }
    }

    Message = mRPCMesAPI.StatusResponseMsg("Attribute changed");
    return 0;
}
