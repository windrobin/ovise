/***************************************************************
 * Name:      OViSEWxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#include "OViSEWxMain.h"

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


OViSEWxFrame::OViSEWxFrame(wxFrame *frame, Ogre::Root *ogreRoot)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("OViSE started up."), 0);
	statusBar->SetStatusText(wxT("FPS:"), 1);
#endif

	mWindowManager = new wxAuiManager(this);

	wxOgreRenderWindow::SetOgreRoot(ogreRoot);
	mRoot = ogreRoot;

	mMainRenderWin = new wxOgreRenderWindow(NULL, NULL, this, WINDOW_MainRender);
	mWindowManager->AddPane(mMainRenderWin, wxCENTER, wxT("RenderWindow"));
	mMainRenderWin->SetStatusBar(statusBar);

	mMainRenderWin->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler( OViSEWxFrame::OnViewClick ), NULL, this);

    finishOgreInitialization();
	setupObjectProperties();

	wxImageList *sceneTreeImageList = new wxImageList(16, 16, true, 5);
	loadSceneTreeImageList(sceneTreeImageList);
	
	//mSceneTree = new OViSESceneTree(mSceneHdlr->getSceneManager(), this, SCENETREE, wxDefaultPosition, wxSize(300, -1), wxTR_EDIT_LABELS | wxTR_MULTIPLE | wxTR_DEFAULT_STYLE);
	this->mSceneTree = new OViSESceneTree(OgreAPIMediator::GetSingletonPtr()->GetSceneManagerPtr(OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager()), this, SCENETREE, wxDefaultPosition, wxSize(300, -1), wxTR_EDIT_LABELS | wxTR_MULTIPLE | wxTR_DEFAULT_STYLE);
	mWindowManager->AddPane(mSceneTree, wxRIGHT, wxT("Scene structure"));
	mSceneTree->SetImageList(sceneTreeImageList);
	mSceneTree->initTree();

	logBox = new wxListBox(this, wxID_ANY);
	mWindowManager->AddPane(logBox, wxBOTTOM, wxT("Log"));
	mLogBoxListener = new OViSELogListener(logBox);

	//mAddMeshDialog = NULL;

	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(mLogBoxListener);

	this->Maximize(true);

	mWindowManager->Update();

	// When selection in OViSESceneTree changed, call OViSEWxFrame::OnSelectionChanged(...) !
	this->mSceneTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( OViSEWxFrame::OnTreeSelectionChanged ), NULL, this);
	// OViSEWxFrame::OnViewClick handles the other direction

	// Parking call here for a short time whil REFACTORING. H.R.
	// Initialize DotSceneManager
	this->mDotSceneMgr = new OViSEDotSceneManager(OViSEDotSceneManager::CreateDefaultConfiguration());
}

OViSEWxFrame::~OViSEWxFrame()
{
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(mLogBoxListener);
}

void OViSEWxFrame::finishOgreInitialization()
{
	QualifiedName* qCamFokusSceneNode = OgreAPIMediator::GetSingletonPtr()->CreateSceneNode(ToWxString("mainCamFocusNode"));
	if (qCamFokusSceneNode == 0 ) return;
	Ogre::SceneNode *camFocusNode = OgreAPIMediator::GetSingletonPtr()->GetSceneNodePtr(*qCamFokusSceneNode);

	camFocusNode->setFixedYawAxis(true);

	QualifiedName* qCamSceneNode = OgreAPIMediator::GetSingletonPtr()->CreateSceneNode(ToWxString("CamNode"), camFocusNode);
	if (qCamSceneNode == 0 ) return;
	Ogre::SceneNode *camNode = OgreAPIMediator::GetSingletonPtr()->GetSceneNodePtr(*qCamSceneNode);

	camNode->setFixedYawAxis(true);
	camNode->setPosition(0, 10, 20);

	QualifiedName* qCamera = OgreAPIMediator::GetSingletonPtr()->CreateCamera(ToWxString("MainCam"), camNode);
	if (qCamera == 0 ) return;
	this->mCam = OgreAPIMediator::GetSingletonPtr()->GetCameraPtr(*qCamera);

	this->mCam->setPosition(Ogre::Vector3(0,0,20));
	// Look back along -Z
	this->mCam->lookAt(Ogre::Vector3::ZERO);
    this->mCam->setNearClipDistance(5);

    this->mCam->setFixedYawAxis(true);
	this->mCam->setQueryFlags(0x01);

	// OLD // UNCHANGED
    Ogre::Viewport *mVp = mMainRenderWin->GetRenderWindow()->addViewport(mCam);
	mMainRenderWin->SetCamera(mCam, camFocusNode);

    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	//mSceneHdlr->createDefaultScene();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    mCam->setAutoAspectRatio(true);

	// OLD
	/*mSceneHdlr = OViSESceneHandling::getSingletonPtr();
	mSceneMgr = mSceneHdlr->getSceneManager();

    mCam = mSceneMgr->createCamera("MainCam");

	mCam->setPosition(Ogre::Vector3(0,0,20));
	// Look back along -Z
	mCam->lookAt(Ogre::Vector3::ZERO);
    mCam->setNearClipDistance(5);

    mCam->setFixedYawAxis(true);
	mCam->setQueryFlags(0x01);

	Ogre::SceneNode *camFocusNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("mainCamFocusNode");
	camFocusNode->setFixedYawAxis(true);
	Ogre::SceneNode *camNode = camFocusNode->createChildSceneNode("CamNode");
	camNode->setFixedYawAxis(true);
	camNode->setPosition(0, 10, 20);
	camNode->attachObject(mCam);

    Ogre::Viewport *mVp = mMainRenderWin->GetRenderWindow()->addViewport(mCam);
	mMainRenderWin->SetCamera(mCam, camFocusNode);

    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	//mSceneHdlr->createDefaultScene();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    mCam->setAutoAspectRatio(true);*/
}

void OViSEWxFrame::setupObjectProperties()
{
	mObjectProperties = new wxPropertyGrid(this, PGID, wxDefaultPosition, wxSize(300, -1));
	mWindowManager->AddPane(mObjectProperties, wxRIGHT, wxT("Properties"));
	this->Connect(PGID, wxEVT_PG_CHANGED, wxPropertyGridEventHandler(OViSEWxFrame::OnPropertyChange));
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

void OViSEWxFrame::loadSceneTreeImageList(wxImageList *list)
{
	// index 0 = ROOT
	wxBitmap rootIcon(wxT("../Media/data/home_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(rootIcon);
	// index 1 = SCENE_NODE
	wxBitmap nodeIcon(wxT("../Media/data/folder_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(nodeIcon);
	// index 2 = MESH
	wxBitmap meshIcon(wxT("../Media/data/box_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(meshIcon);
	// index 3 = CAMERA
	wxBitmap cameraIcon(wxT("../Media/data/camera_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(cameraIcon);
	// index 4 = LIGHT
	wxBitmap lightIcon(wxT("../Media/data/lightbulb_16.png"), wxBITMAP_TYPE_PNG);
	list->Add(lightIcon);
}

void OViSEWxFrame::OnClose(wxCloseEvent &event)
{
	for(std::map<std::string, wxFrame*>::iterator i = mViewWindows.begin(); i != mViewWindows.end(); i++)
	{
		(*i).second->Close();
	}
    Destroy();

	OViSESceneHandling::release();
}

void OViSEWxFrame::OnQuit(wxCommandEvent &event)
{
	for(std::map<std::string, wxFrame*>::iterator i = mViewWindows.begin(); i != mViewWindows.end(); i++)
	{
		(*i).second->Close();
	}
    Destroy();

	OViSESceneHandling::release();
}

void OViSEWxFrame::OnAbout(wxCommandEvent &event)
{
    wxAboutDialogInfo info;
    info.SetName(wxT("OViSE"));
    info.SetVersion(wxT("0.2 Beta (orc)"));

	wxString description = wxT("Institute of Computer Science and Engineering (CSE)\n\r");
	description += wxT("Industrial Applications of Computer Science and Micro Systems (IAIM)\n");
	description += wxT("Prof. Dr. R. Dillmann\n");
	description += wxT("Department of Computer Science\n");
	description += wxT("Karlsruhe Institute of Technology (KIT)\n");
	description += wxT("Ogre Framework for scene visualization. Uses Ogre3D (http://www.ogre3d.org)");
	info.SetDescription(description);

    info.SetCopyright(wxT("(C) 2008-2009 "));

	info.AddDeveloper(wxT("Programming - Alexander Kasper <akasper@ira.uka.de>"));
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

void OViSEWxFrame::OnAddView(wxCommandEvent &event)
{
	int camNo = 0;
	wxString wxCamName;
	wxCamName.Printf(wxT("Camera %i"), camNo);
	while(mSceneMgr->hasCamera(Ogre::String(wxCamName.ToAscii())))
	{
		camNo += 1;
		wxCamName.Printf(wxT("Camera %i"), camNo);
	}
	Ogre::Camera *newCam = mSceneMgr->createCamera(Ogre::String(wxCamName.ToAscii()));
	mAdditionalCameras[Ogre::String(wxCamName.ToAscii())] =  newCam;
	Ogre::SceneNode *camFocusNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camFocusNode->setFixedYawAxis(true);
	Ogre::SceneNode *camNode = camFocusNode->createChildSceneNode();
	camNode->setFixedYawAxis(true);
	camNode->setPosition(0, 0, 10);
	camNode->attachObject(newCam);
    newCam->setNearClipDistance(5);
	newCam->setQueryFlags(0x01);

	// Need to create a new Frame to display the new renderwindow in
	wxFrame *newFrame = new wxFrame(this, wxID_ANY, wxCamName);
	wxOgreRenderWindow *newRenderWin = new wxOgreRenderWindow(newCam, camFocusNode, newFrame, wxID_ANY);
	newRenderWin->SetOgreRoot(mRoot);
	mViewWindows[std::string(wxCamName.ToAscii())] = newFrame;

	newRenderWin->GetRenderWindow()->addViewport(newCam);
	newRenderWin->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler( OViSEWxFrame::OnViewClick ), NULL, this);
	newCam->setAutoAspectRatio(true);

	newFrame->Show();
	newFrame->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OViSEWxFrame::OnAdditionalViewClose ), NULL, this);
}

void OViSEWxFrame::OnAdditionalViewClose(wxCloseEvent &event)
{
	wxFrame *tmp = dynamic_cast<wxFrame*>(event.GetEventObject());
	std::string name = std::string(tmp->GetTitle().ToAscii());
	mViewWindows.erase(name);
	event.Skip();
}

void OViSEWxFrame::OnSaveScreenToFile(wxCommandEvent &event)
{
	wxFileDialog *fDialog = new wxFileDialog(this, wxT("Save screen to file"), wxGetHomeDir(), wxT("OViSEScreenshot.png"),
		wxT("PNG files (*.png)|*.png"), wxFD_SAVE);
	int rval = fDialog->ShowModal();
	if(rval == wxID_OK)
	{
		wxString fullPath = fDialog->GetPath();
		mMainRenderWin->GetRenderWindow()->writeContentsToFile(Ogre::String(fullPath.ToAscii()));
	}
	fDialog->Destroy();
}

void OViSEWxFrame::OnSceneAddMesh(wxCommandEvent &event)
{
	/*
	if(mAddMeshDialog == NULL)
	{
		mAddMeshDialog = new OViSEAddMeshDialog(this, wxID_HIGHEST + 1);
		mAddMeshDialog->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OViSEWxFrame::OnAddMeshDialogClose ), NULL, this);
	}
	mAddMeshDialog->Show();
	*/
}

void OViSEWxFrame::OnAddMeshDialogClose(wxCloseEvent& event)
{
	event.Skip();
	//mAddMeshDialog = NULL;
}

void OViSEWxFrame::OnViewClick(wxMouseEvent& event)
{
	// Collect basic information
	wxOgreRenderWindow *win = dynamic_cast<wxOgreRenderWindow*>(event.GetEventObject());
	wxPoint p = event.GetPosition();
	wxPoint t = win->GetScreenPosition();
	int width = win->GetRenderWindow()->getWidth();
	int height = win->GetRenderWindow()->getHeight();
	wxPoint s = p;
	float sx = (float)s.x / (float)width;
	float sy = (float)s.y / (float)height;
	float d = -1;
	Ogre::Camera *cam = win->GetCamera();
	
	// Get QualifiedNameCollection from scene-query
	QualifiedNameCollection QNames = OgreAPIMediator::GetSingletonPtr()->GetQueryObjects(sx, sy, cam, OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager());
	
	// Handle selection
	if(QNames.IsEmpty())
	{
		// Nothing selected
		this->mSceneTree->UnselectAll();
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
				// CASE 4: Unselect all in complete Query, Add complete Query < IRREGULAR: only unselect, if all from Query are selected
				if (QNames.GetCount() > 0)
				{
					QualifiedNameCollection UnselectedQNames = QualifiedNameCollectionInterface::CollectionDifference(QNames, SelectionManager::getSingletonPtr()->Selection);
					if (UnselectedQNames.GetCount() > 0)
					{
						SelectionManager::getSingletonPtr()->Selection = QualifiedNameCollectionInterface::CollectionUnion(SelectionManager::getSingletonPtr()->Selection, UnselectedQNames);
						for (unsigned long IT = 0; IT < QNames.GetCount(); IT++)
						{
							// Select in SceneTree-View
							wxTreeItemId Item = this->mSceneTree->Items[QNames[IT].UniqueName()];
							this->mSceneTree->SelectItem(Item);
						}
					}
					else
					{
						for (unsigned long IT = 0; IT < QNames.GetCount(); IT++)
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
				if (QNames.GetCount() > 0)
				{
					// Add to first selection // Selection is clear, so it's not neccessary to test, if QName is already in there
					if (QualifiedNameCollectionInterface::CollectionContains(SelectionManager::getSingletonPtr()->Selection, QNames[0]))
					{
						// Unelect in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()];
						this->mSceneTree->UnselectItem(Item);
					}
					else
					{
						// Select in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()];
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
				this->mSceneTree->UnselectAll();

				if (QNames.GetCount() > 0)
				{
					for (unsigned long IT = 0; IT < QNames.GetCount(); IT++)
					{
						// Select in SceneTree-View
						wxTreeItemId Item = this->mSceneTree->Items[QNames[IT].UniqueName()]; // TODO: Upgrade
						this->mSceneTree->SelectItem(Item);
					}
				}
			}
			else
			{
				// CASE 1: Unselect all, Select one or nothing
				this->mSceneTree->UnselectAll();
				
				if (QNames.GetCount() > 0)
				{
					// Select in SceneTree-View
					wxTreeItemId Item = this->mSceneTree->Items[QNames[0].UniqueName()]; // TODO: Upgrade
					this->mSceneTree->SelectItem(Item);
				}
			}
		}
	}

	/*

		//if(!event.ControlDown()) this->RemoveAllSelectedObjects(); // ????
		wxString ObjectName = ToWxString(selectedObject->getName());
		wxTreeItemId Item = this->mSceneTree->Items[ObjectName];
		if(OViSESelectionManager::getSingletonPtr()->Selection.SelectedObjects.count(ObjectName) == 1/*this->mSceneTree->IsSelected(Item)*//*)
		{
			if(event.ControlDown()) this->mSceneTree->UnselectItem(Item);
			else this->mSceneTree->UnselectAll();
		}
		else
		{
			if(event.ControlDown()) this->mSceneTree->SelectItem(Item);
			else
			{
				wxArrayTreeItemIds selections;
				this->mSceneTree->GetSelections(selections);
				this->mSceneTree->UnselectAll();
				this->mSceneTree->SelectItem(Item);
			}
		}
		//this->ToogleSelectedObject(selectedObject, ToWxString(cam->getSceneManager()->getName()));
	}
	else
	{
		this->mSceneTree->UnselectAll();
	}*/
}

void OViSEWxFrame::OnDynamicShadowsChange(wxCommandEvent& event)
{
	if(event.IsChecked()) OgreAPIMediator::GetSingletonPtr()->DynamicShadows(true);
	else OgreAPIMediator::GetSingletonPtr()->DynamicShadows(false);
}

void OViSEWxFrame::OnPropertyChange(wxPropertyGridEvent& event)
{
	wxPGProperty *prop = event.GetProperty();
	SelectionManager::getSingletonPtr()->HandlePropertyChanged(prop);
}

void OViSEWxFrame::setObjectProperties(Ogre::MovableObject *object)
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

void OViSEWxFrame::OnMenuDeleteMeshes(wxCommandEvent &event)
{
	deleteMeshes();
}

void OViSEWxFrame::clearObjectProperties()
{
	mObjectProperties->Clear();
}

void OViSEWxFrame::deleteMeshes()
{
	OViSESelectionMap so = OViSESceneHandling::getSingletonPtr()->getSelectedObjects();
	if(so.empty())
	{
		wxMessageDialog dlg(this, wxT("No meshes selected"), wxT("Error"), wxOK | wxCENTRE | wxICON_ERROR);
		dlg.ShowModal();
		return;
	}

	wxMessageDialog confirmationDialog(this, wxT("Delete selected meshes?"), wxT("Confirmation required"), wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION);
	if(confirmationDialog.ShowModal() == wxID_YES)
	{
		for(OViSESelectionMap::iterator it=so.begin(); it != so.end(); it++)
		{
			OViSESceneHandling::getSingletonPtr()->deleteMesh(it->first);
		}
	}
}


void OViSEWxFrame::OnTreeSelectionChanged( wxTreeEvent& event )
{
	wxTreeItemId Item = event.GetItem();

	wxString Msg = ToWxString("SELECTED ITEMS:");

	if (!Item.IsOk()) this->RemoveAllSelectedObjects();
	else
	{
		wxString TreeItemLabel = this->mSceneTree->GetItemText(Item);
		QualifiedName* pqName = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetQualifiedNameOfObject(TreeItemLabel);
		if (pqName != 0)
		{
			if (this->mSceneTree->IsSelected(Item)) this->AddSelectedObject(*pqName);
			else this->RemoveSelectedObject(*pqName);
		}
	}
	Logging::GetSingletonPtr()->WriteToOgreLog(Msg, Logging::Normal);
}

void OViSEWxFrame::AddSelectedObject(QualifiedName qSelectedObject)
{
	Ogre::MovableObject* MO = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(qSelectedObject);
	if (MO != 0)
	{
		if (!QualifiedNameCollectionInterface::CollectionContains(SelectionManager::getSingletonPtr()->Selection, qSelectedObject))
			SelectionManager::getSingletonPtr()->Selection.Add(qSelectedObject);
		MO->getParentSceneNode()->showBoundingBox(true);
		SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection(this->mObjectProperties);
	}
}

void OViSEWxFrame::RemoveSelectedObject(QualifiedName qSelectedObject)
{
	Ogre::MovableObject* MO = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(qSelectedObject);
	if (MO != 0)
	{
		QualifiedNameCollectionInterface::CollectionRemove(SelectionManager::getSingletonPtr()->Selection, qSelectedObject, false);
		MO->getParentSceneNode()->showBoundingBox(false);
		SelectionManager::getSingletonPtr()->GeneratePropertyGridContentFromSelection(this->mObjectProperties);
	}
}

void OViSEWxFrame::RemoveAllSelectedObjects()
{
	// Remove all BoundingBoxes
	if (SelectionManager::getSingletonPtr()->Selection.GetCount() != 0)
	{
		for (unsigned long IT = 0; IT < SelectionManager::getSingletonPtr()->Selection.GetCount(); IT++)
		{
			QualifiedName qMO = SelectionManager::getSingletonPtr()->Selection[IT];
			Ogre::MovableObject* MO = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(qMO);
			if (MO != 0)
			{
				MO->getParentSceneNode()->showBoundingBox(false);
			}
		}
	}

	// Clear selection
	SelectionManager::getSingletonPtr()->Selection.Empty();

	// Clear propertygrid
	this->mObjectProperties->Clear();
}
void OViSEWxFrame::OnOpenPrototypeManagement( wxCommandEvent& event )
{
	PrototypeManagementDialog *PrototypeManagementDlg = new PrototypeManagementDialog(this, this->mDotSceneMgr);
	PrototypeManagementDlg->ShowModal();
	delete PrototypeManagementDlg;
}

void OViSEWxFrame::OnLoadPointCloud(wxCommandEvent& event)
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

		OViSEPointcloud *pc = new OViSEPointcloud(std::string(pcName.mb_str()), "General", counter, pointlist, NULL);

		Ogre::SceneManager *scnMgr = OViSESceneHandling::getSingletonPtr()->getSceneManager();

		Ogre::Entity *pcEnt = scnMgr->createEntity(std::string(pcEntName.mb_str()), std::string(pcName.mb_str()));
		pcEnt->setMaterialName("Pointcloud");
		scnMgr->getRootSceneNode()->attachObject(pcEnt);
	}
}

void OViSEWxFrame::OnShowSceneStructure(wxCommandEvent &event)
{
	bool update = false;
	Ogre::SceneManager* SM = OgreAPIMediator::GetSingletonPtr()->GetSceneManagerPtr(OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager());

	// Let's see if we're already displaying a structure
	if(SM->hasManualObject("SceneGraphStructure"))
	{
		// yes, delete old structure
		SM->destroyManualObject("SceneGraphStructure");
		// kill all object titles
		for(OViSEObjectTitleVector::iterator iter = mObjectTitlesVector.begin(); iter != mObjectTitlesVector.end(); iter++)
			delete *iter;
		mObjectTitlesVector.clear();
		// if we're not requesting an update, return
		if(!update)	return;
	}
	else  // no structure found
	{
		if(update) return;
			// misguided update request, there's nothing to update so don't do anything
	}

	// either we need to update an existing structure or show a new one

	Ogre::ManualObject *sgs = SM->createManualObject("SceneGraphStructure");
	// set flags, so it cannot be selected
	sgs->setQueryFlags(0x01);

	if(!Ogre::MaterialManager::getSingletonPtr()->resourceExists("SceneStructureMaterial"))
	{
		Ogre::MaterialPtr sgsMaterial = Ogre::MaterialManager::getSingleton().create("SceneStructureMaterial", "General");
		sgsMaterial->setReceiveShadows(false);
		sgsMaterial->getTechnique(0)->setLightingEnabled(true);
		sgsMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0);
		sgsMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0);
	}

	Ogre::SceneManager::MovableObjectIterator iter = SM->getMovableObjectIterator("Entity");
	while(iter.hasMoreElements())
	{
		Ogre::MovableObject *mobj = iter.getNext();
		OViSEObjectTitle *tmp = new OViSEObjectTitle(mobj->getName(), mobj, SM->getCurrentViewport()->getCamera(), mobj->getName(), "BlueHighway");
		mObjectTitlesVector.push_back(tmp);
	}

	sgs->begin("SceneStructureMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	std::list<Ogre::Node*> nodeQueue;
	nodeQueue.push_back(SM->getRootSceneNode());
	for(std::list<Ogre::Node*>::iterator it = nodeQueue.begin(); it != nodeQueue.end(); it++)
	{
		if((*it)->getName() == Ogre::String("mainCamFocusNode")) continue;
		Ogre::Node::ChildNodeIterator iter = (*it)->getChildIterator();
		while(iter.hasMoreElements())
		{
			Ogre::Node *tmp = iter.getNext();
			if(tmp->getName() == Ogre::String("mainCamFocusNode")) continue;
			sgs->position((*it)->_getDerivedPosition());
			sgs->position(tmp->_getDerivedPosition());
			nodeQueue.push_back(tmp);
		}
	}
	sgs->end();
	nodeQueue.clear();
	SM->getRootSceneNode()->attachObject(sgs);
}


void OViSEWxFrame::OnTestStuff( wxCommandEvent& event )
{
	this->GetHandle(); // This line is a debug-dummy
}

void OViSEWxFrame::OnStartStopFrameListeners(wxCommandEvent& event)
{
	/*
	if(event.IsChecked())
		mSceneHdlr->startStopFrameListeners(true);
	else
		mSceneHdlr->startStopFrameListeners(false);
		*/
	this->GetHandle(); // This line is a debug-dummy
}