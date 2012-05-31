#ifndef OVISE_XMLRPCMESSAGEAPI_H
#define OVISE_XMLRPCMESSAGEAPI_H

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

	/** Provides a std::string-message for getting all entity names which lies in the entity-pool
			\param none
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAllEntityNamesMsg() const;

	/** Provides a std::string-message for inserting a new entity into the entity-pool
			\param _name is the name of the new entity
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string InsertEntityMsg( const std::string& _name ) const;

	/** Provides a std::string-message for inserting a new entity into the entity-pool
			\param _name is the name of the new entity
			\param _id becomes the new entitys id
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string InsertEntityMsg( const std::string& _name, int _id ) const;

	/** Provides a std::string-message for removing an entity from the entity-pool by name
			\param _name is the name of the entity which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntityMsg( const std::string& _name ) const;

	/** Provides a std::string-message for removing an entity into the entity-pool by id
			\param _name is the name of the entity which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntityMsg( int _id ) const;

	/** Provides a std::string-message for removing all entities with a common attribute-name
			\param _attributeName is a attribute-name
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntitiesByAttributeMsg( const std::string& _attributeName ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds an integer value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										int _attributeValue ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a boolean value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										bool _attributeValue ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a double value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										double _attributeValue ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a std::string value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										const std::string& _attributeValue ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec2 value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										const vec2& _vec ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec3 value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										const vec3& _vec ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a vec4 value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	//virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
	//									const vec4& _vec ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds a quaternion value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
										const quat& _quat ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param _entityName name of the entity which gets the new attribute
			\param _attributeType names the type of attribute
			\param _attributeName name of the new attribute
			\param _attributeValue holds value in string format for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& _entityName, const std::string& _attributeType,
										const std::string& _attributeName, const std::string& _attributeValue ) const;

	/** Provides a std::string-message to get a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAttributeMsg( const std::string& _entityName, const std::string& _attributeName ) const;

	/** Provides a std::string-message to get all attribute names of a given entity
			\param _entityName is the name of the entity
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAttributeNamesMsg( const std::string& _entityName ) const;

	/** Provides a std::string-message to remove an attribute from an entity of the entity-pool
			\param _entityName name of the entity from which the attribute should be removed
			\param _attributeName name of the attribute which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveAttributeMsg( const std::string& _entityName, const std::string& _attributeName ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new integer value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											int _attributeValue ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new boolean value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											bool _attributeValue ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new double value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											double _attributeValue ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new std::string value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											const std::string& _attributeValue ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new Ogre::Vector2 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											const vec2& _vec ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new Ogre::Vector3 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											const vec3& _vec ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new Ogre::Vector4 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	//virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
	//										const vec4& _vec ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeValue is the new Ogre::Quaternion value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											const quat& _quat ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param _entityName is the name of the entity
			\param _attributeName is the name of the attribute which will be changed
			\param _attributeType is the name of the attribute type as std::string (i.e. "int", "i4", "boolean", "double"
					"string", "vector2", "vector3", "vector4" and "quaternion")
			\param _attributeValue is the new Ogre::Vector2 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& _entityName, const std::string& _attributeName,
											const std::string& _attributeType, const std::string& _attributeValue ) const;
};

#endif   // OVISE_XMLRPCMESSAGEAPI_H
