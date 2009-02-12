#ifndef dotSceneSpecific_h_
#define dotSceneSpecific_h_
#include "dotSceneSpecific.h"
#endif

#ifndef dotSceneCommonMovableObjectParams_h_
#define dotSceneCommonMovableObjectParams_h_
#include "dotSceneCommonMovableObjectParams.h"
#endif

#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#ifndef dotSceneDirection_h_
#define dotSceneDirection_h_
#include "dotSceneDirection.h"
#endif

#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

#ifndef dotSceneColourSpecular_h_
#define dotSceneColourSpecular_h_
#include "dotSceneColourSpecular.h"
#endif

#ifndef dotSceneSpotLightRange_h_
#define dotSceneSpotLightRange_h_
#include "dotSceneSpotLightRange.h"
#endif

#ifndef dotSceneLightAttenuation_h_
#define dotSceneLightAttenuation_h_
#include "dotSceneLightAttenuation.h"
#endif

#ifndef dotSceneUserDataReference_h_
#define dotSceneUserDataReference_h_
#include "dotSceneUserDataReference.h"
#endif

#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	using namespace dotSceneEnums::dotSceneLightEnums;

	/**
	 * This class hold values for all objects, which can occure in light-definition.
	 */
    class dotSceneLight : virtual public dotSceneSpecific
    {
	private:
		std::string _name;	/**< Property name. Name of light in Orge3D-engine*/
		std::string _ID;	/**< Property ID. ID of light in Orge3D-engine.*/
		LightTypes _Type;	/**< Property Type. Type of lightsource. Possible types are: point, directional, spotlight and rad-point.*/
		double _PowerScale;	/**< Property PowerScale. Power of lightsource. Default is 1.0. That equals 100%.*/

		dotSceneCommonMovableObjectParams _CommonMovableObjectParams;	/**< Property CommonMovableObjectParams.*/
		dotScenePosition _Position;						/**< Property Position. Position of light.*/
		dotSceneDirection _Direction;					/**< Property Direction. Direction of light. Can be used for a calculation to find the "lookat"-point.*/
		dotSceneColourDiffuse _DiffuseColour;			/**< Property DiffuseColour. Diffuse colour of light. Common "soft" light.*/
		dotSceneColourSpecular _SpecularColour;			/**< Property SpecularColour. Specular coulour of light. Reflected "shiny" light. */
		dotSceneSpotLightRange _SpotLightRange;			/**< Property SpotLightRange. Range of light, if it's a spotlight.*/
		dotSceneLightAttenuation _LightAttentuation;	/**< Property LightAttentuation. Attenuation of light.*/
		dotSceneUserDataReference _UserDataReference;	/**< Property UserDataReference.*/

	public:
		std::string get_name() const;	/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_ID() const;		/**< Get-method for property ID. @return Returns ID as std::string.*/
		LightTypes get_Type() const;	/**< Get-method for property Type. @return Returns Type as a value of "dotSceneEnums::dotSceneLightEnums::LightTypes"-enum.*/
		double get_PowerScale() const;	/**< Get-method for property PowerScale. @return Returns name as double.*/

		dotSceneCommonMovableObjectParams get_CommonMovableObjectParams() const;	/**< Get-method for property CommonMovableObjectParams. @return Returns a "dotSceneCommonMovableObjectParams"-object.*/
		dotScenePosition get_Position() const;						/**< Get-method for property Position. @return Returns a "dotScenePosition"-object.*/
		dotSceneDirection get_Direction() const;					/**< Get-method for property Direction. @return Returns a "dotSceneDirection"-object.*/
		dotSceneColourDiffuse get_DiffuseColour() const;			/**< Get-method for property ColourDiffuse. @return Returns a "dotSceneColourDiffuse"-object.*/
		dotSceneColourSpecular get_SpecularColour() const;			/**< Get-method for property ColourSpecular. @return Returns a ""dotSceneColourSpecular-object.*/
		dotSceneSpotLightRange get_SpotLightRange() const;			/**< Get-method for property SpotLightRange. @return Returns a "dotSceneSpotLightRange"-object.*/
		dotSceneLightAttenuation get_LightAttenuation() const;		/**< Get-method for property LightAttenuation. @return Returns a "dotSceneLightAttenuation"-object.*/
		dotSceneUserDataReference get_UserDataReference() const;	/**< Get-method for property UserDataReference. @return Returns a "dotSceneUserDataReference"-object.*/

		void set_name(std::string value);	/**< Set-method for property name. @param value Value of std::string.*/
		void set_ID(std::string value);		/**< Set-method for property ID. @param value Value of std::string.*/
		void set_Type(LightTypes value);	/**< Set-method for property Type. @param value Value of "dotSceneEnums::dotSceneLightEnums::LightTypes"-enum.*/
		void set_PowerScale(double value);	/**< Set-method for property PowerScale. @param value Value of double.*/

		void set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value);/**< Set-method for property CommonMovableObjectParams. @param value A "dotSceneCommonMovableObjectParams"-object.*/
		void set_Position(dotScenePosition value);					/**< Set-method for property Position. @param value A "dotScenePosition"-object.*/
		void set_Direction(dotSceneDirection value);				/**< Set-method for property Direction. @param value A "dotSceneDirection"-object.*/
		void set_DiffuseColour(dotSceneColourDiffuse value);		/**< Set-method for property ColourDiffuse. @param value A "dotSceneColourDiffuse"-object.*/
		void set_SpecularColour(dotSceneColourSpecular value);		/**< Set-method for property ColourSpecular. @param value A "dotSceneColourSpecular"-object.*/
		void set_SpotLightRange(dotSceneSpotLightRange value);		/**< Set-method for property SpotLightRange. @param value A "dotSceneSpotLightRange"-object.*/
		void set_LightAttenuation(dotSceneLightAttenuation value);	/**< Set-method for property LightAttenuation. @param value A "dotSceneLightAttenuation"-object.*/
		void set_UserDataReference(dotSceneUserDataReference value);/**< Set-method for property UserDataReference. @param value A "dotSceneUserDataReference"-object.*/
		
		void set_Type(std::string value);		/**< Set-method for property Type. @param value Value of std::string.*/
		void set_PowerScale(std::string value);	/**< Set-method for property PowerScale. @param value Value of std::string.*/

		bool IsValid() const;				/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
		/**
		 * Simple constructor.
		 */
        dotSceneLight();

		/**
		 * Full initialisation constructor of dotSceneLight.
		 * All std::string-values will be parsed automatically.
		 * @param str_name Name of light in Ogre3D-engine in std::string-format.
		 * @param str_ID ID of light in Ogre3D-engine in std::string-format.
		 * @param str_Type Type of light as a value of std::string-format.
		 * @param str_PowerScale Power of light in std::string-format.
		 * @param obj_CommonMovableObjectParams A pre-constrcted "dotSceneCommonMovableObjectParams"-object.
		 * @param obj_Position A pre-constrcted "dotScenePosition"-object.
		 * @param obj_Direction A pre-constrcted "dotSceneDirection"-object.
		 * @param obj_DiffuseColour A pre-constrcted "dotSceneColourDiffuse"-object.
		 * @param obj_SpecularColour A pre-constrcted "dotSceneColourSpecular"-object.
		 * @param obj_SpotLightRange A pre-constrcted "dotSceneSpotLightRange"-object.
		 * @param obj_LightAttentuation A pre-constrcted "dotSceneLightAttentuation"-object.
		 * @param obj_UserDataReference A pre-constrcted "dotSceneUserDataReference"-object.		 */
		dotSceneLight(
			std::string str_name,
			std::string str_ID,
			std::string str_Type,
			std::string str_PowerScale,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotScenePosition obj_Position,
			dotSceneDirection obj_Direction,
			dotSceneColourDiffuse obj_ColourDiffuse,
			dotSceneColourSpecular obj_ColourSpecular,
			dotSceneSpotLightRange obj_SpotLightRange,
			dotSceneLightAttenuation obj_LightAttenuation,
			dotSceneUserDataReference obj_UserDataReference);

		/**
		 * Full initialisation constructor of dotSceneNode.
		 * @param str_name Name of light in Ogre3D-engine in std::string-format.
		 * @param str_ID ID of light in Ogre3D-engine in std::string-format.
		 * @param enum_Type Type of light as a value of "dotSceneEnums::dotSceneLightEnums::LightTypes"-enum.
		 * @param double_PowerScale Power of light in double-format Default is "1.0". That equals 100%.
		 * @param obj_CommonMovableObjectParams A pre-constrcted "dotSceneCommonMovableObjectParams"-object.
		 * @param obj_Position A pre-constrcted "dotScenePosition"-object.
		 * @param obj_Direction A pre-constrcted "dotSceneDirection"-object.
		 * @param obj_DiffuseColour A pre-constrcted "dotSceneColourDiffuse"-object.
		 * @param obj_SpecularColour A pre-constrcted "dotSceneColourSpecular"-object.
		 * @param obj_SpotLightRange A pre-constrcted "dotSceneSpotLightRange"-object.
		 * @param obj_LightAttentuation A pre-constrcted "dotSceneLightAttentuation"-object.
		 * @param obj_UserDataReference A pre-constrcted "dotSceneUserDataReference"-object.
		 */
		dotSceneLight(
			std::string str_name,
			std::string str_ID,
			LightTypes enum_Type,
			double double_PowerScale,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotScenePosition obj_Position,
			dotSceneDirection obj_Direction,
			dotSceneColourDiffuse obj_ColourDiffuse,
			dotSceneColourSpecular obj_ColourSpecular,
			dotSceneSpotLightRange obj_SpotLightRange,
			dotSceneLightAttenuation obj_LightAttenuation,
			dotSceneUserDataReference obj_UserDataReference);
    };
}
