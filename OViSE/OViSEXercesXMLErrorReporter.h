#ifndef OVISE_XERCES_XML_ERRORREPORTER_H_
#define OVISE_XERCES_XML_ERRORREPORTER_H_

// Solution's includes
#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

#ifndef OVISE_LOGGING_USED
#define OVISE_LOGGING_USED
#include "./OViSELogging.h"
#endif

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include Xerces
#ifndef XERCESC_UTIL_XMLSTRING_USED
#define XERCESC_UTIL_XMLSTRING_USED
#include <xercesc/util/XMLString.hpp>
#endif

#ifndef XERCESC_SAX_HANDLERBASE_USED
#define XERCESC_SAX_HANDLERBASE_USED
#include <xercesc/sax/HandlerBase.hpp>
#endif

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

class OViSEXercesXMLErrorReporter : xercesc::ErrorHandler
{
private:
	bool mFoundErrors;
	OViSELogging* mLog;
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