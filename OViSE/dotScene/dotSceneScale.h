#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the x, y and z values of an 3D-vector, interpreted as a scale-factors.
	 */
    class dotSceneScale : public dotSceneObject
    {	
	private:
		double _x; /**< Property x. X value.*/
		double _y; /**< Property y. Y value.*/
		double _z; /**< Property z. Z value.*/

		void set_x(double value);	/**< Set-method for property x. @param value Value of double.*/
		void set_y(double value);	/**< Set-method for property y. @param value Value of double.*/
		void set_z(double value);	/**< Set-method for property z. @param value Value of double.*/

	public:
		double get_x() const;	/**< Get-method for property x. @return Returns x as double.*/
		double get_y() const;	/**< Get-method for property y. @return Returns y as double.*/
		double get_z() const;	/**< Get-method for property z. @return Returns z as double.*/

		/**
		 * Simple constructor. It calls the constructor of base-object.
		 */
		dotSceneScale();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_x X-value in std::string-format.
		 * @param str_y Y-value in std::string-format.
		 * @param str_z Z-value in std::string-format.
		 */
		dotSceneScale(std::string str_x, std::string str_y, std::string str_z);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_x X-value in double-format.
		 * @param double_y Y-value in double-format.
		 * @param double_z Z-value in double-format.
		 */
		dotSceneScale(double double_x, double double_y, double double_z);

		/**
		 * Simple destructor.
		 */
        ~dotSceneScale();
    };
}