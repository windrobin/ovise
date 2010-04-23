#include "../OViSE/SelectionManagerListener.h"

SelectionManagerListener::SelectionManagerListener() { this->MovableObjectListener::SetListenerTypeName(ToWxString("SelectionManagerListener")); }
SelectionManagerListener::~SelectionManagerListener(void) { }
// Management of listener, sealed
void SelectionManagerListener::StartListening()
{
	MovableObjectListener::StartListening();
	OgreObjectListener::StartListening();
	SceneNodeListener::StartListening();
}
void SelectionManagerListener::StopListening()
{
	MovableObjectListener::StopListening();
	OgreObjectListener::StopListening();
	SceneNodeListener::StopListening();
}
// Methods of parent events, sealed
void SelectionManagerListener::OnChanged(ImprovedEvent &event)
{
	// Call SelectionManager::HandlePropertyChanged(...)
	QualifiedName qName = event.GetContextInfo();
	if (SelectionManager::getSingletonPtr()->Selection.Contains(qName))
	{
		wxVariant vContextData = event.GetContextData();
		wxArrayString asContextData = vContextData.GetArrayString();
		if (asContextData.Count() > 0)
		{
			wxString FullProperyName;
			FullProperyName << qName.UniqueName() << ToWxString(".") << asContextData[0];
			wxPGProperty* prop = SelectionManager::getSingletonPtr()->GetPropertyGrid()->GetPropertyByName(FullProperyName);
			if (prop) SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop, InputSourceType::Event);
		}
		else
		{
			wxString DebugStr = ToWxString("DEBUG");
			// Ugly! No name of parameter found!
			// Check out source of event and there event's setup!!!
		}
	}
	// Else: do nothing!
	
	// Forwarding event
	event.Skip();
}
void SelectionManagerListener::OnConstructed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerListener::OnDestructed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerListener::OnRenamed(ImprovedEvent &event)
{
	event.Skip();
}
void SelectionManagerListener::OnSelected(ImprovedEvent &event)
{
	// Apply SelectItem()
	QualifiedName qName = event.GetContextInfo();
	if (!SelectionManager::getSingletonPtr()->Selection.Contains(qName))
	{
		SelectionManager::getSingletonPtr()->Selection.Add(qName);

		// Add ParentSceneNode EVERY time!
		Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
		if (MO)
		{
			Ogre::SceneNode* SN = MO->getParentSceneNode();
			QualifiedName qSN = QualifiedName::GetQualifiedNameByUnique(SN->getName());
			
			// Add SceneNodes multiple timmes is not only allowed - it's ESSENTIAL (!!!)
			// ...because every time a MO is added, a SN is removed
			// ...and so for every MO removed from selection, a SN can be removed too.
			if (qSN.IsValid())
			{
				SelectionManager::getSingletonPtr()->Selection.Add(qSN);
			}
		}
	}

	// Generate PG
	SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection();

	// Forwarding event
	event.Skip();
}
void SelectionManagerListener::OnUnselected(ImprovedEvent &event)
{
	// Apply UnselectItem()
	QualifiedName qName = event.GetContextInfo();
	bool Result = SelectionManager::getSingletonPtr()->Selection.Remove(qName);

	if (Result)
	{
		// Add ParentSceneNode (maybe one of it's many occurrences)!
		Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qName);
		if (MO)
		{
			Ogre::SceneNode* SN = MO->getParentSceneNode();
			QualifiedName qSN = QualifiedName::GetQualifiedNameByUnique(SN->getName());
			SelectionManager::getSingletonPtr()->Selection.Remove(qName);
		}
	}

	SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection();

	// Forwarding event
	event.Skip();
}
void SelectionManagerListener::OnTranslated(ImprovedEvent &event)
{
	// Call SelectionManager::HandlePropertyChanged(...)
	QualifiedName qName = event.GetContextInfo();
	if (SelectionManager::getSingletonPtr()->Selection.Contains(qName))
	{
		wxVariant vContextData = event.GetContextData();
		wxArrayString asContextData = vContextData.GetArrayString();
		if (asContextData.Count() > 0)
		{
			wxString FullProperyName;
			FullProperyName << qName.UniqueName() << ToWxString(".") << asContextData[0];
			wxPGProperty* prop = SelectionManager::getSingletonPtr()->GetPropertyGrid()->GetPropertyByName(FullProperyName);
			if (prop) SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop, InputSourceType::Event);
		}
		else
		{
			wxString DebugStr = ToWxString("DEBUG");
			// Ugly! No name of parameter found!
			// Check out source of event and there event's setup!!!
		}
	}
	// Else: do nothing!
	
	// Forwarding event
	event.Skip();
}
void SelectionManagerListener::OnRotated(ImprovedEvent &event)
{
	// Call SelectionManager::HandlePropertyChanged(...)
	QualifiedName qName = event.GetContextInfo();
	if (SelectionManager::getSingletonPtr()->Selection.Contains(qName))
	{
		wxVariant vContextData = event.GetContextData();
		wxArrayString asContextData = vContextData.GetArrayString();
		if (asContextData.Count() > 0)
		{
			wxString FullProperyName;
			FullProperyName << qName.UniqueName() << ToWxString(".") << asContextData[0];
			wxPGProperty* prop = SelectionManager::getSingletonPtr()->GetPropertyGrid()->GetPropertyByName(FullProperyName);
			if (prop) SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop, InputSourceType::Event);
		}
		else
		{
			wxString DebugStr = ToWxString("DEBUG");
			// Ugly! No name of parameter found!
			// Check out source of event and there event's setup!!!
		}
	}
	// Else: do nothing!
	
	// Forwarding event
	event.Skip();
}
void SelectionManagerListener::OnScaled(ImprovedEvent &event)
{
	// Call SelectionManager::HandlePropertyChanged(...)
	QualifiedName qName = event.GetContextInfo();
	if (SelectionManager::getSingletonPtr()->Selection.Contains(qName))
	{
		wxVariant vContextData = event.GetContextData();
		wxArrayString asContextData = vContextData.GetArrayString();
		if (asContextData.Count() > 0)
		{
			wxString FullProperyName;
			FullProperyName << qName.UniqueName() << ToWxString(".") << asContextData[0];
			wxPGProperty* prop = SelectionManager::getSingletonPtr()->GetPropertyGrid()->GetPropertyByName(FullProperyName);
			if (prop) SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop, InputSourceType::Event);
		}
		else
		{
			wxString DebugStr = ToWxString("DEBUG");
			// Ugly! No name of parameter found!
			// Check out source of event and there event's setup!!!
		}
	}
	// Else: do nothing!
	
	// Forwarding event
	event.Skip();
}