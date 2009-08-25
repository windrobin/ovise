#include "OViSEScenePrototype.h"

void OViSEScenePrototype::SetUniqueName(wxString UniqueName) {this->UniqueName = UniqueName; }
void OViSEScenePrototype::SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation) { this->DOMRepresentation = DOMRepresentation; }

wxString OViSEScenePrototype::GetUniqueName() {	return this->UniqueName; }
xercesc::DOMDocument* OViSEScenePrototype::GetDOMRepresentation() { return this->DOMRepresentation; }
OViSEScenePrototype::OViSEScenePrototype(	wxString UniqueName,
											xercesc::DOMDocument* DOMRepresentation)
{
	this->SetUniqueName(UniqueName);
	this->SetDOMRepresentation(DOMRepresentation);
}
OViSEScenePrototype::~OViSEScenePrototype(void) { this->DOMRepresentation->release(); }