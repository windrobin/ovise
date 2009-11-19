/********************************************************************************
 * Name:      XmlManager.h														*
 * Purpose:   Code describes a class, which encapsulate the complete xml-access.*
 *			  Including operations like read and write prototypes or complete	*
 *			  object-collections.												*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef XML_MANAGER_H_
#define XML_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

// Solution's includes
#include "../QualifiedNames/QualifiedNameCollection.h"
#include "../OViSEAux/OViSEException.h"
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/Logging.h"
#include "../OViSEAux/OgreAPIMediator.h"
#include "../OViSEdotSceneBase/XmlErrorReporter.h"
#include "../OViSEdotSceneBase/ScenePrototype.h"
#include "../OViSEdotSceneBase/DotSceneBaseConfiguration.h"

// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

// Include STD
#include <string>

class XmlManager
{
private:
	// General
	bool mInitialized;
	bool mReadyToExport;
	bool mReadyToImport;

	DotSceneBaseConfiguration* mConfiguration;

	// Both
	wxFileName mURLofExportPath;
	wxFileName mURLofXSD;

	// Both
	bool InitXML();
	bool TerminateXML();

	// Writing XML
	DOMImplementation* mImplementation;
	DOMDocumentType* mDocType;
	::DOMDocument* mDocument;
	
	void MoveDOMToXML(wxFileName filename, bool doExportMeshFiles);

	// Reading XML
	XercesDOMParser *mParser;
	ErrorHandler *mErrHandler;

public:
	// General
	XmlManager(DotSceneBaseConfiguration* Configuration);
	~XmlManager(void);

	// Get info
	bool IsInitialized();
	bool IsReadyToExport();
	bool IsReadyToImport();

	// Set data
	bool		SetURLofXSD(wxString URLofXSD);
	bool		SetURLofExportPath(wxString URLofExportPath);

	// Get data
	wxString	GetURLofXSD();
	wxString	GetURLofExportPath();
	DotSceneBaseConfiguration* GetConfiguration();

	// Management of DOMDocuments
	bool ExportScenePrototype(ScenePrototype* Prototype, wxFileName DestinationURL);
	ScenePrototype* ImportScenePrototype(wxFileName URLofXML);

	// Writing XML
	//bool ExportDotScene(wxString HostingSceneManagerName, QualifiedNameCollection Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	
	// Reading XML
	xercesc::DOMDocument* ImportDotScene(wxString URLofXML);
};

#endif /*XML_MANAGER_H_*/