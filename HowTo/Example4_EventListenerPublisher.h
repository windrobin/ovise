/********************************************************************************
 * Name:      Example4_EventListenerPublisher.h									*
 * Purpose:   This example discribes, how to create a new class, which merges	*
 *			  the abilities of listener and a publisher.						*
 * Author:    Henning Renartz													*
 * Created:   2010-04-28														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// INTRODUCTION:  o This example shows how to create a new class - able to publish
//					events and listening to them too.

// STEP 1:	Include class EventListenerInterface.
#include "../ImprovedEventHandling/EventListenerInterface.h"

// STEP 2:	Include class EventPublisherInterface.
#include "../ImprovedEventHandling/EventPublisherInterface.h"

// STEP 3: Inherit from them...
class MyPublishingListener4 :
	public EventListenerInterface,
	public EventPublisherInterface

{
public:
	MyPublishingListener4(void);
	~MyPublishingListener4(void);
};

// STEP 4: That'S it. This technique allows a wonderful 'magic' way to implement a
//		   event-handling system :-)