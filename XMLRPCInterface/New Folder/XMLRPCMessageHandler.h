#ifndef XMLRPC_MESSAGE_HANDLER_H
#define XMLRPC_MESSAGE_HANDLER_H

#include <list>
#include <string>
#include <cstdlib>

#include "../Core/Entity.h"
#include "../Core/EntityPool.h"
//#include "../rapidxml-1.13/rapidxml.hpp"

#include "HTTPReply.h"
#include "HTTPRequest.h"

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>

typedef Ogre::Vector2 vec2;
typedef Ogre::Vector3 vec3;
typedef Ogre::Vector4 vec4;
typedef Ogre::Quaternion quat;

struct stMethodCallInfo
{
    std::string     methohdName;
    unsigned int    numParams;
    void*           methodPtr;
};

/** Class that processes a XML-RPC network message.
        Parses a message recieved by the Socket, and proceed the named method in the message
 */
class XMLRPCMessageHandler
{
public:
    XMLRPCMessageHandler( EntityPool* _entityPool );
    ~XMLRPCMessageHandler();

    /** Handles the message.
	        \param _message message in XML-RPC format
	        \returns failure code (success: 0; failure: -1)
	 */
    //int HandleMessage( const char* _message );
    int HandleRequest(const std::string& _content, HTTPReply& _reply);
    int HandleHTMLRequest(const HTTPRequest& _request, HTTPReply& _reply);

    //void addMethodToList();

private:
	//rapidxml::xml_document<>        m_document;
	EntityPool*                     m_entityPool;

    std::string m_requestType;

    //std::string getHTTPHeader(const char* _message) const;
    //std::string getHTTPContent(const char* _message) const;
    //int checkHTTPHeader(const std::string& _header);
    std::string trimm(const std::string& _str) const;
    int handleMessageRPC2(const std::string& _content);

    //std::string remAllSpaceCharInString(const std::string& _str) const;
	int callMethod(const std::string& _methodName, const std::list< std::vector< std::string > >& _param_list);


    /** Insert a new entity in the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool insertEntity(const std::list< std::vector< std::string > >& _param_list);

    /** Removes an entity from the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool removeEntity(const std::list< std::vector< std::string > >& _param_list);

    /** Adds a new attribute to an entity of the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool addAttributeToEntity(const std::list< std::vector< std::string > >& _param_list);
};

#endif   // XMLRPC_MESSAGE_HANDLER_H
