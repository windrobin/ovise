#include "OViSEFrameListener.h"

#include "OViSESceneHandling.h"

OViSEFrameListener::OViSEFrameListener(void)
{
	
}

OViSEFrameListener::~OViSEFrameListener(void)
{
	for(std::map<std::string, OViSECallbackObject*>::iterator it = mCallbackObjects.begin(); it != mCallbackObjects.end(); it++)
	{
		delete it->second;
	}
	mCallbackObjects.clear();
	mCallbackPropsMap.clear();
}

bool OViSEFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	OViSESceneHandling::getSingletonPtr()->updateObjectTitles();
	std::map<std::string, OViSECallbackObject*>::iterator it;
	for(it = mCallbackObjects.begin(); it != mCallbackObjects.end(); it++)
	{
		if(mCallbackPropsMap[it->first].mLastCalled + evt.timeSinceLastFrame * 1000 >= mCallbackPropsMap[it->first].mIntervalMS)
		{
			it->second->executeCommands();
			mCallbackPropsMap[it->first].mLastCalled = 0;
		}
		else
		{
			mCallbackPropsMap[it->first].mLastCalled += evt.timeSinceLastFrame * 1000;
		}
	}
	return true;
}

bool OViSEFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}

void OViSEFrameListener::registerCallbackObject(OViSECallbackObject *cbObject, int intervalMS)
{
	if(mCallbackObjects.find(cbObject->getName()) == mCallbackObjects.end())
	{
		mCallbackObjects[cbObject->getName()] = cbObject;
		CallbackProps tmp;
		tmp.mIntervalMS = intervalMS;
		tmp.mLastCalled = 0;
		mCallbackPropsMap[cbObject->getName()] = tmp;
	}
}

void OViSEFrameListener::unregisterCallbackObject(OViSECallbackObject *cbObject)
{
	std::map<std::string, OViSECallbackObject*>::iterator it = mCallbackObjects.find(cbObject->getName());
	if(it != mCallbackObjects.end())
	{
		mCallbackObjects.erase(it);
	}
	std::map<std::string, CallbackProps>::iterator it2 = mCallbackPropsMap.find(cbObject->getName());
	if(it2 != mCallbackPropsMap.end())
		mCallbackPropsMap.erase(it2);
}