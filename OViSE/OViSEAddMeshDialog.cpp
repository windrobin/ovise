#include "OViSEAddMeshDialog.h"

MeshDialogFrameListener::MeshDialogFrameListener(Ogre::SceneManager *scnMgr)
{
	mSceneManager = scnMgr;
}

MeshDialogFrameListener::~MeshDialogFrameListener()
{
}

bool MeshDialogFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	try
	{
		Ogre::SceneNode *tmp = mSceneManager->getSceneNode("MeshNode");
		tmp->yaw(Ogre::Radian(Ogre::Degree(0.1)));
	}
	catch(...) { }
	return true;
}

bool MeshDialogFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}

OViSEAddMeshDialog::OViSEAddMeshDialog( wxWindow* parent, wxWindowID id )
:
AddMeshDialog( parent, id )
{
	mRenderWin = new wxOgreRenderWindow(this, wxID_ANY);
	mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "AddMesh");
	mSceneMgr->setNormaliseNormalsOnScale(true);

	mListener = new MeshDialogFrameListener(mSceneMgr);
	Ogre::Root::getSingletonPtr()->addFrameListener(mListener);

	mSceneHandler = new OViSESceneHandling(mSceneMgr);
	mCam = mSceneMgr->createCamera("AddMeshCam");
	mCam->setNearClipDistance(1);
	mCam->setFarClipDistance(1000);
	mCam->setPosition(-20, 5, 0);
	mCam->lookAt(0, 0, 0);
	mCam->setAutoAspectRatio(true);
	mCam->setFixedYawAxis(true);

	mMeshNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MeshNode");
	
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	mLight = mSceneMgr->createLight("AddMeshLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setPosition(-20, 0, 0);
	mLight->setDirection(1, -1, 0);

	mSceneHandler->addGrid(1, 10, 10, Ogre::Vector3(1, 1, 1));

	mRenderWin->SetCamera(mCam);
	mRenderWin->SetOgreRoot(Ogre::Root::getSingletonPtr());

	Ogre::Viewport *vP = mRenderWin->GetRenderWindow()->addViewport(mCam);
	vP->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));

	wxSizerItem *listSizerItem = GetSizer()->GetItem((size_t)0);
	if(listSizerItem->IsSizer())
		listSizerItem->GetSizer()->Insert(0, mRenderWin, 4, wxEXPAND);

	SetAffirmativeId(mOkButton->GetId());
	SetEscapeId(mCancelButton->GetId());

	updateMeshList();
}

void OViSEAddMeshDialog::updateMeshList()
{
	std::vector<std::string> groups = OViSESceneHandling::getAvailableResourceGroupNames();
	for(std::vector<std::string>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		try
		{
			std::vector<std::string> meshlist = OViSESceneHandling::getAvailableMeshes(*it);
			for(std::vector<std::string>::iterator iter = meshlist.begin(); iter != meshlist.end(); iter++)
			{
				if((*iter).rfind(".mesh") == (*iter).length() - 5)
					mMeshList->Insert(wxString(iter->c_str(), wxConvUTF8), 0);
			}
		}
		catch (std::exception e)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
		}
	}
}

void OViSEAddMeshDialog::OnClose( wxCloseEvent& event )
{
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
	mMeshNode->setPosition(0, 0, 0);
	mCam->setPosition(-20, 5, 0);
	mCam->lookAt(0, 0, 0);
	Ogre::Entity *ent = mSceneMgr->createEntity("tmp", meshToLoad);
	mMeshNode->attachObject(ent);
	Ogre::Vector3 centering = ent->getBoundingBox().getCenter() - mMeshNode->getPosition();
	mMeshNode->translate(-centering, Ogre::Node::TS_WORLD);

	// Move camera so whole object is displayed
	double angle = mCam->getFOVy().valueRadians()/2;
	double dist = ent->getBoundingBox().getSize().length()* 2 * cos(angle);
	if(dist < 1.0)
		dist = 1.0;
	Ogre::Vector3 tmp = mCam->getPosition() - ent->getBoundingBox().getCenter();
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
	try
	{
		Ogre::SceneManager *baseScnMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");
		wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
		Ogre::SceneNode *addNode = baseScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(tmp.ToAscii()));
		Ogre::String entName = Ogre::String(tmp.ToAscii()) + "Entity";
		Ogre::Entity *addEnt = baseScnMgr->createEntity(entName, Ogre::String(lastSelected.ToAscii()));
		addNode->attachObject(addEnt);
		Close();
	}
	catch(Ogre::Exception e) { }
}

void OViSEAddMeshDialog::OnApplyClick( wxCommandEvent& event )
{
	// Add selected mesh to the base scene and continue the dialog
	try
	{
		Ogre::SceneManager *baseScnMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainSceneManager");
		wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
		Ogre::SceneNode *addNode = baseScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(tmp.ToAscii()));
		Ogre::String entName = Ogre::String(tmp.ToAscii()) + "Entity";
		Ogre::Entity *addEnt = baseScnMgr->createEntity(entName, Ogre::String(lastSelected.ToAscii()));
		addNode->attachObject(addEnt);
	}
	catch(Ogre::Exception e) { }
}

void OViSEAddMeshDialog::OnCancelClick( wxCommandEvent& event )
{
	Close();
}

OViSEAddMeshDialog::~OViSEAddMeshDialog()
{
	Ogre::Root::getSingletonPtr()->removeFrameListener(mListener);
	delete mListener;
	Ogre::Root::getSingletonPtr()->destroySceneManager(mSceneMgr);
	delete mSceneHandler;
}
