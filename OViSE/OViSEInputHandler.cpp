#include "OViSEInputHandler.h"

OViSEInputHandler::OViSEInputHandler(Ogre::Camera *cam)
{
	mCamera = cam;
	mRotateSpeed = 0.5;
	mMoveSpeed = 1.0;
}

OViSEInputHandler::~OViSEInputHandler(void)
{
}

void OViSEInputHandler::handleMouseInput(wxMouseEvent &evt)
{
	if(evt.RightUp())
	{
		mRightMouseDown = false;
	}
	if(evt.RightIsDown())
	{
		mRightMouseDown = true;
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;

			if(newX > mX)
				mCamera->yaw(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
			else if(newX < mX)
				mCamera->yaw(Ogre::Radian(Ogre::Degree(mRotateSpeed)));

			if(newY > mY)
				mCamera->pitch(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
			else if(newY < mY)
				mCamera->pitch(Ogre::Radian(Ogre::Degree(mRotateSpeed)));
			mX = newX;
			mY = newY;
		}
	}	
	evt.Skip();
}

void OViSEInputHandler::handleKeyboardInput(wxKeyEvent &evt)
{
	Ogre::Vector3 transVec = Ogre::Vector3::ZERO;
	switch(evt.GetKeyCode())
	{
	case 'a':
	case 'A':
		transVec.x -= mMoveSpeed;
		break;
	case 'd':
	case 'D':
		transVec.x += mMoveSpeed;
		break;
	case 'w':
	case 'W':
		transVec.z -= mMoveSpeed;
		break;
	case 's':
	case 'S':
		transVec.z += mMoveSpeed;
		break;
	case 'q':
	case 'Q':
		transVec.y += mMoveSpeed;
		break;
	case 'e':
	case 'E':
		transVec.y -= mMoveSpeed;
		break;
	default: break;
	}
	mCamera->moveRelative(transVec);

	evt.Skip();
}

void OViSEInputHandler::setCamera(Ogre::Camera *cam)
{
	mCamera = cam;
}