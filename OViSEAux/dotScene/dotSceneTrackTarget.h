#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneLocalDirectionVector_h_
#define dotSceneLocalDirectionVector_h_
#include "dotSceneLocalDirectionVector.h"
#endif

#ifndef dotSceneOffset_h_
#define dotSceneOffset_h_
#include "dotSceneOffset.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneTrackTarget : virtual public dotSceneObject
    {
	private:
		std::string _NodeName;								/**< Property NodeName.*/
		
		dotSceneLocalDirectionVector _LocalDirectionVector;	/**< Property LocalDirectionVector.*/
		dotSceneOffset _Offset;								/**< Property Offset.*/
	
	public:
		std::string get_NodeName() const;									/**< Get-method for property NodeName. @return Returns name as std::string.*/
		
		dotSceneOffset get_Offset() const;									/**< Get-method for property Offset. @return Returns a dotSceneOffset-object.*/
		dotSceneLocalDirectionVector get_LocalDirectionVector() const;		/**< Get-method for property LocalDirectionVector. @return Returns a dotSceneLocalDirectionVector-object.*/

		void set_NodeName(std::string value);								/**< Set-method for property NodeName. @param value Value of a std::string.*/
		
		void set_Offset(dotSceneOffset value);								/**< Set-method for property Offset. @param value A dotSceneOffset-object.*/
		void set_LocalDirectionVector(dotSceneLocalDirectionVector value);	/**< Set-method for property LocalDirectionVector. @param value A dotSceneLocalDirectionVector-object.*/

		bool IsValid() const;								/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
        /**
		 * Simple Constructor.
		 */
		dotSceneTrackTarget();

		/**
		 * Full initialisation constructor of dotSceneTrackTarget.
		 * @param str_NodeName Name of the node in ogre3D, to which should be looked at.
		 * @param obj_Offset Offset to look at.
		 * @param obj_LocalDirectionVector Local direction vector.
		 */
		dotSceneTrackTarget(std::string str_NodeName, dotSceneOffset obj_Offset, dotSceneLocalDirectionVector obj_LocalDirectionVector);
    };
}
