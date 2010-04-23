#include "../ImprovedEventHandling/OgreObjectListener.h"

OgreObjectListener::OgreObjectListener(void) { EventListenerInterface::SetListenerTypeName(ToWxString("OgreObjectListener")); }
OgreObjectListener::~OgreObjectListener(void) { }
// Management of listener
void OgreObjectListener::StartListening()
{
	// Start listening events
	this->StartListeningChanged();
	this->StartListeningConstructed();
	this->StartListeningDestructed();
	this->StartListeningRenamed();
}
void OgreObjectListener::StopListening()
{
	// Stop listening events
	this->StopListeningChanged();
	this->StopListeningConstructed();
	this->StopListeningDestructed();
	this->StopListeningRenamed();
}
void OgreObjectListener::StartListeningChanged()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_CHANGED,	ImprovedEventHandler( OgreObjectListener::OnChanged ),		NULL, this);
}
void OgreObjectListener::StopListeningChanged()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_CHANGED,	ImprovedEventHandler( OgreObjectListener::OnChanged ),		NULL, this);
}
void OgreObjectListener::StartListeningConstructed()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_CONSTRUCTED,ImprovedEventHandler( OgreObjectListener::OnConstructed ),	NULL, this);
}
void OgreObjectListener::StopListeningConstructed()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_CONSTRUCTED,ImprovedEventHandler( OgreObjectListener::OnConstructed ),	NULL, this);
}
void OgreObjectListener::StartListeningDestructed()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_DESTRUCTED, ImprovedEventHandler( OgreObjectListener::OnDestructed ),	NULL, this);
}
void OgreObjectListener::StopListeningDestructed()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_DESTRUCTED, ImprovedEventHandler( OgreObjectListener::OnDestructed ),	NULL, this);
}
void OgreObjectListener::StartListeningRenamed()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Connect(	EVT_OGRE_RENAMED,	ImprovedEventHandler( OgreObjectListener::OnRenamed ),		NULL, this);
}
void OgreObjectListener::StopListeningRenamed()
{	
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();
	eventDispatcher->Disconnect(EVT_OGRE_RENAMED,	ImprovedEventHandler( OgreObjectListener::OnRenamed ),		NULL, this);
}

// Methods of events
void OgreObjectListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void OgreObjectListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }