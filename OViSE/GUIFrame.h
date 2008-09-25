///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define ID_ADD_VIEW 1001
#define ID_SAVE_SCREENSHOT_TO_FILE 1002
#define ID_ADD_MESH 1003
#define idMenuAbout 1004
#define wxOKBUTTON 1005

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* view;
		wxMenu* scene;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAddView( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveScreenToFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSceneAddMesh( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OViSE - powered by wxWidgets!"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,1024 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AddMeshDialog
///////////////////////////////////////////////////////////////////////////////
class AddMeshDialog : public wxDialog 
{
	private:
	
	protected:
		wxListBox* mMeshList;
		
		wxButton* mOkButton;
		wxButton* mApplyButton;
		wxButton* mCancelButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnMeshListSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOkClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnApplyClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancelClick( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AddMeshDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add new mesh to scene"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 690,555 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AddMeshDialog();
	
};

#endif //__GUIFrame__
