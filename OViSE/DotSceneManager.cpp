#include "../OViSE/DotSceneManager.h"

// De- & Constructors
OViSEDotSceneManager::OViSEDotSceneManager(DotSceneBaseConfiguration *Configuration)
{
	this->mValid = true;

	// Store factory's configuration...
	if ( Configuration == 0 ) this->SetConfiguration(OViSEDotSceneManager::CreateDefaultConfiguration());
	else this->SetConfiguration(Configuration);
	
	// Create data-structures in ogre's engine for this factory... // TODO: MOVE TO OgreMediator
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(ToOgreString(this->GetAssociatedResourceGroup().UniqueName()));
	
	// Setup managers for delegated functions...
	this->mXmlMgr = new XmlManager(this->GetConfiguration());
}
OViSEDotSceneManager::~OViSEDotSceneManager()
{
	// TODO: delete Scenes?
	delete this->mXmlMgr;
}

// Accessors of general properies
void OViSEDotSceneManager::SetConfiguration(DotSceneBaseConfiguration* Configuration) { if (Configuration != 0) this->mConfiguration = Configuration; }
DotSceneBaseConfiguration* OViSEDotSceneManager::GetConfiguration() { return this->mConfiguration; }
QualifiedName OViSEDotSceneManager::GetSceneManager() { return this->GetConfiguration()->qSceneManager; }
QualifiedName OViSEDotSceneManager::GetName() { return this->GetConfiguration()->qDotSceneManager; }
QualifiedName OViSEDotSceneManager::GetAssociatedResourceGroup() { return this->GetConfiguration()->qResourceGroup; }
QualifiedNameCollection	OViSEDotSceneManager::GetImportedPrototypes() { return this->mQPrototypes; }
// Static methods
DotSceneBaseConfiguration* OViSEDotSceneManager::CreateDefaultConfiguration()
{
	// Create default values
	wxString NativeName = ToWxString("DEFAULT_DOTSCENEMANAGER");
	QualifiedName qSceneManager = OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager();
	QualifiedName qDotSceneManager = QualifiedName::Create(NativeName, ToWxString("DotSceneManager"));
	QualifiedName qResourceGroup = QualifiedName::Create(NativeName, ToWxString("ResourceGroup"));

	// Create configuration
	DotSceneBaseConfiguration *DefaultConfiguration = new DotSceneBaseConfiguration(qSceneManager, qDotSceneManager, qResourceGroup);

	// Set minimal interpretation
	DefaultConfiguration->doAttachEnvironment = false;
	DefaultConfiguration->doAttachExternals = false;
	DefaultConfiguration->doAttachNodes = true;

	return DefaultConfiguration;
}

bool OViSEDotSceneManager::SetURLofDotSceneXSD(wxString URLofDotSceneXSD) { return this->mXmlMgr->SetURLofXSD(URLofDotSceneXSD); }
bool OViSEDotSceneManager::SetURLofExportPath(wxString URLofExportPath) { return this->mXmlMgr->SetURLofExportPath(URLofExportPath); }
wxString OViSEDotSceneManager::GetURLofDotSceneXSD() { return this->mXmlMgr->GetURLofXSD(); }
wxString OViSEDotSceneManager::GetURLofExportPath() { return this->mXmlMgr->GetURLofExportPath(); }
bool OViSEDotSceneManager::IsReadyToExport() { return this->mXmlMgr->IsReadyToExport(); }
bool OViSEDotSceneManager::IsReadyToImport() { return this->mXmlMgr->IsReadyToImport(); }
bool OViSEDotSceneManager::SetPrototypeData(QualifiedName qPrototype, ScenePrototypeData NewData)
{
	// Validate parameters
	if ( !qPrototype.IsValid() ) return false;
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return false;
	
	// Get and validate ScenePrototype
	ScenePrototype* Prototype = this->mPrototypes[qPrototype.UniqueName()];
	if (Prototype == 0) return false;

	// Set data
	Prototype->Data = NewData;
	return true;
}

ScenePrototypeData OViSEDotSceneManager::GetPrototypeData(QualifiedName qPrototype)
{
	// Validate parameters
	if ( !qPrototype.IsValid() ) return ScenePrototypeData();
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return ScenePrototypeData();
	
	// Get and validate ScenePrototype
	ScenePrototype* Prototype = this->mPrototypes[qPrototype.UniqueName()];
	if (Prototype == 0) return ScenePrototypeData();
	
	// Get data
	return Prototype->Data;
}
bool OViSEDotSceneManager::MakeOgreSceneFromPrototype(QualifiedName qPrototype, QualifiedName qAnchorNode)
{
	bool Match = false;
	bool ReturnValue = false;

	// Validate parameter (valid?)
	if ( !qPrototype.IsValid() ) return false;

	// Validate parameter (correct type?)
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return false;

	ScenePrototype* Prototype = this->mPrototypes[qPrototype.UniqueName()];
	if (Prototype == 0) return false;

	// Add location of files to resourcegroup.
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ToOgreString(Prototype->Data.ResourceBaseDir), Ogre::String("FileSystem"), ToOgreString(this->GetAssociatedResourceGroup().UniqueName()), false);
	
	// Again, initialise ResourceGroup
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(ToOgreString(this->GetAssociatedResourceGroup().UniqueName()));
	
	if ((!Match) && DotSceneInterpreter_DOMToOgre_V1_0_0::IsValidFormatVersion(Prototype->GetDOMRepresentation()))
	{
		DotSceneInterpreter_DOMToOgre_V1_0_0 Interpreter;
		ReturnValue = Interpreter.Interpretation(Prototype->GetDOMRepresentation(), qAnchorNode, this->GetConfiguration());
	}
	
	// <---- TODO: Implement priority-list-selcetion!
	// while(!Match) { Nimm nächsten interpreter von liste; Match = prüfe version interpreter; wenn Match -> interpreter erzeugen + interpretation starten; }

	return ReturnValue;
}

QualifiedName OViSEDotSceneManager::MakePrototypeFromOgreScene(wxString NotUniquePrototypeName, QualifiedNameCollection Selection, wxString VersionStringForExport)
{
	/*bool Match = false;
	ScenePrototype* NewPrototype = 0;
	
	// Hier weiter. TODO: Erzeugen eines unique-name, Auswahl des richtigen Interpreters. Steht schon alles zur Verfügung.
	
	if ((!Match) && DotSceneInterpreter_OgreToDOM_V1_0_0::IsValidFormatVersion(VersionStringForExport))
	{
		DotSceneInterpreter_OgreToDOM_V1_0_0 Interpreter;
		NewPrototype = Interpreter.Interpretation(NotUniquePrototypeName, Selection, this->GetConfiguration());
		if (NewPrototype != 0)
		{
			this->ScenePrototypes[NewPrototype->GetUniqueName()] = NewPrototype;
			Match = true;
		}
	}

	// <---- TODO: Implement priority-list-seleection!
	// while (!Match);

	if (Match) return NewPrototype->GetUniqueName();
	else */
	return QualifiedName();
}

bool OViSEDotSceneManager::ExportScenePrototype(QualifiedName qPrototype, wxFileName DestinationURL)
{
	// Validate parameters (valid?)
	if ( !qPrototype.IsValid() ) return false;

	// Validate parameters (correct type?)
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return false;

	ScenePrototype* pPrototype = this->mPrototypes[qPrototype.UniqueName()];
	if (pPrototype == 0) return false;
	else return this->mXmlMgr->ExportScenePrototype(pPrototype, DestinationURL);
}
QualifiedName OViSEDotSceneManager::ImportScenePrototype(wxFileName URLofXML)
{
	ScenePrototype* pPrototype = this->mXmlMgr->ImportScenePrototype(URLofXML);
	if (pPrototype == 0) return QualifiedName();
	else
	{
		this->mPrototypes[pPrototype->GetName().UniqueName()] = pPrototype;
		this->mQPrototypes.Add(pPrototype->GetName());
		return pPrototype->GetName();
	}
}

bool OViSEDotSceneManager::RemoveScenePrototype(QualifiedName qPrototype)
{
	// Validate parameters (valid?)
	if ( !qPrototype.IsValid() ) return false;

	// Validate parameters (correct type?)
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return false;

	ScenePrototype* pPrototype = this->mPrototypes[qPrototype.UniqueName()];
	if (pPrototype == 0) return false;
	else
	{
		this->mPrototypes.erase(qPrototype.UniqueName());
		this->mQPrototypes.Remove(qPrototype);
		qPrototype.Destroy();
		delete pPrototype;
		return true;
	}
}

QualifiedName OViSEDotSceneManager::RenameScenePrototype(QualifiedName qPrototype, wxString NewNativePrototypeName)
{
	// Validate parameters (valid?)
	if ( !qPrototype.IsValid() ) return QualifiedName();

	// Validate parameters (correct type?)
	if ( this->mPrototypes.count(qPrototype.UniqueName()) == 0 ) return QualifiedName();

	ScenePrototype* pPrototype = this->mPrototypes[qPrototype.UniqueName()];
	if (pPrototype == 0) return QualifiedName();
	else
	{
		this->mPrototypes.erase(pPrototype->GetName().UniqueName());
		this->mQPrototypes.Remove(qPrototype);
		
		pPrototype->Rename(NewNativePrototypeName);

		this->mPrototypes[pPrototype->GetName().UniqueName()] = pPrototype;
		this->mQPrototypes.Add(pPrototype->GetName());
		return pPrototype->GetName();
	}
}

/// * * * * * * * * * When XML-interpreter was changed, you have to adapt this method. * * * * * * * * * 

/*
bool OViSEDotSceneManager::attachSingleSceneTo(	std::string UniqueNameOfPrototype,
																	std::string attachToNodeWithThisName)
{
	// Save time, if list ist empty...
	if (Scenes.empty()) return false;
	
	// Store external anchor node...
	this->ExternalAnchorNode = this->OgreSceneMgr->getSceneNode(Ogre::String(attachToNodeWithThisName)); 

	// Generate unique new root SceneNode - Part 1
    // Find a unique name...
    int rootNodeNameModificationCounter = 0;
	char valueAsString[20];
	Ogre::String rootNodeNameToApply = attachToNodeWithThisName + "_SceneRoot";		
	while (this->OgreSceneMgr->hasSceneNode(rootNodeNameToApply))
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
	dotScene actualScene = Scenes.find(UniqueNameOfPrototype)->second;

	// Create Ogre::String, describing the actual location of file
	Ogre::String actualLocationOfMaterialFile = Ogre::String(this->LocationsOfMaterialFiles[UniqueNameOfPrototype]);

	
    // Subsection of interpretation: Externals
	// Step 1: Clear ResourceGroup, when it exists.
	// TODO: Rename "get_NameOfFactoryOwnedMaterialResourceGroup" to "get_NameOfFactoryOwnedResourceGroup"
	// Clear ResourceGroup "Material", when it exists.
	Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(Ogre::String(this->get_NameOfFactoryOwnedResourceGroup()));

	// Step 2: Add path of dotScene-File to own recourcegroup
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::String(LocationsOfMeshFiles[UniqueNameOfPrototype]), Ogre::String("FileSystem"), this->get_NameOfFactoryOwnedResourceGroup(), false);

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
		recursiveNodeCreator(actualScene.get_Nodes()._ListOfNodes, this->_AttachRootNode, UniqueNameOfPrototype);
    }
/*
	// Subsection of interpretation: Environment <-- ATTENTION, malfunction source...because dotScene-format and blenderexporter aren't fully compatible to ogre (?) 
    if (this->doAttachEnvironment)
    {
        // Set up background-colour
        try // if (actualScene.get_environment().get_colourBackground() != null)
        {
			this->OgreSceneMgr->setAmbientLight(Ogre::ColourValue(
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

			this->OgreSceneMgr->setFog(mode, Ogre::ColourValue(
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

// region methods to attach "dotScene"-Objects

/* IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
   IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
   IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE! IMPORTANT! DO NOT DELETE! KNOWHOW INSIDE!
void OViSEDotSceneManager::recursiveNodeCreator(	std::list<dotSceneNode> actualNodeList,
																	Ogre::SceneNode* attachParentNode,
																	std::string UniqueNameOfPrototype)
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
            while(this->OgreSceneMgr->hasSceneNode(nodeNameToApply))
            {
				nodeNameToApply = actualNodeFromXML.get_name();
				nodeNameToApply = nodeNameToApply + "_";
				sprintf(valueNodeCounterAsString, "%i", nodeNameModificationCounter);
				nodeNameToApply = nodeNameToApply + valueNodeCounterAsString;
                nodeNameModificationCounter++;
            }

            // Create new SceneNode
			Ogre::SceneNode* actualNode = this->OgreSceneMgr->getSceneNode(attachParentNode->getName())->createChildSceneNode(nodeNameToApply);
				
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
                    while(this->OgreSceneMgr->hasEntity(entityNameToApply))
                    {
                        entityNameToApply = formatedToDotSceneEntity.get_name();
                        entityNameToApply = entityNameToApply + "_";
						sprintf(valueAsString, "%i", entityNameModificationCounter);
						entityNameToApply = entityNameToApply + valueAsString;
                        entityNameModificationCounter++;
                    }

					// Create new Entity
					// TODO: ".get_meshFile()" can grab into the "void" -> throws an Exception!!!!!!!!
					
					buff = this->LocationsOfMeshFiles[UniqueNameOfPrototype] + formatedToDotSceneEntity.get_meshFile();
					try
					{
					actualEntity = this->OgreSceneMgr->createEntity(entityNameToApply, buff);		
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
                    while(this->OgreSceneMgr->hasEntity(lightNameToApply))
                    {
						lightNameToApply = formatedToDotSceneLight->get_name();
                        lightNameToApply = lightNameToApply + "_";
						sprintf(valueAsString, "%i", lightNameModificationCounter);
						lightNameToApply = lightNameToApply + valueAsString;
                        lightNameModificationCounter++;
                    }

                    // Create new Light
                    actualLight = this->OgreSceneMgr->createLight(lightNameToApply);

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
                    while (this->OgreSceneMgr->hasCamera(cameraNameToApply))
                    {
						cameraNameToApply = formatedToDotSceneCamera->get_name();
                        cameraNameToApply = cameraNameToApply + "_";
						sprintf(valueAsString, "%i", cameraNameModificationCounter);
						cameraNameToApply = cameraNameToApply + valueAsString;
                        cameraNameModificationCounter++;
                    }

					// Create new Camera
					actualCamera = this->OgreSceneMgr->createCamera(cameraNameToApply);

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
			recursiveNodeCreator(actualNodeFromXML._ListOfChildNodes, actualNode, UniqueNameOfPrototype);
			
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
/// <returns>Returns "true", when process was successful. If not, it returns "false". For example, when "UniqueNameOfPrototype" is unknown.</returns>
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
/// <returns>Returns "true", when process was successful. If not, it returns "false". For example, when "UniqueNameOfPrototype" is unknown.</returns>
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


/*
void OViSEDotSceneManager::v1_0_0_Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene)
{
	xercesc::DOMNodeList *ItemElements = 0, *FileElements = 0;
	xercesc::DOMElement *DOMElement_item = 0;

	ItemElements = DOMElement_externals->getElementsByTagName(ToXMLString("item"));
	if (ItemElements->getLength() > 0)
	{
		for(XMLSize_t ItemNodeIterator = 0; ItemNodeIterator < ItemElements->getLength(); ItemNodeIterator++)
		{
			DOMElement_item = (xercesc::DOMElement*) ItemElements->item(ItemNodeIterator);

			FileElements = DOMElement_item->getElementsByTagName(XMLString::transcode("file"));
			if (FileElements->getLength() > 0)
			{
				xercesc::DOMElement* DOMElement_file = (xercesc::DOMElement*) FileElements->item(0);

				if (	DOMElement_item->hasAttribute(ToXMLString("type"))
					&&	DOMElement_file->hasAttribute(ToXMLString("name")))
				{
					wxString tempName = ToWxString(DOMElement_file->getAttribute(ToXMLString("name")));
					wxString tempType = ToWxString(DOMElement_item->getAttribute(ToXMLString("type")));
					wxString tempPath = this->LocationsOfMeshFiles[UniqueNameOfScene].GetPath();
					wxString tempFullPath;
					tempFullPath << tempPath << tempName;

					Ogre::ResourceGroupManager::getSingleton().declareResource(ToOgreString(tempFullPath), ToOgreString(tempType), ToOgreString(this->GetUniqueNameOfOwnedResourceGroup()));

					wxString LogMsg;
					LogMsg << wxT("OViSE dotScene Manager: Added ") << tempType << wxT(" \"") << tempFullPath << wxT("\" to ResourceGroup \"") << this->GetUniqueNameOfOwnedResourceGroup() << wxT("\"");
					Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(LogMsg), Ogre::LML_NORMAL);
				}
			}
		}
	}
}

void OViSEDotSceneManager::v1_0_0_Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes)
{
	
}

void OViSEDotSceneManager::v1_0_0_Interpretation_Camera(xercesc::DOMElement* DOMElement_camera)
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
/*}

void OViSEDotSceneManager::v1_0_0_Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode)
{
	wxString LogMsg;
}

void OViSEDotSceneManager::v1_0_0_Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode)
{

}


Ogre::Vector3 OViSEDotSceneManager::v1_0_0_Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector3 * * * * * * * * *
	// STEP 1: Create all possible attributes...
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f;

	//XMLFloat test = 
	if (DOMElement_Vector3->hasAttribute(ToXMLString("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("x"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(ToXMLString("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("y"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(ToXMLString("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("z"))).getValue();
	}

	return Ogre::Vector3(fX, fY, fZ);
}

Ogre::Vector4 OViSEDotSceneManager::v1_0_0_Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector4 * * * * * * * * *
	// STEP 1: Create all possible attributes...
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f, fW = 0.0f;

	if (DOMElement_Vector4->hasAttribute(ToXMLString("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("x"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("y"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("z"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("w")))
	{
		fW = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("w"))).getValue();
	}

	return Ogre::Vector4(fX, fY, fZ, fW);
}


Ogre::SceneNode* OViSEDotSceneManager::attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative)
{
	if (NotUniqueName.IsEmpty()) return 0;

	return this->attachSceneNode(NotUniqueName, Translation_Relative, Scale_Relative, Rotation_Relative, this->OgreSceneMgr->getRootSceneNode());
}
Ogre::SceneNode* OViSEDotSceneManager::attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, wxString ParentNode)
{
	if (NotUniqueName.IsEmpty()) return 0;
	if (ParentNode.IsEmpty())
		return this->attachSceneNode(NotUniqueName, Translation_Relative, Scale_Relative, Rotation_Relative, this->OgreSceneMgr->getRootSceneNode());
	else
		return this->attachSceneNode(NotUniqueName, Translation_Relative, Scale_Relative, Rotation_Relative, this->OgreSceneMgr->getSceneNode(ToOgreString(ParentNode)));
}

Ogre::SceneNode* OViSEDotSceneManager::attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, Ogre::SceneNode* ParentNode)
{
	if (NotUniqueName.IsEmpty()) return 0;
	if (ParentNode == 0) return 0;

	wxString NewUniqueName = this->SceneNodeNameMgr->AllocateUniqueName(NotUniqueName);
	
	Ogre::SceneNode* NewSceneNode = ParentNode->createChildSceneNode(ToOgreString(NewUniqueName));

	NewSceneNode->translate(Translation_Relative, Ogre::Node::TS_PARENT);
	NewSceneNode->rotate(Rotation_Relative, Ogre::Node::TS_PARENT);
	NewSceneNode->scale(Scale_Relative);

	return NewSceneNode;
}

Ogre::Entity* OViSEDotSceneManager::attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	wxFileName TempFileName = wxFileName(MeshFile);
	TempFileName.SetExt(ToWxString("mesh")); // To garant a filename with a extension...
	
	// Get unique entity name...
	wxString UniqueEntityName = this->EntityNameMgr->AllocateUniqueName(NotUniqueEntityName);

	// Create entity...
	Ogre::Entity* NewEntity = this->OgreSceneMgr->createEntity(ToOgreString(UniqueEntityName), ToOgreString(TempFileName.GetFullName()));
	AttachToThisNode->attachObject(NewEntity);

	return NewEntity;
}

Ogre::Entity* OViSEDotSceneManager::attachEntity(wxString NotUniqueEntityName, wxString MeshFile, wxString AttachToThisNode)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	return this->attachEntity(NotUniqueEntityName, MeshFile, this->OgreSceneMgr->getSceneNode(ToOgreString(AttachToThisNode)));
}

Ogre::Entity* OViSEDotSceneManager::attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	wxFileName TempFileName = wxFileName(MeshFile);
	return this->attachEntity(NotUniqueEntityName, MeshFile, this->attachSceneNode(NotUniqueEntityName, Translation_Relative, Scale_Relative, Rotation_Relative));
}

Ogre::Entity* OViSEDotSceneManager::attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, wxString AttachToThisNode)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	wxFileName TempFileName = wxFileName(MeshFile);
	return this->attachEntity(NotUniqueEntityName, MeshFile, this->attachSceneNode(NotUniqueEntityName, Translation_Relative, Scale_Relative, Rotation_Relative, AttachToThisNode));
}

Ogre::Entity* OViSEDotSceneManager::attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, Ogre::SceneNode* AttachToThisNode)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	wxFileName TempFileName = wxFileName(MeshFile);
	return this->attachEntity(NotUniqueEntityName, MeshFile, this->attachSceneNode(NotUniqueEntityName, Translation_Relative, Scale_Relative, Rotation_Relative, AttachToThisNode));
}



*/