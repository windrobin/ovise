///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
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
	
	wxMenuItem* loadPointcloud;
	loadPointcloud = new wxMenuItem( scene, ID_LOAD_POINTCLOUD, wxString( wxT("Load Pointcloud") ) , wxEmptyString, wxITEM_NORMAL );
	scene->Append( loadPointcloud );
	
	mbar->Append( scene, wxT("Scene") ); 
	
	network = new wxMenu();
	wxMenuItem* m_networkConnect;
	m_networkConnect = new wxMenuItem( network, ID_SERVER_LISTEN, wxString( wxT("Listen for remote connection") ) , wxEmptyString, wxITEM_CHECK );
	network->Append( m_networkConnect );
	
	mbar->Append( network, wxT("Network") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
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
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnQuit ) );
	this->Connect( showStructure->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnShowSceneStructure ) );
	this->Connect( saveScreenshotToFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnSaveScreenToFile ) );
	this->Connect( dynamicShadows->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDynamicShadowsChange ) );
	this->Connect( points->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMPoints ) );
	this->Connect( wireframe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMWire ) );
	this->Connect( solid->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMSolid ) );
	this->Connect( loadPointcloud->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadPointCloud ) );
	this->Connect( m_networkConnect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnNetworkListenChange ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAbout ) );
	this->Connect( teststuff->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnTestStuff ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnQuit ) );
	this->Disconnect( ID_SHOW_STRUCTURE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnShowSceneStructure ) );
	this->Disconnect( ID_SAVE_SCREENSHOT_TO_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnSaveScreenToFile ) );
	this->Disconnect( ID_DYNAMIC_SHADOWS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDynamicShadowsChange ) );
	this->Disconnect( ID_POINTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMPoints ) );
	this->Disconnect( ID_WIREFRAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMWire ) );
	this->Disconnect( ID_SOLID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDMSolid ) );
	this->Disconnect( ID_LOAD_POINTCLOUD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnLoadPointCloud ) );
	this->Disconnect( ID_SERVER_LISTEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnNetworkListenChange ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAbout ) );
	this->Disconnect( ID_TESTSTUFF, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnTestStuff ) );
	
}

AddMeshDialog::AddMeshDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	ListSizer = new wxBoxSizer( wxHORIZONTAL );
	
	mMeshList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_NEEDED_SB|wxLB_SINGLE|wxLB_SORT ); 
	ListSizer->Add( mMeshList, 1, wxALL|wxEXPAND, 5 );
	
	MainSizer->Add( ListSizer, 4, wxEXPAND, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	
	buttonSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mOkButton = new wxButton( this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mOkButton, 0, wxALL, 5 );
	
	mApplyButton = new wxButton( this, wxID_APPLY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mApplyButton, 0, wxALL, 5 );
	
	mCancelButton = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( mCancelButton, 0, wxALL, 5 );
	
	MainSizer->Add( buttonSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AddMeshDialog::OnCloseDialog ) );
	mMeshList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddMeshDialog::OnMeshListSelect ), NULL, this );
	mOkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnOkClick ), NULL, this );
	mApplyButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnApplyClick ), NULL, this );
	mCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnCancelClick ), NULL, this );
}

AddMeshDialog::~AddMeshDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AddMeshDialog::OnCloseDialog ) );
	mMeshList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddMeshDialog::OnMeshListSelect ), NULL, this );
	mOkButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnOkClick ), NULL, this );
	mApplyButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnApplyClick ), NULL, this );
	mCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddMeshDialog::OnCancelClick ), NULL, this );
	
}

ExportMeshesDialog::ExportMeshesDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* LabelSizer;
	LabelSizer = new wxBoxSizer( wxVERTICAL );
	
	mLabel = new wxStaticText( this, wxID_ANY, wxT("Do you want to export used meshes of scene too?"), wxDefaultPosition, wxDefaultSize, 0 );
	mLabel->Wrap( -1 );
	LabelSizer->Add( mLabel, 0, wxALL, 5 );
	
	
	LabelSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	MainSizer->Add( LabelSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* ButtonSizer;
	ButtonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	mCancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mCancelButton, 0, wxALL, 5 );
	
	
	ButtonSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mOkButton = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mOkButton, 0, wxALL, 5 );
	
	mDeleteButton = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mDeleteButton, 0, wxALL, 5 );
	
	MainSizer->Add( ButtonSizer, 1, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ExportMeshesDialog::OnCloseDialog ) );
	mCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExportMeshesDialog::OnClickCancel ), NULL, this );
	mOkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExportMeshesDialog::OnClickOk ), NULL, this );
}

ExportMeshesDialog::~ExportMeshesDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ExportMeshesDialog::OnCloseDialog ) );
	mCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExportMeshesDialog::OnClickCancel ), NULL, this );
	mOkButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExportMeshesDialog::OnClickOk ), NULL, this );
	
}

_PrototypeManagementDialog::_PrototypeManagementDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	MainSizer = new wxBoxSizer( wxVERTICAL );
	
	ListBoxSizer = new wxBoxSizer( wxHORIZONTAL );
	
	mPrototypeList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SORT ); 
	ListBoxSizer->Add( mPrototypeList, 2, wxALL|wxEXPAND, 5 );
	
	MainSizer->Add( ListBoxSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* ButtonSizer;
	ButtonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	mRemoveButton = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	mRemoveButton->Enable( false );
	
	ButtonSizer->Add( mRemoveButton, 0, wxALL, 5 );
	
	mImportButton = new wxButton( this, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mImportButton, 0, wxALL, 5 );
	
	mExportButton = new wxButton( this, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	mExportButton->Enable( false );
	
	ButtonSizer->Add( mExportButton, 0, wxALL, 5 );
	
	mBuildButton = new wxButton( this, wxID_ANY, wxT("Build Prototype"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mBuildButton, 0, wxALL, 5 );
	
	mAttachButton = new wxButton( this, wxID_ANY, wxT("Attach Prototype"), wxDefaultPosition, wxDefaultSize, 0 );
	mAttachButton->Enable( false );
	
	ButtonSizer->Add( mAttachButton, 0, wxALL, 5 );
	
	mCloseButton = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSizer->Add( mCloseButton, 1, wxALL, 5 );
	
	MainSizer->Add( ButtonSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( MainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _PrototypeManagementDialog::OnCloseDialog ) );
	mPrototypeList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _PrototypeManagementDialog::OnProtoTypeListSelect ), NULL, this );
	mRemoveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickRemove ), NULL, this );
	mImportButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickImport ), NULL, this );
	mExportButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickExport ), NULL, this );
	mBuildButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickBuild ), NULL, this );
	mAttachButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickAttach ), NULL, this );
	mCloseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickClose ), NULL, this );
}

_PrototypeManagementDialog::~_PrototypeManagementDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _PrototypeManagementDialog::OnCloseDialog ) );
	mPrototypeList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _PrototypeManagementDialog::OnProtoTypeListSelect ), NULL, this );
	mRemoveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickRemove ), NULL, this );
	mImportButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickImport ), NULL, this );
	mExportButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickExport ), NULL, this );
	mBuildButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickBuild ), NULL, this );
	mAttachButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickAttach ), NULL, this );
	mCloseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrototypeManagementDialog::OnClickClose ), NULL, this );
	
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

ConnectToServerDialog::ConnectToServerDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	Sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* m_staticText3;
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Connect to:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	Sizer->Add( m_staticText3, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText4;
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer17->Add( m_staticText4, 0, wxALL, 5 );
	
	NameCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	bSizer17->Add( NameCtrl, 1, wxALL, 5 );
	
	bSizer12->Add( bSizer17, 1, wxEXPAND, 5 );
	
	Sizer->Add( bSizer12, 1, wxEXPAND, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	Sizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( Sizer );
	this->Layout();
	Sizer->Fit( this );
	
	this->Centre( wxBOTH );
}

ConnectToServerDialog::~ConnectToServerDialog()
{
}
