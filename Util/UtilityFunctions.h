#ifndef OVISE_UTILITY_H
#define OVISE_UTILITY_H

#include <sstream>
#include <string>

#include <OGRE/OgreVector2.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneQuery.h>

#include "../XMLRPCInterface/HTTPReply.h"

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

/** This function converts a std::string to an integer with std::stringstream
	\param Str is the std::string which will be converted to an integer
	\returns An integer number of Str
*/
int StrToInt(const std::string& Str);

/** This function converts a std::string to a float with std::stringstream
	\param Str is the std::string which will be converted to an float
	\returns A floating point number of Str
*/
float StrToFloat(const std::string& Str);

/** This function cuts leading and successive space-characters
	\param Str is the std::string which will be processed
	\returns Str without leading and successive space-characters
*/
std::string Trim( const std::string& Str );

/** This function returns the header of a http-message
	\param Message is the hole http-message
	\returns Header of http-message
*/
std::string GetHTTPHeader( const std::string& Message );

/** This function returns the content of a http-message
	\param Message is the hole http-message
	\returns Content of http-message
*/
std::string GetHTTPContent( const std::string& Message );

} // namespace OVISE

#endif // OVISE_UTILITY_H
