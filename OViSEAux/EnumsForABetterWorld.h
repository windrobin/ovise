#pragma once

#ifndef OGRE_ENUMS_H_
#define OGRE_ENUMS_H_

namespace OgreEnums
{
	// COMMENT: This version fits Ogre 1.6.4

	namespace MovableObject
	{
		enum MovableType // Sorted alphabetic...
		{
			MOVABLETYPE_Invalid = -1,			// That's a class, not inherited from Ogre::MovableObject
			MOVABLETYPE_BaseClass = 0,			// Ogre::MovableObject base-class!
			
			MOVABLETYPE_BillBoardChain = 1,
			MOVABLETYPE_BillboardSet,
			MOVABLETYPE_Camera,
			MOVABLETYPE_Entity,
			MOVABLETYPE_Frustum,
			MOVABLETYPE_InstancedGeometry_BatchInstance,
			MOVABLETYPE_Light,
			MOVABLETYPE_ManualObject,
			MOVABLETYPE_MovablePlane,
			MOVABLETYPE_ParticleSystem,
			MOVABLETYPE_RibbonTrail,
			MOVABLETYPE_SimpleRenderable,
			MOVABLETYPE_StaticGeometry_Region	// ...and so on...
		};
	};
};

#endif // OGRE_ENUMS_H_