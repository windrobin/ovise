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

	/** Add a grid to the scene. Gridsize is adjustable and it can be attached to any node.
	 * By default the grid is aligned in the x-z-plane. To change that create a scene node for the grid
	 * and rotate it for your needs.
	 * @param size Defines the length of a grid unit
	 * @param numRows Number of rows of the grid
	 * @param numCols Number of columns for the grid
	 * @param col Color of the grid - RGB (0.0-1.0)
	 * @param qSceneManager Name of the scenemanager the grid should be added to
	 * @param qSceneNode Defines the node the grid should be attached to, defaults to the root node
	 */
	void AddGrid(int size, int numRows, int numCols, Ogre::Vector3 col, QualifiedName qSceneManager, QualifiedName qSceneNode);

	/** Adds a mesh depicting a coordinate system.
	 * @param qSceneManager scenemanager the coordinate system will be added to.
	 * @param qSceneNode Defines the SceneNode the coordinate system shall be attached to. Defaults to the root node.
	 */
	void AddCOS(QualifiedName qSceneManager, QualifiedName qSceneNode, float scale = 1.0, bool castShadows=false);
};

#endif // OGRE_API_MEDIATOR_H_