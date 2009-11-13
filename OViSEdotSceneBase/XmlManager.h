

#pragma once

#ifndef XML_MANAGER_H_
#define XML_MANAGER_H_

// Solution's includes
#include "../OViSEAux/OViSEException.h"
#include "../OViSEAux/StringConverter.h"
#include "./XmlErrorReporter.h"
#include "./ScenePrototype.h"
#include "./DotSceneBaseConfiguration.h"

// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

// Include STD
#include <string>

/// Map containing selected objects.
typedef std::map<std::string, Ogre::MovableObject*> OViSESelectionMap;

// Special defines for debugging or mode-activations

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
	ScenePrototype* ImportScenePrototype(wxFileName URLofXML);  // Returns UniqueName of ScenePrototype

	// Writing XML
	bool ExportDotScene(wxString HostingSceneManagerName, OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	
	// Reading XML
	xercesc::DOMDocument* ImportDotScene(wxString URLofXML);
};

#endif /*XML_MANAGER_H_*/