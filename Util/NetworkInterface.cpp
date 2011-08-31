#include "NetworkInterface.h"

CNetworkInterface::CNetworkInterface( EntityPool& EntPool, const wxString& Name )
	: CPluginBase( Name, CPluginBase::PLUGIN_TYPE_NETWORK ), 
	mEntityPool( EntPool ), mRunning( false )
{}

CNetworkInterface::~CNetworkInterface()
{}
