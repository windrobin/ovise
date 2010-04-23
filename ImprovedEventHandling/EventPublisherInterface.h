#pragma once

// Include WX
#include <wx/event.h>
#include <wx/variant.h>
#include <wx/dynarray.h>

// Solution's includes
#include "../ImprovedEventHandling/ImprovedEventTypes.h"
#include "../ImprovedEventHandling/ImprovedEvent.h"
#include "../ImprovedEventHandling/EventDispatcher.h"

class EventPublisherInterface
{
protected:
	wxArrayInt mEventBlacklist;
public:
	EventPublisherInterface(void);
	~EventPublisherInterface(void);

	// Publish events with default methods // For easy access
	bool Publish(wxEventType CommandType);
	bool Publish(wxEventType CommandType, QualifiedName qContextInfo);
	bool Publish(wxEventType CommandType, wxVariant vContextData);
	bool Publish(wxEventType CommandType, QualifiedName qContextInfo, wxVariant vContextData);
};
