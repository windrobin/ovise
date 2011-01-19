#include "AddMeshDialog.h"
#include "SceneHandling.h"

#ifdef __WXGTK__
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#endif

MeshDialogFrameListener::MeshDialogFrameListener(Ogre::SceneManager *scnMgr)
:
mSceneManager( scnMgr )
{
}

MeshDialogFrameListener::~MeshDialogFrameListener()
{
}

bool MeshDialogFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	try
    {
		Ogre::SceneNode *tmp = mSceneManager->getSceneNode("MeshNode");
        tmp->roll(Ogre::Radian(Ogre::Degree(0.1)));
    }
    catch(...) { }
    return true;
}

bool MeshDialogFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
    return true;
}

//----------------------------------------------------------------------

OViSEAddMeshDialog::OViSEAddMeshDialog( wxWindow* parent, wxWindowID id )
:
AddMeshDialog( parent, id ),
mRenderWin( NULL )
{
    mRenderWinWX = new wxWindow(this, wxID_ANY);
    ListSizer->Insert(0, mRenderWinWX, 4, wxEXPAND);
    mRenderWinWX->Bind( wxEVT_SIZE, &OViSEAddMeshDialog::OnRenderWinResize, this );
}

void OViSEAddMeshDialog::InitOgre()
{
	// Create the render window with the given wxwindow handle
	Ogre::NameValuePairList params;
#ifdef __WXMSW__
	params["externalWindowHandle"] = GetOgreHandle();
#elif defined(__WXGTK__)
	params["parentWindowHandle"] = GetOgreHandle();
#endif
	int width;
	int height;
	mRenderWinWX->GetSize (&width, &height);
	mRenderWin = Ogre::Root::getSingleton ().createRenderWindow (
		Ogre::String ("AddMeshDialogRender"),
		width, height, false, &params);
	mRenderWin->setActive (true);

//	qSceneMgr = OgreMediator::GetSingletonPtr()->iSceneManager.Create( wxT("AddMeshScene" ) );
//	mSceneMgr = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr( qSceneMgr );

	mListener = new MeshDialogFrameListener( mSceneMgr );
    Ogre::Root::getSingletonPtr()->addFrameListener(mListener);

    mCam = mSceneMgr->createCamera("AddMeshCam");
    mCam->setNearClipDistance(0.001);
    mCam->setFarClipDistance(1000);
	mCam->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    mCam->setPosition(-20, 0, 5);
    mCam->lookAt(0, 0, 0);
    mCam->setAutoAspectRatio(true);

    mMeshNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MeshNode");
//	qMeshNode = QualifiedName::Create( wxT( "MeshNode" ) );
	//OgreMediator::GetSingletonPtr()->GetObjectAccess()->AddSceneNode(qMeshNode, mMeshNode);
        
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    mLight = mSceneMgr->createLight("AddMeshLight");
    mLight->setType(Ogre::Light::LT_DIRECTIONAL);
    mLight->setPosition(-20, 0, 0);
    mLight->setDirection(1, -1, 0);

	//OgreMediator::GetSingletonPtr()->AddGrid(1, 10, 10, Ogre::Vector3(1, 1, 1), qSceneMgr, qMeshNode);

    Ogre::Viewport *vP = mRenderWin->addViewport(mCam);
    vP->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));

    updateMeshList();
}

void OViSEAddMeshDialog::updateMeshList()
{
	std::vector<std::string> groups = SceneHandling::getAvailableResourceGroupNames();
	for(std::vector<std::string>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		try
		{
			std::vector<std::string> meshlist = SceneHandling::getAvailableMeshes(*it);
			for(std::vector<std::string>::iterator iter = meshlist.begin(); iter != meshlist.end(); iter++)
			{
				if((*iter).rfind(".mesh") == (*iter).length() - 5)
					mMeshList->Append(wxString(iter->c_str(), wxConvUTF8));
			}
		}
		catch (OViSEException e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
		}
	}
}

void OViSEAddMeshDialog::OnCloseDialog( wxCloseEvent& event )
{
    Ogre::Root::getSingletonPtr()->removeFrameListener(mListener);
    delete mListener;
	Ogre::Root::getSingletonPtr()->detachRenderTarget("AddMeshDialogRender");
//	OgreMediator::GetSingletonPtr()->iSceneManager.Destroy( qSceneMgr );
    Destroy();
}

void OViSEAddMeshDialog::OnMeshListSelect( wxCommandEvent& event )
{
    wxString selected = mMeshList->GetStringSelection();
    if(selected.IsEmpty())
        return;
    if(selected.Cmp(lastSelected) == 0)
        return;

    Ogre::String meshToLoad(selected.ToAscii());
    if(mSceneMgr->hasEntity("tmp"))
    {
        mMeshNode->removeAllChildren();
        mSceneMgr->destroyEntity("tmp");
    }
	mMeshNode->setPosition( 0, 0, 0 );
    mCam->setPosition(-20, 0, 5);
    mCam->lookAt(0, 0, 0);
    Ogre::Entity *ent = mSceneMgr->createEntity("tmp", meshToLoad);
	Ogre::AxisAlignedBox BBox = ent->getBoundingBox();
    mMeshNode->attachObject(ent);
    Ogre::Vector3 centering = BBox.getCenter() - mMeshNode->getPosition();
    mMeshNode->translate(-centering, Ogre::Node::TS_WORLD);

    // Move camera so whole object is displayed
    double angle = mCam->getFOVy().valueRadians()/2;
    double dist = BBox.getSize().length()* 2 * cos(angle);
    if(dist < 0.5)
        dist = 0.5;
    Ogre::Vector3 tmp = mCam->getPosition() - BBox.getCenter();
    double toMove = dist - tmp.length();
    if(fabs(toMove) > 0.1)
    {
        mCam->moveRelative(Ogre::Vector3(0, 0, toMove));
    }
    lastSelected = selected;
}

void OViSEAddMeshDialog::OnOkClick( wxCommandEvent& event )
{
    // Add selected mesh to the base scene and close the dialog
//   	OgreMediator *Med = OgreMediator::GetSingletonPtr();
//wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
//Med->iEntity.Create( tmp, lastSelected );        
    this->Close();
}

void OViSEAddMeshDialog::OnApplyClick( wxCommandEvent& event )
{
    // Add selected mesh to the base scene and continue the dialog
//    OgreMediator *Med = OgreMediator::GetSingletonPtr();
//	wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
//	Med->iEntity.Create( tmp, lastSelected ); 
}

void OViSEAddMeshDialog::OnCancelClick( wxCommandEvent& event )
{
    Close();
}

void OViSEAddMeshDialog::OnRenderWinResize( wxSizeEvent& event )
{
	if( mRenderWin )
	{
		// Setting new size;
		int width = event.GetSize().GetWidth ();
		int height = event.GetSize().GetHeight ();
		mRenderWin->resize(width, height);
		// Letting Ogre know the window has been resized;
		mRenderWin->windowMovedOrResized ();
	}
}

Ogre::String OViSEAddMeshDialog::GetOgreHandle()
{
	Ogre::String handle;

#ifdef __WXMSW__
	// Handle for Windows systems
	handle = Ogre::StringConverter::toString((size_t)((HWND)mRenderWinWX->GetHandle()));
#elif defined(__WXGTK__)
	GtkWidget* widget = mRenderWinWX->GetHandle();
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

OViSEAddMeshDialog::~OViSEAddMeshDialog()
{
}
