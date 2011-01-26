#include "SharomeInterface.h"

#include <InterfaceManager.h>
#include <Mem/Serialization.hpp>
#include <Mem/Location.h>
#include <Result.h>

namespace {

void CreateEntityFromCObj( EntityPool& Pool, const OOWM::Mem::CObj& Obj )
{
	Entity& E = Pool.CreateEntity( Obj.getName() );
	E.Set
		( "Type", "Simple" )
		( "Model", "Unknown.mesh" )
		( "SharomeId", Obj.getId() )
	;

	OOWM::Mem::CAttribute A;
	OOWM::SResult Result;
	Obj.getFirstByName( A, "Location", &Result );
	if( Result.m_nCode == R_OK )
	{
		OOWM::Mem::CLocation L;
		if( L.FromAttribute( A ) )
		{
			E.SetAttribute( "Position", vec3( L.m_Position.m_Value[0], L.m_Position.m_Value[1], L.m_Position.m_Value[2] ) );
		}
	}
}

}


SharomeInterface::SharomeInterface( EntityPool& EntPool ) 
	: CNetworkInterface( EntPool )
{
}


SharomeInterface::~SharomeInterface(void)
{
}

bool SharomeInterface::Start()
{
	std::cout << "SharomeInterface init." << std::endl;

	// FIXME: to be set by dialog
	std::string Host = "i61pst1";
	std::string Service = "12345";

	boost::asio::ip::tcp::resolver Resolver( mIOService);
	boost::asio::ip::tcp::resolver::query Query( Host, Service );
	boost::asio::ip::tcp::resolver::iterator EndpointIterator = Resolver.resolve( Query );
	boost::asio::ip::tcp::endpoint Endpoint = *EndpointIterator;

	mConnection.reset( new CConnection( mIOService ) );

	mConnection->Socket().async_connect( Endpoint,
		boost::bind( &SharomeInterface::HandleConnect, this,
		boost::asio::placeholders::error, ++EndpointIterator ) );

	mRunning = true;

	return true;
}

bool SharomeInterface::Stop()
{
	std::cout << "SharomeInterface uninit." << std::endl;
	mConnection->Socket().close();

	mRunning = false;

	return true;
}

void SharomeInterface::Poll()
{
	mIOService.poll();
	mIOService.reset();
}

void SharomeInterface::HandleConnect( const boost::system::error_code& Error,
	boost::asio::ip::tcp::resolver::iterator EndpointIterator )
{
	if(!Error)
	{
		boost::asio::socket_base::keep_alive option(true);
		mConnection->Socket().set_option( option );

		// tell server we want the whole scene
		boost::shared_ptr<Comm::Message> msg( new Comm::Message );
		msg->m_Code = Comm::MSG_GET;
		msg->m_Type = Comm::TYPE_CSCENE;

		mConnection->AsyncWrite(msg,
			boost::bind(&SharomeInterface::HandleWrite, this,
			boost::asio::placeholders::error ) );
	}
	else if( EndpointIterator != boost::asio::ip::tcp::resolver::iterator())
	{
		mConnection->Socket().close();
		boost::asio::ip::tcp::endpoint Endpoint = *EndpointIterator;
		mConnection->Socket().async_connect(Endpoint,
			boost::bind(&SharomeInterface::HandleConnect, this,
			boost::asio::placeholders::error, ++EndpointIterator) );
	}
	else
	{
		std::cerr << Error.message() << std::endl;
	}
}

void SharomeInterface::HandleWrite( const boost::system::error_code& Error )
{
	if(!Error)
	{
		boost::shared_ptr<Comm::Message> Reply;
		Reply.reset( new Comm::Message );
		mConnection->AsyncRead(Reply,
			boost::bind(&SharomeInterface::HandleRead, this,
			boost::asio::placeholders::error, Reply ) );
	}
	else
	{
		std::cerr << Error.message() << std::endl;
	}
}

void SharomeInterface::HandleRead( const boost::system::error_code& Error,
	boost::shared_ptr<Comm::Message> Msg )
{
	if(Error)
	{
		std::cerr << Error.message() << std::endl;
		return;
	}
	
	switch( Msg->m_Code )
	{
	case Comm::MSG_OK:
		{
			std::cout << "Comm OK" << std::endl;
		} break;
	case Comm::MSG_UPDATE:
		{
			if( Msg->m_Type == Comm::TYPE_COBJ )
			{
				OOWM::Mem::CObj Incoming;
				DeserializeObj( Msg->GetData(), Incoming );
				OOWM::SResult Result;
				OOWM::Mem::CObj Helper;
				mLocalScene.getById( Helper, Incoming.getId(), &Result );
				mLocalScene.put( Incoming );
				if( Result.m_nCode != R_OK )
					HandleObjectCreated( Incoming );
				else
					HandleObjectChanged( Incoming );
			}
			if( Msg->m_Type == Comm::TYPE_CSCENE )
			{
				DeserializeScene( Msg->GetData(), mLocalScene );
				HandleSceneChanged();
			}
		} break;
	case Comm::MSG_DEL:
		{
			if( Msg->m_Type == Comm::TYPE_COBJ )
			{
				OOWM::Mem::CObj T;
				mLocalScene.getById( T, Msg->GetData(), 0 );
				mLocalScene.removeById( Msg->GetData(), 0 );
				HandleObjectDeleted( T );
			}
			if( Msg->m_Type == Comm::TYPE_CSCENE )
			{
				mLocalScene.close();
				HandleSceneDeleted();
			}
		} break;
	case Comm::MSG_ERROR:
		{
			HandleError( Msg->GetData() );
		} break;
	default: break;
	}

	
	boost::shared_ptr<Comm::Message> Inc( new Comm::Message );
	mConnection->AsyncRead( Inc,
		boost::bind( &SharomeInterface::HandleRead, this,
		boost::asio::placeholders::error, Inc ) );
}

void SharomeInterface::HandleObjectCreated( const OOWM::Mem::CObj& Obj )
{
	CreateEntityFromCObj( mEntityPool, Obj );
}

void SharomeInterface::HandleObjectChanged( const OOWM::Mem::CObj& Obj )
{
	mEntityPool.RemoveEntitiesByAttributeValue<std::string>( "SharomeId", Obj.getId() );
	CreateEntityFromCObj( mEntityPool, Obj );
}

void SharomeInterface::HandleObjectDeleted( const OOWM::Mem::CObj& Obj )
{
	mEntityPool.RemoveEntitiesByAttributeValue<std::string>( "SharomeId", Obj.getId() );
}

void SharomeInterface::HandleSceneChanged()
{
	// remove all Sharome entities
	mEntityPool.RemoveEntitiesByAttribute( "SharomeId" );

	// add all objects of changed scene
	std::set<std::string> Ids;
	mLocalScene.getIdsByName( Ids, "*" );
	for( std::set<std::string>::iterator i = Ids.begin(); i != Ids.end(); i++ )
	{
		OOWM::Mem::CObj O;
		mLocalScene.getById( O, *i );

		CreateEntityFromCObj( mEntityPool, O );
	}
				
}

void SharomeInterface::HandleSceneDeleted()
{
	mEntityPool.RemoveEntitiesByAttribute( "SharomeId" );
}

void SharomeInterface::HandleError( std::string Msg )
{

}

extern "C" INTERFACE_API
void LoadInterface( CInterfaceManager& InterfaceManager  )
{
	InterfaceManager.RegisterInterface<SharomeInterface>( "Sharome" );
}