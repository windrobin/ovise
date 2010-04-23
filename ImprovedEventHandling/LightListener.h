#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

class LightListener :
	public OgreObjectListener
{
public:
	LightListener(void);
	~LightListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();

	// Methods of events
};