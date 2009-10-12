#include "OViSESelection.h"

void OViSESelection::SetUniqueName(wxString UniqueName) { this->UniqueName = UniqueName; }
wxString OViSESelection::GetUniqueName() { return this->UniqueName; }
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

