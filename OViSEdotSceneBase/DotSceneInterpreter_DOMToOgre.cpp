#include "DotSceneInterpreter_DOMToOgre.h"

DotSceneInterpreter_DOMToOgre::~DotSceneInterpreter_DOMToOgre(void) { }

wxString DotSceneInterpreter_DOMToOgre::GetVersionString( xercesc::DOMDocument* DOMRepresentationOfScene )
{
	// Get root element...
	xercesc::DOMElement *DOMElement_scene = 0;
	DOMElement_scene = DOMRepresentationOfScene->getDocumentElement();

	// Get version-string...
	if (DOMElement_scene->hasAttribute(ToXMLString("formatVersion"))) return ToWxString(DOMElement_scene->getAttribute(ToXMLString("formatVersion")));
	else return wxString(); // Return "" (empty string) when no version-string is found!
}

bool DotSceneInterpreter_DOMToOgre::Interpretation_DOMScene(xercesc::DOMDocument* DOMRepresentationOfScene,
															wxString AnchorNodeName,
															DotSceneBaseConfiguration* Configuration )
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
	if (DotSceneInterpreter_DOMToOgre::Configuration->doAttachExternals && (DOMElement_externals != 0))
    {
		// Prepare AssociatedResourceGroup, when it exists:
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(ToOgreString(this->Configuration->UniqueNameOfAssociatedResourceGroup));

		// Add path of dotScene-File to associated recourcegroup:
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ToOgreString(this->Configuration->LocationOfMeshFiles.GetPath()), Ogre::String("FileSystem"), ToOgreString(DotSceneInterpreter_DOMToOgre::Configuration->UniqueNameOfAssociatedResourceGroup), false); 

		// Identify format version of dotScene:
		this->Interpretation_Externals(DOMElement_externals, this->Configuration->UniqueNameOfAssociatedResourceGroup);

		// Again, initialise assocated resource group:
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(ToOgreString(this->Configuration->UniqueNameOfAssociatedResourceGroup));
	}

	// STEP 2: Optional add nodes, if "doAttachNodes" is true:
	if (DotSceneInterpreter_DOMToOgre::Configuration->doAttachNodes && (DOMElement_nodes != 0))
    {
			this->Interpretation_Nodes(DOMElement_nodes);
    }

	// STEP 3: Optional add environment, if "doAttachEnvironment" is true:
	if (DotSceneInterpreter_DOMToOgre::Configuration->doAttachEnvironment && (DOMElement_environment != 0))
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