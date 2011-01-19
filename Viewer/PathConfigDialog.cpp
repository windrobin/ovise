#include "PathConfigDialog.h"

OViSEPathConfigDialog::OViSEPathConfigDialog(wxString CmdPath, wxString BasePath, wxString MediaPath, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: PathConfigDialog( parent, id, title, pos, size, style)
{	
	this->mCmdDirPicker->SetPath(CmdPath);
	this->mBaseDirPicker->SetPath(BasePath);
	this->mMediaDirPicker->SetPath(MediaPath);

	wxSizer* ButtonSizer = CreateButtonSizer(wxOK|wxCANCEL);
	
	if ( ButtonSizer )
	{
		mMainSizer->Add( ButtonSizer, 0, wxEXPAND,5);
		this->Layout();
		mMainSizer->SetSizeHints( this );
		//this->Layout();
	}
}

OViSEPathConfigDialog::~OViSEPathConfigDialog()
{
}

wxString OViSEPathConfigDialog::GetCmdPath() { return this->mCmdDirPicker->GetPath(); }
wxString OViSEPathConfigDialog::GetBasePath() { return this->mBaseDirPicker->GetPath(); }
wxString OViSEPathConfigDialog::GetMediaPath() { return this->mMediaDirPicker->GetPath(); }
