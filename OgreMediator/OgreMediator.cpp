#include "../OgreMediator/OgreMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreMediator* OgreMediator::instance = 0;

OgreMediator* OgreMediator::GetSingletonPtr()
{
	if (OgreMediator::instance == 0) OgreMediator::instance = new OgreMediator();
	return OgreMediator::instance;
}
OgreMediator::OgreMediator()
{
	this->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OgreMediator::OnOgreChanged ), NULL, this);

	this->Valid = true;

	this->mObjectAccess = new ObjectManager();

	this->iCamera = CameraInterface(this->mObjectAccess);
	this->iEntity = EntityInterface(this->mObjectAccess);
	this->iLight = LightInterface(this->mObjectAccess);
	this->iMovableObject = MovableObjectInterface(this->mObjectAccess);
	this->iSceneNode = SceneNodeInterface(&(this->iMovableObject), this->mObjectAccess);
	this->iSceneManager = SceneManagerInterface(&(this->iSceneNode), this->mObjectAccess);

	// Create default SceneManager
	this->mDefaultSceneManager = this->iSceneManager.Create(ToWxString("Default"));

	// Set it as ActiveSceneManager
	this->iSceneManager.SetActiveSceneManager(this->mDefaultSceneManager);

	// Create and store RaySceneQuery
	this->iSceneManager.CreateRaySceneQuery(this->mDefaultSceneManager);

	this->mOgreChanged = false;
}
OgreMediator::~OgreMediator(void) { this->iSceneManager.Destroy(this->mDefaultSceneManager); }
// General
bool OgreMediator::IsValid() { return this->Valid; }
ObjectManager* OgreMediator::GetObjectAccess() { return this->mObjectAccess; }
void OgreMediator::SendSelectionChanged()
{
	/*
	wxCommandEvent event(OViSE_EVT_SELECTION_CHANGED, this->GetId());
	event.SetEventObject(this);
	this->GetEventHandler();
	*/
}
void OgreMediator::SendOgreChanged()
{
	if ( this->mOgreChanged )
	{
		wxCommandEvent event(OViSE_EVT_OGRE_CHANGED, this->GetId());
		event.SetEventObject(this);
		this->GetEventHandler()->ProcessEvent(event);
	}
}
void OgreMediator::OnOgreChanged(wxCommandEvent& event)
{
	if(this->Valid)
	{
		this->mOgreChanged = false;		
	}
}


