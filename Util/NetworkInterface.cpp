#include "NetworkInterface.h"

CNetworkInterface::CNetworkInterface( EntityPool& EntPool ) 
	: mEntityPool( EntPool ), mName( "Default"), mRunning( false )
{
}

CNetworkInterface::~CNetworkInterface()
{
}

