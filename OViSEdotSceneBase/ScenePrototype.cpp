#include "ScenePrototype.h"

void ScenePrototype::SetUniqueName(wxString UniqueName) {this->UniqueName = UniqueName; }
void ScenePrototype::SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation) { this->DOMRepresentation = DOMRepresentation; }

wxString ScenePrototype::GetUniqueName() {	return this->UniqueName; }
xercesc::DOMDocument* ScenePrototype::GetDOMRepresentation() { return this->DOMRepresentation; }
ScenePrototype::ScenePrototype(	wxString UniqueName,
								xercesc::DOMDocument* DOMRepresentation)
{
	this->SetUniqueName(UniqueName);
	this->SetDOMRepresentation(DOMRepresentation);
}
ScenePrototype::~ScenePrototype(void) { this->DOMRepresentation->release(); }