#include "Example1_EventListener.h"

MyExampleListener1::MyExampleListener1(void) { }
MyExampleListener1::~MyExampleListener1(void) { }

// STEP 6:	In .cpp you have to define, the new functionality of "OnDefault"

void MyExampleListener1::OnDefault(ImprovedEvent &event)
{
	// IMPORTANT: Do not call the parent's OnDefault, exspecially at begin of method!
	// WHY:		  EventListenerInterface::OnDefault(...) calls event.Skip().
	// EFFECT:	  STEP 7 will never be reached.

	// STEP 7:	  Write some usefull code...
	this->GetListenerTypeName(); // That's not usefull, but this is a example ;-)

	// STEP 8:	  Calling "Skip" ends event-handling and starts propagation to
	//			  other listeners.
	event.Skip();
}
