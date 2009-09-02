#pragma once
#ifndef DOTSCENE_INTERPRETER_DOM_TO_OGRE_H_
#define DOTSCENE_INTERPRETER_DOM_TO_OGRE_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>

// Solution's includes
#include "./DotSceneBaseConfiguration.h"
#include "../OViSEAux/UniqueNameManager.h"
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/SceneNodeOffset.h"
#include "../OViSEAux/OViSELogging.h"
#include "../OViSEAux/OgreAPIMediator.h"


// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLFloat.hpp>

XERCES_CPP_NAMESPACE_USE

class DotSceneInterpreter_DOMToOgre
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// All abstract methods
	virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene) = 0;
	virtual void Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes) = 0;
	virtual void Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode) = 0;
	virtual void Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode) = 0;
	virtual void Interpretation_Camera(xercesc::DOMElement* DOMElement_camera) = 0;
	virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment) = 0;
	virtual Ogre::Vector3 Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3) = 0;
	virtual Ogre::Vector4 Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4) = 0;
	virtual Ogre::Quaternion Interpretation_Quaternion(xercesc::DOMElement* DOMElement_Quaternion) = 0;

protected:
	// Attributes
	Ogre::SceneNode* AnchorNode;
	DotSceneBaseConfiguration* Configuration;
	wxString VersionString;

	// Methods
	bool Interpretation_DOMScene(	xercesc::DOMDocument* DOMRepresentationOfScene,
									wxString AttachToNodeWithThisName,
									DotSceneBaseConfiguration* Configuration);

	// Static methods
	
public:
	// De- & Constructors
	~DotSceneInterpreter_DOMToOgre(void);

	// Static methods
	static wxString GetVersionString( xercesc::DOMDocument *DOMRepresentationOfScene );

	// Inheritable methods
	virtual bool Interpretation(xercesc::DOMDocument* DOMRepresentationOfScene,
								wxString AnchorNodeName,
								DotSceneBaseConfiguration* Configuration) = 0;
};

#endif // DOTSCENE_INTERPRETER_DOM_TO_OGRE_H_
