#include "OViSEXmlManager.h"

OViSEXmlManager::OViSEXmlManager(wxString URLofXSD, wxString URLofExportPath) : mValid(true)
{
	this->mCopyThisMeshFiles.Clear();

	this->mURLofExportPath = wxFileName(URLofExportPath);
	this->mURLofExportPath.SetName(ToWxString(""));
	this->mURLofExportPath.SetEmptyExt();

	this->mURLofXSD = wxFileName(URLofXSD);

	if (!wxFileName::FileExists(this->mURLofXSD.GetFullPath())) this->mValid = false;
	if (!wxFileName::DirExists(this->mURLofXSD.GetPath())) this->mValid = false;

	if (this->mValid)
	{
		this->mValid = this->InitXML();
	}
}

OViSEXmlManager::~OViSEXmlManager(void)
{
	this->mValid = this->TerminateXML();

	if (this->mImplementation != 0) delete this->mImplementation;
	if (this->mDocType != 0)
	{
		this->mDocType->release();
		if (this->mDocType != 0) delete this->mDocType;
	}
	if (this->mDocument != 0)
	{
		this->mDocument->release();
		if (this->mDocument != 0) delete this->mDocument;
	}

	if (this->mParser != 0) delete this->mParser;
	if (this->mErrHandler != 0) delete this->mErrHandler;
}

bool OViSEXmlManager::IsValid()
{
	bool ReturnValue = true;

	// Do check...
	ReturnValue = this->mValid; // TODO

	return ReturnValue;
}

bool OViSEXmlManager::InitXML()
{
	wxString ParsingMsg;

	try
	{
		// Initialize Xerces
		XMLPlatformUtils::Initialize();
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("OViSE XML Manager: *** XERCES initialized. ***");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
	}
	catch (const XMLException& e) 
	{
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("OViSE XML Manager: *** Error, while initializing XERCES! Exception message is: ") << ToWxString(e.getMessage());
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
		return false;
	}
	
	return true;
}

bool OViSEXmlManager::TerminateXML()
{
	wxString ParsingMsg;

    try
   	{
		// Terminate Xerces
    	XMLPlatformUtils::Terminate();  
		ParsingMsg.Clear();
		ParsingMsg << ToWxString(": *** XERCES terminated. ***");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
   	}
   	catch( xercesc::XMLException& e )
   	{
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("OViSE XML Manager: *** Error, while terminating XERCES! Exception message is: ") << ToWxString(e.getMessage());
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
		return false;
	}

	return true;
}

xercesc::DOMDocument* OViSEXmlManager::ImportScene(wxString URLofXML)
{
	if (!this->IsValid()) return 0;
	if (!wxFileName::FileExists(URLofXML)) return 0;

	// Setup XML-parser
	this->mParser = new XercesDOMParser();
    this->mParser->setValidationScheme(XercesDOMParser::Val_Always);    
    this->mParser->setDoNamespaces(true); 
	this->mParser->setDoSchema(true); // <- important, when a .XSD is used!!!
	this->mParser->setExternalNoNamespaceSchemaLocation(ToXMLString(this->mURLofXSD.GetFullPath()));

	// OViSEXercesXMLErrorReporter inherits from "xercesc::ErrorHandler" and redirects parsing-errors into Ogre::LogManager
	this->mErrHandler = (xercesc::ErrorHandler*) new OViSEXercesXMLErrorReporter();
	this->mParser->setErrorHandler(this->mErrHandler);

	wxString ParsingMsg;
	bool ErrorsOccured = false;

	ParsingMsg.Clear();
	ParsingMsg << ToWxString("OViSE XML Manager: Parsing file \"") << URLofXML + ToWxString("\"... ");

    try 
    {
        mParser->parse(ToXMLString(URLofXML));

		ParsingMsg << ToWxString("done!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
    }
    catch (const XMLException& e) 
    {
		ParsingMsg << ToWxString("failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

		ParsingMsg.Clear();
		ParsingMsg << ToWxString("OViSE XML Manager: XERCES's exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
    }
    catch (const DOMException& e) 
    {
		ParsingMsg << ToWxString("failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("OViSE XML Manager: XERCES's exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
    }
	catch (const SAXException& e) 
    {
		ParsingMsg << ToWxString("failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("OViSE XML Manager: XERCES's exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
    }
	catch (std::exception e) 
    {
		ParsingMsg << ToWxString("failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
		ParsingMsg << ToWxString("OViSE XML Manager: XERCES's exception message is: ") << ToWxString(e.what());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

		ErrorsOccured = true;
    }
    catch (...) 
    {
		ParsingMsg << ToWxString("failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("OViSE XML Manager: Unexpected Exception occured, while pharsing with XERCES!");
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

		ErrorsOccured = true;
    }
    
	// Returns pointer to DOMDocument, if no errors occured while validation.
	// REMEMBER: These errors are no exceptions like in those cases below.
    if (!((OViSEXercesXMLErrorReporter*) this->mErrHandler)->HasValidationErrors()) ErrorsOccured = true;
	
	delete mParser;
    delete mErrHandler;

	if (ErrorsOccured) return 0;
	else return this->mParser->getDocument();
}

void OViSEXmlManager::CopyOgreSceneToDOM(Ogre::SceneManager* SceneMgr, OViSESelectionMap Selection, bool doExportNotSelectedChildToo)
{
	// CONVENTION: all names of objects are unique in Ogre, Xerces and WX !

	this->mCopyThisMeshFiles.Clear();
	this->mExportThisMeshsToFiles.clear();

	this->mImplementation = DOMImplementationRegistry::getDOMImplementation(ToXMLString("Core")); // Kommentar von HR: Core??? Welche Strings gehen hin noch rein? Enum wäre besser!
	this->mDocument = this->mImplementation->createDocument(0, ToXMLString("scene"), 0); // Don't use any more, but remember: "(XMLString::transcode(this->mDestinationURI.c_str()), XMLString::transcode("scene"), 0)"
	
	// Get "scene"-element and add attribute "formatVersion"...
	DOMElement* SceneElement = this->mDocument->getDocumentElement();
	SceneElement->setAttribute(ToXMLString("formatVersion"), ToXMLString("1.0.0"));

	// Create "nodes"-element and append to "scene"-element...
	DOMElement* NodesElement = this->mDocument->createElement(ToXMLString("nodes"));
	SceneElement->appendChild(NodesElement);

	// Recusive: get nodes from Ogre::SceneManager, create "node"-elements and append 'em to "nodes"-element or parent "node"-elements...
	// Get one (now root) node, and start recursive walkthrough...

	// SceneNode-Filtering! Status now: WhilteList_STAGE1
	// Export only selected SceneNodes. Using DOM-API for a easy and fast handling...	
	HashMap_OgreSceneNodePointer WhiteList_STAGE1; // List of Ogre::MoveableObejcts
	HashMap_DOMPointer WhiteList_STAGE2; // List of nodes/DOMElements
	HashMap_DOMPointer BlackList_STAGE2; // List of already created nodes/DOMElements
	
	if (!Selection.empty())
	{
		// 1) Get list of selected SceneNodes (WhilteList_STAGE1)
		for (OViSESelectionMap::const_iterator iter = Selection.begin(); iter != Selection.end(); iter++)
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
				WhiteList_STAGE1[wxString(tempSceneNode->getName().c_str(), wxConvUTF8)] = tempSceneNode;
			}
		}

		// 2) Generate Stage 2 WhiteList
		if (!WhiteList_STAGE1.empty())
		{
			for(HashMap_OgreSceneNodePointer::iterator iter = WhiteList_STAGE1.begin(); iter != WhiteList_STAGE1.end(); iter++)
			{
				this->RecursiveNodeTreeWalkthrough(iter->second, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2, doExportNotSelectedChildToo);
			}
		}
	}
	else
	{
		// Add RootSceneNode, when there aren't any choosen SceneNodes...
		Ogre::SceneNode* tempSceneNode = SceneMgr->getRootSceneNode();
		WhiteList_STAGE1[ToWxString(tempSceneNode->getName())] = tempSceneNode;

		// 2) Generate Stage 2 WhiteList
		this->RecursiveNodeTreeWalkthrough(WhiteList_STAGE1.begin()->second, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2, doExportNotSelectedChildToo);
	}

	if (!WhiteList_STAGE2.empty())
	{
		for(HashMap_DOMPointer::iterator iter = WhiteList_STAGE2.begin(); iter != WhiteList_STAGE2.end(); iter++)
		{
			NodesElement->appendChild(iter->second);
		}
	}
}


void OViSEXmlManager::RecursiveNodeTreeWalkthrough(Ogre::Node* actualNode, HashMap_OgreSceneNodePointer& WhiteList_STAGE1, HashMap_DOMPointer& WhiteList_STAGE2, HashMap_DOMPointer& BlackList_STAGE2, bool doExportNotSelectedChildToo)
{
	// CONVENTION: all name of objects are uniqu in Ogre, Xerces and WX !

	Ogre::SceneNode* actualSceneNode = static_cast<Ogre::SceneNode*>(actualNode);
	wxString tempSceneNodeName(actualSceneNode->getName().c_str(), wxConvUTF8);

	if (BlackList_STAGE2.count(tempSceneNodeName) == 0)
	{
		Ogre::Vector3 tempPosition = actualSceneNode->getPosition();
		Ogre::Quaternion tempQuaternion = actualSceneNode->getOrientation();
		Ogre::Vector3 tempScale = actualSceneNode->getScale();

		// Data of DOM-element "node"
		DOMElement* New_NodeElement = this->mDocument->createElement(ToXMLString("node"));
		New_NodeElement->setAttribute(XMLString::transcode("name"), ToXMLString(actualSceneNode->getName()));

		// Create general data-elements of new node: "position", "quaternion" & "scale"
		DOMElement* New_PositionElement = this->mDocument->createElement(ToXMLString("position"));
		New_PositionElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(tempPosition.x)));
		New_PositionElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(tempPosition.y)));
		New_PositionElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(tempPosition.z)));

		DOMElement* New_QuaternionElement = this->mDocument->createElement(ToXMLString("quaternion"));	
		New_QuaternionElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(tempQuaternion.x)));
		New_QuaternionElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(tempQuaternion.y)));
		New_QuaternionElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(tempQuaternion.z)));
		New_QuaternionElement->setAttribute(ToXMLString("w"), ToXMLString(Ogre::StringConverter::toString(tempQuaternion.w)));
		
		DOMElement* New_ScaleElement = this->mDocument->createElement(ToXMLString("scale"));
		New_ScaleElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(tempScale.x)));
		New_ScaleElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(tempScale.y)));
		New_ScaleElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(tempScale.z)));

		// Attach "position", "quaternion" & "scale"
		New_NodeElement->appendChild(New_PositionElement);
		New_NodeElement->appendChild(New_QuaternionElement);
		New_NodeElement->appendChild(New_ScaleElement);

		// Create special data-elements of new node ("camera", "light" & "entity")
		Ogre::SceneNode::ObjectIterator ObjIter = actualSceneNode->getAttachedObjectIterator();
		Ogre::MovableObject* MovObj;

		while(ObjIter.hasMoreElements())
		{
			MovObj = ObjIter.getNext();
			bool match = false;
			
			if (MovObj->getMovableType() == "Camera")
			{
				// Ignored, H.R. 18.03.09
				match = false;		
			}

			if (MovObj->getMovableType() == "Entity") // TODO: simplify processing of relacing.
			{
				match = true;

				// 1) Cast movable object to Ogre::Entity
				Ogre::Entity* tempEntity = static_cast<Ogre::Entity*>(MovObj);

				// 2) Get full path of meshfile
				wxFileName tempMeshFullPath(ToWxString(tempEntity->getMesh()->getName()));

				// 3) Create appropriate DOMElement for entity
				DOMElement* New_EntityElement = this->mDocument->createElement(ToXMLString("entity"));	
				New_EntityElement->setAttribute(ToXMLString("name"), ToXMLString(tempEntity->getName()));
				New_EntityElement->setAttribute(ToXMLString("meshFile"), ToXMLString(tempMeshFullPath.GetFullName()));
				
				// Attach special data-element
				New_NodeElement->appendChild(New_EntityElement);

				// 4) Prepare copy/export of meshfile: Can the used *.mesh be located in filesystem?
				if(wxFileExists(tempMeshFullPath.GetFullPath()))
				{
					// Yes: prepare to copy it, place it in the copy-list!
					this->mCopyThisMeshFiles.Add(tempMeshFullPath.GetFullPath());
				}
				else
				{
					// No: prepare to export from memory to filesystem, place it into the export-list!
					this->mExportThisMeshsToFiles.push_back(tempEntity->getMesh());
				}
			}

			if (MovObj->getMovableType() == "Light")
			{
				// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
				match = true;
				Ogre::Light* tempLight = static_cast<Ogre::Light*>(MovObj);

				DOMElement* New_LightElement = this->mDocument->createElement(ToXMLString("light"));
				New_LightElement->setAttribute(ToXMLString("name"), ToXMLString(tempLight->getName()));

				if (tempLight->getType() == Ogre::Light::LT_DIRECTIONAL)
				{
					New_LightElement->setAttribute(ToXMLString("type"), ToXMLString("directional"));
					// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
				}

				if (tempLight->getType() == Ogre::Light::LT_POINT)
				{			
					Ogre::ColourValue tempDiffuseColour = tempLight->getDiffuseColour();
					Ogre::ColourValue tempSpecularColour = tempLight->getSpecularColour();

					DOMElement* New_DiffuseColourElement = this->mDocument->createElement(ToXMLString("colourDiffuse"));			
					New_DiffuseColourElement->setAttribute(ToXMLString("r"), ToXMLString(Ogre::StringConverter::toString(tempDiffuseColour.r)));
					New_DiffuseColourElement->setAttribute(ToXMLString("g"), ToXMLString(Ogre::StringConverter::toString(tempDiffuseColour.g)));
					New_DiffuseColourElement->setAttribute(ToXMLString("b"), ToXMLString(Ogre::StringConverter::toString(tempDiffuseColour.b)));

					DOMElement* New_SpecularColourElement = this->mDocument->createElement(ToXMLString("colourSpecular"));	
					New_SpecularColourElement->setAttribute(ToXMLString("r"), ToXMLString(Ogre::StringConverter::toString(tempSpecularColour.r)));
					New_SpecularColourElement->setAttribute(ToXMLString("g"), ToXMLString(Ogre::StringConverter::toString(tempSpecularColour.g)));
					New_SpecularColourElement->setAttribute(ToXMLString("b"), ToXMLString(Ogre::StringConverter::toString(tempSpecularColour.b)));
				
					// Attach detail-elements
					New_LightElement->setAttribute(ToXMLString("type"), ToXMLString("point"));
					New_LightElement->appendChild(New_DiffuseColourElement);
					New_LightElement->appendChild(New_SpecularColourElement);
				}

				if (tempLight->getType() == Ogre::Light::LT_SPOTLIGHT)
				{
					New_LightElement->setAttribute(ToXMLString("type"), ToXMLString("spotLight"));
					// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
				}

				// Attach special data-element
				New_NodeElement->appendChild(New_LightElement);
			}	
			if (!match)
			{
				break;
			}
		}

		// Attach final element to BlackList_STAGE2 & WhiteList_STAGE2
		// Add to BlackList_STAGE2
		BlackList_STAGE2[tempSceneNodeName] = New_NodeElement;
	}

	// FILTERING: Evaluate, if emelnmt is a child, a parent and if childs or parend are already created in DOM-structure
	DOMElement* Evaluate_NodeElement = BlackList_STAGE2[tempSceneNodeName];

	// Add to WhiteList_STAGE2
	Ogre::SceneNode* parentOfSceneNode = actualSceneNode->getParentSceneNode();
	if (parentOfSceneNode != 0)
	{
		// 1) Parent in WL_S1?
		wxString parentNameOfSceneNode(ToWxString(parentOfSceneNode->getName()));

		if (WhiteList_STAGE1.count(parentNameOfSceneNode) == 1)
		{
			// 1.1) JA -> parent könnte(!) in BL_S2 sein
			if (BlackList_STAGE2.count(parentNameOfSceneNode) == 1)
			{
				// 1.1.1) JA -> parent holen, zum parent hinzufügen
				DOMElement* tempParent = BlackList_STAGE2[parentNameOfSceneNode];
				tempParent->appendChild(Evaluate_NodeElement);
			}
			else
			{
				// 1.1.2) NEIN -> nix machen, nur in der BL_S2 sein, denn der parent kommt später noch dazu
			}
		}
		else
		{
			// 1.2) NEIN -> zu WL hinzufügen
			WhiteList_STAGE2[tempSceneNodeName] = Evaluate_NodeElement;
		}
	}
	else
	{
		WhiteList_STAGE2[tempSceneNodeName] = Evaluate_NodeElement;
	}

	// Handle all childnodes...
	Ogre::SceneNode::ChildNodeIterator ChildIter = actualSceneNode->getChildIterator();
	while(ChildIter.hasMoreElements())
	{
		Ogre::SceneNode* childNode = static_cast<Ogre::SceneNode*>(ChildIter.getNext());
		if (doExportNotSelectedChildToo)
		{
			this->RecursiveNodeTreeWalkthrough(childNode, WhiteList_STAGE1, WhiteList_STAGE2, BlackList_STAGE2, doExportNotSelectedChildToo);
		}
		else
		{
			// 2.1) JA -> wenn child in BL_S2: dort lassen - aber child auch sich selbst(dem parent) hinzufügen
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
								//std::string tempName = ;
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
}


/*void dotSceneXmlWriter::copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr)
{
	this->mCopyThisMeshFiles.Clear();
	this->mExportThisMeshsToFiles.clear();

	this->mImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
	// Kommentar von HR: Core??? Welche String gehen hin noch rein? Enum wäre besser!
	this->mDocument = this->mImplementation->createDocument(0, XMLString::transcode("scene"), 0); // Don't use, but remember: "(XMLString::transcode(this->mDestinationURI.c_str()), XMLString::transcode("scene"), 0)"
	
	// Get "scene"-element and add attribute "formatVersion"...
	DOMElement* SceneElement = this->mDocument->getDocumentElement();
	SceneElement->setAttribute(XMLString::transcode("formatVersion"), XMLString::transcode("1.0.0"));

	// Create "nodes"-element and append to "scene"-element...
	DOMElement* NodesElement = this->mDocument->createElement(XMLString::transcode("nodes"));
	SceneElement->appendChild(NodesElement);

	// Recusive: get nodes from Ogre::SceneManager, create "node"-elements and append 'em to "nodes"-element or parent "node"-elements...
	// Get one (now root) node, and start recursive walkthrough...
	Testausgabe.open("C:\\Testausgabe.txt", std::ios::out|std::ios::trunc);
	this->recursiveNodeTreeWalkthrough(SceneMgr->getRootSceneNode(), NodesElement);
	Testausgabe.close();
}*/

/*
void dotSceneXmlWriter::recursiveNodeTreeWalkthrough(Ogre::Node* actualNode, DOMElement* ActualDOMParent)
{
	Ogre::SceneNode* actualSceneNode = (Ogre::SceneNode*) actualNode;
	Ogre::Vector3 tempPosition = actualSceneNode->getPosition();
	Ogre::Quaternion tempQuaternion = actualSceneNode->getOrientation();
	Ogre::Vector3 tempScale = actualSceneNode->getScale();

	// Data of DOM-element "node"
	DOMElement* New_NodeElement = this->mDocument->createElement(XMLString::transcode("node"));
	ActualDOMParent->appendChild(New_NodeElement);
	New_NodeElement->setAttribute(XMLString::transcode("name"), XMLString::transcode(actualSceneNode->getName().c_str()));

	// General data-elements of new node ("position", "quaternion" & "scale")
	DOMElement* New_PositionElement = this->mDocument->createElement(XMLString::transcode("position"));
	New_NodeElement->appendChild(New_PositionElement);
	New_PositionElement->setAttribute(XMLString::transcode("x"), XMLString::transcode(Ogre::StringConverter::toString(tempPosition.x).c_str()));
	New_PositionElement->setAttribute(XMLString::transcode("y"), XMLString::transcode(Ogre::StringConverter::toString(tempPosition.y).c_str()));
	New_PositionElement->setAttribute(XMLString::transcode("z"), XMLString::transcode(Ogre::StringConverter::toString(tempPosition.z).c_str()));

	DOMElement* New_QuaternionElement = this->mDocument->createElement(XMLString::transcode("quaternion"));
	New_NodeElement->appendChild(New_QuaternionElement);
	New_QuaternionElement->setAttribute(XMLString::transcode("x"), XMLString::transcode(Ogre::StringConverter::toString(tempQuaternion.x).c_str()));
	New_QuaternionElement->setAttribute(XMLString::transcode("y"), XMLString::transcode(Ogre::StringConverter::toString(tempQuaternion.y).c_str()));
	New_QuaternionElement->setAttribute(XMLString::transcode("z"), XMLString::transcode(Ogre::StringConverter::toString(tempQuaternion.z).c_str()));
	New_QuaternionElement->setAttribute(XMLString::transcode("w"), XMLString::transcode(Ogre::StringConverter::toString(tempQuaternion.w).c_str()));

	DOMElement* New_ScaleElement = this->mDocument->createElement(XMLString::transcode("scale"));
	New_NodeElement->appendChild(New_ScaleElement);
	New_ScaleElement->setAttribute(XMLString::transcode("x"), XMLString::transcode(Ogre::StringConverter::toString(tempScale.x).c_str()));
	New_ScaleElement->setAttribute(XMLString::transcode("y"), XMLString::transcode(Ogre::StringConverter::toString(tempScale.y).c_str()));
	New_ScaleElement->setAttribute(XMLString::transcode("z"), XMLString::transcode(Ogre::StringConverter::toString(tempScale.z).c_str()));

	// Special data-elements of new node ("camera", "light" & "entity")
	Ogre::SceneNode::ObjectIterator ObjIter = actualSceneNode->getAttachedObjectIterator();
	Ogre::MovableObject* MovObj;

	while(ObjIter.hasMoreElements())
	{
		MovObj = ObjIter.getNext();
		bool match = false;
		
		if (MovObj->getMovableType() == "Camera")
		{
			// Ignored, H.R. 18.03.09
			match = false;		
		}
		if (MovObj->getMovableType() == "Entity") // TODO: simplify processing of relacing.
		{
			match = true;

			// 1) Cast movable object to Ogre::Entity
			Ogre::Entity* tempEntity = static_cast<Ogre::Entity*>(MovObj);

			// 2) Get full path of meshfile
			wxFileName tempMeshFullPath(wxString(tempEntity->getMesh()->getName().c_str(), wxConvUTF8));

			// 3) Create appropriate DOMElement for entity
			DOMElement* New_EntityElement = this->mDocument->createElement(XMLString::transcode("entity"));
			New_NodeElement->appendChild(New_EntityElement);
			New_EntityElement->setAttribute(XMLString::transcode("name"), XMLString::transcode(tempEntity->getName().c_str()));
			New_EntityElement->setAttribute(XMLString::transcode("meshFile"), XMLString::transcode(std::string(tempMeshFullPath.GetFullName().mb_str()).c_str()));

			// 4) Prepare copy/export of meshfile: Can the used *.mesh be located in filesystem?
			if(wxFileExists(tempMeshFullPath.GetFullPath()))
			{
				// Yes: prepare to copy it, place it in the copy-list!
				this->mCopyThisMeshFiles.Add(tempMeshFullPath.GetFullPath());
			}
			else
			{
				// No: prepare to export from memory to filesystem, place it into the export-list!
				this->mExportThisMeshsToFiles.push_back(tempEntity->getMesh());
			}
		}
		if (MovObj->getMovableType() == "Light")
		{
			// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
			match = true;
			Ogre::Light* tempLight = static_cast<Ogre::Light*>(MovObj);

			DOMElement* New_LightElement = this->mDocument->createElement(XMLString::transcode("light"));
			New_NodeElement->appendChild(New_LightElement);
			New_LightElement->setAttribute(XMLString::transcode("name"), XMLString::transcode(tempLight->getName().c_str()));

			if (tempLight->getType() == Ogre::Light::LT_DIRECTIONAL)
			{
				Testausgabe << "Ogre::Light '" << tempLight->getName() << "' of type '" << "directional" << "'" << std::endl;

				New_LightElement->setAttribute(XMLString::transcode("type"), XMLString::transcode("directional"));
				// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
			}

			if (tempLight->getType() == Ogre::Light::LT_POINT)
			{
				New_LightElement->setAttribute(XMLString::transcode("type"), XMLString::transcode("point"));
				Ogre::ColourValue tempDiffuseColour = tempLight->getDiffuseColour();
				Ogre::ColourValue tempSpecularColour = tempLight->getSpecularColour();

				Testausgabe << "Ogre::Light '" << tempLight->getName() << "' of type '" << "point" << "'" << std::endl;
				Testausgabe << "DiffuseColour (" << tempDiffuseColour.r << ", " << tempDiffuseColour.g << ", " << tempDiffuseColour.b << ")" << std::endl;
				Testausgabe << "SpecularColour (" << tempSpecularColour.r << ", " << tempSpecularColour.g << ", " << tempSpecularColour.b << ")" << std::endl;

				DOMElement* New_DiffuseColourElement = this->mDocument->createElement(XMLString::transcode("colourDiffuse"));
				New_LightElement->appendChild(New_DiffuseColourElement);
				New_DiffuseColourElement->setAttribute(XMLString::transcode("r"), XMLString::transcode(Ogre::StringConverter::toString(tempDiffuseColour.r).c_str()));
				New_DiffuseColourElement->setAttribute(XMLString::transcode("g"), XMLString::transcode(Ogre::StringConverter::toString(tempDiffuseColour.g).c_str()));
				New_DiffuseColourElement->setAttribute(XMLString::transcode("b"), XMLString::transcode(Ogre::StringConverter::toString(tempDiffuseColour.b).c_str()));

				DOMElement* New_SpecularColourElement = this->mDocument->createElement(XMLString::transcode("colourSpecular"));
				New_LightElement->appendChild(New_SpecularColourElement);
				New_SpecularColourElement->setAttribute(XMLString::transcode("r"), XMLString::transcode(Ogre::StringConverter::toString(tempSpecularColour.r).c_str()));
				New_SpecularColourElement->setAttribute(XMLString::transcode("g"), XMLString::transcode(Ogre::StringConverter::toString(tempSpecularColour.g).c_str()));
				New_SpecularColourElement->setAttribute(XMLString::transcode("b"), XMLString::transcode(Ogre::StringConverter::toString(tempSpecularColour.b).c_str()));
			}

			if (tempLight->getType() == Ogre::Light::LT_SPOTLIGHT)
			{
				Testausgabe << "Ogre::Light '" << tempLight->getName() << "' of type '" << "spotLight" << "'" << std::endl;

				New_LightElement->setAttribute(XMLString::transcode("type"), XMLString::transcode("spotLight"));
				// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
			}
		}	
		if (!match)
		{
			Testausgabe << "Not handled movable object. Name: '" << MovObj->getName() << "' Type: '" << MovObj->getMovableType() << "'" << std::endl;
			break;
		}
	}

	Ogre::Node::ChildNodeIterator ChildIter = actualNode->getChildIterator();
	while(ChildIter.hasMoreElements()) recursiveNodeTreeWalkthrough(ChildIter.getNext(), New_NodeElement);
}
*/
void OViSEXmlManager::MoveDOMToXML(wxFileName filename, bool doExportMeshFiles)
{
	// Write DOM-structure to *.xml file!
	DOMLSSerializer* tempLSServializer = this->mImplementation->createLSSerializer();
	tempLSServializer->writeToURI(this->mDocument, XMLString::transcode(filename.GetFullPath().mb_str()));

	if (doExportMeshFiles)
	{
		// Export meshfiles
		Ogre::MeshSerializer tempSerializer;
		while(!this->mExportThisMeshsToFiles.empty())
		{
			// First: Get pointer to mesh in memory!
			Ogre::MeshPtr tempMeshPtr = this->mExportThisMeshsToFiles.back();

			// Use full path of *.xml (dotScene-XML) file...
			wxFileName tempModifiedFileName(filename);

			// ...to modify it with full filename of futher *.mesh file!
			tempModifiedFileName.SetFullName(ToWxString(tempMeshPtr.get()->getName()));

			// Use the modified full path to export *.mesh there. 
			tempSerializer.exportMesh(tempMeshPtr.getPointer(), ToOgreString(tempModifiedFileName.GetFullPath()));

			// Last: Done. Remove pointer of exported mesh!
			this->mExportThisMeshsToFiles.pop_back();
		}

		// Copy meshfiles
		while(!this->mCopyThisMeshFiles.IsEmpty())
		{
			// First: Define location of source file...
			wxFileName Source(this->mCopyThisMeshFiles.Last());	
			
			// ...then define location of destination file...
			wxFileName Target(Source);

			// ...by using the path of *.xml (dotScene-XML) file!
			Target.SetPath(filename.GetPath());

			// Finally copy file!
			// TODO: overwrite-options?
			wxCopyFile(Source.GetFullPath(), Target.GetFullPath(), doExportMeshFiles);

			// Last: Done. Remove filename from list!
			this->mCopyThisMeshFiles.pop_back();
		}
	}
}

bool OViSEXmlManager::ExportScene(Ogre::SceneManager* HostingSceneMgr, OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo = true,  bool doExportMeshFiles = true)
{
	// Check, if FullPathOfExportedDotSceneXML is possible...
	wxFileName TempDestination(DestinationOfSceneXML);
	if (!wxFileName::DirExists(TempDestination.GetPath())) return false;
	if (!TempDestination.GetExt().IsSameAs(ToWxString("xml")))
	{
		wxString debug_test = TempDestination.GetExt(); // DEBUG LINE
		return false;
	}

	this->CopyOgreSceneToDOM(HostingSceneMgr, Selection, doExportNotSelectedChildsToo);
	this->MoveDOMToXML(DestinationOfSceneXML, doExportMeshFiles);

	return true;
}