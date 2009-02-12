#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the 3x3 values of a rotation-matrix.
	 */
    class dotSceneAxisXYZ : virtual public dotSceneObject
    {
	private:
		double _xAxisX;	/**< Property xAxisX. xX value of 3x3-axis-matrix.*/
		double _xAxisY;	/**< Property xAxisY. xY value of 3x3-axis-matrix.*/
		double _xAxisZ;	/**< Property xAxisZ. xZ value of 3x3-axis-matrix.*/
		double _yAxisX;	/**< Property yAxisX. yX value of 3x3-axis-matrix.*/
		double _yAxisY;	/**< Property yAxisY. yY value of 3x3-axis-matrix.*/
		double _yAxisZ;	/**< Property yAxisZ. yZ value of 3x3-axis-matrix.*/
		double _zAxisX;	/**< Property zAxisX. zX value of 3x3-axis-matrix.*/
		double _zAxisY;	/**< Property zAxisY. zY value of 3x3-axis-matrix.*/
		double _zAxisZ;	/**< Property zAxisZ. zZ value of 3x3-axis-matrix.*/

	public:
		double get_xAxisX() const;	/**< Get-method for property xAxisX. @return Returns xAxisX as double.*/
		double get_xAxisY() const;	/**< Get-method for property xAxisY. @return Returns xAxisY as double.*/
		double get_xAxisZ() const;	/**< Get-method for property xAxisZ. @return Returns xAxisZ as double.*/
		double get_yAxisX() const;	/**< Get-method for property yAxisX. @return Returns yAxisX as double.*/
		double get_yAxisY() const;	/**< Get-method for property yAxisY. @return Returns yAxisY as double.*/
		double get_yAxisZ() const;	/**< Get-method for property yAxisZ. @return Returns yAxisZ as double.*/
		double get_zAxisX() const;	/**< Get-method for property zAxisX. @return Returns zAxisX as double.*/
		double get_zAxisY() const;	/**< Get-method for property zAxisY. @return Returns zAxisY as double.*/
		double get_zAxisZ() const;	/**< Get-method for property zAxisZ. @return Returns zAxisZ as double.*/

		void set_xAxisX(double value);	/**< Set-method for property xAxisX. @param value Value of double.*/
		void set_xAxisY(double value);	/**< Set-method for property xAxisY. @param value Value of double.*/
		void set_xAxisZ(double value);	/**< Set-method for property xAxisZ. @param value Value of double.*/
		void set_yAxisX(double value);	/**< Set-method for property yAxisX. @param value Value of double.*/
		void set_yAxisY(double value);	/**< Set-method for property yAxisY. @param value Value of double.*/
		void set_yAxisZ(double value);	/**< Set-method for property yAxisZ. @param value Value of double.*/
		void set_zAxisX(double value);	/**< Set-method for property zAxisX. @param value Value of double.*/
		void set_zAxisY(double value);	/**< Set-method for property zAxisY. @param value Value of double.*/
		void set_zAxisZ(double value);	/**< Set-method for property zAxisZ. @param value Value of double.*/

		void set_xAxisX(std::string value);	/**< Set-method for property xAxisX. @param value Value of std::string.*/
		void set_xAxisY(std::string value);	/**< Set-method for property xAxisY. @param value Value of std::string.*/
		void set_xAxisZ(std::string value);	/**< Set-method for property xAxisZ. @param value Value of std::string.*/
		void set_yAxisX(std::string value);	/**< Set-method for property yAxisX. @param value Value of std::string.*/
		void set_yAxisY(std::string value);	/**< Set-method for property yAxisY. @param value Value of std::string.*/
		void set_yAxisZ(std::string value);	/**< Set-method for property yAxisZ. @param value Value of std::string.*/
		void set_zAxisX(std::string value);	/**< Set-method for property zAxisX. @param value Value of std::string.*/
		void set_zAxisY(std::string value);	/**< Set-method for property zAxisY. @param value Value of std::string.*/
		void set_zAxisZ(std::string value);	/**< Set-method for property zAxisZ. @param value Value of std::string.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. 
		 */
		dotSceneAxisXYZ();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * The order of parameters here corresponds with the order in a dotScene XML-document.
		 * @param str_xAxisX xAxisX-value in std::string-format.
		 * @param str_xAxisY xAxisY-value in std::string-format.
		 * @param str_xAxisZ xAxisZ-value in std::string-format.
		 * @param str_yAxisX yAxisX-value in std::string-format.
		 * @param str_yAxisY yAxisY-value in std::string-format.
		 * @param str_yAxisZ yAxisZ-value in std::string-format.
		 * @param str_zAxisX zAxisX-value in std::string-format.
		 * @param str_zAxisY zAxisY-value in std::string-format.
		 * @param str_zAxisZ zAxisZ-value in std::string-format.
		 */
		dotSceneAxisXYZ(std::string str_xAxisX, std::string str_xAxisY, std::string str_xAxisZ, std::string str_yAxisX, std::string str_yAxisY, std::string str_yAxisZ, std::string str_zAxisX, std::string str_zAxisY, std::string str_zAxisZ);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_xAxisX xAxisX-value in double-format.
		 * @param double_xAxisY xAxisY-value in double-format.
		 * @param double_xAxisZ xAxisZ-value in double-format.
		 * @param double_yAxisX yAxisX-value in double-format.
		 * @param double_yAxisY yAxisY-value in double-format.
		 * @param double_yAxisZ yAxisZ-value in double-format.
		 * @param double_zAxisX zAxisX-value in double-format.
		 * @param double_zAxisY zAxisY-value in double-format.
		 * @param double_zAxisZ zAxisZ-value in double-format.
		 */
		dotSceneAxisXYZ(double double_xAxisX, double double_xAxisY, double double_xAxisZ, double double_yAxisX, double double_yAxisY, double double_yAxisZ, double double_zAxisX, double double_zAxisY, double double_zAxisZ);
    };
}
