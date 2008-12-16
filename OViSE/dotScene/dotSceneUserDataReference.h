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
	class dotSceneUserDataReference : virtual public dotSceneObject
    {
	private:
		std::string _ID;	/**< Property ID. An additional ID can be "hanged on" a dotSceneOnject.*/		
	public:
		std::string get_ID() const;		/**< Get-method for property ID. @return Returns "ID" as a std::string.*/
		
		void set_ID(std::string value);	/**< Set-method for property ID. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneUserDataReference();

		/**
		 * Constructor with parameters.
		 * @param str_ID ID as a std::string-value.
		 */
		dotSceneUserDataReference(std::string str_ID);
    };
}
