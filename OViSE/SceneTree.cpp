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

SceneTree::SceneTree(Ogre::SceneManager *manager, wxWindow* parent, wxWindowID id, const wxPoint& pos,
							   const wxSize& size, long style, const wxValidator& validator, const wxString& name) :
	wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	mSceneManager = manager;
	mInitialized = false;

	this->ConnectOgreMediator();
}

void SceneTree::setSceneManager(Ogre::SceneManager *manager)
{
	mSceneManager = manager;
}


void SceneTree::ConnectOgreMediator()
{
	OgreMediator* test = OgreMediator::GetSingletonPtr();
	test->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( SceneTree::OnOgreChanged ), NULL, this);
}

void SceneTree::initTree()
{
	if(mInitialized)
		return;

	// Intialize tree
	Ogre::SceneNode *rn = mSceneManager->getRootSceneNode();

	SceneTreeData *rootData = new SceneTreeData(ROOT, (void*)rn);
	wxTreeItemId root = AddRoot(wxString(rn->getName().c_str(), wxConvLibc), 0, 0, rootData);
	this->Items[wxString(rn->getName().c_str(), wxConvLibc)] = root;

	wxTreeItemId id;
	for(unsigned short i=0; i<rn->numAttachedObjects(); i++)
	{
		Ogre::MovableObject *obj = rn->getAttachedObject(i);
		if(obj->getMovableType() == Ogre::String("Entity"))
		{
			SceneTreeData *dataItem = new SceneTreeData(ENTITY, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 2, 2, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
		else if(obj->getMovableType() == Ogre::String("Camera"))
		{
			SceneTreeData *dataItem = new SceneTreeData(CAMERA, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 3, 3, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
		else if(obj->getMovableType() == Ogre::String("Light"))
		{
			SceneTreeData *dataItem = new SceneTreeData(LIGHT, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 4, 4, dataItem);
			this->Items[wxString(obj->getName().c_str(), wxConvLibc)] = id;
		}
	}
	for(unsigned short k=0; k<rn->numChildren(); k++)
	{
		addSceneNodeToTree((Ogre::SceneNode*)rn->getChild(k), root);
	}

	mInitialized = true;
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

void SceneTree::updateTreeContents()
{
	DeleteAllItems();
	this->Items.clear();
	this->mInitialized = false;
	initTree();
}

SceneTree::~SceneTree(void)
{
	
}


void SceneTree::OnOgreChanged(wxCommandEvent& event)
{
	this->updateTreeContents();
}
