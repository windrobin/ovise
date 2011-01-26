#ifndef LEGACY_INTERFACE_H
#define LEGACY_INTERFACE_H

#include <NetworkInterface.h>
#include <Mem/Scene.h>

#include "Message.h"
#include "Connection.h"

class SharomeInterface :
	public CNetworkInterface
{
public:
	SharomeInterface( EntityPool& EntPool );
	~SharomeInterface(void);

	bool Start();
	bool Stop();

	void HandleConnect( const boost::system::error_code& Error,
		boost::asio::ip::tcp::resolver::iterator EndpointIterator );
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

	OOWM::Mem::CScene	mLocalScene;
	ConnectionPtr		mConnection;

	boost::asio::io_service mIOService;
};

#endif // LEGACY_INTERFACE_H
