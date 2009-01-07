#ifndef OVISESCENEHANDLING_H_
#define OVISESCENEHANDLING_H_

#ifdef __APPLE__
#include "Ogre/Ogre.h"
#else
#include "Ogre.h"
#endif
#include "OViSEException.h"
#include "OViSEObjectTitle.h"
#include "OViSEPointcloud.h"

/// Map containing all scene managers.
typedef std::map<std::string, Ogre::SceneManager*> OViSEScnMgrMap;
/// Map containing all ray scene querys for object selection.
typedef std::map<std::string, Ogre::RaySceneQuery*> OViSERayQueryMap;
/// Map containing selected objects.
typedef std::map<std::string, Ogre::MovableObject*> OViSESelectionMap;
/// Map containing all object selection maps.
typedef std::map<std::string, OViSESelectionMap> OViSESelections;
/// Map containing object title instances (for updating in the frame listener)
typedef std::vector<OViSEObjectTitle*> OViSEObjectTitleVector;

/**
 * Singleton class responsible for managing initial scene creation and manipulation.
 * This class handles everything that has to do with the whole scene, like cameras, ambient light,
 * mesh loading/creation. The class is implemented as singleton, meaning there can be only one instance
 * at a time. You can get a handle on the class using getSingletonPtr(). 
 * OViSESceneHandling manages a list of Ogre::SceneManagers that are accessed via a unique name. Every scenemanager
 * is responsible for a seperate scene. By default a "BaseSceneManager" is created that holds the contents of the
 * base scene. 
 * Mesh manipulation is done in OViSEMeshManipulation.
 */
class OViSESceneHandling
{
public:
	/// Get handle to singleton instance
	static OViSESceneHandling* getSingletonPtr();

	/** Creates a default scene consisting of a light and a grid.
	 * @param sceneManagerName Name of the scenemanager where the default scene contents should be added
	 */
	void createDefaultScene(std::string sceneManagerName = "BaseSceneManager");

	/** Adds a new scenemanager to the list.
	 * Creates a new scenemanager with the given name and adds it to the accessible list of scenemanagers.
	 */
	void addSceneManager(std::string sceneManagerName);

	/// Get a named scenemanager from the list
	Ogre::SceneManager* getSceneManager(std::string sceneManagerName = "BaseSceneManager");

	/// Removes a scene manager from the list and deletes it
	void removeSceneManager(std::string sceneManagerName);

	/// Retrieves the object selection query for the given scene manager
	Ogre::RaySceneQuery* getObjectSelectionQuery(std::string sceneManagerName);

	/// Add movable to object selection
	void addObjectToSelection(Ogre::MovableObject *movObj, bool showSelection = true, std::string sceneManagerName = "BaseSceneManager");

	/// Remove movable object from object selection
	void removeObjectFromSelection(Ogre::MovableObject *movObj, bool hideSelection = true, std::string sceneManagerName = "BaseSceneManager");
	void removeObjectFromSelection(std::string name, bool hideSelection = true, std::string sceneManagerName = "BaseSceneManager");

	/// Retrieve list of selected objects
	OViSESelectionMap getSelectedObjects(std::string sceneManagerName = "BaseSceneManager");

	/// Check if any objects are selected
	bool hasSelectedObjects(std::string sceneManagerName = "BaseSceneManager");

	/** Returns list of meshes available in loaded resources.
	 * Retrieves a list of all meshes in the given resource group. One can then load a mesh using the given filename.
	 * @param group Name of the resource group to look for meshes
	 * @return List of filenames
	 */
	std::vector<std::string> getAvailableMeshes(std::string group);

	/** Returns a list of all resource groups available.
	 * Retrieves a list of all resource groups currently available in the resource manager.
	 * @return List of resource group names
	 */
	std::vector<std::string> getAvailableResourceGroupNames();

	/** Adds a mesh into the scene.
	 * Adds the named mesh to the given scenemanager.
	 * @param meshName name the mesh will be created with
	 * @param meshFileName name of the file the mesh is based on
	 * @param node scenenode the mesh will be child of
	 * @note Method will create a new entity with name meshName and try to attach it to node (if node == NULL the scenemanagers rootscenenode will be used)
	 */
	void addMesh(std::string meshName, std::string meshFileName, std::string sceneManagerName = "BaseSceneManager", Ogre::SceneNode *node = NULL);

	/** Deletes a mesh from the given scene.
	 * @note Searches for an entity with name meshName, detaches it from the scenenode and destroys it. If
	 * there it is the only entity attached to the scene node and the node doesn't have any children, the node itself will be destroyed.
	 */
	void deleteMesh(std::string meshName, std::string sceneManagerName = "BaseSceneManager");

	/** Loads a complete scene from a dotSceneXML.
	 * This function takes a dotScene-XML-file and imports all meshes into the scene designated by the scene manager and the node.
	 * If the node is NULL, then a new scene node will be created as a child of the root scene node.
	 * @TODO Implement this.
	 */
	void loadSceneFromXML(std::string filename, std::string sceneManagerName = "BaseSceneManager", Ogre::SceneNode *node = NULL);

	/** Resolves a ray scene query to select an object.
	 * Casts a ray from the screen position through the given camera into the scene and evaluates
	 * the nearest object hidden by the ray. Returns a pointer to the object, NULL if no object is hit by the ray.
	 * @param screenx Normalised x-coordinate [0,1]
	 * @param screeny Normalised y-coordinate [0,1]
	 * @param dist Distance of the selected object, -1 if no object is hit
	 * @param cam Camera used for the scenequery
	 */
	Ogre::MovableObject* getSelectedObject(float screenx, float screeny, float& dist, Ogre::Camera *cam, std::string sceneManagerName = "BaseSceneManager");

	/// Removes all selected objects from the selection list and hides bounding boxes
	void clearObjectSelection(std::string sceneManagerName = "BaseSceneManager");

	/** Show graph relations.
	 * Function shows a graphical representation of the scene graph using lines and spheres.
	 */
	void showSceneGraphStructure(bool update = false, std::string sceneManagerName = "BaseSceneManager");

	/** Add a grid to the scene. Gridsize is adjustable and it can be attached to any node.
	 * By default the grid is aligned in the x-z-plane. To change that create a scene node for the grid
	 * and rotate it for your needs.
	 * @param size Defines the length of a grid unit
	 * @param numRows Number of rows of the grid
	 * @param numCols Number of columns for the grid
	 * @param col Color of the grid - RGB (0.0-1.0)
	 * @param sceneManagerName Name of the scenemanager the grid should be added to
	 * @param node Defines the node the grid should be attached to, defaults to the root node
	 */
	void addGrid(int size, int numRows, int numCols, Ogre::Vector3 col, std::string sceneManagerName = "BaseSceneManager", Ogre::SceneNode *node=NULL);

	/** Adds a mesh depicting a coordinate system.
	 * @param sceneManagerName scenemanager the coordinate system will be added to.
	 * @param node Defines the SceneNode the coordinate system shall be attached to. Defaults to the root node.
	 */
	void addCOS(float scale = 1.0, bool castShadows=false, std::string sceneManagerName = "BaseSceneManager", Ogre::SceneNode *node=NULL);

	/** Updates the object titles in the internal map.
	 */
	void updateObjectTitles();

	/// Turn dynamic shadows (stencil) on or off
	void dynamicShadows(bool state);

	/// debug function for testing
	void testStuff();

protected:
	OViSESceneHandling();
	virtual ~OViSESceneHandling();

private:
	/// Singleton instance
	static OViSESceneHandling *mInstance;

	/// Scene managers this SceneHandler works on.
	OViSEScnMgrMap mSceneManagers;

	/// Ray scene querys for object selection
	OViSERayQueryMap mObjectSelectionQuerys;

	/// Map of maps of selected scene nodes
	OViSESelections mObjectSelectionsMap;

	/// Map of all object titles
	OViSEObjectTitleVector mObjectTitlesVector;
};

#endif /*OVISESCENEHANDLING_H_*/
