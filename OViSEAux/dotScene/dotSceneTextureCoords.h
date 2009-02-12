#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneFloatRect_h_
#define dotSceneFloatRect_h_
#include "dotSceneFloatRect.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class contains dotSceneFloatRect-objects, which are stored in a list.
	 */
	class dotSceneTextureCoords : virtual public dotSceneObject
    {
	public:
		std::list<dotSceneFloatRect> listOfFloatRect;	/**< This list contains dotSceneFloatRect-objects.*/

		bool IsValid() const;					/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * This function adds a new dotSceneFloatRect to the list "listOfDotSceneFloatRect".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected access is not fully implemented.
		 * @param someFloatRect A dotSceneFloatRect-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
        bool addFloatRect(dotSceneFloatRect someFloatRect);

		/**
		 * Simple constructor.
		 */
		dotSceneTextureCoords(); 
    };
}