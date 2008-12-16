#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneQuaternion_h_
#define dotSceneQuaternion_h_
#include "dotSceneQuaternion.h"
#endif

#ifndef dotSceneDirection_h_
#define dotSceneDirection_h_
#include "dotSceneDirection.h"
#endif

#ifndef dotSceneAxisXYZ_h_
#define dotSceneAxisXYZ_h_
#include "dotSceneAxisXYZ.h"
#endif

#ifndef dotSceneAngleAxis_h_
#define dotSceneAngleAxis_h_
#include "dotSceneAngleAxis.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneOrientation : virtual public dotSceneObject
    {
	private:
		dotSceneAngleAxis _AngleAxis;					/**< Property AngleAxis.*/
		dotSceneAxisXYZ _AxisXYZ;						/**< Property AxisXYZ.*/
		dotSceneDirection _Direction;					/**< Property Direction.*/
		dotSceneQuaternion _Quaternion;					/**< Property Quaternion.*/
		dotSceneEnums::dotSceneElementTags _Type;		/**< Property Type. Delivers type of used orientation-definition.*/
	
	public:
		dotSceneAngleAxis get_AngleAxis() const;			/**< Get-method for property AngleAxis. @return Returns a dotSceneObjects::dotSceneAngleAxis.*/
		dotSceneAxisXYZ get_AxisXYZ() const;				/**< Get-method for property AxisXYZ. @return Returns a dotSceneObjects::dotSceneAxisXYZ.*/
		dotSceneDirection get_Direction() const;			/**< Get-method for property Direction. @return Returns a dotSceneObjects::dotSceneDirection.*/
		dotSceneQuaternion get_Quaternion() const;			/**< Get-method for property Quaternion. @return Returns a dotSceneObjects::dotSceneQuaternion.*/
		//dotSceneEnums::dotSceneElementTags get_Type() const;/**< Get-method for property Type. @return Returns a dotSceneEnums::dotSceneElementTags.*/
		//std::string get_Type() const;						/**< Get-method for property Type. @return Returns Type as a std::string.*/

		void set_AngleAxis(dotSceneAngleAxis value);			/**< Set-method for property AngleAxis. @param value A dotSceneAngleAxis-object.*/
		void set_AxisXYZ(dotSceneAxisXYZ value);				/**< Set-method for property AxisXYZ. @param A dotSceneAxisXYZ-object.*/
		void set_Direction(dotSceneDirection value);			/**< Set-method for property Direction. @param A dotSceneDirection-object.*/
		void set_Quaternion(dotSceneQuaternion value);			/**< Set-method for property Quaternion. @param A dotSceneQuaternion-object.*/
		//void set_Type(dotSceneEnums::dotSceneElementTags value);/**< Set-method for property Type. @param A value of enum dotSceneEnums::dotSceneElementTags.*/
		//void set_Type(std::string value);						/**< Set-method for property Type. @param A value of std::string. Must be a valid value of enum dotSceneEnums::dotSceneElementTags. Else, it's set to enum-value INVALID.*/

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
		static dotSceneAxisXYZ convert(dotSceneQuaternion someQuaternion);
		static dotSceneQuaternion convert(dotSceneAxisXYZ someAxisXYZ);
		// more conversion needed but not implemented yet

        /**
		 * Simple Constructor.
		 */
		dotSceneOrientation();
    };
}