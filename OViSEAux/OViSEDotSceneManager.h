#ifndef OVISE_DOTSCENE_MANAGER_H_
#define OVISE_DOTSCENE_MANAGER_H_

// Solution's includes
#ifndef OVISE_XML_MANAGER_USED
#define OVISE_XML_MANAGER_USED
#include "./OViSEXmlManager.h"
#endif

#ifndef OVISE_UNIQUENAME_GENERATOR_USED
#define OVISE_UNIQUENAME_GENERATOR_USED
#include "../OViSE/OViSEUniqueNameGenerator.h"
#endif

#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

#ifndef OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#define OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#include "./OViSEDotSceneManagerConfiguration.h"
#endif

#ifndef OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_USED
#define OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_USED
#include "./OViSEInterpreter_DOMToOgre_DotSceneAbstract.h"
#endif

#ifndef OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_V1_0_0_USED
#define OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_V1_0_0_USED
#include "./OViSEInterpreter_DOMToOgre_DotSceneV1_0_0.h"
#endif

#ifndef OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_USED
#define OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_USED
#include "./OViSEInterpreter_OgreToDOM_DotSceneAbstract.h"
#endif

#ifndef OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_V1_0_0_USED
#define OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_V1_0_0_USED
#include "./OViSEInterpreter_OgreToDOM_DotSceneV1_0_0.h"
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

#ifndef XERCES_UTIL_XMLFLOAT_USED
#define XERCES_UTIL_XMLFLOAT_USED
#include <xercesc/util/XMLFloat.hpp>
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

// Special defines for debugging or mode-activations
#define ATTACH_FACTORY__ALLOW_INTERPRETATION_ASSUMPTIONS

class OViSEDotSceneManager
{
private:
	// General attributes
	OViSEDotSceneManagerConfiguration* mConfiguration;
	
	Ogre::SceneNode *mAnchorNode;

	// Management of Prototypes
	WX_DECLARE_STRING_HASH_MAP(OViSEScenePrototype*, HashMap_ScenePrototypes);

	HashMap_ScenePrototypes ScenePrototypes;

	// Access to XML
	OViSEXmlManager *mXmlMgr;
	wxArrayString mImportedScenePrototypes;

	// Sub-managers for logging and unique names
	OViSELogging *Log;

	bool mValid;

	// Methods
	bool CallSuitableInterpreter(xercesc::DOMDocument* SceneInDOMFormat, wxString AnchorNodeName);

public:
	// De- & Constructors
	OViSEDotSceneManager(OViSEDotSceneManagerConfiguration *Configuration);
    ~OViSEDotSceneManager();


	bool		SetPrototypeData(wxString UniquePrototypeName, OViSEScenePrototypeData DataSet); // Return false, if there is no prototyp with that name.
	OViSEScenePrototypeData GetPrototypeData(wxString UniquePrototypeName); // Empty (IsEmpty() == true), if there is no prototype with that unique name. Data can be modified externally.

	// Accessors of general properies
	void SetConfiguration(OViSEDotSceneManagerConfiguration* Configuration);

	OViSEDotSceneManagerConfiguration* GetConfiguration();
	wxString GetUniqueName();
	wxString GetUniqueNameOfAssociatedResourceGroup();

	// Selection of interpreter 
	// OViSEDotSceneManagerConfiguration* CallSuitableInterpreter_DOMToOgre(wxString UniqueNameOfDotSceneManager, wxString SceneManagerName);
	static OViSEDotSceneManagerConfiguration* CreateDefaultConfiguration(wxString UniqueDotSceneManagerName, wxString SceneManagerName);

	// New Im-/Exportstuff, wrapping OViSEXmlManager
	bool SetURLofDotSceneXSD(wxString URLofDotSceneXSD);
	bool SetURLofExportPath(wxString URLofExportPath);
	wxString GetURLofDotSceneXSD();
	wxString GetURLofExportPath();
	bool IsReadyToExport();
	bool IsReadyToImport();


	// Management of DOMDocuments
	bool		MakeOgreSceneFromPrototype(wxString UniquePrototypeName, wxString AnchorNodeName);
	wxString	MakePrototypeFromOgreScene(wxString NotUniquePrototypeName, OViSESelectionMap Selection, wxString VersionStringForExport); // Returns UniquePrototypeName
	
	bool		ExportScenePrototype(wxString UniquePrototypeName, wxFileName DestinationURL);
	wxString	ImportScenePrototype(wxFileName URLofXML);  // Returns UniquePrototypeName


	// Top-Layer handling-methods
	wxArrayString GetImportedScenePrototypes();
	//bool		ExportPrototype(OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	//wxString	ImportPrototype(wxString URLofXML); // Returns unique name of prototype	
	//bool		AttachSceneFromPrototype(wxString UniqueNameOfPrototype, wxString AnchorNodeName);
};

#endif /*OVISE_DOTSCENE_MANAGER_H_*/