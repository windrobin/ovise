# Introduction #

This page describes the usage of the XMLRPC-Interface, which allows access to entities.


# Details #

To use the XMLRPC-Interface you have to activate the plug-in first: menu -> 'Network' -> 'XMLRPC'

## Supported methods: ##

  * _GetAllEntityNames_(void)

  * _InsertEntity_(const std::string& Name, int Id=-1)

  * _RemoveEntity_(const std::string& Name)

  * _RemoveEntity_(int Id)

  * _RemoveEntitiesByAttribute_(const std::string& AttributeName)

  * _AddAttribute_(const std::string& EntityName, const std::string& AttributeName, const T& AttributeValue), where T can be of 'bool', 'int', 'double' or 'std::string'

> _AddAttribute_(const std::string& EntityName, const std::string& AttributeName, Ogre::Vector2)

> _AddAttribute_(const std::string& EntityName, const std::string& AttributeName, Ogre::Vector3)

> _AddAttribute_(const std::string& EntityName, const std::string& AttributeName, Ogre::Quaternion)

  * _GetAttribute_(const std::string& EntityName, const std::string& AttributeName)

  * _GetAttributeNames_(const std::string& EntityName)

  * _RemoveAttribute_(const std::string& EntityName, const std::string& AttributeName)

  * _ChangeAttribute_(const std::string& EntityName, const std::string& AttributeName, const T& AttributeValue), where T can be of 'bool', 'int', 'double' or 'std::string'

> _ChangeAttribute_(const std::string& EntityName, const std::string& AttributeName, const Ogre::Vector2)

> _ChangeAttribute_(const std::string& EntityName, const std::string& AttributeName, const Ogre::Vector3)

> _ChangeAttribute_(const std::string& EntityName, const std::string& AttributeName, const Ogre::Quaternion)


## Python ##
A client written in Python for inserting a new entity with name "Entity\_Test" and position (1.0, 1.0, 3.0) could look like this:

```py

```
#!/usr/bin/env python

import xmlrpclib

cli = xmlrpclib.ServerProxy('http://localhost:2121')

print cli.InsertEntity("Entity_Test")
```
```


if you want to send more method calls at once, then you have to wait a short moment between the calls:

```py2

```
#!/usr/bin/env python

import xmlrpclib
import time

cli = xmlrpclib.ServerProxy('http://localhost:2121')

print cli.InsertEntity("Entity_Test")

time.sleep(0.1)

v = [1.0, 1.0, 3.0]
print cli.AddAttribute("Entity_Test", "Position", v)
```
```

## C++ ##
For writting a C++ client application you need the XMLRPCMessageAPI header file, which can be found in XMLRPCInterface subdirectory of OViSE.
You will find two classes in this header file. One is the WrongDataTypeException which is used by the other class XMLRPCMessageAPI. This exception inherits from std::exception and is thrown whenever a wrong datatype is used in a methodcall.

Valid datatypes are: int, double, bool, std::string, Ogre::Vector2, Ogre::Vector3 and Ogre::Quaternion

The XMLRPCMessageAPI class provides only messages for xmlrpc-message-handling ready for transmitting via HTTP. The HTTP procedure handling has to be done be the client itself.

You can find two example clients in XMLRPC\_TestClient subdirectory of OViSE. One of them is written as a class and both of them uses boost::asio to communicate via HTTP.

### Usage of XMLRPCMessageAPI class ###
```C++

```
...
#include <sstream>
#include <string>
#include "XMLRPCMessageAPI.h"
...
// create a XMLRPCMessageAPI object
XMLRPCMessageAPI msgAPI;
// get XMLRPC-Message for inserting a new entiy
std::string msg = msgAPI.InsertEntityMsg("NewTestEntity");

// create HTTP message
std::stringstream httpMsg;
httpMsg << "POST /RPC2 HTTP/1.0\r\n";
httpMsg << "User-Agent: OViSE_Client@localhost\r\n";
httpMsg << "Host: localhost\r\n";
httpMsg << "Content-Type: text/xml\r\n";
httpMsg << "Content-Length: " << msg.length() << "\r\n";
httpMsg << "\r\n";
httpMsg << msg << "\r\n";
httpMsg << "\r\n";

// the httpMsg is now ready for transmitting
...
```
```

This is one of the full example clients written in C++ using boost::asio for network connection:
```C++

```
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <boost/bind.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include "XMLRPCMessageAPI.h"

class OViSEXMLRPCClient
{
public:
	OViSEXMLRPCClient();
	~OViSEXMLRPCClient();

	void Connect();

private:
	boost::asio::io_service mIOService;
	boost::asio::ip::tcp::resolver mResolver;
	boost::asio::ip::tcp::socket mSocket;

	boost::array< char, 4096 > mBuffer;

	void ResolveHandler( const boost::system::error_code& _ec, boost::asio::ip::tcp::resolver::iterator _it );
	void ConnectHandler( const boost::system::error_code& _ec );
	void WriteHandler();
};

OViSEXMLRPCClient::OViSEXMLRPCClient()
:
mResolver(mIOService),
mSocket(mIOService)
{}

OViSEXMLRPCClient::~OViSEXMLRPCClient()
{}

void OViSEXMLRPCClient::Connect()
{
	boost::asio::ip::tcp::resolver::query query("127.0.0.1", "2121");

	mResolver.async_resolve(query, boost::bind(&OViSEXMLRPCClient::ResolveHandler, this,
                  boost::asio::placeholders::error, boost::asio::placeholders::iterator));

	// start ioService
	mIOService.run();
}

void OViSEXMLRPCClient::ResolveHandler(const boost::system::error_code& _ec,
                                       boost::asio::ip::tcp::resolver::iterator _it)
{
	if(!_ec)
	{
		mSocket.async_connect(*_it, boost::bind(&OViSEXMLRPCClient::ConnectHandler, this,
                        boost::asio::placeholders::error));
	}
	else
		std::cerr << " > could not resolve" << std::endl;
}

void OViSEXMLRPCClient::ConnectHandler(const boost::system::error_code& _ec)
{
	if(!_ec)
	{
		WriteHandler();
		mIOService.stop();
		mSocket.close();
	}
	else
		std::cerr << " > could not connect to server" << std::endl;
}

void OViSEXMLRPCClient::WriteHandler()
{
	// get RPC-Message for inserting a new entity
	XMLRPCMessageAPI msgAPI;
	std::string msg = msgAPI.InsertEntityMsg("NewTestEntity");

	// create http message
	std::stringstream httpMsg;
	httpMsg << "POST /RPC2 HTTP/1.0\r\n";
	httpMsg << "User-Agent: OViSE_Client@localhost\r\n";
	httpMsg << "Host: localhost\r\n";
	httpMsg << "Content-Type: text/xml\r\n";
	httpMsg << "Content-Length: " << msg.length() << "\r\n";
	httpMsg << "\r\n";
	httpMsg << msg << "\r\n";
	httpMsg << "\r\n";

	// write message
	boost::asio::write(mSocket, boost::asio::buffer(httpMsg.str()));

	mSocket.read_some(boost::asio::buffer(mBuffer));
	std::cout << " > read: " << std::string(mBuffer.data()) << std::endl;
}

int main(int _argc, char** _argv)
{
	OViSEXMLRPCClient client;
	client.Connect();
}
```
```