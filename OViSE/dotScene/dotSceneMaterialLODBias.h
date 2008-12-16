#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class contains additional data for entities.
	 */
    class dotSceneMaterialLODBias : virtual public dotSceneObject 
    {
	private:
		std::string _Factor;	/**< Property Factor.*/
		double _MaxDetailIndex;	/**< Property MaxDetailIndex.*/
		double _MinDetailIndex;	/**< Property MinDetailIndex.*/

	public:
		std::string get_Factor() const;				/**< Get-method for property Factor. @return Returns Factor as std::string.*/
		double get_MaxDetailIndex() const;			/**< Get-method for property MaxDetailIndex. @return Returns MaxDetailIndex as double.*/
		double get_MinDetailIndex() const;			/**< Get-method for property MinDetailIndex. @return Returns MinDetailIndex as double.*/

		void set_Factor(std::string value);			/**< Set-method for property Factor. @param value Value of std::string.*/
		void set_MaxDetailIndex(double value);		/**< Set-method for property MaxDetailIndex. @param value Value of double.*/
		void set_MinDetailIndex(double value);		/**< Set-method for property MinDetailIndex. @param value Value of double.*/

		void set_MaxDetailIndex(std::string value);	/**< Set-method for property MaxDetailIndex. @param value Value in std::string-format. Will be parsed to double.*/
		void set_MinDetailIndex(std::string value);	/**< Set-method for property MinDetailIndex. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneMaterialLODBias(); 
		
		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_Factor Untested. Undocumented.
		 * @param str_MaxDetailIndex Untested. Undocumented.
		 * @param str_MinDetailIndex Untested. Undocumented.
		 */
		dotSceneMaterialLODBias(std::string str_Factor, std::string  str_MaxDetailIndex, std::string str_MinDetailIndex);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param str_Factor Untested. Undocumented.
		 * @param double_MaxDetailIndex Untested. Undocumented.
		 * @param double_MinDetailIndex Untested. Undocumented.
		 */
		dotSceneMaterialLODBias(std::string str_Factor, double double_MaxDetailIndex, double double_MinDetailIndex);
    };
}
