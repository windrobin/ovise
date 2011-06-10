#include "SharomeInterface.h"

#include <boost/foreach.hpp>

#include <InterfaceManager.h>
#include <Mem/Serialization.hpp>
#include <Mem/Location.h>
#include <Result.h>

namespace
{
	void CreateEntityFromCObj( EntityPool& Pool, const OOWM::Mem::CObj& Obj )
	{
		Entity& E = Pool.CreateEntity( Obj.getName() );
		E.Set
			( "Type", "Simple" )
			( "Model", Obj.getName() + ".mesh" )
			( "SharomeId", Obj.getId() )
		;

		OOWM::Mem::CAttribute A;
		OOWM::SResult         Result;
		Obj.getFirstByName( A, "Location", &Result );
		if( Result.m_nCode == R_OK )
		{
			OOWM::Mem::CLocation L;
			if( L.FromAttribute( A ) )
			{
				E.SetAttribute( "Position",
					vec3( float(L.m_Position.m_Value[0]),
					float(L.m_Position.m_Value[1]),
					float(L.m_Position.m_Value[2] ) ) );
				E.SetAttribute( "Orientation",
					quat( float(L.m_Orientation.m_Value.w),
					float(L.m_Orientation.m_Value.x),
					float(L.m_Orientation.m_Value.y),
					float(L.m_Orientation.m_Value.z ) ) );
				E.SetAttribute( "Scale",
					vec3( float(L.m_Scale.m_Value[0]),
					float(L.m_Scale.m_Value[1]),
					float(L.m_Scale.m_Value[2] ) ) );
			}
		}
	}
}


SharomeInterface::SharomeInterface( EntityPool& EntPool )
	: CNetworkInterface( EntPool )
{}


SharomeInterface::~SharomeInterface( void )
{}

bool SharomeInterface::Start( const std::string& Host, const std::string& Service )
{
	std::cout << "SharomeInterface init." << std::endl;

	LegacyClient.reset( new CAsyncClient( Host, Service, true ) );
	LegacyClient->ObjectCreatedSignal.connect(
		boost::bind( &SharomeInterface::HandleObjectCreated, this, _1 ) );
	LegacyClient->ObjectChangedSignal.connect(
		boost::bind( &SharomeInterface::HandleObjectChanged, this, _1, _2 ) );
	LegacyClient->ObjectDeletedSignal.connect(
		boost::bind( &SharomeInterface::HandleObjectDeleted, this, _1 ) );
	LegacyClient->SceneChangedSignal.connect(
		boost::bind( &SharomeInterface::HandleSceneChanged, this, _1 ) );
	LegacyClient->SceneDeletedSignal.connect(
		boost::bind( &SharomeInterface::HandleSceneDeleted, this ) );
	LegacyClient->ErrorSignal.connect(
		boost::bind( &SharomeInterface::HandleError, this, _1 ) );

	return true;
}

bool SharomeInterface::Stop()
{
	std::cout << "SharomeInterface uninit." << std::endl;
	LegacyClient.reset();

	return true;
}

void SharomeInterface::Poll()
{
	if( LegacyClient )
		LegacyClient->Poll();
}

void SharomeInterface::HandleObjectCreated( const OOWM::Mem::CObj& Obj )
{
	CreateEntityFromCObj( mEntityPool, Obj );
}

void SharomeInterface::HandleObjectChanged( const OOWM::Mem::CObj& Obj,
	const OOWM::Mem::CObj& OldObj )
{
	Entity* OldEnt = mEntityPool.GetEntityByAttribute( "SharomeId", Obj.getId() );
	if( OldEnt )
	{
		const std::string AttName = "SharomeId";
		std::string ObjID = Obj.getId();
		mEntityPool.RemoveEntitiesByAttributeValue( AttName, ObjID );
	}
	CreateEntityFromCObj( mEntityPool, Obj );
}

void SharomeInterface::HandleObjectDeleted( const OOWM::Mem::CObj& Obj )
{
	const std::string AttName = "SharomeId";
	std::string ObjID = Obj.getId();
	mEntityPool.RemoveEntitiesByAttributeValue( AttName, ObjID );
}

void SharomeInterface::HandleSceneChanged( const OOWM::Mem::CScene& Scene )
{
	// remove all Sharome entities
	mEntityPool.RemoveEntitiesByAttribute( "SharomeId" );

	// add all objects of changed scene
	std::set<std::string> Ids;
	Scene.getIdsByName( Ids, "*" );
	for( std::set<std::string>::iterator i = Ids.begin();
	     i != Ids.end();
	     i++ )
	{
		OOWM::Mem::CObj O;
		Scene.getById( O, *i );

		CreateEntityFromCObj( mEntityPool, O );
	}
}

void SharomeInterface::HandleSceneDeleted()
{
	mEntityPool.RemoveEntitiesByAttribute( "SharomeId" );
}

void SharomeInterface::HandleError( std::string Msg )
{}

extern "C" INTERFACE_API
void LoadInterface( CInterfaceManager& InterfaceManager  )
{
	InterfaceManager.RegisterInterface<SharomeInterface>( "Sharome" );
}
