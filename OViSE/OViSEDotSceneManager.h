#pragma once
#ifndef DOTSCENE_MANAGER_H_
#define DOTSCENE_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

// Solution's includes
#include "../OViSEAux/UniqueNameManager.h"
#include "../OViSEAux/StringConverter.h"
#include "../OViSEdotSceneBase/XmlManager.h"
#include "../OViSEdotSceneBase/DotSceneBaseConfiguration.h"
#include "../OViSEdotSceneBase/DotSceneInterpreter_DOMToOgre.h"
#include "../OViSEdotSceneBase/DotSceneInterpreter_OgreToDOM.h"
#include "../OViSEdotSceneInterpreter/DotSceneInterpreter_DOMToOgre_V1_0_0.h"
#include "../OViSEdotSceneInterpreter/DotSceneInterpreter_OgreToDOM_V1_0_0.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLFloat.hpp>

XERCES_CPP_NAMESPACE_USE

// Include STD
#include <string>

// Special defines for debugging or mode-activations
#define ATTACH_FACTORY__ALLOW_INTERPRETATION_ASSUMPTIONS

class OViSEDotSceneManager
{
private:
	// General attributes
	DotSceneBaseConfiguration* mConfiguration;
	
	Ogre::SceneNode *mAnchorNode;

	// Management of Prototypes
	WX_DECLARE_STRING_HASH_MAP(ScenePrototype*, HashMap_ScenePrototypes);

	HashMap_ScenePrototypes ScenePrototypes;

	// Access to XML
	XmlManager *mXmlMgr;
	//wxArrayString mImportedScenePrototypes;

	// Sub-managers for logging and unique names
	OViSELogging *Log;

	bool mValid;

	// Methods
	bool CallSuitableInterpreter(xercesc::DOMDocument* SceneInDOMFormat, wxString AnchorNodeName);

public:
	// De- & Constructors
	OViSEDotSceneManager(DotSceneBaseConfiguration *Configuration);
    ~OViSEDotSceneManager();


	bool		SetPrototypeData(wxString UniquePrototypeName, ScenePrototypeData DataSet); // Return false, if there is no prototyp with that name.
	ScenePrototypeData GetPrototypeData(wxString UniquePrototypeName); // Empty (IsEmpty() == true), if there is no prototype with that unique name. Data can be modified externally.
	wxString GetPrototypeOriginalName(wxString UniquePrototypeName);

	// Accessors of general properies
	void SetConfiguration(DotSceneBaseConfiguration* Configuration);

	DotSceneBaseConfiguration* GetConfiguration();
	wxString GetUniqueName();
	wxString GetUniqueNameOfAssociatedResourceGroup();

	// Selection of interpreter 
	static DotSceneBaseConfiguration* CreateDefaultConfiguration(wxString UniqueDotSceneManagerName, wxString SceneManagerName);

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

	bool		RemoveScenePrototype(wxString UniquePrototypeName);
	wxString	RenameScenePrototype(wxString OldUniquePrototypeName, wxString NewNotUniquePrototypeName); // Returns the new UniquePrototypeName. If "OldUniquePrototypeName" is unknown, an empty wxString is returned.


	// Top-Layer handling-methods
	wxArrayString GetImportedScenePrototypes();
	//bool		ExportPrototype(OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	//wxString	ImportPrototype(wxString URLofXML); // Returns unique name of prototype	
	//bool		AttachSceneFromPrototype(wxString UniqueNameOfPrototype, wxString AnchorNodeName);
};

#endif /*DOTSCENE_MANAGER_H_*/