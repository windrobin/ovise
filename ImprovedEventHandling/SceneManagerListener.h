#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

class SceneManagerListener :
	public OgreObjectListener
{
public:
	SceneManagerListener(void);
	~SceneManagerListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();

	// Methods of events
};
