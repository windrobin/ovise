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

#ifndef dotSceneTrackTarget_h_
#define dotSceneTrackTarget_h_
#include "dotSceneTrackTarget.h"
#endif

#ifndef dotSceneLookTarget_h_
#define dotSceneLookTarget_h_
#include "dotSceneLookTarget.h"
#endif

#ifndef dotSceneParticleSystem_h_
#define dotSceneParticleSystem_h_
#include "dotSceneParticleSystem.h"
#endif

#ifndef dotSceneBillboardSet_h_
#define dotSceneBillboardSet_h_
#include "dotSceneBillboardSet.h"
#endif

#ifndef dotScenePlane_h_
#define dotScenePlane_h_
#include "dotScenePlane.h"
#endif

#ifndef dotSceneUserDataReference_h_
#define dotSceneUserDataReference_h_
#include "dotSceneUserDataReference.h"
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
	class dotSceneNode : virtual public dotSceneObject
    {
	private:
		std::string _name;		/**< Property name. Name of node in Orge3D-engine-system.*/
		std::string _ID;		/**< Property ID. ID of node in Orge3D-engine-system.*/
		bool _Visible;			/**< Property Visible. Determine visiblity of node in Orge3D-engine-system.*/
		bool _CascadeVisibility;/**< Property CascadeVisibility. Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.*/
		bool _IsTarget;			/**< Property IsTarget. Determine, if a node is a traget in Orge3D-engine-system. Context not sure. Untested.*/
		
		dotScenePosition _Position;						/**< Property Position. Position of node in Orge3D-engine-system.*/
		dotSceneOrientation _Orientation;				/**< Property Orientation. Orientation of node in Orge3D-engine-system.*/
		dotSceneScale _Scale;							/**< Property Scale. Scale of node in Orge3D-engine-system.*/
		dotSceneLookTarget _LookTarget;					/**< Property LookTarget. Additional data for tracking? Context not sure. Untested.*/
		dotSceneTrackTarget _TrackTarget;				/**< Property TrackTarget. Additional data for tracking? Context not sure. Untested.*/
		dotSceneUserDataReference _UserDataReference;	/**< Property UserDataReference. Context not sure. Untested.*/

	public:
		// lists
		std::list<dotSceneNode> _ListOfChildNodes;					/**< Property ListOfChildNodes. Contais all child-nodes of a node.*/
		std::list<dotSceneEntity> _ListOfEntities;					/**< Property ListOfEntities. Contais all entities assigned to a node.*/
		std::list<dotSceneLight> _ListOfLights;					/**< Property ListOfLights. Contais all lightsources assigned to a node.*/
		std::list<dotSceneCamera> _ListOfCameras;					/**< Property ListOfCameras. Contais all cameras assigned to a node.*/
		std::list<dotSceneParticleSystem> _ListOfParticleSystems;	/**< Property ListOfParticleSystems. Contais all particle-systems assigned to a node. Context not sure. Untested.*/
		std::list<dotSceneBillboardSet> _ListOfBillboardSets;		/**< Property ListOfBillboardSets. Contais all billboard-sets assigned to a node. Context not sure. Untested.*/
		std::list<dotScenePlane> _ListOfPlanes;						/**< Property ListOfPlanes. Contais all planes assigned to a node. Context not sure. Untested.*/

		std::string get_name() const;		/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_ID() const;			/**< Get-method for property ID. @return Returns ID as std::string.*/
		bool get_Visible() const;			/**< Get-method for property Visible. @return Returns Visible as bool.*/
		bool get_CascadeVisibility() const;	/**< Get-method for property CascadeVisibility. @return Returns name as bool.*/
		bool get_IsTarget() const;			/**< Get-method for property IsTarget. @return Returns name as bool.*/
		
		dotScenePosition get_Position() const;					/**< Get-method for property Position. @return Returns a "dotScenePosition"-object.*/
		dotSceneOrientation get_Orientation() const;			/**< Get-method for property Orientation. @return Returns a "dotSceneOrientation"-object.*/
		dotSceneScale get_Scale() const;						/**< Get-method for property Scale. @return Returns a "dotSceneScale"-object.*/
		dotSceneLookTarget get_LookTarget() const;				/**< Get-method for property LookTarget. @return Returns a "dotSceneLookTarget"-object.*/
		dotSceneTrackTarget get_TrackTarget() const;			/**< Get-method for property TrackTarget. @return Returns a "dotSceneTrackTarget"-object.*/
		dotSceneUserDataReference get_UserDataReference() const;/**< Get-method for property UserDataReference. @return Returns a "dotSceneUserDataReference"-object.*/

		void set_name(std::string value);		/**< Set-method for property name. @param value Value of a std::string.*/
		void set_ID(std::string value);			/**< Set-method for property ID. @param value Value of a std::string.*/
		void set_Visible(bool value);			/**< Set-method for property Visible. @param value Value of a bool.*/
		void set_CascadeVisibility(bool value);	/**< Set-method for property CascadeVisibility. @param value Value of a bool.*/
		void set_IsTarget(bool value);			/**< Set-method for property IsTarget. @param value Value of a bool.*/
		
		void set_Position(dotScenePosition value);					/**< Set-method for property Position. @param value A "dotScenePosition"-object.*/
		void set_Orientation(dotSceneOrientation value);			/**< Set-method for property Orientation. @param value A "dotSceneOrientation"-object.*/
		void set_Scale(dotSceneScale value);						/**< Set-method for property Scale. @param value A "dotSceneScale"-object.*/
		void set_LookTarget(dotSceneLookTarget value);				/**< Set-method for property LookTarget. @param value A "dotSceneLookTarget"-object.*/
		void set_TrackTarget(dotSceneTrackTarget value);			/**< Set-method for property TrackTarget. @param value A "dotSceneTrackTarget"-object.*/
		void set_UserDataReference(dotSceneUserDataReference value);/**< Set-method for property UserDataReference. @param value A "dotSceneUserDataReference"-object.*/

		void set_Visible(std::string value);			/**< Set-method for property Visible. @param value Value of a std::string.*/
		void set_CascadeVisibility(std::string value);	/**< Set-method for property CascadeVisibility. @param value Value of a std::string.*/
		void set_IsTarget(std::string value);			/**< Set-method for property IsTarget. @param value Value of a std::string.*/

		bool HasChilds() const;
		bool HasCamera() const;
		bool HasEntity() const;
		bool HasLight() const;

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
		/**
		 * This method adds a new dotSceneNode to list "ListOfChildNodes".
		 * @param someNode A dotSceneNode-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addChildNode(dotSceneNode someNode);

		/**
		 * This method adds a new dotSceneEntity to the list "ListOfEntities".
		 * @param someEntity A "dotSceneEntity"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addEntity(dotSceneEntity someEntity);

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
		 * This method adds a new dotSceneParticleSystem to list "ListOfParticleSystems".
		 * @param someParticleSystem A "dotSceneParticleSystem"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addParticleSystem(dotSceneParticleSystem someParticleSystem);

		/**
		 * This method adds a new dotSceneBillboardSet to list "ListOfBillboardSets".
		 * @param someBillboardSet A "dotSceneBillboardSet"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addBillboardSet(dotSceneBillboardSet someBillboardSet);

		/**
		 * This method adds a new dotScenePlane to list "ListOfPlanes".
		 * @param somePlane A "dotScenePlane"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addPlane(dotScenePlane somePlane);

        /**
		 * Simple Constructor.
		 */
		dotSceneNode();

		/**
		 * Full initialisation constructor of dotSceneNode.
		 * All std::string-values will be parsed automatically.
		 * @param str_name Name of the node in ogre3D.
		 * @param str_name  ID of node in Orge3D-engine-system.
		 * @param str_Visible Determine visiblity of node in Orge3D-engine-system.
		 * @param str_CascadeVisibility Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.
		 * @param str_IsTarget Determine, if a node is a traget in Orge3D-engine-system. Context not sure. Untested.
		 * @param obj_Position Position of node in Orge3D-engine-system.
		 * @param obj_Orientation Orientation of node in Orge3D-engine-system.
		 * @param obj_Scale Scale of node in Orge3D-engine-system.
		 * @param obj_LookTarget Additional data for tracking? Context not sure. Untested.
		 * @param obj_TrackTarget Additional data for tracking? Context not sure. Untested.
		 * @param obj_UserDataReference Context not sure. Untested.
		 */
		dotSceneNode(
			std::string str_name,
			std::string str_ID,
			std::string str_Visible,
			std::string str_CascadeVisibility,
			std::string str_IsTarget,	
			dotScenePosition obj_Position,	
			dotSceneOrientation obj_Orientation,
			dotSceneScale obj_Scale,
			dotSceneLookTarget obj_LookTarget,
			dotSceneTrackTarget obj_TrackTarget,
			dotSceneUserDataReference obj_UserDataReference);

		/**
		 * Full initialisation constructor of dotSceneNode.
		 * @param str_name Name of the node in ogre3D.
		 * @param str_name  ID of node in Orge3D-engine-system.
		 * @param bool_Visible Determine visiblity of node in Orge3D-engine-system.
		 * @param bool_CascadeVisibility Determine behavior of visiblity of node in Orge3D-engine-system, relating to it's parent-node. Context not sure. Untested.
		 * @param bool_IsTarget Determine, if a node is a traget in Orge3D-engine-system. Context not sure. Untested.
		 * @param obj_Position Position of node in Orge3D-engine-system.
		 * @param obj_Orientation Orientation of node in Orge3D-engine-system.
		 * @param obj_Scale Scale of node in Orge3D-engine-system.
		 * @param obj_LookTarget Additional data for tracking? Context not sure. Untested.
		 * @param obj_TrackTarget Additional data for tracking? Context not sure. Untested.
		 * @param obj_UserDataReference Context not sure. Untested.
		 */
		dotSceneNode(
			std::string str_name,
			std::string str_ID,
			bool bool_Visible,
			bool bool_CascadeVisibility,
			bool bool_IsTarget,
			dotScenePosition obj_Position,	
			dotSceneOrientation obj_Orientation,
			dotSceneScale obj_Scale,
			dotSceneLookTarget obj_LookTarget,
			dotSceneTrackTarget obj_TrackTarget,
			dotSceneUserDataReference obj_UserDataReference);

		/**
		 * Copy-Constructor.
		 */
		dotSceneNode(const dotSceneNode& CopyObject);
    };
}
