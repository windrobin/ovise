#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

#include "../ImprovedEventHandling/MovableObjectListener.h"
#include "../ImprovedEventHandling/SceneNodeListener.h"

class MultiListener :
	public OgreObjectListener,
	public MovableObjectListener,
	public SceneNodeListener
{
public:
					MultiListener(void);
					~MultiListener(void);

	// Management of listener
	virtual void	StartListening();
	virtual void	StopListening();
};
