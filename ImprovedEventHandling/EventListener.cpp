#include "../ImprovedEventHandling/EventListener.h"

EventListener::EventListener(void) { }
EventListener::~EventListener(void) { }
// Management of listener
void EventListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(EVT_DEFAULT, ImprovedEventHandler( EventListener::OnDefault ), NULL, eventDispatcher);
}
void EventListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_DEFAULT, ImprovedEventHandler( EventListener::OnDefault ), NULL, eventDispatcher);
}
wxString EventListener::GetListenerTypeName() { return ToWxString("DefaultEventListener"); }
// Methods of events
void EventListener::OnDefault(ImprovedEvent &event)
{
	// Do nothing!
	this->GetListenerTypeName(); // Debug-Activity

	// Skip event
	event.Skip();
}

