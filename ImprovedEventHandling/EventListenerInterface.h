/********************************************************************************
 * Name:      EventListenerInterface.h											*
 * Purpose:   An interface-class, defining basic methods 						*
 *			  "StartListening" and "StopListening".								*
 * Created:   2010-01-11														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Solution's includes
#include "../ImprovedEventHandling/ImprovedEvent.h"
#include "../ImprovedEventHandling/ImprovedEventTypes.h"
#include "../ImprovedEventHandling/EventListenerInterface.h"
#include "../ImprovedEventHandling/EventDispatcher.h"
#include "../OViSEAux/StringConverter.h"

class EventListenerInterface :
	public wxEvtHandler
{
protected:
			wxString	mListenerTypeName;
public:
						EventListenerInterface();
						~EventListenerInterface();

	// Management of listener
	virtual wxString	GetListenerTypeName();
	virtual void		SetListenerTypeName(wxString ListenerTypeName);

	virtual void		StartListening();
	virtual void		StopListening();
	
			void		StartListeningDefault();
			void		StopListeningDefault();

	// Methods of events
	virtual void		OnDefault(ImprovedEvent &event);
};
