#include "../ImprovedEventHandling/OgreObjectListener.h"

OgreObjectListener::OgreObjectListener(void) { }
OgreObjectListener::~OgreObjectListener(void) { }
// Management of listener
void OgreObjectListener::StartListening()
{
	// Start listening parents events
	EventListener::StartListening();

	// Start listening events
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(EVT_OGRE_OBJECT_CHANGED,		ImprovedEventHandler( OgreObjectListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_CONSTRUCTED,	ImprovedEventHandler( OgreObjectListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_DESTRUCTED,	ImprovedEventHandler( OgreObjectListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_RENAMED,		ImprovedEventHandler( OgreObjectListener::OnRenamed ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,		ImprovedEventHandler( OgreObjectListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( OgreObjectListener::OnUnselected ),	NULL, this);
}
void OgreObjectListener::StopListening()
{
	// Stop listening parents events
	EventListener::StopListening();

	// Stop listening events
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_CHANGED,	ImprovedEventHandler( OgreObjectListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_CONSTRUCTED,ImprovedEventHandler( OgreObjectListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_DESTRUCTED, ImprovedEventHandler( OgreObjectListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_RENAMED,	ImprovedEventHandler( OgreObjectListener::OnRenamed ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,	ImprovedEventHandler( OgreObjectListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( OgreObjectListener::OnUnselected ),	NULL, this);
}
wxString OgreObjectListener::GetListenerTypeName() { return ToWxString("OgreObjectListener"); }
// Methods of events
void OgreObjectListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }