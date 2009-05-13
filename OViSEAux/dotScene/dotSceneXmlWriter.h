#ifndef DOTSCENEXMLWRITER_H_
#define DOTSCENEXMLWRITER_H_

#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/arrstr.h>
#include "../../OViSE/OViSEPathProvider.h"


// Inlcude Xerces
#ifndef Xerxes_Used
#define Xerxes_Used
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>
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

#include <deque>

XERCES_CPP_NAMESPACE_USE

/**
 * This class provides functionalities to take an entire ogre-scene an write it to an xml-file in dotScene-format.
 * It utilizes Xeces XML to crate a DOM structure in memory and write it to file.
 */
class dotSceneXmlWriter
{
	//wxFileName DestinationURI; // More information: "http://de.wikipedia.org/wiki/Uniform_Resource_Identifier"
private:
	bool Valid;

	DOMImplementation* mImplementation;
	DOMDocumentType* mDocType;
	::DOMDocument* mDocument;

	OViSEPathProvider* mPathProvider;

	wxFileName mDotSceneXsd;
	
	wxArrayString mCopyThisMeshFiles;
	std::deque<Ogre::MeshPtr> mExportThisMeshsToFiles;

	std::fstream Testausgabe;

	void recursiveNodeTreeWalkthrough(Ogre::Node* actualNode, DOMElement* ActualDOMParent);

public:
	dotSceneXmlWriter(OViSEPathProvider* PathProvider);
	~dotSceneXmlWriter(void);

	bool IsValid();

	void copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr);
	void moveDOMToXML(wxFileName filename, bool doExportMeshFiles);

};

#endif /*DOTSCENEXMLWRITER_H_*/
