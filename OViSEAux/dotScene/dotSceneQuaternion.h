#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the w, x, y and z values of an 4D-vector, interpreted as quaternion.
	 */
    class dotSceneQuaternion : virtual public dotSceneObject
    {
	private:
		double _qx;					/**< Property qx. X value of quaternion.*/
		double _qy;					/**< Property qy. Y value of quaternion.*/
		double _qw;					/**< Property qz. Z value of quaternion.*/
		double _qz;					/**< Property qw. W value of quaternion.*/

	public:
		double get_qx() const;		/**< Get-method for property qx. @return Returns qx as double.*/
		double get_qy() const;		/**< Get-method for property qy. @return Returns qy as double.*/
		double get_qz() const;		/**< Get-method for property qz. @return Returns qz as double.*/
		double get_qw() const;		/**< Get-method for property qw. @return Returns qw as double.*/

		void set_qx(double value);	/**< Set-method for property qx. @param value Value of double.*/
		void set_qy(double value);	/**< Set-method for property qy. @param value Value of double.*/
		void set_qz(double value);	/**< Set-method for property qz. @param value Value of double.*/
		void set_qw(double value);	/**< Set-method for property qw. @param value Value of double.*/

		void set_qx(std::string value);	/**< Set-method for property qx. @param value Value in std::string-format. Will be parsed to double.*/
		void set_qy(std::string value);	/**< Set-method for property qy. @param value Value in std::string-format. Will be parsed to double.*/
		void set_qz(std::string value);	/**< Set-method for property qz. @param value Value in std::string-format. Will be parsed to double.*/
		void set_qw(std::string value);	/**< Set-method for property qw. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor. 
		 */
		dotSceneQuaternion();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * The order of parameters here corresponds with the order in a dotScene XML-document.
		 * @param str_qx qX-value in std::string-format.
		 * @param str_qy qY-value in std::string-format.
		 * @param str_qz qZ-value in std::string-format.
		 * @param str_qw qW-value in std::string-format.
		 */
		dotSceneQuaternion(std::string str_qx, std::string str_qy, std::string str_qz, std::string str_qw);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_qx qX-value in double-format.
		 * @param double_qy qY-value in double-format.
		 * @param double_qz qZ-value in double-format.
		 * @param double_qw qW-value in double-format.
		 */
		dotSceneQuaternion(double double_qx, double double_qy, double double_qz, double double_qw);
    };
}
