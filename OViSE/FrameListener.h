#ifndef FRAME_LISTENER_H
#define FRAME_LISTENER_H

#include "CallbackObject.h"
#include <OgreFrameListener.h>
#include <map>

/** This class is a callback for the render routine.
 * The frame listeners methods get called before and after every frame rendering.
 * It can be used to alter the scene inbetween frames.
 */
class CustomFrameListener :
	public Ogre::FrameListener
{
public:
	CustomFrameListener(void);
	~CustomFrameListener(void);

	/// Registers a callback object with this framelistener.
	/// @param cbObject CallbackObject that contains code to run
	/// @param intervalMS Interval in miliseconds in which the callback code should be called
	void registerCallbackObject(CallbackObject* cbObject, int intervalMS);
	/// Removes callback object from registered objects list.
	void unregisterCallbackObject(CallbackObject *cbObject);

	/// Check if registered listeners' commands are executed
	bool isFrameEventsProcessed();
	/// Set if registered listeners' commands should be executed
	void setFrameEventsProcessed(bool frameEventsProcessed = true);

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
	std::map<std::string, CallbackObject*> mCallbackObjects;
	std::map<std::string, CallbackProps> mCallbackPropsMap;

	bool mProcessFrameEvents;
};
#endif //FRAME_LISTENER_H