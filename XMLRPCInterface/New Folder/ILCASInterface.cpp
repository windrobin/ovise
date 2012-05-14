#include "ILCASInterface.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <PluginManager.h>

#include <iostream>


CILCASInterface::CILCASInterface( EntityPool& EntPool, const wxString& Name )
	:
	CNetworkInterface( EntPool, Name ),
	mMessageHandler( &EntPool )
{}


CILCASInterface::~CILCASInterface()
{}

bool CILCASInterface::Start()
{
	// currently we don't care about different ports or host adresses
	// since this interface is listening passively
	mEndpoint.reset( new boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), 2121 ) );

	mAcceptor.reset( new boost::asio::ip::tcp::acceptor( mIOService, *mEndpoint ) );
	mSocket.reset( new boost::asio::ip::tcp::socket( mIOService ) );
	mStrand.reset( mIOService );

	//mAcceptor->open( mEndpoint->protocol() );
	mAcceptor->set_option( boost::asio::ip::tcp::acceptor::reuse_address(true) );
	//mAcceptor->bind( *(mEndpoint.get()) );

	mAcceptor->listen();
	mAcceptor->async_accept( *mSocket, boost::bind( &CILCASInterface::AcceptHandler, this, _1 ) );
	mRunning = true;

	std::cout << "starting interface" << std::endl;

	mSocket.async_read_some(boost::asio::buffer(mBuffer), mStrand.wrap(boost::bind(&CILCASInterface::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));

	return true;
}

bool CILCASInterface::Stop()
{
	// FIXME: Is this the way to do it?
	if( mSocket )
		mSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	if( mAcceptor )
		mAcceptor->close();
	mRunning = false;

	//return true;

	mIOService.stop();
	std::cout << "interface stopped" << std::endl;

	return true;
}

void CILCASInterface::Poll()
{
	mIOService.poll_one();
	mIOService.reset();
}

/*void CILCASInterface::WriteHandler( const boost::system::error_code&,
									std::                size_t )
{}*/

/*void CILCASInterface::ReadHandler(
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
}*/

void CILCASInterface::handleRead(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	if(!_ec)
	{
		boost::tribool result;
		boost::tie(result, boost::tuples::ignore) = mRequestParser.Parse(mRequest, mBuffer.data(), mBuffer.data() + _bytes_transferred);

		if(result)
		{
			if(mRequest.Method == "GET")
			{
				mMessageHandler.HandleHTMLRequest(mRequest, mReply);
				boost::asio::async_write(mSocket, mReply.ToBuffers(), mStrand.wrap(boost::bind(&CILCASInterface::handleWrite, this, boost::asio::placeholders::error)));
			}
			else if(mRequest.Method == "POST")
			{
				int content_length = 0;
				for(std::vector<HTTPHeader>::iterator it = mRequest.Headers.begin(); it != mRequest.Headers.end(); it++)
				{
					if(it->Name == "Content-Length")
					{
						std::istringstream s(it->Value);
						s >> content_length;
						break;
					}
				}
				if(content_length > 0)
				{
					boost::asio::async_read(mSocket, boost::asio::buffer(mBuffer), boost::asio::transfer_at_least(content_length), mStrand.wrap(boost::bind(&CILCASInterface::handleReadContent, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
				}
			}
		}
		else if(!result)
		{
			mReply = HTTPReply::StockReply(HTTPReply::bad_request);
			boost::asio::async_write(mSocket, mReply.ToBuffers(), mStrand.wrap(boost::bind(&CILCASInterface::handleWrite, this, boost::asio::placeholders::error)));
		}
		else
		{
			mSocket.async_read_some(boost::asio::buffer(mBuffer), mStrand.wrap(boost::bind(&CILCASInterface::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
		}
	}

	// If an error occurs then no new asynchronous operations are started. This
	// means that all shared_ptr references to the connection object will
	// disappear and the object will be destroyed automatically after this
	// handler returns. The connection class's destructor closes the socket.
}

void CILCASInterface::handleReadContent(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	std::string content;
	content.assign(mBuffer.begin(), mBuffer.begin() + _bytes_transferred);
	mMessageHandler.HandleRequest(content, mReply);

	boost::asio::async_write(mSocket, mReply.ToBuffers(), mStrand.wrap(boost::bind(&CILCASInterface::handleWrite, this, boost::asio::placeholders::error)));
}

void CILCASInterface::handleWrite(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		boost::system::error_code ignored_ec;
		mSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}

	// No new asynchronous operations are started. This means that all shared_ptr
	// references to the connection object will disappear and the object will be
	// destroyed automatically after this handler returns. The connection class's
	// destructor closes the socket.
}

void CILCASInterface::AcceptHandler( const boost::system::error_code& Error )
{
	if( Error )
		return;
	std::cout << "accept handler called" << std::endl;
	boost::asio::write(*mSocket, boost::asio::buffer( "ready" ) );
	mSocket->async_read_some(boost::asio::buffer(mBuffer),
		boost::bind(&CILCASInterface::handleRead, this, _1, _2));
		//boost::bind( &CILCASInterface::ReadHandler, this, _1, _2 ) );
}

extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterNetworkPlugin<CILCASInterface>( "ILCAS" );
}
