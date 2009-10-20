#include "UniqueNameManagerCollection.h"

// Singleton
UniqueNameManagerCollection* UniqueNameManagerCollection::instance = 0;
UniqueNameManagerCollection* UniqueNameManagerCollection::getSingletonPtr()
{
	if (UniqueNameManagerCollection::instance == 0) UniqueNameManagerCollection::instance = new UniqueNameManagerCollection();
	return UniqueNameManagerCollection::instance;
}

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

	this->OwnSelectionNameManager = true;
	this->SelectionNameMgr = new UniqueNameManager(ToWxString("Selection"));

	this->OwnPropertyGridIDNameManager = true;
	this->PropertyGridIDNameMgr = new UniqueNameManager(ToWxString("ProperyGridID"));
}
UniqueNameManagerCollection::UniqueNameManagerCollection(	UniqueNameManager* CameraNameMgr,
															UniqueNameManager* EntityNameMgr,
															UniqueNameManager* LightNameMgr,
															UniqueNameManager* PrototypeNameMgr,
															UniqueNameManager* SceneNodeNameMgr,
															UniqueNameManager* SelectionNameMgr,
															UniqueNameManager* PropertyGridTagNameMgr)
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

	if (SelectionNameMgr == 0)
	{
		this->OwnSelectionNameManager = true;
		this->SelectionNameMgr = new UniqueNameManager(ToWxString("Selection"));
	}
	else
	{
		this->OwnSelectionNameManager = false;
		this->SelectionNameMgr = SelectionNameMgr;
	}

	if (SceneNodeNameMgr == 0)
	{
		this->OwnPropertyGridIDNameManager = true;
		this->PropertyGridIDNameMgr = new UniqueNameManager(ToWxString("PropertyGridID"));
	}
	else
	{
		this->OwnPropertyGridIDNameManager = false;
		this->PropertyGridIDNameMgr = PropertyGridIDNameMgr;
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

	this->OwnSelectionNameManager = false;
	this->SelectionNameMgr = other.SelectionNameMgr;

	this->OwnPropertyGridIDNameManager = false;
	this->PropertyGridIDNameMgr = other.PropertyGridIDNameMgr;
}

UniqueNameManagerCollection::~UniqueNameManagerCollection(void)
{
	if (this->OwnCameraNameManager) delete this->CameraNameMgr;
	if (this->OwnEntityNameManager) delete this->EntityNameMgr;
	if (this->OwnLightNameManager) delete this->LightNameMgr;
	if (this->OwnPrototypeNameManager) delete this->PrototypeNameMgr;
	if (this->OwnSceneNodeNameManager) delete this->SceneNodeNameMgr;
	if (this->OwnSelectionNameManager) delete this->SelectionNameMgr;
	if (this->OwnPropertyGridIDNameManager) delete this->PropertyGridIDNameMgr;
}

wxString UniqueNameManagerCollection::AllocateCameraName(wxString OriginalName){ return this->CameraNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateEntityName(wxString OriginalName){ return this->EntityNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateLightName(wxString OriginalName){ return this->LightNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocatePrototypeName(wxString OriginalName){ return this->PrototypeNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocateSceneNodeName(wxString OriginalName){ return this->SceneNodeNameMgr->AllocateUniqueName(OriginalName); }

wxString UniqueNameManagerCollection::AllocateSelectionName(wxString OriginalName){ return this->SelectionNameMgr->AllocateUniqueName(OriginalName); }
wxString UniqueNameManagerCollection::AllocatePropertyGridIDName(wxString OriginalName){ return this->PropertyGridIDNameMgr->AllocateUniqueName(OriginalName); }

bool UniqueNameManagerCollection::DeallocateCameraName(wxString ModifiedOriginalName){ return this->CameraNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateEntityName(wxString ModifiedOriginalName){ return this->EntityNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateLightName(wxString ModifiedOriginalName){ return this->LightNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocatePrototypeName(wxString ModifiedOriginalName){ return this->PrototypeNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocateSceneNodeName(wxString ModifiedOriginalName){ return this->SceneNodeNameMgr->DeallocateUniqueName(ModifiedOriginalName); }

bool UniqueNameManagerCollection::DeallocateSelectionName(wxString ModifiedOriginalName){ return this->SelectionNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::DeallocatePropertyGridIDName(wxString ModifiedOriginalName){ return this->PropertyGridIDNameMgr->DeallocateUniqueName(ModifiedOriginalName); }
bool UniqueNameManagerCollection::isCameraName(wxString SomeString) { return this->CameraNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isEntityName(wxString SomeString) { return this->EntityNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isLightName(wxString SomeString) { return this->LightNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isPrototypeName(wxString SomeString) { return this->PrototypeNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isSceneNodeName(wxString SomeString) { return this->SceneNodeNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isSelectionName(wxString SomeString) { return this->SelectionNameMgr->isUniqueName(SomeString); }
bool UniqueNameManagerCollection::isPropertyGridIDName(wxString SomeString) { return this->PropertyGridIDNameMgr->isUniqueName(SomeString); }