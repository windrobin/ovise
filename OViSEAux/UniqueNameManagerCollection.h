#pragma once

#include "../OViSEAux/UniqueNameManager.h"
#include "../OViSEAux/StringConverter.h"

class UniqueNameManagerCollection
{
private:
	bool OwnCameraNameManager;
	bool OwnEntityNameManager;
	bool OwnLightNameManager;
	bool OwnPrototypeNameManager;
	bool OwnSceneNodeNameManager;

	bool OwnSelectionNameManager;
	bool OwnPropertyGridIDNameManager;

	UniqueNameManager* CameraNameMgr;
	UniqueNameManager* EntityNameMgr;
	UniqueNameManager* LightNameMgr;
	UniqueNameManager* PrototypeNameMgr;
	UniqueNameManager* SceneNodeNameMgr;

	UniqueNameManager* SelectionNameMgr;
	UniqueNameManager* PropertyGridIDNameMgr;

	// De- & Constructors
	UniqueNameManagerCollection(void);
	UniqueNameManagerCollection(UniqueNameManager* CameraNameMgr,
								UniqueNameManager* EntityNameMgr,
								UniqueNameManager* LightNameMgr,
								UniqueNameManager* PrototypeNameMgr,
								UniqueNameManager* SceneNodeNameMgr,
								UniqueNameManager* SelectionNameMgr,
								UniqueNameManager* PropertyGridIDNameMgr);
	UniqueNameManagerCollection(const UniqueNameManagerCollection& other);

	// Singleton
	static UniqueNameManagerCollection* instance;
public:
	// De- & Constructors
	~UniqueNameManagerCollection(void);

	// Singleton
	static UniqueNameManagerCollection* getSingletonPtr();

	wxString AllocateCameraName(wxString OriginalName);
	wxString AllocateEntityName(wxString OriginalName);
	wxString AllocateLightName(wxString OriginalName);
	wxString AllocatePrototypeName(wxString OriginalName);
	wxString AllocateSceneNodeName(wxString OriginalName);
	
	wxString AllocateSelectionName(wxString OriginalName);
	wxString AllocatePropertyGridIDName(wxString OriginalName);

	bool DeallocateCameraName(wxString ModifiedOriginalName);	
	bool DeallocateEntityName(wxString ModifiedOriginalName);
	bool DeallocateLightName(wxString ModifiedOriginalName);
	bool DeallocatePrototypeName(wxString ModifiedOriginalName);
	bool DeallocateSceneNodeName(wxString ModifiedOriginalName);

	bool DeallocateSelectionName(wxString ModifiedOriginalName);
	bool DeallocatePropertyGridIDName(wxString ModifiedOriginalName);

	bool isCameraName(wxString SomeString);
	bool isEntityName(wxString SomeString);
	bool isLightName(wxString SomeString);
	bool isPrototypeName(wxString SomeString);
	bool isSceneNodeName(wxString SomeString);
	
	bool isSelectionName(wxString SomeString);
	bool isPropertyGridIDName(wxString SomeString);
};
