#pragma once

// Include WX
#include <wx/string.h>
#include <wx/event.h>
#include <wx/control.h>
#include <wx/arrstr.h>

#include <wx/propgrid/propgrid.h>
#include <wx/valtext.h>

// Solution's includes
#include "../OViSEAux/UniqueNameManagerCollection.h"
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/EnumTranslator_MovableType.h"
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/QualifiedNameCollectionInterface.h"
#include "../OViSEAux/ObjectManager.h"

// Include Ogre
#include "Ogre.h"

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED, wxNewEventType())
END_DECLARE_EVENT_TYPES()

class OgreAPIMediator : public wxControl
{
private:
	// De- & Constructors
	OgreAPIMediator();

	// Singleton
	static OgreAPIMediator* instance;

	// General
	bool Valid;

	// Attributes, used for access to ogre
	Ogre::SceneManager* SceneMgr;
	wxString SceneMgrName;

	// NEW
	Ogre::SceneManager* mActiveSceneManager;

	// Attributes, used for update-priority
	bool OgreChanged;

	OViSEOgreEnums::HashMap_Enums_MovableType_ByString MovableObjectVsTypeRegister; // ATTENTION: not working on different scenemanagers !!!! HR!

public:
	// De- & Constructors
	~OgreAPIMediator(void);

	// Singleton
	static OgreAPIMediator* GetSingletonPtr();
	
	// General
	bool IsValid();

	// DELETE OLD ----------------------------------------------------------------------

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
	// Get...
	wxArrayString getSceneManagerNames();

	// Get pointer
	Ogre::Camera*			getCameraPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera);
	Ogre::Entity*			getEntityPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity);
	Ogre::Light*			getLightPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight);
	Ogre::MovableObject*	getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject);
	Ogre::MovableObject*	getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OViSEOgreEnums::MovableObject::MovableType Type);
	Ogre::SceneNode*		getSceneNodePtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode);
	Ogre::SceneManager*		getSceneManagerPtr(wxString UniqueNameOfSceneManager);

	// Has objects // Markup: DOUBLE_SAFETY_DIRECTIVE
	bool hasCamera(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera);
	bool hasEntity(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity);
	bool hasLight(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight);
	bool hasMovableObject(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OViSEOgreEnums::MovableObject::MovableType Type);
	bool hasSceneNode(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode);
	bool hasSceneManager(wxString UniqueNameOfSceneManager); // Not double-save
	
	// Add objects
	Ogre::Camera*		addCamera(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::Entity*		addEntity(wxString NotUniqueName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::Light*		addLight(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode = 0);
	Ogre::SceneNode*	addSceneNode(wxString NotUniqueName, Ogre::SceneNode* ParentNode = 0);

	// Remove objects
	bool removeCamera(wxString UniqueName);
	bool removeEntity(wxString UniqueName);
	bool removeLight(wxString UniqueName);
	bool removeSceneNode(wxString UniqueName, bool RemoveRecursive = true);
	
	// DELETE OLD ----------------------------------------------------------------------

	// NEW // Attributes, public
	ObjectManager QuickObjectAccess;
	QualifiedName ActiveSceneManager;

	// NEW // Has objects?
	bool				HasCamera(QualifiedName qCamera);
	bool				HasEntity(QualifiedName qEntity);
	bool				HasLight(QualifiedName qLight);
	bool				HasSceneManager(QualifiedName qSceneManager);
	bool				HasSceneNode(QualifiedName qSceneNode);

	// NEW // Get pointer by QualifiedName
	Ogre::Camera*		GetCameraPtr(QualifiedName qCamera);
	Ogre::Entity*		GetEntityPtr(QualifiedName qEntity);
	Ogre::Light*		GetLightPtr(QualifiedName qLight);
	Ogre::SceneManager*	GetSceneManagerPtr(QualifiedName qSceneManager);
	Ogre::SceneNode*	GetSceneNodePtr(QualifiedName qSceneNode);

	// NEW // Get QualifiedName by pointer
	QualifiedName*		GetQualifiedName(Ogre::Camera* pCamera);
	QualifiedName*		GetQualifiedName(Ogre::Entity* pEntity);
	QualifiedName*		GetQualifiedName(Ogre::Light* pLight);
	QualifiedName*		GetQualifiedName(Ogre::SceneManager* pSceneManager);
	QualifiedName*		GetQualifiedName(Ogre::SceneNode* pSceneNode);

	// NEW // Create objects
	QualifiedName*		CreateCamera(wxString Name, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateEntity(wxString Name, wxString MeshFile, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateLight(wxString Name, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateSceneManager(wxString Name);
	QualifiedName*		CreateSceneNode(wxString Name, Ogre::SceneNode* ParentNode = 0);

	QualifiedName*		CreateCamera(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateEntity(QualifiedName qSceneManager, wxString Name, wxString MeshFile, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateLight(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* AttachToThisNode = 0);
	QualifiedName*		CreateSceneManager(wxString Name, Ogre::SceneType Type);
	QualifiedName*		CreateSceneNode(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* ParentNode = 0);

	// NEW // Destroy objects
	bool				DestroySceneManager();

	bool				DestroyCamera(QualifiedName qCamera);
	bool				DestroyEntity(QualifiedName qEntity);
	bool				DestroyLight(QualifiedName qLight);
	bool				DestroySceneManager(QualifiedName qSceneManager);
	bool				DestroySceneNode(QualifiedName qSceneNode);


	// NEW // Get selected object

};
