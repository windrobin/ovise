/********************************************************************************
 * Name:      EventDispatcher.h													*
 * Purpose:   Idea of this class is, to create a central singleton-object,		*
 *			  which hosts all possible events, occuring in OgreMediator context.*
 *			  Events can be connected and released from everywhere simple and	*
 *			  direcly.															*
 *			  Additional, there is more advantage: events can be dispatched		*
 *			  with a central event-logic, hidden behind public access.			*
 *			  At last, this is a good way to implement an better, intuitive		*
 *			  event-API by hinding these #<censord>#..ing macros. Easy to		*
 *			  handle for newbies - and advanced users, too. 					*
 * Created:   2009-12-18														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Include WX
#include <wx/event.h>
#include <wx/variant.h>

// Solution's includes
#include "../ImprovedEventHandling/ImprovedEvent.h"

class EventDispatcher :
	public wxEvtHandler
{
private:
	// De- & Constructors
	EventDispatcher(void);

	// Singleton
	static EventDispatcher* instance;

public:
	// De- & Constructors
	~EventDispatcher(void);

	// Singleton
	static EventDispatcher*	GetSingletonPtr();

	// Sending events with public methods
	void Send(wxEventType CommandType);
	void Send(wxEventType CommandType, QualifiedName qContextInfo);
	void Send(wxEventType CommandType, wxVariant vContextData);
	void Send(wxEventType CommandType, QualifiedName qContextInfo, wxVariant vContextData);
};
