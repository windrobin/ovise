#include "InputHandler.h"

#include <CCSOrbitalCameraMode.h>
#include "AppContext.h"

InputHandler::InputHandler( CCS::CameraControlSystem* CCS,
                            wxWindow *       parent )
							: mCCS( CCS ), mParent( parent ),
							mRotateSpeed( 20.f ), mMoveSpeed( 0.05f ),
							mMouseCaptured( false )
{
	parent->Bind( wxEVT_KEY_DOWN, &InputHandler::handleKeyboardInput, this );
	parent->Bind( wxEVT_RIGHT_DOWN, &InputHandler::handleMouseInput, this );
	parent->Bind( wxEVT_MIDDLE_DOWN, &InputHandler::handleMouseInput, this );
	parent->Bind( wxEVT_MOTION, &InputHandler::handleMouseInput, this );
	parent->Bind( wxEVT_MOUSEWHEEL, &InputHandler::handleMouseInput, this );
	parent->Bind( wxEVT_ENTER_WINDOW, &InputHandler::handleMouseInput, this );
}

InputHandler::~InputHandler( void )
{}

void InputHandler::handleMouseInput( wxMouseEvent &evt )
{
	if( evt.Entering() )
	{
		mParent->SetFocus();
		return;
	}

	CCS::OrbitalCameraMode* OCM = 
		static_cast<CCS::OrbitalCameraMode*>( mCCS->getCameraMode( "Orbital" ) );
	
	if(evt.RightIsDown())
	{
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;
			OCM->yaw( (newX-mX)*mRotateSpeed );
			OCM->pitch( (newY-mY)*mRotateSpeed );

			mX = newX;
			mY = newY;
		}
		else
		{
			mX = evt.GetPosition().x;
			mY = evt.GetPosition().y;
		}
	}
	if(evt.GetWheelDelta() != 0)
	{
		OCM->zoom( evt.GetWheelRotation()/-20.f );
	}
	if(evt.MiddleIsDown())
	{
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;

			translateCameraHorizontal( newX-mX );			
			translateCameraVertical( newY-mY );

			mX = newX;
			mY = newY;
		}
		else
		{
			mX = evt.GetPosition().x;
			mY = evt.GetPosition().y;
		}
	}
	mParent->Refresh( false );
	evt.Skip();
}

void InputHandler::handleKeyboardInput( wxKeyEvent &evt )
{
	switch(evt.GetKeyCode())
	{
	case 'f':
	case 'F':
		//focusCamera();
		if( CAppContext::instance().HasSelection() )
		{
			Entity* TargetEntity = CAppContext::instance().GetSelected();
			Ogre::Entity* Target = TargetEntity->GetOgreEntity();
			if( Target != NULL )
			{
				mCCS->getTargetSceneNode()->setPosition(
					Target->getParentSceneNode()->getPosition() );
			}
		}
		break;
	case WXK_DELETE:
		this->DeleteSelectedObjects();
		break;
	default:
		break;
	}
	evt.Skip();
}

void InputHandler::translateCamera( Ogre::Vector3 trans )
{
	mCCS->getTargetSceneNode()->translate( trans, Ogre::Node::TS_WORLD );
}

void InputHandler::translateCameraVertical( int Delta )
{
	Ogre::Matrix3 localAxes = mCCS->getCameraSceneNode()->getLocalAxes();
	Ogre::Vector3 vertical = localAxes.GetColumn( 1 );
	vertical.normalise();

	translateCamera( Delta/100.f * vertical );
}

void InputHandler::translateCameraHorizontal( int Delta )
{
	Ogre::Matrix3 localAxes = mCCS->getCameraSceneNode()->getLocalAxes();
	Ogre::Vector3 horizontal = localAxes.GetColumn( 0 );
	horizontal.normalise();

	translateCamera( -Delta/100.f * horizontal );
}

void InputHandler::DeleteSelectedObjects()
{
/*	QualifiedNameCollection Selection(SelectionManager::getSingletonPtr()->Selection);
        for (unsigned long IT = 0; IT < Selection.Count(); IT++)
        {
                // A QualififiedName is unique and can be associated deterministically. So try to destroy it via all interfaces.
                // Don't worry about childs: interfaces destroy 'em, too.
                OgreMediator::GetSingletonPtr()->iCamera.Destroy(Selection[IT]);
                OgreMediator::GetSingletonPtr()->iEntity.Destroy(Selection[IT]);
                OgreMediator::GetSingletonPtr()->iLight.Destroy(Selection[IT]);
                OgreMediator::GetSingletonPtr()->iSceneManager.Destroy(Selection[IT]);
                OgreMediator::GetSingletonPtr()->iSceneNode.Destroy(Selection[IT]);
        }*/
}
