/***************************************************************
 * Name:      MainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#include "MainFrame.h"

//#include "../OViSEAux/SocketMessage.h"

#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/dir.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <sstream>

enum
{
	SERVER_ID = 100,
	SOCKET_ID
};


namespace {
	void SetSelectedIndex( wxCommandEvent& Event, int& Dst ) {Dst = Event.GetInt();}
};

//helper functions
enum wxbuildinfoformat {
	short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
	wxString wxbuild(wxVERSION_STRING);

	if (format == long_f )
	{
#if defined(__WXMSW__)
		wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
		wxbuild << _T("-Mac");
#elif defined(__UNIX__)
		wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
		wxbuild << _T("-Unicode build");
#else
		wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
	}

	return wxbuild;
}

MainFrame::MainFrame( wxString MediaDir, wxString PluginDir, wxWindow* ParentWindow )
: MainFrameBase(ParentWindow),
  mMediaPath( MediaDir ),
  mPluginPath( PluginDir ),
  mOgreWindow(0), 
  mInputHandler(0), 
  mCurrentEntity(0),
  mNetworkInterface( mIOService, mEntityPool )
{
#if wxUSE_STATUSBAR
	statusBar->SetStatusText(_("OViSE started up."), 0);
	statusBar->SetStatusText(wxT("FPS:"), 1);
#endif

	// Connect event handlers
	this->Connect( ID_INSERT_ENTITY, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler( MainFrame::OnInsertEntity ) );
	this->Connect( ID_REMOVE_ENTITY, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler( MainFrame::OnRemoveEntity ) );
	this->Connect( ID_ADD_ATTRIBUTE, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler( MainFrame::OnAddAttribute ) );
	this->Connect( ID_DELETE_ATTRIBUTE, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler( MainFrame::OnDeleteAttribute ) );

	mWindowManager.SetManagedWindow( this );

	mOgreWindow = new OgreWindow( mMediaPath, this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, "OgreWindow" );
	mOgreWindow->SetGraphicsInit( boost::bind( &MainFrame::InitOgre, this )  );
	mWindowManager.AddPane( mOgreWindow, wxCENTER, wxT( "RenderWindow" ) );

	// Initialize PropertyGrid
	mAttributeView.reset( new AttributeView( this ) );
	mWindowManager.AddPane( mAttributeView->GetGrid(), wxRIGHT, wxT( "Properties" ) );

	// Initialize SelectionManager
	SetupSceneTree();

	Maximize(true);

	mWindowManager.Update();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
	mWindowManager.UnInit();
	event.Skip();
}

MainFrame::~MainFrame()
{
}

void MainFrame::SetStatusMessage( wxString& Msg, int field )
{
#if wxUSE_STATUSBAR
	statusBar->SetStatusText( Msg, field);
#endif
}

void MainFrame::SetupSceneTree()
{
	// Create scene tree
	this->mSceneTree = new SceneTree(this, wxID_ANY, wxDefaultPosition, wxSize(300, -1),
		wxTR_EDIT_LABELS /*| wxTR_MULTIPLE*/ | wxTR_DEFAULT_STYLE);

	// Register EventListeners of "improved event handling": SceneTree
	this->mWindowManager.AddPane(mSceneTree, wxRIGHT, wxT("Scene structure"));

	// Link the Ogre visualization
	mEntityPool.InsertObserver( mSceneTree );

	// Fill with some test content
	/*mEntityPool.CreateEntity( "Barrel" ).Set
		( "Type", "Simple" )
		( "Model", "Barrel.mesh" )
		( "Position", vec3( -5.f, -5.f, 0.f ) )
	;*/
	
	mEntityPool.CreateEntity( "MisterRoboto").Set
		( "Type", "Robot" )
		( "Model", "Albert.mesh" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
	;
	
	mEntityPool.GetEntityById(1)->SetAttribute("Pan", 50);
	
	/*mEntityPool.CreateEntity( "Cloud" ).Set
		( "Type", "Pointcloud" )
		( "Filename", "torus.off" )
		;*/
}

bool MainFrame::InitOgre()
{
	// Create logging
	// FIXME: this causes memory leaks!
	//Ogre::LogManager *logMgr = new Ogre::LogManager;
	//Ogre::Log *log = Ogre::LogManager::getSingleton().createLog("OViSE.log", true, true, false);
	//Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener( mLogBoxListener );
	
	// Create camera setup
	Ogre::SceneManager* SceneManager = mOgreWindow->GetSceneManager();
	mCamera = SceneManager->createCamera( "MainCamera" );
	mCamera->setNearClipDistance( 0.01f );
	mCamera->setFarClipDistance( 1000.f );
	mCamera->setAutoAspectRatio( true );
	mCamera->setQueryFlags( 0x01 );

	Ogre::SceneNode* CameraFocusNode = SceneManager
		->getRootSceneNode()->createChildSceneNode( "CameraFocusNode" );
	CameraFocusNode->setFixedYawAxis( true, Ogre::Vector3::UNIT_Z );
	CameraFocusNode->yaw( Ogre::Degree( -45.f ), Ogre::Node::TS_WORLD );
	CameraFocusNode->pitch( Ogre::Degree( 45.f ), Ogre::Node::TS_LOCAL );

	typedef Ogre::Quaternion Quat;
	Ogre::SceneNode* CameraNode = CameraFocusNode->createChildSceneNode( "CameraNode" );
	CameraNode->attachObject( mCamera );
	CameraNode->setPosition( 0.f, 5.f, 0.f );
	CameraNode->setOrientation( Quat( Ogre::Degree( -90.f ), Ogre::Vector3::UNIT_X ) *
		Quat( Ogre::Degree( 180.f ), Ogre::Vector3::UNIT_Z ) );

	// Create viewport for camera
	Ogre::Viewport* Viewport = mOgreWindow->GetRenderWindow()->addViewport( mCamera );
	Viewport->setBackgroundColour( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );

	// Initialize resources
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps( 5 );

	// DBG: Testscene
	Ogre::Entity* GridPlane=SceneManager->createEntity( "GridPlane", "GridPlane.mesh" );
	GridPlane->setQueryFlags( 0x01 );
	SceneManager->getRootSceneNode()->attachObject(GridPlane);

	Ogre::Entity* CoS=SceneManager->createEntity( "CoS", "CoS.mesh" );
	SceneManager->getRootSceneNode()->attachObject( CoS );

	Ogre::Light* SunLight = SceneManager->createLight( "Sun" );
	SunLight->setShadowFarDistance( Ogre::Real( 100.f ) );
	SunLight->setCastShadows( true );
	SunLight->setDirection( -1.f, -1.f, -1.f );
	SunLight->setPosition( 100.f, 100.f, 100.f );

	// When selection in OViSESceneTree changed, call MainFrame::OnSelectionChanged(...) !
	mSceneTree->Bind( wxEVT_COMMAND_TREE_SEL_CHANGED, &MainFrame::OnTreeSelectionChanged, this );

	// Create input handler
	mInputHandler.reset( new InputHandler( mCamera, CameraFocusNode, mOgreWindow ) );

	mSceneView.reset( new SceneView( mOgreWindow->GetSceneManager(),
		boost::bind( &OgreWindow::Refresh, mOgreWindow, false, (wxRect*) 0 ) ) );

	LoadVisPlugins();

	mEntityPool.InsertObserver( mSceneView.get() );

	return true;
}

void MainFrame::LoadVisualizationPlugin( wxString Filename )
{
	typedef void (*FunctionType)( SceneView& );
	const wxString InitFunctionName( "LoadEntityView" ); // The function to load from the dynamic library

	wxString Extension;
	wxFileName::SplitPath(Filename,0,0,0,&Extension);

#ifdef WIN32
	if ( Extension != "dll" )
		return;

	// Attempt to load it.
	HMODULE Plugin=LoadLibrary(Filename.c_str());

	if ( Plugin==NULL )
	{
		DWORD Error=GetLastError(); // FIXME
		return;
	}

	FARPROC Function=GetProcAddress(Plugin,InitFunctionName.c_str());

	if ( Function )
	{
		FunctionType f = reinterpret_cast<FunctionType>(Function);
		f( *mSceneView );
	}

#else // Linux
	if ( Extension != "so" )
		return;

	void* Plugin=dlopen(Filename.c_str(), RTLD_NOW);

	if ( Plugin==NULL )
	{
		// FIXME
		std::cout << "Plugin " << " " << Filename << " failed to load:\n" << dlerror() << std::endl;
		return;
	}

	FunctionType Function=reinterpret_cast<FunctionType>(dlsym(Plugin,InitFunctionName.c_str()));

	if ( !Function )
	{
		std::cout << "Plugin entry point not found." << std::endl;
		return;
	}

	Function( *mSceneView );
#endif
}

void MainFrame::LoadNetworkPlugin( wxString Filename )
{
	typedef void (*FunctionType)( boost::asio::io_service&, EntityPool& );
	const wxString InitFunctionName( "LoadInterface" ); // The function to load from the dynamic library

	wxString Extension;
	wxFileName::SplitPath(Filename,0,0,0,&Extension);

#ifdef WIN32
	if ( Extension != "dll" )
		return;

	// Attempt to load it.
	HMODULE Plugin=LoadLibrary(Filename.c_str());

	if ( Plugin==NULL )
	{
		DWORD Error=GetLastError(); // FIXME
		return;
	}

	FARPROC Function=GetProcAddress(Plugin,InitFunctionName.c_str());

	if ( Function )
	{
		FunctionType f = reinterpret_cast<FunctionType>(Function);
		f( mIOService, mEntityPool );
	}

#else // Linux
	if ( Extension != "so" )
		return;

	void* Plugin=dlopen(Filename.c_str(), RTLD_NOW);

	if ( Plugin==NULL )
	{
		// FIXME
		std::cout << "Plugin " << " " << Filename << " failed to load:\n" << dlerror() << std::endl;
		return;
	}

	FunctionType Function=reinterpret_cast<FunctionType>(dlsym(Plugin,InitFunctionName.c_str()));

	if ( !Function )
	{
		std::cout << "Plugin entry point not found." << std::endl;
		return;
	}

	Function( mIOService, mEntityPool );
#endif
}

/** Load plugins.
*/
void MainFrame::LoadVisPlugins()
{
	wxString PluginPath;

#ifdef WIN32
#ifdef NDEBUG
	PluginPath = mPluginPath + "/Visualization/Release/";
#else
	PluginPath = mPluginPath + "/Visualization/Debug/";
#endif
#else
	PluginPath = mPluginPath + "/Visualization/";
#endif
	wxDir Directory( PluginPath );

	if ( !Directory.IsOpened() )
	{
		// FIXME: no plugins
		return;
	}

	// Check for DLL files
	wxString Filename;
	for ( bool c=Directory.GetFirst(&Filename);c;c=Directory.GetNext(&Filename) )
	{
		LoadVisualizationPlugin( PluginPath+Filename );
	}
}

void MainFrame::LoadNWPlugins()
{
	wxString PluginPath;

#ifdef WIN32
#ifdef NDEBUG
	PluginPath = mPluginPath + "/Interfaces/Release/";
#else
	PluginPath = mPluginPath + "/Interfaces/Debug/";
#endif
#else
	PluginPath = mPluginPath + "/Interfaces/";
#endif
	wxDir Directory( PluginPath );

	if ( !Directory.IsOpened() )
	{
		// FIXME: no plugins
		return;
	}

	// Check for DLL files
	wxString Filename;
	for ( bool c=Directory.GetFirst(&Filename);c;c=Directory.GetNext(&Filename) )
	{
		LoadNetworkPlugin( PluginPath+Filename );
	}
}

void MainFrame::OnQuit(wxCommandEvent &event)
{
	Close();
}

void MainFrame::OnIdle(wxIdleEvent& evt)
{
	evt.RequestMore();
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
	wxAboutDialogInfo info;
	info.SetName(wxT("OViSE"));
	info.SetVersion(wxT("0.3 Beta (gnome)"));

	wxString description = wxT("Institute of Computer Science and Engineering (CSE)\n\r");
	description += wxT("Industrial Applications of Computer Science and Micro Systems (IAIM)\n");
	description += wxT("Prof. Dr. R. Dillmann\n");
	description += wxT("http://wwwiaim.ira.uka.de\n");
	description += wxT("Department of Computer Science\n");
	description += wxT("Karlsruhe Institute of Technology (KIT)\n");
	description += wxT("Ogre Framework for scene visualization. Uses Ogre3D (http://www.ogre3d.org)");
	info.SetDescription(description);

	info.SetCopyright(wxT("(C) 2008-20010 "));

	info.AddDeveloper(wxT("Programming - Alexander Kasper <alexander.kasper@kit.edu>"));
	info.AddDeveloper(wxT("Programming - Marius Elvert <marius.elvert@googlemail.com>"));
	info.AddDeveloper(wxT("Programming - Thorsten Engelhardt <thorsten.engelhardt@student.kit.edu>"));
	info.AddDeveloper(wxT("Programming - Henning Renartz <hrenart@gmx.de>"));

	wxString licenseText = wxT("Permission is hereby granted, free of charge,");
	licenseText += wxT("to any person obtaining a copy of this software and associated documentation files (the \"Software\"), ");
	licenseText += wxT("to deal in the Software without restriction, including without limitation the rights to use, copy, modify, ");
	licenseText += wxT("merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the ");
	licenseText += wxT("Software is furnished to do so, subject to the following conditions:\n\n");
	licenseText += wxT("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\n");
	licenseText += wxT("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED ");
	licenseText += wxT("TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE ");
	licenseText += wxT("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, ");
	licenseText += wxT("TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
	info.SetLicense(licenseText);

	info.SetWebSite(wxT("http://code.google.com/p/ovise/"));

	wxAboutBox(info);
}

void MainFrame::OnSaveScreenToFile(wxCommandEvent &event)
{
	wxFileDialog fDialog(this, wxT("Save screen to file"), wxGetHomeDir(), wxT("OViSEScreenshot.png"),
		wxT("PNG files (*.png)|*.png"), wxFD_SAVE);
	int rval = fDialog.ShowModal();
	wxSafeYield();
	if(rval == wxID_OK)
	{
		wxString fullPath = fDialog.GetPath();
		mOgreWindow->GetRenderWindow()->writeContentsToFile(Ogre::String(fullPath.ToAscii()));
	}
}

void MainFrame::OnViewClick(wxMouseEvent& event)
{
	/*wxPoint p = event.GetPosition();
	wxPoint t = mMainRenderWin->GetScreenPosition();
	int width = mRenderWin->getWidth();
	int height = mRenderWin->getHeight();
	wxPoint s = p;
	float sx = (float)s.x / (float)width;
	float sy = (float)s.y / (float)height;
	float d = -1;

	Ogre::Ray tRay = OgreMediator::GetSingletonPtr()->iSceneManager.Assist_GetRayForRaySceneQuery(sx, sy, mCam);
	QualifiedNameCollection QNames = OgreMediator::GetSingletonPtr()->iSceneManager.QueryObjectsByRay(tRay, OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager());
*/
}

void MainFrame::OnDynamicShadowsChange(wxCommandEvent& event)
{
	if(event.IsChecked())
	{
		mOgreWindow->GetSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	}
	else
	{
		mOgreWindow->GetSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	}
}


void MainFrame::OnNetworkListenChange(wxCommandEvent& event)
{
	if(event.IsChecked())
	{
		//start listening
		std::cout << "Start listening for remote connection" << std::endl;
		//mEntityPool.GetEntityById(1)->SetAttribute("Pan", 50);
		//mEntityPool.RemoveEntityById(1);

	}
	else
	{
		//stop listening
		std::cout << "Stop listening for remote connection." << std::endl;
		//mEntityPool.GetEntityById(1)->SetAttribute("Pan", 50);
		//mEntityPool.RemoveEntityById(2);
		//mNetworkInterface.StopListening();
	}
}

void MainFrame::OnInsertEntity( wxCommandEvent& Event )
{
	wxTextEntryDialog Dialog( this, "Name the new entity:", "Create Entity" );

	if ( Dialog.ShowModal() == wxID_OK )
	{
		// FIXME: validate the name
		std::string EntityName(Dialog.GetValue().mb_str());
		Entity* e = new Entity();
		e->SetName( EntityName );

		mEntityPool.InsertEntity( e );
	}
}

void MainFrame::OnRemoveEntity( wxCommandEvent& Event )
{
	if ( mCurrentEntity )
		mEntityPool.RemoveEntity( mCurrentEntity );

	mCurrentEntity = 0;
}


void MainFrame::OnAddAttribute( wxCommandEvent& Event )
{
	if ( !mCurrentEntity )
		return;

	// Setup the "add attribute" dialog
	AddAttributeDialog Dialog( this );
	int SelectedType = 0;
	Dialog.Sizer->Add( Dialog.CreateButtonSizer(wxOK|wxCANCEL), 0, wxEXPAND,5);
	Dialog.Sizer->Fit( &Dialog );

	// Bind selection events to change 'SelectedType'
	boost::function<void(wxCommandEvent&)> Func = boost::bind( &SetSelectedIndex, _1, boost::ref( SelectedType ) );
	Dialog.TypeRadioBox->Bind( wxEVT_COMMAND_RADIOBOX_SELECTED,Func);

	if ( Dialog.ShowModal() == wxID_OK )
	{
		std::string AttribName(Dialog.NameCtrl->GetValue().mb_str());
		std::string AttribValue(Dialog.ValueCtrl->GetValue().mb_str());

		//FIXME: use type information, not just strings!

		if ( mCurrentEntity->GetAttribute( AttribName ) )
		{
			wxMessageBox( "Attribute of that name already exists!",
				"Error while adding attribute", 4|wxCENTRE, this );
			return;
		}

		try {

		switch( SelectedType )
		{
		default:
		case 0:
			// Int
			mCurrentEntity->Set<int>( AttribName, boost::lexical_cast<int>(AttribValue) );
			break;
		case 1:
			// String
			mCurrentEntity->Set<std::string>( AttribName, AttribValue );
			break;
		case 2:
			// Float
			mCurrentEntity->Set<double>( AttribName, boost::lexical_cast<double>(AttribValue) );
			break;
		}
		}
		catch( boost::bad_lexical_cast& )
		{
			wxMessageBox( "Unable to convert value to the set type.",
				"Error while adding attribute", 4|wxCENTRE, this );
		}
	}
}

void MainFrame::OnDeleteAttribute( wxCommandEvent& Event )
{
	if ( !mCurrentEntity )
		return;

	wxPropertyGrid* Grid = mAttributeView->GetGrid();
	wxPGProperty* Selected = Grid->GetSelection();

	if ( !Selected )
		return;

	std::string Name( Selected->GetName().mb_str() );
	mCurrentEntity->RemoveAttribute( Name );
}


void MainFrame::OnConnectServer( wxCommandEvent& Event )
{

}

void MainFrame::OnTreeSelectionChanged( wxTreeEvent& Event )
{
	wxTreeItemId Item = Event.GetItem();
	Entity* Selected = mSceneTree->GetEntity(Item);

	mCurrentEntity = Selected;
	mAttributeView->SetEntity( Selected );
}


void MainFrame::OnShowSceneStructure(wxCommandEvent &event)
{
}

void MainFrame::OnDMPoints(wxCommandEvent &evt)
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_POINTS );
}

void MainFrame::OnDMWire(wxCommandEvent &evt)
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_WIREFRAME );
}

void MainFrame::OnDMSolid(wxCommandEvent &evt)
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_SOLID );
}

void MainFrame::OnTestStuff( wxCommandEvent& event )
{
}
