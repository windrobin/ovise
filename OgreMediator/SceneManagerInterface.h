#pragma once

#include "../OgreMediator/MediatorInterface.h"
#include "../OgreMediator/SceneNodeInterface.h"

class SceneManagerInterface : public MediatorInterface
{
private:
	SceneNodeInterface*	iSceneNode;

public:
	// De- & Constructors, individual
	SceneManagerInterface(SceneNodeInterface* iSceneNode = 0, ObjectManager* ObjMgr = 0);
	virtual ~SceneManagerInterface(void);

	// Methods, inherited and overwritten
	QualifiedName			Create(wxString Name);
	bool					Destroy(QualifiedName qName);
	bool					Exist(QualifiedName qName);
	bool					IsValid();

	// Methods, individual
	QualifiedName			Create(wxString Name, Ogre::SceneType pSceneType);
	QualifiedName			GetName(Ogre::SceneManager* pSceneManager);
	Ogre::SceneManager*		GetPtr(QualifiedName qSceneManager);

	// Methods, individual, active Ogre::SceneManager
	bool					SetActiveSceneManager(QualifiedName qSceneManager);
	QualifiedName			GetActiveSceneManager();

	// Methods, individual, configuration
	bool					SetSceneNodeInterface(SceneNodeInterface* iSceneNode);

	// Methods, individual, manage RaySceneQuery
	bool					CreateRaySceneQuery(QualifiedName qSceneManager);
	bool					DestroyRaySceneQuery(QualifiedName qSceneManager);
	Ogre::RaySceneQuery*	GetRaySceneQuery(QualifiedName qSceneManager);

	// Methods, individual, execute RaySceneQuery
	QualifiedNameCollection	QueryObjectsByRay(Ogre::Ray pRay, QualifiedName qSceneManager);
	QualifiedName			QueryFrontObjectByRay(Ogre::Ray pRay, QualifiedName qSceneManager);
	QualifiedName			QueryBackObjectByRay(Ogre::Ray pRay, QualifiedName qSceneManager);

	// Methods, individual, helper-methods
	Ogre::Ray				Assist_GetRayForRaySceneQuery(float screenx, float screeny, Ogre::Camera *cam);

	// Methods, individual, manage shadows
	void					DynamicShadows(QualifiedName qSceneManager, bool State);
};
