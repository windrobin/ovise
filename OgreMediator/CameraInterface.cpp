#include "../OgreMediator/CameraInterface.h"

// De- & Constructors, individual
CameraInterface::CameraInterface(ObjectManager* ObjMgr) : MovableObjectInterface(ObjMgr) { }
CameraInterface::~CameraInterface(void) { }
// Methods, inherited and overwritten
bool CameraInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::Camera
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get Camera
	Ogre::Camera* C = this->mObjectAccess->GetCamera(qName);
	
	// Get SceneNode
	Ogre::SceneNode* SN = C->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveCamera(qName);

	// Destroy Ogre::Camera
	SN->detachObject(C);
	SM->destroyCamera(C);

	EventDispatcher::Publish(EVT_OGRE_OBJECT_DESTRUCTED, qName);
	EventDispatcher::Publish(EVT_OGRE_CAMERA_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::Camera
	QualifiedName::Destroy(qName);

	return true;
}
bool CameraInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a Light
	if ( this->mObjectAccess->GetCamera(qName) == 0 ) return false;

	return true;
}

// Methods, individual
QualifiedName CameraInterface::Create(wxString Name)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();
	
	// Get RootSceneNode
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());
	Ogre::SceneNode* RSN = SM->getRootSceneNode();

	// Forward & Return
	return this->Create(Name, RSN);
}
QualifiedName CameraInterface::Create(wxString Name, QualifiedName qAnchorSceneNode)
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
QualifiedName CameraInterface::Create(wxString Name, Ogre::SceneNode* pAnchorSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());

	// Create QualifiedName of new Ogre::Camera
	QualifiedName qCamera = QualifiedName::Create(Name, "Camera");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetCamera(qCamera) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qCamera).IsValid()))
	{
		QualifiedName::Destroy(qCamera);
		return QualifiedName();
	}

	// Create new Ogre::Camera
	Ogre::Camera* C = SM->createCamera(ToOgreString(qCamera.UniqueName()));

	// Validate new Ogre::Camera
	if (C == 0)
	{
		QualifiedName::Destroy(qCamera);
		return QualifiedName();
	}

	// Add new Ogre::Entity ObjectManager
	this->mObjectAccess->AddCamera(qCamera, C);

	// Add new association between Ogre::Entity and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(this->mObjectAccess->GetActiveSceneManager(), qCamera);

	// Attach new Ogre::Camera
	if (pAnchorSceneNode == 0)  SM->getRootSceneNode()->attachObject(C);
	else pAnchorSceneNode->attachObject(C);
	
	EventDispatcher::Publish(EVT_OGRE_OBJECT_CONSTRUCTED, qCamera);
	EventDispatcher::Publish(EVT_OGRE_CAMERA_CONSTRUCTED, qCamera);

	// Return QualifiedName of new Ogre::Camera
	return qCamera;
}
Ogre::Camera* CameraInterface::GetPtr(QualifiedName qCamera)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneNode
	if ( !qCamera.IsValid() ) return 0;

	// Get Ogre::Entity and return it (or null)
	return this->mObjectAccess->GetCamera(qCamera);
}
