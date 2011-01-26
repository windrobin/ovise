#include "VoodooInterface.h"
#include <InterfaceManager.h>

#include "../rapidxml-1.13/rapidxml.hpp"

CVoodooInterface::CVoodooInterface( EntityPool& EntPool )
	: CNetworkInterface( EntPool )
{
}

CVoodooInterface::~CVoodooInterface()
{
}

bool CVoodooInterface::Start()
{
	mVoodooDude = new Entity( "VoodooDude" );
	mVoodooDude->Set
		( "Type", "VoodooDoll" )
		( "Model", "VoodooDude.mesh" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
	;

	mVoodooDude = mEntityPool.InsertEntity( mVoodooDude );		

	mConnection = CVoodooConnection::Create( mIOService );

	mConnection->MessageSignal.connect( boost::bind( &CVoodooInterface::HandleMessage, this, _1 ) );
	mConnection->Connect();
}

bool CVoodooInterface::Stop()
{
	mIOService.stop();
}

void CVoodooInterface::Poll()
{
	mIOService.poll();
	mIOService.reset();
}

void CVoodooInterface::HandleMessage( const std::string& Msg )
{
	rapidxml::xml_document<> Document;
	Document.parse<0>( const_cast<char*>( Msg.c_str() ) );

	rapidxml::xml_node<>* RootNode = Document.first_node( "VooDooConnectData" );
	if( !RootNode )
		return; // error happened

	rapidxml::xml_node<>* DataNode = RootNode->first_node( "humPosDataSet" );
	if( !DataNode )
		return; // error happened

/*
<VooDooConnectData>
        <dataType>2</dataType>
        <actRecDataDistribution>
                <dataEntry name="humPresence">0.000000</dataEntry>
        </actRecDataDistribution>
        <humPosDataSet>
                <dataEntry name="humPresence">0.000000</dataEntry>
                <dataEntry id="0" limb="0" name="xPos">50.000000</dataEntry>
                <dataEntry id="0" limb="0" name="y1">1.658063</dataEntry>
                <dataEntry id="0" limb="0" name="yPos">0.000000</dataEntry>
                <dataEntry id="0" limb="0" name="z0">-1.466077</dataEntry>
                <dataEntry id="0" limb="0" name="z2">1.570796</dataEntry>
                <dataEntry id="0" limb="0" name="zPos">3000.000000</dataEntry>
                <dataEntry id="0" limb="3" name="xPos">-274.863037</dataEntry>
                <dataEntry id="0" limb="3" name="y1">1.296665</dataEntry>
                <dataEntry id="0" limb="3" name="yPos">-371.300476</dataEntry>
                <dataEntry id="0" limb="3" name="z0">1.866394</dataEntry>
                <dataEntry id="0" limb="3" name="z2">0.765761</dataEntry>
                <dataEntry id="0" limb="3" name="zPos">2970.664307</dataEntry>
                <dataEntry id="0" limb="4" name="xPos">-387.036804</dataEntry>
                <dataEntry id="0" limb="4" name="yPos">-2.937148</dataEntry>
                <dataEntry id="0" limb="4" name="zPos">3078.948730</dataEntry>
                <dataEntry id="0" limb="6" name="xPos">465.258545</dataEntry>
                <dataEntry id="0" limb="6" name="y1">1.495245</dataEntry>
                <dataEntry id="0" limb="6" name="yPos">-315.547577</dataEntry>
                <dataEntry id="0" limb="6" name="z0">1.150265</dataEntry>
                <dataEntry id="0" limb="6" name="z2">1.614513</dataEntry>
                <dataEntry id="0" limb="6" name="zPos">2968.746826</dataEntry>
                <dataEntry id="0" limb="7" name="xPos">628.091003</dataEntry>
                <dataEntry id="0" limb="7" name="yPos">48.559647</dataEntry>
                <dataEntry id="0" limb="7" name="zPos">2998.938477</dataEntry>
        </humPosDataSet>
        <hbiDataSet>
                <dataEntry id="0" name="hbiFinished">0.000000</dataEntry>
                <dataEntry id="0" name="humanHeight">-1.000000</dataEntry>
        </hbiDataSet>
</VooDooConnectData>
*/
}

extern "C" INTERFACE_API
void LoadInterface( CInterfaceManager& InterfaceManager )
{
	InterfaceManager.RegisterInterface<CVoodooInterface>( "Voodoo" );
}
