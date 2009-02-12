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
	class dotSceneSpotLightRange : virtual public dotSceneObject
    {
	private:
		double _Inner;							/**< Property Inner. Inner angle of light-spot. Defines region of intensive light. MUST be smaller than "outer"-value.*/
		double _Outer;							/**< Property Outer. Outer angle of light-spot. Defines region of decending light. MUST be greather than "inner"-value.*/
		double _Falloff;						/**< Property Falloff. The "falloff" discribes the functionality between inner and outer angle. 1.0 is the neutral value, representing liniarity.*/
		
	public:
		double get_Inner() const;				/**< Get-method for property Inner. @return Returns Inner as double.*/
		double get_Outer() const;				/**< Get-method for property Outer. @return Returns Outer as double.*/
		double get_Falloff() const;				/**< Get-method for property Falloff. @return Returns Falloff as double.*/

		void set_Inner(double value);			/**< Set-method for property Inner. @param value Value of double.*/
		void set_Outer(double value);			/**< Set-method for property Outer. @param value Value of double.*/
		void set_Falloff(double value);			/**< Set-method for property Falloff. @param value Value of double.*/

		void set_Inner(std::string value);		/**< Set-method for property Inner. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Outer(std::string value);		/**< Set-method for property Outer. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Falloff(std::string value);	/**< Set-method for property Falloff. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;					/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneSpotLightRange();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_Inner Inner-value in std::string-format.
		 * @param str_Outer Outer-value in std::string-format.
		 * @param str_Falloff Falloff-value in std::string-format.
		 */
		dotSceneSpotLightRange(std::string str_Inner, std::string str_Outer, std::string str_Falloff);

		/** 
		 * Standard-constructor for direct value-parameters.
		 * @param double_Inner Inner-value in double-format.
		 * @param double_Outer Outer-value in double-format.
		 * @param double_Falloff Falloff-value in double-format.
		 */
        dotSceneSpotLightRange(double double_Inner, double double_Outer, double double_Falloff);
    };
}

