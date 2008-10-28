#include "OViSEInputHandler.h"

OViSEInputHandler::OViSEInputHandler(Ogre::Camera *cam, Ogre::SceneNode *camnode, wxWindow *parent)
{
	mCamera = cam;
	mCameraNode = camnode;
	mParent = parent;
	mRotateSpeed = 1.0;
	mMoveSpeed = 1.0;
	mRightMouseDown = false;
	mMouseCaptured = false;
}

OViSEInputHandler::~OViSEInputHandler(void)
{
}

void OViSEInputHandler::handleMouseInput(wxMouseEvent &evt)
{
	if(evt.RightUp())
	{
		mRightMouseDown = false;
		mParent->ReleaseMouse();
		mMouseCaptured = false;
	}
	if(evt.RightIsDown())
	{
		mRightMouseDown = true;
		if(!mMouseCaptured)
		{
			mParent->CaptureMouse();
			mMouseCaptured = true;
		}
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;

			if(newX > mX)
				yawCamera(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
			else if(newX < mX)
				yawCamera(Ogre::Radian(Ogre::Degree(mRotateSpeed)));

			if(newY > mY)
				pitchCamera(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
			else if(newY < mY)
				pitchCamera(Ogre::Radian(Ogre::Degree(mRotateSpeed)));
	
			mX = newX;
			mY = newY;
		}
	}
	if(evt.GetWheelDelta() != 0)
	{
		if(evt.GetWheelRotation() > 0)
			zoomCamera(-mMoveSpeed);
		else
			zoomCamera(mMoveSpeed);
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
		translateCamera(Ogre::Vector3(-mMoveSpeed, 0, 0));
		break;
	case 'd':
	case 'D':
		translateCamera(Ogre::Vector3(mMoveSpeed, 0, 0));
		break;
	case 'w':
	case 'W':
		translateCamera(Ogre::Vector3(0, 0, -mMoveSpeed));
		break;
	case 's':
	case 'S':
		translateCamera(Ogre::Vector3(0, 0, mMoveSpeed));
		break;
	case 'q':
	case 'Q':
		translateCamera(Ogre::Vector3(0, mMoveSpeed, 0));
		break;
	case 'e':
	case 'E':
		translateCamera(Ogre::Vector3(0, -mMoveSpeed, 0));
		break;
	case 'f':
	case 'F':
		focusCamera();
		break;
	default: break;
	}
	evt.Skip();
}

void OViSEInputHandler::setCamera(Ogre::Camera *cam, Ogre::SceneNode *camnode)
{
	mCamera = cam;
	mCameraNode = camnode;
}

void OViSEInputHandler::translateCamera(Ogre::Vector3 trans)
{
	if(mCameraNode == NULL)
		mCamera->moveRelative(trans);
	else
	{
		mCameraNode->translate(trans, Ogre::Node::TS_PARENT);
	}
}

void OViSEInputHandler::zoomCamera(double amount)
{
	if(mCameraNode != NULL)
	{
		mCamera->getParentSceneNode()->translate(0, 0, amount, Ogre::Node::TS_LOCAL);
		Ogre::Vector3 pos = mCamera->getParentSceneNode()->getPosition();
		if (pos.z < mCamera->getNearClipDistance())
		{
			mCamera->getParentSceneNode()->setPosition(pos.x, pos.y, mCamera->getNearClipDistance());
		}
	}
	else
	{
		mCamera->moveRelative(Ogre::Vector3(0, 0, amount));
		Ogre::Vector3 pos = mCamera->getPosition();
		if (pos.z < mCamera->getNearClipDistance())
		{
			mCamera->setPosition(pos.x, pos.y, mCamera->getNearClipDistance());
		}
	}
}

void OViSEInputHandler::yawCamera(Ogre::Radian angle)
{
	if(mCameraNode == NULL)
	{
		mCamera->yaw(angle);
	}
	else
	{
		mCameraNode->yaw(angle, Ogre::Node::TS_WORLD);
	}
}

void OViSEInputHandler::pitchCamera(Ogre::Radian angle)
{
	if(mCameraNode == NULL)
	{
		mCamera->pitch(angle);
	}
	else
	{
		mCameraNode->pitch(angle, Ogre::Node::TS_LOCAL);
	}
}

void OViSEInputHandler::focusCamera()
{
	std::string scnMgrName = mCamera->getSceneManager()->getName();
	OViSESceneHandling *sceneHandler = OViSESceneHandling::getSingletonPtr();
	if(sceneHandler->hasSelectedObjects(scnMgrName))
	{
		OViSESelectionMap selObjs = sceneHandler->getSelectedObjects(scnMgrName);
		Ogre::Vector3 avgPos = Ogre::Vector3::ZERO;
		int count = 0;
		for(OViSESelectionMap::iterator it = selObjs.begin(); it != selObjs.end(); it++)
		{
			avgPos += it->second->getParentSceneNode()->getPosition();
			count++;
		}
		avgPos /= count;

		if(mCameraNode == NULL)
		{
			mCamera->setPosition(avgPos);
		}
		else
		{
			mCameraNode->setPosition(avgPos);
		}
	}
}
