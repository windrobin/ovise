#pragma once

// Solution's includes
#include "../ImprovedEventHandling/EventListener.h"
#include "../OgreMediator/OgreMediator.h"

class OgreObjectListener :
	public EventListener
{
public:
	OgreObjectListener(void);
	~OgreObjectListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();
	virtual wxString	GetListenerTypeName();

	// Methods of events
	virtual void OnChanged(ImprovedEvent &event);
	virtual void OnConstructed(ImprovedEvent &event);
	virtual void OnDestructed(ImprovedEvent &event);
	virtual void OnRenamed(ImprovedEvent &event);
	virtual void OnSelected(ImprovedEvent &event);
	virtual void OnUnselected(ImprovedEvent &event);
};
