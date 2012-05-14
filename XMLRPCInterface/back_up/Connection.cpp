#include "Connection.h"

Connection::Connection(boost::asio::io_service& _io_service, XMLRPCMessageHandler& _handler)
:
m_strand(_io_service),
m_socket(_io_service),
m_msgHandler(_handler)
{}

Connection::~Connection()
{}

boost::asio::ip::tcp::socket& Connection::socket()
{ return m_socket; }

void Connection::start()
{
	m_socket.async_read_some(boost::asio::buffer(m_buffer), m_strand.wrap(boost::bind(&Connection::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
}

void Connection::handleRead(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	if(!_ec)
	{
		boost::tribool result;
		boost::tie(result, boost::tuples::ignore) = m_requestParser.Parse(m_request, m_buffer.data(), m_buffer.data() + _bytes_transferred);

		if(result)
		{
			if(m_request.Method == "GET")
			{
				m_msgHandler.HandleHTMLRequest(m_request, m_reply);
				boost::asio::async_write(m_socket, m_reply.ToBuffers(), m_strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error)));
			}
			else if(m_request.Method == "POST")
			{
				int content_length = 0;
				for(std::vector<HTTPHeader>::iterator it = m_request.Headers.begin(); it != m_request.Headers.end(); it++)
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
					boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer), boost::asio::transfer_at_least(content_length), m_strand.wrap(boost::bind(&Connection::handleReadContent, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
				}
			}
		}
		else if(!result)
		{
			m_reply = HTTPReply::StockReply(HTTPReply::bad_request);
			boost::asio::async_write(m_socket, m_reply.ToBuffers(), m_strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error)));
		}
		else
		{
			m_socket.async_read_some(boost::asio::buffer(m_buffer), m_strand.wrap(boost::bind(&Connection::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
		}
	}

	// If an error occurs then no new asynchronous operations are started. This
	// means that all shared_ptr references to the connection object will
	// disappear and the object will be destroyed automatically after this
	// handler returns. The connection class's destructor closes the socket.
}

void Connection::handleReadContent(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	std::string content;
	content.assign(m_buffer.begin(), m_buffer.begin() + _bytes_transferred);
	m_msgHandler.HandleRequest(content, m_reply);

	boost::asio::async_write(m_socket, m_reply.ToBuffers(), m_strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error)));
}

void Connection::handleWrite(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		boost::system::error_code ignored_ec;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}

	// No new asynchronous operations are started. This means that all shared_ptr
	// references to the connection object will disappear and the object will be
	// destroyed automatically after this handler returns. The connection class's
	// destructor closes the socket.
}