#include "VoodooInterface.h"
#include <InterfaceManager.h>

#include "../rapidxml-1.13/rapidxml.hpp"

#include <PluginManager.h>

CVoodooInterface::CVoodooInterface( EntityPool& EntPool, const wxString& Name )
	: CNetworkInterface( EntPool, Name )
{}

CVoodooInterface::~CVoodooInterface()
{}

bool CVoodooInterface::Start()
{
	if( !mVoodooParser.LoadBodyMapping() )
		return false;

	mVoodooDude = new Entity( "VoodooDude" );
	mVoodooDude->Set
		( "Type", "VoodooPlugin" )
		( "Model", "VoodooDude.mesh" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
	;

	mVoodooDude = mEntityPool.InsertEntity( mVoodooDude );

	mConnection = CVoodooConnection::Create( mIOService );

	mConnection->MessageSignal.connect( boost::bind( &CVoodooInterface::
			HandleMessage, this, _1 ) );

	std::string ServerAdress = "localhost";
	std::string ServerPort = "22613";

	mConnection->Connect( ServerAdress, ServerPort );

	return true;
}

bool CVoodooInterface::Stop()
{
	mIOService.stop();
	return true;
}

void CVoodooInterface::Poll()
{
	mIOService.poll_one();
	mIOService.reset();
}

void CVoodooInterface::HandleMessage( const std::string& Msg )
{
	rapidxml::xml_document<> Document;
	Document.parse<0>( const_cast<char*>( Msg.c_str() ) );

	if( mVoodooParser.ParseDocument( Document ) )
		mVoodooParser.UpdateEntity( mVoodooDude );
}

extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterNetworkPlugin<CVoodooInterface>( "VoodooInterface" );
}
