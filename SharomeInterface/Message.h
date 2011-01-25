#ifndef SHAROME_MESSAGE_H
#define SHAROME_MESSAGE_H

#include <string>
#include <Util/LZW.hpp>

#include <boost/serialization/vector.hpp>

namespace Comm {

const int MSG_OK		= 0;  /// returned from server on successful update/send/del
const int MSG_UPDATE	= 10; /// message contains update data
const int MSG_GET		= 11; /// retrieve obj with given Id/Name
const int MSG_GETONCE	= 12; /// retrieve obj with given Id/Name but do not sync
const int MSG_SEND		= 13; /// send data but do not receive further updates
const int MSG_DEL		= 14; /// delete object (use carefully!)

const int MSG_ERROR		= -1; /// some error occured

const int TYPE_CVAL		= 100; /// currently unused
const int TYPE_CATTR	= 101; /// currently unused
const int TYPE_COBJ		= 102; /// message contains a CObj
const int TYPE_ID		= 103; /// message contains object id
const int TYPE_NAME		= 104; /// message contains object name
const int TYPE_CSCENE	= 105; /// message contains CScene
const int TYPE_UDEF		= 130; /// message contains undefined stuff

/**
 @brief Class defining a network message.
 @detail Currently the message class consists of a code, data type and string data.
 @author Alexander Kasper
 @date 14-06-2010
*/
class Message
{
	friend class boost::serialization::access;

public:
	/// Default constructor
	Message() : m_Code( MSG_ERROR ), m_Type( TYPE_UDEF ) {}
	/// Constructor taking arguments
	Message( const int Code, const int Type, std::string& Data )
		: m_Code( Code ), m_Type( Type )
	{
		OOWM::Util::compress( Data, std::back_inserter( m_Data ) );
	}
	/// Message code, describes nature of the message.
	int m_Code;
	/// Type of the data
	int m_Type;
	/// Data of the message compressed.
	std::vector<int> m_Data;

	/// Prints the contents of the message.
	void print( bool PrintData = false ) const
	{
		std::cout << "MESSAGE" << std::endl;
		std::cout << "----------------------------" << std::endl;
		std::cout << "Code: " << m_Code << std::endl;
		std::cout << "Type: " << m_Type << std::endl;
		std::cout << "Data size compressed: " << m_Data.size() << std::endl;
		std::cout << "Data size uncompressed: " << GetData().size() << std::endl;
		if( PrintData )
			std::cout << "Data: " << GetData() << std::endl;
	}

	/// Used to serialize the message in binary form for network transmission.
	template<typename Archive>
	void serialize( Archive& ar, const unsigned int version );

	void SetData( std::string Data )
	{
		m_Data.clear();
		OOWM::Util::compress( Data, std::back_inserter( m_Data ) );
	}

	const std::string GetData() const
	{
		if( m_Data.size() > 0 )
			return OOWM::Util::decompress( m_Data.begin(), m_Data.end() );
		else return "";
	}

	const std::string GetLogMsg( bool Data = false ) const
	{
		std::stringstream str;
		str << "[" << m_Code << "][" << m_Type << "]";
		if( Data )
			str << "[" << GetData() << "]";
		return str.str();
	}

	const Message& operator=( const Message& rhs )
	{
		m_Code = rhs.m_Code;
		m_Type = rhs.m_Type;
		m_Data = rhs.m_Data;
		return *this;
	}
};

template<typename Archive> inline
void Message::serialize( Archive& ar, const unsigned int version )
{
	ar & m_Code;
	ar & m_Type;
	ar & m_Data;
}

} // end of namespace Comm

BOOST_CLASS_TRACKING( Comm::Message, boost::serialization::track_never )

#endif // SHAROME_MESSAGE_H
