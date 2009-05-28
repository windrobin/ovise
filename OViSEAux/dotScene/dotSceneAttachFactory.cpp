#include "dotSceneAttachFactory.h"

// TODO: ".get_meshFile()" can grab into the "void" -> throws an Exception!!!!!!!!

// Properies (outer part) of general factory-setting
void dotSceneAdvanced::dotSceneAttachFactory::set_UniqueFactoryName(Ogre::String UniqueFactoryName)
{
	_UniqueFactoryName = UniqueFactoryName;
}

Ogre::String dotSceneAdvanced::dotSceneAttachFactory::get_UniqueFactoryName() const
{
	return _UniqueFactoryName;
}

void dotSceneAdvanced::dotSceneAttachFactory::set_NameOfFactoryOwnedResourceGroup(Ogre::String NameOfFactoryOwnedResourceGroup)
{
	this->_NameOfFactoryOwnedResourceGroup = NameOfFactoryOwnedResourceGroup; 
}	

Ogre::String dotSceneAdvanced::dotSceneAttachFactory::get_NameOfFactoryOwnedResourceGroup() const
{ 
	return this->_NameOfFactoryOwnedResourceGroup; 
}

// Properties of general scene-output configuration
double dotSceneAdvanced::dotSceneAttachFactory::get_ScaleOffset() const 
{ 
	return _ScaleOffset; 
}

void dotSceneAdvanced::dotSceneAttachFactory::set_ScaleOffset(double ScaleOffset) 
{
	_ScaleOffset = ScaleOffset;
} 

Ogre::Vector3 dotSceneAdvanced::dotSceneAttachFactory::get_PositionOffset() const 
{
	return _PositionOffset; 
}

void dotSceneAdvanced::dotSceneAttachFactory::set_PositionOffset(Ogre::Vector3 PositionOffset)
{
	_PositionOffset = PositionOffset;
}

// properties RollOfEntireScene, PitchOfEntireScene and YawOfEntireScene
void dotSceneAdvanced::dotSceneAttachFactory::set_RollOfEntireScene(Ogre::Degree value) 
{
	_RollOfEntireScene = value; 
}

Ogre::Degree dotSceneAdvanced::dotSceneAttachFactory::get_RollOfEntireScene() const
{
	return _RollOfEntireScene; 
}

void dotSceneAdvanced::dotSceneAttachFactory::set_PitchOfEntireScene(Ogre::Degree value) 
{ 
	_PitchOfEntireScene = value; 
}

Ogre::Degree dotSceneAdvanced::dotSceneAttachFactory::get_PitchOfEntireScene() const
{
	return _PitchOfEntireScene; 
}

void dotSceneAdvanced::dotSceneAttachFactory::set_YawOfEntireScene(Ogre::Degree value) 
{
	_YawOfEntireScene = value; 
}

Ogre::Degree dotSceneAdvanced::dotSceneAttachFactory::get_YawOfEntireScene() const
{
	return _YawOfEntireScene; 
}

// property ChildOfAttachRootNode
Ogre::SceneNode* dotSceneAdvanced::dotSceneAttachFactory::get_LastAttachRootNode() const  
{
	return _AttachRootNode; 
}

// Con- & Destructors
// Constructor for dotSceneAttachFactory.
// The following standard-valus will be set:
// ScaleOffset = 1.0
// PositionOffset = (0.0, 0.0, 0.0)
// RollOfEntireScene = PitchOfEntireScene = YawOfEntireScene = 0.0
// <param name="uniqueFactoryName">Unique name of the factoy-instance. That's essencial, because a resource-group in ogre engine 'll be allocaeted with this name.</param>
// <param name="attachToThisManager">Mogre.SceneManager, which this factroy should belong to.</param>
dotSceneAdvanced::dotSceneAttachFactory::dotSceneAttachFactory(Ogre::String UniqueFactoryName, Ogre::SceneManager* sceneMgr)
{
	// Store factory's configuration...
	this->set_UniqueFactoryName(UniqueFactoryName);
	this->set_NameOfFactoryOwnedResourceGroup(UniqueFactoryName);

	this->set_ScaleOffset(1.0);
	this->set_PositionOffset(Ogre::Vector3(0.0, 0.0, 0.0));
	this->set_RollOfEntireScene(Ogre::Degree(0.0));
    this->set_PitchOfEntireScene(Ogre::Degree(0.0));
    this->set_YawOfEntireScene(Ogre::Degree(0.0));

	// Create data-structures in ogre's engine for this factory...
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(this->get_NameOfFactoryOwnedResourceGroup());
	
	// Store reference to Ogre::SceneManager
	this->Mgr = sceneMgr;

	// Platform dependent containers.
	// Linix-library contains map, instant of hash_map...
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	this->DOMScenes = stdext::hash_map<std::string, xercesc::DOMDocument*>();
    LocationsOfMeshFiles = stdext::hash_map<std::string, std::string>();
    LocationsOfMaterialFiles = stdext::hash_map<std::string, std::string>();
#else // Linux Libs
	this->DOMScenes = std::map<std::string, xercesc::DOMDocument*>();
	this->LocationsOfMeshFiles = std::map<std::string, std::string>();
	this->LocationsOfMaterialFiles = std::map<std::string, std::string>();
#endif
}
dotSceneAdvanced::dotSceneAttachFactory::~dotSceneAttachFactory() { }

bool dotSceneAdvanced::dotSceneAttachFactory::addSceneBluePrint(std::string uniqueSceneName,
																xercesc::DOMDocument* newDOMdotSceneBlueprint, 
																std::string locationOfMeshFiles)
{
	// <------ If you want to implement a validity check of "locationOfMeshFiles",
	//         do it here. A proper code-snippet in implemented in C# version.

    // Check, if the key is already used.
	// Remember it's name: it has to be unique! If it's not there, return false.			
	if (DOMScenes.find(uniqueSceneName) != DOMScenes.end()) return false;
	
	// Add new objects to all hashtables with same key
	DOMScenes[uniqueSceneName] = newDOMdotSceneBlueprint;
    LocationsOfMeshFiles[uniqueSceneName] = locationOfMeshFiles;

    // IMPLICIT: Expexting ".material"-files always (!)
	//           at location of ".mesh"-files.
    LocationsOfMaterialFiles[uniqueSceneName] = locationOfMeshFiles;
    
    return true;

    //maybe it's more useful to work with exceptions here
    //exception (in general) will be thrown into framework.
}

/// * * * * * * * * * When XML-interpreter was changed, you have to adapt this method. * * * * * * * * * 
// region methods to attach "dotScene"-Objects
bool dotSceneAdvanced::dotSceneAttachFactory::attachSingleSceneTo(	std::string uniqueSceneName,
																	std::string attachToNodeWithThisName,
																	bool doAttachNodes,
																	bool doAttachExternals,
																	bool doAttachEnvironment)
{
    this->doAttachNodes = doAttachNodes;
    this->doAttachExternals = doAttachExternals;
    this->doAttachEnvironment = doAttachEnvironment;

    return true;//attachSingleSceneTo(uniqueSceneName, attachToNodeWithThisName);
}

/*
bool dotSceneAdvanced::dotSceneAttachFactory::attachSingleSceneTo(	std::string uniqueSceneName,
																	std::string attachToNodeWithThisName)
{
	// Save time, if list ist empty...
	if (Scenes.empty()) return false;
	
	// Store external anchor node...
	this->ExternalAnchorNode = this->Mgr->getSceneNode(Ogre::String(attachToNodeWithThisName)); 

	// Generate unique new root SceneNode - Part 1
    // Find a unique name...
    int rootNodeNameModificationCounter = 0;
	char valueAsString[20];
	Ogre::String rootNodeNameToApply = attachToNodeWithThisName + "_SceneRoot";		
	while (this->Mgr->hasSceneNode(rootNodeNameToApply))
    {
        rootNodeNameToApply = attachToNodeWithThisName + "_SceneRoot";
		rootNodeNameToApply = rootNodeNameToApply + "_";
		sprintf(valueAsString, "%i", rootNodeNameModificationCounter);
		rootNodeNameToApply = rootNodeNameToApply + valueAsString;
        rootNodeNameModificationCounter++;
    }
	
	// Generate unique new root SceneNode - Part 2
	// It is used for light- and camera-setup, because lights and cams working with world-coordinates
	this->_AttachRootNode = this->ExternalAnchorNode->createChildSceneNode(Ogre::String(rootNodeNameToApply));

	// Modify scene's rootnode
    // Rotate entire scene with factory-settings for ROLL, PITCH, YAW
	this->_AttachRootNode->pitch(Ogre::Radian(this->get_PitchOfEntireScene()), Ogre::Node::TS_WORLD);
    this->_AttachRootNode->yaw(Ogre::Radian(this->get_YawOfEntireScene()), Ogre::Node::TS_WORLD);
	this->_AttachRootNode->roll(Ogre::Radian(this->get_RollOfEntireScene()), Ogre::Node::TS_WORLD);

    // Scale rootnode
	this->_AttachRootNode->scale((float)this->get_ScaleOffset(), (float)this->get_ScaleOffset(), (float)this->get_ScaleOffset());

    // * * * * * * * * Complete interpretation of data-object * * * * * * * * *                 
	dotScene actualScene = Scenes.find(uniqueSceneName)->second;

	// Create Ogre::String, describing the actual location of file
	Ogre::String actualLocationOfMaterialFile = Ogre::String(this->LocationsOfMaterialFiles[uniqueSceneName]);

	
    // Subsection of interpretation: Externals
	// Step 1: Clear ResourceGroup, when it exists.
	// TODO: Rename "get_NameOfFactoryOwnedMaterialResourceGroup" to "get_NameOfFactoryOwnedResourceGroup"
	// Clear ResourceGroup "Material", when it exists.
	Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(Ogre::String(this->get_NameOfFactoryOwnedResourceGroup()));

	// Step 2: Add path of dotScene-File to own recourcegroup
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::String(LocationsOfMeshFiles[uniqueSceneName]), Ogre::String("FileSystem"), this->get_NameOfFactoryOwnedResourceGroup(), false);

	// Step 3: Optional add materials, if this->doAttachExternals is true...

    if (this->doAttachExternals)
    {   
        
        
        // Register new used .material-File factory-internal
		dotSceneExternals _externals = actualScene.get_Externals();
		
		if (!_externals.items.empty())
		{
			for(std::list<dotSceneItem>::const_iterator itemFromXMLIterator = _externals.items.begin(); itemFromXMLIterator != _externals.items.end(); itemFromXMLIterator++)
			{
				dotSceneItem itemFromXML = *itemFromXMLIterator;
				if(itemFromXML.get_Type() == "material")
				{
					try
					{                                    
						// Clear ResourceGroup, when it exists.
						//Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(get_NameOfFactoryOwnedMaterialResourceGroup());

						// Add location of files to resourcegroup.
						Ogre::ResourceGroupManager::getSingleton().addResourceLocation(actualLocationOfMaterialFile, Ogre::String("FileSystem"), this->get_NameOfFactoryOwnedResourceGroup(), false);

						// Again, initialise ResourceGroup "Material".
						//Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(get_NameOfFactoryOwnedMaterialResourceGroup());                           
					}
					catch(Ogre::Exception e)
					{	
						bool nix = true;
						//if (e.number == Ogre::Exception::ExceptionCodes::ERR_DUPLICATE_ITEM)
							//When "ERR_DUPLICATE_ITEM" occurs: ignore the exception.
							//Dont worry, no bad entries 'll be made into RessourceGroupManager.
						//	;
						//else throw;
					}
				}
			}
		}
		
    }

	// Step 4: Initialize all...
	// Again, initialise ResourceGroup "Material".
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->get_NameOfFactoryOwnedResourceGroup()); 

	// Subsection of interpretation: Nodes (Entities, Cams, Lights)
    if (this->doAttachNodes)
    {
    	Ogre::LogManager::getSingletonPtr()->logMessage("Attaching nodes...");
		recursiveNodeCreator(actualScene.get_Nodes()._ListOfNodes, this->_AttachRootNode, uniqueSceneName);
    }
/*
	// Subsection of interpretation: Environment <-- ATTENTION, malfunction source...because dotScene-format and blenderexporter aren't fully compatible to ogre (?) 
    if (this->doAttachEnvironment)
    {
        // Set up background-colour
        try // if (actualScene.get_environment().get_colourBackground() != null)
        {
			this->Mgr->setAmbientLight(Ogre::ColourValue(
                actualScene.get_environment().get_colourBackground().get_r(),
                actualScene.get_environment().get_colourBackground().get_g(),
                actualScene.get_environment().get_colourBackground().get_b()));
        }
		catch(std::exception e)
		{
			;// Just catch any exceptions like null reference exceptions
		}

        // Set up ambient-colour
            // until now, nothing happens!
            // no corrspondig value in SceneMgr for background-colour?!

        // Set up fog
		try // if (actualScene.get_environment().get_fog() != null)
		{
            // Select fog-mode
			Ogre::FogMode mode;
			
			if(actualScene.get_environment().get_fog().get_mode() == "linear")		mode = Ogre::FOG_LINEAR;//maybe the only exported value from blender. not sure what other exporters produce!!!
            else if(actualScene.get_environment().get_fog().get_mode() == "exp")	mode = Ogre::FOG_EXP;	//it seems, that the blender exports not this value, so this string "exp" is safe!!!
            else if(actualScene.get_environment().get_fog().get_mode() == "exp2")	mode = Ogre::FOG_EXP2;	//it seems, that the blender exports not this value, so this string "exp2" is safe!!!
			else if(actualScene.get_environment().get_fog().get_mode() == "none")	mode = Ogre::FOG_NONE;	//it seems, that the blender exports not this value, so this string "none" is safe!!!

			this->Mgr->setFog(mode, Ogre::ColourValue(
				actualScene.get_environment().get_fog().get_colourDiffuse().get_r(), 
				actualScene.get_environment().get_fog().get_colourDiffuse().get_g(),
				actualScene.get_environment().get_fog().get_colourDiffuse().get_b()),
                1.0f, //maybe 1.0 is the neutal value? This value is not delivered by blender-exporter or dotScene-format!!!
                actualScene.get_environment().get_fog().get_linearStart(),
                actualScene.get_environment().get_fog().get_linearEnd());
        }
		catch(std::exception e)
		{
			;// Just catch any exceptions like null reference exceptions
		}
    }
*//*
    return true;
}
*/

bool dotSceneAdvanced::dotSceneAttachFactory::attachSingleDOMSceneTo(	std::string uniqueSceneName,
																		std::string attachToNodeWithThisName)
{
	std::string LogMsg;
	std::string dotSceneVersionString;

	LogMsg = "SCENE FACTORY: Attaching scene \"" + uniqueSceneName + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);

	// If list ist empty...
	if (this->DOMScenes.empty())
	{
		LogMsg = "SCENE FACTORY: No scenes are registed. Aborted!";
		Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_CRITICAL);
		return false;
	}

	// If list doesn't contain "uniqueSceneName"...
	if (this->DOMScenes.count(uniqueSceneName) == 0)
	{
		// If DOMScenes is a "map", count equals 0 or greather.
		// If DOMScenes is a "hash_map", count equals 0 or 1.
		// So criteria is valid in both cases.
		LogMsg = "SCENE FACTORY: Scene \"" + uniqueSceneName + "\" is not registed. Aborted!";
		Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_CRITICAL);
		return false;
	}
	
	// Store external anchor node...
	this->ExternalAnchorNode = this->Mgr->getSceneNode(Ogre::String(attachToNodeWithThisName));

	// Create Ogre::String, describing the actual location of file
	Ogre::String actualLocationOfMaterialFiles = Ogre::String(this->LocationsOfMaterialFiles[uniqueSceneName]);

	// Generate unique new root SceneNode - Part 1
    // Find a unique name...
    int rootNodeNameModificationCounter = 0;
	char valueAsString[20];
	Ogre::String rootNodeNameToApply = attachToNodeWithThisName + "_SceneRoot";		
	while (this->Mgr->hasSceneNode(rootNodeNameToApply))
    {
        rootNodeNameToApply = attachToNodeWithThisName + "_SceneRoot_";
		sprintf(valueAsString, "%i", rootNodeNameModificationCounter);  // TODO: use wx command here
		rootNodeNameToApply = rootNodeNameToApply + valueAsString;
        rootNodeNameModificationCounter++;
    }
	
	// Generate unique new root SceneNode - Part 2
	// It is used for light- and camera-setup, because lights and cams working with world-coordinates
	this->_AttachRootNode = this->ExternalAnchorNode->createChildSceneNode(Ogre::String(rootNodeNameToApply));
	LogMsg = "SCENE FACTORY: Created scene's rootNode: \"" + rootNodeNameToApply + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);

	// * * * * * * * * Setup Interpretation (STEP 0) * * * * * * * * *                 
	xercesc::DOMDocument *DOMDocument_dotScene = this->DOMScenes.find(uniqueSceneName)->second;
	xercesc::DOMElement *DOMElement_scene = DOMDocument_dotScene->getDocumentElement();

	xercesc::DOMNodeList *ChildElements;

	xercesc::DOMElement *DOMElement_nodes = 0;
	xercesc::DOMElement *DOMElement_externals = 0;
	xercesc::DOMElement *DOMElement_environment = 0;

	// Check format version (!)
	if (DOMElement_scene->hasAttribute(XMLString::transcode("formatVersion")))
	{
		dotSceneVersionString = XMLString::transcode(DOMElement_scene->getAttribute(XMLString::transcode("formatVersion")));
		LogMsg = "SCENE FACTORY: Identified version of dotScene-format as \"" + dotSceneVersionString + "\"";
		Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);
	}
	else
	{
		LogMsg = "SCENE FACTORY: Couldn't identify version of dotScene-format! Using default version: 1.0.0 (OViSE)";
		dotSceneVersionString = "1.0.0";
		Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_CRITICAL);
	}

	// Get elements "nodes", "externals" and "environment"
	ChildElements = DOMElement_scene->getElementsByTagName(XMLString::transcode("nodes"));
	if (ChildElements->getLength() > 0)
	{
		DOMElement_nodes = (xercesc::DOMElement*) ChildElements->item(0);
	}

	ChildElements = DOMElement_scene->getElementsByTagName(XMLString::transcode("externals"));
	if (ChildElements->getLength() > 0)
	{
		DOMElement_externals = (xercesc::DOMElement*) ChildElements->item(0);
	}

	ChildElements = DOMElement_scene->getElementsByTagName(XMLString::transcode("environment"));
	if (ChildElements->getLength() > 0)
	{
		DOMElement_environment = (xercesc::DOMElement*) ChildElements->item(0);
	}




	// * * * * * * * * Interpretation (STEP 1): Externals * * * * * * * * *
	// COMMENT: It's important, that externals are done before proceeding with nodes and environment.
	//          Necessary materials must be loaded before nodes need 'em.

	// STEP 1: Optional add materials, if "this->doAttachExternals" is true...
    if (this->doAttachExternals && (DOMElement_externals != 0))
    {
		// STEP 1.1: Factory owned ResourceGroup, when it exists.
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(Ogre::String(this->get_NameOfFactoryOwnedResourceGroup()));

		// STEP 1.2: Add path of dotScene-File to own recourcegroup
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::String(this->LocationsOfMeshFiles[uniqueSceneName]), Ogre::String("FileSystem"), this->get_NameOfFactoryOwnedResourceGroup(), false); 

		// STEP 1.3: Identify format version of dotScene:
		bool match = false;
		if ((!match) && (dotSceneVersionString == "1.0.0"))
		{
			// STEP 1.4: Handle externals...
			this->v1_0_0_Interpretation_Externals(DOMElement_externals, uniqueSceneName);
			match = true;
		}

		// IMPORTANT: Other interpretation-methods can be added here for different dotScene-versions
		// if (!match) && (dotSceneVersionString == " ... ")) { ... }

		// STEP 1.5: Again, initialise ResourceGroup "Material".
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->get_NameOfFactoryOwnedResourceGroup());
	}
	

	// * * * * * * * * Interpretation (STEP 2): Nodes (Entities, Cams, Lights) * * * * * * * * *
	// STEP 2: Optional add nodes, if "this->doAttachNodes" is true...
	if (this->doAttachNodes && (DOMElement_nodes != 0))
    {
		// STEP 2.1: Identify format version of dotScene:
		bool match = false;
		if ((!match) && (dotSceneVersionString == "1.0.0"))
		{
			// STEP 2.2: Handle nodes...
			this->v1_0_0_Interpretation_Nodes(DOMElement_nodes);
			match = true;
		}

		// IMPORTANT: Other interpretation-methods can be added here for different dotScene-versions
		// if (!match) && (dotSceneVersionString == " ... ")) { ... }
    }

/*
	// * * * * * * * * Interpretation (STEP 2): Nodes (Entities, Cams, Lights) * * * * * * * * *
    if (this->doAttachNodes)
    {
    	Ogre::LogManager::getSingletonPtr()->logMessage("Attaching nodes...");
		recursiveNodeCreator(actualScene.get_Nodes()._ListOfNodes, this->_AttachRootNode, uniqueSceneName);
    }
/*
	// Subsection of interpretation: Environment <-- ATTENTION, malfunction source...because dotScene-format and blenderexporter aren't fully compatible to ogre (?) 
    if (this->doAttachEnvironment)
    {
        // Set up background-colour
        try // if (actualScene.get_environment().get_colourBackground() != null)
        {
			this->Mgr->setAmbientLight(Ogre::ColourValue(
                actualScene.get_environment().get_colourBackground().get_r(),
                actualScene.get_environment().get_colourBackground().get_g(),
                actualScene.get_environment().get_colourBackground().get_b()));
        }
		catch(std::exception e)
		{
			;// Just catch any exceptions like null reference exceptions
		}

        // Set up ambient-colour
            // until now, nothing happens!
            // no corrspondig value in SceneMgr for background-colour?!

        // Set up fog
		try // if (actualScene.get_environment().get_fog() != null)
		{
            // Select fog-mode
			Ogre::FogMode mode;
			
			if(actualScene.get_environment().get_fog().get_mode() == "linear")		mode = Ogre::FOG_LINEAR;//maybe the only exported value from blender. not sure what other exporters produce!!!
            else if(actualScene.get_environment().get_fog().get_mode() == "exp")	mode = Ogre::FOG_EXP;	//it seems, that the blender exports not this value, so this string "exp" is safe!!!
            else if(actualScene.get_environment().get_fog().get_mode() == "exp2")	mode = Ogre::FOG_EXP2;	//it seems, that the blender exports not this value, so this string "exp2" is safe!!!
			else if(actualScene.get_environment().get_fog().get_mode() == "none")	mode = Ogre::FOG_NONE;	//it seems, that the blender exports not this value, so this string "none" is safe!!!

			this->Mgr->setFog(mode, Ogre::ColourValue(
				actualScene.get_environment().get_fog().get_colourDiffuse().get_r(), 
				actualScene.get_environment().get_fog().get_colourDiffuse().get_g(),
				actualScene.get_environment().get_fog().get_colourDiffuse().get_b()),
                1.0f, //maybe 1.0 is the neutal value? This value is not delivered by blender-exporter or dotScene-format!!!
                actualScene.get_environment().get_fog().get_linearStart(),
                actualScene.get_environment().get_fog().get_linearEnd());
        }
		catch(std::exception e)
		{
			;// Just catch any exceptions like null reference exceptions
		}
    }
*/


	// * * * * * * * * Interpretation (STEP X): Apply factory's Offset-settings to scene's rootnode * * * * * * * * *
    // Rotate entire scene with factory-settings for ROLL, PITCH, YAW
	this->_AttachRootNode->pitch(Ogre::Radian(this->get_PitchOfEntireScene()), Ogre::Node::TS_WORLD);
    this->_AttachRootNode->yaw(Ogre::Radian(this->get_YawOfEntireScene()), Ogre::Node::TS_WORLD);
	this->_AttachRootNode->roll(Ogre::Radian(this->get_RollOfEntireScene()), Ogre::Node::TS_WORLD);
	LogMsg = "SCENE FACTORY: Rotated rootNode with factory-settings.";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_TRIVIAL);

    // Scale rootnode
	this->_AttachRootNode->scale((float)this->get_ScaleOffset(), (float)this->get_ScaleOffset(), (float)this->get_ScaleOffset());
	LogMsg = "SCENE FACTORY: Scaled rootNode with factory-settings.";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_TRIVIAL);

    return true;
}

/* IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
   IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
   IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
void dotSceneAdvanced::dotSceneAttachFactory::recursiveNodeCreator(	std::list<dotSceneNode> actualNodeList,
																	Ogre::SceneNode* attachParentNode,
																	std::string uniqueSceneName)
{	
	using namespace dotSceneObjects;
	std::list<dotSceneNode>::const_iterator actualNodeListIterator;

	if (!actualNodeList.empty())
	{
		actualNodeListIterator = actualNodeList.begin();

		do
		{		
			dotSceneObjects::dotSceneNode actualNodeFromXML = *actualNodeListIterator;
			
            // Generate needed parameters from dotSceneObjects, with are relative to "attachRootNode"
            // Remember: "RelativeToRoot" means the transformingspace TS_PARENT!
			Ogre::Vector3 nodeScaleRalativeToRoot = Ogre::Vector3(
				actualNodeFromXML.get_Scale().get_x(), 
                actualNodeFromXML.get_Scale().get_y(), 
                actualNodeFromXML.get_Scale().get_z());
				
            Ogre::Vector3 nodeTranslationRelativeToRoot = Ogre::Vector3(
				actualNodeFromXML.get_Position().get_x(), 
                actualNodeFromXML.get_Position().get_y(), 
                actualNodeFromXML.get_Position().get_z());

            Ogre::Quaternion nodeRotationRelativeToRoot = Ogre::Quaternion(
				actualNodeFromXML.get_Orientation().get_Quaternion().get_qw(),
                actualNodeFromXML.get_Orientation().get_Quaternion().get_qx(), 
                actualNodeFromXML.get_Orientation().get_Quaternion().get_qy(), 
                actualNodeFromXML.get_Orientation().get_Quaternion().get_qz());
			
            // Generate unique new SceneNode and apply relative parameters
            // Find a unique name
            int nodeNameModificationCounter = 0;
			char valueNodeCounterAsString[20];
			Ogre::String nodeNameToApply = actualNodeFromXML.get_name();
            while(this->Mgr->hasSceneNode(nodeNameToApply))
            {
				nodeNameToApply = actualNodeFromXML.get_name();
				nodeNameToApply = nodeNameToApply + "_";
				sprintf(valueNodeCounterAsString, "%i", nodeNameModificationCounter);
				nodeNameToApply = nodeNameToApply + valueNodeCounterAsString;
                nodeNameModificationCounter++;
            }

            // Create new SceneNode
			Ogre::SceneNode* actualNode = this->Mgr->getSceneNode(attachParentNode->getName())->createChildSceneNode(nodeNameToApply);
				
            // Apply relative parameters
			actualNode->scale(nodeScaleRalativeToRoot);
			actualNode->rotate(nodeRotationRelativeToRoot, Ogre::Node::TS_PARENT);                    
			actualNode->translate(nodeTranslationRelativeToRoot, Ogre::Node::TS_PARENT);

            // Special: apply factorys position-offset
			actualNode->translate(this->get_PositionOffset(), Ogre::Node::TS_WORLD);

            // look up for node-specifics
            //defined normalVector is used only for light and camera setup.
			Ogre::Vector3 normalVector;

			char valueAsString[20];

			Ogre::Entity* actualEntity;
			Ogre::String entityNameToApply;
			dotSceneObjects::dotSceneEntity formatedToDotSceneEntity;
			int entityNameModificationCounter;

			//Ogre::Light* actualLight; // not referenced
			Ogre::String lightNameToApply;
			//dotSceneObjects::dotSceneLight* formatedToDotSceneLight; // not referenced
			//int lightNameModificationCounter; // not referenced

			//Ogre::Camera* actualCamera; // not referenced
			Ogre::String cameraNameToApply;
			//dotSceneObjects::dotSceneCamera* formatedToDotSceneCamera; // not referenced
			//int cameraNameModificationCounter; // not referenced

			// UNSOLVED. Ignore consistancy for a quick solution, H.R. 12.02.2009
			dotSceneEnums::dotSceneElementTags Decider;
			if (actualNodeFromXML.HasEntity()) Decider = dotSceneEnums::entity;
			else Decider = dotSceneEnums::INVALID;

			dotSceneEntity Test;
			std::string buff = "";
			// CONTINUE with modified premises...
			switch (Decider) // <---- CHEATED LINE
			{
				case dotSceneEnums::entity: // if node is an entity (mesh-structure)
					
					// <-- CHEATED LINES, expect only one entitiy...
					formatedToDotSceneEntity = *actualNodeFromXML._ListOfEntities.begin();
                    
					// Generate unique new entity
                    entityNameModificationCounter = 0;
					
					entityNameToApply = formatedToDotSceneEntity.get_name();
                    while(this->Mgr->hasEntity(entityNameToApply))
                    {
                        entityNameToApply = formatedToDotSceneEntity.get_name();
                        entityNameToApply = entityNameToApply + "_";
						sprintf(valueAsString, "%i", entityNameModificationCounter);
						entityNameToApply = entityNameToApply + valueAsString;
                        entityNameModificationCounter++;
                    }

					// Create new Entity
					// TODO: ".get_meshFile()" can grab into the "void" -> throws an Exception!!!!!!!!
					
					buff = this->LocationsOfMeshFiles[uniqueSceneName] + formatedToDotSceneEntity.get_meshFile();
					try
					{
					actualEntity = this->Mgr->createEntity(entityNameToApply, buff);		
					}
					catch(Ogre::Exception e)
					{
						Ogre::String test = e.getDescription();
					}
					// Note: this changed in Ogre 1.6, it is now a functionality of the scene manager
                    //actualEntity->setNormaliseNormals(true);
                    actualEntity->setCastShadows(true);
                    actualNode->attachObject(actualEntity);                                               

                    break;
				/*	
                case light: // if node is a light-source
                                
                    formatedToDotSceneLight = (dotSceneObjects::dotSceneLight*)actualNodeFromXML.get_specific();
                    
					// Generate unique new light
                    lightNameModificationCounter = 0;
					lightNameToApply = formatedToDotSceneLight->get_name();
                    while(this->Mgr->hasEntity(lightNameToApply))
                    {
						lightNameToApply = formatedToDotSceneLight->get_name();
                        lightNameToApply = lightNameToApply + "_";
						sprintf(valueAsString, "%i", lightNameModificationCounter);
						lightNameToApply = lightNameToApply + valueAsString;
                        lightNameModificationCounter++;
                    }

                    // Create new Light
                    actualLight = this->Mgr->createLight(lightNameToApply);

                    // Set light-type, default is LT_POINT
					if ((formatedToDotSceneLight->get_type() == "point")) actualLight->setType(Ogre::Light::LT_POINT);
					else if ((formatedToDotSceneLight->get_type() == "spotLight")) actualLight->setType(Ogre::Light::LT_SPOTLIGHT);
					else if ((formatedToDotSceneLight->get_type() == "directional")) actualLight->setType(Ogre::Light::LT_DIRECTIONAL);
					else actualLight->setType(Ogre::Light::LT_POINT);
                    
					// Set position
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // Create absolute position-vector for light:                          *
                    //      absolute = translation-base + ((rotation * relative) * scale)) *
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // Determine relative position of light to "deliverdExternalRootNode"

                    // Rotate actual light-position with factory-settings for ROLL, PITCH, YAW
					actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_PitchOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_X) * actualNode->getPosition());
                    actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_YawOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_Y) * actualNode->getPosition());
                    actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_RollOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_Z) * actualNode->getPosition());
                    
                    // Apply global scale and set absolute Position of the new light-source
                    actualLight->setPosition(
                        (this->deliverdExternalRootNode->getPosition().x + (actualNode->getPosition().x * this->get_ScaleOffset())),
                        (this->deliverdExternalRootNode->getPosition().y + (actualNode->getPosition().y * this->get_ScaleOffset())),
                        (this->deliverdExternalRootNode->getPosition().z + (actualNode->getPosition().z * this->get_ScaleOffset())));
                
                    // Set direction
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // * dotScene.dtd (.xsd) defines light direction by a quaternion, aimed to an implicid *
                    // * vector with x = 0, y = 0, z = -1                                                  *
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
					normalVector = Ogre::Vector3(0.0, 0.0, -1.0);

                    // Rotate actual light direction with factory-settings for ROLL, PITCH, YAW
                    // Effects of global Y, P, R
					actualNode->pitch(Ogre::Radian(this->get_PitchOfEntireScene()), Ogre::Node::TS_WORLD);
                    actualNode->yaw(Ogre::Radian(this->get_YawOfEntireScene()), Ogre::Node::TS_WORLD);
                    actualNode->roll(Ogre::Radian(this->get_RollOfEntireScene()), Ogre::Node::TS_WORLD);

                    //multiply with final direction of "actualNode"
					normalVector = Ogre::Quaternion(actualNode->getOrientation().w, actualNode->getOrientation().x, actualNode->getOrientation().y, actualNode->getOrientation().z) * normalVector;

                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // * The factor "(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset)"        *
                    // * is used, because light fades out too fast. Maybe that's only a problem with             *
                    // * blemder-imports. That's not tested.                                                     *
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    actualLight->setDirection(
                        actualLight->getPosition().x + normalVector.x * (formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset()) * this->get_ScaleOffset(),
                        actualLight->getPosition().y + normalVector.y * (formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset()) * this->get_ScaleOffset(),
                        actualLight->getPosition().z + normalVector.z * (formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset()) * this->get_ScaleOffset());

                    // Set specular & diffuse colour
                    actualLight->setDiffuseColour(
						formatedToDotSceneLight->get_colourDiffuse().get_r(),
                        formatedToDotSceneLight->get_colourDiffuse().get_g(),
                        formatedToDotSceneLight->get_colourDiffuse().get_b());                   
                    actualLight->setSpecularColour(
						formatedToDotSceneLight->get_colourSpecular().get_r(),
                        formatedToDotSceneLight->get_colourSpecular().get_g(),
                        formatedToDotSceneLight->get_colourSpecular().get_b());                
                    actualLight->setSpecularColour(0.0f, 0.0f, 0.0f);
					
					
                    // Set attenuation, if light-type is LT_SPOT or LT_POINT
                    if ((actualLight->getType() == Ogre::Light::LT_SPOTLIGHT) || (actualLight->getType() == Ogre::Light::LT_POINT))
                    {
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * ATTENTION & REMEMBER:                               *
                        // * formatedToDotSceneLight.lightAttenuation.range      *
                        // * is not the "half-distance" from Blender. It is the  *
                        // * "max. clipping distance" value.                     *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        actualLight->setAttenuation(
							(formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset()),
                            (formatedToDotSceneLight->get_lightAttenuation().get_constant()),
                            (formatedToDotSceneLight->get_lightAttenuation().get_linear() / (formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset())),                                            
                            (formatedToDotSceneLight->get_lightAttenuation().get_quadratic() / (formatedToDotSceneLight->get_lightAttenuation().get_range() * this->get_ScaleOffset() * this->get_ScaleOffset())));
                            //^-- square, because as names say it's a quadratic formula
                    }

                    // Set spotlight range        
                    if (actualLight->getType() ==  Ogre::Light::LT_SPOTLIGHT)
                        actualLight->setSpotlightRange(
							Ogre::Radian(formatedToDotSceneLight->get_lightRange().get_inner()),
                            Ogre::Radian(formatedToDotSceneLight->get_lightRange().get_outer()),
                            formatedToDotSceneLight->get_lightRange().get_falloff());

                    break;
					
                case camera: // if node is a camera
					
                    formatedToDotSceneCamera = (dotSceneObjects::dotSceneCamera*)actualNodeFromXML.get_specific();
                    
					// Generate unique new camera
                    cameraNameModificationCounter = 0;
                    cameraNameToApply = formatedToDotSceneCamera->get_name();
                    while (this->Mgr->hasCamera(cameraNameToApply))
                    {
						cameraNameToApply = formatedToDotSceneCamera->get_name();
                        cameraNameToApply = cameraNameToApply + "_";
						sprintf(valueAsString, "%i", cameraNameModificationCounter);
						cameraNameToApply = cameraNameToApply + valueAsString;
                        cameraNameModificationCounter++;
                    }

					// Create new Camera
					actualCamera = this->Mgr->createCamera(cameraNameToApply);

					// Set position
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // Create absolute position-vector for light:                          *
                    //      absolute = translation-base + ((rotation * relative) * scale)) *
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // Determine relative position of light to "deliverdExternalRootNode"

                    // Rotate actual light-position with factory-settings for ROLL, PITCH, YAW
					actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_PitchOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_X) * actualNode->getPosition());
                    actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_YawOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_Y) * actualNode->getPosition());
                    actualNode->setPosition(Ogre::Quaternion(Ogre::Radian(this->get_RollOfEntireScene().valueRadians()), Ogre::Vector3::UNIT_Z) * actualNode->getPosition());

                    // Apply global scale and set absolute Position of the new camera
                    actualCamera->setPosition(
                        (this->deliverdExternalRootNode->getPosition().x + (actualNode->getPosition().x * this->get_ScaleOffset())),
                        (this->deliverdExternalRootNode->getPosition().y + (actualNode->getPosition().y * this->get_ScaleOffset())),
                        (this->deliverdExternalRootNode->getPosition().z + (actualNode->getPosition().z * this->get_ScaleOffset())));

					// Direction of camera
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    // * dotScene.dtd (.xsd) defines camera direction by a quaternion, aimed to an implicid *
                    // * vector with x = 0, y = 0, z = -1                                                  *
                    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
					normalVector = Ogre::Vector3(0.0, 0.0, -1.0);

					// Rotate actual camera direction with factory-settings for ROLL, PITCH, YAW
                    // Effects of global Y, P, R
					actualNode->pitch(Ogre::Radian(this->get_PitchOfEntireScene()), Ogre::Node::TS_WORLD);
                    actualNode->yaw(Ogre::Radian(this->get_YawOfEntireScene()), Ogre::Node::TS_WORLD);
                    actualNode->roll(Ogre::Radian(this->get_RollOfEntireScene()), Ogre::Node::TS_WORLD);

					//multiply with final direction of "actualNode"
					normalVector = Ogre::Quaternion(actualNode->getOrientation().w, actualNode->getOrientation().x, actualNode->getOrientation().y, actualNode->getOrientation().z) * normalVector;

					// Set final direction
                    actualCamera->setDirection(
                        actualCamera->getPosition().x + normalVector.x * this->get_ScaleOffset(),
                        actualCamera->getPosition().y + normalVector.y * this->get_ScaleOffset(),
                        actualCamera->getPosition().z + normalVector.z * this->get_ScaleOffset());

                    // Set FOV (Field Of View)             
					actualCamera->setFOVy(Ogre::Radian(formatedToDotSceneCamera->get_fov()));

                    // Set projectionType
					if (formatedToDotSceneCamera->get_projectionType() == "orthographic") actualCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
					else if (formatedToDotSceneCamera->get_projectionType() == "orthographic") actualCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
					else actualCamera->setProjectionType(Ogre::PT_PERSPECTIVE);

                    // Set clipping
					try
					{
						actualCamera->setNearClipDistance(formatedToDotSceneCamera->get_clipping().get_nearPlaneDist() * this->get_ScaleOffset());
						actualCamera->setFarClipDistance(formatedToDotSceneCamera->get_clipping().get_farPlaneDist() * this->get_ScaleOffset());
					}
					catch (exception)
					{ 
						// it's possible that clipping doesn't exists in formatedToDotSceneCamera -> do nothing						
					}
                    break;
				
                default: // If node has no specifics (for example a invisible anchor-node)
					break;
			}
			
			// Recursive call for childnode structures
			recursiveNodeCreator(actualNodeFromXML._ListOfChildNodes, actualNode, uniqueSceneName);
			
			actualNodeListIterator++;
		}while(actualNodeListIterator != (actualNodeList.end()));
	}
}
*/


/*
/// <summary>
/// Use this method, to deploy any scenes into your ogre-world, which blue prints are in factorys storage.
/// </summary>
/// <param name="attachToNodeWithThisName">Mogre.SceneNode, which should be used as zero point of origin of scenes.</param>
/// <param name="doAttachNodes">Sets explicid the "doAttachNodes" factory configuration parameter.</param>
/// <param name="doAttachExternals">Sets explicid the "doAttachExternals" factory configuration parameter.</param>
/// <param name="doAttachEnvironment">Sets explicid the "doAttachEnvironment" factory configuration parameter.</param>
/// <param name="isBlenderImport">Sets explicid the "BlenderImport" factory configuration parameter.</param>
/// <returns>Returns "true", when process was successful. If not, it returns "false". For example, when "uniqueSceneName" is unknown.</returns>
public bool attachAllScenesTo(  string attachToNodeWithThisName,
                                bool doAttachNodes,
                                bool doAttachExternals,
                                bool doAttachEnvironment,
                                bool isBlenderImport)
{
    this.doAttachNodes = doAttachNodes;
    this.doAttachExternals = doAttachExternals;
    this.doAttachEnvironment = doAttachEnvironment;
    this.BlenderImport = isBlenderImport;

    return this.attachAllScenesTo(attachToNodeWithThisName);
}*/

/*
/// <summary>
/// Use this method, to deploy any scenes into your ogre-world, which blue prints are in factorys storage.
/// </summary>
/// <param name="attachToNodeWithThisName">Mogre.SceneNode, which should be used as zero point of origin of all scenes.</param>
/// <returns>Returns "true", when process was successful. If not, it returns "false". For example, when "uniqueSceneName" is unknown.</returns>
public bool attachAllScenesTo(  string attachToNodeWithThisName)
{
    #region check for objects-problems or check saveable time. do setup.

    //save time, if list ist empty
    if (Scenes.Count == 0) return true;

    //store RootNode for attach-process
    this.attachRootNode = this.mgr.GetSceneNode(attachToNodeWithThisName);

    #region rotate entire scene with factory-sttings for ROLL, PITCH, YAW

    this.attachRootNode.Pitch(new Radian(this.PitchOfEntireScene), Node.TransformSpace.TS_WORLD);
    this.attachRootNode.Yaw(new Radian(this.YawOfEntireScene), Node.TransformSpace.TS_WORLD);
    this.attachRootNode.Roll(new Radian(this.RollOfEntireScene), Node.TransformSpace.TS_WORLD);

    #endregion
    #endregion
    #region scale rootnode

    this.attachRootNode.Scale((float)this.ScaleOffset, (float)this.ScaleOffset, (float)this.ScaleOffset);

    #endregion
    #region complete interpretation of data-objects

    IDictionaryEnumerator sceneEnumerator = Scenes.GetEnumerator();

    while(sceneEnumerator.MoveNext())
    {
        dotScene actualScene = (dotScene)sceneEnumerator.Value;
        string actualLocationOfMeshFiles = (string)this.LocationsOfMeshFiles[sceneEnumerator.Key];
        string actualLocationOfMaterialFile = (string)this.LocationsOfMaterialFiles[sceneEnumerator.Key];

        #region subsection: externals-interpretation

        if (this.doAttachExternals)
        {                  
            //Register new used .material-File factory-internal 
            foreach (dotSceneItem itemFromXML in actualScene.externals.items)
            {
                switch (itemFromXML.type)
                {
                    case "material":
                        try
                        {                                    
                            //Clear ResourceGroup, when it exists.
                            ResourceGroupManager.Singleton.ClearResourceGroup(NameOfFactoryOwnedMaterialResourceGroup);

                            ResourceGroupManager.Singleton.AddResourceLocation(actualLocationOfMaterialFile, "FileSystem", NameOfFactoryOwnedMaterialResourceGroup, false);

                            //Again, initialise ResourceGroup "Material"
                            ResourceGroupManager.Singleton.InitialiseResourceGroup(NameOfFactoryOwnedMaterialResourceGroup);                           
                        }
                        catch 
                        {
                            if (Mogre.OgreException.IsThrown)
                            {
                                if (Mogre.OgreException.LastException.Number == OgreException.ExceptionCodes.ERR_DUPLICATE_ITEM)
                                    //When "ERR_DUPLICATE_ITEM" occurs: ignore the exception.
                                    //Dont worry, no bad entries 'll be made into RessourceGroupManager.
                                    ;
                                else throw;
                            }
                            else throw;
                        }
                        break;
                    //Other cases could be more comlex. That's why this structure has be choosen.
                    default: break;
                }
            }
        }

        #endregion
        #region subsection: node-interpretation

        if (this.doAttachNodes)
        {
            foreach (dotSceneNode nodeFromXML in actualScene.nodes.nodes)
            {
                #region Generate needed parameters from dotSceneObjects, with are relative to "attachRootNode"

                //Remember: "RelativeToRoot" means the TS_PARENT -transformingspace!
                Mogre.Vector3 nodeScaleRalativeToRoot = new Vector3(
                    (float)nodeFromXML.scale.x,
                    (float)nodeFromXML.scale.y,
                    (float)nodeFromXML.scale.z);
                Mogre.Vector3 nodeTranslationRelativeToRoot = new Vector3(
                    (float)nodeFromXML.position.x,
                    (float)nodeFromXML.position.y,
                    (float)nodeFromXML.position.z);
                Mogre.Quaternion nodeRotationRelativeToRoot = new Quaternion(
                    (float)nodeFromXML.quaternion.qw,
                    (float)nodeFromXML.quaternion.qx,
                    (float)nodeFromXML.quaternion.qy,
                    (float)nodeFromXML.quaternion.qz);

                #endregion
                #region Generate unique new SceneNode and apply relative parameters

                //Find a unique name
                int nodeNameModificationCounter = 0;
                string nodeNameToApply = nodeFromXML.name;
                while (this.mgr.HasSceneNode(nodeNameToApply))
                {
                    nodeNameToApply = nodeFromXML.name;
                    nodeNameToApply = nodeNameToApply + "_" + nodeNameModificationCounter.ToString();
                    nodeNameModificationCounter++;
                }

                //Create new SceneNode
                SceneNode actualNode = this.mgr.GetSceneNode(this.attachRootNode.Name).CreateChildSceneNode(nodeNameToApply);

                //Apply relative parameters
                actualNode.Scale(nodeScaleRalativeToRoot);
                actualNode.Rotate(nodeRotationRelativeToRoot, Node.TransformSpace.TS_PARENT);
                actualNode.Translate(nodeTranslationRelativeToRoot, Node.TransformSpace.TS_PARENT);

                //special: apply factorys position-offset
                actualNode.Translate(this.PositionOffset, Node.TransformSpace.TS_WORLD);
                #endregion
                #region look up for node-specifics

                //defined normalVector is used only for light and camera setup.
                Mogre.Vector3 normalVector;

                switch (nodeFromXML.specific.NameSymbol)
                {
                    case dotSceneElementTags.entity:
                        #region if node is an entity (mesh-structure)

                        dotSceneEntity formatedToDotSceneEntity = (dotSceneEntity)nodeFromXML.specific;
                        #region generate unique new entity

                        int entityNameModificationCounter = 0;
                        string entityNameToApply = formatedToDotSceneEntity.name;
                        while (this.mgr.HasEntity(entityNameToApply))
                        {
                            entityNameToApply = formatedToDotSceneEntity.name;
                            entityNameToApply = entityNameToApply + "_" + entityNameModificationCounter.ToString();
                            entityNameModificationCounter++;
                        }

                        Mogre.Entity actualEntity = this.mgr.CreateEntity(entityNameToApply, actualLocationOfMeshFiles + formatedToDotSceneEntity.meshFile);

                        #endregion
                        actualEntity.NormaliseNormals = true;
                        actualEntity.CastShadows = true;
                        actualNode.AttachObject(actualEntity);

                        #endregion
                        break;
                    case dotSceneElementTags.light:
                        #region if node is a light-source

                        dotSceneLight formatedToDotSceneLight = (dotSceneLight)nodeFromXML.specific;
                        #region generate unique new light

                        //Find a unique name
                        int lightNameModificationCounter = 0;
                        string lightNameToApply = formatedToDotSceneLight.name;

                        while (this.mgr.HasLight(lightNameToApply))
                        {
                            lightNameToApply = formatedToDotSceneLight.name;
                            lightNameToApply = lightNameToApply + "_" + lightNameModificationCounter.ToString();
                            lightNameModificationCounter++;
                        }

                        //Create new Light
                        Mogre.Light actualLight = this.mgr.CreateLight(lightNameToApply);

                        #endregion
                        #region set light-type, default is LT_POINT

                        switch (formatedToDotSceneLight.type)
                        {
                            case "point":
                                actualLight.Type = Light.LightTypes.LT_POINT;
                                break;
                            case "spotLight":
                                actualLight.Type = Light.LightTypes.LT_SPOTLIGHT;
                                break;
                            case "directional":
                                actualLight.Type = Light.LightTypes.LT_DIRECTIONAL;
                                break;
                            default:
                                actualLight.Type = Light.LightTypes.LT_POINT;
                                break;
                        }
                        #endregion
                        #region set position
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
						// * Create absolute position-vector for light:                          *
						// *      absolute = translation-base + ((rotation * relative) * scale)) *
						// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        #region Determine relative position of light to "deliverdExternalRootNode"


                        //rotate actual light-position with factory-settings for ROLL, PITCH, YAW
                        actualNode.Position = new Quaternion(this.PitchOfEntireScene.ValueRadians, Vector3.UNIT_X) * actualNode.Position;
                        actualNode.Position = new Quaternion(this.YawOfEntireScene.ValueRadians, Vector3.UNIT_Y) * actualNode.Position;
                        actualNode.Position = new Quaternion(this.RollOfEntireScene.ValueRadians, Vector3.UNIT_Z) * actualNode.Position;

                        #endregion
                        #region Apply global scale and set absolute Position of the new light-source

                        actualLight.SetPosition(
                            (float)(this.deliverdExternalRootNode.Position.x + (float)(actualNode.Position.x * this.ScaleOffset)),
                            (float)(this.deliverdExternalRootNode.Position.y + (float)(actualNode.Position.y * this.ScaleOffset)),
                            (float)(this.deliverdExternalRootNode.Position.z + (float)(actualNode.Position.z * this.ScaleOffset)));
                        #endregion

                        #endregion
                        #region set direction
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * dotScene.dtd (.xsd) defines light direction by a quaternion, aimed to an implicid *
                        // * vector with x = 0, y = 0, z = -1                                                  *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        normalVector = new Vector3(0f, 0f, -1f);

                        #region rotate actual light direction with factory-settings for ROLL, PITCH, YAW

                        //effects of global Y, P, R
                        actualNode.Pitch(new Radian(this.PitchOfEntireScene), Node.TransformSpace.TS_WORLD);
                        actualNode.Yaw(new Radian(this.YawOfEntireScene), Node.TransformSpace.TS_WORLD);
                        actualNode.Roll(new Radian(this.RollOfEntireScene), Node.TransformSpace.TS_WORLD);

                        //multiply with final direction of "actualNode"
                        normalVector = new Quaternion(actualNode.Orientation.w, actualNode.Orientation.x, actualNode.Orientation.y, actualNode.Orientation.z) * normalVector;

                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * The factor "(float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset)" *
                        // * is used, because light fades out too fast. Maybe that's only a problem with             *
                        // * blemder-imports. That's not tested.                                                     *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        actualLight.SetDirection(
                            actualLight.Position.x + normalVector.x * (float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset) * (float)this.ScaleOffset,
                            actualLight.Position.y + normalVector.y * (float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset) * (float)this.ScaleOffset,
                            actualLight.Position.z + normalVector.z * (float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset) * (float)this.ScaleOffset);
                        #endregion

                        #endregion
                        #region set specular & diffuse colour

                        actualLight.SetDiffuseColour((float)formatedToDotSceneLight.colourDiffuse.r,
                            (float)formatedToDotSceneLight.colourDiffuse.g,
                            (float)formatedToDotSceneLight.colourDiffuse.b);

                        actualLight.SetSpecularColour((float)formatedToDotSceneLight.colourSpecular.r,
                            (float)formatedToDotSceneLight.colourSpecular.g,
                            (float)formatedToDotSceneLight.colourSpecular.b);

                        actualLight.SetSpecularColour(0.0f, 0.0f, 0.0f);
                        #endregion
                        #region set attenuation, if light-type is LT_SPOT or LT_POINT //<-- clean up

                        if (formatedToDotSceneLight.lightAttenuation != null)
                        {
                            if ((actualLight.Type == Light.LightTypes.LT_SPOTLIGHT) || (actualLight.Type == Light.LightTypes.LT_POINT))
                            {
                                // * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                // * ATTENTION & REMEMBER:                               *
                                // * formatedToDotSceneLight.lightAttenuation.range      *
                                // * is not the "half-distance" from Blender. It is the  *
                                // * "max. clipping distance" value.                     *
                                // * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                actualLight.SetAttenuation((float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset),
                                        (float)(formatedToDotSceneLight.lightAttenuation.constant),
                                        (float)(formatedToDotSceneLight.lightAttenuation.linear / (formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset)),
                                        (float)(formatedToDotSceneLight.lightAttenuation.quadratic / (formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset * this.ScaleOffset)));
                                //^-- square, because as names say it's a quadratic formula
                            }
                        }

                        #endregion
                        #region set spotlight range

                        if (formatedToDotSceneLight.lightRange != null)
                        {
                            if (actualLight.Type == Light.LightTypes.LT_SPOTLIGHT)
                                actualLight.SetSpotlightRange((float)formatedToDotSceneLight.lightRange.inner,
                                    (float)formatedToDotSceneLight.lightRange.outer,
                                    (float)formatedToDotSceneLight.lightRange.falloff);
                        }

                        #endregion
                        #endregion
                        break;
                    case dotSceneElementTags.camera:
                        #region if node is a camera

                        dotSceneCamera formatedToDotSceneCamera = (dotSceneCamera)nodeFromXML.specific;
                        #region generate unique new camera

                        int cameraNameModificationCounter = 0;
                        string cameraNameToApply = formatedToDotSceneCamera.name;

                        while (this.mgr.HasCamera(cameraNameToApply))
                        {
                            cameraNameToApply = formatedToDotSceneCamera.name;
                            cameraNameToApply = cameraNameToApply + "_" + cameraNameModificationCounter.ToString();
                            cameraNameModificationCounter++;
                        }
                        Mogre.Camera actualCamera = this.mgr.CreateCamera(cameraNameToApply);

                        #endregion
                        #region set position
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * Create absolute position-vector for camera:                          *
                        // *      absolute = translation-base + ((rotation * relative) * scale)) *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        #region Determine relative position of camera to "deliverdExternalRootNode"

                        //rotate actual camera-position with factory-settings for ROLL, PITCH, YAW
                        actualNode.Position = new Quaternion(this.PitchOfEntireScene.ValueRadians, Vector3.UNIT_X) * actualNode.Position;
                        actualNode.Position = new Quaternion(this.YawOfEntireScene.ValueRadians, Vector3.UNIT_Y) * actualNode.Position;
                        actualNode.Position = new Quaternion(this.RollOfEntireScene.ValueRadians, Vector3.UNIT_Z) * actualNode.Position;

                        #endregion
                        #region Apply global scale and set absolute Position of the new light-source

                        actualCamera.SetPosition(
                            (float)(this.deliverdExternalRootNode.Position.x + (float)(actualNode.Position.x * this.ScaleOffset)),
                            (float)(this.deliverdExternalRootNode.Position.y + (float)(actualNode.Position.y * this.ScaleOffset)),
                            (float)(this.deliverdExternalRootNode.Position.z + (float)(actualNode.Position.z * this.ScaleOffset)));
                        #endregion

                        #endregion
                        #region set direction
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * dotScene.dtd (.xsd) defines light direction by a quaternion, aimed to an implicid *
                        // * vector with x = 0, y = 0, z = -1                                                  *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        normalVector = new Vector3(0f, 0f, -1f);

                        #region rotate actual camera direction with factory-settings for ROLL, PITCH, YAW

                        //effects of global Y, P, R
                        actualNode.Pitch(new Radian(this.PitchOfEntireScene), Node.TransformSpace.TS_WORLD);
                        actualNode.Yaw(new Radian(this.YawOfEntireScene), Node.TransformSpace.TS_WORLD);
                        actualNode.Roll(new Radian(this.RollOfEntireScene), Node.TransformSpace.TS_WORLD);

                        //multiply with final direction of "actualNode"
                        normalVector = new Quaternion(actualNode.Orientation.w, actualNode.Orientation.x, actualNode.Orientation.y, actualNode.Orientation.z) * normalVector;

                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        // * The factor "(float)(formatedToDotSceneLight.lightAttenuation.range * this.ScaleOffset)" *
                        // * is used, because light fades out too fast. Maybe that's only a problem with             *
                        // * blemder-imports. That's not tested.                                                     *
                        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        actualCamera.SetDirection(
                            actualCamera.Position.x + normalVector.x * (float)this.ScaleOffset,
                            actualCamera.Position.y + normalVector.y * (float)this.ScaleOffset,
                            actualCamera.Position.z + normalVector.z * (float)this.ScaleOffset);
                        #endregion

                        #endregion
                        #region set FOV (Field Of View)

                        actualCamera.FOVy = new Radian((float)formatedToDotSceneCamera.fov);

                        #endregion
                        #region set projectionType

                        switch (formatedToDotSceneCamera.projectionType)
                        {
                            case "orthographic": actualCamera.ProjectionType = ProjectionType.PT_ORTHOGRAPHIC; break;
                            case "perspective": actualCamera.ProjectionType = ProjectionType.PT_PERSPECTIVE; break;
                            default: actualCamera.ProjectionType = ProjectionType.PT_PERSPECTIVE; break;
                        }

                        #endregion
                        #region set clipping

                        if (formatedToDotSceneCamera.clipping != null)
                        {
                            actualCamera.NearClipDistance = (float)(formatedToDotSceneCamera.clipping.nearPlaneDist * this.ScaleOffset);
                            actualCamera.FarClipDistance = (float)(formatedToDotSceneCamera.clipping.farPlaneDist * this.ScaleOffset);

                        }
                        #endregion
                        #endregion
                        break;
                    default: break;
                }
                #endregion
            }
        }

        #endregion
        #region subsection: environment <-- ATTENTION, malfunction source.
        //...because dotScene-format and blenderexporter aren't fully compatible to ogre (?)

        if (this.doAttachEnvironment)
        {
            #region set up background-colour

            if (actualScene.environment.colourBackground != null)
            {
                this.mgr.AmbientLight = new ColourValue(
                    (float)actualScene.environment.colourBackground.r,
                    (float)actualScene.environment.colourBackground.g,
                    (float)actualScene.environment.colourBackground.b);
            }

            #endregion
            #region set up ambient-colour

            if (actualScene.environment.colourAmbient != null)
            {
                //until now, nothing happens!
                //no corrspondig value in SceneMgr for background-colour?!
            }

            #endregion
            #region set up fog

            if (actualScene.environment.fog != null)
            {
                #region select fog-mode

                FogMode mode;
                switch (actualScene.environment.fog.mode)
                {
                    case "none":
                        //it seems, that the blender exports not this value, so this string "none" is safe!!!
                        mode = FogMode.FOG_NONE;
                        break;
                    case "linear": //maybe the only exported value from blender. not sure what other exporters produce!!!
                        mode = FogMode.FOG_LINEAR;
                        break;
                    case "exp":
                        //it seems, that the blender exports not this value, so this string "exp" is safe!!!
                        mode = FogMode.FOG_EXP;
                        break;
                    case "exp2":
                        //it seems, that the blender exports not this value, so this string "exp2" is safe!!!
                        mode = FogMode.FOG_EXP2;
                        break;
                    default:
                        //it seems, that the blender exports not this value, so this string "none" is safe!!!
                        mode = FogMode.FOG_NONE;
                        break;
                }

                #endregion
                this.mgr.SetFog(mode,
                    new ColourValue((float)actualScene.environment.fog.colourDiffuse.r, (float)actualScene.environment.fog.colourDiffuse.g, (float)actualScene.environment.fog.colourDiffuse.b),
                    1.0f, //maybe 1.0 is the neutal value? This value is not delivered by blender-exporter or dotScene-format!!!
                    (float)actualScene.environment.fog.linearStart,
                    (float)actualScene.environment.fog.linearEnd);
            }

            #endregion
        }

        #endregion
    }
    #endregion
    return true;
}
#endregion
}      
*/

/*
void main(void)
{
	
	//dotSceneAdvanced::dotSceneAttachFactory *AttachFactory = new dotSceneAdvanced::dotSceneAttachFactory("MyFactory", 



	dotSceneXmlReader *reader = new dotSceneXmlReader("C:/OViSE/OViSE/dotScene/dotScene.xsd", true);
	reader->parseDotSceneXML("C:/OViSE/OViSETestScene.xml");
	dotSceneObjects::dotScene* myScene = reader->loadDotScene();
	
	std::cout << "\n\n   Letzter Check: " << myScene->get_FormatVersion() << " :-)\n\n";

	int dummy;
	std::cin >> dummy;
}*/


void dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, std::string UniqueNameOfScene)
{
	xercesc::DOMNodeList *ItemElements = 0, *FileElements = 0;
	xercesc::DOMElement *DOMElement_item = 0;

	ItemElements = DOMElement_externals->getElementsByTagName(XMLString::transcode("item"));
	if (ItemElements->getLength() > 0)
	{
		for(XMLSize_t ItemNodeIterator = 0; ItemNodeIterator < ItemElements->getLength(); ItemNodeIterator++)
		{
			DOMElement_item = (xercesc::DOMElement*) ItemElements->item(ItemNodeIterator);

			FileElements = DOMElement_item->getElementsByTagName(XMLString::transcode("file"));
			if (FileElements->getLength() > 0)
			{
				xercesc::DOMElement* DOMElement_file = (xercesc::DOMElement*) FileElements->item(0);

				if (	DOMElement_item->hasAttribute(XMLString::transcode("type"))
					&&	DOMElement_file->hasAttribute(XMLString::transcode("name")))
				{
					std::string tempName = XMLString::transcode(DOMElement_file->getAttribute(XMLString::transcode("name")));
					std::string tempType = XMLString::transcode(DOMElement_item->getAttribute(XMLString::transcode("type")));

					std::string tempPath = Ogre::String(this->LocationsOfMeshFiles[UniqueNameOfScene]);
					std::string tempFullPath = tempPath + tempName;

					Ogre::ResourceGroupManager::getSingleton().declareResource(tempFullPath, tempType, this->get_NameOfFactoryOwnedResourceGroup());

					std::string LogMsg = "SCENE FACTORY: Added " + tempType + " \"" + tempFullPath + "\" to ResourceGroup \"" + this->get_NameOfFactoryOwnedResourceGroup() + "\"";
					Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);
				}
			}
		}
	}
}

void dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes)
{
	xercesc::DOMNodeList *NodeElements = 0, *CamElements = 0, *LightElements = 0;
	xercesc::DOMElement *DOMElement_position = 0, *DOMElement_orientation = 0, *DOMElement_quaternion = 0, *DOMElement_scale = 0;

	// In nodes is abstract. So elements beyond "node"-elements must be "global" transitions and rotations for scene's root node. Attribute too.
	
	// Handle cams...


	// Handle lights...

	/// STEP 4.1: Handle childnodes...
	NodeElements = DOMElement_nodes->getElementsByTagName(XMLString::transcode("node"));
	if (NodeElements->getLength() > 0)
	{
		for(XMLSize_t ChildNodeIterator = 0; ChildNodeIterator < NodeElements->getLength(); ChildNodeIterator++)
		{
			this->v1_0_0_Interpretation_Node((xercesc::DOMElement*) NodeElements->item(ChildNodeIterator), this->_AttachRootNode);
		}
	}


	// Handle attributes...
	bool Visible = true;
	bool CascadeVisibility = true;

	if (DOMElement_nodes->hasAttribute(XMLString::transcode("visible")))
	{
		std::string buff = XMLString::transcode(DOMElement_nodes->getAttribute(XMLString::transcode("visible")));
		if (buff == "true") Visible = true;
		if (buff == "false") Visible = false;
		else
		{
			; // Attention: DEBUG-Trap. When this line is reached, something goes wrong. More testing is needed!!!
		}
	}

	if (DOMElement_nodes->hasAttribute(XMLString::transcode("cascadeVisibility")))
	{
		std::string buff = XMLString::transcode(DOMElement_nodes->getAttribute(XMLString::transcode("cascadeVisibility")));
		if (buff == "true") Visible = true;
		if (buff == "false") Visible = false;
		else
		{
			; // Attention: DEBUG-Trap. When this line is reached, something goes wrong. More testing is needed!!!
		}
	}

	this->_AttachRootNode->setVisible(Visible, CascadeVisibility);
}

void dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Camera(xercesc::DOMElement* DOMElement_camera)
{
	/*
	Ogre::Camera test;

      //<xs:attribute name="name" type="xs:string" />
	test = new Ogre::Camera( name , scenemgr );
      //<xs:attribute name="id" type="xs:ID" />
	//test. ?? ID ??
      //<xs:attribute default="45" name="FOVy" type="xs:string" />
	test.setFOVy( );
      //<xs:attribute default="1.3333333" name="aspectRatio" type="xs:string" />
	test.setAspectRatio ( );
      //<xs:attribute default="perspective" name="projectionType"><xs:enumeration value="perspective" /><xs:enumeration value="orthographic" />
	test.setProjectionType( );
      //<xs:attribute default="solid" name="polygonMode"><xs:enumeration value="points" /><xs:enumeration value="wireframe" /><xs:enumeration value="solid" />
	test.setPolygonMode( );
      //<xs:attribute default="yes" name="useRenderingDistance"><xs:enumeration value="yes" /><xs:enumeration value="no" />
	test.setUseRenderingDistance( );
      //<xs:attribute default="1.0" name="lodBiasFactor" type="xs:string" />
	test.setLodBias( );

		
	<xs:sequence>
        <xs:element minOccurs="0" maxOccurs="1" ref="commonMovableObjectParams" />
        <xs:element minOccurs="0" maxOccurs="1" ref="clipping" />
        <xs:element minOccurs="0" maxOccurs="1" ref="position" />
        <xs:element minOccurs="0" maxOccurs="1" ref="orientation" />
        <xs:element minOccurs="0" maxOccurs="1" ref="quaternion" />
        <xs:element minOccurs="0" maxOccurs="1" ref="lookTarget" />
        <xs:element minOccurs="0" maxOccurs="1" ref="trackTarget" />
        <xs:element minOccurs="0" maxOccurs="1" ref="userDataReference" />
	</xs:sequence>
	
	//test.?? commonMovableObjectParams // ?? Hidden?

	//test.?? clipping // ?? Hidden?

	test.setPosition( );

	test.setOrientation( );

	test.setQuaternion( ); // OLD // orientation benutzen

	test.lookAt( );

	test.setAutoTracking( ); // ??

	// userDataRefernce // ?? Undefined
	*/
}

void dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode)
{
	std::string LogMsg;

	// * * * * * * * * Interpretation of element "node" * * * * * * * * *
	// STEP 1: Declare all possible elements...
	xercesc::DOMNodeList *NodeElements = 0, *EntityElements = 0;
	xercesc::DOMElement *DOMElement_position = 0, *DOMElement_orientation = 0, *DOMElement_quaternion = 0, *DOMElement_scale = 0;
	// ++ looktarget ++ tracktarget ++ userdatareference

	// STEP 2: Create all possible attributes... 
	std::string NewNode_name = "", NewNode_id = "";
	bool NewNode_visible = true, NewNode_cascadeVisibility = true, NewNode_isTarget = false;

	// STEP 2.1: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_node->hasAttribute(XMLString::transcode("name")))
	{
		NewNode_name = XMLString::transcode(DOMElement_node->getAttribute(XMLString::transcode("name")));
	}
	if (DOMElement_node->hasAttribute(XMLString::transcode("id")))
	{
		NewNode_id = XMLString::transcode(DOMElement_node->getAttribute(XMLString::transcode("id")));
	}
	if (DOMElement_node->hasAttribute(XMLString::transcode("visible")))
	{
		std::string temp = XMLString::transcode(DOMElement_node->getAttribute(XMLString::transcode("visible")));
		if (temp == "true") NewNode_visible = true;
		if (temp == "false") NewNode_visible = false;
	}
	if (DOMElement_node->hasAttribute(XMLString::transcode("cascadeVisibility")))
	{
		std::string temp = XMLString::transcode(DOMElement_node->getAttribute(XMLString::transcode("cascadeVisibility")));
		if (temp == "true") NewNode_cascadeVisibility = true;
		if (temp == "false") NewNode_cascadeVisibility = false;
	}
	if (DOMElement_node->hasAttribute(XMLString::transcode("isTarget")))
	{
		std::string temp = XMLString::transcode(DOMElement_node->getAttribute(XMLString::transcode("isTarget")));
		if (temp == "true") NewNode_isTarget = true;
		if (temp == "false") NewNode_isTarget = false;
	}
	
	// STEP 2.2: Processing of attribute "name"...
	// Generate unique name for new SceneNode.
    int NodeNameModificationCounter = 0;
	char valueAsString[20];
	Ogre::String NewNode_unique_name = NewNode_name;		
	while (this->Mgr->hasSceneNode(NewNode_unique_name))
    {
		sprintf(valueAsString, "%i", NodeNameModificationCounter); // TODO: use wx command here
		NewNode_unique_name = NewNode_name + "_" + valueAsString;
        NodeNameModificationCounter++;
    }
	
	// Handle "id": There is no information about how "id" has to be used.
	// "visible", "cascadeVisibility" and "isTarget" are handled below.

	// STEP 3: Create unique new SceneNode
	Ogre::SceneNode* NewNode = ParentNode->createChildSceneNode(Ogre::String(NewNode_unique_name));
	LogMsg = "SCENE FACTORY: Created and added new Ogre::SceneNode \"" + NewNode_unique_name + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);

	// STEP 3.1: Set rest of attributes...
	NewNode->setVisible(NewNode_visible, NewNode_cascadeVisibility);
#ifdef ATTACH_FACTORY__ALLOW_INTERPRETATION_ASSUMPTIONS
	NewNode->setAutoTracking(NewNode_isTarget); // <- ATTENTION: There is no information about how "isTarget" has to be used. This is an assumption.
#endif

	// STEP 4: Look for existing elements. First handle complex elements. "position", "scale", ... at last.
	// STEP 4.1: Handle childnodes...
	NodeElements = DOMElement_node->getElementsByTagName(XMLString::transcode("node"));
	if (NodeElements->getLength() > 0)
	{
		for(XMLSize_t ChildNodeIterator = 0; ChildNodeIterator < NodeElements->getLength(); ChildNodeIterator++)
		{
			this->v1_0_0_Interpretation_Node((xercesc::DOMElement*) NodeElements->item(ChildNodeIterator), NewNode);
		}
	}

	// STEP 4.2: Handle entities...
	EntityElements = DOMElement_node->getElementsByTagName(XMLString::transcode("entity"));
	if (EntityElements->getLength() > 0)
	{
		for(XMLSize_t EntityIterator = 0; EntityIterator < EntityElements->getLength(); EntityIterator++)
		{
			this->v1_0_0_Interpretation_Entity((xercesc::DOMElement*) EntityElements->item(EntityIterator), NewNode);
		}
	}

	// STEP 4.3: Handle lights...
	// TODO
	// STEP 4.4: Handle cameras...
	// TODO
	// STEP 4.5: Handle particleSystems...
	// TODO
	// STEP 4.6: Handle billboardSets...
	// TODO
	// STEP 4.7: Handle planes...
	// TODO

	
	xercesc::DOMNodeList *tempList;

	// STEP 4.8: Handle position...
	tempList = DOMElement_node->getElementsByTagName(XMLString::transcode("position"));
	if (tempList->getLength() > 0)
	{
		Ogre::Vector3 tempV3 = this->v1_0_0_Interpretation_Vector3((xercesc::DOMElement*) tempList->item(0));
		NewNode->setPosition(tempV3);
	}

	// STEP 4.9: Handle orientation/quaternion... // Prefering "quaternion" instead of orientation at moment. Exactly mathematical conversions not available now.
	tempList = DOMElement_node->getElementsByTagName(XMLString::transcode("quaternion"));
	if (tempList->getLength() > 0)
	{
		Ogre::Vector4 tempV4 = this->v1_0_0_Interpretation_Vector4((xercesc::DOMElement*) tempList->item(0));
		NewNode->setOrientation(tempV4.w, tempV4.x, tempV4.y, tempV4.z);
	}
	else
	{
		tempList = DOMElement_node->getElementsByTagName(XMLString::transcode("orientation"));
		if (tempList->getLength() > 0)
		{
			// Do nothing. Complex analysis skipped.
		}
	}

	// STEP 4.10: Handle scale...
	tempList = DOMElement_node->getElementsByTagName(XMLString::transcode("scale"));
	if (tempList->getLength() > 0)
	{
		Ogre::Vector3 tempV3 = this->v1_0_0_Interpretation_Vector3((xercesc::DOMElement*) tempList->item(0));
		NewNode->setScale(tempV3);
	}

	// STEP 4.11: Handle lookTarget...
	// TODO
	// STEP 4.12: Handle trackTarget...
	// TODO
	// STEP 4.13: Handle userDataReference...
	// TODO
}

void dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode)
{
	std::string LogMsg;

	// * * * * * * * * Interpretation of element "entity" * * * * * * * * *
	// STEP 1: Declare all possible elements...
	xercesc::DOMNodeList *AnimationsElements = 0, *animationStatesElements = 0;
	xercesc::DOMElement *DOMElement_commonMovableObjectParams = 0, *DOMElement_meshLODBias = 0, *DOMElement_materialLODBias = 0, *DOMElement_userDataReference = 0;

	// STEP 2: Create all possible attributes... 
	std::string NewEntity_name, NewEntity_id, NewEntity_meshFile = "robot.mesh" /* for debugging */, NewEntity_materialName, NewEntity_softwareAnimationRequests, NewEntity_softwareAnimationRequestsNormalsAlso;
	bool NewEntity_displaySkeleton = false, NewEntity_polygonModeOverrideable = false, NewEntity_vertexBufferUseShadow = false, NewEntity_indexBufferUseShadow = false;
	std::string NewEntity_vertexBufferUsage = "staticWriteOnly", NewEntity_indexBufferUsage = "staticWriteOnly"; // <- enum

	// STEP 2.1: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_entity->hasAttribute(XMLString::transcode("name")))
	{
		NewEntity_name = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("name")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("id")))
	{
		NewEntity_id = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("id")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("meshFile")))
	{
		NewEntity_meshFile = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("meshFile")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("materialName")))
	{
		NewEntity_materialName = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("materialName")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("softwareAnimationRequests")))
	{
		NewEntity_softwareAnimationRequests = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("softwareAnimationRequests")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("softwareAnimationRequestsNormalsAlso")))
	{
		NewEntity_softwareAnimationRequestsNormalsAlso = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("softwareAnimationRequestsNormalsAlso")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("displaySkeleton")))
	{
		std::string temp = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("displaySkeleton")));
		if (temp == "true") NewEntity_displaySkeleton = true;
		if (temp == "false") NewEntity_displaySkeleton = false;
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("polygonModeOverrideable")))
	{
		std::string temp = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("polygonModeOverrideable")));
		if (temp == "true") NewEntity_polygonModeOverrideable = true;
		if (temp == "false") NewEntity_polygonModeOverrideable = false;
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("vertexBufferUseShadow")))
	{
		std::string temp = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("vertexBufferUseShadow")));
		if (temp == "true") NewEntity_vertexBufferUseShadow = true;
		if (temp == "false") NewEntity_vertexBufferUseShadow = false;
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("indexBufferUseShadow")))
	{
		std::string temp = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("indexBufferUseShadow")));
		if (temp == "true") NewEntity_indexBufferUseShadow = true;
		if (temp == "false") NewEntity_indexBufferUseShadow = false;
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("vertexBufferUsage")))
	{
		NewEntity_vertexBufferUsage = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("vertexBufferUsage")));
	}
	if (DOMElement_entity->hasAttribute(XMLString::transcode("indexBufferUsage")))
	{
		NewEntity_indexBufferUsage = XMLString::transcode(DOMElement_entity->getAttribute(XMLString::transcode("indexBufferUsage")));
	}

	// STEP 2.2: Processing of attribute "name"...
	// Generate unique name for new SceneNode.
    int EntityNameModificationCounter = 0;
	char valueAsString[20];
	Ogre::String NewEntity_unique_name = NewEntity_name;		
	while (this->Mgr->hasSceneNode(NewEntity_unique_name))
    {
		sprintf(valueAsString, "%i", EntityNameModificationCounter); // TODO: use wx command here
		NewEntity_unique_name = NewEntity_name + "_" + valueAsString;
        EntityNameModificationCounter++;
    }
	
	// Handle "id": There is no information about how "id" has to be used.
	// Other attributes are handled below...

	// STEP 3: Create unique new Ogre::Entity
	Ogre::Entity* NewEntity = this->Mgr->createEntity(NewEntity_unique_name, NewEntity_meshFile);
	LogMsg = "SCENE FACTORY: Created new Ogre::Entity \"" + NewEntity_unique_name + "\" using .mesh \"" + NewEntity_meshFile + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);
	AssociateNode->attachObject(NewEntity);
	LogMsg = "SCENE FACTORY: Attached new Ogre::Entity \"" + NewEntity_unique_name + "\" to Ogre::SceneNode \"" + AssociateNode->getName() + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(LogMsg, Ogre::LML_NORMAL);
}


Ogre::Vector3 dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector3 * * * * * * * * *
	// STEP 1: Create all possible attributes...
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f;

	//XMLFloat test = 
	if (DOMElement_Vector3->hasAttribute(XMLString::transcode("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(XMLString::transcode("x"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(XMLString::transcode("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(XMLString::transcode("y"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(XMLString::transcode("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(XMLString::transcode("z"))).getValue();
	}

	return Ogre::Vector3(fX, fY, fZ);
}

Ogre::Vector4 dotSceneAdvanced::dotSceneAttachFactory::v1_0_0_Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector4 * * * * * * * * *
	// STEP 1: Create all possible attributes...
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f, fW = 0.0f;

	if (DOMElement_Vector4->hasAttribute(XMLString::transcode("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(XMLString::transcode("x"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(XMLString::transcode("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(XMLString::transcode("y"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(XMLString::transcode("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(XMLString::transcode("z"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(XMLString::transcode("w")))
	{
		fW = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(XMLString::transcode("w"))).getValue();
	}

	return Ogre::Vector4(fX, fY, fZ, fW);
}