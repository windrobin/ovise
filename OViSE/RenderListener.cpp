#include "../OViSE/RenderListener.h"

RenderListener::RenderListener() { this->MovableObjectListener::SetListenerTypeName(ToWxString("RenderListener")); }
RenderListener::~RenderListener(void) { }
// Management of listener, sealed
void RenderListener::StartListening()
{
	MovableObjectListener::StartListening();
	OgreObjectListener::StartListening();
	SceneNodeListener::StartListening();
}
void RenderListener::StopListening()
{
	MovableObjectListener::StopListening();
	OgreObjectListener::StopListening();
	SceneNodeListener::StopListening();
}
// Methods of parent events, sealed
void RenderListener::OnChanged(ImprovedEvent &event)
{
	event.Skip();
}
void RenderListener::OnConstructed(ImprovedEvent &event)
{
	event.Skip();
}
void RenderListener::OnDestructed(ImprovedEvent &event)
{
	event.Skip();
}
void RenderListener::OnRenamed(ImprovedEvent &event)
{
	event.Skip();
}
void RenderListener::OnSelected(ImprovedEvent &event)
{
	// Apply SelectItem()
	QualifiedName qName = event.GetContextInfo();
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
	if (MO != 0)
	{
		Ogre::SceneNode* SN = MO->getParentSceneNode();
		QualifiedName qSN = QualifiedName::GetQualifiedNameByUnique(SN->getName());
		if (qSN.IsValid())
			OgreMediator::GetSingletonPtr()->iSceneNode.SetShowBoundingBox(qSN, true);
	}

	// Forwarding event
	event.Skip();
}
void RenderListener::OnUnselected(ImprovedEvent &event)
{
	// Apply UnselectItem()
	QualifiedName qName = event.GetContextInfo();
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
	if (MO != 0)
	{
		Ogre::SceneNode* SN = MO->getParentSceneNode();
		QualifiedName qSN = QualifiedName::GetQualifiedNameByUnique(SN->getName());
		if (qSN.IsValid())
			OgreMediator::GetSingletonPtr()->iSceneNode.SetShowBoundingBox(qSN, false);
	}

	// Forwarding event
	event.Skip();
}
void RenderListener::OnTranslated(ImprovedEvent &event)
{
	// Forwarding event
	event.Skip();
}
void RenderListener::OnRotated(ImprovedEvent &event)
{
	// Forwarding event
	event.Skip();
}
void RenderListener::OnScaled(ImprovedEvent &event)
{
	// Forwarding event
	event.Skip();
}