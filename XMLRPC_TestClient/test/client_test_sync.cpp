#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

int main(int _argc, char** _args)
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
	boost::asio::ip::tcp::socket sock(io_service);

	sock.connect(endpoint);

	boost::array< char, 128 > buf;
	while(1)
	{
		boost::system::error_code error;
		int len = sock.read_some(boost::asio::buffer(buf), error);
		if(error == boost::asio::error::eof)
		{
			std::cout << "\n terminate" << std::endl;
			break;
		}

		std::cout.write(buf.data(), len);
	}

	return 0;
}
