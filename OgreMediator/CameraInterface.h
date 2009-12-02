#pragma once

#include "../OgreMediator/MovableObjectInterface.h"

class CameraInterface : public MovableObjectInterface
{
public:
	// De- & Constructors, individual
	CameraInterface(ObjectManager* ObjMgr = 0);
	virtual ~CameraInterface(void);

	// Methods, inherited and overwritten
	bool			Destroy(QualifiedName qName);
	bool			Exist(QualifiedName qName);

	// Methods, individual
	QualifiedName	Create(wxString Name);
	QualifiedName	Create(wxString Name, QualifiedName qAnchorSceneNode);
	QualifiedName	Create(wxString Name, Ogre::SceneNode* pAnchorSceneNode);
	Ogre::Camera*	GetPtr(QualifiedName qCamera);
};
