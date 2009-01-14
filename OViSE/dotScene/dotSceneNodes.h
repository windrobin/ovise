#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#ifndef dotSceneOrientation_h_
#define dotSceneOrientation_h_
#include "dotSceneOrientation.h"
#endif

#ifndef dotSceneScale_h_
#define dotSceneScale_h_
#include "dotSceneScale.h"
#endif

#ifndef dotSceneLight_h_
#define dotSceneLight_h_
#include "dotSceneLight.h"
#endif

#ifndef dotSceneCamera_h_
#define dotSceneCamera_h_
#include "dotSceneCamera.h"
#endif

#ifndef dotSceneNode_h_
#define dotSceneNode_h_
#include "dotSceneNode.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class contains dotSceneNode-objects, which are stored in a list.
	 */
	class dotSceneNodes : virtual public dotSceneObject
    {
	private:
		bool _Visible;			/**< Property Visible. Determine visiblity of node in Orge3D-engine-system.*/
		bool _CascadeVisibility;/**< Property CascadeVisibility. Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.*/

		dotScenePosition _Position;			/**< Property Position. Position of node in Orge3D-engine-system.*/
		dotSceneOrientation _Orientation;	/**< Property Orientation. Orientation of node in Orge3D-engine-system.*/
		dotSceneScale _Scale;				/**< Property Scale. Scale of node in Orge3D-engine-system.*/

	public:
		std::list<dotSceneNode> _ListOfNodes;		/**< Property ListOfChildNodes. Contais all nodes.*/
		std::list<dotSceneLight> _ListOfLights;		/**< Property ListOfLights. Contais all lightsources assigned to a node.*/
		std::list<dotSceneCamera> _ListOfCameras;	/**< Property ListOfCameras. Contais all cameras assigned to a node.*/

		bool get_Visible() const;					/**< Get-method for property Visible. @return Returns Visible as bool.*/
		bool get_CascadeVisibility() const;			/**< Get-method for property CascadeVisibility. @return Returns name as bool.*/
		dotScenePosition get_Position() const;		/**< Get-method for property Position. @return Returns a "dotScenePosition"-object.*/
		dotSceneOrientation get_Orientation() const;/**< Get-method for property Orientation. @return Returns a "dotSceneOrientation"-object.*/
		dotSceneScale get_Scale() const;			/**< Get-method for property Scale. @return Returns a "dotSceneScale"-object.*/

		void set_Visible(bool value);					/**< Set-method for property Visible. @param value Value of a bool.*/
		void set_CascadeVisibility(bool value);			/**< Set-method for property CascadeVisibility. @param value Value of a bool.*/
		void set_Position(dotScenePosition value);		/**< Set-method for property Position. @param value A "dotScenePosition"-object.*/
		void set_Orientation(dotSceneOrientation value);/**< Set-method for property Orientation. @param value A "dotSceneOrientation"-object.*/
		void set_Scale(dotSceneScale value);			/**< Set-method for property Scale. @param value A "dotSceneScale"-object.*/
		
		void set_Visible(std::string value);			/**< Set-method for property Visible. @param value Value of a std::string.*/
		void set_CascadeVisibility(std::string value);	/**< Set-method for property CascadeVisibility. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * This method adds a new dotSceneNode to list "ListOfNodes".
		 * @param someNode A dotSceneNode-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addNode(dotSceneNode someNode);

		/**
		 * This method adds a new dotSceneLight to list "ListOfLights".
		 * @param someLight A "dotSceneLight"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addLight(dotSceneLight someLight);

		/**
		 * This method adds a new dotSceneCamera to list "ListOfCamera".
		 * @param someCamera A "dotSceneCamera"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addCamera(dotSceneCamera someCamera);

        /**
		 * Simple Constructor.
		 */
		dotSceneNodes();

		/**
		 * Full initialisation constructor of dotSceneNodes.
		 * All std::string-values will be parsed automatically.
		 * @param str_Visible Determine visiblity of node in Orge3D-engine-system.
		 * @param str_CascadeVisibility Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.
		 * @param obj_Position Position of node in Orge3D-engine-system.
		 * @param obj_Orientation Orientation of node in Orge3D-engine-system.
		 * @param obj_Scale Scale of node in Orge3D-engine-system.
		 */
		dotSceneNodes(
			std::string str_Visible,
			std::string str_CascadeVisibility,	
			dotScenePosition obj_Position,	
			dotSceneOrientation obj_Orientation,
			dotSceneScale obj_Scale);

		/**
		 * Full initialisation constructor of dotSceneNodes.
		 * @param bool_Visible Determine visiblity of node in Orge3D-engine-system.
		 * @param bool_CascadeVisibility Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.
		 * @param obj_Position Position of node in Orge3D-engine-system.
		 * @param obj_Orientation Orientation of node in Orge3D-engine-system.
		 * @param obj_Scale Scale of node in Orge3D-engine-system.
		 */
		dotSceneNodes(
			bool bool_Visible,
			bool bool_CascadeVisibility,
			dotScenePosition obj_Position,	
			dotSceneOrientation obj_Orientation,
			dotSceneScale obj_Scale);

		/**
		 * Copy-Constructor.
		 */
		dotSceneNodes(const dotSceneNodes& CopyObject);
    };
}
