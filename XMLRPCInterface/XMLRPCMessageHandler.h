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
#include "../Viewer/AppContext.h"
#include "../Util/UtilityFunctions.h"

#include "HTTPReply.h"
#include "HTTPRequest.h"
#include "XMLRPCServerMessageAPI.h"

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
    XMLRPCMessageHandler( EntityPool* EntityPool );
    ~XMLRPCMessageHandler();

    /** Handles the message.
	        \param _message message in XML-RPC format
	        \returns failure code (success: 0; failure: -1)
	 */
    int HandleMessage( const std::string& Message, HTTPReply& Reply );

private:
	rapidxml::xml_document<>        mDocument;
	EntityPool*                     mEntityPool;

    std::string mRequestType;

    XMLRPCServerMessageAPI mRPCMesAPI;

    int HandleMessageRPC( const std::string& Content, std::string& Message );

	int CallMethod( const std::string& MethodName, const std::list< std::vector< std::string > >& ParamList, std::string& Message );

    int GetAllEntityNames( std::string& Message ) const;

    /** Insert a new entity in the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int InsertEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message );

    /** Removes an entity from the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int RemoveEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message );

    /** Removes entities from the entity pool which specified attribute
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int RemoveEntitiesByAttribute( const std::list< std::vector< std::string > >& ParamList, std::string& Message );

    /** Adds a new attribute to an entity of the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int AddAttributeToEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message );

    /** Removes an attribute from an entity of the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int RemoveAttributeFromEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message);

    /** Gets all attribute names form an entity
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int GetAttributeNamesFromEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const;

    /** Gets an attribute from an entity of the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int GetAttributeFromEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const;

    /** Gets an attribute from an entity by entity-id
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int GetAttributeFromEntityId( const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const;

    /** Changes an attribute of an entity of the entity pool
            \param ParamList list of parameters which were retrieved from the message
            \returns 0 for success; -1 otherwise
    */
    int ChangeAttributeOfEntity( const std::list< std::vector< std::string > >& ParamList, std::string& Message ) const;
};

#endif   // OVISE_XMLRPC_MESSAGE_HANDLER_H
