#ifndef dotScene3D_h_
#define dotScene3D_h_
#include "dotScene3D.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represents the x, y and z values of an 3D-vector, used as a local direction-vector.
	 * It inherits from dotScene3D.
	 */
    class dotSceneLocalDirectionVector : public dotScene3D
    {     
	public:
		/**
		 * Simple constructor.
		 * Implemented, because position-attribute is #IMPLIED but not #REQUIRED in original dotScene.dtd.
		 * It calls th constructor of baseobject.
		 */
		dotSceneLocalDirectionVector();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_x X-value in std::string-format.
		 * @param str_y Y-value in std::string-format.
		 * @param str_z Z-value in std::string-format.
		 */
		dotSceneLocalDirectionVector(std::string str_x, std::string str_y, std::string str_z);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_x X-value in double-format.
		 * @param double_y Y-value in double-format.
		 * @param double_z Z-value in double-format.
		 */
		dotSceneLocalDirectionVector(double double_x, double double_y, double double_z);
    };
}
