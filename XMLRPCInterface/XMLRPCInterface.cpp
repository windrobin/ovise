#include "XMLRPCInterface.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <PluginManager.h>

#include <iostream>


CXMLRPCInterface::CXMLRPCInterface( EntityPool& EntPool, const wxString& Name )
	: CNetworkInterface( EntPool, Name ), mMessageHandler( &EntPool ), mStrand(mIOService)
{}


CXMLRPCInterface::~CXMLRPCInterface()
{
}

bool CXMLRPCInterface::Start()
{
	// currently we don't care about different ports or host adresses
	// since this interface is listening passively
	mEndpoint.reset( new boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), 2121 ) );

	mAcceptor.reset( new boost::asio::ip::tcp::acceptor( mIOService, *mEndpoint ) );
	mSocket.reset( new boost::asio::ip::tcp::socket( mIOService ) );

	mAcceptor->set_option( boost::asio::ip::tcp::acceptor::reuse_address(true) );

	mAcceptor->listen();
	mAcceptor->async_accept( *mSocket, boost::bind( &CXMLRPCInterface::AcceptHandler, this, _1 ) );
	mRunning = true;

	std::cout << "starting interface" << std::endl;
	return true;
}

bool CXMLRPCInterface::Stop()
{
	// FIXME: Is this the way to do it?
	if( mSocket )
		mSocket->close();
	if( mAcceptor )
		mAcceptor->close();
	
	mRunning = false;

	return true;
}

void CXMLRPCInterface::ResetConnection()
{
	Stop();
	
	mRequestParser.Reset();
	mRequest.Method = "";
	mRequest.URI = "";
	mRequest.Headers.clear();

	mReply.Content = "";
	mReply.Headers.clear();

	Start();
}

void CXMLRPCInterface::Poll()
{
	mIOService.poll_one();
	mIOService.reset();
}

void CXMLRPCInterface::HandleRead( const boost::system::error_code& Error, std::size_t BytesTransferred )
{
	if(!Error)
	{
		boost::tribool result;
		boost::tie(result, boost::tuples::ignore) = mRequestParser.Parse(mRequest, mBuffer.data(), mBuffer.data() + BytesTransferred);
		
		if(result)
		{
			if(mRequest.Method == "GET")	// ignore this case
			{}
			else if(mRequest.Method == "POST")
			{
				int content_length = 0;
				for(std::vector< HTTPHeader>::iterator it = mRequest.Headers.begin(); it != mRequest.Headers.end(); it++)
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
					HandleReadContent(Error, BytesTransferred);
				}
			}
		}
		else if(!result)
		{
			mReply = HTTPReply::StockReply(HTTPReply::bad_request);
			mSocket->async_write_some(mReply.ToBuffers(),
				mStrand.wrap(boost::bind(&CXMLRPCInterface::HandleWrite, this, boost::asio::placeholders::error)));
		}
		else
		{
			mSocket->async_read_some(boost::asio::buffer(mBuffer),
				mStrand.wrap(boost::bind(&CXMLRPCInterface::HandleRead, this,
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
		}
	}
}

void CXMLRPCInterface::HandleReadContent( const boost::system::error_code& Error, std::size_t BytesTransferred )
{
	std::string content;
	content.assign(mBuffer.begin(), mBuffer.begin() + BytesTransferred);

	mMessageHandler.HandleMessage(content, mReply);

	mSocket->async_write_some(mReply.ToBuffers(), mStrand.wrap(boost::bind(&CXMLRPCInterface::HandleWrite, this, boost::asio::placeholders::error)));

	ResetConnection();
}

void CXMLRPCInterface::HandleWrite( const boost::system::error_code& Error )
{
	if(!Error)
	{
		// initiate graceful connection closure
		boost::system::error_code ignored_ec;
		mSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}
}

void CXMLRPCInterface::AcceptHandler( const boost::system::error_code& Error )
{
	if( Error )
		return;

	mSocket->async_read_some( boost::asio::buffer(mBuffer),
		boost::bind(&CXMLRPCInterface::HandleRead, this, _1, _2) );
}

extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterNetworkPlugin<CXMLRPCInterface>( "XMLRPC" );
}
