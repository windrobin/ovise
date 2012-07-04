#ifndef OVISE_XMLRPC_SERVER_MESSAGEAPI_H
#define OVISE_XMLRPC_SERVER_MESSAGEAPI_H

#include <sstream>
#include <string>

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>

#include "WrongException.h"

typedef Ogre::Vector2 vec2;
typedef Ogre::Vector3 vec3;
typedef Ogre::Vector4 vec4;
typedef Ogre::Quaternion quat;

class XMLRPCServerMessageAPI
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

	/** Creates a parameter part of type 'vector2', 'vector3', 'vector4' or 'quaternion' for xmlrpc-response-message
			\param NumComponents is the number of components of the vector of quaternion; it must be between 2
				and 4, if this is not the case it will throw a WrongParameterNumberException
			\param Val1, Val2, Val3 and Val4 are the components of the vector or quaternion which
				is the parameter for the response message
	*/
	virtual std::string GetArrayParamString(size_t NumComponents, double Val1, double Val2, double Val3=0.f, double Val4=0.f) const;

	/** Creates a std::string-response-message for an attribute
			\param DataString is already a parameter part of the message, which is created before
				the call of this function
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AttributeCreateResponseMsg(const std::string& DataString) const;

public:
	XMLRPCServerMessageAPI();
	virtual ~XMLRPCServerMessageAPI();

	/** Provides a response std::string-message for an error
		\param Error is a std::string which contains an error message
		\returns a std::string ready for transmitting as message
	*/
	virtual std::string ErrorResponseMsg( const std::string& Error ) const;

	/** Provides a response std::string-message for a status
		\param Status is a std::string which contains a status message
		\returns a std::string ready for transmitting as message
	*/
	virtual std::string StatusResponseMsg( const std::string& Status ) const;

	/** Provides a response std::string-message for all entity names which are in entity-pool
			\param Names is a std::list of all entity names within the entity-pool
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AllEntityNamesResponseMsg( const std::vector< std::string >& Names ) const;

	/** It's a wrapper method for a attribute-response-message for the datatypes: 'int', 'double', 'bool'
		and 'std::string', otherwise a WrongDataTypeException will be thrown
			\param Val is the value of the attribute
			\returns a std::string ready for transmitting as message
	*/
	template< class T >
	std::string AttributeResponseMsg(const T& Val) const
	{
		try
		{
			if(typeid(T) != typeid(int) && typeid(T) != typeid(double) && typeid(T) != typeid(bool)
				&& typeid(T) != typeid(std::string))
				throw WrongDataTypeException();

			return AttributeCreateResponseMsg(GetParamString(Val));
		}
		catch(std::exception& E)
		{
			throw E;
		}
	};

	/** Provides a response std::string-message for an attribute value of an entity
			\param Val is the value of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AttributeResponseMsg( const vec2& Val ) const;

	/** Provides a response std::string-message for an attribute value of an entity
			\param Val is the value of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AttributeResponseMsg( const vec3& Val ) const;

	/** Provides a response std::string-message for an attribute value of an entity
			\param Val is the value of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AttributeResponseMsg( const vec4& Val ) const;

	/** Provides a response std::string-message for an attribute value of an entity
			\param Quat is the value of the attribute
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AttributeResponseMsg( const quat& Quat ) const;

	/**	Provides a response std::string-message for the request of all attribute-names of an entity
			\param Names is a std::list of all entity attributes
			\returns a std::string ready for transmitting as message
	*/
	virtual std::string AllAttributeNamesResponseMsg( const std::vector< std::string >& Names ) const;
};

#endif   // OVISE_XMLRPC_SERVER_MESSAGEAPI_H
