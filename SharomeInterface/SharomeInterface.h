#ifndef LEGACY_INTERFACE_H
#define LEGACY_INTERFACE_H

#include <NetworkInterface.h>
#include <Mem/Scene.h>
#include <LegacyClientLib/AsyncClient.hpp>

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

	virtual void CreateConfigDialog( wxWindow* Parent );

	void Poll();

	void HandleObjectCreated( const OOWM::Mem::CObj& Obj );
	void HandleObjectChanged( const OOWM::Mem::CObj& Obj, const OOWM::Mem::CObj& OldObj );
	void HandleObjectDeleted( const OOWM::Mem::CObj& Obj );
	void HandleSceneChanged( const OOWM::Mem::CScene& Scene );
	void HandleSceneDeleted();
	void HandleError( std::string Msg );

private:
	boost::scoped_ptr<CAsyncClient> LegacyClient;

	struct SSettings
	{
		std::string Host;
		std::string Port;
	};

	SSettings mSettings;
};

#endif // LEGACY_INTERFACE_H
