#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneCommonMovableObjectParams_h_
#define dotSceneCommonMovableObjectParams_h_
#include "dotSceneCommonMovableObjectParams.h"
#endif

#ifndef dotSceneUserDataReference_h_
#define dotSceneUserDataReference_h_
#include "dotSceneUserDataReference.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneParticleSystem : virtual public dotSceneObject
    {
	private:
		std::string _name;			/**< Property name.*/
		std::string _ID;			/**< Property ID.*/
		std::string _TemplateName;	/**< Property TemplateName.*/
		std::string _MaterialName;	/**< Property MaterialName.*/

		dotSceneCommonMovableObjectParams _CommonMovableObjectParams;	/**< Property CommonMovableObjectParams.*/
		dotSceneUserDataReference _UserDataReference;					/**< Property UserDataReference.*/
	
	public:
		std::string get_name() const;			/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_ID() const;				/**< Get-method for property ID. @return Returns ID as std::string.*/
		std::string get_TemplateName() const;	/**< Get-method for property TemplateName. @return Returns TemplateName as std::string.*/
		std::string get_MaterialName() const;	/**< Get-method for property MaterialName. @return Returns MaterialName as std::string.*/

		dotSceneCommonMovableObjectParams get_CommonMovableObjectParams() const;/**< Get-method for property CommonMovableObjectParams. @return Returns a dotSceneCommonMovableObjectParams-object.*/
		dotSceneUserDataReference get_UserDataReference() const;				/**< Get-method for property UserDataReference. @return Returns a dotSceneUserDataReference-object.*/

		void set_name(std::string value);			/**< Set-method for property name. @param value Value of a std::string.*/
		void set_ID(std::string value);				/**< Set-method for property name. @param value Value of a std::string.*/
		void set_TemplateName(std::string value);	/**< Set-method for property name. @param value Value of a std::string.*/
		void set_MaterialName(std::string value);	/**< Set-method for property name. @param value Value of a std::string.*/

		void set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value);/**< Set-method for property CommonMovableObjectParams. @param value A dotSceneCommonMovableObjectParams-object.*/
		void set_UserDataReference(dotSceneUserDataReference value);				/**< Set-method for property UserDataReference. @param value A dotSceneUserDataReference-object.*/

		bool IsValid() const;						/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
        /**
		 * Simple Constructor.
		 */
		dotSceneParticleSystem();

		/**
		 * Full initialisation constructor of dotSceneNode.
		 * Specialisation: dotSceneCamera 
		 * @param str_name Name of the node in ogre3D.
		 * @param str_ID A pre-constrcted dotScenePosition-object.
		 * @param str_TemplateName A pre-constrcted dotSceneQuaternion-object.
		 * @param str_MaterialName A pre-constrcted dotSceneScale-object.
		 * @param obj_CommonMovableObjectParams A pre-constrcted dotSceneCommonMovableObjectParams-object.
		 * @param obj_UserDataReference A pre-constrcted dotSceneUserDataReference-object.
		 */
		dotSceneParticleSystem(std::string str_name, std::string str_ID, std::string str_TemplateName, std::string str_MaterialName, dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams, dotSceneUserDataReference obj_UserDataReference);
    };
}
