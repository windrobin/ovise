#include "../OgreMediator/SceneNodeInterface.h"

// De- & Constructors, individual
SceneNodeInterface::SceneNodeInterface(MovableObjectInterface* iMovableObject, ObjectManager* ObjMgr) : MediatorInterface(ObjMgr) { this->SetMovableObjectInterface(iMovableObject); }
SceneNodeInterface::~SceneNodeInterface(void) { }
// Methods, inherited and overwritten
QualifiedName SceneNodeInterface::Create(wxString Name)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();
	
	// Get RootSceneNode
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());
	Ogre::SceneNode* RSN = SM->getRootSceneNode();

	// Forward & Return
	return this->Create(Name, RSN);
}
bool SceneNodeInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::SceneNode
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get SceneNode
	Ogre::SceneNode* SN = this->mObjectAccess->GetSceneNode(qName);

	// Destroy recusive: childnodes
	Ogre::SceneNode::ChildNodeIterator IT_ChildSN = SN->getChildIterator();
	while(IT_ChildSN.hasMoreElements())
	{
		Ogre::SceneNode* SN_Child = (Ogre::SceneNode*)IT_ChildSN.getNext();
		wxString UniqueName = ToWxString(SN_Child->getName());
		QualifiedName qChildSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		this->Destroy(qChildSceneNode);
	}

	// Destroy recusive: movable objects
	Ogre::SceneNode::ObjectIterator IT_MovObj = SN->getAttachedObjectIterator();
	while(IT_MovObj.hasMoreElements())
	{
		// Get Ogre::MovableObject
		Ogre::MovableObject* MO = IT_MovObj.getNext();
		wxString UniqueName = ToWxString(MO->getName());
		QualifiedName qMovableObject = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		
		// Remove it with interface
		if (this->iMovableObject->Destroy(qMovableObject))
		{
			// Iterator is corrupted, because MovableObject is deleted. Reinitialize it! 
			// "fix" for GCC (obviously can't cast the return value of getAttachedObjectIterator() to a reference
			Ogre::SceneNode::ObjectIterator TmpIt = SN->getAttachedObjectIterator();
			IT_MovObj = TmpIt;
		}
		// else // MovableObject was not registered = was not placed with interface. So don't remove it that way!
	}

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveSceneNode(qName);

	// Destroy Ogre::SceneNode
	SM->destroySceneNode(SN);

	EventDispatcher::Publish(EVT_OGRE_OBJECT_DESTRUCTED, qName);
	EventDispatcher::Publish(EVT_OGRE_SCENENODE_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::SceneNode
	QualifiedName::Destroy(qName);

	return true;
}
bool SceneNodeInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a SceneNode
	if ( this->mObjectAccess->GetSceneNode(qName) == 0 ) return false;

	return true;
}
bool SceneNodeInterface::IsValid()
{
	if( !MediatorInterface::IsValid() ) return false;
	if( !this->mObjectAccess->GetActiveSceneManager().IsValid() ) return false;
	if( this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager()) == 0 ) return false;
	if( this->iMovableObject == 0 ) return false;

	return true;
}
// Methods, individual
QualifiedName SceneNodeInterface::Create(wxString Name, QualifiedName qParentSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Validate parameters
	if ( !qParentSceneNode.IsValid() )  return QualifiedName();

	// Get Ogre::SceneNode
	Ogre::SceneNode* PSN = this->mObjectAccess->GetSceneNode(qParentSceneNode);
	
	// Validate Ogre::SceneNode
	if ( PSN == 0 ) return QualifiedName();

	// Forward & Return
	return this->Create(Name, PSN);
}
QualifiedName SceneNodeInterface::Create(wxString Name, Ogre::SceneNode* pParentSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());

	// Create QualifiedName of new Ogre::SceneNode
	QualifiedName qSceneNode = QualifiedName::Create(Name, "SceneNode");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetSceneNode(qSceneNode) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qSceneNode).IsValid()))
	{
		QualifiedName::Destroy(qSceneNode);
		return QualifiedName();
	}

	// Create new Ogre::SceneNode by validating given pParentSceneNode
	Ogre::SceneNode* SN;

	// Check, if SceneNode is RootSceneNode itself (!)
	if (ToWxString(SM->getRootSceneNode()->getName()).IsSameAs(Name))
	{
		SN = SM->getRootSceneNode();
	}
	else
	{
		if (pParentSceneNode == 0) SN = SM->getRootSceneNode()->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));
		else SN = pParentSceneNode->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));
	}

	// Validate new Ogre::SceneNode
	if (SN == 0)
	{
		QualifiedName::Destroy(qSceneNode);
		return QualifiedName();
	}

	// Add new Ogre::SceneNode ObjectManager
	this->mObjectAccess->AddSceneNode(qSceneNode, SN);

	// Add new association between Ogre::SceneNode and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(this->mObjectAccess->GetActiveSceneManager(), qSceneNode);

	EventDispatcher::Publish(EVT_OGRE_OBJECT_CONSTRUCTED, qSceneNode);
	EventDispatcher::Publish(EVT_OGRE_SCENENODE_CONSTRUCTED, qSceneNode);
	
	// Return QualifiedName of new Ogre::SceneNode
	return qSceneNode;
}
QualifiedName SceneNodeInterface::GetName(Ogre::SceneNode* pSceneNode)
{
	wxString UniqueName = ToWxString(pSceneNode->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
Ogre::SceneNode* SceneNodeInterface::GetPtr(QualifiedName qSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneNode
	if ( !qSceneNode.IsValid() ) return 0;

	// Get Ogre::SceneNode and return it (or null)
	return this->mObjectAccess->GetSceneNode(qSceneNode);
}

// Methods, individual, configuration
bool SceneNodeInterface::SetMovableObjectInterface(MovableObjectInterface* iMovableObject)
{
	if (iMovableObject == 0) return false;
	else
	{
		this->iMovableObject = iMovableObject;
		return true;
	}
}
