/********************************************************************************
 * Name:      ScenePrototype.cpp												*
 * Purpose:   Code implements a class, holding all data of a prototype. A		*
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

#include "../OViSEdotSceneBase/ScenePrototype.h"

void ScenePrototype::SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation) { this->DOMRepresentation = DOMRepresentation; }
QualifiedName ScenePrototype::GetName() { return this->qName; }
xercesc::DOMDocument* ScenePrototype::GetDOMRepresentation() { return this->DOMRepresentation; }
ScenePrototype::ScenePrototype(wxString NativeName, xercesc::DOMDocument* DOMRepresentation)
{
	this->qName = QualifiedName::Create(NativeName, ToWxString("Prototype"));
	this->SetDOMRepresentation(DOMRepresentation);
}
ScenePrototype::ScenePrototype(const ScenePrototype& ToCopy)
{
	this->qName = ToCopy.qName;
	this->DOMRepresentation = ToCopy.DOMRepresentation;
	this->Data = ToCopy.Data;
}
ScenePrototype::~ScenePrototype(void) 
{
	if ( this->qName.IsValid() ) this->qName.Destroy();
	if ( this->DOMRepresentation != 0 ) this->DOMRepresentation->release();
}