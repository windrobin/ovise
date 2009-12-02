#pragma once

#include "../OgreMediator/MediatorInterface.h"
#include "../OgreMediator/MovableObjectInterface.h"

class SceneNodeInterface : public MediatorInterface
{
private:
	MovableObjectInterface*	iMovableObject;

public:
	// De- & Constructors, individual
	SceneNodeInterface(MovableObjectInterface* iMovableObject = 0, ObjectManager* ObjMgr = 0);
	virtual ~SceneNodeInterface(void);

	// Methods, inherited and overwritten
	QualifiedName		Create(wxString Name);
	bool				Destroy(QualifiedName qName);
	bool				Exist(QualifiedName qName);
	bool				IsValid();

	// Methods, individual
	QualifiedName		Create(wxString Name, QualifiedName qParentSceneNode);
	QualifiedName		Create(wxString Name, Ogre::SceneNode* pParentSceneNode);
	QualifiedName		GetName(Ogre::SceneNode* pSceneNode);
	Ogre::SceneNode*	GetPtr(QualifiedName qSceneNode);

	// Methods, individual, configuration
	bool				SetMovableObjectInterface(MovableObjectInterface* iMovableObject);
};
