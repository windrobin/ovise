#ifndef dotSceneColour_h_
#define dotSceneColour_h_
#include "dotSceneColour.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class inherits from dotSceneColour.
	 * Diffuse-colour describes with the RGB-values the "ground"-colour a visible object
	 * or the corresponding light-value, witch causes the object-colours.
	 */
	class dotSceneColourDiffuse : virtual public dotSceneColour 
    {
	private:
		double _a;						/**< Property a. ALPHA value.*/
		bool _UseAlpha;					/**< Property UseAlpha.*/
	public:
		double get_a() const;			/**< Get-method for property a. @return Returns a (ALPHA) as double.*/
		void set_a(double value);		/**< Set-method for property a. @param value Value of double.*/
		void set_a(std::string value);	/**< Set-method for property a. @param value Value in std::string-format. Will be parsed to double. */

		bool HasAlpha() const;			/**< Use this method to check, if a alpha-value is used. @return Returns TRUE if a alpha-value is used.*/

		/**
		 * Simple constructor.
		 */
		dotSceneColourDiffuse();

		/**
		 * Standard-constructor for std::string-parameters.
		 * @param str_r RED-value in std::string-format. Will be parsed to double.
		 * @param str_g GREEN-value in std::string-format. Will be parsed to double.
		 * @param str_b BLUE-value in std::string-format. Will be parsed to double.
		 */
		dotSceneColourDiffuse(std::string str_r, std::string str_g, std::string str_b);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_r RED-value in double-format.
		 * @param double_g GREEN-value in double-format.
		 * @param double_b BLUE-value in double-format.
		 */
		dotSceneColourDiffuse(double double_r, double double_g, double double_b);

		/**
		 * Standard-constructor for std::string-parameters.
		 * @param str_r RED-value in std::string-format. Will be parsed to double.
		 * @param str_g GREEN-value in std::string-format. Will be parsed to double.
		 * @param str_b BLUE-value in std::string-format. Will be parsed to double.
		 * @param str_a ALPHA-value in std::string-format. Will be parsed to double.
		 */
		dotSceneColourDiffuse(std::string str_r, std::string str_g, std::string str_b, std::string str_a);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_r RED-value in double-format.
		 * @param double_g GREEN-value in double-format.
		 * @param double_b BLUE-value in double-format.
		 * @param double_a ALPHA-value in double-format.
		 */
		dotSceneColourDiffuse(double double_r, double double_g, double double_b, double double_a);
    };
}
