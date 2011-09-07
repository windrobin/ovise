#include "AxisDisplay.h"

CAxisDisplay::CAxisDisplay( Ogre::SceneManager* SM )
{
	// create materials
	Ogre::MaterialPtr xAxisMat = Ogre::MaterialManager::getSingleton().create( "xAxisMaterial", "General");
	xAxisMat->setReceiveShadows( false );
	xAxisMat->getTechnique(0)->setLightingEnabled( false );
	xAxisMat->getTechnique(0)->getPass(0)->setVertexColourTracking( Ogre::TVC_AMBIENT | Ogre::TVC_DIFFUSE );
	xAxisMat->getTechnique(0)->getPass(0)->setDepthCheckEnabled( false );
	
	Ogre::MaterialPtr yAxisMat = Ogre::MaterialManager::getSingleton().create( "yAxisMaterial", "General" );
	yAxisMat->setReceiveShadows( false );
	yAxisMat->getTechnique(0)->setLightingEnabled( false );
	yAxisMat->getTechnique(0)->getPass(0)->setVertexColourTracking( Ogre::TVC_AMBIENT | Ogre::TVC_DIFFUSE );
	yAxisMat->getTechnique(0)->getPass(0)->setDepthCheckEnabled( false );
	
	Ogre::MaterialPtr zAxisMat = Ogre::MaterialManager::getSingleton().create( "zAxisMaterial", "General" );
	zAxisMat->setReceiveShadows( false );
	zAxisMat->getTechnique(0)->setLightingEnabled( false );
	zAxisMat->getTechnique(0)->getPass(0)->setVertexColourTracking( Ogre::TVC_AMBIENT | Ogre::TVC_DIFFUSE );
	zAxisMat->getTechnique(0)->getPass(0)->setDepthCheckEnabled( false );
	
	xAxis = SM->createManualObject( "xAxis" );
	yAxis = SM->createManualObject( "yAxis" );
	zAxis = SM->createManualObject( "zAxis" );

	xAxis->begin( "xAxisMaterial", Ogre::RenderOperation::OT_LINE_LIST );
	xAxis->position( Ogre::Vector3( -100, 0, 0 ) );
	xAxis->colour( 1, 0, 0 );
	xAxis->position( Ogre::Vector3( 100, 0, 0 ) );
	xAxis->colour( 1, 0, 0 );
	xAxis->end();
	xAxis->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY );

	yAxis->begin( "yAxisMaterial", Ogre::RenderOperation::OT_LINE_LIST );
	yAxis->position( Ogre::Vector3( 0, -100, 0 ) );
	yAxis->colour( 0, 1, 0 );
	yAxis->position( Ogre::Vector3( 0, 100, 0 ) );
	yAxis->colour( 0, 1, 0 );
	yAxis->end();
	yAxis->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY );

	zAxis->begin( "zAxisMaterial", Ogre::RenderOperation::OT_LINE_LIST );
	zAxis->position( Ogre::Vector3( 0, 0, -100 ) );
	zAxis->colour( 0, 0, 1 );
	zAxis->position( Ogre::Vector3( 0, 0, 100 ) );
	zAxis->colour( 0, 0, 1 );
	zAxis->end();
	zAxis->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY );

	AttachNode = SM->getRootSceneNode()->createChildSceneNode();
	AttachNode->attachObject( xAxis );
	AttachNode->attachObject( yAxis );
	AttachNode->attachObject( zAxis );

	xAxis->setVisible( false );
	yAxis->setVisible( false );
	zAxis->setVisible( false );
}

void CAxisDisplay::ShowXAxis( bool enable)
{
	if( enable )
	{
		xAxis->setVisible( true );
		yAxis->setVisible( false );
		zAxis->setVisible( false );
	}
	else
	{
		xAxis->setVisible( false );
	}
}

void CAxisDisplay::ShowYAxis( bool enable)
{
	if( enable )
	{
		xAxis->setVisible( false );
		yAxis->setVisible( true );
		zAxis->setVisible( false );
	}
	else
	{
		yAxis->setVisible( false );
	}
}

void CAxisDisplay::ShowZAxis( bool enable)
{
	if( enable )
	{
		xAxis->setVisible( false );
		yAxis->setVisible( false );
		zAxis->setVisible( true );
	}
	else
	{
		zAxis->setVisible( false );
	}
}

void CAxisDisplay::Disable()
{
	xAxis->setVisible( false );
	yAxis->setVisible( false );
	zAxis->setVisible( false );
}

void CAxisDisplay::SetPosition( const Ogre::Vector3& pos )
{
	AttachNode->setPosition( pos );
}

void CAxisDisplay::SetOrientation( const Ogre::Quaternion& quat )
{
	AttachNode->setOrientation( quat );
}

void CAxisDisplay::Attach( Ogre::SceneNode* node )
{
	AttachNode->getParentSceneNode()->removeChild( AttachNode );
	node->addChild( AttachNode );
}

CAxisDisplay::~CAxisDisplay(void)
{
}
