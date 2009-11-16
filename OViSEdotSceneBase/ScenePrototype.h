/********************************************************************************
 * Name:      ScenePrototype.h													*
 * Purpose:   Code describes a class, holding all data of a prototype. A		*
 *			  prototype contains an imported dotScene xml-file as DOM-structure,*
 *			  its unique qualified name (which is generated from the native name*
 *			  of dotScene xml-file), and additional data, which is stored inside*
 *			  ScenePrototypeData.												*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-12														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef SCENE_PROTOTYPE_H_
#define SCENE_PROTOTYPE_H_

// Solutuion's inludes
#include "../OViSEdotSceneBase/ScenePrototypeData.h"
#include "../OViSEAux/QualifiedName.h"

// Include Xerces
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

// Include WX
#include <wx/string.h>
#include <wx/filename.h>

class ScenePrototype
{
private:
	QualifiedName qName;
	xercesc::DOMDocument* DOMRepresentation;
	
	void SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation);
public:
	ScenePrototypeData Data;

	QualifiedName			GetName();
	xercesc::DOMDocument*	GetDOMRepresentation();

	bool Rename(wxString NewNativeName);

	ScenePrototype(wxString NativeName, xercesc::DOMDocument* DOMRepresentation);
	ScenePrototype(QualifiedName qName, xercesc::DOMDocument* DOMRepresentation);
	ScenePrototype(const ScenePrototype& ToCopy);
	~ScenePrototype(void);
};

#endif /*SCENE_PROTOTYPE_H_*/