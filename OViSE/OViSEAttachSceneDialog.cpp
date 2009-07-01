#include "OViSEAttachSceneDialog.h"

OViSEAttachSceneDialog::OViSEAttachSceneDialog( wxWindow* parent ) : AttachSceneDialog( parent )
{
	this->mValid = false;
	this->mResultingUniqueNameOfPrototype.Empty();
}

void OViSEAttachSceneDialog::OnCloseDialog( wxCloseEvent& event )
{
	this->Destroy();
}

void OViSEAttachSceneDialog::OnProtoTypeListSelect( wxCommandEvent& event )
{
	if (this->mValid)
	{
		this->mResultingUniqueNameOfPrototype = this->mPrototypeList->GetString(this->mPrototypeList->GetSelection());
	}
	else
	{
		this->mResultingUniqueNameOfPrototype.Empty();
	}
}

void OViSEAttachSceneDialog::OnClickCancel( wxCommandEvent& event )
{
	this->Close();
	this->mResultingUniqueNameOfPrototype.Empty();
}

void OViSEAttachSceneDialog::OnClickOk( wxCommandEvent& event )
{
	this->Close();
}

void OViSEAttachSceneDialog::SetAvailablePrototypes(wxArrayString ListOfAvailablePrototypes)
{
	this->mPrototypeList->Append(ListOfAvailablePrototypes);
	if (this->mPrototypeList->GetCount() > 0) this->mValid = true;
	else this->mValid = false;
}

wxString OViSEAttachSceneDialog::GetResultingUniqueNameOfPrototype() { return this->mResultingUniqueNameOfPrototype; }