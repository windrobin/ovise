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
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define ID_ADD_VIEW 1001
#define ID_SHOW_STRUCTURE 1002
#define ID_SAVE_SCREENSHOT_TO_FILE 1003
#define ID_DYNAMIC_SHADOWS 1004
#define ID_ADD_MESH 1005
#define ID_DELETE_MESHES 1006
#define ID_IMPORT_SCENEPROTOTYPE 1007
#define ID_EXPORT_SCENEPROTOTYPE 1008
#define ID_ATTACH_NEW_SCENE 1009
#define ID_LOAD_POINTCLOUD 1010
#define ID_STARTSTOP_FRAMELISTENERS 1011
#define idMenuAbout 1012
#define ID_TESTSTUFF 1013

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
		wxMenu* actions;
		wxMenu* helpMenu;
		wxMenu* debug;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAddView( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnShowSceneStructure( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveScreenToFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDynamicShadowsChange( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSceneAddMesh( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMenuDeleteMeshes( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnImportScenePrototype( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnExportScenePrototype( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAttachNewScene( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLoadPointCloud( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnStartStopFrameListeners( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTestStuff( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OViSE - powered by wxWidgets!"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
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
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnMeshListSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOkClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnApplyClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancelClick( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AddMeshDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add new mesh to scene"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 916,854 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AddMeshDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ExportMeshesDialog
///////////////////////////////////////////////////////////////////////////////
class ExportMeshesDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* mLabel;
		
		wxButton* mCancelButton;
		
		wxButton* mOkButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnClickCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClickOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		ExportMeshesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Exporting meshes?"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 268,86 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ExportMeshesDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AttachSceneDialog
///////////////////////////////////////////////////////////////////////////////
class AttachSceneDialog : public wxDialog 
{
	private:
	
	protected:
		wxListBox* mPrototypeList;
		wxButton* mCancelButton;
		wxButton* mOkButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnProtoTypeListSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClickCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClickOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AttachSceneDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Which prototype do you want to use for new scene?"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 396,194 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AttachSceneDialog();
	
};

#endif //__GUIFrame__
