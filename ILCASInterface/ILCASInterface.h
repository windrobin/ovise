#ifndef OVISE_ILCAS_INTERFACE_H
#define OVISE_ILCAS_INTERFACE_H

#include "NetworkInterface.h"
#include "SocketMessage.h"

#include <boost/scoped_ptr.hpp>

using namespace boost::asio;

class CILCASInterface :
	public CNetworkInterface
{
public:
	CILCASInterface( EntityPool& EntPool );
	~CILCASInterface( void );

	void WriteHandler( const boost::system::error_code&, std::size_t );
	void AcceptHandler( const boost::system::error_code& );
	void ReadHandler( const boost::system::error_code&, std::size_t );

	bool Start();
	bool Stop();

	void Poll();

private:
	boost::scoped_ptr<ip::tcp::endpoint> mEndpoint;
	boost::scoped_ptr<ip::tcp::acceptor> mAcceptor;
	boost::scoped_ptr<ip::tcp::socket>   mSocket;

	boost::asio::io_service mIOService;

	boost::array<char, 4096> mBuffer;
	boost::asio::streambuf   mStreamBuffer;

	SocketMessage mMessageHandler;
};

#endif // OVISE_ILCAS_INTERFACE_H
