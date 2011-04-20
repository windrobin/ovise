#include "VoodooInterface.h"
#include <InterfaceManager.h>

#include "../rapidxml-1.13/rapidxml.hpp"

CVoodooInterface::CVoodooInterface( EntityPool& EntPool )
	: CNetworkInterface( EntPool )
{}

CVoodooInterface::~CVoodooInterface()
{}

bool CVoodooInterface::Start()
{
	if( !mVoodooParser.LoadBodyMapping() )
		return false;

	mVoodooDude = new Entity( "VoodooDude" );
	mVoodooDude->Set
		( "Type", "VoodooDoll" )
		( "Model", "VoodooDude.mesh" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
	;

	mVoodooDude = mEntityPool.InsertEntity( mVoodooDude );

	mConnection = CVoodooConnection::Create( mIOService );

	mConnection->MessageSignal.connect( boost::bind( &CVoodooInterface::
			HandleMessage, this, _1 ) );
	mConnection->Connect();

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

extern "C" INTERFACE_API
void LoadInterface( CInterfaceManager& InterfaceManager )
{
	InterfaceManager.RegisterInterface<CVoodooInterface>( "Voodoo" );
}
