#ifndef dotScene3D_h_
#define dotScene3D_h_
#include "dotScene3D.h"
#endif
#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the x, y and z values of an 3D-vector, interpreted as a scale-factors.
	 * It inherits from dotScene3D.
	 */
    class dotSceneScale : virtual public dotScene3D
    {	
	public:
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
    };
}