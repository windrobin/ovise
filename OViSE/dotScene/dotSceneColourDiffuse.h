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
	class dotSceneColourDiffuse : public dotSceneColour 
    {
	public:
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
    };
}
