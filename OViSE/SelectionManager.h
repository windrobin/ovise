#pragma once

#ifndef SELECTION_MANAGER_H_
#define SELECTION_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/tokenzr.h> 
#include <wx/propgrid/propgrid.h>
#include <wx/valtext.h>

#include "../OViSEAux/MovableTypeTranslator.h"
#include "../OViSEAux/UniqueNameManagerCollection.h"
//#include "../OViSEAux/OViSESelection.h"
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/QualifiedNameCollectionInterface.h"
#include "../OViSEAux/OgreAPIMediator.h"

// Include Ogre
#include "Ogre.h"

class SelectionManager
{
private:
	// De- & Constructors
	SelectionManager(void);
	
	// Singleton
	static SelectionManager* instance;

	// General
	bool Valid;

public:
	// De- & Constructors
	~SelectionManager(void);

	// Singleton
	static SelectionManager* getSingletonPtr();
	
	// General methods
	bool IsValid();

	// Selection
	QualifiedNameCollection Selection;
	
	// Selection methods
	bool IsSelected(QualifiedName qName);

	// wxPropertyGrid-Handling
	bool AddNOTIMPLEMENTEDToPGCategory(wxPropertyCategory* PC);
	bool AddCameraToPGCategory(wxPropertyCategory* PC, Ogre::Camera* C);
	bool AddEntityToPGCategory(wxPropertyCategory* PC, Ogre::Entity* E);
	bool AddLightToPGCategory(wxPropertyCategory* PC, Ogre::Light* L);
	bool AddSceneNodeToPGCategory(wxPropertyCategory* PC, Ogre::SceneNode* SN, QualifiedName qMovableObject);
	bool AddMovableObjectToPG(wxPropertyGrid* PG, Ogre::MovableObject* MO);
	bool GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG);
	bool GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG, wxString SelectionUniqueName);
	bool GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG, QualifiedNameCollection Selection);

	HashMap_wxString PGIDRegister;

	// Handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
	bool HandlePropertyChanged(wxPGProperty* ChangedProperty);
	bool HandleEntityChanged(QualifiedName qEntity, wxString subPGID, wxVariant value);
	bool HandleEntityChanged(Ogre::Entity* E, wxString subPGID, wxVariant value);
	bool HandlePositionChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
	bool HandleScaleChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
	bool HandleRotationChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
};

#endif // SELECTION_MANAGER_H_