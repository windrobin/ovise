#ifndef OVISE_XMLRPC_MESSAGE_HANDLER_H
#define OVISE_XMLRPC_MESSAGE_HANDLER_H

#include <list>
#include <string>
#include <cstdlib>
#include <iostream>

#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "../Core/Entity.h"
#include "../Core/EntityPool.h"
#include "../rapidxml-1.13/rapidxml.hpp"

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
    std::string HandleMessage( const std::string& _message, HTTPReply& _reply );

    /** 
    */
    int HandleHTMLRequest(const HTTPRequest& _request, HTTPReply& _reply);

private:
	rapidxml::xml_document<>        mDocument;
	EntityPool*                     mEntityPool;

    std::string mRequestType;

    std::string GetHTTPHeader( const std::string& _message ) const;
    std::string GetHTTPContent( const std::string& _message ) const;
    int CheckHTTPHeader( const std::string& _header, HTTPReply& _reply );
    std::string Trimm( const std::string& _str ) const;
    std::string HandleMessageRPC2( const std::string& _content );

	std::string CallMethod( const std::string& _methodName, const std::list< std::vector< std::string > >& _param_list );

    std::string GetAllEntityNames() const;

    /** Insert a new entity in the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool InsertEntity( const std::list< std::vector< std::string > >& _param_list );

    /** Removes an entity from the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool RemoveEntity( const std::list< std::vector< std::string > >& _param_list );

    /** Removes entities from the entity pool which specified attribute
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool RemoveEntitiesByAttribute( const std::list< std::vector< std::string > >& _param_list );

    /** Adds a new attribute to an entity of the entity pool
            \param _param_list list of parameters which were retrieved from the message
            \returns true for success; false otherwise
    */
    bool AddAttributeToEntity( const std::list< std::vector< std::string > >& _param_list );

    std::string RemoveAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list);

    std::string GetAttributeNamesFromEntity( const std::list< std::vector< std::string > >& _param_list ) const;

    std::string GetAttributeFromEntity( const std::list< std::vector< std::string > >& _param_list ) const;

    std::string GetAttributeFromEntityId( const std::list< std::vector< std::string > >& _param_list ) const;

    std::string ChangeAttributeOfEntity( const std::list< std::vector< std::string > >& _param_list ) const;
};

#endif   // OVISE_XMLRPC_MESSAGE_HANDLER_H
