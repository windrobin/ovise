#include "../ImprovedEventHandling/EventListenerInterface.h"

EventListenerInterface::EventListenerInterface(void) { this->SetListenerTypeName(ToWxString("DefaultEventListener")); }
EventListenerInterface::~EventListenerInterface(void) { }
// Management of listener
wxString EventListenerInterface::GetListenerTypeName() { return this->mListenerTypeName; }
void EventListenerInterface::SetListenerTypeName(wxString ListenerTypeName) { this->mListenerTypeName = ListenerTypeName; }
void EventListenerInterface::StartListening() { this->StartListeningDefault(); }
void EventListenerInterface::StopListening() { this->StopListeningDefault(); }
void EventListenerInterface::StartListeningDefault()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(EVT_DEFAULT, ImprovedEventHandler( EventListenerInterface::OnDefault ), NULL, eventDispatcher);
}
void EventListenerInterface::StopListeningDefault()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_DEFAULT, ImprovedEventHandler( EventListenerInterface::OnDefault ), NULL, eventDispatcher);
}
// Methods of events
void EventListenerInterface::OnDefault(ImprovedEvent &event)
{
	// Do nothing!
	this->GetListenerTypeName(); // Debug-Activity

	// Skip event
	event.Skip();
}
