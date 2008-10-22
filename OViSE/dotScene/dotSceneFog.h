#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This object contains data for a fog-setup.
	 */
	class dotSceneFog : public dotSceneObject
    {
	private:
		double _linearStart;					/**< Property linearStart. Distance, where fog begins and grows linear.*/
		double _linearEnd;						/**< Property linearEnd. Distance, where fog ends.*/
		std::string _mode;						/**< Property mode. Mode of fog.*/
		dotSceneColourDiffuse _colourDiffuse;	/**< Property colourDiffuse. Diffuse colour of fog.*/

		void set_linearStart(double value);					/**< Set-method for property linearStart. @param value Value of a double.*/
		void set_linearEnd(double value);					/**< Set-method for property linearEnd. @param value Value of a double.*/
		void set_mode(std::string value);					/**< Set-method for property mode. @param value Value of a std::string.*/
		void set_colourDiffuse(dotSceneColourDiffuse value);/**< Set-method for property colourDiffuse. @param value A dotSceneColourDiffuse-object.*/

	public:
		double get_linearStart() const;					/**< Get-method for property linearStart. @return Returns linearStart as double.*/
		double get_linearEnd() const;					/**< Get-method for property linearEnd. @return Returns linearEnd as double.*/
		std::string get_mode() const;					/**< Get-method for property mode. @return Returns mode as std::string.*/
		dotSceneColourDiffuse get_colourDiffuse() const;/**< Get-method for property colourDiffuse. @return Returns a dotSceneColourDiffuse-object.*/

		/**
		 * Simple constructor. It calls th constructor of baseobject.
		 */
		dotSceneFog();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_linearStart linearStart-value in std::string-format. Will be parsed to double.
		 * @param str_linearEnd linearEnd-value in std::string-format. Will be parsed to double.
		 * @param str_mode mode-value in std::string-format. Will be parsed to double.
		 * @param obj_diffuseColour a pre-constrcted dotSceneColourDiffuse-object.
		 */
		dotSceneFog(std::string str_linearStart, std::string str_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_linearStart linearStart-value in double-format.
		 * @param double_linearEnd linearEnd-value in double-format.
		 * @param str_mode mode-value in std::string-format.
		 * @param obj_diffuseColour a pre-constrcted dotSceneColourDiffuse-object.
		 */
		dotSceneFog(double double_linearStart, double double_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneFog();
    };
}