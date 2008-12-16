#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * Basic-class for 3D-classes.
	 * All 3D-classes inherit from dotScene3D.
	 * In C# this class was planned as abstract class.
	 * In C/C++ there is no difference to a normal class anymore.
	 * But readers and interpreters should use the 3D-classes, which
	 * inherit from this dotScene3D.
	 */
    class dotScene3D : virtual public dotSceneObject 
    {
	private:
		double _x;						/**< Property x. X value.*/
		double _y;						/**< Property y. Y value.*/
		double _z;						/**< Property z. Z value.*/

	public:
		double get_x() const;			/**< Get-method for property x. @return Returns x as double.*/
		double get_y() const;			/**< Get-method for property y. @return Returns y as double.*/
		double get_z() const;			/**< Get-method for property z. @return Returns z as double.*/

		void set_x(double value);		/**< Set-method for property x. @param value Value of double.*/
		void set_y(double value);		/**< Set-method for property y. @param value Value of double.*/
		void set_z(double value);		/**< Set-method for property z. @param value Value of double.*/

		void set_x(std::string value);	/**< Set-method for property x. @param value Value in std::string-format. Will be parsed to double.*/
		void set_y(std::string value);	/**< Set-method for property y. @param value Value in std::string-format. Will be parsed to double.*/
		void set_z(std::string value);	/**< Set-method for property z. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 * @param incomingTag Has to be a possible value of dotSceneElementTags.
		 */
		dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag); 
		
		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
 		 * @param incomingTag Enum-Value of a dotScene-XML-Tag. The tags a defines in dotSceneElementTags.h.
		 * @param str_x X-value in std::string-format.
		 * @param str_y Y-value in std::string-format.
		 * @param str_z Z-value in std::string-format.
		 */
		dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag, std::string str_x, std::string str_y, std::string str_z);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param incomingTag Enum-Value of a dotScene-XML-Tag. The tags a defines in dotSceneElementTags.h.
		 * @param double_x X-value in double-format.
		 * @param double_y Y-value in double-format.
		 * @param double_z Z-value in double-format.
		 */
		dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag, double double_x, double double_y, double double_z);
    };
}
