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

//----------------------------------------------------------------------

OViSEAddMeshDialog::OViSEAddMeshDialog( wxWindow* parent, wxWindowID id )
:
AddMeshDialog( parent, id )
{
	mRenderWin = new wxOgreRenderWindow(NULL, NULL, this, wxID_ANY);
	mSceneHandler = OViSESceneHandling::getSingletonPtr();
	mSceneHandler->addSceneManager("AddMeshScene");
	Ogre::SceneManager *scnMgr = mSceneHandler->getSceneManager("AddMeshScene");
	scnMgr->setNormaliseNormalsOnScale(true);

	mListener = new MeshDialogFrameListener(scnMgr);
	Ogre::Root::getSingletonPtr()->addFrameListener(mListener);

	mCam = scnMgr->createCamera("AddMeshCam");
	mCam->setNearClipDistance(1);
	mCam->setFarClipDistance(1000);
	mCam->setPosition(-20, 5, 0);
	mCam->lookAt(0, 0, 0);
	mCam->setAutoAspectRatio(true);
	mCam->setFixedYawAxis(true);

	mMeshNode = scnMgr->getRootSceneNode()->createChildSceneNode("MeshNode");
	
	scnMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	mLight = scnMgr->createLight("AddMeshLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setPosition(-20, 0, 0);
	mLight->setDirection(1, -1, 0);

	mSceneHandler->addGrid(1, 10, 10, Ogre::Vector3(1, 1, 1), "AddMeshScene");

	mRenderWin->SetCamera(mCam);
	mRenderWin->SetOgreRoot(Ogre::Root::getSingletonPtr());

	Ogre::Viewport *vP = mRenderWin->GetRenderWindow()->addViewport(mCam);
	vP->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));

	wxSizerItem *listSizerItem = GetSizer()->GetItem((size_t)0);
	if(listSizerItem->IsSizer())
		listSizerItem->GetSizer()->Insert(0, mRenderWin, 4, wxEXPAND);

	//SetAffirmativeId(mOkButton->GetId());
	//SetEscapeId(mCancelButton->GetId());

	updateMeshList();
}

void OViSEAddMeshDialog::updateMeshList()
{
	std::vector<std::string> groups = mSceneHandler->getAvailableResourceGroupNames();
	for(std::vector<std::string>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		try
		{
			std::vector<std::string> meshlist = mSceneHandler->getAvailableMeshes(*it);
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

void OViSEAddMeshDialog::OnCloseDialog( wxCloseEvent& event )
{
	Ogre::Root::getSingletonPtr()->removeFrameListener(mListener);
	delete mListener;
	mSceneHandler->removeSceneManager("AddMeshScene");
	Destroy();
}

void OViSEAddMeshDialog::OnMeshListSelect( wxCommandEvent& event )
{
	wxString selected = mMeshList->GetStringSelection();
	if(selected.IsEmpty())
		return;
	if(selected.Cmp(lastSelected) == 0)
		return;
	Ogre::SceneManager *scnMgr = mSceneHandler->getSceneManager("AddMeshScene");
	Ogre::String meshToLoad(selected.ToAscii());
	if(scnMgr->hasEntity("tmp"))
	{
		mMeshNode->removeAllChildren();
		scnMgr->destroyEntity("tmp");
	}
	mMeshNode->setPosition(0, 0, 0);
	mCam->setPosition(-20, 5, 0);
	mCam->lookAt(0, 0, 0);
	Ogre::Entity *ent = scnMgr->createEntity("tmp", meshToLoad);
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
		Ogre::SceneManager *baseScnMgr = mSceneHandler->getSceneManager();
		wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
		mSceneHandler->addMesh(std::string(tmp.ToAscii()), std::string(lastSelected.ToAscii()));
		this->Close();
	}
	catch(Ogre::Exception e) { }
}

void OViSEAddMeshDialog::OnApplyClick( wxCommandEvent& event )
{
	// Add selected mesh to the base scene and continue the dialog
	try
	{
		Ogre::SceneManager *baseScnMgr = Ogre::Root::getSingletonPtr()->getSceneManager("BaseSceneManager");
		wxString tmp = lastSelected.substr(0, lastSelected.Length() - 5);
		mSceneHandler->addMesh(std::string(tmp.ToAscii()), std::string(lastSelected.ToAscii()));
	}
	catch(Ogre::Exception e) { }
}

void OViSEAddMeshDialog::OnCancelClick( wxCommandEvent& event )
{
	Close();
}

OViSEAddMeshDialog::~OViSEAddMeshDialog()
{
	
}
