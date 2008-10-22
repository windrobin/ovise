#ifndef dotSceneProperty_h_
#define dotSceneProperty_h_
#include "dotSceneProperty.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/** 
	 * The idea of "UserData" is not documented, So far, is implemented.
	 */
	class dotSceneUserData : public dotSceneObject
    {
	public:
		std::list<dotSceneProperty> properties; /**< List of properties.*/
		/**
		 * This function adds a new dotSceneProperty to the list "properties".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected acess is not fully implemented.
		 * @param Property A dotSceneProperty-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		void addProperty(dotSceneProperty Property);

		/**
		 * Simple constructor.
		 */
		dotSceneUserData(); 
    };
}
