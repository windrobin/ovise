#include "../ImprovedEventHandling/SceneNodeListener.h"

SceneNodeListener::SceneNodeListener(void) { }
SceneNodeListener::~SceneNodeListener(void) { }
// Management of listener
void SceneNodeListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	
	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,			ImprovedEventHandler( SceneNodeListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,		ImprovedEventHandler( SceneNodeListener::OnUnselected ),	NULL, this);
	
	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_CHANGED,		ImprovedEventHandler( SceneNodeListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_CONSTRUCTED,	ImprovedEventHandler( SceneNodeListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_DESTRUCTED,		ImprovedEventHandler( SceneNodeListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_RENAMED,		ImprovedEventHandler( SceneNodeListener::OnRenamed ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_MOVED,			ImprovedEventHandler( SceneNodeListener::OnMoved ),			NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_ROTATED,		ImprovedEventHandler( SceneNodeListener::OnRotated ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENENODE_SCALED,			ImprovedEventHandler( SceneNodeListener::OnScaled ),		NULL, this);
}
void SceneNodeListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,		ImprovedEventHandler( SceneNodeListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,		ImprovedEventHandler( SceneNodeListener::OnUnselected ),	NULL, this);
	
	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_CHANGED,		ImprovedEventHandler( SceneNodeListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_CONSTRUCTED,	ImprovedEventHandler( SceneNodeListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_DESTRUCTED,	ImprovedEventHandler( SceneNodeListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_RENAMED,		ImprovedEventHandler( SceneNodeListener::OnRenamed ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_MOVED,		ImprovedEventHandler( SceneNodeListener::OnMoved ),			NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_ROTATED,		ImprovedEventHandler( SceneNodeListener::OnRotated ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_SCALED,		ImprovedEventHandler( SceneNodeListener::OnScaled ),		NULL, this);
}
wxString SceneNodeListener::GetListenerTypeName() { return ToWxString("SceneNodeListener"); }
// Methods of parent events
void SceneNodeListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }
// Methods of events
void SceneNodeListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnMoved(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnRotated(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnScaled(ImprovedEvent &event) { event.Skip(); }