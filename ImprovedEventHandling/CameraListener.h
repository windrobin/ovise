#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

class CameraListener :
	public OgreObjectListener
{
public:
	CameraListener(void);
	~CameraListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();

	// Methods of events
};