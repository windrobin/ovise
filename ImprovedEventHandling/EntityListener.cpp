#include "../ImprovedEventHandling/EntityListener.h"

EntityListener::EntityListener(void) { }
EntityListener::~EntityListener(void) { }
// Management of listener
void EntityListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,		ImprovedEventHandler( EntityListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( EntityListener::OnUnselected ),		NULL, this);

	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_ENTITY_CHANGED,		ImprovedEventHandler( EntityListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_ENTITY_CONSTRUCTED,	ImprovedEventHandler( EntityListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_ENTITY_DESTRUCTED,	ImprovedEventHandler( EntityListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_ENTITY_RENAMED,		ImprovedEventHandler( EntityListener::OnRenamed ),		NULL, this);
}
void EntityListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,	ImprovedEventHandler( EntityListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( EntityListener::OnUnselected ),		NULL, this);

	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_ENTITY_CHANGED,	ImprovedEventHandler( EntityListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_ENTITY_CONSTRUCTED,ImprovedEventHandler( EntityListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_ENTITY_DESTRUCTED, ImprovedEventHandler( EntityListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_ENTITY_RENAMED,	ImprovedEventHandler( EntityListener::OnRenamed ),		NULL, this);
}
wxString EntityListener::GetListenerTypeName() { return ToWxString("EntityListener"); }
// Methods of parent events
void EntityListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void EntityListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }
// Methods of events
void EntityListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void EntityListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void EntityListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void EntityListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }