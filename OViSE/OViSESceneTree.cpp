#include "OViSESceneTree.h"

OViSESceneTreeData::OViSESceneTreeData(OViSESceneTreeDataType type, void *dataPointer)
{
	mType = type;
	mData = dataPointer;
}

OViSESceneTreeData::~OViSESceneTreeData()
{

}

OViSESceneTreeDataType OViSESceneTreeData::getType()
{
	return mType;
}

void* OViSESceneTreeData::getDataPointer()
{
	return mData;
}

/// ====================================================================================

OViSESceneTree::OViSESceneTree(Ogre::SceneManager *manager, wxWindow* parent, wxWindowID id, const wxPoint& pos,
							   const wxSize& size, long style, const wxValidator& validator, const wxString& name) :
	wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	mSceneManager = manager;
	mInitialized = false;

	this->ConnectOgreAPIMediator();
}

void OViSESceneTree::setSceneManager(Ogre::SceneManager *manager)
{
	mSceneManager = manager;
}


void OViSESceneTree::ConnectOgreAPIMediator()
{
	OgreAPIMediator* test = OgreAPIMediator::GetSingletonPtr();
	test->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OViSESceneTree::OnOgreChanged ), NULL, this);
}

void OViSESceneTree::initTree()
{
	if(mInitialized)
		return;

	// Intialize tree

	Ogre::SceneNode *rn = mSceneManager->getRootSceneNode();

	OViSESceneTreeData *rootData = new OViSESceneTreeData(ROOT, (void*)rn);
	wxTreeItemId root = AddRoot(wxString(rn->getName().c_str(), wxConvLibc), 0, 0, rootData);

	wxTreeItemId id;
	for(unsigned short i=0; i<rn->numAttachedObjects(); i++)
	{
		Ogre::MovableObject *obj = rn->getAttachedObject(i);
		if(obj->getMovableType() == Ogre::String("Entity"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(ENTITY, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 2, 2, dataItem);
		}
		else if(obj->getMovableType() == Ogre::String("Camera"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(CAMERA, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 3, 3, dataItem);
		}
		else if(obj->getMovableType() == Ogre::String("Light"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(LIGHT, (void*)obj);
			id = AppendItem(root, wxString(obj->getName().c_str(), wxConvLibc), 4, 4, dataItem);
		}
	}
	for(unsigned short k=0; k<rn->numChildren(); k++)
	{
		addSceneNodeToTree((Ogre::SceneNode*)rn->getChild(k), root);
	}

	mInitialized = true;
}

void OViSESceneTree::addSceneNodeToTree(Ogre::SceneNode *node, wxTreeItemId parentItemId)
{
	OViSESceneTreeData *nodeData = new OViSESceneTreeData(SCENE_NODE, (void*)node);
	wxTreeItemId current = AppendItem(parentItemId, wxString(node->getName().c_str(), wxConvLibc), 1, 1, nodeData);
	wxTreeItemId id;
	for(unsigned short i=0; i<node->numAttachedObjects(); i++)
	{
		Ogre::MovableObject *obj = node->getAttachedObject(i);
		if(obj->getMovableType() == Ogre::String("Entity"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(ENTITY, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 2, 2, dataItem);
		}
		else if(obj->getMovableType() == Ogre::String("Camera"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(CAMERA, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 3, 3, dataItem);
		}
		else if(obj->getMovableType() == Ogre::String("Light"))
		{
			OViSESceneTreeData *dataItem = new OViSESceneTreeData(LIGHT, (void*)obj);
			id = AppendItem(current, wxString(obj->getName().c_str(), wxConvLibc), 4, 4, dataItem);
		}
	}

	for(unsigned short k=0; k<node->numChildren(); k++)
	{
		addSceneNodeToTree((Ogre::SceneNode*)node->getChild(k), current);
	}
}

void OViSESceneTree::updateTreeContents()
{
	DeleteAllItems();
	this->mInitialized = false;
	initTree();
}

OViSESceneTree::~OViSESceneTree(void)
{
	
}


void OViSESceneTree::OnOgreChanged(wxCommandEvent& event)
{
	this->updateTreeContents();
}
