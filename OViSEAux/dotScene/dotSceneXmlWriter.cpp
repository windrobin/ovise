#include "dotSceneXmlWriter.h"

dotSceneXmlWriter::dotSceneXmlWriter(OViSEPathProvider* PathProvider)
{
	this->Valid = true;
	this->mCopyThisMeshFiles.Clear();
	this->mPathProvider = PathProvider;

	if (this->mPathProvider != 0)
	{
		this->mDotSceneXsd = wxFileName(this->mPathProvider->getPath_MediaDirectory() + wxT("/data"), wxString(wxT("dotScene.xsd")));

		try
		{
			XMLPlatformUtils::Initialize();
			std::cout << "*** Xerces initialised. ***\n";
		}
		catch (const XMLException& toCatch) 
		{
			char* message = XMLString::transcode(toCatch.getMessage());
			std::string errmsg = "XERCES: Error during initialization! :\n" + (std::string)message + "\n";
			Ogre::LogManager::getSingletonPtr()->logMessage(errmsg, Ogre::LML_CRITICAL);
			XMLString::release(&message);
		}
	}
}

dotSceneXmlWriter::~dotSceneXmlWriter(void)
{
	try
   	{
    	XMLPlatformUtils::Terminate();  // Terminate Xerces
   	}
   	catch( xercesc::XMLException& e )
   	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		std::string lgMsg = "Xerces: " + (std::string)message;
		Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg.c_str(), Ogre::LML_CRITICAL);
		XMLString::release( &message );
	}	   
}


bool dotSceneXmlWriter::IsValid()
{
	bool ReturnValue = true;

	// Do check...

	return ReturnValue;
}

void dotSceneXmlWriter::copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr)
{
	this->mCopyThisMeshFiles.Clear();
	this->mExportThisMeshsToFiles.clear();

	this->mImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
	// Kommentar von HR: Core??? Welche String gehen hin noch rein? Enum wäre besser!
	this->mDocument = this->mImplementation->createDocument(/*XMLString::transcode(this->mDestinationURI.c_str())*/0, XMLString::transcode("scene"), 0);
	
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
}

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

void dotSceneXmlWriter::moveDOMToXML(wxFileName filename, bool doExportMeshFiles)
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
			tempModifiedFileName.SetFullName(wxString(tempMeshPtr.get()->getName().c_str(), wxConvUTF8));

			// Use the modified full path to export *.mesh there. 
			tempSerializer.exportMesh(tempMeshPtr.getPointer(), (std::string)tempModifiedFileName.GetFullPath().mb_str());

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

