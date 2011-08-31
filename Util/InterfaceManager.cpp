#include "InterfaceManager.h"


CInterfaceManager::CInterfaceManager( void )
{}


CInterfaceManager::~CInterfaceManager( void )
{
	/*if( !HasInterfaceRunning() )
		return;

	for( InterfaceMapType::iterator i = mInterfaces.begin();
		i != mInterfaces.end(); i++ )
	{
		if( i->second->IsRunning() )
			i->second->Stop();
	}*/
}

void CInterfaceManager::AddInterface( const std::string& Name, CNetworkInterface* Interface )
{
	mInterfaces[Name] = Interface;
}

CNetworkInterface& CInterfaceManager::GetInterface( const std::string& Name )
{
	return *(mInterfaces.at(Name));
}

std::set<std::string> CInterfaceManager::GetInterfaceNames() const
{
	std::set<std::string> RValues;

	for( InterfaceMapType::const_iterator i = mInterfaces.begin();
	     i != mInterfaces.end();
	     i++ )
	{
		RValues.insert( i->first );
	}

	return RValues;
}

void CInterfaceManager::PollInterfaces() const
{
	for( InterfaceMapType::const_iterator i = mInterfaces.begin();
	     i != mInterfaces.end();
	     i++ )
		i->second->Poll();
}

bool CInterfaceManager::HasInterfaceRunning() const
{
	bool RValue = true;
	for( InterfaceMapType::const_iterator i = mInterfaces.begin();
	     i != mInterfaces.end();
	     i++ )
		RValue = RValue && i->second->IsRunning();

	return RValue;
}
