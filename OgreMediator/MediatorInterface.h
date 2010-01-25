#pragma once

#ifndef MEDIATOR_INTERFACE_H_
#define MEDIATOR_INTERFACE_H_

// Include WX
#include <wx/string.h>

// Include Ogre
#include "Ogre.h"

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/MovableTypeTranslator.h"
#include "../QualifiedNames/QualifiedNameCollection.h"
#include "../OgreMediator/ObjectManager.h"
#include "../ImprovedEventHandling/EventDispatcher.h"

class MediatorInterface
{
protected:
	// ObjectManager
	ObjectManager*	mObjectAccess;

public:
	// De- & Constructors
	MediatorInterface(ObjectManager* ObjMgr = 0);
	virtual ~MediatorInterface(void);

	// General
	virtual bool	IsValid();

	// ObjectManager
	bool			SetObjectManager(ObjectManager* ObjMgr);

	virtual bool	Destroy(QualifiedName qName) = 0;
	virtual bool	Exist(QualifiedName qName) = 0;
};

#endif // MEDIATOR_INTERFACE_H_