#pragma once

#ifndef OVISESELECTION_H_
#define OVISESELECTION_H_

// Include WX
#include <wx/hashmap.h>

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/EnumTranslator.h"

// Include Ogre
#include <Ogre.h>


WX_DECLARE_STRING_HASH_MAP( Ogre::MovableObject*, HashMap_MovableObject );		// HashMap-Collection of Ogre::MovableObjects

WX_DECLARE_STRING_HASH_MAP( Ogre::BillboardChain*,	HashMap_BillboardChain );	// HashMap-Collection of Ogre::BillboardChain
WX_DECLARE_STRING_HASH_MAP( Ogre::BillboardSet*,	HashMap_BillboardSet );		// HashMap-Collection of Ogre::BillboardSet
WX_DECLARE_STRING_HASH_MAP( Ogre::Camera*,			HashMap_Camera );			// HashMap-Collection of Ogre::Camera
WX_DECLARE_STRING_HASH_MAP( Ogre::Entity*,			HashMap_Entity );			// HashMap-Collection of Ogre::Entity
WX_DECLARE_STRING_HASH_MAP( Ogre::Frustum*,			HashMap_Frustum );			// HashMap-Collection of Ogre::Frustum
WX_DECLARE_STRING_HASH_MAP( Ogre::InstancedGeometry::BatchInstance*, HashMap_InstancedGeometry_BatchInstance ); // HashMap-Collection of Ogre::InstancedGeometry::BatchInstance
WX_DECLARE_STRING_HASH_MAP( Ogre::Light*,			HashMap_Light );			// HashMap-Collection of Ogre::Light
WX_DECLARE_STRING_HASH_MAP( Ogre::ManualObject*,	HashMap_ManualObject );		// HashMap-Collection of Ogre::ManualObject
WX_DECLARE_STRING_HASH_MAP( Ogre::MovablePlane*,	HashMap_MovablePlane );		// HashMap-Collection of Ogre::MovablePlane
WX_DECLARE_STRING_HASH_MAP( Ogre::ParticleSystem*,	HashMap_ParticleSystem );	// HashMap-Collection of Ogre::ParticleSystem
WX_DECLARE_STRING_HASH_MAP( Ogre::RibbonTrail*,		HashMap_RibbonTrail );		// HashMap-Collection of Ogre::RibbonTrail
WX_DECLARE_STRING_HASH_MAP( Ogre::SimpleRenderable*,HashMap_SimpleRenderable ); // HashMap-Collection of Ogre::SimpleRenderable
WX_DECLARE_STRING_HASH_MAP( Ogre::StaticGeometry::Region*, HashMap_StaticGeometry_Region ); // HashMap-Collection of Ogre::StaticGeometry::Region

class OViSESelection
{
private:
	wxString UniqueName;
	OViSEOgreEnums::EnumTranslator mEnumTranslator;

public:
	/// HashMaps, containing selected objects.
	HashMap_MovableObject	SelectedMovableObjects;

	HashMap_BillboardChain			SelectedBillboardChains;
	HashMap_BillboardSet			SelectedBillboardSets;
	HashMap_Camera					SelectedCameras;
	HashMap_Entity					SelectedEntities;
	HashMap_Frustum					SelectedFrustums;
	HashMap_InstancedGeometry_BatchInstance	SelectedInstancedGeometryBatchInstances;
	HashMap_Light					SelectedLights;
	HashMap_ManualObject			SelectedManualObjects;
	HashMap_MovablePlane			SelectedMovablePlanes;
	HashMap_ParticleSystem			SelectedParticleSystems;
	HashMap_RibbonTrail				SelectedRibbonTrails;
	HashMap_SimpleRenderable		SelectedSimpleRenderables;
	HashMap_StaticGeometry_Region	SelectedStaticGeometryRegions;

	wxString SceneManagerName;

	void SetUniqueName(wxString UniqueName);
	wxString GetUniqueName();

	bool AddMovableObject(Ogre::MovableObject* pMovableObject);
	bool RemoveMovableObject(Ogre::MovableObject* pMovableObject);
	void RemoveAll();

	OViSESelection(wxString SceneManagerName);
	OViSESelection(Ogre::SceneManager* pSceneManager);
	~OViSESelection(void);
};

#endif // OVISESELECTION_H_