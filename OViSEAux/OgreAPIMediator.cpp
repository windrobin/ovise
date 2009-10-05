#include "OgreAPIMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreAPIMediator* OgreAPIMediator::instance = 0;

OgreAPIMediator* OgreAPIMediator::GetSingletonPtr()
{
	if (OgreAPIMediator::instance == 0) OgreAPIMediator::instance = new OgreAPIMediator();
	return OgreAPIMediator::instance;
}

OgreAPIMediator::OgreAPIMediator()
{
	this->Valid = false;

	this->CameraNameMgr = new UniqueNameManager(ToWxString("Camera"));
	this->EntityNameMgr = new UniqueNameManager(ToWxString("Entity"));
	this->LightNameMgr = new UniqueNameManager(ToWxString("Light"));
	this->SceneNodeNameMgr = new UniqueNameManager(ToWxString("SceneNode"));

	this->OgreChanged = false;

	this->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OgreAPIMediator::OnOgreChanged ), NULL, this);
}

OgreAPIMediator::~OgreAPIMediator(void)
{
	delete this->CameraNameMgr;
	delete this->EntityNameMgr;
	delete this->LightNameMgr;
	delete this->SceneNodeNameMgr;
}

// General
bool OgreAPIMediator::IsValid() { return this->Valid; }

// Get & Set properies
Ogre::SceneManager* OgreAPIMediator::GetSceneManagerByRef() { return this->SceneMgr; }
wxString OgreAPIMediator::GetSceneManagerByName() { return this->SceneMgrName; }

bool OgreAPIMediator::SetSceneManagerByRef(Ogre::SceneManager* SceneMgr)
{
	this->SceneMgr = SceneMgr;

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(this->SceneMgr->getName());
	}
	if (SceneMgr == 0)
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}
bool OgreAPIMediator::SetSceneManagerByName(wxString SceneMgrName)
{
	this->SceneMgr = 0;
	this->SceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(SceneMgrName));

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(SceneMgrName);
	}
	else
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}

void OgreAPIMediator::SendSelectionChanged()
{
	/*
	wxCommandEvent event(OViSE_EVT_SELECTION_CHANGED, this->GetId());
	event.SetEventObject(this);
	this->GetEventHandler();
	*/
}
void OgreAPIMediator::SendOgreChanged()
{
	if ( this->OgreChanged )
	{
		wxCommandEvent event(OViSE_EVT_OGRE_CHANGED, this->GetId());
		event.SetEventObject(this);
		this->GetEventHandler()->ProcessEvent(event);
	}
}

void OgreAPIMediator::OnOgreChanged(wxCommandEvent& event)
{
	if(this->Valid)
	{
		this->OgreChanged = false;		
	}
}

// API to Ogre
Ogre::Camera* OgreAPIMediator::AddCamera(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = this->CameraNameMgr->AllocateUniqueName(NotUniqueName);

	Ogre::Camera* C = this->SceneMgr->createCamera(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(C);
	else AttachToThisNode->attachObject(C);
	this->OgreChanged = true;
	return C;
}

Ogre::Entity* OgreAPIMediator::AddEntity(wxString NotUniqueName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = this->EntityNameMgr->AllocateUniqueName(NotUniqueName);

	Ogre::Entity* E = this->SceneMgr->createEntity(ToOgreString(UniqueName), ToOgreString(MeshFile));
	if (AttachToThisNode == 0) this->SceneMgr->getRootSceneNode()->attachObject(E);
	else AttachToThisNode->attachObject(E);
	this->OgreChanged = true;
	return E;
}

Ogre::Light* OgreAPIMediator::AddLight(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = this->LightNameMgr->AllocateUniqueName(NotUniqueName);

	Ogre::Light* L = this->SceneMgr->createLight(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(L);
	else AttachToThisNode->attachObject(L);
	this->OgreChanged = true;
	return L;
}

Ogre::SceneNode* OgreAPIMediator::AddSceneNode(wxString NotUniqueName, Ogre::SceneNode* ParentNode)
{
	if (!this->Valid) return 0;

	wxString UniqueName = this->SceneNodeNameMgr->AllocateUniqueName(NotUniqueName);

	Ogre::SceneNode* NewSN = 0;
	if (ParentNode == 0) NewSN = this->SceneMgr->getRootSceneNode()->createChildSceneNode(ToOgreString(UniqueName));
	else NewSN = ParentNode->createChildSceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return NewSN;
}

bool OgreAPIMediator::RemoveCamera(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasCamera(ToOgreString(UniqueName))) return false;

	this->CameraNameMgr->DeallocateUniqueName(UniqueName);

	Ogre::Camera* C = this->SceneMgr->getCamera(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = C->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyCamera(C);
	this->OgreChanged = true;
	return true;
}

bool OgreAPIMediator::RemoveEntity(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasEntity(ToOgreString(UniqueName))) return false;

	this->EntityNameMgr->DeallocateUniqueName(UniqueName);
	Ogre::Entity* E = this->SceneMgr->getEntity(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = E->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyEntity(E);
	this->OgreChanged = true;
	return true;
}

bool OgreAPIMediator::RemoveLight(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasLight(ToOgreString(UniqueName))) return false;

	this->LightNameMgr->DeallocateUniqueName(UniqueName);

	Ogre::Light* L = this->SceneMgr->getLight(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = L->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyLight(L);
	this->OgreChanged = true;
	return true;
}

bool OgreAPIMediator::RemoveSceneNode(wxString UniqueName, bool RemoveRecursive)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasSceneNode(ToOgreString(UniqueName))) return false;

	if (RemoveRecursive) ; // Not implemented yet.
	else ;

	this->SceneNodeNameMgr->AllocateUniqueName(UniqueName);

	this->SceneMgr->destroySceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return true;
	
}


