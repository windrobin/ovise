#ifndef dotSceneSpecific_h_
#define dotSceneSpecific_h_
#include "dotSceneSpecific.h"
#endif

#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

#ifndef dotSceneColourSpecular_h_
#define dotSceneColourSpecular_h_
#include "dotSceneColourSpecular.h"
#endif

#ifndef dotSceneNormal_h_
#define dotSceneNormal_h_
#include "dotSceneNormal.h"
#endif

#ifndef dotSceneLightRange_h_
#define dotSceneLightRange_h_
#include "dotSceneLightRange.h"
#endif

#ifndef dotSceneLightAttenuation_h_
#define dotSceneLightAttenuation_h_
#include "dotSceneLightAttenuation.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in light-definition.
	 */
    class dotSceneLight : public dotSceneSpecific
    {
	private:
		std::string _name;							/**< Property name.*/
		std::string _type;							/**< Property type.*/
		dotSceneColourDiffuse _colourDiffuse;		/**< Property colourDiffuse.*/
		dotSceneColourSpecular _colourSpecular;		/**< Property colourSpecular.*/
		dotSceneNormal _normal;						/**< Property normal.*/
		dotSceneLightRange _lightRange;				/**< Property lightRange.*/
		dotSceneLightAttenuation _lightAttenuation; /**< Property lightAttenuation.*/

		void set_name(std::string value);							/**< Set-method for property name. @param value Value of a std::string.*/
		void set_type(std::string value);							/**< Set-method for property type. @param value Value of a std::string.*/
		void set_colourDiffuse(dotSceneColourDiffuse value);		/**< Set-method for property colourDiffuse. @param value A dotSceneColourDiffuse-object.*/
		void set_colourSpecular(dotSceneColourSpecular value);		/**< Set-method for property colourSpecular. @param value A dotSceneColourSpecular-object.*/
		void set_normal(dotSceneNormal value);						/**< Set-method for property normal. @param value A dotSceneNormal-object.*/
		void set_lightRange(dotSceneLightRange value);				/**< Set-method for property lightRange. @param value A dotSceneLightRange-object.*/
		void set_lightAttenuation(dotSceneLightAttenuation value);	/**< Set-method for property lightAttenuation. @param value A dotSceneLightAttenuation-object.*/

	public:
		std::string get_name() const;							/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_type() const;							/**< Get-method for property type. @return Returns type as std::string.*/
		dotSceneColourDiffuse get_colourDiffuse() const;		/**< Get-method for property colourDiffuse. @return Returns a dotSceneColourDiffuse-object.*/
		dotSceneColourSpecular get_colourSpecular() const;		/**< Get-method for property colourSpecular. @return Returns a dotSceneColourSpecular-object.*/
		dotSceneNormal get_normal() const;						/**< Get-method for property normal. @return Returns a dotSceneNormal-object.*/
		dotSceneLightRange get_lightRange() const;				/**< Get-method for property lightRange. @return Returns a dotSceneLightRange-object.*/
		dotSceneLightAttenuation get_lightAttenuation() const;	/**< Get-method for property lightAttenuation. @return Returns a dotSceneLightAttenuation-object.*/
		
		/**
		 * Simple constructor. It calls the constructor of baseobject.
		 */
        dotSceneLight();

		/**
		 * Standard-constructor.
		 * The dotScene-objects have to be constructed before.
		 * @param str_name name-value in string-format.
		 * @param str_type type-value in string-format.
		 * @param obj_colourDiffuse A pre-constrcted dotSceneColourDiffuse-object.
		 * @param obj_colourSpecular A pre-constrcted dotSceneColourSpecular-object.
		 * @param obj_normal A pre-constrcted dotSceneNormal-object.
		 * @param obj_lightRange A pre-constrcted dotSceneLightRange-object.
		 * @param obj_lightAttenuation A pre-constrcted dotSceneLightAttenuation-object.
		 */
		dotSceneLight(std::string str_name, std::string str_type, dotSceneColourDiffuse obj_colourDiffuse, dotSceneColourSpecular obj_colourSpecular, dotSceneNormal obj_normal, dotSceneLightRange obj_lightRange, dotSceneLightAttenuation obj_lightAttenuation);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneLight();
    };
}
