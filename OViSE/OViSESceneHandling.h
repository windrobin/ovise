#ifndef OVISESCENEHANDLING_H_
#define OVISESCENEHANDLING_H_

#include "Ogre.h"

/**
 * Class responsible for managing initial scene creation and manipulation.
 * This class handles everything that has to do with the whole scene, like cameras, ambient light,
 * mesh loading/creation. Mesh manipulation is done in OViSEMeshManipulation.
 */
class OViSESceneHandling
{
public:
	OViSESceneHandling(Ogre::SceneManager *scnMgr);

	/** Creates default scene to be shown on startup.
	 */
	void createDefaultScene();

	/** Add a grid to the scene. Gridsize is adjustable and it can be attached to any node.
	 * By default the grid is aligned in the x-z-plane. To change that create a scene node for the grid
	 * and rotate it for your needs.
	 * @param size Defines the length of a grid unit
	 * @param numRows Number of rows of the grid
	 * @param numCols Number of columns for the grid
	 * @param col Color of the grid - RGB (0.0-1.0)
	 * @param node Defines the node the grid should be attached to, defaults to the root node
	 */
	void addGrid(int size, int numRows, int numCols, Ogre::Vector3& col, Ogre::SceneNode *node=NULL);

	/** Adds a mesh depicting a coordinate system to the given SceneNode.
	 * @param node Defines the SceneNode the coordinate system shall be attached to. Defaults to the root node.
	 */
	void addCOS(bool castShadows=false, Ogre::SceneNode *node=NULL);

	/** Returns list of meshes available in loaded resources.
	 * Retrieves a list of all meshes in the given resource group. One can then load a mesh using the given filename.
	 * @param group Name of the resource group to look for meshes
	 * @return List of filenames
	 */
	static std::vector<std::string> getAvailableMeshes(std::string group);

	virtual ~OViSESceneHandling();

protected:
	/// Scene manager this SceneHandler works on.
	Ogre::SceneManager *mScnMgr;
};

#endif /*OVISESCENEHANDLING_H_*/
