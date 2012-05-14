#ifndef OVISE_ILCAS_INTERFACE_H
#define OVISE_ILCAS_INTERFACE_Hs

#include "NetworkInterface.h"
//#include "SocketMessage.h"
#include "XMLRPCMessageHandler.h"

#include "HTTPRequest.h"
#include "HTTPRequestParser.h"
#include "HTTPReply.h"

#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

class CILCASInterface :	public CNetworkInterface
{
public:
	CILCASInterface( EntityPool& EntPool, const wxString& Name );
	~CILCASInterface( void );

	//void WriteHandler( const boost::system::error_code&, std::size_t );
	void AcceptHandler( const boost::system::error_code& );
	//void ReadHandler( const boost::system::error_code&, std::size_t );

	bool Start();
	bool Stop();

	void Poll();

private:
	boost::scoped_ptr<boost::asio::ip::tcp::endpoint> mEndpoint;
	boost::scoped_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
	boost::scoped_ptr<boost::asio::ip::tcp::socket>   mSocket;

	boost::asio::io_service::strand mStrand;
	boost::asio::io_service mIOService;

	//boost::array<char, 4096> mBuffer;
	boost::array<char, 8192> mBuffer;
	//boost::asio::streambuf   mStreamBuffer;

	//SocketMessage mMessageHandler;
	XMLRPCMessageHandler mMessageHandler;

	HTTPRequest mRequest;
	CHTTPRequestParser mRequestParser;
	HTTPReply mReply;

//	boost::shared_ptr<Connection> m_pConnection;


	void handleRead(const boost::system::error_code& _ec, std::size_t _bytes_transfered);
	void handleReadContent(const boost::system::error_code& _ec, std::size_t _bytes_transfered);
	void handleWrite(const boost::system::error_code& _ec);
};

#endif // OVISE_ILCAS_INTERFACE_H
