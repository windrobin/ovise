/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This file is a dictionary for important comments, used as markup. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Tag: DOUBLE_SAFETY_DIRECTIVE
// Used in: OgreMediator
// Means: There are no qualified unique names in Ogre3D-engine on global level.
//        Because of our unique-name-workarround, a unique name has to pass two checks,
//        instead of one:
//        o First:		Does the name contains a substring which corresponds to a Ogre-Object?
//          Example:	Substring "_Entity_" is included in unique name of every Ogre::Entity-object,
//						placed by OgreMediator.
//        o Second:		Contains Is there a object with that unique name in Ogre3D-engine for sure?
//          Example:	Returns SceneManager::hasEntity(...) true, with give unique name?


// TODO-List:
// IN: SelectionManager
// WHAT: Actually only TS_World is used for Rotation.
// GOAL: Used combobox for selection between different transformspaces