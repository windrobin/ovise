#include "../ImprovedEventHandling/ImprovedEvent.h"

ImprovedEvent::ImprovedEvent(wxEventType CommandType, int ID)
	:  wxCommandEvent(CommandType, ID)
{
	this->vContextData.MakeNull();
}
ImprovedEvent::ImprovedEvent(const ImprovedEvent& EventToCopy)
	: wxCommandEvent(EventToCopy)
{
	qContextInfo = EventToCopy.GetContextInfo();
}
ImprovedEvent::~ImprovedEvent(void) { }
wxEvent* ImprovedEvent::Clone() const
{
	ImprovedEvent* ClonedImprovedEvent = new ImprovedEvent(*this);
	ClonedImprovedEvent->SetContextInfo(qContextInfo);
	return ClonedImprovedEvent;
}
void ImprovedEvent::SetContextInfo(QualifiedName qContextInfo) { this->qContextInfo = qContextInfo; }
QualifiedName ImprovedEvent::GetContextInfo() const { return this->qContextInfo; }
void ImprovedEvent::SetContextData(wxVariant vContextData) { this->vContextData = vContextData; }
wxVariant ImprovedEvent::GetContextData() const { return this->vContextData; }
