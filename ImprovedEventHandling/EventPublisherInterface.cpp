#include "../ImprovedEventHandling/EventPublisherInterface.h"

EventPublisherInterface::EventPublisherInterface(void) { }
EventPublisherInterface::~EventPublisherInterface(void) { }
bool EventPublisherInterface::Publish(wxEventType CommandType)
{
	if (this->mEventBlacklist.Index((int)CommandType) == wxNOT_FOUND)
	{
		this->mEventBlacklist.Add((int)CommandType);
		EventDispatcher::GetSingletonPtr()->Send(CommandType);
		this->mEventBlacklist.Remove((int)CommandType);
		return true;
	}
	else return false;
}
bool EventPublisherInterface::Publish(wxEventType CommandType, QualifiedName qContextInfo)
{
	if (this->mEventBlacklist.Index((int)CommandType) == wxNOT_FOUND)
	{
		this->mEventBlacklist.Add((int)CommandType);
		EventDispatcher::GetSingletonPtr()->Send(CommandType, qContextInfo);
		this->mEventBlacklist.Remove((int)CommandType);
		return true;
	}
	else return false;
}
bool EventPublisherInterface::Publish(wxEventType CommandType, wxVariant vContextData)
{
	if (this->mEventBlacklist.Index((int)CommandType) == wxNOT_FOUND)
	{
		this->mEventBlacklist.Add((int)CommandType);
		EventDispatcher::GetSingletonPtr()->Send(CommandType, vContextData);
		this->mEventBlacklist.Remove((int)CommandType);
		return true;
	}
	else return false;
}
bool EventPublisherInterface::Publish(wxEventType CommandType, QualifiedName qContextInfo, wxVariant vContextData)
{
	if (this->mEventBlacklist.Index((int)CommandType) == wxNOT_FOUND)
	{
		this->mEventBlacklist.Add((int)CommandType);
		EventDispatcher::GetSingletonPtr()->Send(CommandType, qContextInfo, vContextData);
		this->mEventBlacklist.Remove((int)CommandType);
		return true;
	}
	else return false;
}