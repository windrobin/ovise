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
    class dotSceneLightAttenuation : virtual public dotSceneObject
    {
	private:
		double _Range;							/**< Property Range. Discribes the maximum Range of light-source.*/
		double _Constant;						/**< Property Constant. Describes the Constant factor light-attentuation. 1.0 used in most cases.*/
		double _Linear;							/**< Property Linear. Discribes the Linear factor of attentuation. When value is 1.0, it means that 100% light disappears after one pixel. Values lower than 0.01 or 0.001 are usual.*/
		double _Quadratic;						/**< Property Quadratic. Discribes the Quadratic factor of attentuation. Value must be very low, because the effect is quite strong. Opically, this effects is very nice.*/

	public:
		double get_Range() const;				/**< Get-method for property Range. @return Returns Range as double.*/
		double get_Constant() const;			/**< Get-method for property Constant. @return Returns Constant as double.*/
		double get_Linear() const;				/**< Get-method for property Linear. @return Returns Linear as double.*/
		double get_Quadratic() const;			/**< Get-method for property Quadratic. @return Returns Quadratic as double.*/
		
		void set_Range(double value);			/**< Set-method for property Range. @param value Value of double.*/
		void set_Constant(double value);		/**< Set-method for property Constant. @param value Value of double.*/
		void set_Linear(double value);			/**< Set-method for property Linear. @param value Value of double.*/
		void set_Quadratic(double value);		/**< Set-method for property Quadratic. @param value Value of double.*/

		void set_Range(std::string value);		/**< Set-method for property Range. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Constant(std::string value);	/**< Set-method for property Constant. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Linear(std::string value);		/**< Set-method for property Linear. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Quadratic(std::string value);	/**< Set-method for property Quadratic. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;					/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

        /**
		 * Simple constructor.
		 */
		dotSceneLightAttenuation();

		/**
		 * Constructor for string-parameters. All strings will be parsed automatically to double-format.
		 * @param str_Range Range-value in std::string-format.
		 * @param str_Constant Constant-value in std::string-format.
		 * @param str_Linear Linear-value in std::string-format.
		 * @param str_Quadratic Quadratic-value in std::string-format.
		 */
		dotSceneLightAttenuation(std::string str_Range, std::string str_Constant, std::string str_Linear, std::string str_Quadratic);

		/**
		 * Constructor for double-parameters.
		 * @param double_Range Range-value in double-format.
		 * @param double_Constant Constant-value in double-format.
		 * @param double_Linear Linear-value in double-format.
		 * @param double_Quadratic Quadratic-value in double-format.
		 */
		dotSceneLightAttenuation(double double_Range, double double_Constant, double double_Linear, double double_Quadratic);
    };
}
