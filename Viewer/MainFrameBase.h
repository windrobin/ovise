///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MainFrameBase__
#define __MainFrameBase__

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
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/statline.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOAD_SCENE 1000
#define ID_LOAD_POINTCLOUD 1001
#define idMenuQuit 1002
#define ID_SHOW_STRUCTURE 1003
#define ID_SAVE_SCREENSHOT_TO_FILE 1004
#define ID_DYNAMIC_SHADOWS 1005
#define ID_POINTS 1006
#define ID_WIREFRAME 1007
#define ID_SOLID 1008
#define ID_INSERT_ENTITY 1009
#define ID_REMOVE_ENTITY 1010
#define ID_ADD_ATTRIBUTE 1011
#define ID_DELETE_ATTRIBUTE 1012
#define idMenuAbout 1013
#define ID_TESTSTUFF 1014

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
		wxMenuItem* points;
		wxMenuItem* wireframe;
		wxMenuItem* solid;
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* view;
		wxMenu* displayMode;
		wxMenu* scene;
		wxMenu* network;
		wxMenu* helpMenu;
		wxMenu* debug;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnLoadScene( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadPointcloud( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowSceneStructure( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveScreenToFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDynamicShadowsChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMPoints( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMWire( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMSolid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestStuff( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OViSE - powered by wxWidgets!"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PathConfigDialog
///////////////////////////////////////////////////////////////////////////////
class PathConfigDialog : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* mMainSizer;
		wxDirPickerCtrl* mPluginDirPicker;
		wxDirPickerCtrl* mMediaDirPicker;
	
	public:
		
		PathConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OViSE - Configure Path Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 596,138 ), long style = wxDEFAULT_DIALOG_STYLE );
		~PathConfigDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AddAttributeDialog
///////////////////////////////////////////////////////////////////////////////
class AddAttributeDialog : public wxDialog 
{
	private:
	
	protected:
	
	public:
		wxBoxSizer* Sizer;
		wxRadioBox* TypeRadioBox;
		wxTextCtrl* NameCtrl;
		wxTextCtrl* ValueCtrl;
		
		AddAttributeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Attribute"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 279,164 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AddAttributeDialog();
	
};

#endif //__MainFrameBase__
