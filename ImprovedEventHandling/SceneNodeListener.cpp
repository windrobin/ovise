#include "../ImprovedEventHandling/SceneNodeListener.h"

SceneNodeListener::SceneNodeListener(void) { EventListenerInterface::SetListenerTypeName(ToWxString("SceneNodeListener")); }
SceneNodeListener::~SceneNodeListener(void) { }
// Management of listener
void SceneNodeListener::StartListening()
{
	// Start listening events
	this->StartListeningTranslated();
	this->StartListeningRotated();
	this->StartListeningScaled();
}
void SceneNodeListener::StopListening()
{
	// Stop listening events
	this->StopListeningTranslated();
	this->StopListeningRotated();
	this->StopListeningScaled();
}
void SceneNodeListener::StartListeningTranslated()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_SCENENODE_TRANSLATED,	ImprovedEventHandler( SceneNodeListener::OnTranslated ), 	NULL, this);
}
void SceneNodeListener::StopListeningTranslated()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_TRANSLATED,	ImprovedEventHandler( SceneNodeListener::OnTranslated ),		NULL, this);
}
void SceneNodeListener::StartListeningRotated()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_SCENENODE_ROTATED,	ImprovedEventHandler( SceneNodeListener::OnRotated ), 	NULL, this);
}
void SceneNodeListener::StopListeningRotated()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_ROTATED,	ImprovedEventHandler( SceneNodeListener::OnRotated ),	NULL, this);
}
void SceneNodeListener::StartListeningScaled()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_SCENENODE_SCALED,	ImprovedEventHandler( SceneNodeListener::OnScaled ), 	NULL, this);
}
void SceneNodeListener::StopListeningScaled()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_SCENENODE_SCALED,	ImprovedEventHandler( SceneNodeListener::OnScaled ),		NULL, this);
}
// Methods of events
void SceneNodeListener::OnTranslated(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnRotated(ImprovedEvent &event) { event.Skip(); }
void SceneNodeListener::OnScaled(ImprovedEvent &event) { event.Skip(); }