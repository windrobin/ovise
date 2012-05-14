#ifndef XMLRPCMESSAGEAPI_H
#define XMLRPCMESSAGEAPI_H

#include <sstream>
#include <string>

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>

typedef Ogre::Vector2 vec2;
typedef Ogre::Vector3 vec3;
typedef Ogre::Vector4 vec4;
typedef Ogre::Quaternion quat;

/** Class that provides messages of type std::string for transmitting a xml-rpc message over network
*/
class XMLRPCMessageAPI
{
public:
	XMLRPCMessageAPI();
	virtual ~XMLRPCMessageAPI();

	/** Provides a std::string-message for inserting a new entity into the entity-pool
			\param _name is the name of the new entity
			\returns a std::string ready for transmitting
	*/
	virtual std::string insertEntityMsg(const std::string& _name) const;

	/** Provides a std::string-message for inserting a new entity into the entity-pool
			\param _name is the name of the new entity
			\param _id becomes the new entitys id
			\returns a std::string ready for transmitting
	*/
	virtual std::string insertEntityMsg(const std::string& _name, int _id) const;


	/** Provides a std::string-message for removing an entity from the entity-pool by name
			\param _name is the name of the entity which should be removed
			\returns a std::string ready for transmitting
	*/
	virtual std::string removeEntityMsg(const std::string& _name) const;

	/** Provides a std::string-message for removing an entity into the entity-pool by id
			\param _name is the name of the entity which should be removed
			\returns a std::string ready for transmitting
	*/
	virtual std::string removeEntityMsg(int _id) const;
//	virtual std::string getEntityById();
//	virtual std::string getEntityByName();

	/** not implemented yet
	*/
	virtual std::string removeEntitiesByAttributeMsg(const std::string& _attributeName) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds an integer value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, int _attributeValue) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a boolean value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, bool _attributeValue) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a double value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, double _attributeValue) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a std::string value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const std::string& _attributeValue) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec2 value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec2& _vec) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec3 value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec3& _vec) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec4 value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec4& _vec) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a quaternion value for the new attribute
			\returns a std::string ready for transmitting
	*/
	virtual std::string addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const quat& _quat) const;

	/** Removes an attribute from an entity of the entity-pool
			\param _entityName name of the entity from which the attribute should be removed
			\param _attributeName name of the attribute which should be removed
			\returns a std::string ready for transmitting
	*/
	virtual std::string removeAttributeMsg(const std::string& _entityName, const std::string& _attributeName) const;
};

#endif   // XMLRPCMESSAGEAPI_H
