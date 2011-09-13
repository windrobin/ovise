#include "SelectionBox.h"

CSelectionBox::CSelectionBox( Ogre::SceneManager* SceneMgr )
	: mSize( 1.f, 1.f, 1.f ), mParent( NULL ), 
	mCurrentToolAxis( OVISE::TOOLAXIS_NONE ), mCurrentToolMode( OVISE::TOOLMODE_NONE )
{
	mVisual = SceneMgr->createManualObject( OVISE_SelectionBoxName );
	mParent = SceneMgr->getRootSceneNode()->createChildSceneNode( OVISE_SelectionBoxName );
	mParent->attachObject( mVisual );

	Resize( mSize );

	mMoveManip = SceneMgr->createEntity( "MoveManip", "MoveManip.mesh" );
	mMoveNode = mParent->createChildSceneNode("Move");
	mMoveNode->attachObject( mMoveManip );
	mMoveManip->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY );
	mMoveNode->setVisible( false );

	mScaleManip = SceneMgr->createEntity( "ScaleManip", "ScaleManipulator.mesh" );
	mScaleNode = mParent->createChildSceneNode("Scale");
	mScaleNode->attachObject( mScaleManip );
	mScaleManip->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY );
	mScaleNode->setVisible( false );	

	mAxisDisplay.reset( new CAxisDisplay( SceneMgr ) );
	//mAxisDisplay->Attach( mParent );
	mAxisDisplay->Disable();

	mParent->setVisible( false );
}

CSelectionBox::~CSelectionBox()
{
}

void CSelectionBox::Show( Ogre::Entity* Target )
{
	if( Target == NULL )
	{
		mParent->setVisible( false );
		return;
	}

	// resize
	Resize( Target->getParentSceneNode()->_getWorldAABB().getSize() * 1.1f );
	// set to target's position
	mParent->setPosition( Target->getParentSceneNode()->_getWorldAABB().getCenter() );
	mParent->setOrientation( Target->getParentSceneNode()->getOrientation() );
	mParent->setVisible( true, false );

	switch( mCurrentToolMode )
	{
	case OVISE::TOOLMODE_MOVE:
		mMoveNode->setVisible( true );
		mScaleNode->setVisible( false );
		break;
	case OVISE::TOOLMODE_SCALE:
		mScaleNode->setVisible( true );
		mMoveNode->setVisible( false );
		break;
	default: mMoveNode->setVisible( false );
		mScaleNode->setVisible( false );
		break;
	}

	mAxisDisplay->SetPosition( mParent->getPosition() );
	mAxisDisplay->SetOrientation( mParent->getOrientation() );
}

void CSelectionBox::Hide()
{
	mParent->setVisible( false );
	mAxisDisplay->Disable();
}

const int CSelectionBox::GetToolAxis( Ogre::Camera* Cam, 
	const Ogre::Real& ScreenLeft, const Ogre::Real& ScreenTop,
	const Ogre::Real& ScreenRight, const Ogre::Real& ScreenBottom )
{
	// noop
	if( mCurrentToolMode == OVISE::TOOLMODE_NONE )
		return OVISE::TOOLAXIS_NONE;

	// Get box from camera into world around mouse position
	Ogre::PlaneBoundedVolume SelectionTube = Cam->getCameraToViewportBoxVolume(
		ScreenLeft, ScreenTop, ScreenRight, ScreenBottom );

	// setup three spheres on tips of move manipulator tool
	Ogre::Sphere XSphere, YSphere, ZSphere;
	Ogre::Matrix3 LocalAxes = mParent->getLocalAxes();
	XSphere.setCenter( mParent->_getDerivedPosition() + LocalAxes.GetColumn(0)*0.45f );
	XSphere.setRadius( 0.03f );
	YSphere.setCenter( mParent->_getDerivedPosition() + LocalAxes.GetColumn(1)*0.45f );
	YSphere.setRadius( 0.03f );
	ZSphere.setCenter( mParent->_getDerivedPosition() + LocalAxes.GetColumn(2)*0.45f );
	ZSphere.setRadius( 0.03f );

	int Axis = OVISE::TOOLAXIS_NONE;
	// intersect with SelectionTube, color selected axis and return axis
	if( SelectionTube.intersects( XSphere ) )
		Axis = OVISE::TOOLAXIS_X;
	else if( SelectionTube.intersects( YSphere ) )
		Axis = OVISE::TOOLAXIS_Y;
	else if( SelectionTube.intersects( ZSphere ) )
		Axis = OVISE::TOOLAXIS_Z;
	
	switch( mCurrentToolMode )
	{
	case OVISE::TOOLMODE_MOVE:
		ColorManipAxis( mMoveManip, Axis );
		break;
	case OVISE::TOOLMODE_SCALE:
		ColorManipAxis( mScaleManip, Axis );
		break;
	default: break;
	}

	return Axis;
}

void CSelectionBox::ColorManipAxis( Ogre::Entity* Manip, const int& Axis )
{
	Ogre::MaterialPtr SelectedAxisMat = 
		Ogre::MaterialManager::getSingleton().getByName( "SelectedAxisMaterial", "General" );
	if( SelectedAxisMat.isNull() )
	{
		SelectedAxisMat = Ogre::MaterialManager::getSingleton().create( "SelectedAxisMaterial", "General");
		SelectedAxisMat->setAmbient( 0.8f, 0.8f, 0.1f );
		SelectedAxisMat->setDiffuse( 0.8f, 0.8f, 0.1f, 1.f );
		SelectedAxisMat->setDepthCheckEnabled( false );
	}

	switch( Axis )
	{
	case OVISE::TOOLAXIS_X:
		Manip->getSubEntity(0)->setMaterial( SelectedAxisMat );
		break;
	case OVISE::TOOLAXIS_Y:
		Manip->getSubEntity(1)->setMaterial( SelectedAxisMat );
		break;
	case OVISE::TOOLAXIS_Z:
		Manip->getSubEntity(2)->setMaterial( SelectedAxisMat );
		break;
	default: 
		Manip->getSubEntity(0)->setMaterialName( "XAxis" );
		Manip->getSubEntity(1)->setMaterialName( "YAxis" );
		Manip->getSubEntity(2)->setMaterialName( "ZAxis" );
		break;
	}
}

void CSelectionBox::Resize( const Ogre::Vector3& Size )
{
	if( mParent == NULL )
		return;

	if( mVisual->getNumSections() == 0 )
		mVisual->begin( "__SelectionBoxMat", Ogre::RenderOperation::OT_LINE_LIST );
	else
		mVisual->beginUpdate(0);

	// Calculate corner points
	Ogre::Vector3 TopLeftBack, TopLeftFront, TopRightBack, TopRightFront,
		BottomLeftBack, BottomLeftFront, BottomRightBack, BottomRightFront;
	
	TopLeftBack = TopLeftFront = TopRightBack = TopRightFront =
		BottomLeftBack = BottomLeftFront = BottomRightBack = BottomRightFront = 
		mParent->getParent()->getPosition();

	BottomLeftBack -= Size/2;
	TopRightFront += Size/2;
	
	TopLeftFront += Ogre::Vector3( Size.x/2, -Size.y/2, Size.z/2 );
	TopRightBack += Ogre::Vector3( -Size.x/2, Size.y/2, Size.z/2 );
	TopLeftBack += Ogre::Vector3( -Size.x/2, -Size.y/2, Size.z/2 );

	BottomLeftFront += Ogre::Vector3( Size.x/2, -Size.y/2, -Size.z/2 );
	BottomRightBack += Ogre::Vector3( -Size.x/2, Size.y/2, -Size.z/2 );
	BottomRightFront += Ogre::Vector3( Size.x/2, Size.y/2, -Size.z/2 );

	float CornerSize;
	if( Size.x <= Size.y && Size.x <= Size.z )
		CornerSize = Size.x;
	else if( Size.y < Size.x && Size.y <= Size.z )
		CornerSize = Size.y;
	else CornerSize = Size.z;
	CornerSize *= 0.25f;

	Ogre::Vector3 xDir( CornerSize, 0.f, 0.f );
	Ogre::Vector3 yDir( 0.f, CornerSize, 0.f );
	Ogre::Vector3 zDir( 0.f, 0.f, CornerSize );

	// TopLeftFront
	mVisual->position( TopLeftFront );
	mVisual->position( TopLeftFront - zDir );
	mVisual->position( TopLeftFront );
	mVisual->position( TopLeftFront - xDir );
	mVisual->position( TopLeftFront );
	mVisual->position( TopLeftFront + yDir );

	// TopLeftBack
	mVisual->position( TopLeftBack );
	mVisual->position( TopLeftBack - zDir );
	mVisual->position( TopLeftBack );
	mVisual->position( TopLeftBack + xDir );
	mVisual->position( TopLeftBack );
	mVisual->position( TopLeftBack + yDir );

	// TopRightFront
	mVisual->position( TopRightFront );
	mVisual->position( TopRightFront - zDir );
	mVisual->position( TopRightFront );
	mVisual->position( TopRightFront - xDir );
	mVisual->position( TopRightFront );
	mVisual->position( TopRightFront - yDir );

	// TopRightBack
	mVisual->position( TopRightBack );
	mVisual->position( TopRightBack - zDir );
	mVisual->position( TopRightBack );
	mVisual->position( TopRightBack + xDir );
	mVisual->position( TopRightBack );
	mVisual->position( TopRightBack - yDir );

	// BottomLeftFront
	mVisual->position( BottomLeftFront );
	mVisual->position( BottomLeftFront + zDir );
	mVisual->position( BottomLeftFront );
	mVisual->position( BottomLeftFront - xDir );
	mVisual->position( BottomLeftFront );
	mVisual->position( BottomLeftFront + yDir );

	// BottomLeftBack
	mVisual->position( BottomLeftBack );
	mVisual->position( BottomLeftBack + zDir );
	mVisual->position( BottomLeftBack );
	mVisual->position( BottomLeftBack + xDir );
	mVisual->position( BottomLeftBack );
	mVisual->position( BottomLeftBack + yDir );

	// BottomRightFront
	mVisual->position( BottomRightFront );
	mVisual->position( BottomRightFront + zDir );
	mVisual->position( BottomRightFront );
	mVisual->position( BottomRightFront - xDir );
	mVisual->position( BottomRightFront );
	mVisual->position( BottomRightFront - yDir );

	// BottomRightBack
	mVisual->position( BottomRightBack );
	mVisual->position( BottomRightBack + zDir );
	mVisual->position( BottomRightBack );
	mVisual->position( BottomRightBack + xDir );
	mVisual->position( BottomRightBack );
	mVisual->position( BottomRightBack - yDir );
	
	mVisual->end();
}
