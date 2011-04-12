#ifndef LEGACY_INTERFACE_H
#define LEGACY_INTERFACE_H

#include <NetworkInterface.h>
#include <Mem/Scene.h>

#include "Message.h"
#include "Connection.h"

/**
  Interface for Shared Robot Memory.
  Implements the network interface to communicate with the Shared Robot
  Memory system. Receives scene updates and tries to represent them within
  the visualization.
  @remark Changes to the entities within OViSE will currently not be communicated
  back to ShaRoMe!
  @remark Only CValues will be represented as Entity attributes, CAttribute layer
  is not supported.
*/
class SharomeInterface :
	public CNetworkInterface
{
public:
	SharomeInterface( EntityPool& EntPool );
	~SharomeInterface( void );

	bool Start();
	bool Stop();

	void HandleConnect(
	        const boost::system::error_code& Error,
	        boost::asio::ip::tcp::resolver::iterator
	        EndpointIterator );
	void HandleRead( const boost::system::error_code& Error,
	                 boost::shared_ptr<Comm::Message> Msg );
	void HandleWrite( const boost::system::error_code& Error );

	void Poll();

private:
	void HandleObjectCreated( const OOWM::Mem::CObj& Obj );
	void HandleObjectChanged( const OOWM::Mem::CObj& Obj );
	void HandleObjectDeleted( const OOWM::Mem::CObj& Obj );
	void HandleSceneChanged();
	void HandleSceneDeleted();
	void HandleError( std::string Msg );

	OOWM::Mem::CScene mLocalScene;
	ConnectionPtr     mConnection;

	boost::asio::io_service mIOService;
};

#endif // LEGACY_INTERFACE_H
