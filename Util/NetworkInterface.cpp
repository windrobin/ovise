#include "NetworkInterface.h"

CNetworkInterface::CNetworkInterface( EntityPool& EntPool, bool NeedsConfigDialog )
	: mEntityPool( EntPool ), 
	mName( "Default" ), 
	mRunning( false ), 
	mNeedsConfigDialog( NeedsConfigDialog )
{}

CNetworkInterface::~CNetworkInterface()
{}
