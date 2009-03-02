#pragma once
#include <OgreFrameListener.h>
#include <map>
#include "OViSECallbackObject.h"


/** This class is a callback for the render routine.
 * The frame listeners methods get called before and after every frame rendering.
 * It can be used to alter the scene inbetween frames.
 */
class OViSEFrameListener :
	public Ogre::FrameListener
{
public:
	OViSEFrameListener(void);
	~OViSEFrameListener(void);

	/// Registers a callback object with this framelistener.
	/// @param cbObject CallbackObject that contains code to run
	/// @param intervalMS Interval in miliseconds in which the callback code should be called
	void registerCallbackObject(OViSECallbackObject* cbObject, int intervalMS);
	/// Removes callback object from registered objects list.
	void unregisterCallbackObject(OViSECallbackObject *cbObject);

protected:
	virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameEnded(const Ogre::FrameEvent &evt);

	struct CallbackProps
	{
		/// Time that should pass between consecutive calls
		int mIntervalMS;
		/// Time elapsed since last call
		int mLastCalled;
	};

private:
	std::map<std::string, OViSECallbackObject*> mCallbackObjects;
	std::map<std::string, CallbackProps> mCallbackPropsMap;
};
