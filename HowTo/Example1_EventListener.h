/********************************************************************************
 * Name:      Example1_EventListener.h											*
 * Purpose:   This example discribes, how to create a new listener in few steps.*
 * Author:    Henning Renartz													*
 * Created:   2010-04-28														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

// INTRODUCTION:  o Welcome! This little example-class discribes how you can create
//					a basic listener by inherit from EventListenerInterface.
//				  o It shows how to use the listener in code of other methods.
//				  o When some special methods are overwritten, take a additional look
//					into the EventListner_Example1.cpp

#pragma once

// REMEBER: If you want to know, what events can occure_ take a look into 
//			ImprovedEventTypes.h

// STEP 1:	Include class EventListenerInterface. It only listen to events
//			of type EVT_DEFAULT.
#include "../ImprovedEventHandling/EventListenerInterface.h"

// STEP 2: Inherit from it...
class MyExampleListener1 : EventListenerInterface
{
public:
	MyExampleListener1(void);
	~MyExampleListener1(void);

	// STEP 3:	Now your class owns the virtual "OnDefault"-method.
	//			It only skips all incoming EVT_DEFAULT without doing anything.
	//			Optional, you can easily change its funktionality by overwriting it:
	void OnDefault(ImprovedEvent &event);
};

// STEP 4: USAGE
// Ah, that's easy too. Take a look.
//
// void SomeUnknowMethod()
// {
//		// Instanciate and initialize object
//		MyExampleListener1 myListener1;
//
//		// Start and stop listening a specific event. Here "EVT_DEFAULT".
//		myListener1.StartListeningDefault();
//		myListener1.StopListeningDefault();
// }

// STEP 5:	Okay, that's all here. If "OnDefault" is overwritten
//			step forward to "EventListner_Example1.cpp".