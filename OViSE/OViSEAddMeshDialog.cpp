#include "OViSEAddMeshDialog.h"

OViSEAddMeshDialog::OViSEAddMeshDialog( wxWindow* parent )
:
AddMeshDialog( parent )
{
	mRenderWin = new wxOgreRenderWindow(this, wxID_ANY);
	mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "AddMesh");
	mSceneHandler = new OViSESceneHandling(mSceneMgr);
	mCam = mSceneMgr->createCamera("AddMeshCam");
	mCam->setNearClipDistance(5);
	mCam->setFarClipDistance(1000);
	mCam->setPosition(20, 5, 0);
	mCam->setDirection(-1, 0, 0);
	mCam->setAutoAspectRatio(true);
	mSceneHandler->addGrid(1, 10, 10, Ogre::Vector3(0.8, 0.8, 0.8));

	mRenderWin->SetCamera(mCam);
	mRenderWin->SetOgreRoot(Ogre::Root::getSingletonPtr());

	mRenderWin->GetRenderWindow()->addViewport(mCam);

	GetSizer()->Insert(0, mRenderWin, 5);

	//updateMeshList();
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
	// TODO: Implement OnMeshListSelect
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
	Destroy();
}

OViSEAddMeshDialog::~OViSEAddMeshDialog()
{
	
	Ogre::Root::getSingletonPtr()->destroySceneManager(mSceneMgr);
	delete mSceneHandler;
}
