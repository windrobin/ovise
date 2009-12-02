#include "../OgreMediator/MovableObjectInterface.h"

// De- & Constructors, individual
MovableObjectInterface::MovableObjectInterface(ObjectManager* ObjMgr) : MediatorInterface(ObjMgr) { }
MovableObjectInterface::~MovableObjectInterface(void) { }
// Methods, inherited and overwritten
bool MovableObjectInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::Camera
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get MovableObject
	Ogre::MovableObject* MO = this->mObjectAccess->GetMovableObject(qName);
	
	// Get SceneNode
	Ogre::SceneNode* SN = MO->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveMovableObject(qName);

	// Destroy Ogre::MovableObject
	SN->detachObject(MO);
	SM->destroyMovableObject(MO);

	// Destroy QualifiedName of Ogre::MovableObject
	QualifiedName::Destroy(qName);

	// Flag Ogre-engine as chanced
	this->mOgreChanged = true;

	return true;
}
bool MovableObjectInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a SceneNode
	if ( this->mObjectAccess->GetMovableObject(qName) == 0 ) return false;

	return true;
}
bool MovableObjectInterface::IsValid()
{
	if( !MediatorInterface::IsValid() ) return false;
	if( !this->mObjectAccess->GetActiveSceneManager().IsValid() ) return false;
	if( this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager()) == 0 ) return false;

	return true;
}
// Methods, individual
QualifiedName MovableObjectInterface::GetName(Ogre::MovableObject* pMovableObject)
{
	wxString UniqueName = ToWxString(pMovableObject->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
Ogre::MovableObject* MovableObjectInterface::GetPtr(QualifiedName qMovableObject)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qMovableObject
	if ( !qMovableObject.IsValid() ) return 0;

	// Get Ogre::MovableObject and return it (or null)
	return this->mObjectAccess->GetMovableObject(qMovableObject);
}
