#pragma once
#include <OgreFrameListener.h>
#include "OViSESceneHandling.h"


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

	virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameEnded(const Ogre::FrameEvent &evt);

private:
	OViSESceneHandling *mSceneHandler;
};
