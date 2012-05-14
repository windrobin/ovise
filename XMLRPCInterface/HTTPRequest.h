/* HTTP request struct, adapted from the original Boost HTTP-Server3 example
 * http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.http_server_3
*/

// taken and adapt from sharome XMLRPCInterface
 
#ifndef XMLRPC_HTTP_REQUEST_H
#define XMLRPC_HTTP_REQUEST_H

#include "HTTPHeader.h"

#include <vector>

/**
  A HTTP request consisting of HTTP version, request method, the URI
  and a list of headers.
*/
struct HTTPRequest
{
	/// HTTP request method (e.g. GET)
	std::string Method;
	/// URI that is requested (e.g. index.html)
	std::string URI;
	/// HTTP version major number
	int HTTPVersionMajor;
	/// HTTP version minor number
	int HTTPVersionMinor;
	/// List of header elements, name-value-pairs
	std::vector<HTTPHeader> Headers;
};

#endif // XMLRPC_HTTP_REQUEST_H
