#include "SceneTree.h"

SceneTreeData::SceneTreeData(SceneTreeDataType type, void *dataPointer)
{
	mType = type;
	mData = dataPointer;
}

SceneTreeData::~SceneTreeData()
{

}

SceneTreeDataType SceneTreeData::getType()
{
	return mType;
}

void* SceneTreeData::getDataPointer()
{
	return mData;
}

/// ====================================================================================

SceneTree::SceneTree(wxWindow* parent, wxWindowID id, const wxPoint& pos,
							   const wxSize& size, long style, const wxValidator& validator, const wxString& name) :
	wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	this->OGRE_ROOT_STRING = ToWxString("Ogre/Root(Singleton)");
	
	this->DeleteAllItems();
	this->Items.clear();
	wxTreeItemId OgreRootTIID = this->AddRoot(this->OGRE_ROOT_STRING, 0, 0, 0);
	this->Items[this->OGRE_ROOT_STRING] = OgreRootTIID;
	this->ExpandAll();

	this->Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &SceneTree::OnTreeSelectionChanged, this);
	this->SetPublishTreeSelectionChanged(true);
}
void SceneTree::addSceneNodeToTree(Ogre::SceneNode *node, wxTreeItemId parentItemId)
{
	SceneTreeData *nodeData = new SceneTreeData(SCENE_NODE, (void*)node);
	wxTreeItemId current = AppendItem(parentItemId, wxString(node->getName().c_str(), wxConvLibc), 1, 1, nodeData);
	this->Items[wxString(node->getName().c_str(), wxConvLibc)] = current;

	wxTreeItemId id;
	for(unsigned short i=0; i<node->numAttachedObjects(); i++)
	{
		Ogre::MovableObject *obj = node->getAttachedObject(i);
		if(obj->getMovableType() == Ogre::String("Entity"))
		{
			SceneTreeData *dataItem = new SceneTreeData(ENTITY, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 2, 2, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
		else if(obj->getMovableType() == Ogre::String("Camera"))
		{
			SceneTreeData *dataItem = new SceneTreeData(CAMERA, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 3, 3, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
		else if(obj->getMovableType() == Ogre::String("Light"))
		{
			SceneTreeData *dataItem = new SceneTreeData(LIGHT, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 4, 4, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
	}

	for(unsigned short k=0; k<node->numChildren(); k++)
	{
		addSceneNodeToTree((Ogre::SceneNode*)node->getChild(k), current);
	}
}
SceneTree::~SceneTree(void) { this->Unbind(wxEVT_COMMAND_TREE_SEL_CHANGED, &SceneTree::OnTreeSelectionChanged, this); }
void SceneTree::OnTreeSelectionChanged( wxTreeEvent& event )
{
	if (this->GetPublishTreeSelectionChanged())
	{
		wxTreeItemId ID = event.GetItem();
		wxString UniqueName = this->GetItemText(ID);
		QualifiedName qName = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(UniqueName);
		if (qName.IsValid())
		{
			// Publish: unselect old selection
			if (this->mLastSelectedEntry.IsValid()) EventDispatcher::Publish(EVT_OGRE_OBJECT_UNSELECTED, this->mLastSelectedEntry);

			// Remember new selection
			this->mLastSelectedEntry = qName;

			// Publish: selected new selection
			if (this->IsSelected(ID)) EventDispatcher::Publish(EVT_OGRE_OBJECT_SELECTED, qName);
		}
	}
	event.Skip();
}
void SceneTree::OnItemActivated( wxTreeEvent& event ) // Double-Click event
{
	// Set Focus here?
}
void SceneTree::SetPublishTreeSelectionChanged(bool value) { this->mPublishTreeSelectionChanged = value; }
bool SceneTree::GetPublishTreeSelectionChanged() { return this->mPublishTreeSelectionChanged; }
bool SceneTree::AddOgreObject(QualifiedName qOgreObject)
{
	bool Match = false;
	
	wxString FullTest = qOgreObject.UniqueName();

	// Check, if OgreObject is already in SceneTree...
	if (this->Items.count(qOgreObject.UniqueName()) != 0) return Match;

	if ((!Match) && OgreMediator::GetSingletonPtr()->iCamera.Exist(qOgreObject))
	{
		Ogre::Camera* C = OgreMediator::GetSingletonPtr()->iCamera.GetPtr(qOgreObject);
		if (C == 0) return Match;

		// Check, if parent is RootSceneNode
		QualifiedName qPSN;
		if (ToWxString(C->getParentSceneNode()->getName()).Contains(ToWxString("Ogre/SceneRoot")))
		{
			QualifiedNameCollection QNames = QualifiedNameCollection::GetQualifiedNameByNative(ToWxString(C->getParentSceneNode()->getName()));
			qPSN = QNames[0];
		}
		else
		{
			qPSN = OgreMediator::GetSingletonPtr()->iSceneNode.GetName(C->getParentSceneNode());
		}
		
		if (!qPSN.IsValid()) return Match;
		
		if (this->Items.count(qPSN.UniqueName()) == 0)
		{
			// Parent not in SceneTree -> recursive call
			this->AddOgreObject(qPSN);
		}
		wxTreeItemId ParentSceneNodeTIID = this->Items[qPSN.UniqueName()];
		wxTreeItemId CameraTIID = this->AppendItem(ParentSceneNodeTIID, qOgreObject.UniqueName(), 3, 3, 0);
		this->Items[qOgreObject.UniqueName()] = CameraTIID;
		this->ExpandAll();

		Match = true;
	}
	if ((!Match) && OgreMediator::GetSingletonPtr()->iEntity.Exist(qOgreObject))
	{
		Ogre::Entity* E = OgreMediator::GetSingletonPtr()->iEntity.GetPtr(qOgreObject);
		if (E == 0) return Match;
		
		// Check, if parent is RootSceneNode
		QualifiedName qPSN;
		if (ToWxString(E->getParentSceneNode()->getName()).Contains(ToWxString("Ogre/SceneRoot")))
		{
			QualifiedNameCollection QNames = QualifiedNameCollection::GetQualifiedNameByNative(ToWxString(E->getParentSceneNode()->getName()));
			qPSN = QNames[0];
		}
		else
		{
			qPSN = OgreMediator::GetSingletonPtr()->iSceneNode.GetName(E->getParentSceneNode());
		}
	
		if (this->Items.count(qPSN.UniqueName()) == 0)
		{
			// Parent not in SceneTree -> recursive call
			this->AddOgreObject(qPSN);
		}
		wxTreeItemId ParentSceneNodeTIID = this->Items[qPSN.UniqueName()];
		wxTreeItemId EntityTIID = this->AppendItem(ParentSceneNodeTIID, qOgreObject.UniqueName(), 2, 2, 0);
		this->Items[qOgreObject.UniqueName()] = EntityTIID;
		this->ExpandAll();

		Match = true;
	}
	if ((!Match) && OgreMediator::GetSingletonPtr()->iLight.Exist(qOgreObject))
	{
		Ogre::Light* L = OgreMediator::GetSingletonPtr()->iLight.GetPtr(qOgreObject);
		if (L == 0) return Match;

		// Check, if parent is RootSceneNode
		QualifiedName qPSN;
		if (ToWxString(L->getParentSceneNode()->getName()).Contains(ToWxString("Ogre/SceneRoot")))
		{
			QualifiedNameCollection QNames = QualifiedNameCollection::GetQualifiedNameByNative(ToWxString(L->getParentSceneNode()->getName()));
			qPSN = QNames[0];
		}
		else
		{
			qPSN = OgreMediator::GetSingletonPtr()->iSceneNode.GetName(L->getParentSceneNode());
		}

		if (!qPSN.IsValid()) return Match;
		
		if (this->Items.count(qPSN.UniqueName()) == 0)
		{
			// Parent not in SceneTree -> recursive call
			this->AddOgreObject(qPSN);
		}
		wxTreeItemId ParentSceneNodeTIID = this->Items[qPSN.UniqueName()];
		wxTreeItemId LightTIID = this->AppendItem(ParentSceneNodeTIID, qOgreObject.UniqueName(), 4, 4, 0);
		this->Items[qOgreObject.UniqueName()] = LightTIID;
		this->ExpandAll();

		Match = true;
	}
	if ((!Match) && OgreMediator::GetSingletonPtr()->iMovableObject.Exist(qOgreObject))
	{
		Match = true;
	}
	if ((!Match) && OgreMediator::GetSingletonPtr()->iSceneManager.Exist(qOgreObject))
	{
		// Add SceneManager
		wxTreeItemId OgreRootTIID = this->GetRootItem();
		wxTreeItemId SceneManagerTIID = this->AppendItem(OgreRootTIID, qOgreObject.UniqueName(), 0, 0, 0);
		this->Items[qOgreObject.UniqueName()] = SceneManagerTIID;
		this->ExpandAll();
		
		// Add SceneManager's RootSceneNode
		Ogre::SceneManager* SM = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(qOgreObject);
		QualifiedName qRSN = OgreMediator::GetSingletonPtr()->iSceneNode.GetName(SM->getRootSceneNode());
		this->AddOgreObject(qRSN);

		Match = true;
	}
	if ((!Match) && OgreMediator::GetSingletonPtr()->iSceneNode.Exist(qOgreObject))
	{
		Ogre::SceneNode* SN = OgreMediator::GetSingletonPtr()->iSceneNode.GetPtr(qOgreObject);
		if (SN == 0) return Match;
		QualifiedName qSM = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetAssociatedSceneManager(qOgreObject);
		Ogre::SceneManager* SM = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(qSM);
		if (SM == 0) return Match;

		// Ensure SceneManager is in SceneTree...
		if (this->Items.count(qSM.UniqueName()) == 0)
		{
			// SceneManager not in SceneTree -> recursive call
			this->AddOgreObject(qSM);
		}
		
		// Check, if given SceneNode is RootSceneNode
		if (SN->getParentSceneNode() == 0)
		{
			// There is no parent. SceneNode are always attached -> So it is RootSceneNode -> attach to SceneManager
			wxTreeItemId SceneManagerTIID = this->Items[qSM.UniqueName()];
			wxTreeItemId RootSceneNodeTIID = this->AppendItem(SceneManagerTIID, qOgreObject.UniqueName(), 1, 1, 0);
			this->Items[qOgreObject.UniqueName()] = RootSceneNodeTIID;
			this->ExpandAll();
		}
		else
		{
			// Check, if parent is RootSceneNode
			QualifiedName qPSN;
			if (ToWxString(SN->getParentSceneNode()->getName()).Contains(ToWxString("Ogre/SceneRoot")))
			{
				QualifiedNameCollection QNames = QualifiedNameCollection::GetQualifiedNameByNative(ToWxString(SN->getParentSceneNode()->getName()));
				qPSN = QNames[0];
			}
			else
			{
				qPSN = OgreMediator::GetSingletonPtr()->iSceneNode.GetName(SN->getParentSceneNode());
			}

			// Validate QualifiedName
			if (!qPSN.IsValid()) return Match;
			
			if (this->Items.count(qPSN.UniqueName()) == 0)
			{
				// Parent not in SceneTree -> recursive call
				this->AddOgreObject(qPSN);
			}
			wxTreeItemId ParentSceneNodeTIID = this->Items[qPSN.UniqueName()];
			wxTreeItemId SceneNodeTIID = this->AppendItem(ParentSceneNodeTIID, qOgreObject.UniqueName(), 1, 1, 0);
			this->Items[qOgreObject.UniqueName()] = SceneNodeTIID;
			this->ExpandAll();
		}

		Match = true;
	}

	return Match;
}
bool SceneTree::RemoveOgreObject(QualifiedName qOgreObject)
{
	wxString FullTest = qOgreObject.UniqueName();

	// Check, if OgreObject is already in SceneTree...
	if (this->Items.count(qOgreObject.UniqueName()) == 0) return false;

	wxTreeItemId ID = this->Items[FullTest];
	this->Delete(ID);
	this->Refresh();
	/*this->remthis->GetItemParent(ID)
	this->Delete(ID);
	this->CollapseAll();
	this->ExpandAll();
	this->Refresh();
	this->GetParent()->Refresh();
	this->Update();
	this->GetParent()->Update();*/

	return true;
}