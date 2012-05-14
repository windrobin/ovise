#include <cstdlib>
#include <iostream>
#include <deque>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

typedef std::deque< Message > MessageQueue;

class Client
{
public:
	Client(boost::asio::io_service& _io_service, boost::asio::ip::tcp::resolver::iterator endpoint_it);

	void write(const Message& _msg);
	void close();

private:
	boost::asio::io_service& m_io_service;
	boost::asio::ip::tcp::socket m_socket;
	Message m_read_msg;
	MessageQueue m_write_msgs;

	void handle_connect(const boost::system::error_code& _error);
	void handle_read_header(const boost::system::error_code& _error);
	void handle_read_body(const boost::system::error_code& _error);
	void do_write(Message _msg);
	void handle_write(const boost::system::error_code& _error);
	void do_close();
};
