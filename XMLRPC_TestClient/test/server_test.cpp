#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <string>

int main(int _argc, char** _argv)
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 7171));

	boost::array< char, 4096 > buffer;

	std::cout << " > listen on port: 7171" << std::endl;

	while(1)
	{
		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);
		boost::system::error_code error;
		int len = socket.read_some(boost::asio::buffer(buffer), error);
		if(error == boost::asio::error::eof)
		{
			std::cout << " terminate server" << std::endl;
			break;
		}

		std::cout.write(buffer.data(), len);
	}

	return 0;
}
