/********************************************************************************
 * Name:      DotSceneInterpreter_OgreToDOM.h									*
 * Purpose:   Code describes a abstract class, which provides the basic 		*
 *			  methods for interpretation of content of ogre-engine as a DOM-	*
 *			  structure. In a inherited	class all methods must be implemented.	*
 *			  That garants  full compatiblility to dotScene-format.				*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef DOTSCENE_INTERPRETER_OGRE_TO_DOM_H_
#define DOTSCENE_INTERPRETER_OGRE_TO_DOM_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

// Solution's includes
#include "../OViSEdotSceneBase/DotSceneBaseConfiguration.h"
#include "../OViSEdotSceneBase/ScenePrototype.h"
#include "../OViSEAux/StringConverter.h"
#include "../OViSEAux/Logging.h"
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/QualifiedNameCollectionInterface.h"
#include "../OViSEAux/OgreAPIMediator.h"
#include "../OViSEAux/EnumsForABetterWorld.h"

// Include Ogre
#include "Ogre.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLFloat.hpp>

XERCES_CPP_NAMESPACE_USE

// Include STD
#include <string>
#include <deque>
#include <typeinfo>

WX_DECLARE_STRING_HASH_MAP(Ogre::SceneNode*, HashMap_OgreSceneNodePointer);
WX_DECLARE_STRING_HASH_MAP(DOMElement*, HashMap_DOMPointer);

class DotSceneInterpreter_OgreToDOM
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// Abstract methods
	//virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene) = 0;
	//virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment) = 0;
	virtual xercesc::DOMElement* Interpretation_Node(Ogre::SceneNode* actualSceneNode) = 0;
	virtual xercesc::DOMElement* Interpretation_Camera(Ogre::Camera* actualCamera) = 0;
	virtual xercesc::DOMElement* Interpretation_Entity(Ogre::Entity* actualEntity) = 0;
	virtual xercesc::DOMElement* Interpretation_Light(Ogre::Light* actualLight) = 0;
	virtual xercesc::DOMElement* Interpretation_Position(Ogre::Vector3 NodePosition) = 0;
	virtual xercesc::DOMElement* Interpretation_Quaternion(Ogre::Quaternion NodeQuaternion) = 0;
	virtual xercesc::DOMElement* Interpretation_Scale(Ogre::Vector3 NodeScale) = 0;
	virtual xercesc::DOMElement* Interpretation_DiffuseColour(Ogre::ColourValue DiffuseColour) = 0;
	virtual xercesc::DOMElement* Interpretation_SpecularColour(Ogre::ColourValue SpecularColour) = 0;

protected:
	// Attributes
	DotSceneBaseConfiguration* Configuration;
	ScenePrototype* Prototype;
	Ogre::SceneManager* SceneMgr;
	DOMImplementation* Implementation;
	QualifiedNameCollection Selection;

	wxString VersionString;
	QualifiedName qPrototype;

	// Abstract methods
	virtual void SetVersionString(wxString VersionString) = 0;

	// Non-abstract methods
	wxString GetVersionString();
	virtual void Interpretation_Nodes(xercesc::DOMElement* SceneElement);
	void RecursiveNodeTreeWalkthrough(	Ogre::Node* actualSceneNode,
										HashMap_OgreSceneNodePointer& WhiteList_STAGE1,
										HashMap_DOMPointer& WhiteList_STAGE2,
										HashMap_DOMPointer& BlackList);
	bool Interpretation_OgreScene(	wxString PrototypeNativeName,
									QualifiedNameCollection Selection,
									DotSceneBaseConfiguration* Configuration);
public:
	~DotSceneInterpreter_OgreToDOM(void);

	// Inheritable methods
	virtual ScenePrototype* Interpretation(	wxString PrototypeNativeName,
											QualifiedNameCollection Selection,
											DotSceneBaseConfiguration* Configuration) = 0;
};

#endif /*DOTSCENE_INTERPRETER_OGRE_TO_DOM_H_*/