#include "OViSEInputHandler.h"

OViSEInputHandler::OViSEInputHandler(Ogre::Camera *cam, Ogre::SceneNode *camnode, wxWindow *parent)
{
	mCamera = cam;
	mCameraNode = camnode;
	mParent = parent;
	mRotateSpeed = 1.0;
	mMoveSpeed = 1.0;
	mMouseCaptured = false;
}

OViSEInputHandler::~OViSEInputHandler(void)
{
}

void OViSEInputHandler::handleMouseInput(wxMouseEvent &evt)
{
	/*if(evt.RightUp())
	{
		mParent->ReleaseMouse();
		mMouseCaptured = false;
	}
	if(evt.MiddleUp())
	{
		mParent->ReleaseMouse();
		mMouseCaptured = false;*/
	if(evt.RightIsDown())
	{
		/*if(!mMouseCaptured)
		{
			mParent->CaptureMouse();
			mMouseCaptured = true;
		}*/
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
	if(evt.MiddleIsDown())
	{
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;

			if(newX > mX)
				translateCameraHorizontal(mMoveSpeed * 0.5);
			else if(newX < mX)
				translateCameraHorizontal(-mMoveSpeed * 0.5);

			if(newY > mY)
				translateCameraVertical(-mMoveSpeed);
			else if(newY < mY)
				translateCameraVertical(mMoveSpeed);
	
			mX = newX;
			mY = newY;
		}
	}
	evt.Skip();
}

void OViSEInputHandler::handleKeyboardInput(wxKeyEvent &evt)
{
	switch(evt.GetKeyCode())
	{
	case 'a':
	case 'A':
		translateCameraHorizontal(-mMoveSpeed);
		break;
	case 'd':
	case 'D':
		translateCameraHorizontal(mMoveSpeed);
		break;
	case 'w':
	case 'W':
		translateCameraDirectional(-mMoveSpeed);
		break;
	case 's':
	case 'S':
		translateCameraDirectional(mMoveSpeed);
		break;
	case 'q':
	case 'Q':
		translateCameraVertical(mMoveSpeed);
		break;
	case 'e':
	case 'E':
		translateCameraVertical(-mMoveSpeed);
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

void OViSEInputHandler::translateCameraVertical(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 vertical = localAxes.GetColumn(1);
	vertical.normalise();

	translateCamera(moveSpeed * vertical);
}

void OViSEInputHandler::translateCameraHorizontal(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 horizontal = localAxes.GetColumn(0);
	horizontal.normalise();

	translateCamera(moveSpeed * horizontal);
}

void OViSEInputHandler::translateCameraDirectional(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 directional = localAxes.GetColumn(2);	
	directional.normalise();

	translateCamera(moveSpeed * directional);
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
