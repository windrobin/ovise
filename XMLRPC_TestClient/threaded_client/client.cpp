#include "Client.h"

Client::Client(boost::asio::io_service& _io_service, boost::asio::ip::tcp::resolver::iterator _endpoint_it)
:
m_io_service(_io_service),
m_socket(io_service)
{
	boost::asio::ip::tcp::endpoint endpnt = *_endpoint_it;
	m_socket.async_connect(endpnt, boost::bind(&Client::handle_connection, this, boost::asio::placeholders::error, ++endpoint_it));
}

void Client::write(const Message& _msg)
{
	m_io_service.post(boost::bind(&Client::handle::do_write, this, _msg));
}

void Client::close()
{
	m_io_service.post(boost::bind(&Client::do_close, this));
}

void Client::handle_connect(const boost::syste::error_code& _error, boost::asio::ip::tcp::resolver::iterator _endpoint_it)
{
	if(!_error)
	{
		boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.data(), Message::header_length),
			boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
	}
	else if(endpoint_it != boost::asio::ip::tcp::resolver::iterator())
	{
		m_socket.close();
		boost::asio::ip::tcp::endpoint endpnt = *endpoint_it;
		m_socket.async_connect(endpnt, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_it));
	}
}

void Client::handle_read_header(const boost::system::error_code& _error)
{
	if(!_error && m_read_msg.decode_header())
	{
		boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.body(), m_read_msg.body_length()),
			boost::bind(&Client::handle_read_body, this, boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void Client::handle_read_body(const boost::system::error_code& _error)
{
	if(!_error)
	{
		std::cout.write(m_read_msg.body(), m_read_msg.body_length());
		std::cout << std::endl;
		boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.data(), Message::header_length),
			boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void Client::do_write(Message _msg)
{
	bool write_in_progress = !m_write_msgs.empty();
	m_write_msgs.push_back(_msg);
	if(!write_in_progress)
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front().data(), m_write_msgs.front().length()),
			boost::bind(&Client::handle_write, this, boost::asio::placeholders::error));
	}
}

void Client::handle_write(const boost::system::error_code& _error)
{
	if(!_error)
	{
		m_write_msgs.pop_front();
		if(!m_write_msgs.empty())
		{
			boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front().data(),
				m_write_msgs.front().length()), boost::bind(&Client::handle_write, this,
				boost::asio::placeholders::error));
		}
	}
	else
	{
		do_close();
	}
}

void Client::do_close()
{
	m_socket.close();
}
