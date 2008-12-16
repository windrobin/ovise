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
	class dotSceneExternals : virtual public dotSceneObject
    {
	public:
		std::list<dotSceneItem> items; /**< Attribute items.*/

		/**
		 * This function adds a new dotSceneItem to the list "items".
		 * At last, a proctected acess is not fully implemented.
		 * @param item A dotSceneItem-object.
		 * @return Returns a bool value. TRUE, when there was no problem.
		 */
        bool addItem(dotSceneItem someItem);

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
        dotSceneExternals();
    };
}