#pragma once

// Solution's includes
#include "../ImprovedEventHandling/ImprovedEvent.h"
#include "../ImprovedEventHandling/ImprovedEventTypes.h"
#include "../ImprovedEventHandling/EventListenerInterface.h"
#include "../ImprovedEventHandling/EventDispatcher.h"
#include "../OViSEAux/StringConverter.h"

class EventListener :
	public EventListenerInterface,
	protected wxEvtHandler
{
public:
	EventListener();
	~EventListener();

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();
	virtual wxString	GetListenerTypeName();

	// Methods of events
	virtual void OnDefault(ImprovedEvent &event);
};
