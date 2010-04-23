#include "../ImprovedEventHandling/EventDispatcher.h"

EventDispatcher* EventDispatcher::instance = 0;
EventDispatcher::EventDispatcher() { }
EventDispatcher::~EventDispatcher() { }
EventDispatcher* EventDispatcher::GetSingletonPtr()
{
	if (EventDispatcher::instance == 0) EventDispatcher::instance = new EventDispatcher();
	return EventDispatcher::instance;
}
void EventDispatcher::Send(wxEventType CommandType)
{
	ImprovedEvent event(CommandType, 0);
	this->ProcessEvent(event);
}
void EventDispatcher::Send(wxEventType CommandType, QualifiedName qContextInfo)
{
	ImprovedEvent event(CommandType, 0);
	event.SetContextInfo(qContextInfo);
	this->ProcessEvent(event);
}
void EventDispatcher::Send(wxEventType CommandType, wxVariant vContextData)
{
	ImprovedEvent event(CommandType, 0);
	event.SetContextData(vContextData);
	this->ProcessEvent(event);
}
void EventDispatcher::Send(wxEventType CommandType, QualifiedName qContextInfo, wxVariant vContextData)
{
	ImprovedEvent event(CommandType, 0);
	event.SetContextInfo(qContextInfo);
	event.SetContextData(vContextData);
	this->ProcessEvent(event);
}
