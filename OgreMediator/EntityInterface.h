#pragma once

#include "../OgreMediator/MovableObjectInterface.h"

// Include WX
#include <wx/filename.h>

class EntityInterface : public MovableObjectInterface
{
public:
	// De- & Constructors, individual
	EntityInterface(ObjectManager* ObjMgr = 0);
	virtual ~EntityInterface(void);

	// Methods, inherited and overwritten
	bool			Destroy(QualifiedName qName);
	bool			Exist(QualifiedName qName);

	// Methods, individual
	QualifiedName	Create(wxString Name, wxString MeshFile);
	QualifiedName	Create(wxString Name, wxString MeshFile, QualifiedName qAnchorSceneNode);
	QualifiedName	Create(wxString Name, wxString MeshFile, Ogre::SceneNode* pAnchorSceneNode);
	Ogre::Entity*	GetPtr(QualifiedName qEntity);
};
