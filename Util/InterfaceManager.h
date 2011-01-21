#ifndef OVISE_INTERFACE_MANAGER_H
#define OVISE_INTERFACE_MANAGER_H

#include <boost/asio/io_service.hpp>

#include "NetworkInterface.h"

class EntityPool;

class CInterfaceManager
{
public:
	explicit CInterfaceManager( boost::asio::io_service& IOService, EntityPool& EntPool );
	~CInterfaceManager(void);

	template<class InterfaceType> inline
	void RegisterInterface( const std::string& InterfaceName )
	{
		mInterfaces[InterfaceName] = new InterfaceType( mIOService, mEntityPool );
	}

	CNetworkInterface* GetInterface( const std::string& Name );
	std::set<std::string> GetInterfaceNames() const;

private:
	typedef std::map<std::string, CNetworkInterface* > InterfaceMapType;
	InterfaceMapType			mInterfaces;

	boost::asio::io_service&	mIOService;
	EntityPool&					mEntityPool;
};

#endif // OVISE_INTERFACE_MANAGER_H
