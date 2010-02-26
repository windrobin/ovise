#pragma once

// Include WX
#include <wx/hashmap.h>

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../QualifiedNames/QualifiedNameCollection.h"

#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/MovableTypeTranslator.h"
#include "../OViSEAux/ObjectTitle.h"

// Include Ogre
#include "Ogre.h"

WX_DECLARE_STRING_HASH_MAP(Ogre::Camera*, CameraHashMap);
WX_DECLARE_STRING_HASH_MAP(Ogre::Entity*, EntityHashMap);
WX_DECLARE_STRING_HASH_MAP(Ogre::Light*, LightHashMap);
WX_DECLARE_STRING_HASH_MAP(Ogre::SceneManager*, SceneManagerHashMap);
WX_DECLARE_STRING_HASH_MAP(Ogre::SceneNode*, SceneNodeHashMap);
WX_DECLARE_STRING_HASH_MAP(Ogre::RaySceneQuery*, RaySceneQueryHashMap);

/// Map containing object title instances (for updating in the frame listener)
typedef std::vector<ObjectTitle*> ObjectTitleVector;

class ObjectManager
{
private:
	QualifiedNameHashMap mQNames; // Lookup-table: get QualifiedName of an object by its UniqueName
	QualifiedNameHashMap mAssociatedSceneManagers; // Lookup-table: get QualifiedName of an object's SceneManager by object's UniqueName

	CameraHashMap		 mCameras;
	EntityHashMap		 mEntities;
	LightHashMap		 mLights;
	SceneManagerHashMap  mSceneManagers;
	SceneNodeHashMap	 mSceneNodes;
	RaySceneQueryHashMap mRaySceneQuery;

	OgreEnums::MovableTypeByStringHashMap mMovableTypeEnums;

	// NEW
	QualifiedName mActiveSceneManager;

	ObjectTitleVector mObjectTitlesVector;

public:
	ObjectManager(void);
	~ObjectManager(void);

	// General
	QualifiedName			GetQualifiedNameOfObject(wxString UniqueName);
	bool					RemoveUnidentifiedObject(QualifiedName QName);

	// Accociadted SceneManager // Delivers quick access to a Ogre-objects hosting/associated Ogre::SceneManager
	bool					AddAssociatedSceneManager(QualifiedName qSceneManager, QualifiedName qObject);
	bool					RemoveAssociatedSceneManager(QualifiedName qObject);
	QualifiedName			GetAssociatedSceneManager(QualifiedName qObject);

	// Ogre::Camera
	bool					AddCamera(QualifiedName QName, Ogre::Camera* pCamera);
	bool					RemoveCamera(QualifiedName QName);
	Ogre::Camera*			GetCamera(QualifiedName QName);
	QualifiedNameCollection GetCameras();

	// Ogre::Entity
	bool					AddEntity(QualifiedName QName, Ogre::Entity* pEntity);
	bool					RemoveEntity(QualifiedName QName);
	Ogre::Entity*			GetEntity(QualifiedName QName);
	QualifiedNameCollection GetEntities();

	// Ogre::Light
	bool					AddLight(QualifiedName QName, Ogre::Light* pLight);
	bool					RemoveLight(QualifiedName QName);
	Ogre::Light*			GetLight(QualifiedName QName);
	QualifiedNameCollection GetLights();

	// Ogre::SceneManager
	bool					AddSceneManager(QualifiedName QName, Ogre::SceneManager* pSceneManager);
	bool					RemoveSceneManager(QualifiedName QName);
	Ogre::SceneManager*		GetSceneManager(QualifiedName QName);
	QualifiedNameCollection GetSceneManagers();

	// Ogre::SceneNode
	bool					AddSceneNode(QualifiedName QName, Ogre::SceneNode* pSceneNode);
	bool					RemoveSceneNode(QualifiedName QName);
	Ogre::SceneNode*		GetSceneNode(QualifiedName QName);
	QualifiedNameCollection GetSceneNodes();

	// Ogre::MovableObject (abtract)
	bool									RemoveMovableObject(QualifiedName QName);
	Ogre::MovableObject*					GetMovableObject(QualifiedName QName);
	OgreEnums::MovableObject::MovableType	GetMovableType(QualifiedName QName);

	// Ogre::SceneQuery
	bool					AddRaySceneQuery(QualifiedName qSceneManager, Ogre::RaySceneQuery* pRaySceneQuery);
	bool					RemoveRaySceneQuery(QualifiedName qSceneManager);
	Ogre::RaySceneQuery*	GetRaySceneQuery(QualifiedName qSceneManager);

	// NEW
	bool					SetActiveSceneManager(QualifiedName qSceneManager);
	QualifiedName			GetActiveSceneManager(); // There is anytime one!

	/** Show graph relations.
	 *  Function shows a graphical representation of the scene graph using lines and spheres.
	 */
	void					ShowSceneGraphStructure(QualifiedName qSceneManager, bool update = false);

	/** Updates the object titles in the internal map.
	*/
	void					UpdateObjectTitles();
};
