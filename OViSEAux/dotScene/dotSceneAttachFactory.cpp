#include "dotSceneAttachFactory.h"

using namespace dotSceneObjects;

// Properies (outer part) of general factory-setting
void dotSceneAdvanced::dotSceneAttachFactory::set_UniqueFactoryName(Ogre::String UniqueFactoryName)
{
	_UniqueFactoryName = UniqueFactoryName;
}

Ogre::String dotSceneAdvanced::dotSceneAttachFactory::get_UniqueFactoryName() const
{
	return _UniqueFactoryName;
}

void dotSceneAdvanced::dotSceneAttachFactory::set_NameOfFactoryOwnedMaterialResourceGroup(Ogre::String NameOfFactoryOwnedMaterialResourceGroup)
{
	_NameOfFactoryOwnedMaterialResourceGroup = NameOfFactoryOwnedMaterialResourceGroup; 
}	

Ogre::String dotSceneAdvanced::dotSceneAttachFactory::get_NameOfFactoryOwnedMaterialResourceGroup() const
{ 
	return _NameOfFactoryOwnedMaterialResourceGroup; 
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
	this->set_NameOfFactoryOwnedMaterialResourceGroup(UniqueFactoryName);

	this->set_ScaleOffset(1.0);
	this->set_PositionOffset(Ogre::Vector3(0.0, 0.0, 0.0));
	this->set_RollOfEntireScene(Ogre::Degree(0.0));
    this->set_PitchOfEntireScene(Ogre::Degree(0.0));
    this->set_YawOfEntireScene(Ogre::Degree(0.0));

	// Create data-structures in ogre's engine for this factory...
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(get_NameOfFactoryOwnedMaterialResourceGroup());
	
	// Store reference to Ogre::SceneManager
	this->Mgr = sceneMgr;

	// Platform dependent containers.
	// Linix-library contains map, instant of hash_map...
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	this->Scenes = stdext::hash_map<std::string, dotScene>();
    LocationsOfMeshFiles = stdext::hash_map<std::string, std::string>();
    LocationsOfMaterialFiles = stdext::hash_map<std::string, std::string>();
#else // Linux Libs
	this->Scenes = std::map<std::string, dotScene>();
	this->LocationsOfMeshFiles = std::map<std::string, std::string>();
	this->LocationsOfMaterialFiles = std::map<std::string, std::string>();
#endif
}
dotSceneAdvanced::dotSceneAttachFactory::~dotSceneAttachFactory() { }

/*
void dotSceneAdvanced::dotSceneAttachFactory::convertXMLNode(XMLSceneNode *xmlNode, Ogre::SceneNode *parentNode)
{
	switch(xmlNode->mType)
	{
	case XMLSceneNode::ENTITY:
		{			
			// Generate needed parameters from dotSceneObjects, with are relative to "attachRootNode"

			//Remember: "RelativeToRoot" means the TS_PARENT -transformingspace!
			Ogre::Vector3 nodeScaleRalativeToRoot(		(float)xmlNode->mScale[0], 
														(float)xmlNode->mScale[1], 
														(float)xmlNode->mScale[2]);
			Ogre::Vector3 nodeTranslationRelativeToRoot((float)xmlNode->mPosition[0], 
														(float)xmlNode->mPosition[1], 
														(float)xmlNode->mPosition[2]);
			Ogre::Quaternion nodeRotationRelativeToRoot((float)xmlNode->mQuaternion[3], 
														(float)xmlNode->mQuaternion[0], 
														(float)xmlNode->mQuaternion[1], 
														(float)xmlNode->mQuaternion[2]);

			// Generate unique new SceneNode and apply relative parameters

			//Find a unique name
			int nodeNameModificationCounter = 0;
			char valueAsString[20];
			Ogre::String nodeNameToApply = xmlNode->mName;
			while(this->Mgr->hasSceneNode(nodeNameToApply))
			{
				nodeNameToApply = xmlNode->mName;
				nodeNameToApply = nodeNameToApply + "_";
				//itoa(nodeNameModificationCounter, valueAsString, 10);
				sprintf(valueAsString, "%i", nodeNameModificationCounter);
				nodeNameToApply = nodeNameToApply + valueAsString;
				nodeNameModificationCounter++;
			}

			//Create new SceneNode
			Ogre::SceneNode* actualSceneNode = parentNode->createChildSceneNode(nodeNameToApply);
            
			//Apply relative parameters
			actualSceneNode->scale(nodeScaleRalativeToRoot);
			actualSceneNode->rotate(nodeRotationRelativeToRoot, Ogre::Node::TS_PARENT);                    
			actualSceneNode->translate(nodeTranslationRelativeToRoot, Ogre::Node::TS_PARENT);

            int entityNameModificationCounter = 0;
            string entityNameToApply = xmlNode->mEntityName;
            while (this->Mgr->hasEntity(entityNameToApply))
            {
                entityNameModificationCounter++;
            }
            char hlp[10];
            sprintf(hlp, "%i", entityNameModificationCounter);
            entityNameToApply += "_" + (string)hlp;

            Ogre::Entity *actualEntity = this->Mgr->createEntity(entityNameToApply, xmlNode->mEntityMeshFile);

            actualEntity->setNormaliseNormals(true);
            //actualEntity->setCastShadows(true);
            actualSceneNode->attachObject(actualEntity);
            Ogre::LogManager::getSingletonPtr()->logMessage("Attached Entity.");
            if(xmlNode->children.size() > 0)
            {
            	for(int i=0; i<(int)xmlNode->children.size(); i++)
            	{
            		convertXMLNode(xmlNode->children.at(i), actualSceneNode);
            	}
            }
		} break;
		default: break;
	}
}
*/
// methods to add new "dotScene"-Objects
bool dotSceneAdvanced::dotSceneAttachFactory::addSceneBluePrint(std::string uniqueSceneName, dotScene newScene, 
																std::string locationOfMeshFiles)
{
	// <------ If you want to implement a validity check of "locationOfMeshFiles",
	//         do it here. A proper code-snippet in implemented in C# version.

    // Check, if the key is already used.
	// Remember it's name: it has to be unique! If it's not there, return false.			
	if (Scenes.find(uniqueSceneName) != Scenes.end()) return false;
	
	// Add new objects to all hashtables with same key
	Scenes[uniqueSceneName] = newScene;
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

    return attachSingleSceneTo(uniqueSceneName, attachToNodeWithThisName);
}

bool dotSceneAdvanced::dotSceneAttachFactory::attachSingleSceneTo(	std::string uniqueSceneName,
																	std::string attachToNodeWithThisName)
{
	// Save time, if list ist empty...
	if (Scenes.empty()) return false;
	
	// Store external anchor node...
	this->deliverdExternalRootNode = this->Mgr->getSceneNode(Ogre::String(attachToNodeWithThisName)); 

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
	this->_AttachRootNode = this->deliverdExternalRootNode->createChildSceneNode(Ogre::String(rootNodeNameToApply));

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
    if (this->doAttachExternals)
    {   
        // Clear ResourceGroup "Material", when it exists.
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(Ogre::String(this->get_NameOfFactoryOwnedMaterialResourceGroup()));
        
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
						Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(get_NameOfFactoryOwnedMaterialResourceGroup());

						// Add location of files to resourcegroup.
						Ogre::ResourceGroupManager::getSingleton().addResourceLocation(actualLocationOfMaterialFile, Ogre::String("FileSystem"), get_NameOfFactoryOwnedMaterialResourceGroup(), false);

						// Again, initialise ResourceGroup "Material".
						Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(get_NameOfFactoryOwnedMaterialResourceGroup());                           
					}
					catch(Ogre::Exception e)
					{					
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
*/
    return true;
}

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
					actualEntity = this->Mgr->createEntity(entityNameToApply, this->LocationsOfMeshFiles[uniqueSceneName] + formatedToDotSceneEntity.get_meshFile());				
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
				*/
                default: // If node has no specifics (for example a invisible anchor-node)
					break;
			}
			
			// Recursive call for childnode structures
			recursiveNodeCreator(actualNodeFromXML._ListOfChildNodes, actualNode, uniqueSceneName);
			
			actualNodeListIterator++;
		}while(actualNodeListIterator != (actualNodeList.end()));
	}
}


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

void deletethisstub(){}

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