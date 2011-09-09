#ifndef OVISE_UTILITY_H
#define OVISE_UTILITY_H

#include <OGRE/OgreVector2.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneQuery.h>

namespace OVISE
{

/**
* This function gets the screenspace coordinates for a position in 3d space
*
* Taken from http://www.ogre3d.org/tikiwiki/GetScreenspaceCoords&structure=Cookbook
* and adapted
* @param   Point   The 3d point to retrieve the coordidnates of.
* @param   Camera   The active camera
* @param   Result   The Vector2 to store the result in
*
* @return   Returns true if the object is visible and the coordinates were
*         retrieved, false otherwise.
*/
bool GetScreenspaceCoords( const Ogre::Vector3& Point, const Ogre::Camera* Camera, Ogre::Vector2& Result);

/**
  Raycasting to polygon level.

  Taken from: http://www.ogre3d.org/tikiwiki/Raycasting+to+the+polygon+level&structure=Cookbook
*/
Ogre::Entity* RaycastToPolygon( const Ogre::Real& x, const Ogre::Real& y,
	Ogre::RaySceneQuery* Query, Ogre::Camera* Camera );

} // namespace OVISE

#endif // OVISE_UTILITY_H
