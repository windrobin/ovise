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
	 * It describes with its RGB-values the backgroud-colour. It's a property of the entire world.
	 * Not of a special visible object or a source of light.
	 */
	class dotSceneColourBackground : virtual public dotSceneColour
    {
	public:
		/**
		 * Simple constructor.
		 */
		dotSceneColourBackground();

		/**
		 * Standard-constructor for std::string-parameters.
		 * @param str_r RED-value in std::string-format. Will be parsed to double.
		 * @param str_g GREEN-value in std::string-format. Will be parsed to double.
		 * @param str_b BLUE-value in std::string-format. Will be parsed to double.
		 */
		dotSceneColourBackground(std::string str_r, std::string str_g, std::string str_b);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_r RED-value in double-format.
		 * @param double_g GREEN-value in double-format.
		 * @param double_b BLUE-value in double-format.
		 */
		dotSceneColourBackground(double double_r, double double_g, double double_b);
    };
}

