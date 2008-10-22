#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This Object is usable, but not complete.
	 * Holds values used for clipping-information of cameras.
	 * ATTENTION: Idea of UserData(Reference) is not documented.
	 */
	class dotSceneClipping : public dotSceneObject
	{
	private:
		double _nearPlaneDist;	/**< Property nearPlaneDist. Distance, where clipping begins. MUST be lower than farPlaneDist.*/
        double _farPlaneDist;	/**< Property farPlaneDist. Distance, where clipping ends. MUST be greather than nearPlaneDist.*/

		void set_nearPlaneDist(double value);	/**< Set-method for property nearPlaneDist. @param value Value of double.*/
		void set_farPlaneDist(double value);	/**< Set-method for property farPlaneDist. @param value Value of double.*/

	public:
		double get_nearPlaneDist() const;	/**< Get-method for property nearPlaneDist. @return Returns formatVersion as double.*/
		double get_farPlaneDist() const;	/**< Get-method for property farPlaneDist. @return Returns formatVersion as double.*/

		/**
		 * Simple constructor.
		 * Implemented, because position-attribute is #IMPLIED but not #REQUIRED in original dotScene.dtd.
		 * It calls th constructor of baseobject.
		 */
		dotSceneClipping(); 

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_nearPlaneDist nearPlaneDist-value in std::string-format. Will be parsed to double.
		 * @param str_farPlaneDist farPlaneDist-value in std::string-format. Will be parsed to double.
		 */
		dotSceneClipping(std::string str_nearPlaneDist, std::string str_farPlaneDist);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_nearPlaneDist nearPlaneDist-value in double-format.
		 * @param double_farPlaneDist farPlaneDist-value in double-format.
		 */
		dotSceneClipping(double double_nearPlaneDist, double double_farPlaneDist);

		/**
		 * Simple destructor.
		 */
        ~dotSceneClipping();
    };
}
