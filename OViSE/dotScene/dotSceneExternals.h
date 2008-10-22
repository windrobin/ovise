#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneItem_h_
#define dotSceneItem_h_
#include "dotSceneItem.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in externals-definition.
	 */
	class dotSceneExternals : public dotSceneObject
    {
	public:
		std::list<dotSceneItem> items; /**< Attribute items.*/

		/**
		 * This function adds a new dotSceneItem to the list "items".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected acess is not fully implemented.
		 * @param item A dotSceneItem-object.
		 * @return Returns a bool value. TRUE, when there was no problem.
		 */
        bool addItem(dotSceneItem item);

		/**
		 * Simple constructor.
		 */
        dotSceneExternals();
    };
}