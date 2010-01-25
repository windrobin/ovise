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
	virtual wxString	GetListenerTypeName();

	// Methods of parent events
	virtual void OnSelected(ImprovedEvent &event);
	virtual void OnUnselected(ImprovedEvent &event);

	// Methods of events
	virtual void OnChanged(ImprovedEvent &event);
	virtual void OnConstructed(ImprovedEvent &event);
	virtual void OnDestructed(ImprovedEvent &event);
	virtual void OnRenamed(ImprovedEvent &event);
};