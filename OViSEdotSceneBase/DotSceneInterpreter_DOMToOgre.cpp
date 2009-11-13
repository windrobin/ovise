/********************************************************************************
 * Name:      DotSceneInterpreter_DOMToOgre.cpp									*
 * Purpose:   Code implements the central method of it's abstract class,		*
 *			  which provides the basic methods for interpretation of a DOM		*
 *			  structure. In a inherited class all methods must be implemented.	*
 *			  That garants a full compatiblility to dotScene-format.			*
 *			  The implemented method is always the same and ensures				*
 *			  interpretation with only one method-call.							*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../OViSEdotSceneBase/DotSceneInterpreter_DOMToOgre.h"

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
															QualifiedName* qAnchorNodeName,
															DotSceneBaseConfiguration* Configuration )
{
	wxString LogMsg;
	Ogre::SceneManager* SceneMgr = 0;
	this->Configuration = Configuration;

	// Get and check Ogre::SceneManager...
	SceneMgr = OgreAPIMediator::GetSingletonPtr()->GetSceneManagerPtr(this->Configuration->qSceneManager);
	if (SceneMgr == 0) return false; // "Configuration" is invalid!
	
	// Store external anchor node...
	if (qAnchorNodeName == 0)
	{
		this->AnchorNode = SceneMgr->getRootSceneNode();

		LogMsg.Clear();
		LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Parameter 'qAnchorNodeName' is (null). Using RootSceneNode!");
		Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);
	}
	else
	{
		if (!qAnchorNodeName->IsValid())
		{
			this->AnchorNode = SceneMgr->getRootSceneNode();

			LogMsg.Clear();
			LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Parameter 'qAnchorNodeName' is INVALID. Using RootSceneNode!");
			Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);
		}
		else
		{
			if (!OgreAPIMediator::GetSingletonPtr()->HasSceneNode(*qAnchorNodeName))
			{
				this->AnchorNode = SceneMgr->getRootSceneNode();

				LogMsg.Clear();
				LogMsg << ToWxString("OViSE DOM Interpretation (abstract): 'qAnchorNodeName' with value \"") << qAnchorNodeName->UniqueName() << ToWxString("\" is not a qualified name of a Ogre::SceneNode. Using RootSceneNode instead!");
				Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);
			}
			else
			{
				this->AnchorNode = OgreAPIMediator::GetSingletonPtr()->GetSceneNodePtr(*qAnchorNodeName);

				LogMsg.Clear();
				LogMsg << ToWxString("OViSE DOM Interpretation (abstract): Using given paramter 'qAnchorNodeName' with value \"") << qAnchorNodeName->UniqueName() << ToWxString("\".");
				Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);
			}
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
		Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(ToOgreString(this->Configuration->qResourceGroup.UniqueName()));

		// Add path of dotScene-File to associated recourcegroup:
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ToOgreString(this->Configuration->LocationOfMeshFiles.GetPath()), Ogre::String("FileSystem"), ToOgreString(this->Configuration->qResourceGroup.UniqueName()), false); 

		// Identify format version of dotScene:
		this->Interpretation_Externals(DOMElement_externals, this->Configuration->qResourceGroup);

		// Again, initialise assocated resource group:
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(ToOgreString(this->Configuration->qResourceGroup.UniqueName()));
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

	// STEP 4: Apply offset-settings to anchornode (with new operator)
	this->AnchorNode = this->AnchorNode + this->Configuration->SceneOffset;

	LogMsg.Clear();
	LogMsg = ToWxString("OViSE DOM Interpretation (abstract): Applied offset-settings to anhcor-node.");
	Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

	return true;
}
