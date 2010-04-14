#ifndef SELECTION_MANAGER_H_
#define SELECTION_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/tokenzr.h> 
#include <wx/propgrid/propgrid.h>
#include <wx/valtext.h>

#include "../OViSEAux/MovableTypeTranslator.h"
#include "../QualifiedNames/QualifiedName.h"
#include "../QualifiedNames/QualifiedNameCollection.h"
#include "../OgreMediator/OgreMediator.h"
#include "../OViSEAux/Logging.h"

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

	// Handle property changing
	wxPGProperty* ChangedProperty;

	// Attributes: construction of wxPropertyGrid
	wxPropertyGrid* PG;
	wxPropertyCategory* PCSelection;

	// Methods: construction of wxPropertyGrid
	bool AddNOTIMPLEMENTED();
	bool AddCamera(Ogre::Camera* C);
	bool AddEntity(Ogre::Entity* E);
	bool AddLight(Ogre::Light* L);
	wxPropertyCategory* AddSceneNode(Ogre::SceneNode* SN);
	bool AddMovableObject(Ogre::MovableObject* MO);

public:
	// De- & Constructors
	~SelectionManager(void);

	// Get-/Set-Methods of attributes
	wxPropertyGrid* GetPropertyGrid();
	void SetPropertyGrid(wxPropertyGrid* PG);

	// Singleton
	static SelectionManager* getSingletonPtr();
	
	// General methods
	bool IsValid();

	// Selection
	QualifiedNameCollection Selection;
	
	// Methods: selection
	bool IsSelected(QualifiedName qName);

	// Methods: construction of wxPropertyGrid
	bool GeneratePropertyGridContentFromSelection();
	bool GeneratePropertyGridContentFromSelection(wxString SelectionUniqueName);
	bool GeneratePropertyGridContentFromSelection(QualifiedNameCollection Selection);

	// Attributes: handle OnPropertyChanged(...)
	HashMap_wxString PGIDRegister;

	// Methods: handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
	bool HandlePropertyChanged(wxPGProperty* ChangedProperty);
	bool HandleSceneNodeChanged(QualifiedName qSceneNode, wxString subPGID);
	bool HandleSceneNodeChanged(Ogre::SceneNode* SN, wxString subPGID);
	bool HandleCameraChanged(QualifiedName qCamera, wxString subPGID);
	bool HandleCameraChanged(Ogre::Camera* C, wxString subPGID);
	bool HandleEntityChanged(QualifiedName qEntity, wxString subPGID);
	bool HandleEntityChanged(Ogre::Entity* E, wxString subPGID);
	bool HandleLightChanged(QualifiedName qLight, wxString subPGID);
	bool HandleLightChanged(Ogre::Light* L, wxString subPGID);
	bool HandlePositionChanged(Ogre::SceneNode* SN);
	bool HandleScaleChanged(Ogre::SceneNode* SN);
	bool HandleRotationChanged(Ogre::SceneNode* SN);
	bool HandleLightDirectionChanged(Ogre::Light* L);
	bool HandleLightDiffuseColourChanged(Ogre::Light* L);
	bool HandleLightSpecularColourChanged(Ogre::Light* L);
};

#endif // SELECTION_MANAGER_H_