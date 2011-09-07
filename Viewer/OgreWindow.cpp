
#ifdef __WXGTK__
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#elif __WXMSW__
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wx/msw/winundef.h>
#endif

#include "OgreWindow.h"
#include "MainFrame.h"
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <wx/dcclient.h>
#include <boost/lexical_cast.hpp>



namespace
{
	Ogre::String GetOgreHandle( wxWindow* Wnd )
	{
		Ogre::String handle;

#ifdef __WXMSW__
		// Handle for Windows systems
		handle =
				Ogre::StringConverter::toString((size_t)((HWND)Wnd->
												 GetHWND()));
#elif defined( __WXGTK__ )
		GtkWidget* widget = Wnd->GetHandle();
		gtk_widget_realize( widget ); // Mandatory. Otherwise, a segfault happens.
		if(!GTK_WIDGET_REALIZED( widget ))
			printf( "Error, GtkWidget not realized!\n" );

		std::stringstream handleStream;
		Display*          display = GDK_WINDOW_XDISPLAY( widget->window );
		Window            wid = GDK_WINDOW_XWINDOW( widget->window );

		// Get the right display (DisplayString() returns ":display.screen")
		std::string displayStr = DisplayString( display );
		displayStr =
				displayStr.substr( 1, ( displayStr.find( ".", 0 ) - 1 ) );

		// Put all together
		handleStream << displayStr << ':' <<
		DefaultScreen( display ) << ':' << wid;
		handle = handleStream.str();
#else
		// Any other unsupported system
	#error Not supported on this platform.
#endif
		return handle;
	}

	void LoadPlugins( Ogre::Root* Root )
	{
		// Load plugins
		try
		{
#ifdef _WIN32
#ifdef _DEBUG
			Root->loadPlugin( "Plugin_ParticleFX_d" );
			//Root->loadPlugin( "Plugin_OctreeSceneManager_d" );
			Root->loadPlugin( "Plugin_CgProgramManager_d" );
			Root->loadPlugin( "RenderSystem_Direct3D9_d" );
#else
			Root->loadPlugin( "RenderSystem_Direct3D9" );
			Root->loadPlugin( "Plugin_ParticleFX" );
			//Root->loadPlugin( "Plugin_OctreeSceneManager" );
			Root->loadPlugin( "Plugin_CgProgramManager" );
#endif
#else
			Root->loadPlugin( "RenderSystem_GL" );
			Root->loadPlugin( "Plugin_ParticleFX" );
			//Root->loadPlugin( "Plugin_OctreeSceneManager" );
			Root->loadPlugin("Plugin_CgProgramManager");
#endif
		}
		catch (Ogre::InternalErrorException e)
		{
			// FIXME: is this handled correctly? no error box or something?
			std::cerr << e.getFullDescription() << std::endl;
			throw;
		}
	}


	bool SelectRendersystem( Ogre::Root* Root )
	{
		// Find and set rendersystem
#if OGRE_VERSION_MAJOR >= 1 && OGRE_VERSION_MINOR >= 7
		const Ogre::RenderSystemList *rsList =
				&Root->getAvailableRenderers();
#else
		const Ogre::RenderSystemList *rsList =
				Root->getAvailableRenderers();
#endif

		Ogre::RenderSystemList::const_iterator it = rsList->begin();
		Ogre::RenderSystem *                   selectedRenderSystem;
		while(it != rsList->end())
		{
			selectedRenderSystem = *( it++ );
			Ogre::String lMsg = "Found rendersystem: " +
								selectedRenderSystem->getName();
			Ogre::LogManager::getSingletonPtr()->logMessage( lMsg );
#ifdef _WIN32
			if(selectedRenderSystem->getName().find( "Direct3D9" )
			   != std::string::npos)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage(
					"******* Setting Direct3D9 rendersystem. ***********" );
				Root->setRenderSystem( selectedRenderSystem );
				break;
			}
#else
			if(selectedRenderSystem->getName().find( "GL" ) !=
			   std::string::npos)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage(
					"******* Setting OpenGL rendersystem. ***********" );
				Root->setRenderSystem( selectedRenderSystem );
				break;
			}
#endif
		}
		if(Root->getRenderSystem() == NULL)
		{
			// FIXME: switch between exceptions and return values for error messages?
			Ogre::LogManager::getSingletonPtr()->logMessage(
				"No suitable rendersystem found!" );
			return false;
		}

		// wxYield();
		return true;
	}

	Ogre::NameValuePairList GetRenderWindowParams( wxWindow* Wnd )
	{
		// Create the render window with the given wxwindow handle
		Ogre::NameValuePairList params;
#ifdef __WXMSW__
		params["externalWindowHandle"] = GetOgreHandle( Wnd );
#elif defined( __WXGTK__ )
		params["parentWindowHandle"] = GetOgreHandle( Wnd );
#endif

		wxConfig OviseConfig;
		long     FSAA = 0;

		if ( OviseConfig.HasEntry( "FSAA" ) )
			FSAA = OviseConfig.ReadLong( "FSAA", 0 );

		// TODO: Add more settings (FSAA etc) here
		params["vsync"] = "true";
		params["FSAA"] = boost::lexical_cast<std::string>( FSAA );

		return params;
	}
}
BEGIN_EVENT_TABLE( OgreWindow, wxWindow )
EVT_SIZE(           OgreWindow::OnResize )
// EVT_WINDOW_CREATE(  OgreWindow::OnCreate)
EVT_PAINT(          OgreWindow::OnPaint )
END_EVENT_TABLE()


OgreWindow::OgreWindow( const wxString& MediaPath,
						wxWindow*       Parent,
						wxWindowID      id,
						const wxPoint&  pos,
						const wxSize&   size,
						long            style,
						const wxString& name )
	: wxWindow( Parent,id,pos,size,style,
				name ), mMediaDir( MediaPath ), mRenderWindow( 0 ),
	mSceneMgr( 0 ), mContextCreated( false )
{
	/*this->Bind(wxEVT_CREATE, &OgreWindow::OnCreate, this);
	   this->Bind(wxEVT_SIZE, &OgreWindow::OnResize, this);
	   this->Bind(wxEVT_PAINT, &OgreWindow::OnPaint, this);*/
}

OgreWindow::~OgreWindow()
{}

void OgreWindow::LoadResources()
{
	Ogre::String     MediaDirStr( mMediaDir.data() );
	Ogre::ConfigFile cf;
	cf.load( MediaDirStr + "/resources.cfg" );

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String                      secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings =
				seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i=settings->begin(); i!=settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().
			addResourceLocation( MediaDirStr + archName,
				typeName,
				secName );
		}
		// wxYield();
	}
}

void OgreWindow::OnCreate( wxWindowCreateEvent& Event )
{
	try
	{
#ifndef _WIN32
		// Postpone init till we are realized
		if ( !gtk_widget_get_realized( this->GetHandle() ) )
			return;

#endif
		std::cout << __FILE__ << ": " << __LINE__ << std::endl;
		std::cout <<
		( mContextCreated ? "Context created" : "Context NOT created" )
				  << std::endl;

		Ogre::NameValuePairList Params = GetRenderWindowParams( this );

		if( !mRoot )
			mRoot.reset( new Ogre::Root( "", "" ) );

		// Load resources and plugins
		LoadResources();
		LoadPlugins( mRoot.get() );

		if ( !SelectRendersystem( mRoot.get() ) )
		{
			std::cout << "Unable to select RenderSystem" <<
			std::endl;
		}
		//	return;

		// Initialize root without creating a render window yet
		mRoot->initialise( false );

		// Create the render window with the given wxwindow handle
		int DisplayWidth=0;
		int DisplayHeight=0;
		this->GetSize( &DisplayWidth, &DisplayHeight );

		mRenderWindow = mRoot->createRenderWindow (
			Ogre::String ( "OgreRenderWindow" ),
			DisplayWidth, DisplayHeight, false, &Params );
		mRenderWindow->setActive ( true );

		// Get active SceneManager...
		this->mSceneMgr = mRoot->createSceneManager( Ogre::ST_GENERIC,
			"SceneManager" );

		if ( mInitFunc )
			mInitFunc();

		mContextCreated = true;
	}
	catch(... )
	{
		std::cout << "Some error happened (" << __FILE__ << ")" <<
		std::endl;
	}
}

void OgreWindow::OnPaint( wxPaintEvent& Event )
{
	/*if ( !mContextCreated )
	   {
			wxWindowCreateEvent Event;
			OnCreate(Event);
	   }*/

	wxPaintDC Context( this );

	UpdateOgre();
}

void OgreWindow::OnResize( wxSizeEvent& evt )
{
	if ( !mContextCreated )
	{
		wxWindowCreateEvent Event;
		OnCreate( Event );
	}
	// Setting new size;
	int width = evt.GetSize().GetWidth ();
	int height = evt.GetSize().GetHeight ();
	this->GetSize( &width,&height );

	// Letting Ogre know the window has been resized;
	if ( mRenderWindow )
	{
#ifndef _WIN32
		mRenderWindow->resize( width,height );
#endif
		mRenderWindow->windowMovedOrResized();
	}

	evt.Skip();
}

void OgreWindow::UpdateOgre()
{
	if(!mRenderWindow)
		return;

	mRoot->_fireFrameStarted();
	mRoot->_fireFrameRenderingQueued();
	mRenderWindow->update( true );
	mRoot->_fireFrameEnded();

	int   numTris = int(mRenderWindow->getTriangleCount());
	float avFPS = mRenderWindow->getAverageFPS();

	wxString metrics;
	metrics.Printf( wxT( "FPS: %f\tTris:%i" ), avFPS, numTris );

	MainFrame* mf = reinterpret_cast<MainFrame*>( GetParent());
	mf->SetStatusMessage( metrics, 1 );
}
