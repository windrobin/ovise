#ifndef OVISE_DEFAULT_INTERFACE_CONFIG_DLG_H
#define OVISE_DEFAULT_INTERFACE_CONFIG_DLG_H

#include <wx/propdlg.h>
#include <wx/textctrl.h>

class CDefaultInterfaceConfigDlg : public wxPropertySheetDialog
{
DECLARE_CLASS(CDefaultInterfaceConfigDlg)
public:
	CDefaultInterfaceConfigDlg();

	bool Create( wxWindow* parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, 
		long style = wxDEFAULT_DIALOG_STYLE, 
		const wxString& name = "dialogBox" );

	wxPanel* CreateGeneralSettingsPage( wxWindow* Parent );

	wxTextCtrl* HostTextCtrl;
	wxTextCtrl* PortTextCtrl;

protected:
DECLARE_EVENT_TABLE()
};

#endif // OVISE_DEFAULT_INTERFACE_CONFIG_DLG_H
