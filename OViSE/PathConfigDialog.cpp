#include "PathConfigDialog.h"

OViSEPathConfigDialog::OViSEPathConfigDialog(wxString CmdPath, wxString BasePath, wxString MediaPath, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: PathConfigDialog( parent, id, title, pos, size, style)
{
	this->mInitialCmdPath = CmdPath;
	this->mInitialBasePath = BasePath;
	this->mInitialMediaPath = MediaPath;
	
	this->mCmdDirPicker->SetPath(CmdPath);
	this->mBaseDirPicker->SetPath(BasePath);
	this->mMediaDirPicker->SetPath(MediaPath);

	this->SetCmdPath(CmdPath);
	this->SetBasePath(BasePath);
	this->SetMediaPath(MediaPath);
}
OViSEPathConfigDialog::~OViSEPathConfigDialog(void) { }
void OViSEPathConfigDialog::SetCmdPath(wxString CmdPath) { this->mCmdPath = CmdPath; }
void OViSEPathConfigDialog::SetBasePath(wxString BasePath) { this->mBasePath = BasePath; }
void OViSEPathConfigDialog::SetMediaPath(wxString MediaPath) { this->mMediaPath = MediaPath; }
wxString OViSEPathConfigDialog::GetCmdPath() { return this->mCmdPath; }
wxString OViSEPathConfigDialog::GetBasePath() { return this->mBasePath; }
wxString OViSEPathConfigDialog::GetMediaPath() { return this->mMediaPath; }
void OViSEPathConfigDialog::OnClose( wxCloseEvent& event ) { event.Skip(); }
void OViSEPathConfigDialog::OnCmdDirChanged( wxFileDirPickerEvent& event )
{
	this->SetCmdPath(event.GetPath());
	event.Skip();
}
void OViSEPathConfigDialog::OnBaseDirChanged( wxFileDirPickerEvent& event )
{
	this->SetBasePath(event.GetPath());
	event.Skip();
}
void OViSEPathConfigDialog::OnMediaDirChanged( wxFileDirPickerEvent& event )
{
	this->SetMediaPath(event.GetPath());
	event.Skip();
}
void OViSEPathConfigDialog::OnClickCancel( wxCommandEvent& event )
{
	this->SetCmdPath(this->mInitialCmdPath);
	this->SetBasePath(this->mInitialBasePath);
	this->SetMediaPath(this->mInitialMediaPath);
	this->Close();
	event.Skip();
}
void OViSEPathConfigDialog::OnClickSave( wxCommandEvent& event )
{
	this->Close();
	event.Skip();
}