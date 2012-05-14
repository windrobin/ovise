#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

int main(int _argc, char** _args)
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 7171));

	std::cout << " > listen on port : 7171" << std::endl;

	std::string msg("ready");
	while(1)
	{
		boost::asio::ip::tcp::socket sock(io_service);

		acceptor.accept(sock);
		std::cout << " > client blah" << std::endl;

		sock.send(boost::asio::buffer(msg));
	}

	return 0;
}
