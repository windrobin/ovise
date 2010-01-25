#include "../ImprovedEventHandling/CameraListener.h"

CameraListener::CameraListener(void) { }
CameraListener::~CameraListener(void) { }
// Management of listener
void CameraListener::StartListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Start listening parents events
	eventDispatcher->Connect(EVT_OGRE_OBJECT_SELECTED,		ImprovedEventHandler( CameraListener::OnSelected ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( CameraListener::OnUnselected ),		NULL, this);
	
	// Start listening events
	eventDispatcher->Connect(EVT_OGRE_CAMERA_CHANGED,		ImprovedEventHandler( CameraListener::OnChanged ),		NULL, this);
	eventDispatcher->Connect(EVT_OGRE_CAMERA_CONSTRUCTED,	ImprovedEventHandler( CameraListener::OnConstructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_CAMERA_DESTRUCTED,	ImprovedEventHandler( CameraListener::OnDestructed ),	NULL, this);
	eventDispatcher->Connect(EVT_OGRE_CAMERA_RENAMED,		ImprovedEventHandler( CameraListener::OnRenamed ),		NULL, this);
}
void CameraListener::StopListening()
{
	EventDispatcher* eventDispatcher = EventDispatcher::GetSingletonPtr();

	// Stop listening parents events
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_SELECTED,	ImprovedEventHandler( CameraListener::OnSelected ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_OBJECT_UNSELECTED,	ImprovedEventHandler( CameraListener::OnUnselected ),		NULL, this);
	
	// Stop listening events
	eventDispatcher->Disconnect(EVT_OGRE_CAMERA_CHANGED,	ImprovedEventHandler( CameraListener::OnChanged ),		NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_CAMERA_CONSTRUCTED,ImprovedEventHandler( CameraListener::OnConstructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_CAMERA_DESTRUCTED, ImprovedEventHandler( CameraListener::OnDestructed ),	NULL, this);
	eventDispatcher->Disconnect(EVT_OGRE_CAMERA_RENAMED,	ImprovedEventHandler( CameraListener::OnRenamed ),		NULL, this);
}
wxString CameraListener::GetListenerTypeName() { return ToWxString("CameraListener"); }
// Methods of parent events
void CameraListener::OnSelected(ImprovedEvent &event) { event.Skip(); }
void CameraListener::OnUnselected(ImprovedEvent &event) { event.Skip(); }
// Methods of events
void CameraListener::OnChanged(ImprovedEvent &event) { event.Skip(); }
void CameraListener::OnConstructed(ImprovedEvent &event) { event.Skip(); }
void CameraListener::OnDestructed(ImprovedEvent &event) { event.Skip(); }
void CameraListener::OnRenamed(ImprovedEvent &event) { event.Skip(); }