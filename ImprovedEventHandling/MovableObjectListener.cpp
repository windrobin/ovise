#include "../ImprovedEventHandling/MovableObjectListener.h"

MovableObjectListener::MovableObjectListener(void) { }
MovableObjectListener::~MovableObjectListener(void) { }
// Management of listener
void MovableObjectListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,				ImprovedEventHandler( MovableObjectListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,			ImprovedEventHandler( MovableObjectListener::OnUnselected ),		NULL, this);

	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_MOVABLEOBJECT_CHANGED,		ImprovedEventHandler( MovableObjectListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_MOVABLEOBJECT_CONSTRUCTED,	ImprovedEventHandler( MovableObjectListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_MOVABLEOBJECT_DESTRUCTED,		ImprovedEventHandler( MovableObjectListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_MOVABLEOBJECT_RENAMED,		ImprovedEventHandler( MovableObjectListener::OnRenamed ),		NULL, this);
}
void MovableObjectListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,			ImprovedEventHandler( MovableObjectListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,			ImprovedEventHandler( MovableObjectListener::OnUnselected ),		NULL, this);

	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_CHANGED,		ImprovedEventHandler( MovableObjectListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_CONSTRUCTED,	ImprovedEventHandler( MovableObjectListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_DESTRUCTED,	ImprovedEventHandler( MovableObjectListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_MOVABLEOBJECT_RENAMED,		ImprovedEventHandler( MovableObjectListener::OnRenamed ),		NULL, this);
}
wxString MovableObjectListener::GetListenerTypeName() { return ToWxString("MovableObjectListener"); }
// Methods of parent events
void MovableObjectListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void MovableObjectListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }
// Methods of events
void MovableObjectListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void MovableObjectListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void MovableObjectListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void MovableObjectListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }