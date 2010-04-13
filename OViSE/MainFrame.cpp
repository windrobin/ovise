/***************************************************************
 * Name:      MainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#include "MainFrame.h"

#ifdef __WXGTK__
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#endif

#include "../OViSEAux/SocketMessage.h"
#include "Pointcloud.h"

#include <wx/textfile.h>
#include <wx/tokenzr.h>

enum 
{
	SERVER_ID = 100,
	SOCKET_ID
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

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBase(parent), mSocketServer( NULL ), SocketOk( false )
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("OViSE started up."), 0);
	statusBar->SetStatusText(wxT("FPS:"), 1);
#endif

	mWindowManager.SetManagedWindow( this );
	mOgreInitialized = false;

	mMainRenderWin = new wxWindow(this, WINDOW_MainRender);
	mWindowManager.AddPane(mMainRenderWin, wxCENTER, wxT("RenderWindow"));

	// Connect window events
	mMainRenderWin->Bind(wxEVT_SIZE, &MainFrame::OnRenderWindowResize, this);
	Bind(wxEVT_IDLE, &MainFrame::OnIdle, this);
	mMainRenderWin->Bind(wxEVT_LEFT_DCLICK, &MainFrame::OnViewClick, this);
	
	mLogBox = new wxListBox(this, wxID_ANY);
	mWindowManager.AddPane(mLogBox, wxBOTTOM, wxT("Log"));
	mLogBoxListener = new CustomLogListener(mLogBox);

	// Initialize PropertyGrid
	setupObjectProperties();

	// Initialize SelectionManager
	SelectionManager::getSingletonPtr()->SetPropertyGrid(this->mObjectProperties);

	mAddMeshDialog = NULL;

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
	this->mOgreObjectRL.StopListening();

	this->mMovableObjectLL.StopListening();
	this->mCameraLogListenerLL.StopListening();
	this->mEntityLogListenerLL.StopListening();
	this->mLightLogListenerLL.StopListening();
	this->mSceneManagerLL.StopListening();
	this->mSceneNodeLL.StopListening();

	this->mOgreObjectSML.StopListening();

	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(mLogBoxListener);
	delete mRoot;
	if( mSocketServer != NULL )
		delete mSocketServer;
	delete mInputHandler;
}

bool MainFrame::InitOgre()
{
	// Create logging
	Ogre::LogManager *logMgr = new Ogre::LogManager;
	Ogre::Log *log = Ogre::LogManager::getSingleton().createLog("OViSE.log", true, true, false);
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener( mLogBoxListener );

	// Create Ogre root
	mRoot = new Ogre::Root("", "");
	
	// Load resources
	Ogre::ConfigFile cf;
	cf.load("../resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i=settings->begin(); i!=settings->end(); ++i){
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
		wxYield();
	}

	// Load plugins
	try
	{
#ifdef _WIN32
#ifdef _DEBUG
		mRoot->loadPlugin("Plugin_ParticleFX_d");
		mRoot->loadPlugin("Plugin_BSPSceneManager_d");
		mRoot->loadPlugin("Plugin_OctreeSceneManager_d");
		mRoot->loadPlugin("Plugin_CgProgramManager_d");
		mRoot->loadPlugin("RenderSystem_Direct3D9_d");
#else
		mRoot->loadPlugin("RenderSystem_Direct3D9");
		mRoot->loadPlugin("Plugin_ParticleFX");
		mRoot->loadPlugin("Plugin_BSPSceneManager");
		mRoot->loadPlugin("Plugin_OctreeSceneManager");
		mRoot->loadPlugin("Plugin_CgProgramManager");
#endif
#else
		mRoot->loadPlugin("RenderSystem_GL");
		mRoot->loadPlugin("Plugin_ParticleFX");
		mRoot->loadPlugin("Plugin_BSPSceneManager");
		mRoot->loadPlugin("Plugin_OctreeSceneManager");
		//mRoot->loadPlugin("Plugin_CgProgramManager");
#endif
	}
	catch (Ogre::InternalErrorException e)
	{
		std::cerr << e.getFullDescription() << std::endl;
		exit(-1);
	}
	
	wxYield();
	// Find and set rendersystem
	Ogre::RenderSystemList *rsList = mRoot->getAvailableRenderers();
	Ogre::RenderSystemList::iterator it = rsList->begin();
	Ogre::RenderSystem *selectedRenderSystem;
	while(it != rsList->end())
	{
		selectedRenderSystem = *(it++);
		Ogre::String lMsg = "Found rendersystem: " + selectedRenderSystem->getName();
		Ogre::LogManager::getSingletonPtr()->logMessage(lMsg);
#ifdef _WIN32
		if(selectedRenderSystem->getName().find("Direct3D9") != std::string::npos)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("******* Setting Direct3D9 rendersystem. ***********");
			mRoot->setRenderSystem(selectedRenderSystem);
			break;
		}
#else
		if(selectedRenderSystem->getName().find("GL") != std::string::npos)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("******* Setting OpenGL rendersystem. ***********");
			mRoot->setRenderSystem(selectedRenderSystem);
			break;
		}
#endif
	}
	if(mRoot->getRenderSystem() == NULL)
	{
		delete mRoot;
		Ogre::LogManager::getSingletonPtr()->logMessage("No suitable rendersystem found!");
		return false;
	}

	wxYield();
	// Initialize root without creating a render window yet
	mRoot->initialise(false);

	// Create the render window with the given wxwindow handle
	Ogre::NameValuePairList params;
#ifdef __WXMSW__
	params["externalWindowHandle"] = GetOgreHandle();
#elif defined(__WXGTK__)
	params["parentWindowHandle"] = GetOgreHandle();
#endif
	int width;
	int height;
	mMainRenderWin->GetSize (&width, &height);
	mRenderWin = Ogre::Root::getSingleton ().createRenderWindow (
		Ogre::String ("OgreRenderWindow"),
		width, height, false, &params);
	mRenderWin->setActive (true);

	// Register EventListeners of "improved event handling": Render3D
	this->mOgreObjectRL.StartListening();

	// Register EventListeners of "improved event handling": Logs
	this->mMovableObjectLL.StartListening();
	this->mCameraLogListenerLL.StartListening();
	this->mEntityLogListenerLL.StartListening();
	this->mLightLogListenerLL.StartListening();
	this->mSceneManagerLL.StartListening();
	this->mSceneNodeLL.StartListening();

	// Register EventListeners of "improved event handling": SelectionManager (PropertyGrid)
	this->mOgreObjectSML.StartListening();

	// Create scene tree
	wxImageList *sceneTreeImageList = new wxImageList(16, 16, true, 5);
	this->loadSceneTreeImageList(sceneTreeImageList);
	
	this->mSceneTree = new SceneTree(this, SCENETREE, wxDefaultPosition, wxSize(300, -1), wxTR_EDIT_LABELS | wxTR_MULTIPLE | wxTR_DEFAULT_STYLE);
	// Register EventListeners of "improved event handling": SceneTree
	this->mOgreObjectSTL.SetSceneTree(this->mSceneTree);
	this->mOgreObjectSTL.StartListening();
	this->mWindowManager.AddPane(mSceneTree, wxRIGHT, wxT("Scene structure"));
	this->mSceneTree->SetImageList(sceneTreeImageList);

	// First access to OgreMediator <------------------------
	OgreMediator* Mediator = OgreMediator::GetSingletonPtr();
	
	// Get active SceneManager...
	this->mSceneMgr = Mediator->iSceneManager.GetPtr(Mediator->iSceneManager.GetActiveSceneManager());

	// Create and store RootSceneNode in qualified context...
	//Mediator->iSceneNode.Create(ToWxString(this->mSceneMgr->getRootSceneNode()->getName()));

	// Create camera setup
	QualifiedName qCamFokusSceneNode = Mediator->iSceneNode.Create(ToWxString("mainCamFocusNode"));
	if ( !qCamFokusSceneNode.IsValid() ) return false;
	Ogre::SceneNode *camFocusNode = Mediator->iSceneNode.GetPtr(qCamFokusSceneNode);
	camFocusNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
	QualifiedName qCamSceneNode = Mediator->iSceneNode.Create(ToWxString("CamNode"), camFocusNode);
	if ( !qCamSceneNode.IsValid() ) return false;
	Ogre::SceneNode *camNode = Mediator->iSceneNode.GetPtr(qCamSceneNode);
	camNode->setPosition(0, 5, 0);
	Ogre::Quaternion q(Ogre::Degree(180), Ogre::Vector3::UNIT_Z);
	Ogre::Quaternion p(Ogre::Degree(-90), Ogre::Vector3::UNIT_X);
	camNode->setOrientation(p*q);
	QualifiedName qCamera = Mediator->iCamera.Create(ToWxString("MainCam"), camNode);
	if ( !qCamera.IsValid() ) return false;
	mCam = Mediator->iCamera.GetPtr(qCamera);
	mCam->setNearClipDistance(0.01);
	mCam->setFarClipDistance(1000);
    mCam->setAutoAspectRatio(true);
	mCam->setQueryFlags(0x01);

	camFocusNode->yaw(Ogre::Degree(-45), Ogre::Node::TS_WORLD);
	camFocusNode->pitch(Ogre::Degree(45), Ogre::Node::TS_LOCAL);

	wxYield();
	// Create viewport for camera
    Ogre::Viewport *mVp = mRenderWin->addViewport(mCam);
	mVp->setBackgroundColour(Ogre::ColourValue(0.9, 0.9, 0.9));
	
	// Initialize resources
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// DBG: Testscene
	QualifiedName qGridPlane = Mediator->iEntity.Create(ToWxString("GridPlane"), ToWxString("GridPlane.mesh"));
	Mediator->iEntity.GetPtr(qGridPlane)->setQueryFlags(0x01);
	Mediator->iEntity.Create(ToWxString("CoS"), ToWxString("CoS.mesh"));
	
	QualifiedName qSunLight = Mediator->iLight.Create(ToWxString("Sun"));
	Ogre::Light* SunLight = Mediator->iLight.GetPtr(qSunLight);
	SunLight->setCastShadows(true);
	SunLight->setDirection(-1,-1,-1);
	SunLight->setPosition(100, 100, 100);

	// When selection in OViSESceneTree changed, call MainFrame::OnSelectionChanged(...) !
	mSceneTree->Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &MainFrame::OnTreeSelectionChanged, this);
	
	
	//MainFrame::OnViewClick handles the other direction

	mWindowManager.Update();

	// Parking call here for a short time whil REFACTORING. H.R.
	// Initialize DotSceneManager
	mDotSceneMgr = new OViSEDotSceneManager(OViSEDotSceneManager::CreateDefaultConfiguration());

	// Create input handler
	mInputHandler = new InputHandler(mCam, camFocusNode, mMainRenderWin);

	mRoot->addFrameListener( &mFrameListener );

	mOgreInitialized = true;
	return true;
}

/// @todo Set this up so it uses values from config file
void MainFrame::InitSocketInterface()
{
	// Create the address - defaults to localhost:0 initially
#if wxUSE_IPV6
	wxIPV6address Address;
#else
	wxIPV4address Address;
#endif
	Address.Service(3000);

	mSocketServer = new wxSocketServer( Address );

	// We use Ok() here to see if the server is really listening
	if (! mSocketServer->Ok())
	{
		Logging::GetSingletonPtr()->WriteToOgreLog( "Could not listen at the specified port !", Logging::Critical );
		return;
	}
	Bind( wxEVT_SOCKET, &MainFrame::OnSocketEvent, this, SOCKET_ID );
	Bind( wxEVT_SOCKET, &MainFrame::OnServerEvent, this, SERVER_ID );
	Logging::GetSingletonPtr()->WriteToOgreLog( "Server listening.", Logging::Normal );
	SocketOk = true;
	mSocketServer->SetEventHandler( *this, SERVER_ID );
	mSocketServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
	mSocketServer->Notify(true);
	mNumClients = 0;
}

void MainFrame::OnServerEvent( wxSocketEvent& evt )
{
	wxSocketBase *Socket = NULL;
	Logging *Log = Logging::GetSingletonPtr();

	Socket = mSocketServer->Accept( false );

	if( Socket )
	{
		Log->WriteToOgreLog( wxT( "New client connection accepted." ), Logging::Normal );
	}
	else
	{
		Log->WriteToOgreLog( wxT( "Couldn't accept a new connection." ), Logging::Critical );
		return;
	}

	Socket->SetEventHandler( *this, SOCKET_ID );
	Socket->SetNotify( wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG );
	Socket->Notify( true );

	mNumClients++;
}

void MainFrame::OnSocketEvent( wxSocketEvent& evt )
{
	Logging *Log = Logging::GetSingletonPtr();
	wxSocketBase *Socket = evt.GetSocket();

	switch( evt.GetSocketEvent() )
	{
	case wxSOCKET_INPUT:
		{
			Socket->SetNotify( wxSOCKET_LOST_FLAG );
			// do stuff
			Socket->SetFlags( wxSOCKET_WAITALL );
			unsigned char len;
			Socket->Read( &len, 1 );
			wxCharBuffer Buffer( len );
			Socket->Read( Buffer.data(), len );
			wxString ReceivedCmd( Buffer );
			SocketMessage Msg;
			unsigned char ReturnValue;
			if( Msg.Parse( ReceivedCmd ) )
			{
				Log->WriteToOgreLog( wxT( "Received command: " ) + Msg.GetCommand(), Logging::Normal );
				for( std::vector<wxString>::const_iterator It = Msg.GetArguments().begin(); It != Msg.GetArguments().end(); It++ )
					Log->WriteToOgreLog( wxT( "Argument: " ) + *It, Logging::Normal );
				ReturnValue = '0'; //OK
			}
			else
			{
				Log->WriteToOgreLog( wxT( "Couldn't parse command!" ), Logging::Critical );
				ReturnValue = '1'; // ERROR
			}
			Socket->Write( &ReturnValue, 1 );

			Socket->SetNotify( wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG );
		} break;
	case wxSOCKET_LOST:
		{
			mNumClients--;
			Log->WriteToOgreLog( wxT( "Deleting socket." ), Logging::Normal );

			Socket->Destroy();
		} break;
	default: break;
	}
}

Ogre::String MainFrame::GetOgreHandle()
{
	Ogre::String handle;

#ifdef __WXMSW__
	// Handle for Windows systems
	handle = Ogre::StringConverter::toString((size_t)((HWND)mMainRenderWin->GetHandle()));
#elif defined(__WXGTK__)
	GtkWidget* widget = mMainRenderWin->GetHandle();
	gtk_widget_realize( widget );	// Mandatory. Otherwise, a segfault happens.
	if(!GTK_WIDGET_REALIZED(widget))
	  printf("Error, GtkWidget not realized!\n");
	
	std::stringstream handleStream;
	Display* display = GDK_WINDOW_XDISPLAY( widget->window );
	Window wid = GDK_WINDOW_XWINDOW( widget->window );
	
	// Get the right display (DisplayString() returns ":display.screen")
	std::string displayStr = DisplayString( display );
	displayStr = displayStr.substr( 1, ( displayStr.find( ".", 0 ) - 1 ) );
	
	// Put all together
	handleStream << displayStr << ':' << DefaultScreen( display ) << ':' << wid;
	handle = handleStream.str();
#else
	// Any other unsupported system
	#error Not supported on this platform.
#endif
	return handle;
}

void MainFrame::setupObjectProperties()
{
	mObjectProperties = new wxPropertyGrid(this, PGID, wxDefaultPosition, wxSize(300, -1));
	mWindowManager.AddPane(mObjectProperties, wxRIGHT, wxT("Properties"));
	this->Connect(PGID, wxEVT_PG_CHANGED, wxPropertyGridEventHandler(MainFrame::OnPropertyChange));
	mObjectProperties->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);
	/*
	mObjectProperties->Append(new wxPropertyCategory(wxT("Node Properties")));
	mObjectProperties->Append(new wxStringProperty(wxT("Name"), wxT("NodeName")));
	mObjectProperties->SetPropertyValidator(wxT("NodeName"), wxTextValidator(wxFILTER_ALPHANUMERIC));

	wxPGProperty* tID = mObjectProperties->Append(new wxStringProperty(wxT("Translation"), wxPG_LABEL, wxT("<composed>")));
	mObjectProperties->AppendIn(tID, new wxFloatProperty(wxT("x"), wxT("tx")));
	mObjectProperties->SetPropertyValidator(wxT("Translation.tx"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(tID, new wxFloatProperty(wxT("y"), wxT("ty")));
	mObjectProperties->SetPropertyValidator(wxT("Translation.ty"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(tID, new wxFloatProperty(wxT("z"), wxT("tz")));
	mObjectProperties->SetPropertyValidator(wxT("Translation.tz"), wxTextValidator(wxFILTER_NUMERIC));

	wxPGProperty* rID = mObjectProperties->Append(new wxStringProperty(wxT("Rotation"), wxPG_LABEL, wxT("<composed>")));
	mObjectProperties->AppendIn(rID, new wxFloatProperty(wxT("x"), wxT("rx")));
	mObjectProperties->SetPropertyValidator(wxT("Rotation.rx"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(rID, new wxFloatProperty(wxT("y"), wxT("ry")));
	mObjectProperties->SetPropertyValidator(wxT("Rotation.ry"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(rID, new wxFloatProperty(wxT("z"), wxT("rz")));
	mObjectProperties->SetPropertyValidator(wxT("Rotation.rz"), wxTextValidator(wxFILTER_NUMERIC));

	wxPGProperty* sID = mObjectProperties->Append(new wxStringProperty(wxT("Scale"), wxPG_LABEL, wxT("<composed>")));
	mObjectProperties->AppendIn(sID, new wxFloatProperty(wxT("x"), wxT("sx")));
	mObjectProperties->SetPropertyValidator(wxT("Scale.sx"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(sID, new wxFloatProperty(wxT("y"), wxT("sy")));
	mObjectProperties->SetPropertyValidator(wxT("Scale.sy"), wxTextValidator(wxFILTER_NUMERIC));
	mObjectProperties->AppendIn(sID, new wxFloatProperty(wxT("z"), wxT("sz")));
	mObjectProperties->SetPropertyValidator(wxT("Scale.sz"), wxTextValidator(wxFILTER_NUMERIC));

	mObjectProperties->Append(new wxPropertyCategory(wxT("Mesh Properties")));
	mObjectProperties->Append(new wxStringProperty(wxT("Name"), wxT("MeshName")));
	mObjectProperties->SetPropertyValidator(wxT("MeshName"), wxTextValidator(wxFILTER_ALPHANUMERIC));
	mObjectProperties->Append(new wxStringProperty(wxT("Material"), wxT("MeshMaterial")));
	mObjectProperties->SetPropertyValidator(wxT("MeshMaterial"), wxTextValidator(wxFILTER_ALPHANUMERIC));

	*/
	mObjectProperties->SetSplitterLeft(true);
}

void MainFrame::loadSceneTreeImageList(wxImageList *list)
{
	// index 0 = ROOT
	wxBitmap rootIcon(wxT("../../Media/data/home_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(rootIcon);
	// index 1 = SCENE_NODE
	wxBitmap nodeIcon(wxT("../../Media/data/folder_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(nodeIcon);
	// index 2 = MESH
	wxBitmap meshIcon(wxT("../../Media/data/box_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(meshIcon);
	// index 3 = CAMERA
	wxBitmap cameraIcon(wxT("../../Media/data/camera_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(cameraIcon);
	// index 4 = LIGHT
	wxBitmap lightIcon(wxT("../../Media/data/lightbulb_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(lightIcon);
}

void MainFrame::OnQuit(wxCommandEvent &event)
{
	Close();
}

void MainFrame::OnIdle(wxIdleEvent& evt)
{
	UpdateRenderWindow();
	evt.RequestMore();
}

void MainFrame::OnRenderWindowResize(wxSizeEvent& evt)
{
	if(mOgreInitialized)
	{
		// Setting new size;
		int width = evt.GetSize().GetWidth ();
		int height = evt.GetSize().GetHeight ();
		mRenderWin->resize(width, height);
		// Letting Ogre know the window has been resized;
		mRenderWin->windowMovedOrResized ();

		UpdateRenderWindow();
	}
}

void MainFrame::UpdateRenderWindow()
{
	if(mOgreInitialized)
	{
		mRoot->_fireFrameStarted();
		mRenderWin->update(true);
		if( mAddMeshDialog )
			mAddMeshDialog->mRenderWin->update(true);
		mRoot->_fireFrameEnded();

		float FPS = mRenderWin->getLastFPS();
		wxString fpsStr;
		fpsStr.Printf(wxT("FPS: %lf"), FPS);
		statusBar->SetStatusText(fpsStr, 1);
	}
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

	info.AddDeveloper(wxT("Programming - Alexander Kasper <alexander.kasper@kit.edu>\n"));
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
		mRenderWin->writeContentsToFile(Ogre::String(fullPath.ToAscii()));
	}
}

void MainFrame::OnSceneAddMesh(wxCommandEvent &event)
{
	if(mAddMeshDialog == NULL)
	{
		mAddMeshDialog = new OViSEAddMeshDialog(this, wxID_HIGHEST + 1);
		mAddMeshDialog->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnAddMeshDialogClose ), NULL, this);
	}
	mAddMeshDialog->Show();
	wxSafeYield();
	mAddMeshDialog->InitOgre();
}

void MainFrame::OnAddMeshDialogClose(wxCloseEvent& event)
{
	mAddMeshDialog->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnAddMeshDialogClose ), NULL, this);
	event.Skip();
	mAddMeshDialog = NULL;
}

void MainFrame::OnViewClick(wxMouseEvent& event)
{
	wxPoint p = event.GetPosition();
	wxPoint t = mMainRenderWin->GetScreenPosition();
	int width = mRenderWin->getWidth();
	int height = mRenderWin->getHeight();
	wxPoint s = p;
	float sx = (float)s.x / (float)width;
	float sy = (float)s.y / (float)height;
	float d = -1;

	Ogre::Ray tRay = OgreMediator::GetSingletonPtr()->iSceneManager.Assist_GetRayForRaySceneQuery(sx, sy, mCam);
	QualifiedNameCollection QNames = OgreMediator::GetSingletonPtr()->iSceneManager.QueryObjectsByRay(tRay, OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager());
	
	// Handle selection
	if(QNames.IsEmpty())
	{
		// Nothing selected
		//this->mSceneTree->UnselectAll();
		this->UnselectOgreObjects(SelectionManager::getSingletonPtr()->Selection);
	}
	else
	{
		// CASE:				ACTION:
		// 1:	-			->	Unselect all, Select one or nothing
		// 2:	CTRL		->	Unselect one or nothing, Add one or nothing to Selection(front)
		// 3:	SHIFT		->	Unselect all, Add complete Query
		// 4:	CTRL, SHIFT ->	Unselect all in complete Query, Add complete Query < IRREGULAR: only unselect, if all from Query are selected

		if (event.ControlDown())
		{
			if (event.ShiftDown())
			{
				// CASE 4: Add only objects to selection, which are not in till now.
				// Get QNames, whose are not selecte now. ( QNames without any qName, which is in Selection )
				QualifiedNameCollection UnselectedQNames = QualifiedNameCollection::CollectionDifference(QNames, SelectionManager::getSingletonPtr()->Selection);
				this->SelectOgreObjects(UnselectedQNames);
			}
			else
			{
				// CASE 2: Unselect one or nothing, Add one or nothing to Selection(front)
				// Add to previous selection
				if (SelectionManager::getSingletonPtr()->Selection.Contains(QNames[0])) this->UnselectOgreObject(QNames[0]);
				else this->SelectOgreObject(QNames[0]);
			}
		}
		else
		{
			if (event.ShiftDown())
			{
				// CASE 3: Unselect all, select complete Query
				this->UnselectOgreObjects(SelectionManager::getSingletonPtr()->Selection);
				this->SelectOgreObjects(QNames);
			}
			else
			{
				// CASE 1: Unselect all, select one or nothing
				this->UnselectOgreObjects(SelectionManager::getSingletonPtr()->Selection);
				this->SelectOgreObject(QNames[0]);
			}
		}
	}
}
void MainFrame::SelectOgreObject(QualifiedName qName)
{
	bool valid = qName.IsValid();
	EventDispatcher::Publish(EVT_OGRE_OBJECT_SELECTED, qName);
}
void MainFrame::SelectOgreObjects(QualifiedNameCollection QSelection)
{
	if (!QSelection.IsEmpty())
	{
		for (unsigned long IT = 0; IT < QSelection.Count(); IT++)
		{
			this->SelectOgreObject(QSelection[IT]);
		}
	}
}
void MainFrame::UnselectOgreObject(QualifiedName qName) { EventDispatcher::Publish(EVT_OGRE_OBJECT_UNSELECTED, qName); }
void MainFrame::UnselectOgreObjects(QualifiedNameCollection QSelection)
{
	if (!QSelection.IsEmpty())
	{
		for (unsigned long IT = 0; IT < QSelection.Count(); IT++)
		{
			this->UnselectOgreObject(QSelection[IT]);
		}
	}
}

void MainFrame::OnDynamicShadowsChange(wxCommandEvent& event)
{
	if(event.IsChecked())
	{
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	}
	else
	{
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	}
}

void MainFrame::OnPropertyChange(wxPropertyGridEvent& event)
{
	wxPGProperty *prop = event.GetProperty();
	SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop);
	/*
    // It may be NULL
    if ( !prop )
        return;

    // Get name of changed property
    const wxString& name = prop->GetName();
	std::string objname = (const char*)mObjectProperties->GetPropertyValueAsString(wxT("MeshName")).ToAscii();

	OViSESelectionMap selObjs = OViSESceneHandling::getSingletonPtr()->getSelectedObjects();
	if(selObjs.empty())
		return;
	Ogre::SceneNode *snode = selObjs[objname]->getParentSceneNode();
	if(!snode)
		return;
	Ogre::Vector3 pos = snode->getPosition();
	Ogre::Vector3 scale = snode->getScale();
	Ogre::Quaternion tmprot = snode->getOrientation();

	wxVariant tmp = prop->GetValue();
	wxString tmpstr = tmp.GetString();

	double vals[3];

	wxStringTokenizer checker(tmpstr, wxT(";"));

	if(name == wxString(wxT("Translation")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		pos = Ogre::Vector3(vals[0], vals[1], vals[2]);
	}
	if(name == wxString(wxT("Translation.tx")))
	{
		float tx = tmp.GetDouble();
		pos.x = tx;
	}
	if(name == wxString(wxT("Translation.ty")))
	{
		float ty = tmp.GetDouble();
		pos.y = ty;
	}
	if(name == wxString(wxT("Translation.tz")))
	{
		float tz = tmp.GetDouble();
		pos.z = tz;
	}

	snode->setPosition(pos);

	if(name == wxString(wxT("Rotation")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		Ogre::Radian p = Ogre::Radian(Ogre::Degree(vals[0])) - tmprot.getPitch();
		Ogre::Radian r = Ogre::Radian(Ogre::Degree(vals[1])) - tmprot.getRoll();
		Ogre::Radian y = Ogre::Radian(Ogre::Degree(vals[2])) - tmprot.getYaw();
		snode->pitch(p);
		snode->roll(r);
		snode->yaw(y);
	}
	if(name == wxString(wxT("Rotation.rx")))
	{
		float rx = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(rx)) - tmprot.getPitch());
	}
	if(name == wxString(wxT("Rotation.ry")))
	{
		float ry = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(ry)) - tmprot.getRoll());
	}
	if(name == wxString(wxT("Rotation.rz")))
	{
		float rz = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(rz)) - tmprot.getYaw());
	}

	if(name == wxString(wxT("Scale")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		scale = Ogre::Vector3(vals[0], vals[1], vals[2]);
	}
	if(name == wxString(wxT("Scale.sx")))
	{
		float sx = tmp.GetDouble();
		scale.x = sx;
	}
	if(name == wxString(wxT("Scale.sy")))
	{
		float sy = tmp.GetDouble();
		scale.y = sy;
	}
	if(name == wxString(wxT("Scale.sz")))
	{
		float sz = tmp.GetDouble();
		scale.z = sz;
	}

	snode->setScale(scale);

	*/
	// call update for scene structure
	//mSceneHdlr->showSceneGraphStructure(true);
}

void MainFrame::setObjectProperties(Ogre::MovableObject *object)
{
	Ogre::SceneNode *pnode = object->getParentSceneNode();
	mObjectProperties->SetPropertyValue(wxT("NodeName"), wxString(pnode->getName().c_str(), wxConvUTF8));

	mObjectProperties->SetPropertyValue(wxT("Translation.tx"), (float)pnode->getPosition().x);
	mObjectProperties->SetPropertyValue(wxT("Translation.ty"), (float)pnode->getPosition().y);
	mObjectProperties->SetPropertyValue(wxT("Translation.tz"), (float)pnode->getPosition().z);

	mObjectProperties->SetPropertyValue(wxT("Rotation.rx"), (float)pnode->getOrientation().getPitch().valueDegrees());
	mObjectProperties->SetPropertyValue(wxT("Rotation.ry"), (float)pnode->getOrientation().getRoll().valueDegrees());
	mObjectProperties->SetPropertyValue(wxT("Rotation.rz"), (float)pnode->getOrientation().getYaw().valueDegrees());

	mObjectProperties->SetPropertyValue(wxT("Scale.sx"), (float)pnode->getScale().x);
	mObjectProperties->SetPropertyValue(wxT("Scale.sy"), (float)pnode->getScale().y);
	mObjectProperties->SetPropertyValue(wxT("Scale.sz"), (float)pnode->getScale().z);

	mObjectProperties->SetPropertyValue(wxT("MeshName"), wxString(object->getName().c_str(), wxConvUTF8));

	mObjectProperties->SetPropertyValue(wxT("MeshMaterial"), wxT("TODO"));
}

void MainFrame::OnMenuDeleteMeshes(wxCommandEvent &event)
{
	deleteMeshes();
}

void MainFrame::clearObjectProperties()
{
	mObjectProperties->Clear();
}

void MainFrame::deleteMeshes()
{
/*	SelectionMap so = SceneHandling::getSingletonPtr()->getSelectedObjects();
	if(so.empty())
	{
		wxMessageDialog dlg(this, wxT("No meshes selected"), wxT("Error"), wxOK | wxCENTRE | wxICON_ERROR);
		dlg.ShowModal();
		return;
	}

	wxMessageDialog confirmationDialog(this, wxT("Delete selected meshes?"), wxT("Confirmation required"), wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION);
	if(confirmationDialog.ShowModal() == wxID_YES)
	{
		for(SelectionMap::iterator it=so.begin(); it != so.end(); it++)
		{
			SceneHandling::getSingletonPtr()->deleteMesh(it->first);
		}
	}*/
}


void MainFrame::OnTreeSelectionChanged( wxTreeEvent& event )
{
	/*wxTreeItemId Item = event.GetItem();

	wxString Msg = ToWxString("SELECTED ITEMS:");

	if (!Item.IsOk()) this->RemoveAllSelectedObjects();
	else
	{
		wxString TreeItemLabel = this->mSceneTree->GetItemText(Item);
		QualifiedName qName = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(TreeItemLabel);
		if (qName.IsValid())
		{
			if (this->mSceneTree->IsSelected(Item)) this->AddSelectedObject(qName);
			else this->RemoveSelectedObject(qName);
		}
	}
	//Logging::GetSingletonPtr()->WriteToOgreLog(Msg, Logging::Normal);

	QualifiedName qName = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetActiveSceneManager();
	//OgreEventDispatcher::GetSingletonPtr()->SendOgreChanged(qName);
	//OgreEventDispatcher::GetSingletonPtr()->SendSceneNodeChanged(qName);*/
	event.Skip();
}

void MainFrame::AddSelectedObject(QualifiedName qSelectedObject)
{
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qSelectedObject);
	if (MO != 0)
	{
		/*if (!SelectionManager::getSingletonPtr()->Selection.Contains(qSelectedObject))
			SelectionManager::getSingletonPtr()->Selection.Add(qSelectedObject);*/
		MO->getParentSceneNode()->showBoundingBox(true);
		//SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection(this->mObjectProperties);
	}
}

void MainFrame::RemoveSelectedObject(QualifiedName qSelectedObject)
{
	Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qSelectedObject);
	if (MO != 0)
	{
		//SelectionManager::getSingletonPtr()->Selection.Remove(qSelectedObject);
		MO->getParentSceneNode()->showBoundingBox(false);
		//SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection(this->mObjectProperties);
	}
}

void MainFrame::RemoveAllSelectedObjects()
{
	// Remove all BoundingBoxes
	if (SelectionManager::getSingletonPtr()->Selection.Count() != 0)
	{
		for (unsigned long IT = 0; IT < (unsigned long)SelectionManager::getSingletonPtr()->Selection.Count(); IT++)
		{
			QualifiedName qMO = SelectionManager::getSingletonPtr()->Selection[IT];
			Ogre::MovableObject* pMO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qMO);
			if (pMO != 0) pMO->getParentSceneNode()->showBoundingBox(false);
		}
	}

	// Clear selection
	//SelectionManager::getSingletonPtr()->Selection.Clear();

	// Clear propertygrid
	this->mObjectProperties->Clear();
}
void MainFrame::OnOpenPrototypeManagement( wxCommandEvent& event )
{
	PrototypeManagementDialog *PrototypeManagementDlg = new PrototypeManagementDialog(this, this->mDotSceneMgr);
	//PrototypeManagementDlg->SetAvailablePrototypes(this->mSceneHdlr->GetAvailablePrototypesOfDotSceneManager());
	PrototypeManagementDlg->ShowModal();
	//this->mSceneHdlr->AttachNewScene(AttachSceneDlg->GetResultingUniqueNameOfPrototype());
	delete PrototypeManagementDlg;
}

void MainFrame::OnLoadPointCloud(wxCommandEvent& event)
{
	wxFileDialog pcFileDialog(this, wxT("Select pointcloud file"), wxEmptyString, wxEmptyString, wxT("*.txt"));
	if(pcFileDialog.ShowModal() == wxID_OK)
	{
		wxString pcName = pcFileDialog.GetFilename();
		pcName.Truncate(pcName.Length() - 4);
		wxString pcEntName = pcName + wxT("Entity");
		wxTextFile PCFile;
		PCFile.Open(pcFileDialog.GetPath());
		double curr;
		float* pointlist = NULL;
		float* colourlist = NULL;
		bool HasColours = false;
		wxString line;

		std::vector<float> pointvector;
		std::vector<float> colourvector;
		int numPoints = 0;
		for(line = PCFile.GetFirstLine(); !PCFile.Eof(); line = PCFile.GetNextLine())
		{
			if( !line.StartsWith(wxT("#")) )
			{
				if( line.Matches(wxT("*,*")) )
				{
					HasColours = true;
					wxString points = line.BeforeFirst(',');
					wxString colours = line.AfterFirst(',');

					wxStringTokenizer p(points, wxT(" "));
					if(int(p.CountTokens()) != 3)
						continue;
					while( p.HasMoreTokens() )
					{
						p.GetNextToken().ToDouble(&curr);
						pointvector.push_back(float(curr));
					}
					wxStringTokenizer c(colours, wxT(" "));
					if(int(c.CountTokens()) != 3)
						continue;
					while( c.HasMoreTokens() )
					{
						c.GetNextToken().ToDouble(&curr);
						colourvector.push_back(float(curr));
					}
				}
				else
				{
					wxStringTokenizer p(line, wxT(" "));
					if(int(p.CountTokens()) != 3)
						continue;
					while (p.HasMoreTokens() )
					{
						p.GetNextToken().ToDouble(&curr);
						pointvector.push_back(float(curr));
					}
				}
				numPoints++;
			}
		}
		
		pointlist = new float[numPoints*3];
		if(HasColours)
			colourlist = new float[numPoints*3];
		for(int i = 0; i<numPoints*3; i++)
		{
			pointlist[i] = pointvector.at(i);
			if(HasColours)
			{
				float c = colourvector.at(i);
				if(c > 1.0f)
					c = c/255;
				colourlist[i] = c;
			}
		}


		Pointcloud* pc = new Pointcloud(std::string(pcName.mb_str()), "General", numPoints, pointlist, colourlist);
		/*if( pointlist != NULL )
			delete pointlist;
		if( colourlist != NULL )
			delete colourlist;*/
		
		OgreMediator* Med = OgreMediator::GetSingletonPtr();
		QualifiedName qPCNode = Med->iSceneNode.Create(pcName + wxT("Node"));
		QualifiedName qPC = Med->iEntity.Create(pcEntName, pcName, qPCNode);
		Ogre::Entity *pcEnt = Med->iEntity.GetPtr(qPC);
		pcEnt->setMaterialName("Pointcloud");

		//Med->SendOgreChanged();

		//delete pc;
	}
}

void MainFrame::OnShowSceneStructure(wxCommandEvent &event)
{
	//mSceneHdlr->showSceneGraphStructure();
	OgreMediator* Med = OgreMediator::GetSingletonPtr();
	Med->GetObjectAccess()->ShowSceneGraphStructure(Med->iSceneManager.GetActiveSceneManager());
}

void MainFrame::OnDMPoints(wxCommandEvent &evt)
{
	ObjectManager* Mgr = OgreMediator::GetSingletonPtr()->GetObjectAccess();
	Mgr->GetSceneManager(Mgr->GetActiveSceneManager())->getCurrentViewport()->getCamera()->setPolygonMode( Ogre::PM_POINTS );
}

void MainFrame::OnDMWire(wxCommandEvent &evt)
{
	ObjectManager* Mgr = OgreMediator::GetSingletonPtr()->GetObjectAccess();
	Mgr->GetSceneManager(Mgr->GetActiveSceneManager())->getCurrentViewport()->getCamera()->setPolygonMode( Ogre::PM_WIREFRAME );
}

void MainFrame::OnDMSolid(wxCommandEvent &evt)
{
	ObjectManager* Mgr = OgreMediator::GetSingletonPtr()->GetObjectAccess();
	Mgr->GetSceneManager(Mgr->GetActiveSceneManager())->getCurrentViewport()->getCamera()->setPolygonMode( Ogre::PM_SOLID );
}

void MainFrame::OnTestStuff( wxCommandEvent& event )
{
	OgreMediator* Med = OgreMediator::GetSingletonPtr();
	QualifiedName qNode = Med->iSceneNode.Create(wxT("MyNode"));
	Med->iEntity.Create(wxT("Barrel"), wxT("Barrel.mesh"), qNode);
	//Med->SendOgreChanged();
}
