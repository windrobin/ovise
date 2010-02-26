#ifndef DOTSCENE_MANAGER_H_
#define DOTSCENE_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

// Solution's includes
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
	WX_DECLARE_STRING_HASH_MAP(ScenePrototype*, PrototypeHashMap);

	PrototypeHashMap		mPrototypes;
	QualifiedNameCollection mQPrototypes;

	// Access to XML
	XmlManager *mXmlMgr;

	bool mValid;

	// Methods
	bool CallSuitableInterpreter(xercesc::DOMDocument* SceneInDOMFormat, wxString AnchorNodeName);

public:
	// De- & Constructors
	OViSEDotSceneManager(DotSceneBaseConfiguration *Configuration);
    ~OViSEDotSceneManager();


	bool				SetPrototypeData(QualifiedName qPrototype, ScenePrototypeData DataSet); // Return false, if there is no prototyp with that name.
	ScenePrototypeData	GetPrototypeData(QualifiedName qPrototype); // Empty (IsEmpty() == true), if there is no prototype with that unique name. Data can be modified externally.

	// Accessors of general properies
	void						SetConfiguration(DotSceneBaseConfiguration* Configuration);

	DotSceneBaseConfiguration*	GetConfiguration();
	QualifiedName				GetSceneManager();
	QualifiedName				GetName();
	QualifiedName				GetAssociatedResourceGroup();
	QualifiedNameCollection		GetImportedPrototypes();

	// Selection of interpreter 
	static		DotSceneBaseConfiguration* CreateDefaultConfiguration();

	// New Im-/Exportstuff, wrapping OViSEXmlManager
	bool		SetURLofDotSceneXSD(wxString URLofDotSceneXSD);
	bool		SetURLofExportPath(wxString URLofExportPath);
	wxString	GetURLofDotSceneXSD();
	wxString	GetURLofExportPath();
	bool		IsReadyToExport();
	bool		IsReadyToImport();


	// Management of DOMDocuments
	bool			MakeOgreSceneFromPrototype(QualifiedName qPrototype, QualifiedName qAnchorNode);
	QualifiedName	MakePrototypeFromOgreScene(wxString NotUniquePrototypeName, QualifiedNameCollection Selection, wxString VersionStringForExport); // Returns UniquePrototypeName
	
	bool			ExportScenePrototype(QualifiedName qPrototype, wxFileName DestinationURL);
	QualifiedName	ImportScenePrototype(wxFileName URLofXML);  // Returns UniquePrototypeName

	bool			RemoveScenePrototype(QualifiedName qPrototype);
	QualifiedName	RenameScenePrototype(QualifiedName qPrototype, wxString NewNativePrototypeName); // Returns the new UniquePrototypeName. If "OldUniquePrototypeName" is unknown, an empty wxString is returned.


	// Top-Layer handling-methods
	wxArrayString GetImportedScenePrototypes();
	//bool		ExportPrototype(OViSESelectionMap Selection, wxString DestinationOfSceneXML, bool doExportNotSelectedChildsToo,  bool doExportMeshFiles);
	//wxString	ImportPrototype(wxString URLofXML); // Returns unique name of prototype	
	//bool		AttachSceneFromPrototype(wxString UniqueNameOfPrototype, wxString AnchorNodeName);
};

#endif /*DOTSCENE_MANAGER_H_*/