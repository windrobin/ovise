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
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/statline.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define ID_SHOW_STRUCTURE 1001
#define ID_SAVE_SCREENSHOT_TO_FILE 1002
#define ID_DYNAMIC_SHADOWS 1003
#define ID_POINTS 1004
#define ID_WIREFRAME 1005
#define ID_SOLID 1006
#define ID_INSERT_ENTITY 1007
#define ID_REMOVE_ENTITY 1008
#define ID_ADD_ATTRIBUTE 1009
#define ID_DELETE_ATTRIBUTE 1010
#define ID_LOAD_POINTCLOUD 1011
#define idMenuAbout 1012
#define ID_TESTSTUFF 1013

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
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowSceneStructure( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveScreenToFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDynamicShadowsChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMPoints( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMWire( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDMSolid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadPointCloud( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestStuff( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OViSE - powered by wxWidgets!"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AddMeshDialog
///////////////////////////////////////////////////////////////////////////////
class AddMeshDialog : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* ListSizer;
		wxListBox* mMeshList;
		
		wxButton* mOkButton;
		wxButton* mApplyButton;
		wxButton* mCancelButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMeshListSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOkClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnApplyClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelClick( wxCommandEvent& event ) { event.Skip(); }
		
	
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
		wxButton* mDeleteButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnClickCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ExportMeshesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Exporting meshes?"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 268,86 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ExportMeshesDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _PrototypeManagementDialog
///////////////////////////////////////////////////////////////////////////////
class _PrototypeManagementDialog : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* MainSizer;
		wxBoxSizer* ListBoxSizer;
		wxListBox* mPrototypeList;
		wxButton* mRemoveButton;
		wxButton* mImportButton;
		wxButton* mExportButton;
		wxButton* mBuildButton;
		wxButton* mAttachButton;
		wxButton* mCloseButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnProtoTypeListSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickImport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickExport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickBuild( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickAttach( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_PrototypeManagementDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("( dotScene ) Prototype Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 557,339 ), long style = wxDEFAULT_DIALOG_STYLE );
		~_PrototypeManagementDialog();
	
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
