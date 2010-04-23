#include "../ImprovedEventHandling/MovableObjectListener.h"

MovableObjectListener::MovableObjectListener(void) { EventListenerInterface::SetListenerTypeName(ToWxString("MovableObjectListener")); }
MovableObjectListener::~MovableObjectListener(void) { }
// Management of listener
void MovableObjectListener::StartListening()
{
	// Start listening events
	this->StartListeningSelected();
	this->StartListeningUnselected();	
}
void MovableObjectListener::StopListening()
{
	// Stop listening events
	this->StopListeningSelected();
	this->StopListeningUnselected();
}
void MovableObjectListener::StartListeningSelected()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_MOVABLEOBJECT_SELECTED,	ImprovedEventHandler( MovableObjectListener::OnSelected ),	NULL, this);
}
void MovableObjectListener::StopListeningSelected()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_SELECTED,	ImprovedEventHandler( MovableObjectListener::OnSelected ),	NULL, this);
}
void MovableObjectListener::StartListeningUnselected()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_MOVABLEOBJECT_UNSELECTED,	ImprovedEventHandler( MovableObjectListener::OnUnselected ),NULL, this);
}
void MovableObjectListener::StopListeningUnselected()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_UNSELECTED,	ImprovedEventHandler( MovableObjectListener::OnUnselected ),NULL, this);
}
// Methods of events
void MovableObjectListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void MovableObjectListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }