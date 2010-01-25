/********************************************************************************
 * Name:      EventListenerInterface.h											*
 * Purpose:   An interface-class, defining the abstract-methods					*
 *			  "RegisterListener" and "UnregisterListener".						*
 * Created:   2010-01-11														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/
#pragma once

#include "../ImprovedEventHandling/EventDispatcher.h"

class EventListenerInterface
{
public:
	EventListenerInterface() { }

	virtual void		StartListening() = 0;
	virtual void		StopListening() = 0;
	virtual wxString	GetListenerTypeName() = 0;
};
