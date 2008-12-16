#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneFog_h_
#define dotSceneFog_h_
#include "dotSceneFog.h"
#endif

#ifndef dotSceneColourBackground_h_
#define dotSceneColourBackground_h_
#include "dotSceneColourBackground.h"
#endif

#ifndef dotSceneColourAmbient_h_
#define dotSceneColourAmbient_h_
#include "dotSceneColourAmbient.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	
	/**
	 * This class hold values for all objects, which can occure in environment-definition.
	 */
	class dotSceneEnvironment : virtual public dotSceneObject
    {
	private:
		dotSceneFog _fog;											/**< Property fog.*/
		dotSceneColourBackground _colourBackground;					/**< Property colourBackground.*/
		dotSceneColourAmbient _colourAmbient;						/**< Property colourAmbient.*/

	public:
		dotSceneFog get_fog() const;								/**< Get-method for property fog. @return Returns a dotSceneFog-object.*/
		dotSceneColourBackground get_colourBackground() const;		/**< Get-method for property colourBackground. @return Returns a dotSceneColourBackground-object.*/
		dotSceneColourAmbient get_colourAmbient() const;			/**< Get-method for property colourAmbient. @return Returns a dotSceneColourAmbient-object.*/

		void set_fog(dotSceneFog value);							/**< Set-method for property fog. @param value A dotSceneFog-object.*/
		void set_colourBackground(dotSceneColourBackground value);	/**< Set-method for property colourBackground. @param value A dotSceneColourBackground-object.*/
		void set_colourAmbient(dotSceneColourAmbient value);		/**< Set-method for property colourAmbient. @param value A dotSceneColourAmbient-object.*/

		bool IsValid() const;										/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 */
		dotSceneEnvironment();

		/** 
		 * Standard-constructor.
		 * The dotScene-objects have to be constructed before.
		 * @param obj_fog A pre-constrcted dotSceneFog-object.
		 * @param obj_colorAmbient A pre-constrcted dotSceneColorAmbient-object.
		 * @param obj_colorBackground A pre-constrcted dotSceneColorBackground-object.
		 */
		dotSceneEnvironment(dotSceneFog obj_fog, dotSceneColourAmbient obj_colorAmbient, dotSceneColourBackground obj_colorBackground);
    };
}