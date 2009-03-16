#ifndef DOTSCENEXMLWRITER_H_
#define DOTSCENEXMLWRITER_H_

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

XERCES_CPP_NAMESPACE_USE

/**
 * This class provides functionalities to take an entire ogre-scene an write it to an xml-file in dotScene-format.
 * It utilizes Xeces XML to crate a DOM structure in memory and write it to file.
 */
class dotSceneXmlWriter
{
private:
	//DOMImplementation *mImplementation;
	//DOMDocument *mDocument;
public:
	void copyOgreSceneToDOM(Ogre::SceneManager* SceneMgr);
	void moveDOMToXML(std::string filename = "C:\\TextOutputFrom_dotSceneWriter.xml");

	dotSceneXmlWriter(void);
	~dotSceneXmlWriter(void);
};

#endif /*DOTSCENEXMLWRITER_H_*/