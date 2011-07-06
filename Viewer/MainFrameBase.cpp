///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 22 2011)
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

#include "MainFrameBase.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* loadScene;
	loadScene = new wxMenuItem( fileMenu, ID_LOAD_SCENE, wxString( wxT("&Load scene") ) + wxT('\t') + wxT("Alt+L"), wxT("Load scene from .scene file"), wxITEM_NORMAL );
	fileMenu->Append( loadScene );
	
	wxMenuItem* loadPointcloud;
	loadPointcloud = new wxMenuItem( fileMenu, ID_LOAD_POINTCLOUD, wxString( wxT("Load pointcloud") ) , wxT("Load scene from .scene file"), wxITEM_NORMAL );
	fileMenu->Append( loadPointcloud );
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") ); 
	
	view = new wxMenu();
	wxMenuItem* showStructure;
	showStructure = new wxMenuItem( view, ID_SHOW_STRUCTURE, wxString( wxT("Show Structure") ) , wxT("Show Scene Structure"), wxITEM_NORMAL );
	view->Append( showStructure );
	
	wxMenuItem* saveScreenshotToFile;
	saveScreenshotToFile = new wxMenuItem( view, ID_SAVE_SCREENSHOT_TO_FILE, wxString( wxT("Save Screenshot to File...") ) , wxT("Saves a screenshot of the view to a file specified by the user."), wxITEM_NORMAL );
	view->Append( saveScreenshotToFile );
	
	wxMenuItem* dynamicShadows;
	dynamicShadows = new wxMenuItem( view, ID_DYNAMIC_SHADOWS, wxString( wxT("Dynamic Shadows") ) , wxEmptyString, wxITEM_CHECK );
	view->Append( dynamicShadows );
	
	displayMode = new wxMenu();
	points = new wxMenuItem( displayMode, ID_POINTS, wxString( wxT("Points") ) , wxEmptyString, wxITEM_RADIO );
	displayMode->Append( points );
	
	wireframe = new wxMenuItem( displayMode, ID_WIREFRAME, wxString( wxT("Wireframe") ) , wxEmptyString, wxITEM_RADIO );
	displayMode->Append( wireframe );
	
	solid = new wxMenuItem( displayMode, ID_SOLID, wxString( wxT("Solid") ) , wxEmptyString, wxITEM_RADIO );
	displayMode->Append( solid );
	solid->Check( true );
	
	view->Append( -1, wxT("Display Mode"), displayMode );
	
	mbar->Append( view, wxT("View") ); 
	
	scene = new wxMenu();
	wxMenuItem* m_menuInsertEntity;
	m_menuInsertEntity = new wxMenuItem( scene, ID_INSERT_ENTITY, wxString( wxT("Insert Entity") ) , wxEmptyString, wxITEM_NORMAL );
	scene->Append( m_menuInsertEntity );
	
	wxMenuItem* m_menuRemoveEntity;
	m_menuRemoveEntity = new wxMenuItem( scene, ID_REMOVE_ENTITY, wxString( wxT("Remove Entity") ) , wxEmptyString, wxITEM_NORMAL );
	scene->Append( m_menuRemoveEntity );
	
	wxMenuItem* m_separator3;
	m_separator3 = scene->AppendSeparator();
	
	wxMenuItem* m_menuAddAttribute;
	m_menuAddAttribute = new wxMenuItem( scene, ID_ADD_ATTRIBUTE, wxString( wxT("Add Attribute") ) , wxEmptyString, wxITEM_NORMAL );
	scene->Append( m_menuAddAttribute );
	
	wxMenuItem* m_menuDeleteAttribute;
	m_menuDeleteAttribute = new wxMenuItem( scene, ID_DELETE_ATTRIBUTE, wxString( wxT("Delete Attribute") ) , wxEmptyString, wxITEM_NORMAL );
	scene->Append( m_menuDeleteAttribute );
	
	wxMenuItem* m_separator2;
	m_separator2 = scene->AppendSeparator();
	
	mbar->Append( scene, wxT("Scene") ); 
	
	network = new wxMenu();
	mbar->Append( network, wxT("Network") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	wxMenuItem* plugins;
	plugins = new wxMenuItem( helpMenu, ID_PLUGINS, wxString( wxT("Plugins...") ) , wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( plugins );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	debug = new wxMenu();
	wxMenuItem* teststuff;
	teststuff = new wxMenuItem( debug, ID_TESTSTUFF, wxString( wxT("TestStuff") ) , wxEmptyString, wxITEM_NORMAL );
	debug->Append( teststuff );
	
	mbar->Append( debug, wxT("Debug") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnClose ) );
	this->Connect( loadScene->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadScene ) );
	this->Connect( loadPointcloud->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadPointcloud ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnQuit ) );
	this->Connect( showStructure->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnShowSceneStructure ) );
	this->Connect( saveScreenshotToFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnSaveScreenToFile ) );
	this->Connect( dynamicShadows->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDynamicShadowsChange ) );
	this->Connect( points->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMPoints ) );
	this->Connect( wireframe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMWire ) );
	this->Connect( solid->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMSolid ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAbout ) );
	this->Connect( plugins->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnPluginsSummary ) );
	this->Connect( teststuff->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnTestStuff ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnClose ) );
	this->Disconnect( ID_LOAD_SCENE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadScene ) );
	this->Disconnect( ID_LOAD_POINTCLOUD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadPointcloud ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnQuit ) );
	this->Disconnect( ID_SHOW_STRUCTURE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnShowSceneStructure ) );
	this->Disconnect( ID_SAVE_SCREENSHOT_TO_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnSaveScreenToFile ) );
	this->Disconnect( ID_DYNAMIC_SHADOWS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDynamicShadowsChange ) );
	this->Disconnect( ID_POINTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMPoints ) );
	this->Disconnect( ID_WIREFRAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMWire ) );
	this->Disconnect( ID_SOLID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMSolid ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAbout ) );
	this->Disconnect( ID_PLUGINS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnPluginsSummary ) );
	this->Disconnect( ID_TESTSTUFF, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnTestStuff ) );
	
}

PathConfigDialog::PathConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mMainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* BasePathSizer;
	BasePathSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Plugins Path") ), wxVERTICAL );
	
	mPluginDirPicker = new wxDirPickerCtrl( this, wxID_ANY, wxT("Not configured"), wxT("Select OViSE's base folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST );
	BasePathSizer->Add( mPluginDirPicker, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	mMainSizer->Add( BasePathSizer, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* MediaPathSizer;
	MediaPathSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Media Path") ), wxVERTICAL );
	
	mMediaDirPicker = new wxDirPickerCtrl( this, wxID_ANY, wxT("Not configured"), wxT("Select OViSE's media folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST );
	MediaPathSizer->Add( mMediaDirPicker, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	mMainSizer->Add( MediaPathSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( mMainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

PathConfigDialog::~PathConfigDialog()
{
}

AddAttributeDialog::AddAttributeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	Sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* m_staticText3;
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Create a new attribute:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	Sizer->Add( m_staticText3, 0, wxALL, 5 );
	
	wxString TypeRadioBoxChoices[] = { wxT("Integer"), wxT("String"), wxT("Floating-point number") };
	int TypeRadioBoxNChoices = sizeof( TypeRadioBoxChoices ) / sizeof( wxString );
	TypeRadioBox = new wxRadioBox( this, wxID_ANY, wxT("Attribute Type"), wxDefaultPosition, wxDefaultSize, TypeRadioBoxNChoices, TypeRadioBoxChoices, 2, wxRA_SPECIFY_COLS );
	TypeRadioBox->SetSelection( 0 );
	Sizer->Add( TypeRadioBox, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText4;
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer12->Add( m_staticText4, 0, wxALL, 5 );
	
	NameCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( NameCtrl, 1, wxALL, 5 );
	
	wxStaticText* m_staticText5;
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer12->Add( m_staticText5, 0, wxALL, 5 );
	
	ValueCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( ValueCtrl, 1, wxALL, 5 );
	
	Sizer->Add( bSizer12, 1, wxEXPAND, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	Sizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( Sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

AddAttributeDialog::~AddAttributeDialog()
{
}

CSettingsDlg::CSettingsDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer6->Add( m_staticText8, 0, wxALL, 5 );
	
	HostTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( HostTextCtrl, 1, wxALL|wxEXPAND, 5 );
	
	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer7->Add( m_staticText9, 0, wxALL, 5 );
	
	PortTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( PortTextCtrl, 1, wxALL|wxEXPAND, 5 );
	
	bSizer4->Add( bSizer7, 1, wxEXPAND, 5 );
	
	RememberSettingsCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Remember settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( RememberSettingsCheckBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer4->Add( m_sdbSizer1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

CSettingsDlg::~CSettingsDlg()
{
}

PluginsDialog::PluginsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	PluginList = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	bSizer7->Add( PluginList, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	bSizer7->Add( m_sdbSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

PluginsDialog::~PluginsDialog()
{
}
