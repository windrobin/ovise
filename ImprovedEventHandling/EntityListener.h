#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

class EntityListener :
	public OgreObjectListener
{
public:
	EntityListener(void);
	~EntityListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();

	// Methods of events
};