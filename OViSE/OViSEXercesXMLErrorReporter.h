#ifndef OVISE_XERCES_XML_ERRORREPORTER_H_
#define OVISE_XERCES_XML_ERRORREPORTER_H_

// Include Xerces
#ifndef Xerxes_Used
#define Xerxes_Used
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>

XERCES_CPP_NAMESPACE_USE

#endif

// Include Ogre (for logging)
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif


#ifdef XERCES_NEW_IOSTREAMS
#include <iostream>
#else
#include <iostream.h>
#endif



class OViSEXercesXMLErrorReporter : xercesc::ErrorHandler
{
private:
	bool mFoundErrors;
public:
	OViSEXercesXMLErrorReporter();
	~OViSEXercesXMLErrorReporter();

	void fatalError(const xercesc::SAXParseException& fatalE);
    void error(const xercesc::SAXParseException& defaultE);
	void warning(const xercesc::SAXParseException& warningE);
    void resetErrors();

	bool HasValidationErrors() const;
};

#endif /*OVISE_XERCES_XML_ERRORREPORTER_H_*/