#include "SelectionBox.h"

CSelectionBox::CSelectionBox( Ogre::SceneManager* SceneMgr )
	: mSize( 1.f, 1.f, 1.f ), mParent( NULL )
{
	mVisual = SceneMgr->createManualObject( OVISE_SelectionBoxName );
	mParent = SceneMgr->getRootSceneNode()->createChildSceneNode( OVISE_SelectionBoxName );
	mParent->attachObject( mVisual );
	mParent->setVisible( false );
	Resize( mSize );
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
	mParent->setVisible( true );
}

void CSelectionBox::Hide()
{
	mParent->setVisible( false );
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
