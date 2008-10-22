#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This object discribes the angles of intensities of a light-spot.
	 * The values are abstract here, not fixed to degree or radian-values.
	 */
	class dotSceneLightRange : public dotSceneObject
    {
	private:
		double _inner;	/**< Property inner. Inner angle of light-spot. Defines region of intensive light. MUST be smaller than "outer"-value.*/
		double _outer;	/**< Property outer. Outer angle of light-spot. Defines region of decending light. MUST be greather than "inner"-value.*/
		double _falloff;/**< Property falloff. The "falloff" discribes the functionality between inner and outer angle. 1.0 is the neutral value, representing liniarity.*/
		
		void set_inner(double value);	/**< Set-method for property inner. @param value Value of double.*/
		void set_outer(double value);	/**< Set-method for property outer. @param value Value of double.*/
		void set_falloff(double value);	/**< Set-method for property falloff. @param value Value of double.*/

	public:
		double get_inner() const;	/**< Get-method for property inner. @return Returns inner as double.*/
		double get_outer() const;	/**< Get-method for property outer. @return Returns outer as double.*/
		double get_falloff() const;	/**< Get-method for property falloff. @return Returns falloff as double.*/

		/**
		 * Simple constructor. It calls the constructor of baseobject.
		 */
		dotSceneLightRange();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_inner inner-value in std::string-format.
		 * @param str_outer outer-value in std::string-format.
		 * @param str_falloff falloff-value in std::string-format.
		 */
		dotSceneLightRange(std::string str_inner, std::string str_outer, std::string str_falloff);

		/** 
		 * Standard-constructor for direct value-parameters.
		 * @param double_inner inner-value in double-format.
		 * @param double_outer outer-value in double-format.
		 * @param double_falloff falloff-value in double-format.
		 */
        dotSceneLightRange(double, double, double);

		/**
		 * Simple destructor.
		 */
        ~dotSceneLightRange();
    };
}

