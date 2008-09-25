///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") );
	
	view = new wxMenu();
	wxMenuItem* addView;
	addView = new wxMenuItem( view, ID_ADD_VIEW, wxString( wxT("Add") ) , wxEmptyString, wxITEM_NORMAL );
	view->Append( addView );
	
	wxMenuItem* saveScreenshotToFile;
	saveScreenshotToFile = new wxMenuItem( view, ID_SAVE_SCREENSHOT_TO_FILE, wxString( wxT("Save Screenshot to File...") ) , wxT("Saves a screenshot of the view to a file specified by the user."), wxITEM_NORMAL );
	view->Append( saveScreenshotToFile );
	
	mbar->Append( view, wxT("View") );
	
	scene = new wxMenu();
	wxMenuItem* addMesh;
	addMesh = new wxMenuItem( scene, ID_ADD_MESH, wxString( wxT("Add Mesh") ) + wxT('\t') + wxT("Strg+I"), wxT("Add a new mesh to the scene"), wxITEM_NORMAL );
	scene->Append( addMesh );
	
	mbar->Append( scene, wxT("Scene") );
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") );
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( addView->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAddView ) );
	this->Connect( saveScreenshotToFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveScreenToFile ) );
	this->Connect( addMesh->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSceneAddMesh ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAddView ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveScreenToFile ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSceneAddMesh ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
}

AddMeshDialog::AddMeshDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	mMeshList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_HSCROLL|wxLB_SINGLE|wxLB_SORT ); 
	MainSizer->Add( mMeshList, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	
	buttonSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mOkButton = new wxButton( this, wxOKBUTTON, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mOkButton, 0, wxALL, 5 );
	
	mApplyButton = new wxButton( this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mApplyButton, 0, wxALL, 5 );
	
	mCancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mCancelButton, 0, wxALL, 5 );
	
	MainSizer->Add( buttonSizer, 1, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AddMeshDialog::OnClose ) );
	mMeshList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddMeshDialog::OnMeshListSelect ), NULL, this );
	mOkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnOkClick ), NULL, this );
	mApplyButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnApplyClick ), NULL, this );
	mCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnCancelClick ), NULL, this );
}

AddMeshDialog::~AddMeshDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AddMeshDialog::OnClose ) );
	mMeshList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddMeshDialog::OnMeshListSelect ), NULL, this );
	mOkButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnOkClick ), NULL, this );
	mApplyButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnApplyClick ), NULL, this );
	mCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnCancelClick ), NULL, this );
}
