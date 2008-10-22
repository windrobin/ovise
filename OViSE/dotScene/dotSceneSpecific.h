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
	class dotSceneSpecific : public dotSceneObject
	{
	public:
		dotSceneSpecific();

		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 * @param ElementTag Has to be a possible value of dotSceneElementTags.
		 */
		dotSceneSpecific(dotSceneElementTags ElementTag);

		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 * @param ElenentName A std::string value, which can be interpreted as dotSceneElementTags.
		 */
		dotSceneSpecific(std::string ElenentName);
		//dotSceneSpecific(dotSceneSpecific); /// Simple copy-constructor. // <param name="obj">Object, whiche values will be copied.</param>
		
		/**
		 * Simple destructor.
		 */
		~dotSceneSpecific();
	};
}