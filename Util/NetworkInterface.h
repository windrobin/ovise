#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include "../Core/EntityPool.h"
#include "PluginBase.h"

#include <boost/asio.hpp>
#include <wx/propdlg.h>

/** Base class for network interfaces.
	Network plugins shall derive from this. The Poll() method will be called
	from the main applications main loop repeatedly to poll the interface for
	work. The call must return as soon as possible! 
	(see boost::asio::io_service::poll_one())
 */
class CNetworkInterface : public CPluginBase
{
public:
	explicit CNetworkInterface( EntityPool& EntPool, const wxString& Name );
	virtual ~CNetworkInterface();

	/**
	  Should implement intialization and starting of the interface.
	*/
	virtual bool Start() = 0;
	/// Should implement unitialization and stopping of interface
	virtual bool Stop() = 0;

	/// Checks if the interface is running
	bool IsRunning() const { return mRunning; }

	/**
	  Poll the interface for updates.
	  This will be periodically called by the interface manager. This call
	  should process a small batch of network events in the interface and
	  then return (like boost::io_service::poll_once())
	*/
	virtual void Poll() = 0;

protected:
	EntityPool&            mEntityPool;
	bool                   mRunning;
};


#endif
