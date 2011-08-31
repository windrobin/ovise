#ifndef OVISE_INTERFACE_MANAGER_H
#define OVISE_INTERFACE_MANAGER_H

#include <boost/asio/io_service.hpp>

#include "NetworkInterface.h"

/**
  Manages the various network interface plugins.
  This class is responsible for loading and unloading of the network
  interface plugins. Also polls all interfaces for updates.
*/
class CInterfaceManager
{
public:
	CInterfaceManager();
	~CInterfaceManager( void );

	void AddInterface( const std::string& Name, CNetworkInterface* Interface );

	CNetworkInterface& GetInterface( const std::string& Name );
	std::set<std::string> GetInterfaceNames() const;

	bool HasInterfaceRunning() const;

	void PollInterfaces() const;

private:
	typedef std::map<std::string, CNetworkInterface* > InterfaceMapType;
	InterfaceMapType mInterfaces;
};

#endif // OVISE_INTERFACE_MANAGER_H
