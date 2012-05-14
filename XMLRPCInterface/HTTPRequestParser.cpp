/* HTTP request parser, adapted from the original Boost HTTP-Server3 example
 * http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.http_server_3
*/

#include "HTTPRequestParser.h"
#include "HTTPRequest.h"

CHTTPRequestParser::CHTTPRequestParser()
  : m_State(method_start)
{
}

void CHTTPRequestParser::Reset()
{
	m_State = method_start;
}

boost::tribool CHTTPRequestParser::Consume(HTTPRequest& req, char input)
{
  switch (m_State)
  {
  case method_start:
	if (!is_char(input) || is_ctl(input) || is_tspecial(input))
	{
	  return false;
	}
	else
	{
	  m_State = method;
	  req.Method.push_back(input);
	  return boost::indeterminate;
	}
  case method:
	if (input == ' ')
	{
	  m_State = uri;
	  return boost::indeterminate;
	}
	else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
	{
	  return false;
	}
	else
	{
	  req.Method.push_back(input);
	  return boost::indeterminate;
	}
  case uri_start:
	if (is_ctl(input))
	{
	  return false;
	}
	else
	{
	  m_State = uri;
	  req.URI.push_back(input);
	  return boost::indeterminate;
	}
  case uri:
	if (input == ' ')
	{
	  m_State = http_version_h;
	  return boost::indeterminate;
	}
	else if (is_ctl(input))
	{
	  return false;
	}
	else
	{
	  req.URI.push_back(input);
	  return boost::indeterminate;
	}
  case http_version_h:
	if (input == 'H')
	{
	  m_State = http_version_t_1;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_t_1:
	if (input == 'T')
	{
	  m_State = http_version_t_2;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_t_2:
	if (input == 'T')
	{
	  m_State = http_version_p;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_p:
	if (input == 'P')
	{
	  m_State = http_version_slash;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_slash:
	if (input == '/')
	{
	  req.HTTPVersionMajor = 0;
	  req.HTTPVersionMinor = 0;
	  m_State = http_version_major_start;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_major_start:
	if (is_digit(input))
	{
	  req.HTTPVersionMajor = req.HTTPVersionMajor * 10 + input - '0';
	  m_State = http_version_major;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_major:
	if (input == '.')
	{
	  m_State = http_version_minor_start;
	  return boost::indeterminate;
	}
	else if (is_digit(input))
	{
	  req.HTTPVersionMajor = req.HTTPVersionMajor * 10 + input - '0';
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_minor_start:
	if (is_digit(input))
	{
	  req.HTTPVersionMinor = req.HTTPVersionMinor * 10 + input - '0';
	  m_State = http_version_minor;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case http_version_minor:
	if (input == '\r')
	{
	  m_State = expecting_newline_1;
	  return boost::indeterminate;
	}
	else if (is_digit(input))
	{
	  req.HTTPVersionMinor = req.HTTPVersionMinor * 10 + input - '0';
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case expecting_newline_1:
	if (input == '\n')
	{
	  m_State = header_line_start;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case header_line_start:
	if (input == '\r')
	{
	  m_State = expecting_newline_3;
	  return boost::indeterminate;
	}
	else if (!req.Headers.empty() && (input == ' ' || input == '\t'))
	{
	  m_State = header_lws;
	  return boost::indeterminate;
	}
	else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
	{
	  return false;
	}
	else
	{
	  req.Headers.push_back(HTTPHeader());
	  req.Headers.back().Name.push_back(input);
	  m_State = header_name;
	  return boost::indeterminate;
	}
  case header_lws:
	if (input == '\r')
	{
	  m_State = expecting_newline_2;
	  return boost::indeterminate;
	}
	else if (input == ' ' || input == '\t')
	{
	  return boost::indeterminate;
	}
	else if (is_ctl(input))
	{
	  return false;
	}
	else
	{
	  m_State = header_value;
	  req.Headers.back().Value.push_back(input);
	  return boost::indeterminate;
	}
  case header_name:
	if (input == ':')
	{
	  m_State = space_before_header_value;
	  return boost::indeterminate;
	}
	else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
	{
	  return false;
	}
	else
	{
	  req.Headers.back().Name.push_back(input);
	  return boost::indeterminate;
	}
  case space_before_header_value:
	if (input == ' ')
	{
	  m_State = header_value;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case header_value:
	if (input == '\r')
	{
	  m_State = expecting_newline_2;
	  return boost::indeterminate;
	}
	else if (is_ctl(input))
	{
	  return false;
	}
	else
	{
	  req.Headers.back().Value.push_back(input);
	  return boost::indeterminate;
	}
  case expecting_newline_2:
	if (input == '\n')
	{
	  m_State = header_line_start;
	  return boost::indeterminate;
	}
	else
	{
	  return false;
	}
  case expecting_newline_3:
	return (input == '\n');
  default:
	return false;
  }
}

bool CHTTPRequestParser::is_char(int c)
{
  return c >= 0 && c <= 127;
}

bool CHTTPRequestParser::is_ctl(int c)
{
  return (c >= 0 && c <= 31) || (c == 127);
}

bool CHTTPRequestParser::is_tspecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
	return true;
  default:
	return false;
  }
}

bool CHTTPRequestParser::is_digit(int c)
{
  return c >= '0' && c <= '9';
}