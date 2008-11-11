#include "OViSEFrameListener.h"

OViSEFrameListener::OViSEFrameListener(void)
{
	mSceneHandler = OViSESceneHandling::getSingletonPtr();
}

OViSEFrameListener::~OViSEFrameListener(void)
{
}

bool OViSEFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	mSceneHandler->updateObjectTitles();
	return true;
}

bool OViSEFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}