#include "../ImprovedEventHandling/LightListener.h"

LightListener::LightListener(void) { }
LightListener::~LightListener(void) { }
// Management of listener
void LightListener::StartListening()
{
	/*
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,		ImprovedEventHandler( LightListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( LightListener::OnUnselected ),		NULL, this);

	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_LIGHT_CHANGED,		ImprovedEventHandler( LightListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_LIGHT_CONSTRUCTED,	ImprovedEventHandler( LightListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_LIGHT_DESTRUCTED,		ImprovedEventHandler( LightListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_LIGHT_RENAMED,		ImprovedEventHandler( LightListener::OnRenamed ),		NULL, this);
	*/
}
void LightListener::StopListening()
{
	/*
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,	ImprovedEventHandler( LightListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( LightListener::OnUnselected ),		NULL, this);

	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_LIGHT_CHANGED,		ImprovedEventHandler( LightListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_LIGHT_CONSTRUCTED,	ImprovedEventHandler( LightListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_LIGHT_DESTRUCTED,	ImprovedEventHandler( LightListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_LIGHT_RENAMED,		ImprovedEventHandler( LightListener::OnRenamed ),		NULL, this);
	*/
}
//wxString LightListener::GetListenerTypeName() { return ToWxString("LightListener"); }
// Methods of events
