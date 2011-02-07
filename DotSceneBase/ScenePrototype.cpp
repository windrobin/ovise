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

void ScenePrototype::SetDOMRepresentation(
        xercesc::DOMDocument* DOMRepresentation ) {
	this->DOMRepresentation = DOMRepresentation;
}

xercesc::DOMDocument* ScenePrototype::GetDOMRepresentation() {
	return this->DOMRepresentation;
}
bool ScenePrototype::Rename( wxString NewNativeName )
{
	return true;
}
ScenePrototype::ScenePrototype( wxString              NativeName,
                                xercesc::DOMDocument* DOMRepresentation )
{
	this->SetDOMRepresentation( DOMRepresentation );
}
ScenePrototype::ScenePrototype( const ScenePrototype& ToCopy )
{
	this->DOMRepresentation = ToCopy.DOMRepresentation;
	this->Data = ToCopy.Data;
}
ScenePrototype::~ScenePrototype( void )
{
	if ( this->DOMRepresentation != 0 ) this->DOMRepresentation->release();
}
