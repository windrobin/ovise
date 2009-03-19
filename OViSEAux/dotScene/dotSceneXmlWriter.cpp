#include "dotSceneXmlWriter.h"



void dotSceneXmlWriter::copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr)
{
	this->mImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
	// Kommentar von HR: Core??? Welche String gehen hin noch rein? Enum wäre besser!
	
	this->mDocument = this->mImplementation->createDocument(0, XMLString::transcode("scene"), 0);
	
	// Get "scene"-element and add attribute "formatVersion"...
	DOMElement *SceneElement = this->mDocument->getDocumentElement();
	SceneElement->setAttribute(XMLString::transcode("formatVersion"), XMLString::transcode("1.0.0"));

	// Create "nodes"-element and append to "scene"-element...
	DOMElement* NodesElement = this->mDocument->createElement(XMLString::transcode("nodes"));
	SceneElement->appendChild(NodesElement);

	// Recusive: get nodes from Ogre::SceneManager, create "node"-elements and append 'em to "nodes"-element or parent "node"-elements...

	// Get one (now root) node, and start recursive walkthrough...
	Testausgabe.open("C:\\Testausgabe.txt", std::ios::out|std::ios::trunc);
	this->recursiveNodeTreeWalkthrough(SceneMgr->getRootSceneNode());
	Testausgabe.close();
}

void dotSceneXmlWriter::recursiveNodeTreeWalkthrough(Ogre::Node* actualNode)
{
	this->mDocument->getElementsByTagName("nodes");
	Ogre::SceneNode* actualSceneNode = (Ogre::SceneNode*) actualNode;
	Testausgabe << "-----" << actualSceneNode->getName() << "-----" << std::endl;
	Ogre::Vector3 tempPosition = actualSceneNode->getPosition();
	Ogre::Quaternion tempQuaternion = actualSceneNode->getOrientation();
	Ogre::Vector3 tempScale = actualSceneNode->getScale();
	Testausgabe << "Ogre::Position (" << tempPosition.x << ", " << tempPosition.y << ", " << tempPosition.z << ")" << std::endl;
	Testausgabe << "Ogre::Quaternion (" << tempQuaternion.w << ", " << tempQuaternion.x << ", " << tempQuaternion.y << ", " << tempQuaternion.z << ")" << std::endl;
	Testausgabe << "Ogre::Scale (" << tempScale.x << ", " << tempScale.y << ", " << tempScale.z << ")" << std::endl;


	Ogre::SceneNode::ObjectIterator ObjIter = actualSceneNode->getAttachedObjectIterator();
	Ogre::MovableObject* MovObj;
	while(ObjIter.hasMoreElements())
	{
		MovObj = ObjIter.getNext();

		Ogre::Entity* tempEntity;
		Ogre::Light* tempLight;

		bool match = false;
		
		if (MovObj->getMovableType() == "Camera")
		{
			// Ignored, H.R. 18.03.09
			match = false;		
		}
		if (MovObj->getMovableType() == "Entity")
		{
			match = true;
			tempEntity = static_cast<Ogre::Entity*>(MovObj);
			Testausgabe << "Ogre::Entity '" << tempEntity->getName() << "' with MESH-file '" << tempEntity->getMesh()->getName() << "'" << std::endl;
		}
		if (MovObj->getMovableType() == "Light")
		{
			// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
			match = true;
			tempLight = static_cast<Ogre::Light*>(MovObj);

			Ogre::String tempLightTypeName;
			switch(tempLight->getType())
			{
			case Ogre::Light::LT_DIRECTIONAL:	tempLightTypeName = "directional";	break;
			case Ogre::Light::LT_POINT:			tempLightTypeName = "point";		break;
			case Ogre::Light::LT_SPOTLIGHT:		tempLightTypeName = "spotLight";	break;
			}

			Ogre::ColourValue tempDiffuseColour = tempLight->getDiffuseColour();
			Ogre::ColourValue tempSpecularColour = tempLight->getSpecularColour();

			Testausgabe << "Ogre::Light '" << tempLight->getName() << "' of type '" << tempLightTypeName << "'" << std::endl;
			
			switch(tempLight->getType())
			{
			case Ogre::Light::LT_DIRECTIONAL:
				// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
				break;

			case Ogre::Light::LT_POINT:
				Testausgabe << "DiffuseColour (" << tempDiffuseColour.r << ", " << tempDiffuseColour.g << ", " << tempDiffuseColour.b << ")" << std::endl;
				Testausgabe << "SpecularColour (" << tempSpecularColour.r << ", " << tempSpecularColour.g << ", " << tempSpecularColour.b << ")" << std::endl;
				break;

			case Ogre::Light::LT_SPOTLIGHT:
				// Not full implemented -> not all types of light handled!!!, H.R. 18.03.09
				break;
			}
		}	
		if (!match)
		{
			Testausgabe << "Not handled movable object. Name: '" << MovObj->getName() << "' Type: '" << MovObj->getMovableType() << "'" << std::endl;
			break;
		}
	}

	Ogre::Node::ChildNodeIterator ChildIter = actualNode->getChildIterator();
	while(ChildIter.hasMoreElements()) recursiveNodeTreeWalkthrough(ChildIter.getNext());
}


void dotSceneXmlWriter::moveDOMToXML(std::string filename)
{
	//throw std::exception("dotSceneXmlWriter::moveDOMToXML(std::string filename = \"C:\TextOutputFrom_dotSceneWriter.xml\" not implemented yet!");
}

dotSceneXmlWriter::dotSceneXmlWriter(void)
{
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
