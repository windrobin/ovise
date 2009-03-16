#include "dotSceneXmlWriter.h"

void dotSceneXmlWriter::copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr)
{
	DOMImplementation *implementation = 0;
	DOMDocument *document = 0;
	implementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("SceneRoot"));
	document = implementation->createDocument(0, XMLString::transcode("scene"), 0);
	
	// Get "scene"-element and add attribute "formatVersion"...
	DOMElement *SceneElement = document->getDocumentElement();
	SceneElement->setAttribute(XMLString::transcode("formatVersion"), XMLString::transcode("1.0.0"));

	// Create "nodes"-element nd append to "scene"-element...
	DOMElement* NodesElement = document->createElement(XMLString::transcode("nodes"));
	SceneElement->appendChild(NodesElement);

	// Recusive: get nodes from Ogre::SceneManager, create "node"-elements and append 'em to "nodes"-element or parent "node"-elements...

	// Step 1: get one node...
	Ogre::SceneNode *root = SceneMgr->getRootSceneNode();
	root->getName();	
	root->getOrientation();
	root->getPosition();
	root->getScale();




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
