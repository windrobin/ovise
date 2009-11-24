#include "FrameListener.h"
#include "SceneHandling.h"

CustomFrameListener::CustomFrameListener(void)
{
	
}

CustomFrameListener::~CustomFrameListener(void)
{
	for(std::map<std::string, CallbackObject*>::iterator it = mCallbackObjects.begin(); it != mCallbackObjects.end(); it++)
	{
		delete it->second;
	}
	mCallbackObjects.clear();
	mCallbackPropsMap.clear();
}

bool CustomFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	SceneHandling::getSingletonPtr()->updateObjectTitles();
	if(mProcessFrameEvents)
	{
		std::map<std::string, CallbackObject*>::iterator it;
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
	}
	return true;
}

bool CustomFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}

void CustomFrameListener::registerCallbackObject(CallbackObject *cbObject, int intervalMS)
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

void CustomFrameListener::unregisterCallbackObject(CallbackObject *cbObject)
{
	std::map<std::string, CallbackObject*>::iterator it = mCallbackObjects.find(cbObject->getName());
	if(it != mCallbackObjects.end())
	{
		mCallbackObjects.erase(it);
	}
	std::map<std::string, CallbackProps>::iterator it2 = mCallbackPropsMap.find(cbObject->getName());
	if(it2 != mCallbackPropsMap.end())
		mCallbackPropsMap.erase(it2);
}

bool CustomFrameListener::isFrameEventsProcessed()
{
	return mProcessFrameEvents;
}

void CustomFrameListener::setFrameEventsProcessed(bool frameEventsProcessed)
{
	mProcessFrameEvents = frameEventsProcessed;
}