#pragma once

#include "../OgreMediator/MediatorInterface.h"

class MovableObjectInterface : public MediatorInterface
{
public:
	// De- & Constructors, individual
	MovableObjectInterface(ObjectManager* ObjMgr = 0);
	virtual ~MovableObjectInterface(void);

	// Methods, inherited and overwritten
	virtual bool			Destroy(QualifiedName qName);
	virtual bool			Exist(QualifiedName qName);
	bool					IsValid();

	// Methods, individual
	QualifiedName			GetName(Ogre::MovableObject* pMovableObject);
	Ogre::MovableObject*	GetPtr(QualifiedName qMovableObject);
};
