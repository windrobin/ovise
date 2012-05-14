#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

void client()
{
	try
	{
		boost::asio::io_service ios;

		boost::asio::ip::tcp::resolver resolver(ios);
		boost::asio::ip::tcp::query query(boost::asio::ip::tcp::v4(), m_host, m_port);
		boost::asio::ip::tcp::resolver::iterator iter = resolver.resolver(query);

		boost::asio::ip::tcp::socket sock(ios);
		sock.connect(*iter);

		std::cout << " Enter message: ";
		std::string request;
		getline(std::cin, request);
		boost::asio::write(sock, boost::asio::buffer(request));

		char data = '\0';
		boost::asio::write(sock, boost::asio::buffer(data, 1));

		while(true)
		{
			boost::array< char, msg_length > reply;

			boost::system::error_code er;
			size_t length = sock.read_some(boost::asio::buffer(reply), er);
			if(er == boost::asio::error::eof)
				break;
			else if(er)
				throw boost::system::system_error(er);
			std::cout.write(reply.c_array(), length);
		}
		std::cout << std::endl;
	}
	catch(std::exception& _e)
	{ std::cerr << "Exception: " << _e.what() << std::endl; }
}
