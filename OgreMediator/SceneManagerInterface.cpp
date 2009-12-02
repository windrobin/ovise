#include "../OgreMediator/SceneManagerInterface.h"

// De- & Constructors, individual
SceneManagerInterface::SceneManagerInterface(SceneNodeInterface* iSceneNode, ObjectManager* ObjMgr) : MediatorInterface(ObjMgr) { this->SetSceneNodeInterface(iSceneNode); }
SceneManagerInterface::~SceneManagerInterface(void) { }
// Methods, inherited and overwritten
QualifiedName SceneManagerInterface::Create(wxString Name) { return this->Create(Name, Ogre::ST_GENERIC); }
bool SceneManagerInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::SceneManager
	if ( !this->Exist(qName) ) return false;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qName);

	// Destroy recusive: childnodes
	Ogre::SceneNode* RSN = SM->getRootSceneNode();
	wxString UniqueName = ToWxString(RSN->getName());
	QualifiedName qRootSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	this->iSceneNode->Destroy(qRootSceneNode);

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveSceneManager(qName);

	// Destroy Ogre::SceneManager
	Ogre::Root::getSingletonPtr()->destroySceneManager(SM);

	// Destroy QualifiedName of Ogre::SceneManager
	QualifiedName::Destroy(qName);

	// Flag Ogre-engine as chanced
	this->mOgreChanged = true;

	return true;
}
bool SceneManagerInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a SceneManager
	if (this->mObjectAccess->GetSceneManager(qName) == 0) return false;
	
	return true;
}
bool SceneManagerInterface::IsValid()
{
	if( !MediatorInterface::IsValid() ) return false;
	if( this->iSceneNode == 0 ) return false;

	return true;
}
// Methods, individual
QualifiedName SceneManagerInterface::Create(wxString Name, Ogre::SceneType pSceneType)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Create QualifiedName of new Ogre::SceneManager
	QualifiedName qSceneManager = QualifiedName::Create(Name, "SceneManager");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetSceneManager(qSceneManager) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qSceneManager).IsValid()))
	{
		QualifiedName::Destroy(qSceneManager);
		return QualifiedName();
	}

	// Create and validate new Ogre::SceneManager
	Ogre::SceneManager* SM = Ogre::Root::getSingletonPtr()->createSceneManager(pSceneType, ToOgreString(qSceneManager.UniqueName()));

	if (SM == 0)
	{
		QualifiedName::Destroy(qSceneManager);
		return QualifiedName();
	}

	// Add new Ogre::Camera ObjectManager
	this->mObjectAccess->AddSceneManager(qSceneManager, SM);

	// Add new association between Ogre::SceneManager and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(qSceneManager, qSceneManager);

	// Flag Ogre-engine as chanced
	this->mOgreChanged = true;
	
	// Return QualifiedName of new Ogre::Camera
	return qSceneManager;
}
QualifiedName SceneManagerInterface::GetName(Ogre::SceneManager* pSceneManager)
{
	wxString UniqueName = ToWxString(pSceneManager->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
Ogre::SceneManager*	SceneManagerInterface::GetPtr(QualifiedName qSceneManager)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneManager
	if ( !qSceneManager.IsValid() ) return 0;

	// Get SceneManager and return it (or null)
	return this->mObjectAccess->GetSceneManager(qSceneManager);
}
// Methods, individual, active Ogre::SceneManager
bool SceneManagerInterface::SetActiveSceneManager(QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return false;

	// Forward & Return
	return this->mObjectAccess->SetActiveSceneManager(qSceneManager);
}
QualifiedName SceneManagerInterface::GetActiveSceneManager() { return this->mObjectAccess->GetActiveSceneManager(); }
// Methods, individual, configuration
bool SceneManagerInterface::SetSceneNodeInterface(SceneNodeInterface* iSceneNode)
{
	if (iSceneNode == 0) return false;
	else
	{
		this->iSceneNode = iSceneNode;
		return true;
	}
}