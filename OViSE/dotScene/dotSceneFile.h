#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class holds a string, representing a filename.
	 */
	class dotSceneFile : public dotSceneObject
    {
	private:
		std::string _name; /**< Property name. A filename in std::string -format.*/

		void set_name(std::string value);	/**< Set-method for property name. @param value Value of a std::string.*/

	public:
		std::string get_name();				/**< Get-method for property name. @return Returns name as std::string.*/

		/**
		 * Simple constructor.
		 * Implemented, because position-attribute is #IMPLIED but not #REQUIRED in original dotScene.dtd.
		 * It calls the constructor of baseobject.
		 */
		dotSceneFile();

		/**
		 * Constructor for filestring-object.
		 * @param name Filename-value in std::string -format.
		 */
		dotSceneFile(std::string name);
    };
}
