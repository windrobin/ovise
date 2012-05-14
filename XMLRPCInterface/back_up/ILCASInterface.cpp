#include "ILCASInterface.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <PluginManager.h>

#include <iostream>


CILCASInterface::CILCASInterface( EntityPool& EntPool, const wxString& Name )
	: CNetworkInterface( EntPool, Name ), mMessageHandler( &EntPool )
{}


CILCASInterface::~CILCASInterface()
{
}

bool CILCASInterface::Start()
{
	// currently we don't care about different ports or host adresses
	// since this interface is listening passively
	mEndpoint.reset( new boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), 2121 ) );

	mAcceptor.reset( new boost::asio::ip::tcp::acceptor( mIOService, *mEndpoint ) );
	mSocket.reset( new boost::asio::ip::tcp::socket( mIOService ) );

	//mAcceptor->open( mEndpoint->protocol() );
	mAcceptor->set_option( boost::asio::ip::tcp::acceptor::reuse_address(true) );
	//mAcceptor->bind( *(mEndpoint.get()) );

	mAcceptor->listen();
	mAcceptor->async_accept( *mSocket, boost::bind( &CILCASInterface::AcceptHandler, this, _1 ) );
	mRunning = true;

	std::cout << "starting interface" << std::endl;
	return true;
}

bool CILCASInterface::Stop()
{
	// FIXME: Is this the way to do it?
	if( mSocket )
		mSocket->shutdown( boost::asio::ip::tcp::socket::shutdown_both );
	if( mAcceptor )
		mAcceptor->close();
	mRunning = false;

	return true;
}

void CILCASInterface::Poll()
{
	mIOService.poll_one();
	mIOService.reset();
}

void CILCASInterface::WriteHandler( const boost::system::error_code&,
									std::                size_t )
{}

void CILCASInterface::ReadHandler(
		const boost::system::error_code& Error,
		std::size_t
		BytesTransferred )
{
	if( Error )
		return;

	//std::cout << "-------------------" << std::endl;

	//std::cout <<
	//std::string( mBuffer.data(), BytesTransferred ) << std::endl;
	//std::cout << "-------------------" << std::endl;

	//std::cout << std::string(mBuffer.data(), BytesTransferred) << std::endl;

	//std::cout << "-------------------" << std::endl;

	//const char* Data = boost::asio::buffer_cast<const char*>(
	//		mStreamBuffer.data() );
	int Id = mMessageHandler.HandleMessage( std::string(mBuffer.data(), BytesTransferred).c_str()  );
	if(Id < 0)
        std::cout << " > message handling failed" << std::endl;
    else if(Id == 1)	// close connection to client and reopen for listening
    {
    	Stop();
    	Start();
    }
    else
    {
		//mStreamBuffer.consume( BytesTransferred );

		std::string ready = "ready\n";

		boost::asio::write( *mSocket, boost::asio::buffer( ready ) );
		//boost::lexical_cast<std::string>( Id ) ) );


		mSocket->async_read_some( boost::asio::buffer(mBuffer),
			boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );

		//boost::asio::async_read_until( *mSocket, mStreamBuffer, "</Entity>",
		//	boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );
	}
}

void CILCASInterface::AcceptHandler( const boost::system::error_code& Error )
{
	if( Error )
		return;
	std::cout << "accept handler called" << std::endl;
	boost::asio::write( *mSocket, boost::asio::buffer( "ready" ) );
	mSocket->async_read_some( boost::asio::buffer(mBuffer),
		boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );
}

extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterNetworkPlugin<CILCASInterface>( "ILCAS" );
}
