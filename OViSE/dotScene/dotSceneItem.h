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
    class dotSceneItem : virtual public dotSceneObject
    {
	private:
		std::string _Type;	/**< Property Type.*/
		dotSceneFile _File; /**< Property File.*/

	public:
		std::string get_Type() const;		/**< Get-method for property Type. @return Returns type as std::string.*/
		dotSceneFile get_File() const;		/**< Get-method for property File. @return Returns a dotSceneFile-object.*/
		void set_Type(std::string value);	/**< Set-method for property Type. @param value Value of a std::string.*/
		void set_File(dotSceneFile value);	/**< Set-method for property File. @param value A dotSceneFile-object.*/
		bool IsValid() const;				/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. It calls constructor of baseobject.
		 */
        dotSceneItem();

		/**
		 * Standard-constructor.
		 * The dotScene-objects have to be constructed before.
		 * @param str_type type-value in string-format. Has to be "material" for material-ressources.
		 * @param obj_file A pre-constrcted dotSceneFile-object.
		 */
		dotSceneItem(std::string str_Type, dotSceneFile obj_File);

		/**
		 * Simple destructor.
		 */
        ~dotSceneItem();
    };
}
