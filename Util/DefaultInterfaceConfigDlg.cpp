#include "DefaultInterfaceConfigDlg.h"

#include <wx/bookctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/checkbox.h>

IMPLEMENT_CLASS( CDefaultInterfaceConfigDlg, wxPropertySheetDialog )

BEGIN_EVENT_TABLE( CDefaultInterfaceConfigDlg, wxPropertySheetDialog )
END_EVENT_TABLE()

CDefaultInterfaceConfigDlg::CDefaultInterfaceConfigDlg()
{	
}

bool CDefaultInterfaceConfigDlg::Create( wxWindow* Parent, wxWindowID Id, 
	const wxString& Title, const wxPoint& Pos, 
	const wxSize& Size, long Style, const wxString& Name )
{
	SetSheetStyle( wxPROPSHEET_SHRINKTOFIT );

	SetSheetInnerBorder(0);
    SetSheetOuterBorder(0);

	if( !wxPropertySheetDialog::Create( Parent, Id, Title, Pos, Size, 
		Style, Name ) )
		return false;

	CreateButtons( wxOK | wxCANCEL );

	wxBookCtrlBase* Notebook = GetBookCtrl();

	wxPanel* GeneralSettings = CreateGeneralSettingsPage( Notebook );

	Notebook->AddPage( GeneralSettings, wxT( "General" ), true );

	LayoutDialog();

	return true;
}

wxPanel* CDefaultInterfaceConfigDlg::CreateGeneralSettingsPage( wxWindow* Parent )
{
	wxPanel* Panel = new wxPanel( Parent );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText8 = new wxStaticText( Panel, wxID_ANY, 
		wxT("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer10->Add( m_staticText8, 0, wxALL, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	HostTextCtrl = new wxTextCtrl( Panel, wxID_ANY, 
		wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( HostTextCtrl, 3, wxALL, 5 );
	
	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText9 = new wxStaticText( Panel, wxID_ANY, 
		wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer11->Add( m_staticText9, 0, wxALL, 5 );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	PortTextCtrl = new wxTextCtrl( Panel, wxID_ANY, 
		wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( PortTextCtrl, 3, wxALL, 5 );
	
	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );
	
	wxCheckBox* SaveSettingsCheckBox = new wxCheckBox( Panel, wxID_ANY,
		wxT("Save settings"), wxDefaultPosition, wxDefaultSize, 0 );
	SaveSettingsCheckBox->SetValue(true); 
	bSizer9->Add( SaveSettingsCheckBox, 2, wxALL, 5 );
	
	Panel->SetSizerAndFit( bSizer9 );

	return Panel;
}
