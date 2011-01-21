#ifndef OVISE_ILCAS_INTERFACE_H
#define OVISE_ILCAS_INTERFACE_H

#include "NetworkInterface.h"
#include "SocketMessage.h"

class CILCASInterface :
	public CNetworkInterface
{
public:
	CILCASInterface( boost::asio::io_service& IOService, EntityPool& EntPool );
	~CILCASInterface(void);

	void WriteHandler( const boost::system::error_code& , std::size_t );
	void AcceptHandler( const boost::system::error_code& );
	void ReadHandler( const boost::system::error_code&, std::size_t );

	bool Init();

private:
	boost::asio::ip::tcp::endpoint	mEndpoint;
	boost::asio::ip::tcp::acceptor	mAcceptor;
	boost::asio::ip::tcp::socket	mSocket;

	boost::array<char, 4096>		mBuffer;
	boost::asio::streambuf			mStreamBuffer;

	SocketMessage					mMessageHandler;
};

#endif // OVISE_ILCAS_INTERFACE_H
