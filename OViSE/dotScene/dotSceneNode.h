#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#ifndef dotSceneQuaternion_h_
#define dotSceneQuaternion_h_
#include "dotSceneQuaternion.h"
#endif

#ifndef dotSceneScale_h_
#define dotSceneScale_h_
#include "dotSceneScale.h"
#endif

#ifndef dotSceneEntity_h_
#define dotSceneEntity_h_
#include "dotSceneEntity.h"
#endif

#ifndef dotSceneLight_h_
#define dotSceneLight_h_
#include "dotSceneLight.h"
#endif

#ifndef dotSceneCamera_h_
#define dotSceneCamera_h_
#include "dotSceneCamera.h"
#endif

#ifndef dotSceneElementTags_h_
#define dotSceneElementTags_h_
#include "dotSceneElementTags.h"
#endif

#ifndef list_h_
#define list_h_
#include <list>
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneNode : public dotSceneObject
    {
	private:
		std::string _name;					/**< Property name.*/
		dotScenePosition _position;			/**< Property position.*/
		dotSceneQuaternion _quaternion;		/**< Property quaternion.*/
		dotSceneScale _scale;				/**< Property scale.*/
		dotSceneSpecific* _specific;		/**< Property specific.*/
		dotSceneElementTags _NodeTypeTag;	/**< Property NodeTypeTag. Delivers type of included spezialisation of general node as dotSceneElementTags:: For example dotSceneElementTags::camera.*/
		std::string _NodeTypeName;			/**< Property NodeTypeName. Delivers type of included spezialisation of general node as sting. For example "camera".*/
	
		void set_NodeTypeTag(dotSceneElementTags value);/**< Set-method for property NodeTypeTag. @param value A dotSceneElementTags-value.*/
		void set_NodeTypeName(std::string value);		/**< Set-method for property NodeTypeName. @param value Value of a std::string.*/
	
	public:
		std::list<dotSceneNode> childNodes;	/**< dotSceneNode-childs of current dotSceneNode.*/

		std::string get_name() const;				/**< Get-method for property name. @return Returns name as std::string.*/
		dotScenePosition get_position() const;		/**< Get-method for property position. @return Returns a dotScenePosition-object.*/
		dotSceneQuaternion get_quaternion() const;	/**< Get-method for property quaternion. @return Returns a dotSceneQuaternion-object.*/
		dotSceneScale get_scale() const;			/**< Get-method for property scale. @return Returns a dotSceneScale-object.*/
		dotSceneSpecific* get_specific() const;		/**< Get-method for property specific. @return Returns a dotSceneSpecific-object.*/
		dotSceneElementTags get_NodeTypeTag() const;/**< Get-method for property NodeTypeTag. @return Returns a dotSceneElementTags-value.*/
		std::string get_NodeTypeName() const;		/**< Get-method for property NodeTypeName. @return Returns NodeTypeName as std::string.*/

		void set_name(std::string value);				/**< Set-method for property name. @param value Value of a std::string.*/
		void set_position(dotScenePosition value);		/**< Set-method for property position. @param value A dotScenePosition-object.*/
		void set_quaternion(dotSceneQuaternion value);	/**< Set-method for property quaternion. @param value A dotSceneQuaternion-object.*/
		void set_scale(dotSceneScale value);			/**< Set-method for property scale. @param value A dotSceneScale-object.*/
		void set_specific(dotSceneSpecific* value);		/**< Set-method for property specific. @param value A dotSceneSpecific-object.*/
				
		/**
		 * This function adds a new dotSceneNode to the list "childNodes".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected acess is not fully implemented.
		 * @param node A dotSceneNode-object.
		 * @return Returns a bool value. TRUE, when there was no problem.
		 */
		bool addChildNode(dotSceneNode node);

        /**
		 * Simple Constructor.
		 */
		dotSceneNode();

		/**
		 * Standard-constructor of dotSceneNode.
		 * Specialisation of this class works throught an object, which inherits from
		 * abstract class dotSceneSpecific. These classes are: 
		 * o dotSceneEntity 
		 * o dotSceneCamera 
		 * o dotSceneLight 
		 * o an unpecialised (empty) dotScene-Node is also possible.
		 * @param str_name Name of the node in ogre3D.
		 * @param obj_position A pre-constrcted dotScenePosition-object.
		 * @param obj_quaternion A pre-constrcted dotSceneQuaternion-object.
		 * @param obj_scale A pre-constrcted dotSceneScale-object.
		 * @param obj_specific Following classes inherit from dotSceneSpecific: dotSceneEntity, dotSceneCamera, dotSceneLight.
		 */
		dotSceneNode(std::string str_name, dotScenePosition obj_position, dotSceneQuaternion obj_quaternion, dotSceneScale obj_scale, /*const dotSceneSpecific&*/dotSceneSpecific* obj_specific);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneNode();
    };
}
