/* HTTP request parser, adapted from the original Boost HTTP-Server3 example
 * http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.http_server_3
*/

// taken and adapt from sharome XMLRPCInterface

#ifndef XMLRPC_REQUEST_PARSER_H
#define XMLRPC_REQUEST_PARSER_H

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

struct HTTPRequest;

/// Parser for incoming requests.
class CHTTPRequestParser
{
public:
  /// Construct ready to parse the request method.
  CHTTPRequestParser();

  /// Reset to initial parser state.
  void Reset();

  /// Parse some data. The tribool return value is true when a complete request
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> Parse(HTTPRequest& req,
      InputIterator begin, InputIterator end)
  {
    while (begin != end)
    {
      boost::tribool result = Consume(req, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

private:
  /// Handle the next character of input.
  boost::tribool Consume(HTTPRequest& req, char input);

  /// Check if a byte is an HTTP character.
  static bool is_char(int c);

  /// Check if a byte is an HTTP control character.
  static bool is_ctl(int c);

  /// Check if a byte is defined as an HTTP tspecial character.
  static bool is_tspecial(int c);

  /// Check if a byte is a digit.
  static bool is_digit(int c);

  /// The current state of the parser.
  enum State
  {
    method_start,
    method,
    uri_start,
    uri,
    http_version_h,
    http_version_t_1,
    http_version_t_2,
    http_version_p,
    http_version_slash,
    http_version_major_start,
    http_version_major,
    http_version_minor_start,
    http_version_minor,
    expecting_newline_1,
    header_line_start,
    header_lws,
    header_name,
    space_before_header_value,
    header_value,
    expecting_newline_2,
    expecting_newline_3
  } m_State;
};

#endif // XMLRPC_REQUEST_PARSER_H
