#include "PathConfigDialog.h"

OViSEPathConfigDialog::OViSEPathConfigDialog( wxString  PluginPath,
                                              wxString  MediaPath,
                                              wxWindow* parent )
	: PathConfigDialog( parent )
{
	this->mPluginDirPicker->SetPath( PluginPath );
	this->mMediaDirPicker->SetPath( MediaPath );

	wxSizer* ButtonSizer = CreateButtonSizer( wxOK | wxCANCEL );

	if ( ButtonSizer )
	{
		mMainSizer->Add( ButtonSizer, 0, wxEXPAND,5 );
		this->Layout();
		mMainSizer->SetSizeHints( this );
	}
}

OViSEPathConfigDialog::~OViSEPathConfigDialog()
{}

wxString OViSEPathConfigDialog::GetPluginPath() {
	return mPluginDirPicker->GetPath();
}
wxString OViSEPathConfigDialog::GetMediaPath() {
	return mMediaDirPicker->GetPath();
}
