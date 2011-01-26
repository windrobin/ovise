#include "InterfaceManager.h"


CInterfaceManager::CInterfaceManager( EntityPool& EntPool )
	: mEntityPool( EntPool )
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

void CInterfaceManager::PollInterfaces()
{
	for( InterfaceMapType::iterator i = mInterfaces.begin(); i != mInterfaces.end(); i++ )
		i->second->Poll();
}

bool CInterfaceManager::HasInterfaceRunning()
{
	bool RValue = true;
	for( InterfaceMapType::iterator i = mInterfaces.begin(); i != mInterfaces.end(); i++ )
		RValue = RValue && i->second->IsRunning();

	return RValue;
}
