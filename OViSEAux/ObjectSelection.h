#pragma once

#ifndef OBJECTSELECTION_H_
#define OBJECTSELECTION_H_

// Include WX
#include <wx/hashmap.h>
#include <wx/arrstr.h> 

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/MovableTypeTranslator.h"
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/QualifiedNameCollectionInterface.h"
#include "../OViSEAux/OgreAPIMediator.h"

// Include Ogre
#include <Ogre.h>

class ObjectSelection
{
private:
	// General attributes
	wxString UniqueName;
	QualifiedName mSceneManager;
	bool Valid;

public:
	// Attributes
	QualifiedNameCollection SelectedObjects;

	// De- & Constructors
	ObjectSelection();
	ObjectSelection(QualifiedName qSceneManager);
	~ObjectSelection(void);
	
	// General Methods
	bool IsValid();
	
	//void setUniqueName(wxString UniqueName);
	//wxString getUniqueName();
	
	// Methods
	bool HasMovableObject(QualifiedName qMovableObject);
	bool AddMovableObject(QualifiedName qMovableObject);
	bool removeMovableObject(wxString MovableObjectName);
	void removeAll();
	wxArrayString getAllMovableObjectNames();


	QualifiedName GetSceneManager();
	void SetSceneManager(QualifiedName qSceneManager);
};

#endif // OBJECTSELECTION_H_