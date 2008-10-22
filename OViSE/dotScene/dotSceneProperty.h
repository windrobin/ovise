#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This Object is usable, but not complete.
	 * ATTENTION: Idea of UserData(Reference) is not documented.
	 */
	class dotSceneProperty : public dotSceneObject
    {
	public:
		std::string type;	//**< Property type.*/
        std::string name;	//**< Property name.*/
        std::string data;	//**< Property data.*/

		/**
		 * Constructor for string-parameters.
		 * This Object simply works as a container.
		 * @param string_type Attribute "type" form dotScene XML-document in string-format.
		 * @param string_name Attribute "name" form dotScene XML-document in string-format.
		 * @param string_data Attribute "data" form dotScene XML-document in string-format.
		 */
		dotSceneProperty(std::string string_type, std::string string_name, std::string string_data);

		/**
		 * Simple destructor.
		 */
        ~dotSceneProperty();
    };
}
