#include "Example2_EventListener.h"

// STEP 6:	In .cpp you have to overwrite "StartListening()" and "StopListening()"
void MyExampleListener2::StartListening()
{
	// STEP 6.1: You can implement the 'big button' by calling each special
	//			 start/stop method. That's usefull, if you don't want to listen to
	//			 all events.
	this->StartListeningChanged();
	this->StartListeningConstructed();
	this->StartListeningDestructed();
	//this->StartListeningRenamed(); // <- don't listen to this event
	//this->StartListeningSelected(); // <- don't listen to this event
	this->StartListeningUnselected();

	// STEP 6.2: ...or by calling "StartListening()" of it's parents.
	OgreObjectListener::StartListening();
	MovableObjectListener::StartListening();
}

void MyExampleListener2::StopListening()
{
	OgreObjectListener::StopListening();
	MovableObjectListener::StopListening();
}

//STEP 7:	If you want to enable 'autostart' and 'autostop' functionality,
//			call "StartListening()" and "StopListening()" in de-/constructor
MyExampleListener2::MyExampleListener2(void)
{
	this->StartListening();
}

MyExampleListener2::~MyExampleListener2(void)
{
	this->StopListening();
}
