#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include "XMLRPCMessageAPI.h"

boost::asio::io_service g_io_service;
boost::asio::ip::tcp::resolver g_resolver(g_io_service);
boost::asio::ip::tcp::socket g_socket(g_io_service);
boost::array< char, 4096 > g_buffer;

int g_op = -1;

int g_entity_id = 42;
std::string g_entity_name = "testEntity42";

void read_handler(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	if(!_ec)
	{
		std::cout << std::string(g_buffer.data(), _bytes_transferred) << std::endl;
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);

		/*if(std::string(g_buffer.data()) == "close")
		{
			g_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			g_socket.close();
			std::cout << " > TCP connection closed" << std::endl;
		}*/

		// close connection
		//boost::system::error_code ignored_ec;
		//g_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		/*g_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    	g_socket.close();
	    std::cout << "TCP connection closed." << std::endl;*/
	}
	else
		std::cerr << " > could not read" << std::endl;
}

void connect_handler(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		std::cout << " > prepare message" << std::endl;

		XMLRPCMessageAPI msg_api;

		std::string msg = "";

		switch(g_op)
		{
			case -1:
				return;
			//case 0: msg = msg_api.insertEntityMsg(g_entity_name, g_entity_id);
			case 0: msg = msg_api.insertEntityMsg(g_entity_name);
				break;
			case 1: msg = msg_api.removeEntityMsg(g_entity_id);
				break;
			case 2: msg = msg_api.removeEntityMsg(g_entity_name);
				break;
			case 3:
				break;
		}

		std::cout << " > msg: " << std::endl << msg << std::endl;

		// create http header
		std::stringstream header;
		header << "POST /RPC2 HTTP/1.0" << std::endl;
		header << "User-Agent: " << std::endl;
		header << "Host: " << std::endl;
		header << "Content-Type: text/xml" << std::endl;
		header << "Content-Length: " << msg.length() << std::endl;
		header << std::endl;
		header << msg;
		header << "\r\n\r\n";

		//boost::asio::write(g_socket, boost::asio::buffer(msg));
		boost::asio::write(g_socket, boost::asio::buffer(header.str()));
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);
		boost::asio::write(g_socket, boost::asio::buffer("ready\n"));
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

	std::cout << " > select operation: " << std::endl;
	std::cout << " > 0 - insert entity" << std::endl;
	std::cout << " > 1 - remove entity by id" << std::endl;
	std::cout << " > 2 - remove entity by name" << std::endl;
	std::cout << " > 3 - not specified yet" << std::endl;
	std::cout << " > 4 - cancle and exit program" << std::endl;
	std::cout << std::endl << " > input: ";
	std::cin >> g_op;

	switch(g_op)
	{
		case 0: std::cout << " > insert name: ";
			std::cin >> g_entity_name;
			std::cout << std::endl;
			//std::cout << " > insert id: ";
			//std::cin >> g_entity_id;
			break;
		case 1:	std::cout << " > insert id: ";
			std::cin >> g_entity_id;
			break;
		case 2: std::cout << " > insert name: ";
			std::cin >> g_entity_name;
			break;
	}
	std::cout << std::endl;

	std::cout << " > run io_service" << std::endl;

	g_io_service.run();

	std::cout << " > program ended" << std::endl;

	return 0;
}
