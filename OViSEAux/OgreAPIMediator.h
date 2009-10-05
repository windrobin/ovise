#pragma once

// Include WX
#include <wx/string.h>
#include <wx/event.h>
#include <wx/control.h>

// Solution's includes
#include "./UniqueNameManagerCollection.h"
#include "./StringConverter.h"
#include "./UniqueNameManager.h"

// Include Ogre
#include "Ogre.h"


BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED, wxNewEventType())
END_DECLARE_EVENT_TYPES()

class OgreAPIMediator : public wxControl
{
private:
	//DECLARE_EVENT_TABLE()

	// De- & Constructors
	OgreAPIMediator();
	OgreAPIMediator(const OgreAPIMediator&);
	~OgreAPIMediator(void);

	// Singleton
	static OgreAPIMediator* instance;

	// General
	bool Valid;

	// Attributes, used in implicid name-management
	UniqueNameManager* CameraNameMgr;
	UniqueNameManager* EntityNameMgr;
	UniqueNameManager* LightNameMgr;
	UniqueNameManager* SceneNodeNameMgr;

	// Attributes, used for access to ogre
	Ogre::SceneManager* SceneMgr;
	wxString SceneMgrName;

	// Attributes, used for update-priority
	bool OgreChanged;

public:
	// Singleton
	static OgreAPIMediator* GetSingletonPtr();
	
	// General
	bool IsValid();

	// Get & Set properies
	Ogre::SceneManager* GetSceneManagerByRef();
	wxString GetSceneManagerByName();
	bool SetSceneManagerByRef(Ogre::SceneManager* SceneMgr);
	bool SetSceneManagerByName(wxString SceneMgrName);

	// wxEvent handling
	void SendSelectionChanged();
	void SendOgreChanged();
	void OnOgreChanged(wxCommandEvent& event);

	// API to Ogre
	Ogre::Camera*		AddCamera(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::Entity*		AddEntity(wxString NotUniqueName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::Light*		AddLight(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::SceneNode*	AddSceneNode(wxString NotUniqueName, Ogre::SceneNode* ParentNode = 0);
	bool RemoveCamera(wxString UniqueName);
	bool RemoveEntity(wxString UniqueName);
	bool RemoveLight(wxString UniqueName);
	bool RemoveSceneNode(wxString UniqueName, bool RemoveRecursive = true);
};
