#pragma once

#ifndef OVISE_SELECTION_MANAGER_H_
#define OVISE_SELECTION_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/tokenzr.h> 
#include <wx/propgrid/propgrid.h>
#include <wx/valtext.h>

#include "../OViSEAux/EnumTranslator_MovableType.h"
#include "../OViSEAux/UniqueNameManagerCollection.h"
#include "../OViSEAux/OViSESelection.h"
#include "../OViSEAux/OgreAPIMediator.h"

// Include Ogre
#include "Ogre.h"

WX_DECLARE_STRING_HASH_MAP( OViSESelection, HashMap_OViSESelection );
WX_DECLARE_STRING_HASH_MAP( wxString, HashMap_wxString );

class OViSESelectionManager
{
private:
	// De- & Constructors
	OViSESelectionManager(void);
	
	// Singleton
	static OViSESelectionManager* instance;

	// General
	bool Valid;

public:
	// De- & Constructors
	~OViSESelectionManager(void);

	// Singleton
	static OViSESelectionManager* getSingletonPtr();
	
	// General methods
	bool isValid();

	// Selection methods
	// ... still none

	// Selection
	HashMap_OViSESelection Selections; // Experimental, not implemented yet.

	OViSESelection Selection;

	// wxPropertyGrid-Handling
	bool addNOTIMPLEMENTEDToPGCategory(wxPropertyCategory* PC);
	bool addCameraToPGCategory(wxPropertyCategory* PC, Ogre::Camera* C);
	bool addEntityToPGCategory(wxPropertyCategory* PC, Ogre::Entity* E);
	bool addLightToPGCategory(wxPropertyCategory* PC, Ogre::Light* L);
	bool addSceneNodeToPGCategory(wxPropertyCategory* PC, Ogre::SceneNode* SN, wxString MOName);
	
	bool addMovableObjectToPG(wxPropertyGrid* PG, Ogre::MovableObject* MO);

	bool generatePropertyGridContentFromSelection(wxPropertyGrid* PG);
	bool generatePropertyGridContentFromSelection(wxPropertyGrid* PG, wxString SelectionUniqueName);
	bool generatePropertyGridContentFromSelection(wxPropertyGrid* PG, OViSESelection S);

	HashMap_wxString PGIDRegister;

	// Handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
	bool handlePropertyChanged(wxPGProperty* ChangedProperty);
	bool handleEntityChanged(Ogre::Entity* E, wxString subPGID, wxVariant value);
	bool handlePositionChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
	bool handleScaleChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
	bool handleRotationChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value);
};

#endif // OVISE_SELECTION_MANAGER_H_