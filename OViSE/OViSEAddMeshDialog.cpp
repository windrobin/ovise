#include "OViSEAddMeshDialog.h"

OViSEAddMeshDialog::OViSEAddMeshDialog( wxWindow* parent, wxWindowID id )
:
AddMeshDialog( parent, id )
{
	mRenderWin = new wxOgreRenderWindow(this, wxID_ANY);
	mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "AddMesh");
	mSceneMgr->setNormaliseNormalsOnScale(true);
	mSceneHandler = new OViSESceneHandling(mSceneMgr);
	mCam = mSceneMgr->createCamera("AddMeshCam");
	mCam->setNearClipDistance(5);
	mCam->setFarClipDistance(1000);
	mCam->setPosition(20, 5, 0);
	mCam->setDirection(-1, 0, 0);
	mCam->setAutoAspectRatio(true);
	mCam->setFixedYawAxis(true);

	mMeshNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	mLight = mSceneMgr->createLight("AddMeshLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setPosition(-20, 0, 0);
	mLight->setDirection(1, 1, 0);

	mSceneHandler->addGrid(1, 10, 10, Ogre::Vector3(0.8, 0.8, 0.8));

	mRenderWin->SetCamera(mCam);
	mRenderWin->SetOgreRoot(Ogre::Root::getSingletonPtr());

	mRenderWin->GetRenderWindow()->addViewport(mCam);

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
	Ogre::Entity *ent = mSceneMgr->createEntity("tmp", meshToLoad);
	mMeshNode->attachObject(ent);

	// TODO: Move camera so whole object is displayed
	Ogre::AxisAlignedBox bbox = ent->getBoundingBox();
	Ogre::Real disty = bbox.getMaximum().y - bbox.getMinimum().y;
	Ogre::Real scaleFactor = 10/disty;
	mMeshNode->scale(scaleFactor, scaleFactor, scaleFactor);
	mMeshNode->translate(-bbox.getCenter());
	lastSelected = selected;
}

void OViSEAddMeshDialog::OnOkClick( wxCommandEvent& event )
{
	// TODO: Implement OnOkClick
}

void OViSEAddMeshDialog::OnApplyClick( wxCommandEvent& event )
{
	// TODO: Implement OnApplyClick
}

void OViSEAddMeshDialog::OnCancelClick( wxCommandEvent& event )
{
	Close();
}

OViSEAddMeshDialog::~OViSEAddMeshDialog()
{
	Ogre::Root::getSingletonPtr()->destroySceneManager(mSceneMgr);
	delete mSceneHandler;
}
