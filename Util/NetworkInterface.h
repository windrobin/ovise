#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H


#include "../Core/EntityPool.h"
#include <boost/asio.hpp>

#ifdef WIN32
#define INTERFACE_API __declspec( dllexport )
#else
#define INTERFACE_API
#endif

/** Base class for network interfaces.
        Network plugins shall derive from this. The given io_service object will be polled
        from the main loop enabling interfaces to manipulate the entity pool in a
        synchronized fashion.
 */
class CNetworkInterface
{
public:
	CNetworkInterface( EntityPool& EntPool );
	virtual ~CNetworkInterface();

	/// Should implement intialization and starting of the interface
	virtual bool Start( const std::string& Host, const std::string& Service ) = 0;
	/// Should implement unitialization and stopping of interface
	virtual bool Stop() = 0;

	bool IsRunning() {
		return mRunning;
	}

	/**
	  Poll the interface for updates.
	  This will be periodically called by the interface manager. This call
	  should process a small batch of network events in the interface and
	  then return (like boost::io_service::poll_once())
	*/
	virtual void Poll() = 0;

protected:
	EntityPool& mEntityPool;
	std::string mName;
	bool        mRunning;
};


#endif
