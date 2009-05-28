#ifndef DOTSCENEATTACHFACTORY_H_
#define DOTSCENEATTACHFACTORY_H_

// Inlcude Xerces
#ifndef Xerxes_Used
#define Xerxes_Used
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLFloat.hpp>
#include <string>
#endif

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include dotSceneObjects
#define dotScene_h_

#ifndef dotScene_h_
#define dotScene_h_
#include "dotScene.h"
#endif

// Include dotSceneReader
#ifndef dotSceneXmlReader_h_
#define dotSceneXmlReader_h_
#include "dotSceneXmlReader.h"
#endif

// Include containers
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include <hash_map>
#else
#include <map>
#endif

#define ATTACH_FACTORY__ALLOW_INTERPRETATION_ASSUMPTIONS

namespace dotSceneAdvanced
{
	/**
	 * Finally, this class implements a factory, which interpretes data from a DOM-structure.
	 * Manipulators and internal management allow to work flexible and efficently in any project.
	 * FEATURES:
	 * - complete interpretation of any scene, discribed by a dotScene-XML-document and compatible mesh- and material-files
	 * - any scene can be placed multible time in any project - like a complex object
	 * - names of the components are modified comprehensible
	 * - every single node can be adressed and modified by the usual methods of Ogre::SceneManager
	 * Enjoy it ;-)
	 * Written by H.R., ITEC TH Karlsruhe, Germany, 2008-2009
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
		Ogre::String _NameOfFactoryOwnedResourceGroup;

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
		Ogre::SceneNode *_AttachRootNode; //<- Green List: rename to "SceneRootNode"
		
		/// Converts a node from XML to Ogre, works recursively to catch all children
		//void convertXMLNode(XMLSceneNode *xmlNode, Ogre::SceneNode *parentNode);

		// HashMaps manage to blueprints and their locations
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		stdext::hash_map<std::string, xercesc::DOMDocument*> DOMScenes;
		stdext::hash_map<std::string, std::string> LocationsOfMeshFiles;
		stdext::hash_map<std::string, std::string> LocationsOfMaterialFiles;
#else // Unix Libs
		std::map<std::string, xercesc::DOMDocument*> DOMScenes;
		std::map<std::string, std::string> LocationsOfMeshFiles;
		std::map<std::string, std::string> LocationsOfMaterialFiles;
#endif

		// Attributes for interpretation
		Ogre::String _UniqueManagerName;
		Ogre::SceneManager *Mgr;
		Ogre::SceneNode *ExternalAnchorNode;

		void v1_0_0_Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, std::string UniqueNameOfScene);
		void v1_0_0_Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes);
		void v1_0_0_Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode);
		void v1_0_0_Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode);
		void v1_0_0_Interpretation_Camera(xercesc::DOMElement* DOMElement_camera);

		Ogre::Vector3 v1_0_0_Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3);
		Ogre::Vector4 v1_0_0_Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4);

	public:
		//@{
		/**
		 * Properties (outer part) of general factory-setting.
		 */
		void set_UniqueFactoryName(Ogre::String);
		Ogre::String get_UniqueFactoryName() const;
		void set_NameOfFactoryOwnedResourceGroup(Ogre::String);
		Ogre::String get_NameOfFactoryOwnedResourceGroup() const;
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

		///@name Methods to add new blueprint in DOM-form
        //@{
        /**
         * Use this method, to add a new scene blue print to factory, which is contained in a dotScene-object.
         * dotScene-Objects are created in a dotSceneXmlReader-object.
         * @param uniqueSceneName Unique name for new scene blue print. Factory uses this string as hash-key
         * @param newScene A dotScene-object.
         * @param locationOfMeshFiles Location of .mesh and .material files, used in the scene.
         * @return "true", when adding the blue print was successful. Returns false, if not. For example, when uniqueSceneName is not unique.
         */
		bool addSceneBluePrint(std::string uniqueSceneName, xercesc::DOMDocument* newDOMdotSceneBlueprint, std::string locationOfMeshFiles); 

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
		bool attachSingleDOMSceneTo(std::string uniqueSceneName, std::string attachToNodeWithThisName);
		//@}
		//@}		
	};
}

#endif /*DOTSCENEATTACHFACTORY_H_*/