#ifndef OVISE_VOODOO_INTERFACE_H
#define OVISE_VOODOO_INTERFACE_H

#include "NetworkInterface.h"
#include "Connection.hpp"

class CVoodooInterface :
	public CNetworkInterface
{
public:
	CVoodooInterface( EntityPool& EntPool );
	~CVoodooInterface(void);

	bool Start();
	bool Stop();

	void Poll();

private:
	void HandleMessage( const std::string& Msg );

	boost::asio::io_service			mIOService;
	CVoodooConnection::CtnPointer   mConnection;

	Entity* mVoodooDude;
};

#endif // OVISE_VOODOO_INTERFACE_H
