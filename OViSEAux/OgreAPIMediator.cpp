#include "OgreAPIMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreAPIMediator* OgreAPIMediator::instance = 0;

OgreAPIMediator* OgreAPIMediator::GetSingletonPtr()
{
	if (OgreAPIMediator::instance == 0) OgreAPIMediator::instance = new OgreAPIMediator();
	return OgreAPIMediator::instance;
}
OgreAPIMediator::OgreAPIMediator()
{
	this->Valid = false;
	this->OgreChanged = false;
	this->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OgreAPIMediator::OnOgreChanged ), NULL, this);
}
OgreAPIMediator::~OgreAPIMediator(void) { }
// General
bool OgreAPIMediator::IsValid() { return this->Valid; }
// Get & Set properies
Ogre::SceneManager* OgreAPIMediator::GetSceneManagerByRef() { return this->SceneMgr; }
wxString OgreAPIMediator::GetSceneManagerByName() { return this->SceneMgrName; }
bool OgreAPIMediator::SetSceneManagerByRef(Ogre::SceneManager* SceneMgr)
{
	this->SceneMgr = SceneMgr;

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(this->SceneMgr->getName());
	}
	if (SceneMgr == 0)
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}
bool OgreAPIMediator::SetSceneManagerByName(wxString SceneMgrName)
{
	this->SceneMgr = 0;
	this->SceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(SceneMgrName));

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(SceneMgrName);
	}
	else
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}
void OgreAPIMediator::SendSelectionChanged()
{
	/*
	wxCommandEvent event(OViSE_EVT_SELECTION_CHANGED, this->GetId());
	event.SetEventObject(this);
	this->GetEventHandler();
	*/
}
void OgreAPIMediator::SendOgreChanged()
{
	if ( this->OgreChanged )
	{
		wxCommandEvent event(OViSE_EVT_OGRE_CHANGED, this->GetId());
		event.SetEventObject(this);
		this->GetEventHandler()->ProcessEvent(event);
	}
}
void OgreAPIMediator::OnOgreChanged(wxCommandEvent& event)
{
	if(this->Valid)
	{
		this->OgreChanged = false;		
	}
}
// API to Ogre
// Get names of...
wxArrayString OgreAPIMediator::getSceneManagerNames()
{
	wxArrayString AS;
	Ogre::SceneManagerEnumerator::SceneManagerIterator SI = Ogre::Root::getSingletonPtr()->getSceneManagerIterator();
	while(SI.hasMoreElements()) { AS.Add(ToWxString(SI.getNext()->getName())); }
	return AS;
}
// Get pointer
Ogre::Camera* OgreAPIMediator::getCameraPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getCamera(ToOgreString(UniqueNameOfCamera));
}
Ogre::Entity* OgreAPIMediator::getEntityPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getEntity(ToOgreString(UniqueNameOfEntity));
}
Ogre::Light* OgreAPIMediator::getLightPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getLight(ToOgreString(UniqueNameOfLight));
}
Ogre::MovableObject* OgreAPIMediator::getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	if (this->MovableObjectVsTypeRegister.count(UniqueNameOfMovableObject) == 0) return 0;
	else
	{
		OViSEOgreEnums::MovableObject::MovableType Type = this->MovableObjectVsTypeRegister[UniqueNameOfMovableObject];
		if (Type < 1) return 0; // Baseclass (0) is absract. It doesn't exits, like Type == Invalid (-1). So Type has to be greather than 1 !
		return SM->getMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getEnumAsString(Type)));
	}
}
Ogre::MovableObject* OgreAPIMediator::getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OViSEOgreEnums::MovableObject::MovableType Type)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	if (Type < 1) return 0; // Baseclass (0) is absract. It doesn't exits, like Type == Invalid (-1). So Type has to be greather than 1 !
	return SM->getMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getEnumAsString(Type)));
}
Ogre::SceneNode* OgreAPIMediator::getSceneNodePtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getSceneNode(ToOgreString(UniqueNameOfSceneNode));
}
Ogre::SceneManager*	OgreAPIMediator::getSceneManagerPtr(wxString UniqueNameOfSceneManager) { return Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(UniqueNameOfSceneManager)); }
// Has objects
bool OgreAPIMediator::hasCamera(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isCameraName(UniqueNameOfCamera)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasCamera(ToOgreString(UniqueNameOfCamera));
}
bool OgreAPIMediator::hasEntity(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isEntityName(UniqueNameOfEntity)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasEntity(ToOgreString(UniqueNameOfEntity));
}
bool OgreAPIMediator::hasLight(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isLightName(UniqueNameOfLight)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasLight(ToOgreString(UniqueNameOfLight));
}
bool OgreAPIMediator::hasMovableObject(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OViSEOgreEnums::MovableObject::MovableType Type)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	// check name? //TODO
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	
	switch(Type)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			if (!this->hasCamera(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			if (!this->hasEntity(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			if (!this->hasLight(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		default: break; // all types not implemented // TODO
	}

	// Now, ever return true ;-)
	return SM->hasMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getEnumAsString(Type)));
}
bool OgreAPIMediator::hasSceneNode(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isSceneNodeName(UniqueNameOfSceneNode)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasSceneNode(ToOgreString(UniqueNameOfSceneNode));
}
bool OgreAPIMediator::hasSceneManager(wxString UniqueNameOfSceneManager)
{
	//if (!UniqueNameManagerCollection::getSingletonPtr()->isEntityName(UniqueNameOfEntity)) return false; // check scene manager // NOT IMPLEMENTED
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if ( SM == 0 ) return false;
	else return true;
}
// Add objects
Ogre::Camera* OgreAPIMediator::addCamera(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateCameraName(NotUniqueName);

	Ogre::Camera* C = this->SceneMgr->createCamera(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(C);
	else AttachToThisNode->attachObject(C);
	this->MovableObjectVsTypeRegister[UniqueName] = OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera;
	this->OgreChanged = true;
	return C;
}
Ogre::Entity* OgreAPIMediator::addEntity(wxString NotUniqueName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateEntityName(NotUniqueName);

	Ogre::Entity* E = this->SceneMgr->createEntity(ToOgreString(UniqueName), ToOgreString(MeshFile));
	if (AttachToThisNode == 0) this->SceneMgr->getRootSceneNode()->attachObject(E);
	else AttachToThisNode->attachObject(E);
	this->MovableObjectVsTypeRegister[UniqueName] = OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity;
	this->OgreChanged = true;
	return E;
}
Ogre::Light* OgreAPIMediator::addLight(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateLightName(NotUniqueName);

	Ogre::Light* L = this->SceneMgr->createLight(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(L);
	else AttachToThisNode->attachObject(L);
	this->MovableObjectVsTypeRegister[UniqueName] = OViSEOgreEnums::MovableObject::MOVABLETYPE_Light;
	this->OgreChanged = true;
	return L;
}
Ogre::SceneNode* OgreAPIMediator::addSceneNode(wxString NotUniqueName, Ogre::SceneNode* ParentNode)
{
	if (!this->Valid) return 0;

	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateSceneNodeName(NotUniqueName);

	Ogre::SceneNode* NewSN = 0;
	if (ParentNode == 0) NewSN = this->SceneMgr->getRootSceneNode()->createChildSceneNode(ToOgreString(UniqueName));
	else NewSN = ParentNode->createChildSceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return NewSN;
}
// Remove objects
bool OgreAPIMediator::removeCamera(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasCamera(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateCameraName(UniqueName);

	Ogre::Camera* C = this->SceneMgr->getCamera(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = C->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyCamera(C);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeEntity(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasEntity(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateEntityName(UniqueName);
	Ogre::Entity* E = this->SceneMgr->getEntity(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = E->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyEntity(E);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeLight(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasLight(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateLightName(UniqueName);

	Ogre::Light* L = this->SceneMgr->getLight(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = L->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyLight(L);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeSceneNode(wxString UniqueName, bool RemoveRecursive)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasSceneNode(ToOgreString(UniqueName))) return false;

	if (RemoveRecursive) ; // Not implemented yet. // TODO
	else ;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateSceneNodeName(UniqueName);

	this->SceneMgr->destroySceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return true;
	
}
/*
bool OViSESelection::AddMovableObject(Ogre::MovableObject* pMovableObject)
{
	// Stop, if pMovableObject is null
	if ( pMovableObject == 0 ) return false;

	// Get SceneManager by name
	Ogre::SceneManager* TempSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->SceneManagerName));

	// Stop, if no SceneManager has been found
	if (TempSceneMgr == 0) return false;

	// Get characteristics of pMovableObject
	wxString TempMovableObjectName = ToWxString(pMovableObject->getName());
	wxString TempMovableTypeName = this->mEnumTranslator.getMovableObjectAsString(pMovableObject);
	OViSEOgreEnums::MovableObject::MovableType TempMovableTypeEnum = this->mEnumTranslator.getMovableObjectAsEnum(pMovableObject);
	
	// Stop, if SceneManager doesn't contain pMovableObject
	if (!TempSceneMgr->hasMovableObject(ToOgreString(TempMovableObjectName), ToOgreString(TempMovableTypeName))) return false;

	bool FlagBad = false;

	// Add pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject can not indentified or is already in selection
	switch(TempMovableTypeEnum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:
			if ( this->SelectedBillboardChains.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedBillboardChains[TempMovableObjectName] = (Ogre::BillboardChain*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet:
			if ( this->SelectedBillboardSets.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedBillboardSets[TempMovableObjectName] = (Ogre::BillboardSet*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			if ( this->SelectedCameras.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedCameras[TempMovableObjectName] = (Ogre::Camera*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			if ( this->SelectedEntities.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedEntities[TempMovableObjectName] = (Ogre::Entity*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum:
			if ( this->SelectedFrustums.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedFrustums[TempMovableObjectName] = (Ogre::Frustum*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance:
			if ( this->SelectedInstancedGeometryBatchInstances.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedInstancedGeometryBatchInstances[TempMovableObjectName] = (Ogre::InstancedGeometry::BatchInstance*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			if ( this->SelectedLights.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedLights[TempMovableObjectName] = (Ogre::Light*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject:
			if ( this->SelectedManualObjects.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedManualObjects[TempMovableObjectName] = (Ogre::ManualObject*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane:
			if ( this->SelectedMovablePlanes.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedMovablePlanes[TempMovableObjectName] = (Ogre::MovablePlane*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:
			if ( this->SelectedParticleSystems.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedParticleSystems[TempMovableObjectName] = (Ogre::ParticleSystem*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:
			if ( this->SelectedRibbonTrails.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedRibbonTrails[TempMovableObjectName] = (Ogre::RibbonTrail*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:
			if ( this->SelectedSimpleRenderables.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedSimpleRenderables[TempMovableObjectName] = (Ogre::SimpleRenderable*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:
			if ( this->SelectedStaticGeometryRegions.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedStaticGeometryRegions[TempMovableObjectName] = (Ogre::StaticGeometry::Region*) pMovableObject;
			break;

		default: // Stop, if MovableType of pMovableObject can not indetified/is not valid (important)
			FlagBad = true;
			break;
	}

	// Add pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject is already in Selection
	if ( this->SelectedMovableObjects.count(TempMovableObjectName) == 1 ) FlagBad = true;
	else this->SelectedMovableObjects[TempMovableObjectName] = pMovableObject;

	// Result of activities: return false, but inhomogen container-contents are repaired automatically.
	if ( FlagBad ) return false; 
	else return true;
}
bool OViSESelection::RemoveMovableObject(Ogre::MovableObject* pMovableObject)
{
	// Stop, if pMovableObject is null
	if ( pMovableObject == 0 ) return false;

	// Get SceneManager by name
	Ogre::SceneManager* TempSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->SceneManagerName));

	// Stop, if no SceneManager has been found
	if (TempSceneMgr == 0) return false;

	// Get characteristics of pMovableObject
	wxString TempMovableObjectName = ToWxString(pMovableObject->getName());
	wxString TempMovableTypeName = this->mEnumTranslator.getMovableObjectAsString(pMovableObject);
	OViSEOgreEnums::MovableObject::MovableType TempMovableTypeEnum = this->mEnumTranslator.getMovableObjectAsEnum(pMovableObject);
	
	// Stop, if SceneManager doesn't contain pMovableObject
	if (!TempSceneMgr->hasMovableObject(ToOgreString(TempMovableObjectName), ToOgreString(TempMovableTypeName))) return false;

	bool FlagBad = false;

	// Remove pMovableObject from SelectedMovableObjects. Move forward, if pMovableObject is not in Selection
	if ( this->SelectedMovableObjects.count(TempMovableObjectName) == 1) this->SelectedMovableObjects.erase(TempMovableObjectName);
	else FlagBad = true;

	// Remove pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject can not indentified 
	switch(TempMovableTypeEnum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:
			if ( this->SelectedBillboardChains.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedBillboardChains.erase(TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet:
			if ( this->SelectedBillboardSets.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedBillboardSets.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			if ( this->SelectedCameras.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedCameras.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			if ( this->SelectedEntities.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedEntities.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum:
			if ( this->SelectedFrustums.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedFrustums.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance:
			if ( this->SelectedInstancedGeometryBatchInstances.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedInstancedGeometryBatchInstances.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			if ( this->SelectedLights.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedLights.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject:
			if ( this->SelectedManualObjects.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedManualObjects.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane:
			if ( this->SelectedMovablePlanes.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedMovablePlanes.erase(TempMovableObjectName);
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:
			if ( this->SelectedParticleSystems.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedParticleSystems.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:
			if ( this->SelectedRibbonTrails.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedRibbonTrails.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:
			if ( this->SelectedSimpleRenderables.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedSimpleRenderables.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:
			if ( this->SelectedStaticGeometryRegions.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedStaticGeometryRegions.erase( TempMovableObjectName );
			break;

		default: // Stop, if MovableType of pMovableObject can not indetified/is not valid (important)
			FlagBad = true;
			break;
	}
	
	if ( FlagBad ) return false;
	else return true;
}
void OViSESelection::RemoveAll()
{
	this->SelectedMovableObjects.clear();

	this->SelectedBillboardChains.clear();
	this->SelectedBillboardSets.clear();
	this->SelectedCameras.clear();
	this->SelectedEntities.clear();
	this->SelectedFrustums.clear();
	this->SelectedInstancedGeometryBatchInstances.clear();
	this->SelectedLights.clear();
	this->SelectedManualObjects.clear();
	this->SelectedMovablePlanes.clear();
	this->SelectedParticleSystems.clear();
	this->SelectedRibbonTrails.clear();
	this->SelectedSimpleRenderables.clear();
	this->SelectedStaticGeometryRegions.clear();
}

OViSESelection::OViSESelection(wxString SceneManagerName)
{
	this->UniqueName = ToWxString("INVALID");
	this->SceneManagerName = SceneManagerName;
}
OViSESelection::OViSESelection(Ogre::SceneManager* pSceneManager)
{
	this->UniqueName = ToWxString("INVALID");
	this->SceneManagerName = ToWxString(pSceneManager->getName());
}
OViSESelection::~OViSESelection(void) { this->SelectedMovableObjects.clear(); }
*/