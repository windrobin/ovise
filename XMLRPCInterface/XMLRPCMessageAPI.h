#ifndef OVISE_XMLRPCMESSAGEAPI_H
#define OVISE_XMLRPCMESSAGEAPI_H

#include <sstream>
#include <string>
#include <typeinfo>
#include <exception>

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>

#include <boost/lexical_cast.hpp>

#include "WrongException.h"

typedef Ogre::Vector2 vec2;
typedef Ogre::Vector3 vec3;
//typedef Ogre::Vector4 vec4;
typedef Ogre::Quaternion quat;

/** Class that provides messages of type std::string for transmitting a xml-rpc message over network
*/
class XMLRPCMessageAPI
{
private:
	/** Creates the header of a XMLRPCMessage
			\param MsgName is the name of the function which will be called
			\returns the header as a std::string
	*/
	std::string GetXMLRPCMessageHeader(const std::string& MsgName) const;

	/** Creates the tail of a XMLRPCMessage
			\param none
			\returns the tail as a std::string
	*/
	std::string GetXMLRPCMessageTail() const;

	/** Creates a parameter part of type 'int', 'double', 'boolean' or 'std::string' for xmlrpc-message
			\param Val is the parameter for the message
			\returns a parameter part as a std::string
	*/
	template< class T >
	std::string GetParamString(const T& Val) const
	{
		std::stringstream msg;

		msg << "   <param>" << "\r\n";
		msg << "    <value> ";

		try
		{
			if(typeid(T) == typeid(int))
			{
				msg << "<i4> " << Val << " </i4>";
			}
			else if(typeid(T) == typeid(double))
			{
				msg << "<double> " << Val << " </double>";
			}
			else if(typeid(T) == typeid(bool))
			{
				msg << "<boolean> " << Val << " </boolean>";
			}
			else if(typeid(T) == typeid(std::string))
			{
				msg << "<string> " << Val << " </string>";
			}
			else
			{
				throw WrongDataTypeException();
			}
		}
		catch(std::exception& E)
		{
			throw E;
		}

		msg << " </value>" << "\r\n";
		msg << "   </param>" << "\r\n";

		return msg.str();
	};

	/** Creates a parameter part of type 'vector2', 'vector3' or 'quaternion' for xmlrpc-message
			\param NumComponents is the number of components of the vector of quaternion; it must be between 2
				and 4, if this is not the case it will throw a WrongParameterNumberException
			\param Val1, Val2, Val3 and Val4 are the components of the vector or quaternion which
				is the parameter for the message
			\returns a parameter part as a std::string
	*/
	virtual std::string GetArrayParamString(size_t NumComponents, double Val1, double Val2, double Val3=0.f, double Val4=0.f) const;

	/** Creates a std::string-message for adding a new attribute to an entity of the entity-pool
			\param EntityName name of the entity which gets the new attribute
			\param AttributeName name of the new attribute
			\param DataString is already a parameter part of the message, which is created before
				the call of this function
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeCreateMsg(const std::string& EntityName, const std::string& AttributeName,
												const std::string& DataString) const;

	/** Creates a std::string-message for changing an existing attribute to an entity of the entity-pool
			\param EntityName name of the entity which has the attribute
			\param AttributeName name of the attribute that should be changed
			\param DataString is already a parameter part of the message, wich is created before
				the call of this function
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeCreateMsg(const std::string& EntityName, const std::string& AttributeName,
													const std::string& DataString) const;

public:
	XMLRPCMessageAPI();
	virtual ~XMLRPCMessageAPI();

	/** Provides a std::string-message for getting all entity names which lies in the entity-pool
			\param none
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAllEntityNamesMsg() const;

	/** Provides a std::string-message for inserting a new entity into the entity-pool
			\param Name is the name of the new entity
			\param Id becomes the new entitys id, if it is greater or equal than 0
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string InsertEntityMsg( const std::string& Name, int Id=-1 ) const;

	/** Provides a std::string-message for removing an entity from the entity-pool by name
			\param Name is the name of the entity which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntityMsg( const std::string& Name ) const;

	/** Provides a std::string-message for removing an entity into the entity-pool by id
			\param Name is the name of the entity which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntityMsg( int Id ) const;

	/** Provides a std::string-message for removing all entities with a common attribute-name
			\param AttributeName is a attribute-name
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveEntitiesByAttributeMsg( const std::string& AttributeName ) const;

	/** It's a wrapper method for adding a new attribute to an entity of the entity-pool
		for the datatypes: 'int', 'double', 'bool' and 'std::string', otherwise
		a WrongDataTypeException will be thrown
			\param EntityName name of the entity which gets the new attribute
			\param AttributeName name of the new attribute
			\param AttributeValue holds value(of type 'int', 'double', 'bool' or 'std::string', otherwise
				a WrongDataTypeException will be thrown) for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	template< class T >
	std::string AddAttributeMsg(const std::string& EntityName, const std::string& AttributeName,
							const T& AttributeValue) const
	{
		try
		{
			if(typeid(T) != typeid(int) && typeid(T) != typeid(double) && typeid(T) != typeid(bool)
				&& typeid(T) != typeid(std::string))
				throw WrongDataTypeException();

			return AddAttributeCreateMsg(EntityName, AttributeName, GetParamString(AttributeValue));
		}
		catch(std::exception& E)
		{
			throw E;
		}
	};

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param EntityName name of the entity which gets the new attribute
			\param AttributeName name of the new attribute
			\param AttributeValue holds a vec2 value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
										const vec2& Vec ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param EntityName name of the entity which gets the new attribute
			\param AttributeName name of the new attribute
			\param AttributeValue holds a vec3 value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
										const vec3& Vec ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
			\param EntityName name of the entity which gets the new attribute
			\param AttributeName name of the new attribute
			\param AttributeValue holds a quaternion value for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
										const quat& Quat ) const;

	/** Provides a std::string-message for adding a new attribute to an entity of the entity-pool
		It's just useful for console-clients, you shouldn't use it if not necessary
			\param EntityName name of the entity which gets the new attribute
			\param AttributeType names the type of attribute
			\param AttributeName name of the new attribute
			\param AttributeValue holds value in string format for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AddAttributeMsg( const std::string& EntityName, const std::string& AttributeType,
										const std::string& AttributeName, const std::string& AttributeValue ) const;

	/** Provides a std::string-message to get a value of an attribute of a given entity
			\param EntityName is the name of the entity
			\param AttributeName is the name of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAttributeMsg( const std::string& EntityName, const std::string& AttributeName ) const;

	/** Provides a std::string-message to get all attribute names of a given entity
			\param EntityName is the name of the entity
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string GetAttributeNamesMsg( const std::string& EntityName ) const;

	/** Provides a std::string-message to remove an attribute from an entity of the entity-pool
			\param EntityName name of the entity from which the attribute should be removed
			\param AttributeName name of the attribute which should be removed
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string RemoveAttributeMsg( const std::string& EntityName, const std::string& AttributeName ) const;

	/** It's a wrapper method for changing an existing attribute of an entity of the entity-pool
		for the datatypes: 'int', 'double', 'bool' and 'std::string', otherwise
		a WrongDataTypeException will be thrown
			\param EntityName name of the entity which has the attribute
			\param AttributeName name of the attribute that should be changed
			\param AttributeValue holds value(of type 'int', 'double', 'bool' or 'std::string', otherwise
				a WrongDataTypeException will be thrown) for the new attribute
			\returns a std::string ready for transmitting as message
	*/
	template< class T >
	std::string ChangeAttributeMsg(const std::string& EntityName, const std::string& AttributeName,
									const T& AttributeValue) const
	{
		try
		{
			if(typeid(T) != typeid(int) && typeid(T) != typeid(double) && typeid(T) != typeid(bool)
				&& typeid(T) != typeid(std::string))
				throw WrongDataTypeException();

			return ChangeAttributeCreateMsg(EntityName, AttributeName, GetParamString(AttributeValue));
		}
		catch(std::exception& E)
		{
			throw E;
		}
	};

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param EntityName is the name of the entity
			\param AttributeName is the name of the attribute which will be changed
			\param AttributeValue is the new Ogre::Vector2 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
											const vec2& Vec ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param EntityName is the name of the entity
			\param AttributeName is the name of the attribute which will be changed
			\param AttributeValue is the new Ogre::Vector3 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
											const vec3& Vec ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
			\param EntityName is the name of the entity
			\param AttributeName is the name of the attribute which will be changed
			\param AttributeValue is the new Ogre::Quaternion value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
											const quat& Quat ) const;

	/** Provides a std::string-message for changing a value of an attribute of a given entity
		It's just useful for console-clients, you shouldn't use it if not necessary
			\param EntityName is the name of the entity
			\param AttributeName is the name of the attribute which will be changed
			\param AttributeType is the name of the attribute type as std::string (i.e. "int", "i4", "boolean", "double"
					"string", "vector2", "vector3", "vector4" and "quaternion")
			\param AttributeValue is the new Ogre::Vector2 value for the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string ChangeAttributeMsg( const std::string& EntityName, const std::string& AttributeName,
											const std::string& AttributeType, const std::string& AttributeValue ) const;
};

#endif   // OVISE_XMLRPCMESSAGEAPI_H
