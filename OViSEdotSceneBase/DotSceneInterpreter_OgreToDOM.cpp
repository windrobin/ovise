#include "DotSceneInterpreter_OgreToDOM.h"

wxString DotSceneInterpreter_OgreToDOM::GetVersionString() { return VersionString; }
DotSceneInterpreter_OgreToDOM::~DotSceneInterpreter_OgreToDOM(void) { }
bool DotSceneInterpreter_OgreToDOM::Interpretation_OgreScene(	wxString NotUniquePrototypeName,
																OViSESelectionMap Selection,
																DotSceneBaseConfiguration* Configuration)
{
	wxString LogMsg;

	if (NotUniquePrototypeName.IsSameAs(ToWxString(""))) this->NotUniquePrototypeName = ToWxString("NoName");
	else this->NotUniquePrototypeName = NotUniquePrototypeName;

	this->Selection  = Selection;
	this->Configuration = Configuration;
	this->SetVersionString(ToWxString("1.0.0"));

	// Get and check Ogre::SceneManager...
	this->SceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->Configuration->SceneManagerName));
	if (this->SceneMgr == 0) return false; // "Configuration" is invalid!

	// Create UniquePrototypeName...
	this->UniquePrototypeName = this->Configuration->PrototypeNameMgr->AllocateUniqueName(this->NotUniquePrototypeName);

	// Create DOMImplementation
	this->Implementation = DOMImplementationRegistry::getDOMImplementation(ToXMLString("Core")); // Kommentar von HR: Core??? Welche Strings gehen hin noch rein? Enum wäre besser!

	// Create DOMDocument
	xercesc::DOMDocument* TempDOMDocument = DotSceneInterpreter_OgreToDOM::Implementation->createDocument(0, ToXMLString("scene"), 0); // Don't use any more, but remember: "(XMLString::transcode(this->mDestinationURI.c_str()), XMLString::transcode("scene"), 0)"
	
	// Create new Prototype
	this->Prototype = new ScenePrototype(this->UniquePrototypeName, NotUniquePrototypeName, TempDOMDocument);

	// Get "scene"-element and add attribute "formatVersion"...
	DOMElement* SceneElement = this->Prototype->GetDOMRepresentation()->getDocumentElement();
	SceneElement->setAttribute(ToXMLString("formatVersion"), ToXMLString(this->GetVersionString()));

	// Complete interpretation...
	this->Interpretation_Nodes(SceneElement);

	return true;
}

void DotSceneInterpreter_OgreToDOM::Interpretation_Nodes(xercesc::DOMElement* SceneElement)
{
	// Create "nodes"-element and append to "scene"-element...
	DOMElement* NodesElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("nodes"));
	SceneElement->appendChild(NodesElement);

	// Recusive: get nodes from Ogre::SceneManager, create "node"-elements and append 'em to "nodes"-element or parent "node"-elements...
	// Get one (now root) node, and start recursive walkthrough...

	// SceneNode-Filtering! Status now: WhilteList_STAGE1
	// Export only selected SceneNodes. Using DOM-API for a easy and fast handling...	
	HashMap_OgreSceneNodePointer WhiteList_STAGE1; // List of Ogre::MoveableObejcts
	HashMap_DOMPointer WhiteList_STAGE2; // List of nodes/DOMElements
	HashMap_DOMPointer BlackList_STAGE2; // List of already created nodes/DOMElements
	
	// STEP 1: Generate Stage 2 WhiteList == Selected SceneNodes (WhilteList_STAGE1)
	if (!this->Selection.empty())
	{
		for (OViSESelectionMap::const_iterator iter = this->Selection.begin(); iter != this->Selection.end(); iter++)
		{
			// OViSESelectionMap uses objects of Ogre::MovableObject and not Ogre::Node or Ogre::SceneNode.
			// First get these nodes, then find out if a Ogre::Node is a Ogre::SceneNode
			// Ogre::SceneNodes will be added to WhilteList_STAGE1

			Ogre::MovableObject* MovObj = iter->second; // Maybe Ogre::Light, Ogre::Cam or Ogre::Entity etc.

			// Filter: Only Ogre::Light, Ogre::Cam and Ogre::Entity are handled. Ignore other classes!
			// TODO: Improve to all ogre types (far futhur)
			bool match = false;
			if((!match) && (MovObj->getMovableType() == "Camera"))
			{
				match = false; //true;
			}
			if((!match) && (MovObj->getMovableType() == "Entity")) match = true;
			if((!match) && (MovObj->getMovableType() == "Light"))
			{
				match = false; //true;
			}

			if (match)
			{
				Ogre::SceneNode* tempSceneNode = static_cast<Ogre::SceneNode*>(MovObj->getParentSceneNode());
				WhiteList_STAGE1[ToWxString(tempSceneNode->getName())] = tempSceneNode;
			}
		}
	}
	else
	{
		// Add RootSceneNode, when there aren't any choosen SceneNodes...
		WhiteList_STAGE1[ToWxString(this->SceneMgr->getRootSceneNode()->getName())] = this->SceneMgr->getRootSceneNode();
	}

	// STEP 2: Generate Stage 2 WhiteList recursivly (WhilteList_STAGE2)
	if (!WhiteList_STAGE1.empty())
	{
		for(HashMap_OgreSceneNodePointer::iterator iter = WhiteList_STAGE1.begin(); iter != WhiteList_STAGE1.end(); iter++)
		{
			this->RecursiveNodeTreeWalkthrough(iter->second, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2);
		}
	}

	// STEP 3: Process WhiteList_STAGE2 == append childelements
	if (!WhiteList_STAGE2.empty())
	{
		for(HashMap_DOMPointer::iterator iter = WhiteList_STAGE2.begin(); iter != WhiteList_STAGE2.end(); iter++)
		{
			NodesElement->appendChild(iter->second);
		}
	}
}

void DotSceneInterpreter_OgreToDOM::RecursiveNodeTreeWalkthrough(	Ogre::Node* SomeNode,
																	HashMap_OgreSceneNodePointer& WhiteList_STAGE1,
																	HashMap_DOMPointer& WhiteList_STAGE2,
																	HashMap_DOMPointer& BlackList_STAGE2)
{
	// STEP 1: Convert Ogre::Node to Ogre::SceneNode and get it's (unique) name
	Ogre::SceneNode* SomeSceneNode = static_cast<Ogre::SceneNode*>(SomeNode);
	wxString SceneNodeName = ToWxString(SomeSceneNode->getName());

	// STEP 2: If there is a Element with this name in BlackList_STAGE2 do nothing. Else...
	if (BlackList_STAGE2.count(SceneNodeName) == 0)
	{
		// STEP 2.1: Create DOM-element "node"
		DOMElement* New_NodeElement = this->Interpretation_Node(SomeSceneNode);

		// STEP 2.2: Add new element to BlackList_STAGE2
		BlackList_STAGE2[SceneNodeName] = New_NodeElement;
	}

	// STEP 3: FILTERING! Evaluate, if element is a child, is a parent and if it's childs or parent's are already created in DOM-structure
	//		   Find out, if element has to be added to WhiteList_STAGE2.
	DOMElement* Evaluate_NodeElement = BlackList_STAGE2[SceneNodeName];

	Ogre::SceneNode* ParentOfSceneNode = SomeSceneNode->getParentSceneNode();
	if (ParentOfSceneNode != 0)
	{
		wxString ParentNameOfSceneNode(ToWxString(ParentOfSceneNode->getName()));

		// Is parent in WL_S1?
		if (WhiteList_STAGE1.count(ParentNameOfSceneNode) == 1)
		{
			// YES -> parent could be(!) in BL_S2
			if (BlackList_STAGE2.count(ParentNameOfSceneNode) == 1)
			{
				// YES -> get parent and add to parent
				DOMElement* Parent = BlackList_STAGE2[ParentNameOfSceneNode];
				Parent->appendChild(Evaluate_NodeElement);
			}
			else
			{
				// NO -> do nothing, could only be in BL_S2, because parent will be added later
			}
		}
		else
		{
			// NO -> add to WL
			WhiteList_STAGE2[SceneNodeName] = Evaluate_NodeElement;
		}
	}
	else
	{
		WhiteList_STAGE2[SceneNodeName] = Evaluate_NodeElement;
	}

	// STEP4 : Handle all childnodes...
	Ogre::SceneNode::ChildNodeIterator ChildIter = SomeSceneNode->getChildIterator();

	while(ChildIter.hasMoreElements())
	{
		Ogre::SceneNode* childNode = static_cast<Ogre::SceneNode*>(ChildIter.getNext());

		if (this->Configuration->doExportNotSelectedChildToo)
		{
			RecursiveNodeTreeWalkthrough(childNode, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2);
		}
		else
		{
			// YES -> if child in BL_S2: stay there, but add child to itself (the parent) too.
			// At least join actual SceneNode with already handled childs from BL_S2
			wxString childNodeName(ToWxString(childNode->getName()));

			if (BlackList_STAGE2.count(childNodeName) == 1)
			{
				// Check if DOMElement alreay added...
				bool Matching_DOMElement = false;

				DOMNodeList* tempDOMChildNodes = Evaluate_NodeElement->getElementsByTagName(ToXMLString("node"));
				if (tempDOMChildNodes->getLength() != 0)
				{
					for(XMLSize_t NodeIterator = 0; NodeIterator < tempDOMChildNodes->getLength(); ++NodeIterator)
					{
						DOMNode* CurrentNode = tempDOMChildNodes->item(NodeIterator);
						if (CurrentNode->getNodeType() == DOMNode::ELEMENT_NODE)
						{
							DOMElement* CurrentElement = dynamic_cast<xercesc::DOMElement*>(CurrentNode);
							if (CurrentElement->hasAttribute(ToXMLString("name")))
							{
								wxString tempDOMChildNodeName(ToWxString(CurrentElement->getAttribute(ToXMLString("name"))));
								if (childNodeName.IsSameAs(tempDOMChildNodeName))  // Check if DOMElement alreay exists...
								{
									Matching_DOMElement = true;
								}
							}
						}
					}
				}

				if (!Matching_DOMElement)
				{
					DOMElement* tempChild = BlackList_STAGE2[childNodeName];
					Evaluate_NodeElement->appendChild(tempChild);
				}
			}
		}
	}

	// Phew! Finished. Me too ;-)
}

