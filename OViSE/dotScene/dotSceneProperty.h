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
	class dotSceneProperty : virtual public dotSceneObject
    {
	private:
		std::string _Type;		/**< Property type.*/
        std::string _Name;		/**< Property name.*/
        std::string _Data;		/**< Property data.*/

	public:
		std::string get_Type() const;		/**< Get-method for property Type. @return Returns Type as std::string.*/
		std::string get_Name() const;		/**< Get-method for property Name. @return Returns Name as std::string.*/
		std::string get_Data() const;		/**< Get-method for property Data. @return Returns Data as std::string.*/

		void set_Type(std::string value);	/**< Set-method for property Type. @param value Value of a std::string.*/	
		void set_Name(std::string value);	/**< Set-method for property Name. @param value Value of a std::string.*/
		void set_Data(std::string value);	/**< Set-method for property Data. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. It calls constructor of baseobject.
		 */
		dotSceneProperty();

		/**
		 * Constructor for string-parameters.
		 * This Object simply works as a container.
		 * @param str_Type Attribute "Type" form dotScene XML-document in string-format.
		 * @param str_Name Attribute "Name" form dotScene XML-document in string-format.
		 * @param str_Data Attribute "Data" form dotScene XML-document in string-format.
		 */
		dotSceneProperty(std::string str_Type, std::string str_Name, std::string str_Data);

		/**
		 * Simple destructor.
		 */
        ~dotSceneProperty();
    };
}
