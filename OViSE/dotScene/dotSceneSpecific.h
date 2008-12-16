#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * Abstract basic-class for specific-classes.
	 * All specific-objects, like camera, light and entity inherit from it.
	 */
	class dotSceneSpecific : virtual public dotSceneObject
	{
	public:
		virtual bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor for initialisations.
		 * It calls the constructor of baseobject.
		 */
		dotSceneSpecific();

		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 * @param incomingTag Has to be a possible value of dotSceneElementTags.
		 */
		dotSceneSpecific(dotSceneEnums::dotSceneElementTags incomingTag);
	};
}