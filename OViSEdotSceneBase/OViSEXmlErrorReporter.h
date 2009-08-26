#pragma once
#ifndef OVISE_XML_ERRORREPORTER_H_
#define OVISE_XML_ERRORREPORTER_H_

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/OViSELogging.h"

// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>

// Include STD
#include <string>

class OViSEXmlErrorReporter : xercesc::ErrorHandler
{
private:
	bool mFoundErrors;
	OViSELogging* mLog;
public:
	OViSEXmlErrorReporter();
	~OViSEXmlErrorReporter();

	void fatalError(const xercesc::SAXParseException& fatalE);
    void error(const xercesc::SAXParseException& defaultE);
	void warning(const xercesc::SAXParseException& warningE);
    void resetErrors();

	bool HasValidationErrors() const;
};

#endif /*OVISE_XML_ERRORREPORTER_H_*/