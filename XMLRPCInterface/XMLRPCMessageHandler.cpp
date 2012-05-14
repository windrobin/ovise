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

std::string XMLRPCMessageHandler::HandleMessage( const std::string& _message, HTTPReply& _reply )
{
    std::string strHeader = GetHTTPHeader(_message);
    std::string strContent = GetHTTPContent(_message);

    std::string strRes = HandleMessageRPC2(strContent) + '\n';
    if(strRes[0] == 'S')
        _reply.Status = HTTPReply::ok;
    else if(strRes[0] == 'E')
        _reply.Status = HTTPReply::bad_request;
    else if(strRes[0] == 'R')
        _reply.Status = HTTPReply::ok;

    return strRes;
}

std::string XMLRPCMessageHandler::HandleMessageRPC2( const std::string& _content )
{
    std::string methodName;
    std::list< std::vector< std::string > > param_list;

    try
    {
        mDocument.parse< 0 >(const_cast< char* >((char*)(_content.c_str())));

        rapidxml::xml_node<>* rootNode = mDocument.first_node("methodCall");
        if(!rootNode)
            return "E: No rootnode found in xmlrpc-message";

        rapidxml::xml_node<>* node = rootNode->first_node("methodName");
        if(!node)
            return "E: No node 'methodName' found in xmlrpc-message";

        methodName = Trimm(node->value());

        rapidxml::xml_node<>* param_node = node->next_sibling("params")->first_node("param");

        while(param_node)
        {
            node = param_node->first_node();
            if(!node)
                return "E: Could not find parameternode in xmlrpc-message";

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
                        return "E: Type change in scope of array in xmlrpc-message";      // type change in scope of array

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
                return "E: Unkown node in xmlrpc-message";
            }

            param_node = param_node->next_sibling("param");
        }
    }
    catch(rapidxml::parse_error _pe)
    {
        std::stringstream res;
        res << "E: Could not parse xmlrpc-message\n";
        res << " what: " << _pe.what() << "\n";
        return res.str();
    }

    return CallMethod(methodName, param_list);
}

std::string XMLRPCMessageHandler::CallMethod( const std::string& _methodName,
                    const std::list< std::vector< std::string > >& _param_list )
{
    if( !(_methodName.compare("insertEntity")) )
    {
        if(_param_list.size() == 0 || _param_list.size() > 2)
        {
            std::cerr << " > _param_list size is empty or is greater than 2" << std::endl;
            return "E: Parameterlist has an incorrect size (maybe it's empty or greater than 2)";
        }

        if( !InsertEntity(_param_list) )
            return "E: Could not insert entity";
    }
    else if( !(_methodName.compare("removeEntity")) )
    {
        if(_param_list.size() != 1)
            return "E: Parameterlist is incorrect";

        if( !RemoveEntity(_param_list) )
            return "E: Could not remove entity";
    }
    else if( !(_methodName.compare("removeEntitiesByAttribute")) )
    {
        if(_param_list.size() < 1)
            return "E: Parameterlist is incorrect";

        if( !RemoveEntitiesByAttribute(_param_list) )
            return "E: Could not remove entities by attributes";
    }
    else if( !(_methodName.compare("addAttribute")) )
    {
        if(_param_list.size() < 3)
            return "E: Parameterlist is incorrect";

        if( !AddAttributeToEntity(_param_list) )
            return "E: could not add attribute to entity";
    }
    else if( !(_methodName.compare("getAttribute")) )
    {
        if(_param_list.size() < 2)
            return "E: Parameterlist is incorrect";

        return GetAttributeFromEntity(_param_list);
    }
    else if( !(_methodName.compare("getAttributeNamesFromEntity")) )
    {
        if(_param_list.size() < 1)
            return "E: No entity specified";

        return GetAttributeNamesFromEntity(_param_list);
    }
    else if( !(_methodName.compare("removeAttributeFromEntity")) )
    {
        return RemoveAttributeFromEntity(_param_list);
    }
    else if( !(_methodName.compare("getAllEntityNames")) )
    {
        return GetAllEntityNames();
    }
    else if( !(_methodName.compare("changeAttributeOfEntity")) )
    {
        return ChangeAttributeOfEntity(_param_list);
    }
    else
    {
        std::cerr << " > method doesn't exist" << std::endl;
        return "E: Method doesn't exist";
    }

    return "S: OK";
}

std::string XMLRPCMessageHandler::GetAllEntityNames() const
{
    std::string res = "R:";
    std::vector< std::string > names = mEntityPool->GetEntityNames();
    for(size_t t = 0; t < names.size(); t++)
        res += " " + names.at(t);

    return res;
}

bool XMLRPCMessageHandler::InsertEntity( const std::list< std::vector< std::string > >& _param_list )
{
    std::cout << " > insertEntity()" << std::endl;
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    if(_param_list.size() == 1)
    {
        std::vector< std::string > param_vec = *it;
        if( !((param_vec.at(0)).compare("i4")) )        // check datatype for id
        {
            int id = atoi( (const char*)((param_vec.at(1)).c_str()) );
            std::cout << " > id: " << id << std::endl;
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
            return false;
        }
    }
    else
    {
        if( (*it).at(0).compare("string") )     // check datatype for name
            return false;

        std::string name = (*it).at(1);
        it++;

        if( (*it).at(0).compare("i4") && (*it).at(0).compare("int") )   // check datatype for id
            return false;

        int id = atoi( (const char*)(((*it).at(1)).c_str()) );

        Entity* e = new Entity(id);
        e->SetName(name);
        mEntityPool->InsertEntity(e);
    }

    return true;
}

bool XMLRPCMessageHandler::RemoveEntity( const std::list< std::vector< std::string > >& _param_list )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();
    std::vector< std::string > param_vec = *it;

    if(param_vec.at(0) == "i4" || param_vec.at(0) == "int")     // check datatype for id
    {
        int id = atoi( (const char*)((param_vec.at(1)).c_str()) );
        Entity* e = mEntityPool->GetEntityById(id);
        if(e == NULL)
            return false;
        mEntityPool->RemoveEntity(e);
    }
    else if(param_vec.at(0) == "string")    // check datatype for name
    {
        std::string name = param_vec.at(1);
        Entity* e = mEntityPool->GetEntityByName(name);
        if(e == NULL)
            return false;
        mEntityPool->RemoveEntity(e);  // remove entity
    }
    else
    {
        return false;
    }

    return true;
}


bool XMLRPCMessageHandler::RemoveEntitiesByAttribute( const std::list< std::vector< std::string > >& _param_list )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    mEntityPool->RemoveEntitiesByAttribute((*it).at(1));

    return true;
}

bool XMLRPCMessageHandler::AddAttributeToEntity( const std::list< std::vector< std::string > >& _param_list )
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
        return false;
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
                bool val = ( !(value.compare("false")) || !(value.compare("FALSE")) ) ? 0 : 1;
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
                return false;
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
                return false;
            }
        }
    }
    else    // no standard type
    {
        std::string type = (*it).at(1);
        it++;
        std::string value = (*it).at(1);

        // todo: set attribute
    }

    return true;
}

std::string XMLRPCMessageHandler::RemoveAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list )
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        res << "E: There is no entity with Name '" << entityName << "'";
        return res.str();
    }

    e->RemoveAttribute(attributeName);

    res << "S: OK";

    return res.str();
}

std::string XMLRPCMessageHandler::GetAttributeNamesFromEntity(
                            const std::list< std::vector< std::string > >& _param_list ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)
    {
        res << "E: There is no entity with name '" << entityName << "'";
        return res.str();
    }

    std::vector< std::string > attrNames = e->GetAttributeNames();

    if(attrNames.size() == 0)
        return "";

    res << "R:";
    std::vector< std::string >::const_iterator attr_it = attrNames.begin();
    while(attr_it != attrNames.end())
    {
        res << " " << *attr_it;
        attr_it++;
    }

    return res.str();
}

std::string XMLRPCMessageHandler::GetAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list )
const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    std::string entityName = (*it).at(1);
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityByName(entityName);

    std::stringstream res;

    if(e == NULL)   // if there's no entity with given entityName return error -1
    {
        res << "E: There is no entity with name '" << entityName << "'";
        return res.str();
    }

    if( !(attributeName.compare("id")) )
    {
        res << "R: " << e->GetId();
    }
    else
    {
        const EntityVariantType* vt = e->GetAttribute(attributeName);

        if(vt == NULL)
        {
            res << "E: Attribute with name '" << attributeName << "' doesn't exist";
        }

        res << "R: " << boost::apply_visitor(EntityVisitor(), *vt);

        return res.str();
    }

    return res.str();
}

std::string XMLRPCMessageHandler::GetAttributeFromEntityId(
                                const std::list< std::vector< std::string > >& _param_list ) const
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();

    int entityId = atoi(((*it).at(1)).c_str());
    it++;
    std::string attributeName = (*it).at(1);

    Entity* e = mEntityPool->GetEntityById(entityId);

    std::stringstream res;

    if(e == NULL)
    {
        res << "E: There is no entity with id: " << entityId;
        return res.str();
    }

    if( !(attributeName.compare("name")) )
    {
        res << "R: " << e->GetName();
    }
    else
    {
        res << "E: There is no attribute with name '" << attributeName << "'";
        return res.str();
    }

    return res.str();
}

std::string XMLRPCMessageHandler::ChangeAttributeOfEntity( const std::list< std::vector< std::string > >& _param_list )
const
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
        //std::cerr << " > there's no entity with name " << entityName << std::endl;
        res << "E: There is no entity with name '" << entityName << "'";
        return res.str();
    }

    if( !attributeType.compare("int") || !attributeType.compare("i4") )
    {
        e->Set(attributeName, atoi(attributeValue.c_str()));
    }
    else if( !attributeType.compare("boolean") )
    {
        if( !attributeValue.compare("true") || !attributeValue.compare("True") || !attributeValue.compare("TRUE") )
            e->Set(attributeName, true);
        else if( !attributeValue.compare("false") || !attributeValue.compare("False") || !attributeValue.compare("FALSE") )
            e->Set(attributeName, false);
        else
            return "E: Wrong value for type boolean";
    }
    else if( !attributeType.compare("double") )
    {
        e->Set(attributeName, atof(attributeValue.c_str()));
    }
    else if( !attributeType.compare("string") )
    {
        e->Set(attributeName, attributeValue);
    }
    else if( !attributeType.compare("vector2") )
    {
        std::string val1 = "";
        std::string val2 = "";

        unsigned int ws = 0;
        for(unsigned int i = 0; i < attributeValue.length(); i++)
        {
            if(attributeValue[i] == ' ')
                ws++;

            if(ws == 0)
                val1 += attributeValue[i];
            else
                val2 += attributeValue[i];
        }

        vec4 v;
        v[0] = atof(val1.c_str());
        v[1] = atof(val2.c_str());

        e->Set(attributeName, v);
    }
    else if( !attributeType.compare("vector3") )
    {
        std::string val1 = "";
        std::string val2 = "";
        std::string val3 = "";

        unsigned int ws = 0;
        for(unsigned int i = 0; i < attributeValue.length(); i++)
        {
            if(attributeValue[i] == ' ')
                ws++;

            if(ws == 0)
                val1 += attributeValue[i];
            else if(ws == 1)
                val2 += attributeValue[i];
            else
                val3 += attributeValue[i];
        }

        vec4 v;
        v[0] = atof(val1.c_str());
        v[1] = atof(val2.c_str());
        v[2] = atof(val3.c_str());

        e->Set(attributeName, v);
    }
    else if( !attributeType.compare("vector4") )
    {
        std::string val1 = "";
        std::string val2 = "";
        std::string val3 = "";
        std::string val4 = "";

        unsigned int ws = 0;
        for(unsigned int i = 0; i < attributeValue.length(); i++)
        {
            if(attributeValue[i] == ' ')
                ws++;

            if(ws == 0)
                val1 += attributeValue[i];
            else if(ws == 1)
                val2 += attributeValue[i];
            else if(ws == 2)
                val3 += attributeValue[i];
            else
                val4 += attributeValue[i];
        }

        vec4 v;
        v[0] = atof(val1.c_str());
        v[1] = atof(val2.c_str());
        v[2] = atof(val3.c_str());
        v[3] = atof(val4.c_str());

        e->Set(attributeName, v);
    }
    else if( !attributeType.compare("quaternion") )
    {
        std::string val1 = "";
        std::string val2 = "";
        std::string val3 = "";
        std::string val4 = "";

        unsigned int ws = 0;
        for(unsigned int i = 0; i < attributeValue.length(); i++)
        {
            if(attributeValue[i] == ' ')
                ws++;

            if(ws == 0)
                val1 += attributeValue[i];
            else if(ws == 1)
                val2 += attributeValue[i];
            else if(ws == 2)
                val3 += attributeValue[i];
            else
                val4 += attributeValue[i];
        }

        quat q;
        q[0] = atof(val1.c_str());
        q[1] = atof(val2.c_str());
        q[2] = atof(val3.c_str());
        q[3] = atof(val4.c_str());

        e->Set(attributeName, q);
    }

    return "S: OK";
}
