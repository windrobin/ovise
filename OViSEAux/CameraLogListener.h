#pragma once

// Solution's includes
#include "../ImprovedEventHandling/MovableObjectListener.h"
#include "../OViSEAux/Logging.h"

class CameraLogListener :
	public MovableObjectListener
{
public:
	CameraLogListener(void);
	~CameraLogListener(void);
	
	/*
	// Methods of parent events, sealed
	void OnChanged(ImprovedEvent &event);
	void OnConstructed(ImprovedEvent &event);
	void OnDestructed(ImprovedEvent &event);
	void OnRenamed(ImprovedEvent &event);
	void OnSelected(ImprovedEvent &event);
	void OnUnselected(ImprovedEvent &event);
	*/
};