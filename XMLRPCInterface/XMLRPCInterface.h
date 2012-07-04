#ifndef OVISE_XMLRPC_INTERFACE_H
#define OVISE_XMLRPC_INTERFACE_H

#include "NetworkInterface.h"
#include "XMLRPCMessageHandler.h"

#include "HTTPReply.h"
#include "HTTPRequest.h"
#include "HTTPRequestParser.h"

#include <boost/scoped_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

using namespace boost::asio;

class CXMLRPCInterface : public CNetworkInterface
{
public:
	CXMLRPCInterface( EntityPool& EntPool, const wxString& Name );
	~CXMLRPCInterface( void );

	void AcceptHandler( const boost::system::error_code& );

	bool Start();
	bool Stop();

	void ResetConnection();

	void Poll();

private:
	boost::scoped_ptr<ip::tcp::endpoint> mEndpoint;
	boost::scoped_ptr<ip::tcp::acceptor> mAcceptor;
	boost::scoped_ptr<ip::tcp::socket>   mSocket;

	boost::asio::io_service mIOService;

	boost::array<char, 8192> mBuffer;

	boost::asio::io_service::strand mStrand;

	XMLRPCMessageHandler mMessageHandler;

	HTTPRequest mRequest;
	CHTTPRequestParser mRequestParser;
	HTTPReply mReply;

	void HandleRead( const boost::system::error_code& Error, std::size_t BytesTransferred );
	void HandleReadContent( const boost::system::error_code& Error, std::size_t BytesTransferred );
	void HandleWrite( const boost::system::error_code& Error );
};

#endif // OVISE_XMLRPC_INTERFACE_H
