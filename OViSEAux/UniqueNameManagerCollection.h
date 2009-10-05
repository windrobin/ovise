#pragma once

#include "./UniqueNameManager.h"
#include "./StringConverter.h"

class UniqueNameManagerCollection
{
private:
	bool OwnCameraNameManager;
	bool OwnEntityNameManager;
	bool OwnLightNameManager;
	bool OwnPrototypeNameManager;
	bool OwnSceneNodeNameManager;

	UniqueNameManager* CameraNameMgr;
	UniqueNameManager* EntityNameMgr;
	UniqueNameManager* LightNameMgr;
	UniqueNameManager* PrototypeNameMgr;
	UniqueNameManager* SceneNodeNameMgr;
public:
	UniqueNameManagerCollection(void);
	UniqueNameManagerCollection(UniqueNameManager* CameraNameMgr,
								UniqueNameManager* EntityNameMgr,
								UniqueNameManager* LightNameMgr,
								UniqueNameManager* PrototypeNameMgr,
								UniqueNameManager* SceneNodeNameMgr);
	UniqueNameManagerCollection(const UniqueNameManagerCollection& other);
	~UniqueNameManagerCollection(void);

	wxString AllocateCameraName(wxString OriginalName);
	wxString AllocateEntityName(wxString OriginalName);
	wxString AllocateLightName(wxString OriginalName);
	wxString AllocatePrototypeName(wxString OriginalName);
	wxString AllocateSceneNodeName(wxString OriginalName);

	bool DeallocateCameraName(wxString ModifiedOriginalName);	
	bool DeallocateEntityName(wxString ModifiedOriginalName);
	bool DeallocateLightName(wxString ModifiedOriginalName);
	bool DeallocatePrototypeName(wxString ModifiedOriginalName);
	bool DeallocateSceneNodeName(wxString ModifiedOriginalName);
};
