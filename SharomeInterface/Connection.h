#ifndef SHAROME_CONNECTION_H
#define SHAROME_CONNECTION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>



/**
 @brief Represents a network connection.
 @author Alexander Kasper
 @date 14-06-2010
 @brief This class represents a network connection between client and server. It enables synchronous and asynchronous
 message transfer inbetween them. This class is heavily based on the serialization example from the boost library,
 which can be found here: http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html
*/
class CConnection
{
public:
	CConnection( boost::asio::io_service& IO_Service )
		: m_Socket( IO_Service ), m_Strand( IO_Service ) {}

	void set_result( boost::optional<boost::system::error_code>* a, boost::system::error_code b ) 
	{		
		a->reset(b); 
	}

	/// Return the socket of this connection
	boost::asio::ip::tcp::socket& Socket() { return m_Socket; }

	/// Write message to network, return immediately and invoke the given handler on completion of the write operation.
	template<typename T, typename Handler>
	void AsyncWrite( boost::shared_ptr<T> t, Handler hdlr );

	/// Write message to network and block until write operation completes
	template<typename T>
	bool SyncWrite( boost::shared_ptr<T> t, int TimeoutMS = 1000 );

	/// Issue read command, return immediately and invoke handler on completion of read operation.
	template<typename T, typename Handler>
	void AsyncRead( boost::shared_ptr<T> t, Handler hdlr );

	/// Read from network and block until it completes.
	template<typename T>
	bool SyncRead( T& t, int TimeoutMS = 1000 );

	/// Internal function to handle asynchronous read.
	template<typename T, typename Handler>
	void HandleReadHeader( const boost::system::error_code& Error, boost::shared_ptr<T> t, boost::tuple<Handler> hdler );

	/// Internal function to handle asynchronous read.
	template<typename T, typename Handler>
	void HandleReadData( const boost::system::error_code& Error, boost::shared_ptr<T> t, boost::tuple<Handler> hdler );

private:
	boost::asio::ip::tcp::socket m_Socket;
	
	static const unsigned int HeaderLength = 8;

	/// Holds an outbound header.
	std::string m_OutboundHeader;

	/// Holds the outbound data.
	std::string m_OutboundData;

	/// Holds an inbound header.
	char m_InboundHeader[HeaderLength];

	/// Holds the inbound data.
	std::vector<char> m_InboundData;

	/// Strand for synchronisation
	boost::asio::io_service::strand m_Strand;
};

typedef boost::shared_ptr<CConnection> ConnectionPtr;

template<typename T, typename Handler> inline
void CConnection::AsyncWrite( boost::shared_ptr<T> t, Handler hdlr )
{
	// Serialize data
	std::ostringstream ArchiveStream;
	boost::archive::text_oarchive Archive(ArchiveStream);
	Archive << *t;
	m_OutboundData = ArchiveStream.str();

	// Format header
	std::ostringstream HeaderStream;
	HeaderStream << std::setw( HeaderLength )
		<< std::hex << m_OutboundData.size();

	if(!HeaderStream || HeaderStream.str().size() != HeaderLength)
	{
		boost::system::error_code Error(boost::asio::error::invalid_argument);
		m_Socket.io_service().post( 
			m_Strand.wrap( boost::bind( hdlr, Error ) ) );
		return;
	}
	m_OutboundHeader = HeaderStream.str();

	// Write data to header
	std::vector<boost::asio::const_buffer> Buffers;
	Buffers.push_back( boost::asio::buffer( m_OutboundHeader ) );
	Buffers.push_back( boost::asio::buffer( m_OutboundData ) );
	boost::asio::async_write( m_Socket, Buffers, 
		m_Strand.wrap( hdlr ) );
}

template<typename T> inline
bool CConnection::SyncWrite( boost::shared_ptr<T> t, int TimeoutMS )
{
	// Serialize data
	std::ostringstream ArchiveStream;
	boost::archive::text_oarchive Archive( ArchiveStream );
	Archive << *t;
	m_OutboundData = ArchiveStream.str();

	// Format header
	std::ostringstream HeaderStream;
	HeaderStream << std::setw( HeaderLength )
		<< std::hex << m_OutboundData.size();

	if( !HeaderStream || HeaderStream.str().size() != HeaderLength )
	{
		boost::system::error_code Error( boost::asio::error::invalid_argument );
		std::cerr << Error.message() << std::endl;
		return false;
	}
	m_OutboundHeader = HeaderStream.str();

	// Write data to header
	std::vector<boost::asio::const_buffer> Buffers;
	Buffers.push_back(boost::asio::buffer( m_OutboundHeader ) );
	Buffers.push_back(boost::asio::buffer( m_OutboundData ) );
	
	// Use timer and async_write to create sync_write with timeout
	// see: http://lists.boost.org/Archives/boost/2007/04/120339.php
	boost::optional<boost::system::error_code> timer_result; 
	boost::asio::deadline_timer timer( m_Socket.io_service() ); 
	timer.expires_from_now( boost::posix_time::milliseconds( TimeoutMS ) ); 
	timer.async_wait( boost::bind( &CConnection::set_result, this, &timer_result, _1 ) ); 
	boost::optional<boost::system::error_code> read_result; 
	boost::asio::async_write( m_Socket, Buffers, 
		boost::bind( &CConnection::set_result, this, &read_result, _1 ) ); 
  
	m_Socket.io_service().reset(); 
	while( m_Socket.io_service().run_one() ) 
	{ 
	  if( read_result ) 
		timer.cancel(); 
	  else if ( timer_result ) 
		m_Socket.cancel(); 
	} 
	if ( !read_result ) 
	  return false;

	return true;
}

template<typename T, typename Handler> inline
void CConnection::AsyncRead( boost::shared_ptr<T> t, Handler hdlr )
{
	// Issue a read operation to read exactly the number of bytes in a header.
	void (CConnection::*f)(const boost::system::error_code&,
		boost::shared_ptr<T>, boost::tuple<Handler>) = &CConnection::HandleReadHeader<T, Handler>;
	
	boost::asio::async_read( m_Socket, boost::asio::buffer(m_InboundHeader),
		m_Strand.wrap( boost::bind(f, this, boost::asio::placeholders::error, t,
		  boost::make_tuple( hdlr ) ) ) );
}

template<typename T> inline
bool CConnection::SyncRead( T& t, int TimeoutMS )
{
	// emulate syncread with timeout by async-reading the header
	// see syncwrite
	boost::optional<boost::system::error_code> timer_result; 
	boost::asio::deadline_timer timer( m_Socket.io_service() ); 
	timer.expires_from_now( boost::posix_time::milliseconds( TimeoutMS ) ); 
	timer.async_wait( boost::bind( &CConnection::set_result, this, &timer_result, _1 ) ); 
	boost::optional<boost::system::error_code> read_result; 
	boost::asio::async_read( m_Socket, boost::asio::buffer( m_InboundHeader ),
		boost::bind( &CConnection::set_result, this, &read_result, _1 ) ); 
  
	m_Socket.io_service().reset(); 
	while( m_Socket.io_service().run_one() ) 
	{ 
	  if( read_result ) 
		timer.cancel(); 
	  else if( timer_result ) 
		m_Socket.cancel(); 
	} 
	if( !read_result ) 
	  return false;

	std::istringstream is( std::string( m_InboundHeader, HeaderLength ) );
	std::size_t InboundDataSize = 0;
	if( !( is >> std::hex >> InboundDataSize ) )
	{
		boost::system::error_code E( boost::asio::error::invalid_argument );
		std::cerr << E.message() << std::endl;
		return false;
	}

	m_InboundData.resize( InboundDataSize );
	boost::asio::read( m_Socket, boost::asio::buffer( m_InboundData ) );

	try
	{
		std::string ArchiveData( &m_InboundData[0], m_InboundData.size() );
		std::istringstream ArchiveStream( ArchiveData );
		boost::archive::text_iarchive Archive( ArchiveStream );
		Archive >> t;
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

template<typename T, typename Handler> inline
void CConnection::HandleReadHeader( const boost::system::error_code& Error, boost::shared_ptr<T> t, boost::tuple<Handler> hdler )
{
	if( Error )
		boost::get<0>( hdler )( Error );
	else
	{
		std::istringstream is( std::string( m_InboundHeader, HeaderLength ) );
		std::size_t InboundDataSize = 0;
		if( !( is >> std::hex >> InboundDataSize ) )
		{
			boost::system::error_code E( boost::asio::error::invalid_argument );
			boost::get<0>( hdler )( E );
			return;
		}

		m_InboundData.resize(InboundDataSize);
		void (CConnection::*f)( const boost::system::error_code&,
			boost::shared_ptr<T>, boost::tuple<Handler> )
			= &CConnection::HandleReadData<T,Handler>;
		boost::asio::async_read( m_Socket, boost::asio::buffer( m_InboundData ),
			m_Strand.wrap( boost::bind( f, this, boost::asio::placeholders::error,
						   t, hdler ) ) );
	}
}

template<typename T, typename Handler> inline
void CConnection::HandleReadData( const boost::system::error_code& Error, boost::shared_ptr<T> t, boost::tuple<Handler> hdler )
{
	if( Error )
		boost::get<0>( hdler )( Error );
	else
	{
		try
		{
			std::string ArchiveData( &m_InboundData[0], m_InboundData.size() );
			std::istringstream ArchiveStream( ArchiveData );
			boost::archive::text_iarchive Archive( ArchiveStream );
			Archive >> *t.get();
		}
		catch ( std::exception& e )
		{
			std::cerr << e.what() << std::endl;
			boost::system::error_code error( boost::asio::error::invalid_argument );
			boost::get<0>( hdler )( error );
			return;
		}

		boost::get<0>( hdler )( Error );
	}
}

#endif //SHAROME_CONNECTION_H
