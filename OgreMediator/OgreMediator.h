#pragma once

#ifndef OGRE_API_MEDIATOR_H_
#define OGRE_API_MEDIATOR_H_

// Include WX
#ifdef __WXMSW__
#include "wx/msw/winundef.h"
#endif
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
#include "../OgreMediator/ObjectManager.h"
#include "../OgreMediator/SceneManagerInterface.h"
#include "../OgreMediator/SceneNodeInterface.h"
#include "../OgreMediator/MovableObjectInterface.h"
#include "../OgreMediator/CameraInterface.h"
#include "../OgreMediator/EntityInterface.h"
#include "../OgreMediator/LightInterface.h"

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED, wxNewEventType())
END_DECLARE_EVENT_TYPES()

class OgreMediator : public wxControl
{
private:
	// De- & Constructors
	OgreMediator();

	// Singleton
	static OgreMediator*	instance;

	// General
	bool Valid;
	QualifiedName			mDefaultSceneManager;
	ObjectManager*			mObjectAccess;

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
	ObjectManager*			GetObjectAccess();
};

#endif // OGRE_API_MEDIATOR_H_