#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	using namespace dotSceneEnums::dotSceneGeneralEnums;

	/**
	 * This class contains values for a 3D-direction definition.
	 */
    class dotSceneDirection : virtual public dotSceneObject
    {
	private:
		double _x;	/**< Property x. X value of 3D-base-vector.*/
		double _y;	/**< Property y. Y value of 3D-base-vector.*/
		double _z;	/**< Property z. Z value of 3D-base-vector.*/
		RelativeTo _RelativeTo;	/**< Property RelativeTo. yX value of 3x3-axis-matrix.*/
		int _LocalDirX;	/**< Property LocalDirX. X value of direction-normal.*/
		int _LocalDirY;	/**< Property LocalDirY. Y value of direction-normal.*/
		int _LocalDirZ;	/**< Property LocalDirZ. Z value of direction-normal.*/

	public:
		double get_x() const;	/**< Get-method for property x. @return Returns x as double.*/
		double get_y() const;	/**< Get-method for property y. @return Returns y as double.*/
		double get_z() const;	/**< Get-method for property z. @return Returns z as double.*/
		RelativeTo get_RelativeTo() const;	/**< Get-method for property RelativeTo. @return Returns RelativeTo as enum .*/
		int get_LocalDirX() const;	/**< Get-method for property LocalDirX. @return Returns LocalDirX as int.*/
		int get_LocalDirY() const;	/**< Get-method for property LocalDirY. @return Returns LocalDirY as int.*/
		int get_LocalDirZ() const;	/**< Get-method for property LocalDirZ. @return Returns LocalDirZ as int.*/

		void set_x(double value);	/**< Set-method for property x. @param value Value of double.*/
		void set_y(double value);	/**< Set-method for property y. @param value Value of double.*/
		void set_z(double value);	/**< Set-method for property z. @param value Value of double.*/
		void set_RelativeTo(RelativeTo value);	/**< Set-method for property RelativeTo. @param value Value of enum dotSceneEnums::dotSceneDirectionEnums::RelativeTo.*/
		void set_LocalDirX(int value);	/**< Set-method for property LocalDirX. @param value Value of int.*/
		void set_LocalDirY(int value);	/**< Set-method for property LocalDirY. @param value Value of int.*/
		void set_LocalDirZ(int value);	/**< Set-method for property LocalDirZ. @param value Value of int.*/

		void set_x(std::string value);	/**< Set-method for property x. @param value Value of std::string.*/
		void set_y(std::string value);	/**< Set-method for property y. @param value Value of std::string.*/
		void set_z(std::string value);	/**< Set-method for property z. @param value Value of std::string.*/
		void set_RelativeTo(std::string value);	/**< Set-method for property RelativeTo. @param value Value of std::string.*/
		void set_LocalDirX(std::string value);	/**< Set-method for property LocalDirX. @param value Value of std::string.*/
		void set_LocalDirY(std::string value);	/**< Set-method for property LocalDirY. @param value Value of std::string.*/
		void set_LocalDirZ(std::string value);	/**< Set-method for property LocalDirZ. @param value Value of std::string.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. 
		 */
		dotSceneDirection();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * The order of parameters here corresponds with the order in a dotScene XML-document.
		 * @param str_x x-value in std::string-format.
		 * @param str_y y-value in std::string-format.
		 * @param str_z z-value in std::string-format.
		 * @param str_RelativeTo RelativeTo-value in std::string-format.
		 * @param str_LocalDirX LocalDirX-value in std::string-format.
		 * @param str_LocalDirY LocalDirY-value in std::string-format.
		 * @param str_LocalDirZ LocalDirZ-value in std::string-format.
		 */
		dotSceneDirection(std::string str_x, std::string str_y, std::string str_z, std::string str_RelativeTo, std::string str_LocalDirX, std::string str_LocalDirY, std::string str_LocalDirZ);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_x x-value in double-format.
		 * @param double_y y-value in double-format.
		 * @param double_z z-value in double-format.
		 * @param enum_RelativeTo RelativeTo-value in enum dotSceneEnums::dotSceneDirectionEnums::RelativeTo-format.
		 * @param int_LocalDirX LocalDirX-value in int-format.
		 * @param int_LocalDirY LocalDirY-value in int-format.
		 * @param int_LocalDirZ LocalDirZ-value in int-format.
		 */
		dotSceneDirection(double double_x, double double_y, double double_z, RelativeTo enum_RelativeTo, int int_LocalDirX, int int_LocalDirY, int int_LocalDirZ);
    };
}
