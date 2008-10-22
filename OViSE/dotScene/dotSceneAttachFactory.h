//Old comments of c# implementation:
///
/*
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Mogre;
*/

#include <string>
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include <hash_map>
#else
#include <map>
#endif

#include <Ogre.h>
#include "DotSceneXmlReader.h"
#include "dotScene.h"


namespace dotSceneAdvanced
{
	using namespace dotSceneObjects;

	/**
	 * Finally, this class implements a factory, which interpretes data of a dotSceneObject-structure.
	 * Manipulators an intern management allow users to work efficently in their projects.
	 * FEATURES:
	 * - complete interpretation of any scene, discribed by a dotScene-XML-document and compatible mesh- and material-files
	 * - any scene can be placed multible time in any project - like a complex object
	 * - names of the components are modified comprehensible
	 * - every single node can be adressed and modified by the usual Mogre.SceneManager methods
	 * .
	 * CLEARNESS: the Mogre.SceneNode, which the factory uses as attach-point is not modified hidden inside the factory.
	 * PORTABLE: it works in the .NET-framework of Mikrosoft. Today, that means with a Windows-OS, using a .NET-Framework Version of 2.0 or grather.
	 * FLEXIBLE: the assembly can be used with C++ Code in a managed environment without problems.
	 * Enjoy it ;-)
	 * Written by H.R., ITEC TH Karlsruhe, Germany, 2007-2008
	 */ 
    class dotSceneAttachFactory
    {
	private:
        // Properies (inner part) of general factory-setting
		/**
		 * Unique name of a dotSceneAttachFactory. 
		 * That's IMPORTANT, because every dotSceneAttachFactory has it's own resource-group in the ogre-engine (!).
		 */
		Ogre::String _UniqueFactoryName;
		/// Unique name of the dotSceneAttachFactory's resource-group in the ogre-engine.
		Ogre::String _NameOfFactoryOwnedMaterialResourceGroup;

		// Properties of general scene-output configuration
		/**
		 * property ScaleOffset.
		 * Factory configuration: this offset value scales the entire scene.
		 * The factor works as a multiplication.
		 * Neutral value: 1.0
		 */
		double _ScaleOffset;
		/**
		 * property PositionOffset.
		 * Factory configuration: this offset value translates the entire scene.
		 * The factor works as a addition.
		 * Neutral value: 0.0
		 * */
		Ogre::Vector3 _PositionOffset;

		/**
		 * properties RollOfEntireScene PitchOfEntireScene and YawOfEntireScene.
		 * Factory configuration: roll-angle-offset turns the complete scene arround the x-axis.
		 * Neutral value: 0.0
		 * The factor works as an additional angle.
		 * Factory configuration: pitch-angle-offset turns the complete scene arround the y-axis.
		 * Factory configuration: yaw-angle-offset turns the complete scene arround the z-axis.
		 */
		Ogre::Degree _RollOfEntireScene , _PitchOfEntireScene, _YawOfEntireScene;

		/**
		 * property ChildOfAttachRootNode.
		 * This property is a reference to the basic node of the scene. When a Ogre::SceneNode
		 * is delivered, the factory creates a child-node , which is used as scene's own
		 * zero point of origin. So there is no change applyed to delivered Ogre::SceneNode.
		 */
		Ogre::SceneNode *_AttachRootNode;
		
		/// Converts a node from XML to Ogre, works recursively to catch all children
		void convertXMLNode(XMLSceneNode *xmlNode, Ogre::SceneNode *parentNode);

		// HashMaps manage to blueprints and their locations
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		//VeRsIoN//stdext::hash_map<std::string, Scene> Scenes;
		stdext::hash_map<std::string, dotScene> Scenes;
		stdext::hash_map<std::string, std::string> LocationsOfMeshFiles;
		stdext::hash_map<std::string, std::string> LocationsOfMaterialFiles;
#else
		//VeRsIoN//std::map<std::string, Scene*> Scenes;
		std::map<std::string, dotScene> Scenes;
		std::map<std::string, std::string> LocationsOfMeshFiles;
		std::map<std::string, std::string> LocationsOfMaterialFiles;
#endif

		// Attributes for interpretation
		Ogre::String _UniqueManagerName;
		Ogre::SceneManager *Mgr;
		Ogre::SceneNode *deliverdExternalRootNode;

		void recursiveNodeCreator(std::list<dotSceneNode> actualNodeList, Ogre::SceneNode* attachParentNode, std::string uniqueSceneName);
	public:
		//@{
		/**
		 * Properties (outer part) of general factory-setting.
		 */
		void set_UniqueFactoryName(Ogre::String);
		Ogre::String get_UniqueFactoryName() const;
		void set_NameOfFactoryOwnedMaterialResourceGroup(Ogre::String);
		Ogre::String get_NameOfFactoryOwnedMaterialResourceGroup() const;
		//@}
		
		//@{
		/// Properties of general scene-output configuration
		double get_ScaleOffset() const;
		void set_ScaleOffset(double);
		Ogre::Vector3 get_PositionOffset() const;
		void set_PositionOffset(Ogre::Vector3);
		//@}
		//@{
		/// Properties RollOfEntireScene, PitchOfEntireScene and YawOfEntireScene
		void set_RollOfEntireScene(Ogre::Degree);
		Ogre::Degree get_RollOfEntireScene() const;
		void set_PitchOfEntireScene(Ogre::Degree);
		Ogre::Degree get_PitchOfEntireScene() const;
		void set_YawOfEntireScene(Ogre::Degree);
		Ogre::Degree get_YawOfEntireScene() const;
		//@}

		/// property ChildOfAttachRootNode
		Ogre::SceneNode* get_LastAttachRootNode() const;

		///@name Factory configuration:
		//@{ 
		/// This value defines, if nodes (entities, lights, cameras) should be deployed.
		bool doAttachNodes;
		/// This value defines, if externals (for example materials) should be registered and used.
		bool doAttachExternals;
		/// This value defines, if the environment configuration (for example fog) should be applied to scene.
		bool doAttachEnvironment;
		//@}

		// Con- & Destructors
		dotSceneAttachFactory(Ogre::String UniqueFactoryName, Ogre::SceneManager* sceneMgr);
        ~dotSceneAttachFactory();

        ///@name Methods to add new "dotScene"-Objects
        //@{
        /**
         * Use this method, to add a new scene blue print to factory, which is contained in a dotScene-object.
         * dotScene-Objects are created in a dotSceneXmlReader-object.
         * @param uniqueSceneName Unique name for new scene blue print. Factory uses this string as hash-key
         * @param newScene A dotScene-object.
         * @param locationOfMeshFiles Location of .mesh and .material files, used in the scene.
         * @return "true", when adding the blue print was successful. Returns false, if not. For example, when uniqueSceneName is not unique.
         */
		bool addSceneBluePrint(std::string uniqueSceneName, dotScene newScene, std::string locationOfMeshFiles); 

		//@{
		/// region methods to attach "dotScene"-Objects
		/**
		 * Use this method, to deploy a scene into your ogre-world.
		 * The scene 'll be generated form the blue print, specified by "uniqueSceneName".
		 * @param uniqueSceneName Identifies the blue print in factorys own blue print storage.
		 * @param attachToNodeWithThisName Mogre.SceneNode, which should be used as zero point of origin of scene.
		 * @param doAttachNodes Sets explicid the "doAttachNodes" factory configuration parameter.
		 * @param doAttachExternals Sets explicitly the "doAttachExternals" factory configuration parameter.
		 * @param doAttachEnvironment Sets explicitly the "doAttachEnvironment" factory configuration parameter.
		 * @param isBlenderImport Sets explicitly the "BlenderImport" factory configuration parameter.
		 * @return "true", when process was successful. If not, it returns "false". For example, when "uniqueSceneName" is unknown.
		 */
		bool attachSingleSceneTo(std::string uniqueSceneName, std::string attachToNodeWithThisName, 
								bool doAttachNodes, bool doAttachExternals, bool doAttachEnvironment);
		/**
		 * Use this method, to deploy a scene into your ogre-world.
		 * The scene 'll be generated form the blue print, specified by "uniqueSceneName".
		 * @param uniqueSceneName Identifies the blue print in factorys own blue print storage.
		 * @param attachToNodeWithThisName Mogre.SceneNode, which should be used as zero point of origin of scene.
		 * @return "true", when process was successful. If not, it returns "false". For example, when "uniqueSceneName" is unknown.
		 */
		bool attachSingleSceneTo(std::string uniqueSceneName, std::string attachToNodeWithThisName); 
		//@}
		//@}
	};
}