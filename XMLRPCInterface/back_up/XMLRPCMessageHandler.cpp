#include "XMLRPCMessageHandler.h"

#include "../Core/EntityPool.h"

XMLRPCMessageHandler::XMLRPCMessageHandler(EntityPool* _entityPool)
:
m_entityPool(_entityPool)
{}

XMLRPCMessageHandler::~XMLRPCMessageHandler()
{}

int XMLRPCMessageHandler::HandleMessage(const char* _message)
{
    //std::cout << _message << std::endl;

    std::string header = getHTTPHeader(_message);
    /*std::cout << " > header: " << std::endl;
    std::cout << " ----------" << std::endl;
    std::cout << header;
    std::cout << std::endl;*/

    std::cout << std::endl;

    std::string content = getHTTPContent(_message);
    /*std::cout << " > content: " << std::endl;
    std::cout << " -----------" << std::endl;
    std::cout << content;
    std::cout << std::endl;*/

    int res = checkHTTPHeader(header);
    if(res < 0)
        return -1;
    else if(res == 1)
    {
        int r = handleMessageRPC2(content);
        if(r == -1)
            std::cout << " > handleMessageRPC2 returns with -1" << std::endl;
    }

    std::cout << " > message handling finished" << std::endl;

    return 0;
}

std::string XMLRPCMessageHandler::getHTTPHeader(const char* _message) const
{
    std::string mesg(_message);
    size_t pos = mesg.find("\r\n\r\n");
    std::string header = mesg.substr(0, pos);

    return header;
}

std::string XMLRPCMessageHandler::getHTTPContent(const char* _message) const
{
    std::string mesg(_message);
    size_t pos1 = mesg.find("\r\n\r\n");
    size_t pos2 = mesg.find("\r\n\r\n", pos1 + 1);
    std::string content = mesg.substr(pos1 + 4, pos2 - pos1 - 4);
    //std::cout << " > content pos 1: " << pos1 << " pos 2: " << pos2 << std::endl;

    /*for(size_t t = 0; t < content.length(); t++)
        if(content[t] == '\r')
            content.erase(t, 1);*/

    //std::cout << " > http content: " << content << std::endl;

    return content;
}

int XMLRPCMessageHandler::checkHTTPHeader(const std::string& _header)
{
    size_t pos1 = _header.find("POST");
    size_t pos2 = _header.find("\r\n");
    if(pos1 == std::string::npos)
        return -1;
    std::string post = _header.substr(pos1 + 4, pos2 - pos1 - 4);

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

    post = trimm(post);
    userAgent = trimm(userAgent);
    host = trimm(host);
    contentType = trimm(contentType);
    contentLength = trimm(contentLength);

    if(post == "/RPC2 HTTP/1.0" || post == "/RPC2 HTTP/1.1")
    {
        // check content-type
        if(contentType != "text/xml")
            return -1;

        return 1;
    }

    return 0;
}

std::string XMLRPCMessageHandler::trimm(const std::string& _str) const
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

int XMLRPCMessageHandler::handleMessageRPC2(const std::string& _content)
{
    std::string methodName;
    std::list< std::vector< std::string > > param_list;

    // ------- ofd
    std::cout << " > ### handleMessageRPC2 call ###" << std::endl;
    std::cout << " >    > _content: " << std::endl;
    std::cout << _content << std::endl;
    std::cout << " > ##############################" << std::endl;
    // --- end ofd

    try
    {
        //std::cout << " > parse document" << std::endl;
        m_document.parse< 0 >(const_cast< char* >((char*)(_content.c_str())));

        rapidxml::xml_node<>* rootNode = m_document.first_node("methodCall");
        if(!rootNode)
            return -1;

        rapidxml::xml_node<>* node = rootNode->first_node("methodName");
        if(!node)
            return -1;

        methodName = trimm(node->value());
        //std::cout << " > funcName: ." << methodName << "." << std::endl;

        rapidxml::xml_node<>* param_node = node->next_sibling("params")->first_node("param");
        /*if(!param_node)
            return -1;*/

        //std::cout << " > parse nodes" << std::endl;

        while(param_node)
        {
            //std::cout << " > chk_pnt 0" << std::endl;
            node = param_node->first_node();
            if(!node)
                return -1;

            //std::cout << " > chk_pnt 1" << std::endl;

            std::string strDataType = trimm(node->name());
            std::vector< std::string > param_vec;
            std::cout << " > data_type: ." << strDataType << "." << std::endl;
            if(!strDataType.compare("array"))       // check if we have an array
            {
        std::cout << " > enter branch array" << std::endl;
                rapidxml::xml_node<>* array_val_node = node->first_node()->first_node();
                std::string strType = trimm(array_val_node->first_node()->name());            // get type of container vec2, vec3, vec4 or quat
                param_vec.push_back(strType);
                std::string strValue = trimm(array_val_node->first_node()->value());
                param_vec.push_back(strValue);

                array_val_node = array_val_node->next_sibling("value");
                strType = trimm(array_val_node->first_node()->name());                        // this time get datatype of container
                param_vec.push_back(strType);
                while(array_val_node)
                {
                    if(trimm(array_val_node->first_node()->name()).compare(strType))
                        return -1;      // type change in scope of array

                    std::string strVal = trimm(array_val_node->first_node()->value());  // get data
                    param_vec.push_back(strVal);
                    array_val_node = array_val_node->next_sibling("value");
                }
                param_list.push_back(param_vec);
            }
            else if(!strDataType.compare("value"))
            {
        std::cout << " > enter branch value" << std::endl;
                strDataType = trimm(node->first_node()->name());
                std::string strDataValue = trimm(node->first_node()->first_node()->value());
                
                param_vec.push_back(strDataType);
                param_vec.push_back(strDataValue);

                param_list.push_back(param_vec);

                std::cout << " > datatype: ." << strDataType << ".";
                std::cout << " > value: ." << strDataValue << "." << std::endl;
            }
            else
            {
        std::cout << " > enter branch else" << std::endl;
                return -1;
            }

            param_node = param_node->next_sibling("param");
        }
    }
    catch(rapidxml::parse_error _pe)
    {
        std::cerr << " > Could not parse xmlrpc-message" << std::endl;
        std::cerr << " > what: " << _pe.what() << std::endl;
        return -1;
    }

    return callMethod(methodName, param_list);
}

/*int XMLRPCMessageHandler::HandleMessageOld(const char* _message)
{
    std::cout << _message << std::endl;

    std::string methodName;
    std::list< std::vector< std::string > > param_list;

    try
    {
        std::cout << " > parse document" << std::endl;
        m_document.parse< 0 >(const_cast< char* >(_message));

        rapidxml::xml_node<>* rootNode = m_document.first_node("methodCall");
        if(!rootNode)
            return -1;

        rapidxml::xml_node<>* node = rootNode->first_node("methodName");
        if(!node)
            return -2;

        //methodName = remAllSpaceCharInString(node->value());
        methodName = trimm(node->value());
        std::cout << " > funcName: " << methodName << std::endl;

        //int param_cnt = 0;
        //std::list< std::vector< std::string > > param_list;

        rapidxml::xml_node<>* param_node = node->next_sibling("params")->first_node("param");
        if(!param_node)
            return -2;

        //while(param_cnt < 10)
        while(param_node)
        {
            node = param_node->first_node("value");
            if(!node)
                return -2;

            //param_cnt++;

            node = node->first_node();
            //std::string strDatatype = remAllSpaceCharInString(node->name());
            std::string strDatatype = trimm(node->name());

            std::vector< std::string > param_vec;

            // check if we have an array
            if( !strDatatype.compare("array") )
            {
                //rapidxml::xml_node<>* array_val_node = node->first_node()->first_node();
                //while(array_val_node)
                //{
                //    std::string strType = remAllSpaceCharInString(array_val_node->first_node());            // get datatype
                //    std::string strVal = remAllSpaceCharInString(array_val_node->first_node()->value());    // get data
                //    param_vec.push_back(strType);
                //    param_vec.push_back(strVal);
                //    array_val_node = array_val_node->next_sibling("value");
                //}
                //param_list.push_back(param_vec);

                rapidxml::xml_node<>* array_val_node = node->first_node()->first_node();
                //std::string strType = remAllSpaceCharInString(array_val_node->first_node()->name());            // get type of container vec2, vec3, vec4 or quat
                std::string strType = trimm(array_val_node->first_node()->name());
                param_vec.push_back(strType);
                array_val_node = array_val_node->next_sibling("value");
                //strType = remAllSpaceCharInString(array_val_node->first_node()->name());                        // this time get datatype
                strType = trimm(array_val_node->first_node()->name());
                param_vec.push_back(strType);
                while(array_val_node)
                {
                    //if( remAllSpaceCharInString(array_val_node->first_node()->name()).compare(strType) )
                    if( trimm(array_val_node->first_node()->name()).compare(strType))
                        return -5;  // type change in scope of array

                    //std::string strVal = remAllSpaceCharInString(array_val_node->first_node()->value());    // get data
                    std::string strVal = trimm(array_val_node->first_node()->value());
                    param_vec.push_back(strVal);
                    array_val_node = array_val_node->next_sibling("value");
                }
                param_list.push_back(param_vec);
            }
            else
            {
                //std::string strDataValue = remAllSpaceCharInString(node->value());
                std::string strDataValue = trimm(node->value());

                param_vec.push_back(strDatatype);
                param_vec.push_back(strDataValue);

                param_list.push_back(param_vec);

                std::cout << " > datatype: " << strDatatype;
                std::cout << " value: " << strDataValue << std::endl;
            }

            param_node = param_node->next_sibling("param");
            //if(!param_node)
            //{
            //    std::cout << " > no more parameters" << std::endl;
            //    break;
            //}
        }
    }
    //catch(...)
    catch(rapidxml::parse_error _pe)
    {
        std::cerr << " > Could not parse xmlrpc-message" << std::endl;
        std::cerr << " > what: " << _pe.what() << std::endl;
        return -4;
    }

    if(!callMethod(methodName, param_list))
    {
        std::cerr << " > rpc method call failed" << std::endl;
        return -3;
    }

    return 0;
}*/

int XMLRPCMessageHandler::callMethod(const std::string& _methodName, const std::list< std::vector< std::string > >& _param_list)
{

    std::cout << " > ---------------------------------------------" << std::endl;
    std::cout << " > method to call: ." << _methodName << "." << std::endl;
    std::cout << " > parameter list: " << std::endl;
    std::list< std::vector< std::string > >::const_iterator it_param = _param_list.begin();
    while(it_param != _param_list.end())
    {
        std::vector< std::string > vec;
        vec = (*it_param);
        for(size_t t = 0; t < vec.size(); t++)
            std::cout << " > ." << vec[t] << ". ";
        std::cout << std::endl;
        it_param++;
    }
    std::cout << " > ---------------------------------------------" << std::endl;

    std::cout << " > call method: " << _methodName << std::endl;

    if( !(_methodName.compare("insertEntity")) )
    {
        if(_param_list.size() == 0 || _param_list.size() > 2)
        {
            std::cerr << " > _param_list size is empty or is greater than 2" << std::endl;
            return -1;
        }

        if( !insertEntity(_param_list) )
            return -1;
    }
    else if( !(_methodName.compare("removeEntity")) )
    {
        if(_param_list.size() != 1)
            return -1;

        if( !removeEntity(_param_list) )
            return -1;
    }
    else if( !(_methodName.compare("removeEntitiesByAttribute")) )
    {}
    else if( !(_methodName.compare("addAttribute")) )
    {
        if(_param_list.size() < 3 || _param_list.size() > 4)
            return -1;

        if( !addAttributeToEntity(_param_list) )
            return -1;
    }
    else if( !(_methodName.compare("removeAttribute")) )
    {}
    else if( !(_methodName.compare("closeConnectionMsg")) )
    { return 1; }
    else
    {
        std::cerr << " > method doesn't exist" << std::endl;
        return -1;
    }

    return 0;
}

bool XMLRPCMessageHandler::insertEntity(const std::list< std::vector< std::string > >& _param_list)
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
            m_entityPool->InsertEntity(new Entity(id));     // create and insert new entity in entity-pool
        }
        else if( !((param_vec.at(0)).compare("string")) )   // check datatype for name
        {
            std::string name = param_vec.at(1);
            Entity* e = new Entity();               // create new entity
            e->SetName(name);                       // give entity the name
            m_entityPool->InsertEntity(e);          // insert entity in entity-pool
        }
        else
            return false;
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
        m_entityPool->InsertEntity(e);

        //m_entityPool->InsertEntity(new Entity(name, id));
        //m_entityPool->InsertEntity(_param_list.pop_front().at(1), atoi(_param_list.pop_front().at(1)));
    }

    std::cout << " > return true" << std::endl;
    return true;
}

bool XMLRPCMessageHandler::removeEntity(const std::list< std::vector< std::string > >& _param_list)
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();
    std::vector< std::string > param_vec = *it;

    if(param_vec.at(0) == "i4" || param_vec.at(0) == "int")     // check datatype for id
    {
        int id = atoi( (const char*)((param_vec.at(1)).c_str()) );
        m_entityPool->RemoveEntity(m_entityPool->GetEntityById(id));    // remove entity by id
    }
    else if(param_vec.at(0) == "string")    // check datatype for name
    {
        std::string name = param_vec.at(1);
        m_entityPool->RemoveEntity(m_entityPool->GetEntityByName(name));    // remove entity by name
    }
    else
        return false;

    return true;
}

bool XMLRPCMessageHandler::addAttributeToEntity(const std::list< std::vector< std::string > >& _param_list)
{
    std::list< std::vector< std::string > >::const_iterator it = _param_list.begin();
    std::string name = (*it).at(1);
    it++;
    std::string attrName = (*it).at(1);
    it++;

    // get entity by name
    Entity* e = m_entityPool->GetEntityByName(name);

    if(_param_list.size() == 3)    // if value is of standard type then use this branch
    {
        std::string valueType = (*it).at(0);
        std::string value = (*it).at(1);

        if( (*it).size() == 2 )
        {
            if( !(valueType.compare("i4")) || !(valueType.compare("int")) )     // check for datatype int
                e->Set<int>( attrName, atoi( ((const char*)(value.c_str())) ) );
            else if( !(valueType.compare("boolean")) )                          // check for datatype boolean
            {
                bool val = ( !(value.compare("false")) || !(value.compare("FALSE")) ) ? 0 : 1;
                e->Set<bool>(attrName, val);
            }
            else if( !(valueType.compare("double")) )                           // check for datatype double
                e->Set<double>( attrName, atof( ((const char*)(value.c_str())) ) );
            else if( !(valueType.compare("string")) )                           // check for datatype string
                e->Set<std::string>(attrName, value);
            else
                return false;
        }
        else if( (*it).size() > 2 )     // we have an array; could be an vec2, vec3, vec4 or a quat (see Entity.h typdefs)
        {
            // on first position (i.e. (*it).at(0)) in the vector lies the container-type
            // on second position in the vector lies the datatype for the following data
            // behind the second position follows the data
            if( !(valueType.compare("vector2")) )
            {
                if( (*it).at(1).compare("double") )     // only double supportet yet
                {
                    double x = atof((const char*)((*it).at(2).c_str()));
                    double y = atof((const char*)((*it).at(3).c_str()));
                    
                    vec2 v(x, y);
                    e->Set<vec2>(attrName, v);
                }
            }
            else if( !(valueType.compare("vector3")) )
            {
                double x = atof((const char*)((*it).at(2).c_str()));
                double y = atof((const char*)((*it).at(3).c_str()));
                double z = atof((const char*)((*it).at(4).c_str()));
                
                vec3 v(x, y, z);
                e->Set<vec3>(attrName, v);
            }
            else if( !(valueType.compare("vector4")) )
            {
                double x = atof((const char*)((*it).at(2).c_str()));
                double y = atof((const char*)((*it).at(3).c_str()));
                double z = atof((const char*)((*it).at(4).c_str()));
                double w = atof((const char*)((*it).at(5).c_str()));

                vec4 v(x, y, z, w);
                e->Set<vec4>(attrName, v);
            }
            else if( !(valueType.compare("quaternion")) )
            {
                double w = atof((const char*)((*it).at(2).c_str()));
                double x = atof((const char*)((*it).at(3).c_str()));
                double y = atof((const char*)((*it).at(4).c_str()));
                double z = atof((const char*)((*it).at(5).c_str()));

                quat q(w, x, y, z);
                e->Set<quat>(attrName, q);
            }
            else
                return false;
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
