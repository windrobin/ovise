/********************************************************************************
 * Name:      Example3_EventListener.h											*
 * Purpose:   This example discribes, how to create a new publisher in few		*
 *			  steps.															*
 * Author:    Henning Renartz													*
 * Created:   2010-04-28														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// STEP 1:	Include class EventPublisherInterface.
#include "../ImprovedEventHandling/EventPublisherInterface.h"

// STEP 2: Inherit from it...
class MyExamplePublisher3 :
	public EventPublisherInterface
{
public:
	MyExamplePublisher3(void);
	~MyExamplePublisher3(void);
};


// STEP 3: USAGE
// That's it. Now use it...
//
// void SomeUnknowMethod()
// {
//		// Instanciate and initialize object
//		MyExamplePublisher3 myPublisher3;
//
//		// Start and stop listening a specific event. Here "EVT_DEFAULT".
//		myPublisher3.Publish(
// }