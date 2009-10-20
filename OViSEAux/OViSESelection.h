#pragma once

#ifndef OVISESELECTION_H_
#define OVISESELECTION_H_

// Include WX
#include <wx/hashmap.h>
#include <wx/arrstr.h> 

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/EnumTranslator_MovableType.h"
#include "../OViSEAux/OgreAPIMediator.h"

// Include Ogre
#include <Ogre.h>

class OViSESelection
{
private:
	// General attributes
	wxString UniqueName;
	wxString SceneManagerName;
	bool Valid;

public:
	// Attributes
	OViSEOgreEnums::HashMap_Enums_MovableType_ByString SelectedObjects;

	// De- & Constructors
	OViSESelection();
	OViSESelection(wxString SceneManagerName);
	~OViSESelection(void);
	
	// General Methods
	bool isValid();
	
	void setUniqueName(wxString UniqueName);
	wxString getUniqueName();
	
	// Methods
	bool hasMovableObject(wxString MovableObjectName);
	bool addMovableObject(wxString MovableObjectName, OViSEOgreEnums::MovableObject::MovableType MovableObjectType);
	bool removeMovableObject(wxString MovableObjectName);
	void removeAll();
	wxArrayString getAllMovableObjectNames();


	wxString getSceneManagerName();
	void setSceneManagerName(wxString SceneManagerName);
};

#endif // OVISESELECTION_H_