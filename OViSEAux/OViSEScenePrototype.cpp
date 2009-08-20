#include "OViSEScenePrototype.h"

wxString OViSEScenePrototype::GetUniqueName() {	return this->UniqueName; }
xercesc::DOMDocument* OViSEScenePrototype::GetDOMRepresentation() { return this->DOMRepresentation; }
OViSEScenePrototype::OViSEScenePrototype(	wxString UniqueName,
											xercesc::DOMDocument* DOMRepresentation)
{
	this->SetUniqueName(UniqueName);
	this->SetDOMRepresentation(DOMRepresentation);
}
OViSEScenePrototype::~OViSEScenePrototype(void) { this->DOMRepresentation->release(); }