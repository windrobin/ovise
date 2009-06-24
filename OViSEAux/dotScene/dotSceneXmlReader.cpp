#include "dotSceneXmlReader.h"
// Cut out of Projectmap: "$(WX_HOME)\lib\vc_lib";"C:\lib\wxCode\components\propgrid\lib\vc_lib"
// zusätzliche abhängigkeiten: wxbase28ud.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxcode_msw28ud_propgrid.lib
/*
 * *********** Implementierung dotSceneXMLReader ********************
 */

dotSceneXmlReader::dotSceneXmlReader(wxString URLofDotSceneXSD)
{
	this->mURLofDotSceneXSD = URLofDotSceneXSD;
	
	wxString ParsingMsg;

	try
	{
		XMLPlatformUtils::Initialize();
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: *** Initialised ***");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
	}
	catch (const XMLException& e) 
	{
		ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
    }
}

dotSceneXmlReader::~dotSceneXmlReader()
{
	delete mParser;
    delete mErrHandler;

	wxString ParsingMsg;

    try
   	{
		// Terminate Xerces
    	XMLPlatformUtils::Terminate();  
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: *** Terminated ***");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
   	}
   	catch( xercesc::XMLException& e )
   	{
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.getMessage());
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);
	}
}

xercesc::DOMDocument* dotSceneXmlReader::ParseDotSceneXML(wxString URLofXML)
{
	// Setup XML-parser
	mParser = new XercesDOMParser();
    mParser->setValidationScheme(XercesDOMParser::Val_Always);    
    mParser->setDoNamespaces(true); 
	mParser->setDoSchema(true); // <- important, when a .XSD is used!!!
    mParser->setExternalNoNamespaceSchemaLocation(ToXMLString(mURLofDotSceneXSD));

	// OViSEXercesXMLErrorReporter inherits from "xercesc::ErrorHandler"
	// and redirects parsing-errors into Ogre::LogManager
	mErrHandler = (xercesc::ErrorHandler*) new OViSEXercesXMLErrorReporter();
	mParser->setErrorHandler(mErrHandler);

	wxString ParsingMsg;

    try 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Parsing file \"") << URLofXML + ToWxString("\"");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);

        mParser->parse(ToXMLString(URLofXML));

		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Done!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_NORMAL);
    }
    catch (const XMLException& e) 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

		ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        return false;
    }
    catch (const DOMException& e) 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        return false;
    }
	catch (const SAXException& e) 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.getMessage());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        return false;
    }
	catch (std::exception e) 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Exception message is: ") << ToWxString(e.what());
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        return false;
    }
    catch (...) 
    {
		ParsingMsg.Clear();
		ParsingMsg << ToWxString("XERCES: Failed!");
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        ParsingMsg.Clear();
        ParsingMsg << ToWxString("XERCES: Unexpected Exception!");
        Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(ParsingMsg), Ogre::LML_CRITICAL);

        return false;
    }
    
	// Returns pointer to DOMDocument, if no errors occured while validation.
	// REMEMBER: These errors are no exceptions like in those cases below.
    if (!((OViSEXercesXMLErrorReporter*) this->mErrHandler)->HasValidationErrors()) return this->mParser->getDocument();
	else return 0;
}
