#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This object holds values needed for attentuation description in ogre.
	 * Attentuation works only on light-spots and light-points.
	 */
    class dotSceneLightAttenuation : public dotSceneObject
    {
	private:
		double _range;		/**< Property range. Discribes the maximum range of light-source.*/
		double _constant;	/**< Property constant. Describes the constant factor light-attentuation. 1.0 used in most cases.*/
		double _linear;		/**< Property linear. Discribes the linear factor of attentuation. When value is 1.0, it means that 100% light disappears after one pixel. Values lower than 0.01 or 0.001 are usual.*/
		double _quadratic;	/**< Property quadratic. Discribes the quadratic factor of attentuation. Value must be very low, because the effect is quite strong. Opically, this effects is very nice.*/

		void set_range(double value);		/**< Set-method for property range. @param value Value of double.*/
		void set_constant(double value);	/**< Set-method for property constant. @param value Value of double.*/
		void set_linear(double value);		/**< Set-method for property linear. @param value Value of double.*/
		void set_quadratic(double value);	/**< Set-method for property quadratic. @param value Value of double.*/
	public:
		double get_range() const;		/**< Get-method for property range. @return Returns range as double.*/
		double get_constant() const;	/**< Get-method for property constant. @return Returns constant as double.*/
		double get_linear() const;		/**< Get-method for property linear. @return Returns linear as double.*/
		double get_quadratic() const;	/**< Get-method for property quadratic. @return Returns quadratic as double.*/

        /**
		 * Simple constructor. It calls the constructor of baseobject.
		 */
		dotSceneLightAttenuation();

		/**
		 * Constructor for string-parameters. All strings will be parsed automatically to double-format.
		 * @param str_range range-value in std::string-format.
		 * @param str_constant constant-value in std::string-format.
		 * @param str_linear linear-value in std::string-format.
		 * @param str_quadratic quadratic-value in std::string-format.
		 */
		dotSceneLightAttenuation(std::string str_range, std::string str_constant, std::string str_linear, std::string str_quadratic);

		/**
		 * Constructor for double-parameters.
		 * @param double_range range-value in double-format.
		 * @param double_constant constant-value in double-format.
		 * @param double_linear linear-value in double-format.
		 * @param double_quadratic quadratic-value in double-format.
		 */
		dotSceneLightAttenuation(double double_range, double double_constant, double double_linear, double double_quadratic);

		/**
		 * Simple destructor.
		 */
        ~dotSceneLightAttenuation();
    };
}
