#include "OViSEFrameListener.h"

OViSEFrameListener::OViSEFrameListener(void)
{
	mSceneHandler = OViSESceneHandling::getSingletonPtr();
}

OViSEFrameListener::~OViSEFrameListener(void)
{
	for(std::map<std::string, OViSECallbackObject*>::iterator it = mCallbackObjects.begin(); it != mCallbackObjects.end(); it++)
	{
		delete it->second;
	}
	mCallbackObjects.clear();
}

bool OViSEFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	mSceneHandler->updateObjectTitles();
	std::map<std::string, OViSECallbackObject*>::iterator it;
	for(it = mCallbackObjects.begin(); it != mCallbackObjects.end(); it++)
		it->second->executeCommands();
	return true;
}

bool OViSEFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}

void OViSEFrameListener::registerCallbackObject(OViSECallbackObject *cbObject)
{
	if(mCallbackObjects.find(cbObject->getName()) == mCallbackObjects.end())
		mCallbackObjects[cbObject->getName()] = cbObject;
}

void OViSEFrameListener::unregisterCallbackObject(OViSECallbackObject *cbObject)
{
	std::map<std::string, OViSECallbackObject*>::iterator it = mCallbackObjects.find(cbObject->getName());
	if(it != mCallbackObjects.end())
		mCallbackObjects.erase(it);
}