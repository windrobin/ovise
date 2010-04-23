#pragma once

#include "../OgreMediator/MovableObjectInterface.h"
#include "../ImprovedEventHandling/EventPublisherInterface.h"

class LightInterface :
	public MovableObjectInterface,
	public EventPublisherInterface
{
public:
	// De- & Constructors, individual
	LightInterface(ObjectManager* ObjMgr = 0);
	virtual ~LightInterface(void);

	// Methods, inherited and overwritten
	bool			Destroy(QualifiedName qName);
	bool			Exist(QualifiedName qName);

	// Methods, individual
	QualifiedName	Create(wxString Name);
	QualifiedName	Create(wxString Name, QualifiedName qAnchorSceneNode);
	QualifiedName	Create(wxString Name, Ogre::SceneNode* pAnchorSceneNode);
	Ogre::Light*	GetPtr(QualifiedName qLight);
};
