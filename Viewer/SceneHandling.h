#ifndef OVISESCENEHANDLING_H_
#define OVISESCENEHANDLING_H_

#include "OViSEException.h"

// Include Ogre
#ifdef __APPLE__
#include <Ogre/Ogre.h>
#else
#include <Ogre.h>
#endif

namespace SceneHandling
{
/** Returns list of meshes available in loaded resources.
 * Retrieves a list of all meshes in the given resource group. One can then load a mesh using the given filename.
 * @param group Name of the resource group to look for meshes
 * @return List of filenames
 */
	std::vector<std::string> getAvailableMeshes( std::string group );

/** Returns a list of all resource groups available.
 * Retrieves a list of all resource groups currently available in the resource manager.
 * @return List of resource group names
 */
	std::vector<std::string> getAvailableResourceGroupNames();
} // namespace

#endif /*OVISESCENEHANDLING_H_*/
