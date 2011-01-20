#include "ILCASInterface.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>


CILCASInterface::CILCASInterface( boost::asio::io_service& IOService, EntityPool& EntPool )
	: CNetworkInterface( IOService, EntPool ),
	mEndpoint( boost::asio::ip::tcp::v4(), 2121 ),
	mAcceptor( mIOService ),
	mSocket( mIOService ),
	mMessageHandler( &EntPool )
{
	mAcceptor.listen();
	mAcceptor.async_accept( mSocket,
		boost::bind( &CILCASInterface::AcceptHandler, this, _1 ) );
}


CILCASInterface::~CILCASInterface(void)
{
}

void CILCASInterface::WriteHandler( const boost::system::error_code&, std::size_t )
{
}

void CILCASInterface::ReadHandler( const boost::system::error_code& Error, std::size_t BytesTransferred )
{
	if( Error )
		return;

	std::cout << std::string( mBuffer.data(), BytesTransferred ) << std::endl;

	const char* Data = boost::asio::buffer_cast<const char*>( mStreamBuffer.data() );
	int Id = mMessageHandler.HandleMessage( Data );
	mStreamBuffer.consume( BytesTransferred );

	boost::asio::write( mSocket, boost::asio::buffer( boost::lexical_cast<std::string>( Id ) ) );

	boost::asio::async_read_until( mSocket, mStreamBuffer, "</Entity>", 
		boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );
}

void CILCASInterface::AcceptHandler( const boost::system::error_code& Error )
{
	if( Error )
		return;

	boost::asio::write( mSocket, boost::asio::buffer( "ready" ) );
	boost::asio::async_read_until( mSocket, mStreamBuffer, "</Entity>", 
		boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );
}
