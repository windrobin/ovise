#include "LightInterface.h"

// De- & Constructors, individual
LightInterface::LightInterface(ObjectManager* ObjMgr) : MovableObjectInterface(ObjMgr) { }
LightInterface::~LightInterface(void) { }
// Methods, inherited and overwritten
bool LightInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::Light
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get Light
	Ogre::Light* L = this->mObjectAccess->GetLight(qName);
	
	// Get SceneNode
	Ogre::SceneNode* SN = L->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveLight(qName);

	// Destroy Ogre::Light
	SN->detachObject(L);
	SM->destroyLight(L);

	// Publish event
	this->Publish(EVT_OGRE_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::Light
	QualifiedName::Destroy(qName);

	return true;
}
bool LightInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a Light
	if ( this->mObjectAccess->GetLight(qName) == 0 ) return false;

	return true;
}

// Methods, individual
QualifiedName LightInterface::Create(wxString Name)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();
	
	// Get RootSceneNode
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());
	Ogre::SceneNode* RSN = SM->getRootSceneNode();

	// Forward & Return
	return this->Create(Name, RSN);
}
QualifiedName LightInterface::Create(wxString Name, QualifiedName qAnchorSceneNode)
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
	return this->Create(Name, ASN);
}
QualifiedName LightInterface::Create(wxString Name, Ogre::SceneNode* pAnchorSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());

	// Create QualifiedName of new Ogre::Light
	QualifiedName qLight = QualifiedName::Create(Name, "Light");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetLight(qLight) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qLight).IsValid()))
	{
		QualifiedName::Destroy(qLight);
		return QualifiedName();
	}

	// Create new Ogre::Light
	Ogre::Light* L = SM->createLight(ToOgreString(qLight.UniqueName()));

	// Validate new Ogre::Light
	if (L == 0)
	{
		QualifiedName::Destroy(qLight);
		return QualifiedName();
	}

	// Add new Ogre::Entity ObjectManager
	this->mObjectAccess->AddLight(qLight, L);

	// Add new association between Ogre::Entity and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(this->mObjectAccess->GetActiveSceneManager(), qLight);

	// Attach new Ogre::Light
	if (pAnchorSceneNode == 0)  SM->getRootSceneNode()->attachObject(L);
	else pAnchorSceneNode->attachObject(L);
	
	// Publish event
	this->Publish(EVT_OGRE_CONSTRUCTED, qLight);

	// Return QualifiedName of new Ogre::Light
	return qLight;
}
Ogre::Light* LightInterface::GetPtr(QualifiedName qLight)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneNode
	if ( !qLight.IsValid() ) return 0;

	// Get Ogre::Entity and return it (or null)
	return this->mObjectAccess->GetLight(qLight);
}

