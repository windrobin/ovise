#include "OViSEInterpreter_DOMToOgre_DotSceneAbstract.h"

OViSEInterpreter_DOMToOgre_DotSceneAbstract::~OViSEInterpreter_DOMToOgre_DotSceneAbstract(void) { }

wxString OViSEInterpreter_DOMToOgre_DotSceneAbstract::GetVersionString( xercesc::DOMDocument* DOMRepresentationOfScene )
{
	// Get root element...
	xercesc::DOMElement *DOMElement_scene = 0;
	DOMElement_scene = DOMRepresentationOfScene->getDocumentElement();

	// Get version-string...
	if (DOMElement_scene->hasAttribute(ToXMLString("formatVersion"))) return ToWxString(DOMElement_scene->getAttribute(ToXMLString("formatVersion")));
	else return wxString(); // Return "" (empty string) when no version-string is found!
}

bool OViSEInterpreter_DOMToOgre_DotSceneAbstract::Interpretation_DOMScene(	xercesc::DOMDocument* DOMRepresentationOfScene,
																			wxString AnchorNodeName,
																			OViSEDotSceneManagerConfiguration* Configuration )
{
	wxString LogMsg;
	Ogre::SceneManager* SceneMgr = 0;
	this->Configuration = Configuration;

	// Get and check Ogre::SceneManager...
	SceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->Configuration->SceneManagerName));
	if (SceneMgr == 0) return false; // "Configuration" is invalid!
	
	// Store external anchor node...
	if (AnchorNodeName.IsEmpty())
	{
		this->AnchorNode = SceneMgr->getRootSceneNode();

		LogMsg.Clear();
		LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Name of anchor-SceneNode is empty. Using RootSceneNode!");
		this->Configuration->Log->WriteToOgreLog(LogMsg, OViSELogging::Normal);
	}
	else
	{
		if (SceneMgr->hasSceneNode(ToOgreString(AnchorNodeName)))
		{
			this->AnchorNode = SceneMgr->getSceneNode(ToOgreString(AnchorNodeName));

			LogMsg.Clear();
			LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Using given anchor-SceneNode \"") << AnchorNodeName << ToWxString("\".");
			this->Configuration->Log->WriteToOgreLog(LogMsg, OViSELogging::Normal);
		}
		else
		{
			this->AnchorNode = SceneMgr->getRootSceneNode();

			LogMsg.Clear();
			LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Given anchor-SceneNode \"") << AnchorNodeName << ToWxString("\" does not exist. Using RootSceneNode instead!");
			this->Configuration->Log->WriteToOgreLog(LogMsg, OViSELogging::Normal);
		}
	}

	// Basic setup...
	xercesc::DOMElement *DOMElement_scene = DOMRepresentationOfScene->getDocumentElement();

	// Begin interpretation at top-stage...
	xercesc::DOMNodeList *ChildElements;

	xercesc::DOMElement *DOMElement_nodes = 0;
	xercesc::DOMElement *DOMElement_externals = 0;
	xercesc::DOMElement *DOMElement_environment = 0;

	// Get elements "nodes", "externals" and "environment"
	ChildElements = DOMElement_scene->getElementsByTagName(ToXMLString("nodes"));
	if (ChildElements->getLength() > 0) DOMElement_nodes = (xercesc::DOMElement*) ChildElements->item(0);

	ChildElements = DOMElement_scene->getElementsByTagName(ToXMLString("externals"));
	if (ChildElements->getLength() > 0) DOMElement_externals = (xercesc::DOMElement*) ChildElements->item(0);

	ChildElements = DOMElement_scene->getElementsByTagName(ToXMLString("environment"));
	if (ChildElements->getLength() > 0) DOMElement_environment = (xercesc::DOMElement*) ChildElements->item(0);

	// STEP 1: Optional add materials, if "doAttachExternals" is true:
	if (OViSEInterpreter_DOMToOgre_DotSceneAbstract::Configuration->doAttachExternals && (DOMElement_externals != 0))
    {
		// Prepare AssociatedResourceGroup, when it exists:
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(ToOgreString(this->Configuration->UniqueNameOfAssociatedResourceGroup));

		// Add path of dotScene-File to associated recourcegroup:
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ToOgreString(this->Configuration->LocationOfMeshFiles.GetPath()), Ogre::String("FileSystem"), ToOgreString(OViSEInterpreter_DOMToOgre_DotSceneAbstract::Configuration->UniqueNameOfAssociatedResourceGroup), false); 

		// Identify format version of dotScene:
		this->Interpretation_Externals(DOMElement_externals, this->Configuration->UniqueNameOfAssociatedResourceGroup);

		// Again, initialise assocated resource group:
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(ToOgreString(this->Configuration->UniqueNameOfAssociatedResourceGroup));
	}

	// STEP 2: Optional add nodes, if "doAttachNodes" is true:
	if (OViSEInterpreter_DOMToOgre_DotSceneAbstract::Configuration->doAttachNodes && (DOMElement_nodes != 0))
    {
			this->Interpretation_Nodes(DOMElement_nodes);
    }

	// STEP 3: Optional add environment, if "doAttachEnvironment" is true:
	if (OViSEInterpreter_DOMToOgre_DotSceneAbstract::Configuration->doAttachEnvironment && (DOMElement_environment != 0))
    {
			this->Interpretation_Environment(DOMElement_environment);
    }

	// STEP 4: Apply  offset-settings to anchornode: rotate entire scene with ROLL, PITCH, YAW
	this->AnchorNode->pitch(Ogre::Radian(this->Configuration->SceneOffset.GetPitchOffset()), Ogre::Node::TS_WORLD);
    this->AnchorNode->yaw(Ogre::Radian(this->Configuration->SceneOffset.GetYawOffset()), Ogre::Node::TS_WORLD);
	this->AnchorNode->roll(Ogre::Radian(this->Configuration->SceneOffset.GetRollOffset()), Ogre::Node::TS_WORLD);
	
	LogMsg.Clear();
	LogMsg = ToWxString("OViSE DOM Interpretation (abstract): Rotated anchor-node with offset-settings.");
	this->Configuration->Log->WriteToOgreLog(LogMsg, OViSELogging::Normal);

    // STEP 5: Apply  offset-settings to anchornode: scale anchornode
	this->AnchorNode->scale((float)this->Configuration->SceneOffset.GetScaleOffset(), (float)this->Configuration->SceneOffset.GetScaleOffset(), (float)this->Configuration->SceneOffset.GetScaleOffset());
	
	LogMsg.Clear();
	LogMsg = ToWxString("OViSE DOM Interpretation (abstract): Scaled anchor-node with offset-settings.");
	this->Configuration->Log->WriteToOgreLog(LogMsg, OViSELogging::Normal);

	return true;
}

Ogre::SceneNode* OViSEInterpreter_DOMToOgre_DotSceneAbstract::AttachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, Ogre::SceneNode* ParentNode)
{
	if (NotUniqueName.IsEmpty()) return 0;
	if (ParentNode == 0) return 0;

	wxString NewUniqueName = this->Configuration->SceneNodeNameMgr->AllocateUniqueName(NotUniqueName);
	
	Ogre::SceneNode* NewSceneNode = ParentNode->createChildSceneNode(ToOgreString(NewUniqueName));

	NewSceneNode->translate(Translation_Relative, Ogre::Node::TS_PARENT);
	NewSceneNode->scale(Scale_Relative);
	NewSceneNode->rotate(Rotation_Relative, Ogre::Node::TS_PARENT);
	
	return NewSceneNode;
}

Ogre::Entity* OViSEInterpreter_DOMToOgre_DotSceneAbstract::AttachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	if (NotUniqueEntityName.IsEmpty()) return 0;

	wxFileName TempFileName = wxFileName(MeshFile);
	TempFileName.SetExt(ToWxString("mesh")); // To garant a filename with a extension...
	
	// Get unique entity name...
	wxString UniqueEntityName = this->Configuration->EntityNameMgr->AllocateUniqueName(NotUniqueEntityName);

	// Create entity...
	Ogre::Entity* NewEntity = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->Configuration->SceneManagerName))->createEntity(ToOgreString(UniqueEntityName), ToOgreString(TempFileName.GetFullName()));
	AttachToThisNode->attachObject(NewEntity);

	return NewEntity;
}



