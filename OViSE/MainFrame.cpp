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
    : MainFrameBase(parent)
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

	setupObjectProperties();

	//mAddMeshDialog = NULL;

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
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(mLogBoxListener);
	delete mRoot;
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

	// Create camera setup
	QualifiedName* qCamFokusSceneNode = OgreAPIMediator::GetSingletonPtr()->CreateSceneNode(ToWxString("mainCamFocusNode"));
	if (qCamFokusSceneNode == 0 ) return false;
	Ogre::SceneNode *camFocusNode = OgreAPIMediator::GetSingletonPtr()->GetSceneNodePtr(*qCamFokusSceneNode);
	camFocusNode->setFixedYawAxis(true);
	QualifiedName* qCamSceneNode = OgreAPIMediator::GetSingletonPtr()->CreateSceneNode(ToWxString("CamNode"), camFocusNode);
	if (qCamSceneNode == 0 ) return false;
	Ogre::SceneNode *camNode = OgreAPIMediator::GetSingletonPtr()->GetSceneNodePtr(*qCamSceneNode);
	camNode->setFixedYawAxis(true);
	camNode->setPosition(0, 10, 20);
	QualifiedName* qCamera = OgreAPIMediator::GetSingletonPtr()->CreateCamera(ToWxString("MainCam"), camNode);
	if (qCamera == 0 ) return false;
	mCam = OgreAPIMediator::GetSingletonPtr()->GetCameraPtr(*qCamera);
	mCam->setPosition(Ogre::Vector3(0,0,20));
	mCam->lookAt(Ogre::Vector3::ZERO);
    mCam->setNearClipDistance(5);
    mCam->setFixedYawAxis(true);
	mCam->setAutoAspectRatio(true);
	mCam->setQueryFlags(0x01);

	wxYield();
	// Create viewport for camera
    Ogre::Viewport *mVp = mRenderWin->addViewport(mCam);

	// Initialize resources
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// DBG: Testscene
	OgreAPIMediator* Mediator = OgreAPIMediator::GetSingletonPtr();
	Mediator->CreateEntity(ToWxString("Plane"), ToWxString("Plane.mesh"));
	Mediator->CreateEntity(ToWxString("CoS"), ToWxString("CoS.mesh"));

	QualifiedName* qSunLight = Mediator->CreateLight(ToWxString("Sun"));
	Ogre::Light* SunLight = Mediator->GetLightPtr(*qSunLight);
	SunLight->setCastShadows(true);
	SunLight->setDirection(-1,-1,-1);
	SunLight->setPosition(100, 100, 100);

	// Create scene tree
	wxImageList *sceneTreeImageList = new wxImageList(16, 16, true, 5);
	loadSceneTreeImageList(sceneTreeImageList);
	mSceneMgr = OgreAPIMediator::GetSingletonPtr()->GetSceneManagerPtr(OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager());
	mSceneTree = new SceneTree(mSceneMgr, this, SCENETREE, wxDefaultPosition, wxSize(300, -1), wxTR_EDIT_LABELS | wxTR_MULTIPLE | wxTR_DEFAULT_STYLE);
	mWindowManager.AddPane(mSceneTree, wxRIGHT, wxT("Scene structure"));
	mSceneTree->SetImageList(sceneTreeImageList);
	mSceneTree->initTree();
	// When selection in OViSESceneTree changed, call MainFrame::OnSelectionChanged(...) !
	mSceneTree->Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &MainFrame::OnTreeSelectionChanged, this);
	//MainFrame::OnViewClick handles the other direction

	mWindowManager.Update();

	// Parking call here for a short time whil REFACTORING. H.R.
	// Initialize DotSceneManager
	mDotSceneMgr = new OViSEDotSceneManager(OViSEDotSceneManager::CreateDefaultConfiguration());

	// Create input handler
	mInputHandler = new InputHandler(mCam, camFocusNode, mMainRenderWin);

	mOgreInitialized = true;
	return true;
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
	description += wxT("Department of Computer Science\n");
	description += wxT("Karlsruhe Institute of Technology (KIT)\n");
	description += wxT("Ogre Framework for scene visualization. Uses Ogre3D (http://www.ogre3d.org)");
	info.SetDescription(description);

    info.SetCopyright(wxT("(C) 2008-2009 "));

	info.AddDeveloper(wxT("Programming - Alexander Kasper <akasper@ira.uka.de>\n"));
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
	/*
	if(mAddMeshDialog == NULL)
	{
		mAddMeshDialog = new OViSEAddMeshDialog(this, wxID_HIGHEST + 1);
		mAddMeshDialog->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnAddMeshDialogClose ), NULL, this);
	}
	mAddMeshDialog->Show();
	*/
}

void MainFrame::OnAddMeshDialogClose(wxCloseEvent& event)
{
	event.Skip();
	//mAddMeshDialog = NULL;
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

	// REACTORING of "OViSESceneHandling" takes affect here! //

	QualifiedNameCollection QNames = OgreAPIMediator::GetSingletonPtr()->GetQueryObjects(sx, sy, mCam, OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager());
	
	if(!QNames.IsEmpty())
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
				// CASE 4: Unselect all in complete Query, Add complete Query < IRREGULAR: only unselect, if all from Query are selected
				if (QNames.Count() > 0)
				{
					QualifiedNameCollection UnselectedQNames = QualifiedNameCollection::CollectionDifference(QNames, SelectionManager::getSingletonPtr()->Selection);
					if (UnselectedQNames.Count() > 0)
					{
						SelectionManager::getSingletonPtr()->Selection = QualifiedNameCollection::CollectionUnion(SelectionManager::getSingletonPtr()->Selection, UnselectedQNames);
						for (unsigned long IT = 0; IT < UnselectedQNames.Count(); IT++)
						{
							// Select in SceneTree-View
							wxTreeItemId Item = this->mSceneTree->Items[UnselectedQNames[IT].UniqueName()]; // TODO: Upgrade
							this->mSceneTree->SelectItem(Item);
						}
					}
					else
					{
						SelectionManager::getSingletonPtr()->Selection = QualifiedNameCollection::CollectionDifference(SelectionManager::getSingletonPtr()->Selection, QNames);
						for (unsigned long IT = 0; IT < QNames.Count(); IT++)
						{
							// Select in SceneTree-View
							wxTreeItemId Item = this->mSceneTree->Items[QNames[IT].UniqueName()]; // TODO: Upgrade
							this->mSceneTree->UnselectItem(Item);
						}
					}
				}
			}
			else
			{
				// CASE 2: Unselect one or nothing, Add one or nothing to Selection(front)
				if (QNames.Count() > 0)
				{
					// Add to first selection // Selection is clear, so it's not neccessary to test, if QName is already in there
					if (SelectionManager::getSingletonPtr()->Selection.Contains(QNames[0]))
					{
						SelectionManager::getSingletonPtr()->Selection.Remove( QNames[0] );
	
						// Unelect in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()]; // TODO: Upgrade
						this->mSceneTree->UnselectItem(Item);
					}
					else
					{
						// Select in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()]; // TODO: Upgrade
						this->mSceneTree->SelectItem(Item);
					}
				}
			}
		}
		else
		{
			if (event.ShiftDown())
			{
				// CASE 3: Unselect all, Add complete Query
				SelectionManager::getSingletonPtr()->Selection.Clear();
				this->mSceneTree->UnselectAll();

				if (QNames.Count() > 0)
				{
					for (unsigned long IT = 0; IT < QNames.Count(); IT++)
					{
						// Add to all selection // Selection is clear, so it's not neccessary to test, if QName is already in there
						SelectionManager::getSingletonPtr()->Selection.Add(QNames[IT]);
						
						// Select in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[IT].UniqueName()]; // TODO: Upgrade
						this->mSceneTree->SelectItem(Item);
					}
				}
			}
			else
			{
				// CASE 1: Unselect all, Select one or nothing
				SelectionManager::getSingletonPtr()->Selection.Clear();
				this->mSceneTree->UnselectAll();

				if (QNames.Count() > 0)
				{
					// Add to first selection // Selection is clear, so it's not neccessary to test, if QName is already in there
					SelectionManager::getSingletonPtr()->Selection.Add(QNames[0]);

					// Select in SceneTree-View
					wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()]; // TODO: Upgrade
					this->mSceneTree->SelectItem(Item);
				}
			}
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
	wxTreeItemId Item = event.GetItem();

	wxString Msg = ToWxString("SELECTED ITEMS:");

	if (!Item.IsOk()) // case : UnselectAll()
	{
		this->RemoveAllSelectedObjects();
	}
	else // case : UnselectItem(...)
	{
		wxString TreeItemLabel = this->mSceneTree->GetItemText(Item);

		Ogre::MovableObject* selectedObject = SceneHandling::getSingletonPtr()->getSelectedObject(TreeItemLabel, this->mSceneMgr);

		this->RemoveAllSelectedObjects();

		wxArrayTreeItemIds SelectedItems;
		this->mSceneTree->GetSelections(SelectedItems);

		wxString SceneManagerName;// = SelectionManager::getSingletonPtr()->Selection.getSceneManagerName();

		
		int count = SelectedItems.Count();
		for(unsigned int IT = 0; IT < SelectedItems.Count(); IT++)
		{
			wxString ItemLabel = this->mSceneTree->GetItemText(SelectedItems[IT]);
			Msg << ToWxString(" '") << ItemLabel << ("' ");
			
			QualifiedNameCollection QNames = QualifiedNameCollection::GetQualifiedNameByUnique(ItemLabel);
			if (QNames.Count() == 1)
			{
				Ogre::MovableObject* SelectedObject = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(QNames[0]);
				if(SelectedObject != NULL)
				{
					this->AddSelectedObject(SelectedObject, ToWxString(mCam->getSceneManager()->getName()));
				}
			}
		}
	}

	Logging::GetSingletonPtr()->WriteToOgreLog(Msg, Logging::Normal);
	/*
	{
		

		//this->ToogleSelectedObject(selectedObject, ToWxString(this->mMainRenderWin->GetCamera()->getSceneManager()->getName()));
		
		
	}*/
}

void MainFrame::AddSelectedObject(Ogre::MovableObject* selectedObject, wxString SceneManagerName)
{
	//mSceneHdlr->addObjectToSelection(selectedObject, true, ToStdString(SceneManagerName));
	//setObjectProperties(selectedObject);

	// #Mark:NewSelection#

	/*wxString ObjectName = ToWxString(selectedObject->getName());

	SelectionManager::getSingletonPtr()->Selection.setSceneManagerName(SceneManagerName);
	if (SelectionManager::getSingletonPtr()->Selection.hasMovableObject(ObjectName))
	{
		// Remove from selection
		SelectionManager::getSingletonPtr()->Selection.removeMovableObject(ObjectName); // Toggle item
		
		// Hide bounding box
		selectedObject->getParentSceneNode()->showBoundingBox(false);
	}
	else
	{
		// Add to selection
		OgreEnums::MovableObject::MovableType Type = OgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getStringAsEnum(ToWxString(selectedObject->getMovableType()));
		SelectionManager::getSingletonPtr()->Selection.addMovableObject(ObjectName, Type);
		
		// Show bounding box
		selectedObject->getParentSceneNode()->showBoundingBox(true);
	//}

	SelectionManager::getSingletonPtr()->generatePropertyGridContentFromSelection(this->mObjectProperties);*/
}

void MainFrame::RemoveAllSelectedObjects()
{
	//this->mSceneHdlr->clearObjectSelection(/*cam->getSceneManager()->getName()*/);
	//clearObjectProperties();
	
	/*wxArrayString Keys = SelectionManager::getSingletonPtr()->Selection.getAllMovableObjectNames();
	wxString NameOfSceneManager = SelectionManager::getSingletonPtr()->Selection.getSceneManagerName();
	for (int IT = 0; IT < Keys.Count(); IT++)
	{
		wxString SceneManagerName = OViSESelectionManager::getSingletonPtr()->Selection.getSceneManagerName();
		OgreEnums::MovableObject::MovableType Type = SelectionManager::getSingletonPtr()->Selection.SelectedObjects[Keys[IT]];

		Ogre::MovableObject* SelectedObject = OgreAPIMediator::GetSingletonPtr()->getMovableObjectPtr(
			OViSESelectionManager::getSingletonPtr()->Selection.getSceneManagerName(),
			Keys[IT],
			Type);

		if(SelectedObject != NULL) SelectedObject->getParentSceneNode()->showBoundingBox(false);
	}
	// #Mark:NewSelection#
	SelectionManager::getSingletonPtr()->Selection.removeAll();

	this->mObjectProperties->Clear();*/
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
		wxFileInputStream input(pcFileDialog.GetDirectory() + wxT("\\") + pcFileDialog.GetFilename());
		wxTextInputStream text(input);
		wxString line;
		float t;

		std::vector<float> pointvector;
		int counter = 0, cc = 0;
		while(!input.Eof())
		{
			text >> t;
			pointvector.push_back(t);
			cc++;
			if(cc == 3)
			{
				counter++;
				cc = 0;
			}
		}
		
		float *pointlist = new float[counter*3-1];
		for(int i = 0; i<counter*3-1; i++)
		{
			pointlist[i] = pointvector.at(i);
		}

		Pointcloud *pc = new Pointcloud(std::string(pcName.mb_str()), "General", counter, pointlist, NULL);

		Ogre::Entity *pcEnt = mSceneMgr->createEntity(std::string(pcEntName.mb_str()), std::string(pcName.mb_str()));
		pcEnt->setMaterialName("Pointcloud");
		mSceneMgr->getRootSceneNode()->attachObject(pcEnt);
	}
}

void MainFrame::OnShowSceneStructure(wxCommandEvent &event)
{
	//mSceneHdlr->showSceneGraphStructure();
}


void MainFrame::OnTestStuff( wxCommandEvent& event )
{
	//mSceneHdlr->testStuff();
}
