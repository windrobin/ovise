/********************************************************************************
 * Name:      DotSceneInterpreter_OgreToDOM.cpp									*
 * Purpose:   Code implements central methods of it's abstract class,			*
 *			  which provides the basic methods for interpretation of content of *
 *			  ogre-engine as a DOM-structure. In a inherited class all methods	*
 *			  must be implemented.												*
 *			  That garants full compatiblility to dotScene-format.				*
 *			  Here implemented methods is always the same and ensures			*
 *			  interpretation with only one method-call.							*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../OViSEdotSceneBase/DotSceneInterpreter_OgreToDOM.h"

wxString DotSceneInterpreter_OgreToDOM::GetVersionString() { return VersionString; }
DotSceneInterpreter_OgreToDOM::~DotSceneInterpreter_OgreToDOM(void) { }
bool DotSceneInterpreter_OgreToDOM::Interpretation_OgreScene(	wxString PrototypeNativeName,
																QualifiedNameCollection Selection,
																DotSceneBaseConfiguration* Configuration)
{
	wxString LogMsg;

	if (PrototypeNativeName.IsSameAs(ToWxString(""))) PrototypeNativeName = ToWxString("NoName");

	this->Selection  = Selection;
	this->Configuration = Configuration;
	this->SetVersionString(ToWxString("1.0.0"));

	// Get and check Ogre::SceneManager...
	this->SceneMgr = OgreAPIMediator::GetSingletonPtr()->GetSceneManagerPtr(this->Configuration->qSceneManager);
	if (this->SceneMgr == 0) return false; // "Configuration" is invalid!

	// Create DOMImplementation
	this->Implementation = DOMImplementationRegistry::getDOMImplementation(ToXMLString("Core")); // Comment by HR: Core??? Has anyone a list of more valid strings? An enum would be better!

	// Create DOMDocument
	xercesc::DOMDocument* TempDOMDocument = DotSceneInterpreter_OgreToDOM::Implementation->createDocument(0, ToXMLString("scene"), 0); // Don't use any more, but remember: "(XMLString::transcode(this->mDestinationURI.c_str()), XMLString::transcode("scene"), 0)"
	
	// Create new Prototype
	this->Prototype = new ScenePrototype(PrototypeNativeName, TempDOMDocument);

	// Store qualified name of prototype
	this->qPrototype = this->Prototype->GetName();

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
	if (!this->Selection.IsEmpty())
	{
		for (unsigned long IT = 0; IT < this->Selection.Count(); IT++)
		{
			// OLD: OViSESelectionMap uses objects of Ogre::MovableObject and not Ogre::Node or Ogre::SceneNode.
			// OLD: First get these nodes, then find out if a Ogre::Node is a Ogre::SceneNode
			// OLD: Ogre::SceneNodes will be added to WhilteList_STAGE1
			// NEW: Now using qualified names instead!
			QualifiedName qMO = this->Selection[IT];

			// Filter: Only Ogre::Light, Ogre::Cam and Ogre::Entity are handled. Ignore other classes!
			// TODO: Improve to all ogre types (far futhur)
			bool Match = false;
			
			switch(OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableType(qMO))
			{
			case OgreEnums::MovableObject::MOVABLETYPE_Camera: Match = false; break;
			case OgreEnums::MovableObject::MOVABLETYPE_Entity: Match = true; break;
			case OgreEnums::MovableObject::MOVABLETYPE_Light: Match = false; break;
			}

			if (Match)
			{
				// Now get Ogre::MovableObject
				Ogre::MovableObject* MO = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(qMO);
				if ( MO != 0 )
				{
					Ogre::SceneNode* SN = static_cast<Ogre::SceneNode*>(MO->getParentSceneNode());
					WhiteList_STAGE1[ToWxString(SN->getName())] = SN;
				}
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
	// INFO: the litte u... before a variable means "unique name"

	// STEP 1: Convert Ogre::Node to Ogre::SceneNode and get it's (unique) name
	Ogre::SceneNode* SN = static_cast<Ogre::SceneNode*>(SomeNode);
	wxString uSN = ToWxString(SN->getName());

	// STEP 2: If there is a Element with this name in BlackList_STAGE2 do nothing. Else...
	if (BlackList_STAGE2.count(uSN) == 0)
	{
		// STEP 2.1: Create DOM-element "node"
		DOMElement* New_NodeElement = this->Interpretation_Node(SN);

		// STEP 2.2: Add new element to BlackList_STAGE2
		BlackList_STAGE2[uSN] = New_NodeElement;
	}

	// STEP 3: FILTERING! Evaluate, if element is a child, is a parent and if it's childs or parent's are already created in DOM-structure
	//		   Find out, if element has to be added to WhiteList_STAGE2.
	DOMElement* Evaluate_NodeElement = BlackList_STAGE2[uSN];

	Ogre::SceneNode* ParentSN = SN->getParentSceneNode();
	if (ParentSN != 0)
	{
		wxString uParentSN(ToWxString(ParentSN->getName()));

		// Is parent in WL_S1?
		if (WhiteList_STAGE1.count(uParentSN) == 1)
		{
			// YES -> parent could be(!) in BL_S2
			if (BlackList_STAGE2.count(uParentSN) == 1)
			{
				// YES -> get parent and add to parent
				DOMElement* Parent = BlackList_STAGE2[uParentSN];
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
			WhiteList_STAGE2[uSN] = Evaluate_NodeElement;
		}
	}
	else
	{
		WhiteList_STAGE2[uSN] = Evaluate_NodeElement;
	}

	// STEP4 : Handle all childnodes...
	Ogre::SceneNode::ChildNodeIterator ChildIter = SN->getChildIterator();

	while(ChildIter.hasMoreElements())
	{
		Ogre::SceneNode* ChildSN = static_cast<Ogre::SceneNode*>(ChildIter.getNext());

		if (this->Configuration->doExportNotSelectedChildToo)
		{
			RecursiveNodeTreeWalkthrough(ChildSN, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2);
		}
		else
		{
			// YES -> if child in BL_S2: stay there, but add child to itself (the parent) too.
			// At least join actual SceneNode with already handled childs from BL_S2
			wxString uChildSN(ToWxString(ChildSN->getName()));

			if (BlackList_STAGE2.count(uChildSN) == 1)
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
								if (uChildSN.IsSameAs(tempDOMChildNodeName))  // Check if DOMElement alreay exists...
								{
									Matching_DOMElement = true;
								}
							}
						}
					}
				}

				if (!Matching_DOMElement)
				{
					DOMElement* tempChild = BlackList_STAGE2[uChildSN];
					Evaluate_NodeElement->appendChild(tempChild);
				}
			}
		}
	}

	// Phew! Finished. Me too ;-)
}

