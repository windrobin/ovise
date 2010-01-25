#include "../OgreMediator/OgreMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreMediator* OgreMediator::instance = 0;
OgreMediator* OgreMediator::GetSingletonPtr()
{
	if (OgreMediator::instance == 0){
		OgreMediator::instance = new OgreMediator();
		// Create default SceneManager
	OgreMediator::instance->mDefaultSceneManager = OgreMediator::instance->iSceneManager.Create(ToWxString("Default"));

	// Set it as ActiveSceneManager
	OgreMediator::instance->iSceneManager.SetActiveSceneManager(OgreMediator::instance->mDefaultSceneManager);

	// Create and store RaySceneQuery
	OgreMediator::instance->iSceneManager.CreateRaySceneQuery(OgreMediator::instance->mDefaultSceneManager);

	// Create and store RootSceneNode
	OgreMediator::instance->iSceneNode.Create(ToWxString(OgreMediator::instance->iSceneManager.GetPtr(OgreMediator::instance->mDefaultSceneManager)->getRootSceneNode()->getName()));
	}
	return OgreMediator::instance;
}
OgreMediator::OgreMediator()
{
	this->Valid = true;

	this->mObjectAccess = new ObjectManager();

	this->iCamera = CameraInterface(this->mObjectAccess);
	this->iEntity = EntityInterface(this->mObjectAccess);
	this->iLight = LightInterface(this->mObjectAccess);
	this->iMovableObject = MovableObjectInterface(this->mObjectAccess);
	this->iSceneNode = SceneNodeInterface(&(this->iMovableObject), this->mObjectAccess);
	this->iSceneManager = SceneManagerInterface(&(this->iSceneNode), this->mObjectAccess);
}
OgreMediator::~OgreMediator(void) { this->iSceneManager.Destroy(this->mDefaultSceneManager); }
// General
bool OgreMediator::IsValid() { return this->Valid; }
ObjectManager* OgreMediator::GetObjectAccess() { return this->mObjectAccess; }
