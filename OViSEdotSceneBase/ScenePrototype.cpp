#include "ScenePrototype.h"

void ScenePrototype::SetUniqueName(wxString UniqueName) { this->UniqueName = UniqueName; }
void ScenePrototype::SetOriginalName(wxString OriginalName) { this->OriginalName = OriginalName; }
void ScenePrototype::SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation) { this->DOMRepresentation = DOMRepresentation; }

wxString ScenePrototype::GetUniqueName() { return this->UniqueName; }
wxString ScenePrototype::GetOriginalName() { return this->OriginalName; }
xercesc::DOMDocument* ScenePrototype::GetDOMRepresentation() { return this->DOMRepresentation; }
ScenePrototype::ScenePrototype(	wxString UniqueName,
								wxString OriginalName,
								xercesc::DOMDocument* DOMRepresentation)
{
	this->SetUniqueName(UniqueName);
	this->SetOriginalName(OriginalName);
	this->SetDOMRepresentation(DOMRepresentation);
}
ScenePrototype::~ScenePrototype(void) { this->DOMRepresentation->release(); }