#ifndef CONNECTION_H
#define CONNECTION_H

// taken and adapt from sharome XMLRPCInterface

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include "HTTPRequest.h"
#include "HTTPRequestParser.h"
#include "HTTPReply.h"
#include "XMLRPCMessageHandler.h"

class Connection : public boost::enable_shared_from_this<Connection>, private boost::noncopyable
{
public:
	Connection(boost::asio::io_service& _io_service, XMLRPCMessageHandler& _handler);
	~Connection();

	boost::asio::ip::tcp::socket& socket();

	void start();

private:
	void handleRead(const boost::system::error_code& _ec, std::size_t _bytes_transfered);
	void handleReadContent(const boost::system::error_code& _ec, std::size_t _bytes_transfered);
	void handleWrite(const boost::system::error_code& _ec);

	boost::asio::io_service::strand m_strand;
	boost::asio::ip::tcp::socket m_socket;

	boost::array<char, 8192> m_buffer;

	HTTPRequest m_request;
	CHTTPRequestParser m_requestParser;
	HTTPReply m_reply;
	XMLRPCMessageHandler m_msgHandler;
};

#endif   // CONNECTION_H
