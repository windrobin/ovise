#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <sstream>
#include <string>

boost::asio::io_service g_io_service;
boost::asio::ip::tcp::resolver g_resolver(g_io_service);
boost::asio::ip::tcp::socket g_socket(g_io_service);
boost::array< char, 4096 > g_buffer;

void read_handler(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	if(!_ec)
	{
		std::cout << std::string(g_buffer.data(), _bytes_transferred) << std::endl;
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);

		//boost::asio::write(g_socket, boost::asio::buffer("ready"));
		if(std::string(g_buffer.data()) == "ready")
		{
			std::cout << " > disconnect client" << std::endl;
			boost::system::error_code error;
			g_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
			g_socket.close();
		}
	}
	else
		std::cerr << " > could not read" << std::endl;
}

void connect_handler(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		std::cout << " > prepare message" << std::endl;
		std::stringstream msg;
		msg << "<?xml version=\"1.0\"?>" << std::endl;
		msg << "<methodCall>" << std::endl;
		msg << " <methodName> testFunc </methodName>" << std::endl;
		msg << "  <params>" << std::endl;
		msg << "   <param>" << std::endl;
		msg << "    <value> <i4> 42 </i4> </value>" << std::endl;
		msg << "   </param>" << std::endl;
		msg << "   <param>" << std::endl;
		msg << "    <value> <double> 3.14 </double> </value>" << std::endl;
		msg << "   </param>" << std::endl;
		msg << "  </params>" << std::endl;
		msg << "</methodCall>" << std::endl;

		std::cout << " > msg: " << std::endl << msg.str() << std::endl;

		boost::asio::write(g_socket, boost::asio::buffer(msg.str()));
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);
	}
	else
		std::cerr << " > could not connect to server" << std::endl;
}

void resolve_handler(const boost::system::error_code& _ec, boost::asio::ip::tcp::resolver::iterator _it)
{
	if(!_ec)
	{
		std::cout << " > connect to server" << std::endl;
		g_socket.async_connect(*_it, connect_handler);
		std::cout << " > connected to server" << std::endl;
	}
	else
		std::cerr << " > could not resolve" << std::endl;
}

int main(int _argc, char** _argv)
{
	if(_argc != 3)
	{
		std::cerr << "> usage: client <host> <port>" << std::endl;
		return 1;
	}

	std::cout << " > program started" << std::endl;

	boost::asio::ip::tcp::resolver::query query(_argv[1], _argv[2]);

	std::cout << " > resolve query" << std::endl;
	g_resolver.async_resolve(query, resolve_handler);

	std::cout << " > run io_service" << std::endl;

	g_io_service.run();

	std::cout << " > program ended" << std::endl;

	return 0;
}
