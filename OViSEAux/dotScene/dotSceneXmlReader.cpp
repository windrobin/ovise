#include "dotSceneXmlReader.h"
// Cut out of Projectmap: "$(WX_HOME)\lib\vc_lib";"C:\lib\wxCode\components\propgrid\lib\vc_lib"
// zusätzliche abhängigkeiten: wxbase28ud.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxcode_msw28ud_propgrid.lib
/*
 * *********** Implementierung dotSceneXMLReader ********************
 */

dotSceneXmlReader::dotSceneXmlReader(std::string URLofDotSceneXSD, bool DbgMode)
{
	this->mURLofDotSceneXSD = URLofDotSceneXSD;
	this->mDebugMode = DbgMode;
	
	std::string ParsingMsg;

	try
	{
		XMLPlatformUtils::Initialize();
		ParsingMsg = "XERCES: *** Initialised ***";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_NORMAL);
	}
	catch (const XMLException& toCatch) 
	{
        char* message = XMLString::transcode(toCatch.getMessage());
        ParsingMsg = "XERCES: Exception message is: " + (string)message;
        Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
    }
}

dotSceneXmlReader::~dotSceneXmlReader()
{
	delete mParser;
    delete mErrHandler;

	std::string ParsingMsg;

    try
   	{
    	XMLPlatformUtils::Terminate();  // Terminate Xerces
		ParsingMsg = "XERCES: *** Terminated ***";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_NORMAL);
   	}
   	catch( xercesc::XMLException& e )
   	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ParsingMsg = "Xerces: " + (string)message;
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg.c_str(), Ogre::LML_CRITICAL);
		XMLString::release( &message );
	}	   
}

xercesc::DOMDocument* dotSceneXmlReader::parseDotSceneXML(string URLofXML)
{
	// Setup XML-parser
	mParser = new XercesDOMParser();
    mParser->setValidationScheme(XercesDOMParser::Val_Always);    
    mParser->setDoNamespaces(true); 
	mParser->setDoSchema(true); // <- important, when a .XSD is used!!!
    mParser->setExternalNoNamespaceSchemaLocation(mURLofDotSceneXSD.c_str());

	// OViSEXercesXMLErrorReporter inherits from "xercesc::ErrorHandler"
	// and redirects parsing-errors into Ogre::LogManager
	mErrHandler = (xercesc::ErrorHandler*) new OViSEXercesXMLErrorReporter();
	mParser->setErrorHandler(mErrHandler);

	std::string ParsingMsg;

    try 
    {
		ParsingMsg = "XERCES: Parsing file \"" + URLofXML + "\"";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_NORMAL);
        mParser->parse(URLofXML.c_str());
		ParsingMsg = "XERCES: Done!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_NORMAL);
    }
    catch (const XMLException& toCatch) 
    {
		ParsingMsg = "XERCES: Failed!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        char* message = XMLString::transcode(toCatch.getMessage());
        ParsingMsg = "XERCES: Exception message is: " + (string)message;
        Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
        return false;
    }
    catch (const DOMException& toCatch) 
    {
		ParsingMsg = "XERCES: Failed!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
		char* message = XMLString::transcode(toCatch.getMessage());
        ParsingMsg = "XERCES: Exception message is: " + (string)message;
        Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
        return false;
    }
	catch (const SAXException& toCatch) 
    {
		ParsingMsg = "XERCES: Failed!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        char* message = XMLString::transcode(toCatch.getMessage());
        ParsingMsg = "XERCES: Exception message is: " + (string)message;
        Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
        return false;
    }
	catch (std::exception e) 
    {
		ParsingMsg = "XERCES: Failed!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
		const char* message = e.what();
		ParsingMsg = "XERCES: Exception message is: " + (string)message;
        Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        return false;
    }
    catch (...) 
    {
		ParsingMsg = "XERCES: Failed!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
		ParsingMsg = "XERCES: Unexpected Exception!";
		Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
        return false;
    }
    
	// Returns pointer to DOMDocument, if no errors occured while validation.
	// REMEMBER: These errors are no exceptions like in those cases below.
    if (!((OViSEXercesXMLErrorReporter*) this->mErrHandler)->HasValidationErrors()) return this->mParser->getDocument();
	else return 0;
}
