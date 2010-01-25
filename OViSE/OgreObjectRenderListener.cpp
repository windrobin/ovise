#include "../OViSE/OgreObjectRenderListener.h"

OgreObjectRenderListener::OgreObjectRenderListener() {  }
OgreObjectRenderListener::~OgreObjectRenderListener(void) { }
// Management of listener, sealed
void OgreObjectRenderListener::StartListening() { OgreObjectListener::StartListening(); }
wxString OgreObjectRenderListener::GetListenerTypeName() { return ToWxString("OgreObjectRenderListener"); }
// Methods of parent events, sealed
void OgreObjectRenderListener::OnChanged(ImprovedEvent &event)
{
	event.Skip();
}
void OgreObjectRenderListener::OnConstructed(ImprovedEvent &event)
{
	event.Skip();
}
void OgreObjectRenderListener::OnDestructed(ImprovedEvent &event)
{
	event.Skip();
}
void OgreObjectRenderListener::OnRenamed(ImprovedEvent &event)
{
	event.Skip();
}
void OgreObjectRenderListener::OnSelected(ImprovedEvent &event)
{
	// Apply SelectItem()
	QualifiedName qName = event.GetContextInfo();
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
	if (MO != 0) MO->getParentSceneNode()->showBoundingBox(true);

	// Forwarding event
	event.Skip();
}
void OgreObjectRenderListener::OnUnselected(ImprovedEvent &event)
{
	// Apply UnselectItem()
	QualifiedName qName = event.GetContextInfo();
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
	if (MO != 0) MO->getParentSceneNode()->showBoundingBox(false);

	// Forwarding event
	event.Skip();
}