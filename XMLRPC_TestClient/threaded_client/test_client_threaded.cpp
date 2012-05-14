#include <cstdlib>
#include <iostream>
#include <deque>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "client.h"

using boost::asio::ip::tcp;

typedef std::deque< Message > MessageQueue;

int main(int _argc, char** _argv)
{
	try
	{
	}
	catch()
	{
		std::cerr << " > Exception: " << _e.what() << std::endl;
	}

	return 0;
}
