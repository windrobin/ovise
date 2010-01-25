#include "../ImprovedEventHandling/SceneManagerListener.h"

SceneManagerListener::SceneManagerListener(void) { }
SceneManagerListener::~SceneManagerListener(void) { }
// Management of listener
void SceneManagerListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,				ImprovedEventHandler( SceneManagerListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,			ImprovedEventHandler( SceneManagerListener::OnUnselected ),		NULL, this);
	
	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_SCENEMANAGER_CHANGED,			ImprovedEventHandler( SceneManagerListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENEMANAGER_CONSTRUCTED,		ImprovedEventHandler( SceneManagerListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENEMANAGER_DESTRUCTED,		ImprovedEventHandler( SceneManagerListener::OnDestructed ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_SCENEMANAGER_RENAMED,			ImprovedEventHandler( SceneManagerListener::OnRenamed ),		NULL, this);

}
void SceneManagerListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,			ImprovedEventHandler( SceneManagerListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,			ImprovedEventHandler( SceneManagerListener::OnUnselected ),		NULL, this);
	
	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_SCENEMANAGER_CHANGED,		ImprovedEventHandler( SceneManagerListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENEMANAGER_CONSTRUCTED,	ImprovedEventHandler( SceneManagerListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENEMANAGER_DESTRUCTED,	ImprovedEventHandler( SceneManagerListener::OnDestructed ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_SCENEMANAGER_RENAMED,		ImprovedEventHandler( SceneManagerListener::OnRenamed ),		NULL, this);
}
wxString SceneManagerListener::GetListenerTypeName() { return ToWxString("SceneManagerListener"); }
// Methods of parent events
void SceneManagerListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void SceneManagerListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }
// Methods of events
void SceneManagerListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void SceneManagerListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void SceneManagerListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void SceneManagerListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }