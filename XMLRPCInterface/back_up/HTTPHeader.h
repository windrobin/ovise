/* HTTP Header struct, adapted from the original Boost HTTP-Server3 example
 * http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.http_server_3
*/

#ifndef XMLRPC_HTTP_HEADER_H
#define XMLRPC_HTTP_HEADER_H

#include <string>

/**
  Represents a HTTP header name-value-pair.
*/
struct HTTPHeader
{
	/// Name of the header field
	std::string Name;
	/// Value of the header field
	std::string Value;
};

#endif //XMLRPC_HTTP_HEADER_H
