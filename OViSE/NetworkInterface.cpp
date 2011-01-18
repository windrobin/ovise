#include "NetworkInterface.h"

CNetworkInterface::CNetworkInterface( boost::asio::io_service& IOService, EntityPool& EntPool ) 
	: mIOService( IOService ), mEntityPool( EntPool )
{
}

CNetworkInterface::~CNetworkInterface()
{
}

