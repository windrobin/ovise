#include "InputHandler.h"

#include "SelectionManager.h"

InputHandler::InputHandler(Ogre::Camera *cam, Ogre::SceneNode *camnode, wxWindow *parent)
{
	mCamera = cam;
	mCameraNode = camnode;
	mParent = parent;
	mRotateSpeed = 1.0;
	mMoveSpeed = 0.05;
	mMouseCaptured = false;

	parent->Bind(wxEVT_KEY_DOWN, &InputHandler::handleKeyboardInput, this);
	parent->Bind(wxEVT_RIGHT_DOWN, &InputHandler::handleMouseInput, this);
	parent->Bind(wxEVT_MIDDLE_DOWN, &InputHandler::handleMouseInput, this);
	parent->Bind(wxEVT_MOTION, &InputHandler::handleMouseInput, this);
	parent->Bind(wxEVT_MOUSEWHEEL, &InputHandler::handleMouseInput, this);
}

InputHandler::~InputHandler(void)
{
}

void InputHandler::handleMouseInput(wxMouseEvent &evt)
{
	if(evt.RightIsDown())
	{
		if(evt.Dragging())
		{
			int newX = evt.GetPosition().x;
			int newY = evt.GetPosition().y;

			if(newX > mX)
				yawCamera(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
			else if(newX < mX)
				yawCamera(Ogre::Radian(Ogre::Degree(mRotateSpeed)));

			if(newY > mY)
				pitchCamera(Ogre::Radian(Ogre::Degree(mRotateSpeed)));
			else if(newY < mY)
				pitchCamera(Ogre::Radian(Ogre::Degree(-mRotateSpeed)));
	
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

void InputHandler::handleKeyboardInput(wxKeyEvent &evt)
{
	switch(evt.GetKeyCode())
	{
	case 'a':
	case 'A':
		translateCameraHorizontal(mMoveSpeed);
		break;
	case 'd':
	case 'D':
		translateCameraHorizontal(-mMoveSpeed);
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
	case 't':
	case 'T':
		showHelpOverlay();
		break;
	default: break;
	}
	evt.Skip();
}

void InputHandler::setCamera(Ogre::Camera *cam, Ogre::SceneNode *camnode)
{
	mCamera = cam;
	mCameraNode = camnode;
}

void InputHandler::translateCamera(Ogre::Vector3 trans)
{
	if(mCameraNode == NULL)
		mCamera->moveRelative(trans);
	else
	{
		mCameraNode->translate(trans, Ogre::Node::TS_PARENT);
	}
}

void InputHandler::translateCameraVertical(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 vertical = localAxes.GetColumn(2);
	vertical.normalise();

	translateCamera(moveSpeed * vertical);
}

void InputHandler::translateCameraHorizontal(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 horizontal = localAxes.GetColumn(0);
	horizontal.normalise();

	translateCamera(moveSpeed * horizontal);
}

void InputHandler::translateCameraDirectional(double moveSpeed)
{
	Ogre::Matrix3 localAxes = mCameraNode->getLocalAxes();
	Ogre::Vector3 directional = localAxes.GetColumn(1);	
	directional.normalise();

	translateCamera(moveSpeed * directional);
}

void InputHandler::zoomCamera(double amount)
{
	if(mCameraNode != NULL)
	{
		mCamera->getParentSceneNode()->translate(0, amount, 0, Ogre::Node::TS_PARENT);
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

void InputHandler::yawCamera(Ogre::Radian angle)
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

void InputHandler::pitchCamera(Ogre::Radian angle)
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

void InputHandler::setDistance(float dist)
{
	if(mCameraNode == NULL)
		return;
	mCamera->getParentSceneNode()->setPosition(Ogre::Vector3(0, dist, 0));
	Ogre::Vector3 pos = mCamera->getParentSceneNode()->getPosition();
	if (pos.z < mCamera->getNearClipDistance())
	{
		mCamera->getParentSceneNode()->setPosition(pos.x, pos.y, mCamera->getNearClipDistance());
	}
}

void InputHandler::focusCamera()
{
	// FIXME: replace with new selection functionality
	SelectionManager* SelMgr = SelectionManager::getSingletonPtr();
	if(SelMgr->Selection.Count() != 0)
	{
		Ogre::AxisAlignedBox ObjectsBox = Ogre::AxisAlignedBox::BOX_NULL;
		Ogre::Vector3 avgPos = Ogre::Vector3::ZERO;
		for(unsigned long i = 0; i < SelMgr->Selection.Count(); i++)
		{
			Ogre::AxisAlignedBox temp = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(SelMgr->Selection[i])->getWorldBoundingBox();
			ObjectsBox.merge(temp);
		}
		avgPos = ObjectsBox.getCenter();
		
		if(mCameraNode == NULL)
		{
			mCamera->setPosition(avgPos);
		}
		else
		{
			mCameraNode->setPosition(avgPos);

			float distance = (ObjectsBox.getSize().length() / 2.0) / (Ogre::Math::Tan(mCamera->getFOVy() * 0.5));

			setDistance(distance);
		}
	}
}

void InputHandler::showHelpOverlay()
{
	Ogre::OverlayManager *overlayMgr = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay *hlpOverlay = overlayMgr->getByName("GeneralOverlays/HelpOverlay");
	if(!hlpOverlay) throw OViSEException("Help Overlay not found!");
	if(hlpOverlay->isVisible())
		hlpOverlay->hide();
	else hlpOverlay->show();		
}
