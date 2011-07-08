#include "NetworkInterface.h"

CNetworkInterface::CNetworkInterface( EntityPool& EntPool )
	: mEntityPool( EntPool ), 
	mRunning( false )
{}

CNetworkInterface::~CNetworkInterface()
{}
