#pragma once
#ifndef SCENE_PROTOTYPE_H_
#define SCENE_PROTOTYPE_H_

// Solutuion's inludes
#include "./ScenePrototypeData.h"

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
	wxString UniqueName;
	wxString OriginalName;
	xercesc::DOMDocument* DOMRepresentation;
	
	void SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation);
public:
	ScenePrototypeData Data;

	void SetUniqueName(wxString UniqueName);
	void SetOriginalName(wxString OriginalName);

	wxString				GetUniqueName();
	wxString				GetOriginalName();
	xercesc::DOMDocument*	GetDOMRepresentation();

	ScenePrototype(	wxString UniqueName,
					wxString OriginalName,
					xercesc::DOMDocument* DOMRepresentation);
	~ScenePrototype(void);
};

#endif /*SCENE_PROTOTYPE_H_*/