#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneNodes_h_
#define dotSceneNodes_h_
#include "dotSceneNodes.h"
#endif

#ifndef dotSceneExternals_h_
#define dotSceneExternals_h_
#include "dotSceneExternals.h"
#endif

#ifndef dotSceneEnvironment_h_
#define dotSceneEnvironment_h_
#include "dotSceneEnvironment.h"
#endif

#ifndef dotSceneShadowSettings_h_
#define dotSceneShadowSettings_h_
#include "dotSceneShadowSettings.h"
#endif

#ifndef list_h_
#define list_h_
#include <list>
#endif

#pragma once

namespace dotSceneObjects
{
	/**
	 * Class dotScene contains all data, which is need for construction an entire scene.
	 * This class is made to contain a complete description of a dotScene-XML.
	 * dotScene-Version 1.0.0 is used. All classes of the dotSceneObjects-concept are
	 * planned as passive classes. So a XML-reader-class should fill the structure and
	 * a factory should interprete a dotScene-class like a blueprint.
	 */
	class dotScene : virtual public dotSceneObjects::dotSceneObject
	{
	private:
		std::string _FormatVersion;		/**< Property FormatVersion. Version of dotScene.dtd (dotScene.xsd), used for the contained scene.*/
		std::string _ID;				/**< Property ID. ID, identify this scene-configuration.*/
		std::string _SceneManagerType;	/**< Property SceneManagerType. Describes used type of Ogre3D-scenemanager.*/
		std::string _SceneManagerName;	/**< Property SceneManagerName. Name of used scenemanager.*/
		std::string _MinOgreVersion;	/**< Property MinOgreVersion. Minimal version of Ogre3D-engine to use this scene-data.*/
		std::string _Author;			/**< Property Author. Author of this dotSceneFile.*/
		bool _ShowBoundingBoxes;		/**< Property ShowBoundingBoxes. Untested. Context unknown.*/

		dotSceneShadowSettings _ShadowSettings;			/**< Property ShadowSettings. Setting for usage of shadows in this scene.*/
		dotSceneExternals _Externals;					/**< Property Externals. Contains all externals, referencing files. For example material-files.*/
		dotSceneNodes _Nodes;							/**< Property Nodes. Contais all nodes of the scene. Including entities, cameras and lights.*/
		dotSceneUserDataReference _UserDataReference;	/**< Property UserDataReference. Context unknown.*/

		// resourceGroup		// cardinality: 0..1	// status: ignore
		// sceneManagerOption	// cardinality: 0+		// status: ignore
		// environment			// cardinality: 0..1	// status: ignore		/**< Property environment. Contains information about configuration of environment, like fog, ambient light and so on.*/
		// camera				// cardinality: 0+		// status: ignore
		// animations			// cardinality: 0+		// status: wonT be used
		// animationStates		// cardinality: 0+		// status: wonT be used
		// terrain				// cardinality: 0..1	// status: ignore
		// octree				// cardinality: 0..1	// status: ignore

	public:
		std::list<dotSceneLight> _ListOfLights;		/**< Property ListOfLights. Global lights in this scene, not assigned to a node.*/

		std::string get_FormatVersion() const;		/**< Get-method for property FormatVersion. @return Returns FormatVersion as std::string.*/
		std::string get_ID() const;					/**< Get-method for property ID. @return Returns ID as std::string.*/
		std::string get_SceneManagerType() const;	/**< Get-method for property SceneManagerType. @return Returns SceneManagerType as std::string.*/
		std::string get_SceneManagerName() const;	/**< Get-method for property SceneManagerName. @return Returns SceneManagerName as std::string.*/
		std::string get_MinOgreVersion() const;		/**< Get-method for property MinOgreVersion. @return Returns MinOgreVersion as std::string.*/
		std::string get_Author() const;				/**< Get-method for property Author. @return Returns Author as std::string.*/
		bool		get_ShowBoundingBoxes() const;	/**< Get-method for property ShowBoundingBoxes. @return Returns ShowBoundingBoxes as bool.*/

		dotSceneShadowSettings		get_ShadowSettings() const;		/**< Get-method for property ShadowSettings. @return Returns a "dotSceneShadowSettings"-object.*/
		dotSceneExternals			get_Externals() const;			/**< Get-method for property Externals. @return Returns a "dotSceneExternals"-object.*/
		dotSceneNodes				get_Nodes() const;				/**< Get-method for property Nodes. @return Returns a "dotSceneNodes"-object.*/
		dotSceneUserDataReference	get_UserDataReference() const;	/**< Get-method for property UserDataReference. @return Returns a "dotSceneUserDataReference"-object.*/

		void set_FormatVersion(std::string value);		/**< Set-method for property FormatVersion. @param value Value of std::string.*/
		void set_ID(std::string value);					/**< Set-method for property ID. @param value Value of std::string.*/
		void set_SceneManagerType(std::string value);	/**< Set-method for property SceneManagerType. @param value Value of std::string.*/
		void set_SceneManagerName(std::string value);	/**< Set-method for property SceneManagerName. @param value Value of std::string.*/
		void set_MinOgreVersion(std::string value);		/**< Set-method for property MinOgreVersion. @param value Value of std::string.*/
		void set_Author(std::string value);				/**< Set-method for property Author. @param value Value of std::string.*/
		void set_ShowBoundingBoxes(bool value);			/**< Set-method for property ShowBoundingBoxes. @param value Value of bool.*/

		void set_ShadowSettings(dotSceneShadowSettings value);		/**< Set-method for property ShadowSettings. @param value A "dotSceneShadowSettings"-object.*/
		void set_Externals(dotSceneExternals value);				/**< Set-method for property Externals. @param value A "dotSceneExternals"-object.*/
		void set_Nodes(dotSceneNodes value);						/**< Set-method for property Nodes. @param value A "dotSceneNodes"-object.*/
		void set_UserDataReference(dotSceneUserDataReference value);/**< Set-method for property UserDataReference. @param value A "dotSceneUserDataReference"-object.*/

		void set_ShowBoundingBoxes(std::string value);	/**< Set-method for property ShowBoundingBoxes. @param value Value of std::string.*/

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * This method adds a new dotSceneLight to list "ListOfLights".
		 * @param someLight A dotSceneLight-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addLight(dotSceneLight someLight);

        /**
		 * Simple constructor.
		 */
		dotScene();

		/**
		 * Full initialisation constructor of dotScene.
		 * All std::string-values will be parsed automatically.
		 * @param str_FormatVersion This parameter defines the Version of the dotScene XML-document. For example this Assembly is written for formatVersion "1.0.0".
		 * @param str_ID ID, identify this scene-configuration.
		 * @param str_SceneManagerType Describes used type of Ogre3D-scenemanager.
		 * @param str_SceneManagerName Name of used scenemanager.
		 * @param str_MinOgreVersion Minimal version of Ogre3D-engine to use this scene-data.
		 * @param str_Author Author of this dotSceneFile.
		 * @param str_ShowBoundingBoxes Untested. Context unknown.
		 * @param obj_ShadowSettings A pre-constrcted "dotSceneShadowSettings"-object.
		 * @param obj_Externals A pre-constrcted "dotSceneExternals"-object. It contains file-references like ".material".
		 * @param obj_Nodes A pre-constrcted "dotSceneNodes"-object. It contains all "dotSceneNode"-objects.
		 * @param obj_UserDataReference A pre-constrcted "dotSceneUserDataReference"-object. Untested. Context unknown.
		 
		 */
		dotScene(
			std::string str_FormatVersion,
			std::string str_ID,
			std::string str_SceneManagerType,
			std::string str_SceneManagerName,
			std::string str_MinOgreVersion,
			std::string str_Author,
			std::string str_ShowBoundingBoxes,
			dotSceneShadowSettings obj_ShadowSettings,
			dotSceneExternals obj_Externals,
			dotSceneNodes obj_Nodes,
			dotSceneUserDataReference obj_UserDataReference);

		/**
		 * Full initialisation constructor of dotScene.
		 * @param str_FormatVersion This parameter defines the Version of the dotScene XML-document. For example this Assembly is written for formatVersion "1.0.0".
		 * @param str_ID ID, identify this scene-configuration.
		 * @param str_SceneManagerType Describes used type of Ogre3D-scenemanager.
		 * @param str_SceneManagerName Name of used scenemanager.
		 * @param str_MinOgreVersion Minimal version of Ogre3D-engine to use this scene-data.
		 * @param str_Author Author of this dotSceneFile.
		 * @param bool_ShowBoundingBoxes Untested. Context unknown.
		 * @param obj_ShadowSettings A pre-constrcted "dotSceneShadowSettings"-object.
		 * @param obj_Externals A pre-constrcted "dotSceneExternals"-object. It contains file-references like ".material".
		 * @param obj_Nodes A pre-constrcted "dotSceneNodes"-object. It contains all "dotSceneNode"-objects.
		 * @param obj_UserDataReference A pre-constrcted "dotSceneUserDataReference"-object. Untested. Context unknown.
		 */
		dotScene(
			std::string str_FormatVersion,
			std::string str_ID,
			std::string str_SceneManagerType,
			std::string str_SceneManagerName,
			std::string str_MinOgreVersion,
			std::string str_Author,
			bool bool_ShowBoundingBoxes,
			dotSceneShadowSettings obj_ShadowSettings,
			dotSceneExternals obj_Externals,
			dotSceneNodes obj_Nodes,
			dotSceneUserDataReference obj_UserDataReference);
    };
}
