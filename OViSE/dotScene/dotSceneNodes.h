#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneNode_h_
#define dotSceneNode_h_
#include "dotSceneNode.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class contains dotSceneNode-objects, which are stored in a list.
	 */
	class dotSceneNodes : public dotSceneObject
    {
	public:
		std::list<dotSceneNode> listOfNodes;	/**< This list contains dotSceneNode-objects.*/

		/**
		 * This function adds a new dotSceneNode to the list "nodes".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected acess is not fully implemented.
		 * @param node A dotSceneNode-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
        bool addItem(dotSceneNode node);

		/**
		 * Simple constructor.
		 */
		dotSceneNodes(); 
    };
}
