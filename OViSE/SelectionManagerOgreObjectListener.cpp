#include "../OViSE/SelectionManagerOgreObjectListener.h"

SelectionManagerOgreObjectListener::SelectionManagerOgreObjectListener() {  }
SelectionManagerOgreObjectListener::~SelectionManagerOgreObjectListener(void) { }
// Management of listener, sealed
void SelectionManagerOgreObjectListener::StartListening() { OgreObjectListener::StartListening(); }
wxString SelectionManagerOgreObjectListener::GetListenerTypeName() { return ToWxString("SelectionManagerOgreObjectListener"); }
// Methods of parent events, sealed
void SelectionManagerOgreObjectListener::OnChanged(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerOgreObjectListener::OnConstructed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerOgreObjectListener::OnDestructed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerOgreObjectListener::OnRenamed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerOgreObjectListener::OnSelected(ImprovedEvent &event)
{
	// Apply SelectItem()
	QualifiedName qName = event.GetContextInfo();
	if (!SelectionManager::getSingletonPtr()->Selection.Contains(qName))
			SelectionManager::getSingletonPtr()->Selection.Add(qName);
	SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection();

	// Forwarding event
	event.Skip();
}
void SelectionManagerOgreObjectListener::OnUnselected(ImprovedEvent &event)
{
	// Apply UnselectItem()
	QualifiedName qName = event.GetContextInfo();
	SelectionManager::getSingletonPtr()->Selection.Remove(qName);
	SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection();

	// Forwarding event
	event.Skip();
}