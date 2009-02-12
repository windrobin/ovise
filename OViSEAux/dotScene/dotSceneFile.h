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
	class dotSceneFile : virtual public dotSceneObject
    {
	private:
		std::string _FileName; /**< Property name. A filename in std::string -format.*/

	public:
		std::string get_FileName() const;		/**< Get-method for property name. @return Returns name as std::string.*/
		void set_FileName(std::string value);	/**< Set-method for property name. @param value Value of a std::string.*/
		bool IsValid() const;					/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

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
		dotSceneFile(std::string FileName);
    };
}
