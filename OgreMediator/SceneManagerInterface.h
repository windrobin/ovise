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
	QualifiedName		Create(wxString Name);
	bool				Destroy(QualifiedName qName);
	bool				Exist(QualifiedName qName);
	bool				IsValid();

	// Methods, individual
	QualifiedName		Create(wxString Name, Ogre::SceneType pSceneType);
	QualifiedName		GetName(Ogre::SceneManager* pSceneManager);
	Ogre::SceneManager*	GetPtr(QualifiedName qSceneManager);

	// Methods, individual, active Ogre::SceneManager
	bool				SetActiveSceneManager(QualifiedName qSceneManager);
	QualifiedName		GetActiveSceneManager();

	// Methods, individual, configuration
	bool				SetSceneNodeInterface(SceneNodeInterface* iSceneNode);
};
