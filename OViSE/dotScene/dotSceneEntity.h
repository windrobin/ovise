#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneEntityEnums_h_
#define dotSceneEntityEnums_h_
#include "dotSceneEntityEnums.h"
#endif

#ifndef dotSceneMaterialLODBias_h_
#define dotSceneMaterialLODBias_h_
#include "dotSceneMaterialLODBias.h"
#endif

#ifndef dotSceneMeshLODBias_h_
#define dotSceneMeshLODBias_h_
#include "dotSceneMeshLODBias.h"
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
	 * This class hold all information, needed for an Ogre::Enity class.
	 */
	class dotSceneEntity : virtual public dotSceneObject 
    {
	private:
		std::string _meshFile;							/**< Property meshFile. Filename of mesh-file, which is used for the entity.*/
		std::string _name;								/**< Property name. Name of file.*/

		std::string _ID;								/**< (NEW) Property ID. ID of entity. Don't know how this value is related to. This attribute is new and untested. (Nov 2008)*/		
		std::string _materialName;						/**< (NEW) Property materialName. Name of material applied to entity. This attribute is new and untested. (Nov 2008).*/
		bool _displaySkeleton;							/**< (NEW) Property displaySkeleton. 'true', if polygon-skeleton should be displayed. Default is 'false'. This attribute is new and untested. (Nov 2008).*/
		bool _polygonModeOverrideable;					/**< (NEW) Property polygonModeOverrideable. 'true', if polygon-mode can be changed. Default is 'false'. This attribute is new and untested. (Nov 2008).*/
		std::string _softwareAnimationRequests;			/**< (NEW) Property softwareAnimationRequests. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		std::string _softwareAnimationRequestsNormalsAlso;					/**< (NEW) Property softwareAnimationRequestsNormalsAlso. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		dotSceneEnums::dotSceneEntityEnums::BufferUsage _vertexBufferUsage;	/**< (NEW) Property vertexBufferUsage. Default-value is 'BufferUsage_staticWriteOnly'. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		bool _vertexBufferUseShadow;										/**< (NEW) Property vertexBufferUseShadow. Default-value is 'false'. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		dotSceneEnums::dotSceneEntityEnums::BufferUsage _indexBufferUsage;	/**< (NEW) Property indexBufferUsage. Default-value is 'BufferUsage_staticWriteOnly'. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		bool _indexBufferUseShadow;											/**< (NEW) Property indexBufferUseShadow. Default-value is 'false'. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/

		dotSceneCommonMovableObjectParams _CommonMovableObjectParams;	/**< (NEW) Property CommonMovableObjectParams. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		dotSceneMeshLODBias _MeshLODBias;				/**< (NEW) Property MeshLODBias. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		dotSceneMaterialLODBias _MaterialLODBias;		/**< (NEW) Property MaterialLODBias. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/
		dotSceneUserDataReference _UserDataReference;	/**< (NEW) Property UserDataReference. Functionality not identified yet. This attribute is new and untested. (Nov 2008).*/

	public:
		std::list<dotSceneObject> _animations;			/**< Animations not implemented yet.*/
		std::list<dotSceneObject> _animationStates;		/**< Animations not implemented yet.*/

		std::string get_meshFile() const;				/**< Get-method for property meshFile. @return Returns meshFile as a std::string.*/
		std::string get_name() const;					/**< Get-method for property name. @return Returns name as a std::string.*/

		std::string get_ID() const;						/**< (NEW) Get-method for property "ID". @return Returns "ID" as a std::string.*/
		std::string get_materialName() const;			/**< (NEW) Get-method for property "materialName". @return Returns "materialName" as a std::string.*/
		bool get_displaySkeleton() const;				/**< (NEW) Get-method for property "displaySkeleton". @return Returns "displaySkeleton" as a bool.*/
		bool get_polygonModeOverrideable() const;		/**< (NEW) Get-method for property "polygonModeOverrideable". @return Returns "polygonModeOverrideable" as a bool.*/
		std::string get_softwareAnimationRequests() const;								/**< (NEW) Get-method for property "softwareAnimationRequests". @return Returns "softwareAnimationRequests" as a std::string.*/
		std::string get_softwareAnimationRequestsNormalsAlso() const;					/**< (NEW) Get-method for property "softwareAnimationRequestsNormalsAlso". @return Returns "softwareAnimationRequestsNormalsAlso" as a std::string.*/
		dotSceneEnums::dotSceneEntityEnums::BufferUsage get_vertexBufferUsage() const;	/**< (NEW) Get-method for property "vertexBufferUsage". @return Returns a value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		bool get_vertexBufferUseShadow() const;											/**< (NEW) Get-method for property "vertexBufferUseShadow". @return Returns "vertexBufferUseShadow" as a bool.*/
		dotSceneEnums::dotSceneEntityEnums::BufferUsage get_indexBufferUsage() const;	/**< (NEW) Get-method for property "indexBufferUsage". @return Returns a value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		bool get_indexBufferUseShadow() const;											/**< (NEW) Get-method for property "indexBufferUseShadow". @return Returns "indexBufferUseShadow" as a bool.*/

		dotSceneCommonMovableObjectParams get_CommonMovableObjectParams() const;		/**< (NEW) Get-method for property "CommonMovableObjectParams". @return Returns a "dotSceneCommonMovableObjectParams"-object.*/
		dotSceneMeshLODBias get_MeshLODBias() const;			/**< (NEW) Get-method for property "MeshLODBias". @return Returns a "dotSceneMaterialLODBias"-object.*/
		dotSceneMaterialLODBias get_MaterialLODBias() const;	/**< (NEW) Get-method for property "MaterialLODBias". @return Returns a "dotSceneMeshLODBias"-object.*/
		dotSceneUserDataReference get_UserDataReference() const;/**< (NEW) Get-method for property "UserDataReference". @return Returns a "dotSceneUserDataReference"-object.*/

		void set_name(std::string value);				/**< Set-method for property name. @param value Value of a std::string.*/
		void set_meshFile(std::string value);			/**< Set-method for property meshFile. @param value Value of a std::string.*/

		void set_ID(std::string value);					/**< (NEW) Set-method for property "ID". @param value Value of a std::string.*/
		void set_materialName(std::string value);		/**< (NEW) Set-method for property "materialName". @param value Value of a std::string.*/
		void set_displaySkeleton(bool value);			/**< (NEW) Set-method for property "displaySkeleton". @param value Value of a bool.*/
		void set_polygonModeOverrideable(bool value);	/**< (NEW) Set-method for property "polygonModeOverrideable". @param value Value of a bool.*/
		void set_softwareAnimationRequests(std::string value);								/**< (NEW) Set-method for property "softwareAnimationRequests". @param value Value of a std::string.*/
		void set_softwareAnimationRequestsNormalsAlso(std::string value);					/**< (NEW) Set-method for property "softwareAnimationRequestsNormalsAlso". @param value Value of a std::string.*/
		void set_vertexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage value);	/**< (NEW) Set-method for property "vertexBufferUsage". @param value Value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		void set_vertexBufferUseShadow(bool value);											/**< (NEW) Set-method for property "vertexBufferUseShadow". @param value Value of a bool.*/
		void set_indexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage value);	/**< (NEW) Set-method for property "indexBufferUsage". @param value Value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		void set_indexBufferUseShadow(bool value);											/**< (NEW) Set-method for property "indexBufferUseShadow". @param value Value of a bool.*/

		void set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value);		/**< (NEW) Set-method for property "CommonMovableObjectParams". @param value A "dotSceneCommonMovableObjectParams"-object.*/
		void set_MeshLODBias(dotSceneMeshLODBias value);			/**< (NEW) Set-method for property "MeshLODBias". @param value A "dotSceneMaterialLODBias"-object.*/
		void set_MaterialLODBias(dotSceneMaterialLODBias value);	/**< (NEW) Set-method for property "MaterialLODBias". @param value A "dotSceneMeshLODBias"-object.*/
		void set_UserDataReference(dotSceneUserDataReference value);/**< (NEW) Set-method for property "UserDataReference". @param value A "dotSceneUserDataReference"-object.*/

		void set_displaySkeleton(std::string value);		/**< (NEW) Set-method for property "displaySkeleton". @param value Value of a bool.*/
		void set_polygonModeOverrideable(std::string value);/**< (NEW) Set-method for property "polygonModeOverrideable". @param value Value of a bool.*/
		void set_vertexBufferUsage(std::string value);		/**< (NEW) Set-method for property "vertexBufferUsage". @param value Value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		void set_vertexBufferUseShadow(std::string value);	/**< (NEW) Set-method for property "vertexBufferUseShadow". @param value Value of a bool.*/
		void set_indexBufferUsage(std::string value);		/**< (NEW) Set-method for property "indexBufferUsage". @param value Value of dotSceneEnums::dotSceneEntityEnums::BufferUsage.*/
		void set_indexBufferUseShadow(std::string value);	/**< (NEW) Set-method for property "indexBufferUseShadow". @param value Value of a bool.*/

		bool addAnimantion(dotSceneObject someAnimation);
		bool addAnimantionState(dotSceneObject someAnimationState);

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 * Calls constructor of baseobject.
		 */
		dotSceneEntity();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double & bool(integer) -format.
		 * @param str_meshFile Filename of Mesh. For example: "teacup.mesh"
		 * @param str_name Name equals the MeshFile-HashKey.
		 * @param str_ID Some ID. Context unknown.
		 * @param str_materialName Name of material, applied to entity.
		 * @param str_displaySkeleton Context unknown. Will be parsed automaticcally to value-type.
		 * @param str_polygonModeOverrideable Context unknown. Will be parsed automaticcally to value-type.
		 * @param str_softwareAnimationRequests Context unknown.
		 * @param str_softwareAnimationRequestsNormalsAlso  Context unknown.
		 * @param str_vertexBufferUsage Context unknown. Will be parsed automaticcally to enum-type.
		 * @param str_vertexBufferUseShadow Context unknown. Will be parsed automaticcally to value-type.
		 * @param str_indexBufferUsage Context unknown. Will be parsed automaticcally to enum-type.
		 * @param str_indexBufferUseShadow Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_CommonMovableObjectParams Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_MeshLODBias  Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_MaterialLODBias Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_UserDataReference Context unknown. Will be parsed automaticcally to value-type.
		 */
		dotSceneEntity(
			std::string str_meshFile,
			std::string str_name,
			std::string str_ID,
			std::string str_materialName,
			std::string str_displaySkeleton,
			std::string str_polygonModeOverrideable,
			std::string str_softwareAnimationRequests,
			std::string str_softwareAnimationRequestsNormalsAlso,
			std::string str_vertexBufferUsage,
			std::string str_vertexBufferUseShadow,
			std::string str_indexBufferUsage,
			std::string str_indexBufferUseShadow,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotSceneMeshLODBias obj_MeshLODBias,
			dotSceneMaterialLODBias obj_MaterialLODBias,
			dotSceneUserDataReference obj_UserDataReference);
		
		/**
		 * Standard-constructor for direct value-parameters.
		 * @param str_meshFile Filename of Mesh. For example: "teacup.mesh"
		 * @param str_name Name equals the MeshFile-HashKey.
		 * @param str_ID Some ID. Context unknown.
		 * @param str_materialName Name of material, applied to entity.
		 * @param bool_displaySkeleton Context unknown.
		 * @param bool_polygonModeOverrideable  Context unknown.
		 * @param str_softwareAnimationRequests  Context unknown.
		 * @param str_softwareAnimationRequestsNormalsAlso  Context unknown.
		 * @param enum_vertexBufferUsage  Context unknown.
		 * @param bool_vertexBufferUseShadow  Context unknown.
		 * @param enum_indexBufferUsage  Context unknown.
		 * @param bool_indexBufferUseShadow  Context unknown.
		 * @param obj_CommonMovableObjectParams Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_MeshLODBias  Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_MaterialLODBias Context unknown. Will be parsed automaticcally to value-type.
		 * @param obj_UserDataReference Context unknown. Will be parsed automaticcally to value-type.
		 */
		dotSceneEntity(std::string str_meshFile,
			std::string str_name,
			std::string str_ID,
			std::string str_materialName,
			bool bool_displaySkeleton,
			bool bool_polygonModeOverrideable,
			std::string str_softwareAnimationRequests,
			std::string str_softwareAnimationRequestsNormalsAlso,
			dotSceneEnums::dotSceneEntityEnums::BufferUsage enum_vertexBufferUsage,
			bool bool_vertexBufferUseShadow,
			dotSceneEnums::dotSceneEntityEnums::BufferUsage enum_indexBufferUsage,
			bool bool_indexBufferUseShadow,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotSceneMeshLODBias obj_MeshLODBias,
			dotSceneMaterialLODBias obj_MaterialLODBias,
			dotSceneUserDataReference obj_UserDataReference);

		/**
		 * Copy-Constructor.
		 */
		dotSceneEntity(const dotSceneEntity& CopyObject);
    };
}

// OLD methods and attributes of older format versions than 1.0.0
		// Old attributes
		//bool _static;									/**< Property static. Boolean attribute, representing the initial value of static.*/
		//bool _visible;								/**< Property visible. Boolean attribute, representing the initial value for Ogre::Entity::Visible.*/
		//bool _castShadows;							/**< Property castShadows. Boolean attribute, representing the initial value for Ogre::Entity::CastShadows.*/
		//double _renderingDistance;					/**< Property renderingDistance. Boolean attribute, representing the initial value for renderingDistance of Ogre::Entity.*/

		//bool get_static() const;						/**< Get-method for property static. @return Returns static as bool.*/
		//bool get_visible() const;						/**< Get-method for property visible. @return Returns visible as bool.*/
		//bool get_castShadows() const;					/**< Get-method for property castShadows. @return Returns castShadows as bool.*/
		//double get_renderingDistance() const;			/**< Get-method for property renderingDistance. @return Returns renderingDistance as bool.*/

		//void set_static(bool value);					/**< Set-method for property static. @param value Value of a bool.*/
		//void set_visible(bool value);					/**< Set-method for property visible. @param value Value of a bool.*/
		//void set_castShadows(bool value);				/**< Set-method for property castShadows. @param value Value of a bool.*/
		//void set_renderingDistance(double value);		/**< Set-method for property renderingDistance. @param value Value of a bool.*/

		//void set_static(std::string value);				/**< Set-method for property static. @param value Value in std::string-format. Will be parsed to bool. Allowed values "0" and "1".*/
		//void set_visible(std::string value);			/**< Set-method for property visible. @param value Value in std::string-format. Will be parsed to bool. Allowed values "0" and "1".*/
		//void set_castShadows(std::string value);		/**< Set-method for property castShadows. @param value Value in std::string-format. Will be parsed to bool. Allowed values "0" and "1".*/
		//void set_renderingDistance(std::string value);	/**< Set-method for property renderingDistance. @param value Value in std::string-format. Will be parsed to double.*/
