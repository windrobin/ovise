#ifndef OVISE_XML_MANAGER_H_
#define OVISE_XML_MANAGER_H_

// Solution's includes
#ifndef OVISE_EXCEPTION_USED
#define OVISE_EXCEPTION_USED
#include "../OViSE/OViSEException.h"
#endif

#ifndef OVISE_XERCES_XML_ERRORREPORTER_USED
#define OVISE_XERCES_XML_ERRORREPORTER_USED
#include "../OViSE/OViSEXercesXMLErrorReporter.h"
#endif

#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

#ifndef OVISE_SCENE_PROTOTYPE_USED
#define OVISE_SCENE_PROTOTYPE_USED
#include "./OViSEScenePrototype.h"
#endif

#ifndef OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#define OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#include "./OViSEDotSceneManagerConfiguration.h"
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

#ifndef XERCES_PARSERS_XERCESDOMPARSER_USED
#define XERCES_PARSERS_XERCESDOMPARSER_USED
#include <xercesc/parsers/XercesDOMParser.hpp>
#endif

#ifndef XERCES_DOM_DOM_USED
#define XERCES_DOM_DOM_USED
#include <xercesc/dom/DOM.hpp>
#endif

#ifndef XERCES_CPP_NAMESPACE_USE_USED
#define XERCES_CPP_NAMESPACE_USE_USED
XERCES_CPP_NAMESPACE_USE
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_FILENAME_USED
#define WX_FILENAME_USED
#include <wx/filename.h>
#endif

#ifndef WX_DIR_USED
#define WX_DIR_USED
#include <wx/dir.h>
#endif

#ifndef WX_ARRAYSTRING_USED
#define WX_ARRAYSTRING_USED
#include <wx/arrstr.h>
#endif

#ifndef WX_HASHMAP_USED
#define WX_HASHMAP_USED
#include <wx/hashmap.h>
#endif

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

/// Map containing selected objects.
typedef std::map<std::string, Ogre::MovableObject*> OViSESelectionMap;

// Special defines for debugging or mode-activations

class OViSEXmlManager
{
private:
	// General
	bool mInitialized;
	bool mReadyToExport;
	bool mReadyToImport;

	OViSEDotSceneManagerConfiguration* mConfiguration;

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
	OViSEXmlManager(OViSEDotSceneManagerConfiguration* Configuration);
	OViSEXmlManager(wxString URLofXSD, wxString URLofExportPath);
	~OViSEXmlManager(void);

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
	OViSEDotSceneManagerConfiguration* GetConfiguration();

	// Management of DOMDocuments
	bool ExportScenePrototype(OViSEScenePrototype* ScenePrototype, wxFileName DestinationURL);
	OViSEScenePrototype* ImportScenePrototype(wxFileName URLofXML);  // Returns UniquePrototypeName

	// Writing XML
	bool ExportDotScene(wxString HostingSceneManagerName, OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	
	// Reading XML
	xercesc::DOMDocument* ImportDotScene(wxString URLofXML);
};

#endif /*OVISE_XML_MANAGER_H_*/