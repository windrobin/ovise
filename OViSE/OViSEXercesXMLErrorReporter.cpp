#include "OViSEXercesXMLErrorReporter.h"

OViSEXercesXMLErrorReporter::OViSEXercesXMLErrorReporter() : mFoundErrors(false) { }
OViSEXercesXMLErrorReporter::~OViSEXercesXMLErrorReporter() { }

void OViSEXercesXMLErrorReporter::fatalError(const xercesc_3_0::SAXParseException& fatalE)
{
	this->mFoundErrors = true;

	char* buffText;

	buffText = xercesc_3_0::XMLString::transcode(fatalE.getSystemId());
	std::string tSystemId = (std::string)buffText;
	
	xercesc_3_0::XMLString::binToText(fatalE.getLineNumber(), buffText, 19, 10);
	std::string tLineNumber = (std::string)buffText;

	xercesc_3_0::XMLString::binToText(fatalE.getColumnNumber(), buffText, 19, 10);
	std::string tColumnNumber = (std::string)buffText;
	
	buffText =  xercesc::XMLString::transcode(fatalE.getMessage());
	std::string tMessage = (std::string)buffText;

	std::string ParsingMsg;
	
	ParsingMsg = "Xerces3.0 XML-Parser: Fatal Error at file \"" + tSystemId + "\", line " + tLineNumber + ", column " + tColumnNumber + "!";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);

	ParsingMsg = "Xerces3.0 Message: \"" + tMessage + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
}

void OViSEXercesXMLErrorReporter::error(const xercesc::SAXParseException& defaultE)
{
	this->mFoundErrors = true;

	char* buffText;

	buffText = xercesc_3_0::XMLString::transcode(defaultE.getSystemId());
	std::string tSystemId = (std::string)buffText;
	
	xercesc_3_0::XMLString::binToText(defaultE.getLineNumber(), buffText, 19, 10);
	std::string tLineNumber = (std::string)buffText;

	xercesc_3_0::XMLString::binToText(defaultE.getColumnNumber(), buffText, 19, 10);
	std::string tColumnNumber = (std::string)buffText;
	
	buffText =  xercesc::XMLString::transcode(defaultE.getMessage());
	std::string tMessage = (std::string)buffText;
	
	std::string ParsingMsg;

	ParsingMsg = "Xerces3.0 XML-Parser: Fatal Error at file \"" + tSystemId + "\", line " + tLineNumber + ", column " + tColumnNumber + "!";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);

	ParsingMsg = "Xerces3.0 Message: \"" + tMessage + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_CRITICAL);
}

void OViSEXercesXMLErrorReporter::warning(const xercesc::SAXParseException& warningE)
{
	this->mFoundErrors = true;

	char* buffText;

	buffText = xercesc_3_0::XMLString::transcode(warningE.getSystemId());
	std::string tSystemId = (std::string)buffText;
	
	xercesc_3_0::XMLString::binToText(warningE.getLineNumber(), buffText, 19, 10);
	std::string tLineNumber = (std::string)buffText;

	xercesc_3_0::XMLString::binToText(warningE.getColumnNumber(), buffText, 19, 10);
	std::string tColumnNumber = (std::string)buffText;
	
	buffText =  xercesc::XMLString::transcode(warningE.getMessage());
	std::string tMessage = (std::string)buffText;
	
	std::string ParsingMsg;

	ParsingMsg = "Xerces3.0 XML-Parser: Fatal Error at file \"" + tSystemId + "\", line " + tLineNumber + ", column " + tColumnNumber + "!";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_TRIVIAL);

	ParsingMsg = "Xerces3.0 Message: \"" + tMessage + "\"";
	Ogre::LogManager::getSingletonPtr()->logMessage(ParsingMsg, Ogre::LML_TRIVIAL);
}

void OViSEXercesXMLErrorReporter::resetErrors()
{
	this->mFoundErrors = false;
}

bool OViSEXercesXMLErrorReporter::HasValidationErrors() const
{
	return this->mFoundErrors;
}
