#include "OViSEExportMeshesDialog.h"

OViSEExportMeshesDialog::OViSEExportMeshesDialog( wxWindow* parent, wxWindowID id ) : ExportMeshesDialog( parent, id ) { }
OViSEExportMeshesDialog::~OViSEExportMeshesDialog(void) { }
void OViSEExportMeshesDialog::OnCloseDialog( wxCloseEvent& event ) { this->Destroy(); }
void OViSEExportMeshesDialog::OnClickCancel( wxCommandEvent& event )
{
	this->SetReturnCode(wxID_CANCEL);
	this->Close();
}
void OViSEExportMeshesDialog::OnClickOk( wxCommandEvent& event )
{
	this->SetReturnCode(wxID_OK);
	this->Close();
}