/********************************************************************************
 * Name:      Example2_EventListener.h											*
 * Purpose:   This example discribes, how to create a new listener which        *
 *			  inherits from multiple listeners to automatically handle all of   *
 *			  parent's events. Also this example shows how to start/stop a		*
 *			  collection of specialized starts and stops - and that				*
 *			  when the new listener is (de)constructed.							*
 * Author:    Henning Renartz													*
 * Created:   2010-04-28														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// REMEBER: If you want to know, what events can occure_ take a look into 
//			ImprovedEventTypes.h

// STEP 1:	Include classes OgreObjectListener and MovableObjectListener.
//			They listen to following events:
//			o EVT_OGRE_CHANGED, EVT_OGRE_CONSTRUCTED, EVT_OGRE_DESTRUCTED, EVT_OGRE_RENAMED
//			o EVT_OGRE_MOVABLEOBJECT_SELECTED, EVT_OGRE_MOVABLEOBJECT_UNSELECTED

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"
#include "../ImprovedEventHandling/MovableObjectListener.h"

// STEP 2: Inherit from them...
class MyExampleListener2 :
	public OgreObjectListener,
	public MovableObjectListener
{
public:
	// STEP 3:	Now your class owns the vitual methods
	//			"StartListening()" and "StopListening()". If you want
	//			to create 'big buttons', starting and stoping a collection
	//			of special starts and stops - that's the correct place:
	void StartListening();
	void StopListening();

	// STEP 4: To enable an 'autostart' or 'autostop', "StartListening()"
	//		  and "StopListening()"  have to be called in de-/constructor.
	MyExampleListener2(void);
	~MyExampleListener2(void);
};

// STEP 5: USAGE
//
// void SomeUnknowMethod()
// {
//		// Instanciate and initialize object
//		MyExampleListener2 myListener2;
//
//		// Start listening:
//		myListener2.StartListeningChanged();
//		myListener2.StartListeningRenamed();
//		myListener2.StartListeningConstructed();
//		myListener2.StartListeningDestructed();
//		myListener2.StartListeningSelected();
//		myListener2.StartListeningUnselected();
//		//... that's not quite elegant :-(
//
//		// Better use the 'big button': start listening ALL events. :-)
//		myListener2.StartListening();
// }

// STEP 6:	Okay, that's all here. Step forward to "EventListner_Example2.cpp" and
//			take a look at "StartListening()" and "StopListening()".
