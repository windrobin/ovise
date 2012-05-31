#include "XMLRPCMessageHandler.h"

#include "../Core/EntityPool.h"

XMLRPCMessageHandler::XMLRPCMessageHandler(EntityPool* _entityPool)
:
mEntityPool(_entityPool),
mRequestType("")
{}

XMLRPCMessageHandler::~XMLRPCMessageHandler()
{}

int XMLRPCMessageHandler::HandleHTMLRequest(const HTTPRequest& _request, HTTPReply& _reply)
{}

std::string XMLRPCMessageHandler::GetHTTPHeader( const std::string& _message ) const
{
    size_t pos = _message.find("\r\n\r\n");
    std::string header = _message.substr(0, pos);

    return header;
}

std::string XMLRPCMessageHandler::GetHTTPContent( const std::string& _message ) const
{
    size_t pos1 = _message.find("\r\n\r\n");
    size_t pos2 = _message.find("\r\n\r\n", pos1 + 1);
    std::string content = _message.substr(pos1 + 4, pos2 - pos1 - 4);

    return content;
}

int XMLRPCMessageHandler::CheckHTTPHeader( const std::string& _header, HTTPReply& _reply )
{
    std::size_t headerLength = _header.length();
    if(headerLength < 3)
        return -2;  // more data required

    std::size_t pos1;
    std::size_t pos2 = _header.find(" ");
    std::string req = _header.substr(0, pos2);

    std::string headerLine = "";
    if(req == "POST")
    {
        mRequestType = "POST";
        pos2 = _header.find("\r\n");
        headerLine = _header.substr(4, pos2 - 4);
    }
    else if(req == "GET")
    {
        mRequestType = "GET";
        pos2 = _header.find("\r\n");
        headerLine = _header.substr(3, pos2 - 3);
    }
    else
    {
        mRequestType = "NONE";
        headerLine = "";
    }

    pos1 = _header.find("User-Agent:", pos2 + 1);
    pos2 = _header.find("\r\n", pos2 + 1);
    if(pos1 == std::string::npos)
        return -1;
    std::string userAgent = _header.substr(pos1 + 11, pos2 - pos1 - 11);

    pos1 = _header.find("Host:", pos2 + 1);
    pos2 = _header.find("\r\n", pos2 + 1);
    if(pos1 == std::string::npos)
        return -1;
    std::string host = _header.substr(pos1 + 5, pos2 - pos1 - 5);

    pos1 = _header.find("Content-Type:", pos2 + 1);
    pos2 = _header.find("\r\n", pos2 + 1);
    if(pos1 == std::string::npos)
        return -1;
    std::string contentType = _header.substr(pos1 + 13, pos2 - pos1 - 13);

    pos1 = _header.find("Content-Length:", pos2 + 1);
    pos2 = _header.find("\r\n", pos2 + 1);
    if(pos1 == std::string::npos)
        return -1;
    std::string contentLength = _header.substr(pos1 + 15, pos2 - pos1 - 15);

    mRequestType = Trimm(mRequestType);
    headerLine = Trimm(headerLine);
    userAgent = Trimm(userAgent);
    host = Trimm(host);
    contentType = Trimm(contentType);
    contentLength = Trimm(contentLength);

    if(headerLine == "/RPC2 HTTP/1.0" || headerLine == "/RPC2 HTTP/1.1")
    {
        // check content-type
        if(contentType != "text/xml")
        {
            _reply.Status = HTTPReply::bad_request;
            _reply.Content = "can only process text/xml messages";
            return -1;
        }

        return 1;
    }

    return 0;
}

std::string XMLRPCMessageHandler::Trimm( const std::string& _str ) const
{
    std::string res = _str;
    
    size_t pos1 = _str.find_first_not_of(" \r\n");
    size_t pos2 = _str.find_last_not_of(" \r\n");
    if(pos1 == std::string::npos)
        return _str;
    if(pos2 == std::string::npos)
        pos2 = _str.length();

    res = _str.substr(pos1, pos2 - pos1 + 1);

    return res;
}

int XMLRPCMessageHandler::HandleMessage( const std::string& _message, HTTPReply& _reply )
{
    std::string strHeader = GetHTTPHeader(_message);
    std::string strContent = GetHTTPContent(_message);

    // ------- ofd
    std::cerr << " > -----------------------------------------------" << std::endl;
    std::cerr << " > [XMLRPCMessageHandler::HandleMessage] message: \n" << _message << std::endl;
    std::cerr << " > -----------------------------------------------" << std::endl;
    // --- end ofd

    std::string message = "";
    int res = HandleMessageRPC(strContent, message);

    std::cerr << " > [HandleMessage] res: " << res << std::endl;

    if(res == 0)
        _reply.Status = HTTPReply::ok;
    else
        _reply.Status = HTTPReply::bad_request;

    _reply.Content = message;

    return res;
}

int XMLRPCMessageHandler::HandleMessageRPC( const std::string& _content, std::string& _message )
{
    std::string methodName;
    std::list< std::vector< std::string > > param_list;

    try
    {
        mDocument.parse< 0 >(const_cast< char* >((char*)(_content.c_str())));

        rapidxml::xml_node<>* rootNode = mDocument.first_node("methodCall");
        if(!rootNode)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("No rootnode found in xmlrpc-message");
            return -1;
        }

        rapidxml::xml_node<>* node = rootNode->first_node("methodName");
        if(!node)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("No node 'methodName' found in xmlrpc-message");
            return -1;
        }

        methodName = Trimm(node->value());

        rapidxml::xml_node<>* param_node = node->next_sibling("params")->first_node("param");

        while(param_node)
        {
            node = param_node->first_node();
            if(!node)
            {
                mRPCMesAPI.ErrorResponseMsg("Could not find parameternode in xmlrpc-message");
                return -1;
            }

            std::string strDataType = Trimm(node->name());
            std::vector< std::string > param_vec;
            if(!strDataType.compare("array"))       // check if we have an array
            {
                rapidxml::xml_node<>* array_val_node = node->first_node()->first_node();

                // get type of container vec2, vec3, vec4 or quat
                std::string strType = Trimm(array_val_node->first_node()->name());
                param_vec.push_back(strType);
                std::string strValue = Trimm(array_val_node->first_node()->value());
                param_vec.push_back(strValue);

                array_val_node = array_val_node->next_sibling("value");

                // this time get datatype of container
                strType = Trimm(array_val_node->first_node()->name());
                param_vec.push_back(strType);
                while(array_val_node)
                {
                    if(Trimm(array_val_node->first_node()->name()).compare(strType))
                    {
                        _message = mRPCMesAPI.ErrorResponseMsg("Type change in scope of array in xmlrpc-message");
                        return -1;
                    }

                    std::string strVal = Trimm(array_val_node->first_node()->value());  // get data
                    param_vec.push_back(strVal);
                    array_val_node = array_val_node->next_sibling("value");
                }
                param_list.push_back(param_vec);
            }
            else if(!strDataType.compare("value"))
            {
                strDataType = Trimm(node->first_node()->name());
                std::string strDataValue = Trimm(node->first_node()->first_node()->value());
                
                param_vec.push_back(strDataType);
                param_vec.push_back(strDataValue);

                param_list.push_back(param_vec);
            }
            else
            {
                _message = mRPCMesAPI.ErrorResponseMsg("Unknown node in xmlrpc-message");
                return -1;
            }

            param_node = param_node->next_sibling("param");
        }
    }
    catch(rapidxml::parse_error _pe)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not parse xmlrpc-message");
        return -1;
    }

    return CallMethod(methodName, param_list, _message);
}

int XMLRPCMessageHandler::CallMethod( const std::string& _methodName,
                    const std::list< std::vector< std::string > >& _param_list, std::string& _message )
{
    if( !(_methodName.compare("InsertEntity")) )
    {
        if(_param_list.size() == 0 || _param_list.size() > 2)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist has an incorrect size (maybe it's empty or greater than 2)");
            return -1;
        }

        if( InsertEntity(_param_list, _message) != 0 )
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not insert entity");
            return -1;
        }
    }
    else if( !(_methodName.compare("RemoveEntity")) )
    {
        if(_param_list.size() != 1)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        if( RemoveEntity(_param_list, _message) != 0)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not remove entity");
            return -1;
        }
    }
    else if( !(_methodName.compare("RemoveEntitiesByAttribute")) )
    {
        if(_param_list.size() < 1)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        if( RemoveEntitiesByAttribute(_param_list, _message) != 0)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not remove entities by attribute");
            return -1;
        }
    }
    else if( !(_methodName.compare("AddAttribute")) )
    {
        if(_param_list.size() < 3)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        if( AddAttributeToEntity(_param_list, _message) != 0)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute to entity");
            return -1;
        }
    }
    else if( !(_methodName.compare("GetAttribute")) )
    {
        if(_param_list.size() < 2)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        return GetAttributeFromEntity(_param_list, _message);
    }
    else if( !(_methodName.compare("GetAttributeNamesFromEntity")) )
    {
        if(_param_list.size() < 1)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("No entity specified");
            return -1;
        }

        return GetAttributeNamesFromEntity(_param_list, _message);
    }
    else if( !(_methodName.compare("RemoveAttributeFromEntity")) )
    {
        if(_param_list.size() < 2)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        return RemoveAttributeFromEntity(_param_list, _message);
    }
    else if( !(_methodName.compare("GetAllEntityNames")) )
    {
        /*if(_param_list.size() < 1)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("No entity specified");
            return -1;
        }*/

        return GetAllEntityNames(_message);
    }
    else if( !(_methodName.compare("ChangeAttributeOfEntity")) )
    {
        if(_param_list.size() < 2)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Parameterlist is incorrect");
            return -1;
        }

        return ChangeAttributeOfEntity(_param_list, _message);
    }
    else
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Method doesn't exist");
        return -1;
    }

    return 0;
}

int XMLRPCMessageHandler::GetAllEntityNames(std::string& _message) const
{
    std::vector< std::string > names = mEntityPool->GetEntityNames();
    _message = mRPCMesAPI.AllEntityNamesResponseMsg(names);
    return 0;
}

int XMLRPCMessageHandler::InsertEntity( const std::list< std::vector< std::string > >& _param_list, std::string& _message )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    if(_param_list.size() == 1)
    {
        std::vector< std::string > param_vec = *it;
        if( !((param_vec.at(0)).compare("i4")) )        // check datatype for id
        {
            int id = atoi( (const char*)((param_vec.at(1)).c_str()) );
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
            _message = mRPCMesAPI.ErrorResponseMsg("Wrong parameters");
            return -1;
        }
    }
    else
    {
        if( (*it).at(0).compare("string") )     // check datatype for name
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype for entity name");
            return -1;
        }

        std::string name = (*it).at(1);
        it++;

        if( (*it).at(0).compare("i4") && (*it).at(0).compare("int") )   // check datatype for id
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype for an entity id");
            return -1;
        }

        int id = atoi( (const char*)(((*it).at(1)).c_str()) );

        Entity* e = new Entity(id);
        e->SetName(name);
        mEntityPool->InsertEntity(e);
    }

    _message = mRPCMesAPI.StatusResponseMsg("Entity inserted");
    return 0;
}

int XMLRPCMessageHandler::RemoveEntity( const std::list< std::vector< std::string > >& _param_list, std::string& _message )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();
    std::vector< std::string > param_vec = *it;

    if(param_vec.at(0) == "i4" || param_vec.at(0) == "int")     // check datatype for id
    {
        int id = atoi( (const char*)((param_vec.at(1)).c_str()) );
        Entity* e = mEntityPool->GetEntityById(id);
        if(e == NULL)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity by id");
            return -1;
        }
        mEntityPool->RemoveEntity(e);
    }
    else if(param_vec.at(0) == "string")    // check datatype for name
    {
        std::string name = param_vec.at(1);
        Entity* e = mEntityPool->GetEntityByName(name);
        if(e == NULL)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity by name");
            return -1;
        }
        mEntityPool->RemoveEntity(e);  // remove entity
    }
    else
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Wrong parameters");
        return -1;
    }

    _message = mRPCMesAPI.StatusResponseMsg("Entity removed");
    return 0;
}


int XMLRPCMessageHandler::RemoveEntitiesByAttribute( const std::list< std::vector< std::string > >& _param_list,
                                                    std::string& _message )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    mEntityPool->RemoveEntitiesByAttribute((*it).at(1));

    _message = mRPCMesAPI.StatusResponseMsg("Entities removed by attribute");
    return 0;
}

int XMLRPCMessageHandler::AddAttributeToEntity( const std::list< std::vector< std::string > >& _param_list,
                                                std::string& _message )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();
    std::string name = (*it).at(1);
    it++;
    std::string attrName = (*it).at(1);
    it++;

    // get entity by name
    Entity* e = mEntityPool->GetEntityByName(name);
    if(e == NULL)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if(_param_list.size() == 3)    // if value is of standard type then use this branch
    {
        std::string valueType = (*it).at(0);
        std::string value = (*it).at(1);

        if( (*it).size() == 2 )
        {
            if( !(valueType.compare("i4")) || !(valueType.compare("int")) )     // check for datatype int
            {
                e->Set<int>( attrName, atoi( ((const char*)(value.c_str())) ) );
            }
            else if( !(valueType.compare("boolean")) )                          // check for datatype boolean
            {
                bool val = ( !(value.compare("false")) || !(value.compare("False")) || !(value.compare("FALSE")) || !(value.compare("0")) ) ? 0 : 1;
                e->Set<bool>(attrName, val);
            }
            else if( !(valueType.compare("double")) )                           // check for datatype double
            {
                e->Set<double>( attrName, atof( ((const char*)(value.c_str())) ) );
            }
            else if( !(valueType.compare("string")) )                           // check for datatype string
            {
                e->Set<std::string>(attrName, value);
            }
            else
            {
                _message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute with given datatype");
                return -1;
            }
        }
        else if( (*it).size() > 2 )     // we have an array; could be an vec2, vec3, vec4 or
        {                               // a quat (see Entity.h typdefs)
            // at first position in the vector is the datatype (it should be a string) for the container-name
            // on second position (i.e. (*it).at(1)) in the vector lies the container-type
            // on third position in the vector lies the datatype for the following data
            // behind the third position follows the data
            valueType = (*it).at(1);
            if( !(valueType.compare("vector2")) )
            {
                double x = atof((const char*)((*it).at(3).c_str()));
                double y = atof((const char*)((*it).at(4).c_str()));

                vec2 v(x, y);
                e->Set<vec2>(attrName, v);
            }
            else if( !(valueType.compare("vector3")) )
            {
                double x = atof((const char*)((*it).at(3).c_str()));
                double y = atof((const char*)((*it).at(4).c_str()));
                double z = atof((const char*)((*it).at(5).c_str()));
                
                vec3 v(x, y, z);
                e->Set<vec3>(attrName, v);
            }
            else if( !(valueType.compare("vector4")) )
            {
                double x = atof((const char*)((*it).at(3).c_str()));
                double y = atof((const char*)((*it).at(4).c_str()));
                double z = atof((const char*)((*it).at(5).c_str()));
                double w = atof((const char*)((*it).at(6).c_str()));

                vec4 v(x, y, z, w);
                e->Set<vec4>(attrName, v);
            }
            else if( !(valueType.compare("quaternion")) )
            {
                double w = atof((const char*)((*it).at(3).c_str()));
                double x = atof((const char*)((*it).at(4).c_str()));
                double y = atof((const char*)((*it).at(5).c_str()));
                double z = atof((const char*)((*it).at(6).c_str()));

                quat q(w, x, y, z);
                e->Set<quat>(attrName, q);
            }
            else
            {
                _message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute with given datatype");
                return -1;
            }
        }
    }
    else    // no standard type
    {
        std::string type = (*it).at(1);
        it++;
        std::string value = (*it).at(1);

        // todo: set attribute

        _message = mRPCMesAPI.ErrorResponseMsg("Could not add attribute with given datatype");
        return -1;
    }

    _message = mRPCMesAPI.StatusResponseMsg("Attribute added to entity");
    return 0;
}

int XMLRPCMessageHandler::RemoveAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list,
                                                    std::string& _message )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    e->RemoveAttribute(attributeName);

    _message = mRPCMesAPI.StatusResponseMsg("Attribute removed from entity");

    return 0;
}

int XMLRPCMessageHandler::GetAttributeNamesFromEntity(
                            const std::list< std::vector< std::string > >& _param_list, std::string& _message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    std::vector< std::string > attrNames = e->GetAttributeNames();

    if(attrNames.size() == 0)
        _message = mRPCMesAPI.StatusResponseMsg("Entity doesn't have any attributes");
    else
        _message = mRPCMesAPI.AllAttributeNamesResponseMsg(attrNames);

    return 0;
}

int XMLRPCMessageHandler::GetAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list,
                                                std::string& _message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)   // if there's no entity with given entityName return error -1
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if( !(attributeName.compare("id")) )
    {
        _message = mRPCMesAPI.AttributeResponseMsg(e->GetId());
    }
    else
    {
        const EntityVariantType* vt = e->GetAttribute(attributeName);

        if(vt == NULL)
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Could not find attribute");
            return -1;
        }

        _message = mRPCMesAPI.AttributeResponseMsg(boost::apply_visitor(EntityVisitor(), *vt));
    }

    return 0;
}

int XMLRPCMessageHandler::GetAttributeFromEntityId(
                                const std::list< std::vector< std::string > >& _param_list, std::string& _message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    int entityId = atoi(((*it).at(1)).c_str());
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityById(entityId);

    std::stringstream res;

    if(e == NULL)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity with given id");
        return -1;
    }

    if( !(attributeName.compare("name")) )
    {
        _message = mRPCMesAPI.AttributeResponseMsg(e->GetName());
    }
    else
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find attribute");
        return -1;
    }

    return 0;
}

int XMLRPCMessageHandler::ChangeAttributeOfEntity( const std::list< std::vector< std::string > >& _param_list,
                                                std::string& _message ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);
    it++;
    std::string attributeType = (*it).at(0);
    std::string attributeValue = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;
    if(e == NULL)
    {
        _message = mRPCMesAPI.ErrorResponseMsg("Could not find entity");
        return -1;
    }

    if( !attributeType.compare("int") || !attributeType.compare("i4") )
    {
        e->Set(attributeName, atoi(attributeValue.c_str()));
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
            _message = mRPCMesAPI.ErrorResponseMsg("Wrong value for type boolean");
            return -1;
        }
    }
    else if( !attributeType.compare("double") )
    {
        e->Set(attributeName, atof(attributeValue.c_str()));
    }
    else if( !attributeType.compare("string") && (*it).size() < 3)
    {
        e->Set(attributeName, attributeValue);
    }
    else
    {
        // because rpc doesn't know a vector2, vector3, vector4 or a quaternion,
        // therefore a such a type is stored as a string with value 'vector2','vector3','vector4' or 'quaternion'
        attributeType = (*it).at(1);
        std::cerr << " > [ChangeAttributeOfEntity] attributeType: " << attributeType << std::endl;

        if( !attributeType.compare("vector2") )
        {
            vec2 v;
            v[0] = atof((*it).at(3).c_str());
            v[1] = atof((*it).at(4).c_str());

            e->Set(attributeName, v);
        }
        else if( !attributeType.compare("vector3") )
        {
            vec3 v;
            v[0] = atof((*it).at(3).c_str());
            v[1] = atof((*it).at(4).c_str());
            v[2] = atof((*it).at(5).c_str());

            e->Set(attributeName, v);
        }
        else if( !attributeType.compare("vector4") )
        {
            vec4 v;
            v[0] = atof((*it).at(3).c_str());
            v[1] = atof((*it).at(4).c_str());
            v[2] = atof((*it).at(5).c_str());
            v[3] = atof((*it).at(6).c_str());

            e->Set(attributeName, v);
        }
        else if( !attributeType.compare("quaternion") )
        {
            quat q;
            q[0] = atof((*it).at(3).c_str());
            q[1] = atof((*it).at(4).c_str());
            q[2] = atof((*it).at(5).c_str());
            q[3] = atof((*it).at(6).c_str());

            e->Set(attributeName, q);
        }
        else
        {
            _message = mRPCMesAPI.ErrorResponseMsg("Wrong datatype");
            return -1;
        }
    }

    _message = mRPCMesAPI.StatusResponseMsg("Attribute changed");
    return 0;
}
