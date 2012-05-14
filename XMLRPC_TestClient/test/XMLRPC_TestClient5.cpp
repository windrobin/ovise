#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

// this code is heavily based on the boost::asio example async_client.hpp
// which can be found here: http://www.boost.org/doc/libs/1_44_0/doc/html/boost_asio/example/http/client/async_client.cpp

class Client
{
public:
	Client(boost::asio::io_service& _io_service, const std::string& _server, const std::string& path)
	:
	m_resolver(_io_service),
	m_socket(_io_service)
	{
		std::ostream req_stream(&m_request);
		req_stream << "GET " << _path << " HTTP/1.0" << "\r\n";
		req_stream << "Host: " << _server << "\r\n";
		req_stream << "Accept: */*" << "\r\n";
		req_stream << "Connection: close" << "\r\n\r\n";

		// start an asynchronous resolve to translate the server and service names
		// into a list of endpoints
		tcp::resolver::query query(_server, "http");
		m_resolver.async_resolve(query, boost::bind(&Client::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator));

	}

private:
	tpc::resolver m_resolver;
	tcp::socket m_socket;
	boost::asio::streambuf m_request;
	boost::asio::streambuf m_response;


	void handle_resolve(const boost::system::error_code& _ec, tcp::resolver::iterator _endpoint_it)
	{
		if(!_ec)
		{
			// attempt a connection to the first endpoint in the list
			// each endpoint will be tried until we successfully establish a connection
			tcp::endpoint endpoint = *_endpoint_it;
			m_socket.async_connection(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_it));
		}
		else
		{
			std::cout << " > Error: " << _ec.message() << std::endl;
		}
	}

	void handle_connect(const boost::system::error_code& _ec, tcp::resolver::iterator _endpoint_it)
	{
		if(!_ec)
		{
			// the connection was successful
			// send the request
			boost::asio::async_write(m_socket, m_request, boost::bind(&Client::handle_write_request, this, boost::asio::placeholders::error));
		}
		else if(_endpoint_it != tcp::resolver::iterator())
		{
			// the connection failed
			// try the next endpoint in the list
			m_socket.close();
			tcp::endpoint endpoint = *_endpoint_it;
			m_socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_it));
		}
		else
			std::cout << " > Error: " << _ec.message() << std::endl;
	}

	void handle_write_request(const boost::system::error_code& _ec)
	{
		if(!_ec)
		{
			// read the response status line
			// the m_response streambuf will automatically grow to accommodate the entire line
			// the growth may be limited by passing a maximum size to the streambuf constructor
			boost::asio::async_read_until(m_socket, m_response, "\r\n", boost::bind(&Client::handle_read_status_line, this, boost::asio::placeholders::error));
		}
		else
			std::cout << " > Error: " << _ec.message() << std::endl;
	}

	void handle_read_status_line(const boost::system::error_code& _ec)
	{
		if(!_ec)
		{
			// check that response is OK
			std::istream res_stream(&m_response);
			std::string http_version;
			res_stream >> htt_version;
			unsigned int status_code;
			res_stream >> status_code;

			std::string status_msg;
			std::getline(res_stream, status_msg);
			if(!res_stream || http_version.substr(0, 5) != "HTTP/")
			{
				std::cout << " > invalid response" << std::endl;
				return;
			}
			if(status_code != 200)
			{
				std::cout << " > response returned with status code" << status_code << std::endl;
				return;
			}

			// read the response headers, which are terminated by a blank line
			boost::asio::async_read_until(m_socket, m_response, "\r\n\r\n", boost::bind(&Client::handle_read_headers, this, boost::asio::placeholders::error));
		}
		else
			std::cout << " > Error: " << _ec.message() << std::endl;
	}

	void handle_read_headers(const boost::system::error_code& _ec)
	{
		if(!_ec)
		{
			// process the response headers
			std::istream res_stream(&m_response);
			std::string header;
			while(std::getline(res_stream, header) && header != "\r")
				std::cout << header << std::endl;
			std::cout << std::endl;

			// write whatever content we already have to output
			if(m_response.size() > 0)
				sdt::cout << &m_response;

			// start reading remaining data until EOF
			boost::asio::async_read(m_socket, m_response, boost::asio::transfer_at_least(1), boost::bind(&Client::handle_read_content, this, boost::asio::placeholders::error));
		}
		else
			std::cout << " > Error: " << _ec.message() << std::endl;
	}

	void handle_read_content(const boost::system::error_code& _ec)
	{
		if(!_ec)
		{
			std::cout << &m_response;

			boost::asio::async_read(m_socket, m_response, boost::asio::transfer_at_least(1), boost::bind(&Client::handle_read_content, this, boost::asio::placeholders::error));
		}
		else if(_ec != boost::asio::error::eof)
			std::cout << " > Error: " << _ec << std::endl;
	}
};

int main(int _argc, char** _argv)
{
	try
	{
		if(_argc != 3)
		{
			std::cout << " > Usage: rpc_test_client5 <server> <path>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;
		Client cnt(io_service, _argv[1], _argv[2]);
		io_service.run();
	}
	catch(std::exception& _e)
		std::cout << " > Exception: " << _e.what() << std::endl;

	return 0;
}
