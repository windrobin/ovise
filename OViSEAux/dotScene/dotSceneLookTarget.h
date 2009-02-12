#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#ifndef dotSceneLocalDirectionVector_h_
#define dotSceneLocalDirectionVector_h_
#include "dotSceneLocalDirectionVector.h"
#endif

#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneLookTarget : virtual public dotSceneObject
    {
	private:
		std::string _NodeName;										/**< Property NodeName.*/
		dotSceneEnums::dotSceneGeneralEnums::RelativeTo _RelativeTo;/**< Property RelativeTo.*/
		
		dotScenePosition _Position;									/**< Property Position.*/
		dotSceneLocalDirectionVector _LocalDirectionVector;			/**< Property LocalDirectionVector.*/
	
	public:
		std::string get_NodeName() const;											/**< Get-method for property NodeName. @return Returns name as std::string.*/
		dotSceneEnums::dotSceneGeneralEnums::RelativeTo get_RelativeTo() const;		/**< Get-method for property RelativeTo. @return Returns name as dotSceneEnums::dotSceneGeneralEnums::RelativeTo.*/
		
		dotScenePosition get_Position() const;										/**< Get-method for property Position. @return Returns a dotScenePosition-object.*/
		dotSceneLocalDirectionVector get_LocalDirectionVector() const;				/**< Get-method for property LocalDirectionVector. @return Returns a dotSceneLocalDirectionVector-object.*/

		void set_NodeName(std::string value);										/**< Set-method for property NodeName. @param value Value of a std::string.*/
		void set_RelativeTo(dotSceneEnums::dotSceneGeneralEnums::RelativeTo value);	/**< Set-method for property RelativeTo. @param value Value of a dotSceneEnums::dotSceneGeneralEnums::RelativeTo.*/
		
		void set_Position(dotScenePosition value);									/**< Set-method for property Position. @param value A dotScenePosition-object.*/
		void set_LocalDirectionVector(dotSceneLocalDirectionVector value);			/**< Set-method for property LocalDirectionVector. @param value A dotSceneLocalDirectionVector-object.*/

		void set_RelativeTo(std::string value);										/**< Set-method for property RelativeTo. @param value Value of a std::string.*/

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
        /**
		 * Simple Constructor.
		 */
		dotSceneLookTarget();

		/**
		 * Full initialisation constructor of dotSceneLookTarget for string parameters.
		 * @param str_NodeName Name of the node in ogre3D, to which should be looked at.
		 * @param str_RelativeTo Perspective-calculation relative to local-, parent- or world-geometric.
		 * @param obj_Position Position to look at.
		 * @param obj_LocalDirectionVector Local direction vector.
		 */
		dotSceneLookTarget(std::string str_NodeName, std::string str_RelativeTo, dotScenePosition obj_Position, dotSceneLocalDirectionVector obj_LocalDirectionVector);

		/**
		 * Full initialisation constructor of dotSceneLookTarget for value parameters.
		 * @param str_NodeName Name of the node in ogre3D, to which should be looked at.
		 * @param enum_RelativeTo Perspective-calculation relative to local-, parent- or world-geometric.
		 * @param obj_Position Position to look at.
		 * @param obj_LocalDirectionVector Local direction vector.
		 */
		dotSceneLookTarget(std::string str_NodeName, dotSceneEnums::dotSceneGeneralEnums::RelativeTo enum_RelativeTo, dotScenePosition obj_Position, dotSceneLocalDirectionVector obj_LocalDirectionVector);
    };
}
