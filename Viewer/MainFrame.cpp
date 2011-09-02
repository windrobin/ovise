/***************************************************************
 * Name:      MainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#include "MainFrame.h"

#include "../Util/SceneLoader.h"
#include "../Util/VertexData.h"

#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/dir.h>
#include <wx/config.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <sstream>

COViSEFrameListener::COViSEFrameListener( CCS::CameraControlSystem* CCS )
	: mCCS( CCS )
{}

bool COViSEFrameListener::frameEnded( const Ogre::FrameEvent& evt )
{
	mCCS->update( evt.timeSinceLastFrame );
	return true;
}

namespace
{
	void SetSelectedIndex( wxCommandEvent& Event, int& Dst ) {
		Dst = Event.GetInt();
	}
};

// helper functions
enum wxbuildinfoformat {
	short_f, long_f
};

wxString wxbuildinfo( wxbuildinfoformat format )
{
	wxString wxbuild( wxVERSION_STRING );

	if (format == long_f )
	{
#if defined( __WXMSW__ )
		wxbuild << _T( "-Windows" );
#elif defined( __WXMAC__ )
		wxbuild << _T( "-Mac" );
#elif defined( __UNIX__ )
		wxbuild << _T( "-Linux" );
#endif

#if wxUSE_UNICODE
		wxbuild << _T( "-Unicode build" );
#else
		wxbuild << _T( "-ANSI build" );
#endif // wxUSE_UNICODE
	}

	return wxbuild;
}

namespace {
bool GetDLLDetails( wxString Name, 
	wxDynamicLibraryDetails& Details, 
	const wxDynamicLibraryDetailsArray& List )
{
	for( std::size_t i=0; i<List.GetCount(); i++ )
	{
		if( List.Item(i).GetName().Contains( Name ) )
		{
			Details = List.Item(i);
			return true;
		}
	}
	
	return false;
}
}

MainFrame::MainFrame( wxString  MediaDir,
                      wxString  PluginDir,
                      wxWindow* ParentWindow )
	: MainFrameBase( ParentWindow ),
	mMediaPath( MediaDir ),
	mPluginPath( PluginDir ),
	mOgreWindow( 0 ),
	mInputHandler( 0 )
{
#if wxUSE_STATUSBAR
	statusBar->SetStatusText( _( "OViSE started up." ), 0 );
	statusBar->SetStatusText( wxT( "FPS:" ), 1 );
#endif
	// Connect event handlers
	Bind( wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnInsertEntity, this, ID_INSERT_ENTITY );
	Bind( wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnRemoveEntity, this, ID_REMOVE_ENTITY );
	Bind( wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAddAttribute, this, ID_ADD_ATTRIBUTE );
	Bind( wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnDeleteAttribute, this, ID_DELETE_ATTRIBUTE );
	Bind( wxEVT_IDLE, &MainFrame::OnIdle, this, wxID_ANY );

	mWindowManager.SetManagedWindow( this );

	mOgreWindow = new OgreWindow( mMediaPath, this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, "OgreWindow" );
	mOgreWindow->SetGraphicsInit( boost::bind( &MainFrame::InitOgre, this )  );
	mWindowManager.AddPane( mOgreWindow, wxCENTER, wxT( "RenderWindow" ) );

	mOgreWindow->Bind( wxEVT_LEFT_DOWN, &MainFrame::OnViewClick, this );

	// Initialize PropertyGrid
	mAttributeView.reset( new AttributeView( this ) );
	mWindowManager.AddPane( mAttributeView->GetGrid(), wxRIGHT,
		wxT( "Properties" ) );

	// Initialize SelectionManager
	SetupSceneTree();

	CAppContext::instance().SelectionChangedSignal.connect(
		boost::bind( &MainFrame::OnSelectionChange, this, _1, _2 ) );
	
	Maximize( true );

	mWindowManager.Update();
}

void MainFrame::OnClose( wxCloseEvent& event )
{
	mNetworkTimer.Stop();
	mWindowManager.UnInit();
	event.Skip();
}

MainFrame::~MainFrame()
{
	// need to manually delete this to make sure it gets cleaned up before
	// the plugins are unloaded
	//mSceneView.reset();
}

void MainFrame::OnIdle( wxIdleEvent& Event )
{
	mOgreWindow->UpdateOgre();
	Event.RequestMore();
}

void MainFrame::OnLoadScene( wxCommandEvent& event )
{
	wxFileDialog OpenFileDialog( this,
	                             wxT( " Load .scene file " ), "", "",
	                             "scene files (*.scene)|*.scene",
	                             wxFD_OPEN | wxFD_FILE_MUST_EXIST );

	if( OpenFileDialog.ShowModal() == wxID_CANCEL )
		return;

	std::string Filename( OpenFileDialog.GetPath().mb_str() );

	LoadSceneFromXML( Filename, mEntityPool );
}

void MainFrame::OnLoadPointcloud( wxCommandEvent& event )
{
	wxFileDialog OpenFileDialog( this,
	                             wxT( " Load pointcloud from file " ),
	                             "", "",
	                             "OFF files (*.off)|*.off|PLY files (*.ply)|*.ply",
	                             wxFD_OPEN | wxFD_FILE_MUST_EXIST );

	if( OpenFileDialog.ShowModal() == wxID_CANCEL )
		return;

	std::string Filename( OpenFileDialog.GetPath().mb_str() );

	mEntityPool.CreateEntity( Filename ).Set
		( "Type", "Pointcloud" )
		( "Filename", Filename )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Orientation", quat( 1.f, 0.f, 0.f, 0.f ) )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
		( "PointSize", 0.05f )
	;
}

void MainFrame::OnSelectionChange( Entity* NewSel, Entity* OldSel )
{
	if( NewSel == NULL )
	{
		// need to clear the selection here
		mSceneTree->SelectItem( mSceneTree->GetRootItem() );
	}
	else
	{
		wxTreeItemId Item;
		if( mSceneTree->GetTreeItem( NewSel, Item ) )
		{
			mSceneTree->SelectItem( Item );
		}
	}
}

void MainFrame::SetStatusMessage( wxString& Msg, int field )
{
#if wxUSE_STATUSBAR
	statusBar->SetStatusText( Msg, field );
#endif
}

void MainFrame::SetupSceneTree()
{
	// Create scene tree
	this->mSceneTree = new SceneTree( this,
		wxID_ANY,
		wxDefaultPosition,
		wxSize( 300, -1 ),
		wxTR_EDIT_LABELS /*| wxTR_MULTIPLE*/ | wxTR_DEFAULT_STYLE );

	// Register EventListeners of "improved event handling": SceneTree
	this->mWindowManager.AddPane( mSceneTree, wxRIGHT,
		wxT( "Scene structure" ));

	/*mEntityPool.CreateEntity( "MisterRoboto" ).Set
		( "Type", "Robot" )
		( "Model", "Albert.mesh" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
	;*/

	/*std::vector<Ogre::Vector3> TestTrajectory;
	TestTrajectory.push_back( vec3(0.f, 0.f, 0.f) );
	TestTrajectory.push_back( vec3(1.f, 0.f, 0.f) );
	TestTrajectory.push_back( vec3(1.f, 1.f, 0.f) );
	TestTrajectory.push_back( vec3(1.f, 1.f, 1.f) );
	
	mEntityPool.CreateEntity( "TestTrajectory" ).Set
		( "Type", "Trajectory" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Color", vec3( 0.f, 0.f, 0.f ) )
		( "PointSize", 0.02f )
		( "Points", TestTrajectory )
	;*/

	/*mEntityPool.CreateEntity( "TestHand" ).Set
		( "Type", "Skeletal" )
		( "Position", Ogre::Vector3::ZERO )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
		( "Model", "RainerHand.mesh" )
	;*/

	/*mEntityPool.CreateEntity( "TestCloud" ).Set
		( "Type", "Pointcloud" )
		( "Filename", "C:/Dev/Test.ply" )
		( "Position", vec3( 0.f, 0.f, 0.f ) )
		( "Orientation", quat( 1.f, 0.f, 0.f, 0.f ) )
		( "Scale", vec3( 1.f, 1.f, 1.f ) )
		( "PointSize", 0.05f )
	;*/

	// Link the Ogre visualization
	mEntityPool.InsertObserver( mSceneTree );
	mEntityPool.InsertObserver( mAttributeView.get() );
}

bool MainFrame::InitOgre()
{
	// Create camera setup
	Ogre::SceneManager* SceneManager = mOgreWindow->GetSceneManager();
	mCamera = SceneManager->createCamera( "MainCamera" );
	mCamera->setNearClipDistance( 0.01f );
	mCamera->setFarClipDistance( 1000.f );
	mCamera->setAutoAspectRatio( true );
	mCamera->setQueryFlags( 0x01 );

	Ogre::SceneNode* CameraFocusNode = 
		SceneManager->getRootSceneNode()->createChildSceneNode( "CameraFocusNode" );
	CameraFocusNode->pitch( Ogre::Degree( 90.f ), Ogre::Node::TS_WORLD );
	CameraFocusNode->setPosition( 0.f, 0.f, 1.f );
	
	// Create viewport for camera
	Ogre::Viewport* Viewport = 
		mOgreWindow->GetRenderWindow()->addViewport( mCamera );
	Viewport->setBackgroundColour( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );

	// Initialize resources
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps( 5 );

	// setup camera control system
	mCCS.reset( new CCS::CameraControlSystem( SceneManager, "CCS", mCamera, true ) );
	mCCS->setFixedYawAxis( true, Ogre::Vector3::UNIT_Z );
	mCCS->setCameraTarget( CameraFocusNode );

	// DBG: Testscene
	Ogre::Entity* GridPlane = 
		SceneManager->createEntity( "GridPlane", "GridPlane.mesh" );
	GridPlane->setQueryFlags( 0x01 );
	SceneManager->getRootSceneNode()->attachObject( GridPlane );

	Ogre::Entity* CoS=SceneManager->createEntity( "CoS", "CoS.mesh" );
	SceneManager->getRootSceneNode()->attachObject( CoS );

	Ogre::Light* SunLight = SceneManager->createLight( "Sun" );
	SunLight->setShadowFarDistance( Ogre::Real( 100.f ) );
	SunLight->setCastShadows( true );
	SunLight->setDirection( -1.f, -1.f, -1.f );
	SunLight->setPosition( 100.f, 100.f, 100.f );

	// When selection in OViSESceneTree changed, call MainFrame::OnSelectionChanged(...) !
	mSceneTree->Bind( wxEVT_COMMAND_TREE_SEL_CHANGED,
		&MainFrame::OnTreeSelectionChanged,
		this );

	// Create input handler
	mInputHandler.reset( new InputHandler( mCCS.get(), mOgreWindow ) );

	mSceneView.reset( new SceneView( mOgreWindow->GetSceneManager(),
			boost::bind( &OgreWindow::Refresh, mOgreWindow, false,
				(wxRect*) 0 ) ) );

	mPluginManager.reset( new CPluginManager( mEntityPool, mSceneView.get(), this ) );
	mPluginManager->LoadPlugins( mPluginPath );

	std::set<std::string> Interfaces = mPluginManager->GetInterfaceManager().GetInterfaceNames();
	for( std::set<std::string>::iterator i = Interfaces.begin();
	     i != Interfaces.end(); i++ )
	{
		wxMenuItem* InterfaceItem = network->AppendCheckItem( wxID_ANY, *i );
		boost::function< void ( wxCommandEvent& ) > InitHandler(
		        boost::bind( &MainFrame::OnNetworkInterfaceCheck,
				this, _1, *i ) );

		Bind( wxEVT_COMMAND_MENU_SELECTED, InitHandler,	InterfaceItem->GetId() );
	}

	mNetworkTimer.Bind( wxEVT_TIMER, &MainFrame::OnNetworkTimer, this );

	mEntityPool.InsertObserver( mSceneView.get() );

	mOrbitalCamMode.reset( new CCS::OrbitalCameraMode( mCCS.get(), 2.f, Ogre::Radian(), Ogre::Radian( Ogre::Degree( -45.f ) )  ) );
	mCCS->registerCameraMode( "Orbital", mOrbitalCamMode.get() );
	mCCS->setCurrentCameraMode( mCCS->getCameraMode("Orbital") );
	mOgreWindow->GetRoot()->addFrameListener( new COViSEFrameListener( mCCS.get() ) );

	mRaySceneQuery.reset( new Ogre::DefaultRaySceneQuery( SceneManager ) );

	return true;
}

void MainFrame::OnNetworkInterfaceCheck( wxCommandEvent& Event,
                                         std::string&    Name )
{
	CNetworkInterface& Interface = mPluginManager->GetInterfaceManager().GetInterface( Name );

	if( Event.IsChecked() )
	{
		/*if( Interface->NeedsConfig() )
		{
			CSettingsDlg Settings( this );

			wxConfig Config( "OViSE" );
			if( Config.HasGroup( wxString(Name.c_str()) ) )
			{
				wxString ConfHost = Config.Read( wxString(Name.c_str()) + wxT("/Host") );
				wxString ConfPort = Config.Read( wxString(Name.c_str()) + wxT("/Port") );

				Settings.HostTextCtrl->SetValue( ConfHost );
				Settings.PortTextCtrl->SetValue( ConfPort );
				Settings.RememberSettingsCheckBox->SetValue( true );
			}

			if( Settings.ShowModal() != wxID_OK )
				return;

			if( Settings.RememberSettingsCheckBox->IsChecked() )
			{
				Config.Write( wxString(Name.c_str()) + wxT("/Host"), 
					Settings.HostTextCtrl->GetValue() );
				Config.Write( wxString(Name.c_str()) + wxT("/Port"), 
					Settings.PortTextCtrl->GetValue() );
			}
			Host = std::string( Settings.HostTextCtrl->GetValue().mb_str() );
			Port = std::string( Settings.PortTextCtrl->GetValue().mb_str() );
		}
		else
		{
			Host = "";
			Port = "";
		}*/

		/*if( Interface.GetConfigDialog() == NULL )
			Interface.CreateConfigDialog( this );

		wxPropertySheetDialog* ConfDlg = Interface.GetConfigDialog();
		if( ConfDlg && ConfDlg->ShowModal() == wxID_OK )
		{
			wxString msg = wxT( "Starting interface " ) + wxString( Name );
			SetStatusMessage( msg );
			if( Interface.Start() && !mNetworkTimer.IsRunning() )
				mNetworkTimer.Start( 50 );
		}
		else if( !ConfDlg ) // no config dialog, try to start anyway
		{
			wxString msg = wxT( "Starting interface " ) + wxString( Name );
			SetStatusMessage( msg );
			if( Interface.Start() && !mNetworkTimer.IsRunning() )
				mNetworkTimer.Start( 50 );
		}*/

		wxString msg = wxT( "Starting interface " ) + wxString( Name );
		SetStatusMessage( msg );
		if( Interface.Start() && !mNetworkTimer.IsRunning() )
			mNetworkTimer.Start( 50 );
	}
	else
	{
		wxString msg = wxT( "Stopping interface " ) + wxString( Name );
		SetStatusMessage( msg );
		Interface.Stop();
		
		if( !mPluginManager->GetInterfaceManager().HasInterfaceRunning() )
			mNetworkTimer.Stop();
	}
}

void MainFrame::OnQuit( wxCommandEvent &event )
{
	Close();
}

void MainFrame::OnNetworkTimer( wxTimerEvent& Event )
{
	if( mPluginManager->GetInterfaceManager().HasInterfaceRunning() )
		mPluginManager->GetInterfaceManager().PollInterfaces();
	else
		mNetworkTimer.Stop();
}

void MainFrame::OnAbout( wxCommandEvent &event )
{
	wxAboutDialogInfo info;
	info.SetName( wxT( "OViSE" ));
	info.SetVersion( wxT( "0.4 Beta (troll)" ));

	wxString description = wxT( "Institute for Anthropomatics (IfA)\n\r" );
	description += wxT( "Humanoid and Intelligence Systems Lab (HIS)\n" );
	description += wxT( "Prof. Dr. R. Dillmann\n" );
	description += wxT( "http://his.anthropomatik.kit.edu\n" );
	description += wxT( "Department of Computer Science\n" );
	description += wxT( "Karlsruhe Institute of Technology (KIT)\n" );
	description += wxT(	"Ogre Framework for scene visualization. Uses Ogre3D (http://www.ogre3d.org)" );
	info.SetDescription( description );

	info.SetCopyright( wxT( "(C) 2008-2011 " ));

	info.AddDeveloper( wxT( "Programming - Alexander Kasper <alexander.kasper@kit.edu>" ));
	info.AddDeveloper( wxT( "Programming - Marius Elvert <marius.elvert@googlemail.com>" ));
	info.AddDeveloper( wxT( "Programming - Thorsten Engelhardt <thorsten.engelhardt@student.kit.edu>" ));
	info.AddDeveloper( wxT(	"Programming - Henning Renartz <hrenart@gmx.de>" ));

	wxString licenseText = wxT(	"Permission is hereby granted, free of charge," );
	licenseText += wxT(	"to any person obtaining a copy of this software and associated documentation files (the \"Software\"), " );
	licenseText += wxT(	"to deal in the Software without restriction, including without limitation the rights to use, copy, modify, " );
	licenseText += wxT(	"merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the " );
	licenseText += wxT(	"Software is furnished to do so, subject to the following conditions:\n\n" );
	licenseText += wxT(	"The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\n" );
	licenseText += wxT(	"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED " );
	licenseText += wxT(	"TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE " );
	licenseText += wxT(	"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, " );
	licenseText += wxT(	"TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." );
	info.SetLicense( licenseText );

	info.SetWebSite( wxT( "http://code.google.com/p/ovise/" ));

	wxAboutBox( info );
}

void MainFrame::OnPluginsSummary( wxCommandEvent& event )
{
	PluginsDialog PDlg( this );
	PDlg.PluginList->InsertColumn( 0, wxT( "Plugin" ) );
	PDlg.PluginList->InsertColumn( 1, wxT( "Version" ) );
	PDlg.PluginList->InsertColumn( 2, wxT( "Type" ) );
	PDlg.PluginList->InsertColumn( 3, wxT( "Path" ) );
	PDlg.PluginList->SetColumnWidth( 0, 150 );
	PDlg.PluginList->SetColumnWidth( 1, 55 );
	PDlg.PluginList->SetColumnWidth( 3, 600 );

	long Index = 0;
	wxDynamicLibraryDetailsArray DLLDetails = 
		wxDynamicLibrary::ListLoaded();

	const std::map<std::string, DllPtr>& Plugins = mPluginManager->GetPlugins();

	for( std::map<std::string, DllPtr>::const_iterator i = Plugins.begin();
		 i != Plugins.end(); i++ )
	{
		Index = PDlg.PluginList->InsertItem( 0, i->first );
		wxDynamicLibraryDetails Details;
		if( GetDLLDetails( i->second->GetName(), Details, DLLDetails ) )
		{
			PDlg.PluginList->SetItem( Index, 1, Details.GetVersion() );
			PDlg.PluginList->SetItem( Index, 3, Details.GetPath() );
		}
		else
			PDlg.PluginList->SetItem( Index, 1, wxT( "N/A" ) );

		switch( i->second->GetType() )
		{
		case CPluginBase::PLUGIN_TYPE_NETWORK:
			PDlg.PluginList->SetItem( Index, 2, wxT( "Network" ) );
			break;
		case CPluginBase::PLUGIN_TYPE_VISUAL:
			PDlg.PluginList->SetItem( Index, 2, wxT( "Visualization" ) );
			break;
		case CPluginBase::PLUGIN_TYPE_SENSOR:
			PDlg.PluginList->SetItem( Index, 2, wxT( "Sensor" ) );
			break;
		default:
			PDlg.PluginList->SetItem( Index, 2, wxT( "Unknown" ) );
			break;
		}
	}

	PDlg.ShowModal();
}

void MainFrame::OnSaveScreenToFile( wxCommandEvent &event )
{
	wxFileDialog fDialog( this, wxT( "Save screen to file" ),
	                      wxGetHomeDir(),  
						  wxFileName::CreateTempFileName(wxT("OViSE")),
	                      wxT( "PNG files (*.png)|*.png" ), wxFD_SAVE );
	int rval = fDialog.ShowModal();
	wxYieldIfNeeded();
	if(rval == wxID_OK)
	{
		wxString fullPath = fDialog.GetPath();
		mOgreWindow->GetRenderWindow()->writeContentsToFile(
			Ogre::String( fullPath.ToAscii()));
	}
}

void MainFrame::OnViewClick( wxMouseEvent& event )
{
	wxPoint p = event.GetPosition();
	int width = mOgreWindow->GetRenderWindow()->getWidth();
	int height = mOgreWindow->GetRenderWindow()->getHeight();
	float sx = (float)p.x / (float)width;
	float sy = (float)p.y / (float)height;
	
	Ogre::Ray MouseRay = mCamera->getCameraToViewportRay( sx, sy );
	mRaySceneQuery->setRay( MouseRay );
	mRaySceneQuery->setSortByDistance( true );

	Ogre::RaySceneQueryResult& QueryResult = mRaySceneQuery->execute();

	if( QueryResult.size() == 0 ) 
	{
		CAppContext::instance().ClearSelection();
		return;
	}

	// Taken from: http://www.ogre3d.org/tikiwiki/Raycasting+to+the+polygon+level&structure=Cookbook
	// at this point we have raycast to a series of different objects bounding boxes. 
	// we need to test these different objects to see which is the first polygon hit. 
	// there are some minor optimizations (distance based) that mean we wont have to 
	// check all of the objects most of the time, but the worst case scenario is that 
	// we need to test every triangle of every object. 
	Ogre::Real ClosestDistance = -1.0f;
	Ogre::Entity* ClosestResult;

	for( size_t QRIndex = 0; QRIndex < QueryResult.size(); QRIndex++ ) 
	{ 
		// stop checking if we have found a raycast hit that is closer 
		// than all remaining entities 
		if( ( ClosestDistance >= 0.0f ) && 
			( ClosestDistance < QueryResult[QRIndex].distance ) )
			break; 
		
		// only check this result if its a hit against an entity 
		if( ( QueryResult[QRIndex].movable != NULL ) && 
			( QueryResult[QRIndex].movable->getMovableType().compare("Entity") == 0 ) ) 
		{ 
			// get the entity to check 
			Ogre::Entity* PEntity = static_cast<Ogre::Entity*>(QueryResult[QRIndex].movable);   
			
			// mesh data to retrieve
			size_t VertexCount; 
			size_t IndexCount; 
			Ogre::Vector3* Vertices; 
			unsigned long* Indices;  
			
			// get the mesh information 
			Util::GetMeshInformation( PEntity->getMesh(), 
				VertexCount, 
				Vertices, 
				IndexCount, 
				Indices, 
				PEntity->getParentSceneNode()->_getDerivedPosition(),
				PEntity->getParentSceneNode()->_getDerivedOrientation(), 
				PEntity->getParentSceneNode()->_getDerivedScale() );

			// test for hitting individual triangles on the mesh 
			bool NewClosestFound = false; 
			for( int i = 0; i < static_cast<int>(IndexCount); i += 3 ) 
			{ 
				// check for a hit against this triangle 
				std::pair<bool, Ogre::Real> Hit = 
					Ogre::Math::intersects( MouseRay, 
					Vertices[Indices[i]], 
					Vertices[Indices[i+1]], 
					Vertices[Indices[i+2]], 
					true, false);  
				// if it was a hit check if its the closest 
				if( Hit.first ) 
				{ 
					if( ( ClosestDistance < 0.0f ) || 
						( Hit.second < ClosestDistance ) ) 
					{ 
						// this is the closest so far, save it off 
						ClosestDistance = Hit.second; 
						NewClosestFound = true; 
					} 
				} 
			}

			// free the verticies and indicies memory 
			delete[] Vertices;
			delete[] Indices;

			// if we found a new closest raycast for this object, update the 
			// closest_result before moving on to the next object. 
			if( NewClosestFound ) 
				ClosestResult = PEntity;
		}  
	}

	if( ClosestDistance < 0.0f ) 
	{
		// raycast failed 
		ClosestResult = NULL;
	} 
	
	if( ClosestResult )
	{
		Entity* Selection = mEntityPool.GetEntityByOgreEntity( ClosestResult );
		if( Selection )
			CAppContext::instance().SetSelection( Selection );
		else
			CAppContext::instance().ClearSelection();
	}

	event.Skip();
}

void MainFrame::OnDynamicShadowsChange( wxCommandEvent& event )
{
	if(event.IsChecked())
	{
		mOgreWindow->GetSceneManager()->setShadowTechnique(
			Ogre::SHADOWTYPE_STENCIL_MODULATIVE );
	}
	else
	{
		mOgreWindow->GetSceneManager()->setShadowTechnique(
			Ogre::SHADOWTYPE_NONE );
	}
}


void MainFrame::OnInsertEntity( wxCommandEvent& Event )
{
	wxTextEntryDialog Dialog( this, "Name the new entity:", "Create Entity" );

	if ( Dialog.ShowModal() == wxID_OK )
	{
		// FIXME: validate the name
		std::string EntityName( Dialog.GetValue().mb_str());
		Entity*     e = new Entity();
		e->SetName( EntityName );

		mEntityPool.InsertEntity( e );
	}
}

void MainFrame::OnRemoveEntity( wxCommandEvent& Event )
{
	if ( CAppContext::instance().HasSelection() )
		mEntityPool.RemoveEntity( CAppContext::instance().GetSelected() );

	CAppContext::instance().ClearSelection();
}


void MainFrame::OnAddAttribute( wxCommandEvent& Event )
{
	if ( !CAppContext::instance().HasSelection() ) return;

	// Setup the "add attribute" dialog
	AddAttributeDialog Dialog( this );
	int SelectedType = 0;
	Dialog.Sizer->Add( Dialog.CreateButtonSizer( wxOK | wxCANCEL ), 0, wxEXPAND,5 );
	Dialog.Sizer->Fit( &Dialog );

	// Bind selection events to change 'SelectedType'
	boost::function<void(wxCommandEvent&)> Func = boost::bind( &SetSelectedIndex,
		_1,	boost::ref( SelectedType ) );
	Dialog.TypeRadioBox->Bind( wxEVT_COMMAND_RADIOBOX_SELECTED,Func );

	if ( Dialog.ShowModal() == wxID_OK )
	{
		std::string AttribName( Dialog.NameCtrl->GetValue().mb_str());
		std::string AttribValue( Dialog.ValueCtrl->GetValue().mb_str());

		// FIXME: use type information, not just strings!

		if ( CAppContext::instance().GetSelected()->GetAttribute( AttribName ) )
		{
			wxMessageBox( "Attribute of that name already exists!",
				"Error while adding attribute",
				4 | wxCENTRE,
				this );
			return;
		}

		try
		{
			Entity* Selected = CAppContext::instance().GetSelected();
			switch( SelectedType )
			{
			default:
			case 0:
				// Int
				Selected->Set<int>( AttribName, 
					boost::lexical_cast<int>( AttribValue ) );
				break;
			case 1:
				// String
				Selected->Set<std::string>( AttribName, AttribValue );
				break;
			case 2:
				// Float
				Selected->Set<double>( AttribName, 
					boost::lexical_cast<double>( AttribValue ) );
				break;
			}
		}
		catch( boost::bad_lexical_cast& )
		{
			wxMessageBox(
				"Unable to convert value to the set type.",
				"Error while adding attribute",
				4 | wxCENTRE,
				this );
		}
	}
}

void MainFrame::OnDeleteAttribute( wxCommandEvent& Event )
{
	if ( !CAppContext::instance().HasSelection() ) return;

	wxPropertyGrid* Grid = mAttributeView->GetGrid();
	wxPGProperty*   Selected = Grid->GetSelection();

	if ( !Selected ) return;

	std::string Name( Selected->GetName().mb_str() );
	CAppContext::instance().GetSelected()->RemoveAttribute( Name );
}


void MainFrame::OnTreeSelectionChanged( wxTreeEvent& Event )
{
	wxTreeItemId Item = Event.GetItem();
	Entity* Selected = mSceneTree->GetEntity( Item );

	CAppContext::instance().SetSelection( Selected );
	mAttributeView->SetEntity( Selected );
}


void MainFrame::OnShowSceneStructure( wxCommandEvent &event )
{}

void MainFrame::OnDMPoints( wxCommandEvent &evt )
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_POINTS );
}

void MainFrame::OnDMWire( wxCommandEvent &evt )
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_WIREFRAME );
}

void MainFrame::OnDMSolid( wxCommandEvent &evt )
{
	if( evt.IsChecked() )
		mCamera->setPolygonMode( Ogre::PM_SOLID );
}

void MainFrame::OnTestStuff( wxCommandEvent& event )
{
	/*	
	// This code shows updating a trajectory
	std::vector<Ogre::Vector3> Points;

	Entity* ent = mEntityPool.GetEntityByName( "TestTrajectory" );
	if( !ent )
		return;

	const Entity::VariantType* Att = ent->GetAttribute( "Points" );
	if( !Att )
		return;

	const boost::any* PAny = boost::get<boost::any>( Att );
	if( PAny )
	{
		try
		{
			const std::vector<Ogre::Vector3>& OldPoints =
				boost::any_cast<std::vector<Ogre::Vector3> >(*PAny);

			Points.assign( OldPoints.begin(), OldPoints.end() );
			Points.push_back( Ogre::Vector3( 1.f, 2.f, 2.f ) );
			Points.push_back( Ogre::Vector3( 1.f, 3.f, 2.f ) );

			ent->SetAttribute( "Points", Points );
		}
		catch( boost::bad_any_cast & )
		{}
	}*/
}
