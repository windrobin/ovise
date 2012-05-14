/* HTTP reply, adapted from the original Boost HTTP-Server3 example
 * http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.http_server_3
*/

#ifndef XMLRPC_HTTP_REPLY_H
#define XMLRPC_HTTP_REPLY_H

#include "HTTPHeader.h"
#include <vector>
#include <boost/asio.hpp>

/// A reply to be sent to a client.
struct HTTPReply
{
  /// The status of the reply.
  enum StatusType
  {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  } Status;

  /// The headers to be included in the reply.
  std::vector<HTTPHeader> Headers;

  /// The content to be sent in the reply.
  std::string Content;

  /// Convert the reply into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the reply object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> ToBuffers();

  /// Get a stock reply.
  static HTTPReply StockReply(StatusType status);
};

#endif // XMLRPC_HTTP_REPLY_H
