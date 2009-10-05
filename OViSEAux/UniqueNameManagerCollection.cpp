#include "UniqueNameManagerCollection.h"

UniqueNameManagerCollection::UniqueNameManagerCollection(void)
{
	this->OwnCameraNameManager = true;
	this->CameraNameMgr = new UniqueNameManager(ToWxString("Camera"));

	this->OwnEntityNameManager = true;
	this->EntityNameMgr = new UniqueNameManager(ToWxString("Entity"));

	this->OwnLightNameManager = true;
	this->LightNameMgr = new UniqueNameManager(ToWxString("Light"));

	this->OwnPrototypeNameManager = true;
	this->PrototypeNameMgr = new UniqueNameManager(ToWxString("Prototype"));

	this->OwnSceneNodeNameManager = true;
	this->SceneNodeNameMgr = new UniqueNameManager(ToWxString("SceneNode"));
}
UniqueNameManagerCollection::UniqueNameManagerCollection(	UniqueNameManager* CameraNameMgr,
															UniqueNameManager* EntityNameMgr,
															UniqueNameManager* LightNameMgr,
															UniqueNameManager* PrototypeNameMgr,
															UniqueNameManager* SceneNodeNameMgr)
{
	if (CameraNameMgr == 0)
	{
		this->OwnCameraNameManager = true;
		this->CameraNameMgr = new UniqueNameManager(ToWxString("Camera"));
	}
	else
	{
		this->OwnCameraNameManager = false;
		this->CameraNameMgr = CameraNameMgr;
	}

	if (EntityNameMgr == 0)
	{
		this->OwnEntityNameManager = true;
		this->EntityNameMgr = new UniqueNameManager(ToWxString("Entity"));
	}
	else
	{
		this->OwnEntityNameManager = false;
		this->EntityNameMgr = EntityNameMgr;
	}

	if (LightNameMgr == 0)
	{
		this->OwnLightNameManager = true;
		this->LightNameMgr = new UniqueNameManager(ToWxString("Light"));
	}
	else
	{
		this->OwnLightNameManager = false;
		this->LightNameMgr = LightNameMgr;
	}

	if (PrototypeNameMgr == 0)
	{
		this->OwnPrototypeNameManager = true;
		this->PrototypeNameMgr = new UniqueNameManager(ToWxString("Prototype"));
	}
	else
	{
		this->OwnPrototypeNameManager = false;
		this->PrototypeNameMgr = PrototypeNameMgr;
	}

	if (SceneNodeNameMgr == 0)
	{
		this->OwnSceneNodeNameManager = true;
		this->SceneNodeNameMgr = new UniqueNameManager(ToWxString("SceneNode"));
	}
	else
	{
		this->OwnSceneNodeNameManager = false;
		this->SceneNodeNameMgr = SceneNodeNameMgr;
	}
}

UniqueNameManagerCollection::UniqueNameManagerCollection(const UniqueNameManagerCollection& other)
{
	this->OwnCameraNameManager = false;
	this->CameraNameMgr = other.CameraNameMgr;

	this->OwnEntityNameManager = false;
	this->EntityNameMgr = other.EntityNameMgr;

	this->OwnLightNameManager = false;
	this->LightNameMgr = other.LightNameMgr;

	this->OwnPrototypeNameManager = false;
	this->PrototypeNameMgr = other.PrototypeNameMgr;

	this->OwnSceneNodeNameManager = false;
	this->SceneNodeNameMgr = other.SceneNodeNameMgr;
}

UniqueNameManagerCollection::~UniqueNameManagerCollection(void)
{
	if (this->OwnCameraNameManager) delete this->CameraNameMgr;
	if (this->OwnEntityNameManager) delete this->EntityNameMgr;
	if (this->OwnLightNameManager) delete this->LightNameMgr;
	if (this->OwnPrototypeNameManager) delete this->PrototypeNameMgr;
	if (this->OwnSceneNodeNameManager) delete this->SceneNodeNameMgr;
}

wxString UniqueNameManagerCollection::AllocateCameraName(wxString OriginalName){ return this->CameraNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateEntityName(wxString OriginalName){ return this->EntityNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateLightName(wxString OriginalName){ return this->LightNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocatePrototypeName(wxString OriginalName){ return this->PrototypeNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateSceneNodeName(wxString OriginalName){ return this->SceneNodeNameMgr->AllocateUniqueName(OriginalName); }

bool UniqueNameManagerCollection::DeallocateCameraName(wxString ModifiedOriginalName){ return this->CameraNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateEntityName(wxString ModifiedOriginalName){ return this->EntityNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateLightName(wxString ModifiedOriginalName){ return this->LightNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocatePrototypeName(wxString ModifiedOriginalName){ return this->PrototypeNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateSceneNodeName(wxString ModifiedOriginalName){ return this->SceneNodeNameMgr->DeallocateUniqueName(ModifiedOriginalName); }