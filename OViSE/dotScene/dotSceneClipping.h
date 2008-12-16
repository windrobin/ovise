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
	class dotSceneClipping : virtual public dotSceneObject
	{
	private:
		double _NearPlaneDist;						/**< Property NearPlaneDist. Distance, where clipping begins. MUST be lower than FarPlaneDist.*/
        double _FarPlaneDist;						/**< Property FarPlaneDist. Distance, where clipping ends. MUST be greather than NearPlaneDist.*/

	public:
		double get_NearPlaneDist() const;			/**< Get-method for property NearPlaneDist. @return Returns NearPlaneDist as double.*/
		double get_FarPlaneDist() const;			/**< Get-method for property FarPlaneDist. @return Returns FarPlaneDist as double.*/
		void set_NearPlaneDist(std::string value);	/**< Set-method for property NearPlaneDist. @param value Value of std::string.*/
		void set_FarPlaneDist(std::string value);	/**< Set-method for property FarPlaneDist. @param value Value of std::string.*/
		void set_NearPlaneDist(double value);		/**< Set-method for property NearPlaneDist. @param value Value of double.*/
		void set_FarPlaneDist(double value);		/**< Set-method for property FarPlaneDist. @param value Value of double.*/
		bool IsValid() const;						/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneClipping(); 

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_NearPlaneDist NearPlaneDist-value in std::string-format. Will be parsed to double.
		 * @param str_FarPlaneDist FarPlaneDist-value in std::string-format. Will be parsed to double.
		 */
		dotSceneClipping(std::string str_NearPlaneDist, std::string str_FarPlaneDist);

		/**
		 * Standard-constructor for double-parameters.
		 * @param double_NearPlaneDist NearPlaneDist-value in double-format.
		 * @param double_FarPlaneDist FarPlaneDist-value in double-format.
		 */
		dotSceneClipping(double double_NearPlaneDist, double double_FarPlaneDist);

		/**
		 * Simple destructor.
		 */
        ~dotSceneClipping();
    };
}
