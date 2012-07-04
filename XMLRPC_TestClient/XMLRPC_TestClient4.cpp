#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include "XMLRPCMessageAPI.h"

boost::asio::io_service g_io_service;
boost::asio::ip::tcp::resolver g_resolver(g_io_service);
boost::asio::ip::tcp::socket g_socket(g_io_service);
boost::array< char, 4096 > g_buffer;

int g_op = -1;

int g_entity_id = 42;
std::string g_entity_name = "testEntity42";
std::string g_attribute_type = "";
std::string g_attribute_name = "";
std::string g_attribute_value = "";

int g_readyReturned = 0;

void write_handler();	// forward declaration

std::string trimm(const std::string& _str)
{
	std::string res = _str;
    
    size_t pos1 = _str.find_first_not_of(" \r\n");
    size_t pos2 = _str.find_last_not_of(" \r\n");
    if(pos1 == std::string::npos)
        return _str;
    if(pos2 == std::string::npos)
        pos2 = _str.length();

    res = _str.substr(pos1, pos2 - pos1 + 1);

    return res;
}

void read_handler(const boost::system::error_code& _ec, std::size_t _bytes_transferred)
{
	std::cout << " > read_handler call" << std::endl;
	if(!_ec)
	{
		std::cout << " > old buffer entry: " << std::string(g_buffer.data(), _bytes_transferred) << std::endl;
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);

		std::string content;
		content.assign(g_buffer.begin(), g_buffer.begin() + _bytes_transferred);
		std::cout << " > read buffer: " << content << std::endl;
	}
	else
		std::cerr << " > could not read" << std::endl;
}

void write_handler()
{
	std::cout << " > prepare message" << std::endl;

	XMLRPCMessageAPI msg_api;

	std::string msg = "";

	switch(g_op)
	{
		case 0: msg = msg_api.InsertEntityMsg(g_entity_name);
			break;
		case 1: msg = msg_api.RemoveEntityMsg(g_entity_id);
			break;
		case 2: msg = msg_api.RemoveEntityMsg(g_entity_name);
			break;
		case 3: msg = msg_api.RemoveEntitiesByAttributeMsg(g_attribute_name);
			break;
		case 4: msg = msg_api.AddAttributeMsg(g_entity_name, g_attribute_type, g_attribute_name, g_attribute_value);
			break;
		case 5: msg = msg_api.GetAttributeMsg(g_entity_name, g_attribute_name);
			break;
		case 6: msg = msg_api.GetAttributeNamesMsg(g_entity_name);
			break;
		case 7: msg = msg_api.GetAllEntityNamesMsg();
			break;
		case 8: msg = msg_api.RemoveAttributeMsg(g_entity_name, g_attribute_name);
			break;
		case 9: msg = msg_api.ChangeAttributeMsg(g_entity_name, g_attribute_name, g_attribute_type, g_attribute_value);
			break;
	}

	// create http header
	std::stringstream header;
	header << "POST /RPC2 HTTP/1.0" << "\r\n";
	header << "User-Agent: OViSE_Client@localhost" << "\r\n";
	header << "Host: localhost" << "\r\n";
	header << "Content-Type: text/xml" << "\r\n";
	header << "Content-Length: " << msg.length() << "\r\n";
	header << "\r\n";
	header << msg << "\r\n";
	header << "\r\n";

	std::cout << " > msg: " << std::endl << msg << std::endl;

	std::cout << " > write message" << std::endl;
	boost::asio::write(g_socket, boost::asio::buffer(header.str()));
	std::cout << " > message written" << std::endl;
	std::cout << " > read some" << std::endl;

	g_socket.read_some(boost::asio::buffer(g_buffer));
	std::cout << " > read some done: " << std::string(g_buffer.data()) << std::endl;
}

void connect_handler(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		write_handler();
		std::cout << " > read some in connect_handler" << std::endl;
		g_socket.async_read_some(boost::asio::buffer(g_buffer), read_handler);
		std::cout << " > read: " << std::string(g_buffer.data()) << std::endl;
		std::cout << " > read some in connect_handler done" << std::endl;
		g_io_service.stop();
		g_socket.close();
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
	std::cout << " > 3 - remove entities by attribute" << std::endl;
	//std::cout << " > 4 - remove entities by attribute and value" << std::endl;
	std::cout << " > 4 - add attribute" << std::endl;
	std::cout << " > 5 - get attribute" << std::endl;
	std::cout << " > 6 - get all attribute names from entity" << std::endl;
	std::cout << " > 7 - get all entity names from entitypool" << std::endl;
	std::cout << " > 8 - remove attribute from entity" << std::endl;
	std::cout << " > 9 - change attribute of entity" << std::endl;
	std::cout << std::endl;
	std::cout << " > 10 - cancle and exit program" << std::endl;
	std::cout << std::endl << " > input: ";
	std::cin >> g_op;

	switch(g_op)
	{
		case 0: std::cout << " > insert name: ";
				std::cin >> g_entity_name;
				std::cout << std::endl;
				g_entity_name = trimm(g_entity_name);
			break;
		case 1:	std::cout << " > insert id: ";
				std::cin >> g_entity_id;
			break;
		case 2: std::cout << " > insert name: ";
				std::cin >> g_entity_name;
				g_entity_name = trimm(g_entity_name);
			break;
		case 3: std::cout << " > insert attribute name: ";
				std::cin >> g_attribute_name;
				g_attribute_name = trimm(g_attribute_name);
			break;
		case 4:	std::cout << " > insert entity name: ";
				std::cin >> g_entity_name;
				std::cout << std::endl;
				std::cout << " > possible attribute types: 'boolean', 'int', 'double', 'string', 'vector2', 'vector3', 'vector4', 'quaternion'" << std::endl;
				std::cout << std::endl;
				std::cout << " > insert attribute type: ";
				std::cin >> g_attribute_type;
				std::cout << " > insert attribute name: ";
				std::cin >> g_attribute_name;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				std::cout << " > insert attribute value(max length 80 characters): ";
				{
					char buffer[81];
					memset(buffer, 0, 81);
					std::cin.getline(buffer, 81, '\n');
					g_attribute_value = buffer;
				}

				g_entity_name = trimm(g_entity_name);
				g_attribute_type = trimm(g_attribute_type);
				g_attribute_name = trimm(g_attribute_name);
				g_attribute_value = trimm(g_attribute_value);

				// check type and value
				if(g_attribute_type == "boolean")
				{
					if(g_attribute_value != "true" && g_attribute_value != "True" && g_attribute_value != "TRUE"
					&& g_attribute_value != "false" && g_attribute_value != "False" && g_attribute_value != "FALSE")
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else if(g_attribute_type == "int")
				{
					if( !(boost::lexical_cast< int >(g_attribute_value) < INT_MAX && boost::lexical_cast< int >(g_attribute_value) > INT_MIN) )
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else if(g_attribute_type == "double")
				{
					if( !(boost::lexical_cast< float >(g_attribute_value) < HUGE_VAL && boost::lexical_cast< float >(g_attribute_value) > -HUGE_VAL) )
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else if(g_attribute_type == "string") {}
				else if(g_attribute_type == "vector2")
				{
					std::cout << " > attribute_value: " << g_attribute_value << std::endl;

					std::string val1 = "";
					std::string val2 = "";

					unsigned int ws = 0;
					for(unsigned int i = 0; i < g_attribute_value.length(); i++)
					{
						if(g_attribute_value[i] == ' ')
							ws++;

						if(ws == 0)
							val1 += g_attribute_value[i];
						else
							val2 += g_attribute_value[i];
					}

					if(ws != 1)
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else if(g_attribute_type == "vector3")
				{
					std::cout << " > attribute_value: " << g_attribute_value << std::endl;

					unsigned int ws = 0;
					for(unsigned int i = 0; i < g_attribute_value.length(); i++)
						if(g_attribute_value[i] == ' ')
							ws++;

					if(ws != 2)
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else if(g_attribute_type == "vector4" || g_attribute_type == "quaternion")
				{
					std::cout << " > attribute_value: " << g_attribute_value << std::endl;

					unsigned int ws = 0;
					for(unsigned int i = 0; i < g_attribute_value.length(); i++)
						if(g_attribute_value[i] == ' ')
							ws++;

					if(ws != 3)
					{
						std::cout << " > the value is not appropriate to the given datatype" << std::endl;
						return 0;
					}
				}
				else
				{
					std::cout << " > datatype is not implemented yet" << std::endl;
					return 0;
				}
			break;
		case 5: std::cout << " > insert entity name: ";
				std::cin >> g_entity_name;
				std::cout << " > insert attribute name: ";
				std::cin >> g_attribute_name;

				g_entity_name = trimm(g_entity_name);
				g_attribute_name = trimm(g_attribute_name);
			break;
		case 6: std::cout << " > insert entity name: ";
				std::cin >> g_entity_name;
				g_entity_name = trimm(g_entity_name);
			break;
		case 7:	// dummy need to be here, otherwise it will return 0
			break;
		case 8: std::cout << " > insert entity name: ";
				std::cin >> g_entity_name;
				std::cout << std::endl;
				std::cout << " > insert attribute name: ";
				std::cin >> g_attribute_name;
				std::cout << std::endl;

				g_entity_name = trimm(g_entity_name);
				g_attribute_name = trimm(g_attribute_name);
			break;
		case 9: std::cout << " > insert entity name: ";
				std::cin >> g_entity_name;
				std::cout << " > insert attribute name: ";
				std::cout << std::endl;
				std::cout << " > possible attribute types: 'boolean', 'int', 'double', 'string', 'vector2', 'vector3', 'quaternion'" << std::endl;
				std::cout << " > insert attribute type: ";
				std::cin >> g_attribute_type;
				std::cout << " > insert attribute name: ";
				std::cin >> g_attribute_name;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				std::cout << " > insert attribute value(max length 80 characters): ";
				{
					char buffer[81];
					memset(buffer, 0, 81);
					std::cin.getline(buffer, 81, '\n');
					g_attribute_value = buffer;
				}

				g_entity_name = trimm(g_entity_name);
				g_attribute_type = trimm(g_attribute_type);
				g_attribute_name = trimm(g_attribute_name);
				g_attribute_value = trimm(g_attribute_value);
			break;
		default: std::cout << " > exit program" << std::endl;
			return 0;
	}
	std::cout << std::endl;

	std::cout << " > run io_service" << std::endl;

	g_io_service.run();

	std::cout << " > program ended" << std::endl;

	return 0;
}
