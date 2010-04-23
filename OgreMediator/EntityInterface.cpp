#include "../OgreMediator/EntityInterface.h"

// De- & Constructors, individual
EntityInterface::EntityInterface(ObjectManager* ObjMgr) : MovableObjectInterface(ObjMgr) { }
EntityInterface::~EntityInterface(void) { }
// Methods, inherited and overwritten
bool EntityInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::Entity
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get Entity
	Ogre::Entity* E = this->mObjectAccess->GetEntity(qName);
	
	// Get SceneNode
	Ogre::SceneNode* SN = E->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveEntity(qName);

	// Destroy Ogre::Entity
	SN->detachObject(E);
	SM->destroyEntity(E);
	
	// Publish event
	this->Publish(EVT_OGRE_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::Entity
	QualifiedName::Destroy(qName);

	return true;
}
bool EntityInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a Entity
	if ( this->mObjectAccess->GetEntity(qName) == 0 ) return false;

	return true;
}

// Methods, individual
QualifiedName EntityInterface::Create(wxString Name, wxString MeshFile)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();
	
	// Get RootSceneNode
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());
	Ogre::SceneNode* RSN = SM->getRootSceneNode();

	// Forward & Return
	return this->Create(Name, MeshFile, RSN);
}
QualifiedName EntityInterface::Create(wxString Name, wxString MeshFile, QualifiedName qAnchorSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Validate parameters
	if ( !qAnchorSceneNode.IsValid() ) return QualifiedName();

	// Get Ogre::SceneNode
	Ogre::SceneNode* ASN = this->mObjectAccess->GetSceneNode(qAnchorSceneNode);
	
	// Validate Ogre::SceneNode
	if ( ASN == 0 ) return QualifiedName();

	// Forward & Return
	return this->Create(Name, MeshFile, ASN);
}
QualifiedName EntityInterface::Create(wxString Name, wxString MeshFile, Ogre::SceneNode* pAnchorSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());

	// Validate parameter MeshFile
	//if ( !wxFileName::FileExists(MeshFile) ) return QualifiedName(); // TODO: H.R. 03.12.09: Don't validate that. No error should occure!

	// Create QualifiedName of new Ogre::Entity
	QualifiedName qEntity = QualifiedName::Create(Name, "Entity");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetEntity(qEntity) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qEntity).IsValid()))
	{
		QualifiedName::Destroy(qEntity);
		return QualifiedName();
	}

	// Create new Ogre::Entity
	Ogre::Entity* E = SM->createEntity(ToOgreString(qEntity.UniqueName()), ToOgreString(MeshFile));

	// Validate new Ogre::Entity
	if (E == 0)
	{
		QualifiedName::Destroy(qEntity);
		return QualifiedName();
	}

	// Add new Ogre::Entity ObjectManager
	this->mObjectAccess->AddEntity(qEntity, E);

	// Add new association between Ogre::Entity and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(this->mObjectAccess->GetActiveSceneManager(), qEntity);

	// Attach new Ogre::Entity
	if (pAnchorSceneNode == 0)  SM->getRootSceneNode()->attachObject(E);
	else pAnchorSceneNode->attachObject(E);

	// Publish event
	this->Publish(EVT_OGRE_CONSTRUCTED, qEntity);
	
	// Return QualifiedName of new Ogre::Entity
	return qEntity;
}
Ogre::Entity* EntityInterface::GetPtr(QualifiedName qEntity)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneNode
	if ( !qEntity.IsValid() ) return 0;

	// Get Ogre::Entity and return it (or null)
	return this->mObjectAccess->GetEntity(qEntity);
}
