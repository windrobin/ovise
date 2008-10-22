#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneFile_h_
#define dotSceneFile_h_
#include "dotSceneFile.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class holds a file-reference and information obout its type. For example "material".
	 */
    class dotSceneItem : public dotSceneObject
    {
	private:
		std::string _type;	/**< Property type.*/
		dotSceneFile _file; /**< Property file.*/

		void set_type(std::string value);	/**< Set-method for property type. @param value Value of a std::string.*/
		void set_file(dotSceneFile value);	/**< Set-method for property file. @param value A dotSceneFile-object.*/

	public:
		std::string get_type() const;	/**< Get-method for property type. @return Returns type as std::string.*/
		dotSceneFile get_file() const;	/**< Get-method for property file. @return Returns a dotSceneFile-object.*/

		/**
		 * Simple constructor. It calls the constructor of baseobject.
		 */
        dotSceneItem();

		/**
		 * Standard-constructor.
		 * The dotScene-objects have to be constructed before.
		 * @param str_type type-value in string-format. Has to be "material" for material-ressources.
		 * @param obj_file A pre-constrcted dotSceneFile-object.
		 */
		dotSceneItem(std::string str_type, dotSceneFile obj_file);

		/**
		 * Simple destructor.
		 */
        ~dotSceneItem();
    };
}
