/********************************************************************************
 * Name:      XmlErrorReporter.h												*
 * Purpose:   Code describes a class, handling validation-, read- and write-	*
 *			  error. Any error will be send to log.								*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#ifndef OVISE_XML_ERRORREPORTER_H_
#define OVISE_XML_ERRORREPORTER_H_

// Solution's includes
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/Logging.h"

// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>

// Include STD
#include <string>

class XmlErrorReporter : xercesc::ErrorHandler
{
private:
	bool mFoundErrors;

public:
	XmlErrorReporter();
	~XmlErrorReporter();

	void fatalError(const xercesc::SAXParseException& fatalE);
    void error(const xercesc::SAXParseException& defaultE);
	void warning(const xercesc::SAXParseException& warningE);
    void resetErrors();

	bool HasValidationErrors() const;
};

#endif /*OVISE_XML_ERRORREPORTER_H_*/