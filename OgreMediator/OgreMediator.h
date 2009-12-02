#pragma once

#ifndef OGRE_API_MEDIATOR_H_
#define OGRE_API_MEDIATOR_H_

// Include WX
#include <wx/string.h>
#include <wx/event.h>
#include <wx/control.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

#include <wx/propgrid/propgrid.h>
#include <wx/valtext.h>

// Include Ogre
#include "Ogre.h"

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/MovableTypeTranslator.h"
#include "../QualifiedNames/QualifiedNameCollection.h"
#include "../OViSEAux/ObjectManager.h"
#include "../OgreMediator/SceneManagerInterface.h"
#include "../OgreMediator/SceneNodeInterface.h"
#include "../OgreMediator/MovableObjectInterface.h"
#include "../OgreMediator/CameraInterface.h"
#include "../OgreMediator/EntityInterface.h"
#include "../OgreMediator/LightInterface.h"

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED, wxNewEventType())
END_DECLARE_EVENT_TYPES()

// NEW - from OViSESceneHandling
WX_DECLARE_STRING_HASH_MAP(Ogre::RaySceneQuery*, RaySceneQueryHashMap);


class OgreMediator : public wxControl
{
private:
	// De- & Constructors
	OgreMediator();

	// Singleton
	static OgreMediator* instance;

	// General
	bool Valid;
	QualifiedName mDefaultSceneManager;

	// Attributes, used for access to ogre
	Ogre::SceneManager* SceneMgr;
	wxString SceneMgrName;

	// CHECK
	QualifiedName mActiveSceneManager;
	Ogre::SceneManager* mActiveSceneManagerPtr;
	RaySceneQueryHashMap mSceneQuerys;

	// NEW
	ObjectManager*			mObjectAccess;

	// NEW // Attributes, used for update-priority
	bool mOgreChanged;

	OgreEnums::MovableTypeByStringHashMap MovableObjectVsTypeRegister; // ATTENTION: not working on different scenemanagers !!!! HR!

public:
	// De- & Constructors
	~OgreMediator(void);

	// Singleton
	static OgreMediator*	GetSingletonPtr();
	
	// General
	bool					IsValid();

	// Attributes, public: Interfaces, "managed" access to Ogre
	SceneManagerInterface	iSceneManager;
	SceneNodeInterface		iSceneNode;
	MovableObjectInterface	iMovableObject;
	CameraInterface			iCamera;
	EntityInterface			iEntity;
	LightInterface			iLight;

	// Methods, public: access to "managed" objects
	const ObjectManager*	GetObjectAccess();

	Ogre::RaySceneQuery*	CreateRaySceneQuery(QualifiedName qSceneManager);
	Ogre::RaySceneQuery*	GetRaySceneQuery(QualifiedName qSceneManager);
	QualifiedNameCollection	GetQueryObjects(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager);
	QualifiedName			GetQueryFrontObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager);
	QualifiedName			GetQueryBackObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager);

	// NEW // from OViSESceneHandling // General
	void DynamicShadows(bool state);

	// wxEvent handling
	void SendSelectionChanged();
	void SendOgreChanged();
	void OnOgreChanged(wxCommandEvent& event);
};

#endif // OGRE_API_MEDIATOR_H_