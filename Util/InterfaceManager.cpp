#include "InterfaceManager.h"


CInterfaceManager::CInterfaceManager( boost::asio::io_service& IOService, EntityPool& EntPool )
	: mIOService( IOService ), mEntityPool( EntPool )
{
}


CInterfaceManager::~CInterfaceManager(void)
{
}

CNetworkInterface* CInterfaceManager::GetInterface( const std::string& Name )
{
	return mInterfaces[Name];
}

std::set<std::string> CInterfaceManager::GetInterfaceNames() const
{
	std::set<std::string> RValues;
	
	for( InterfaceMapType::const_iterator i = mInterfaces.begin(); i != mInterfaces.end(); i++ )
	{
		RValues.insert( i->first );
	}

	return RValues;
}

bool CInterfaceManager::HasInterfaceRunning()
{
	bool RValue = true;
	for( InterfaceMapType::iterator i = mInterfaces.begin(); i != mInterfaces.end(); i++ )
		RValue = RValue && i->second->IsRunning();

	return RValue;
}
