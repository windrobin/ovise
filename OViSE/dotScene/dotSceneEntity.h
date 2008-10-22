#ifndef dotSceneSpecific_h_
#define dotSceneSpecific_h_
#include "dotSceneSpecific.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold all information, needed for an Ogre::Enity class.
	 */
	class dotSceneEntity : public dotSceneSpecific 
    {
	private:
		std::string _name;			//**< Property name. Name of file.*/
		std::string _meshFile;		//**< Property meshFile. Filename of mesh-file, which is used for the entity.*/
		bool _static;				//**< Property static. Boolean attribute, representing the initial value of static.*/
		bool _visible;				//**< Property visible. Boolean attribute, representing the initial value for Ogre::Entity::Visible.*/
		bool _castShadows;			//**< Property castShadows. Boolean attribute, representing the initial value for Ogre::Entity::CastShadows.*/
		double _renderingDistance;	//**< Property renderingDistance. Boolean attribute, representing the initial value for renderingDistance of Ogre::Entity.*/

		void set_name(std::string value);			/**< Set-method for property name. @param value Value of a std::string.*/
		void set_meshFile(std::string value);		/**< Set-method for property meshFile. @param value Value of a std::string.*/
		void set_static(bool value);				/**< Set-method for property static. @param value Value of a bool.*/
		void set_visible(bool value);				/**< Set-method for property visible. @param value Value of a bool.*/
		void set_castShadows(bool value);			/**< Set-method for property castShadows. @param value Value of a bool.*/
		void set_renderingDistance(double value);	/**< Set-method for property renderingDistance. @param value Value of a bool.*/

	public:
		std::string get_name() const;			/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_meshFile() const;		/**< Get-method for property meshFile. @return Returns meshFile as std::string.*/
		bool get_static() const;				/**< Get-method for property static. @return Returns static as bool.*/
		bool get_visible() const;				/**< Get-method for property visible. @return Returns visible as bool.*/
		bool get_castShadows() const;			/**< Get-method for property castShadows. @return Returns castShadows as bool.*/
		double get_renderingDistance() const;	/**< Get-method for property renderingDistance. @return Returns renderingDistance as bool.*/

		/**
		 * Simple constructor.
		 * Implemented, because position-attribute is #IMPLIED but not #REQUIRED in original dotScene.dtd.
		 * It calls th constructor of baseobject.
		 */
		dotSceneEntity();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double & bool(integer) -format.
		 * @param str_name Name equals the MeshFile-HashKey.
		 * @param str_meshFile Filename of Mesh. For example: "teacup.mesh"
		 * @param str_static Will be parsed to integer and used as bool with a type-cast.
		 * @param str_visible Will be parsed to integer and used as bool with a type-cast.
		 * @param str_castShadows Will be parsed to integer and used as bool with a type-cast.
		 * @param str_renderingDistance Will be parsed to double.
		 */
		dotSceneEntity(std::string str_name, std::string str_meshFile, std::string str_static, std::string str_visible, std::string str_castShadows, std::string str_renderingDistance);
		
		/**
		 * Standard-constructor for direct value-parameters.
		 * @param str_name Name equals the MeshFile-HashKey.
		 * @param str_meshFile Filename of Mesh. For example: "teacup.mesh"
		 * @param bool_static Will be parsed to integer and used as bool with a type-cast.
		 * @param bool_visible Will be parsed to integer and used as bool with a type-cast.
		 * @param bool_castShadows Will be parsed to integer and used as bool with a type-cast.
		 * @param bool_renderingDistance Will be parsed to double.
		 */
		dotSceneEntity(std::string str_name, std::string str_meshFile, bool bool_static, bool bool_visible, bool bool_castShadows, double double_renderingDistance);
	    
		/**
		 * Simple destructor.
		 */
		~dotSceneEntity();
    };
}
