#ifndef dotSceneSpecific_h_
#define dotSceneSpecific_h_
#include "dotSceneSpecific.h"
#endif

#ifndef dotSceneNormal_h_
#define dotSceneNormal_h_
#include "dotSceneNormal.h"
#endif

#ifndef dotSceneClipping_h_
#define dotSceneClipping_h_
#include "dotSceneClipping.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	/**
	 * This class describes a Ogre::Camera.
	 * It holds values of all parameters, which can occure between camera-tags in a dotScene-XML.
	 */
	class dotSceneCamera : public dotSceneSpecific 
    { 
	private:
		std::string _name;				/**< Property name.*/
		double _fov;					/**< Property fov.*/
		std::string _projectionType;	/**< Property projectionType.*/
		dotSceneNormal _normal;			/**< Property normal.*/
		dotSceneClipping _clipping;		/**< Property clipping.*/

		void set_name(std::string value);			/**< Set-method for property name. @param value Value of a std::string.*/
		void set_fov(double value);					/**< Set-method for property fov. @param value A double-value.*/
		void set_projectionType(std::string value);	/**< Set-method for property projectionType. @param value Value of a std::string.*/
		void set_normal(dotSceneNormal value);		/**< Set-method for property normal. @param value A dotSceneNormal-object.*/
		void set_clipping(dotSceneClipping value);	/**< Set-method for property clipping. @param value A dotSceneClipping-object.*/

	public:
		std::string get_name() const;			/**< Get-method for property name. @return Returns name as std::string.*/
		double get_fov() const;					/**< Get-method for property fov. @return Returns fov as double.*/
		std::string get_projectionType() const;	/**< Get-method for property projectionType. @return Returns projectionType as std::string.*/
		dotSceneNormal get_normal() const;		/**< Get-method for property normal. @return Returns a dotSceneNormal-object.*/
		dotSceneClipping get_clipping() const;	/**< Get-method for property clipping. @return Returns a dotSceneClipping-object.*/
        
        /**
		 * Simple constructor.
		 * It calls the constructor of base-object.
		 */
		dotSceneCamera();

		/**
		 * Standard-constructor for std::string-parameters.
		 * The dotScene-objects have to be constructed before.
		 * @param str_name name-value in string-format.
		 * @param str_fov fov-value in string-format. Will be parsed to double.
		 * @param str_projectionType projectionType-value in string-format.
		 * @param name obj_normal A pre-constrcted dotSceneNormal-object.
		 * @param name obj_clipping A pre-constrcted dotSceneClipping-object.
		 */
		dotSceneCamera(std::string str_name, std::string str_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping);
		
		/**
		 * Standard-constructor for double-parameters.
		 * The dotScene-objects have to be constructed before.
		 * @param str_name name-value in string-format.
		 * @param str_fov fov-value in double-format. Will be parsed to double.
		 * @param str_projectionType projectionType-value in string-format.
		 * @param name obj_normal A pre-constrcted dotSceneNormal-object.
		 * @param name obj_clipping A pre-constrcted dotSceneClipping-object.
		 */
		dotSceneCamera(std::string str_name, double double_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneCamera();
    };
}
