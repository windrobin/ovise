#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneAngleAxisEnums_h_
#define dotSceneAngleAxisEnums_h_
#include "dotSceneAngleAxisEnums.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the 3D-vector plus aditional angle (and information about it units)
	 */
    class dotSceneAngleAxis : virtual public dotSceneObject
    {
	private:
		double _Angle;		/**< Property Angle. Ratation-angle.*/
		dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits _AngleUnit;	/**< Property AngleUnit. AngleUnit value of enum dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits.*/
		double _x;			/**< Property x. X value of ratation-base.*/
		double _y;			/**< Property y. Y value of ratation-base.*/
		double _z;			/**< Property z. Z value of ratation-base.*/

	public:
		double get_Angle() const;	/**< Get-method for property Angle. @return Returns xAxisX as double.*/
		dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits get_AngleUnit() const;	/**< Get-method for property AngleUnit. @return Returns AngleUnit as enum dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits.*/
		double get_x() const;		/**< Get-method for property x. @return Returns x as double.*/
		double get_y() const;		/**< Get-method for property y. @return Returns y as double.*/
		double get_z() const;		/**< Get-method for property z. @return Returns z as double.*/

		void set_Angle(double value);	/**< Set-method for property Angle. @param value Value of double.*/
		void set_AngleUnit(dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits value);	/**< Set-method for property AngleAxis. @param value Value of enum dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits.*/
		void set_x(double value);		/**< Set-method for property x. @param value Value of double.*/
		void set_y(double value);		/**< Set-method for property y. @param value Value of double.*/
		void set_z(double value);		/**< Set-method for property z. @param value Value of double.*/

		void set_Angle(std::string value);		/**< Set-method for property xAxisX. @param value Value of std::string.*/
		void set_AngleUnit(std::string value);	/**< Set-method for property xAxisY. @param value Value of std::string.*/
		void set_x(std::string value);			/**< Set-method for property xAxisZ. @param value Value of std::string.*/
		void set_y(std::string value);			/**< Set-method for property yAxisX. @param value Value of std::string.*/
		void set_z(std::string value);			/**< Set-method for property yAxisY. @param value Value of std::string.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. 
		 */
		dotSceneAngleAxis();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double or enum-format.
		 * The order of parameters here corresponds with the order in a dotScene XML-document.
		 * @param str_Angle Angle-value in std::string-format.
		 * @param str_AngleUnit AngleUnit-value in std::string-format.
		 * @param str_x X-value in std::string-format.
		 * @param str_y Y-value in std::string-format.
		 * @param str_z Z-value in std::string-format.
		 */
		dotSceneAngleAxis(std::string str_Angle, std::string str_AngleUnit, std::string str_x, std::string str_y, std::string str_z);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_Angle Angle-value in double-format.
		 * @param enum_AngleUnit AngleUnit-value in enum dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits-format.
		 * @param double_x X-value in double-format.
		 * @param double_y Y-value in double-format.
		 * @param double_z Z-value in double-format.
		 */
		dotSceneAngleAxis(double double_Angle, dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits enum_AngleUnit, double double_x, double double_y, double double_z);
    };
}