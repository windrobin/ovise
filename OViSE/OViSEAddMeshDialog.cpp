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
	mCam->setPosition(-20, 0, 0);
	mRenderWin->GetRenderWindow()->addViewport(mCam);
	mSceneHandler->addGrid(1, 10, 10, Ogre::Vector3(0.8, 0.8, 0.8));

	GetSizer()->Insert(0, mRenderWin, 5);

	updateMeshList();
}

void OViSEAddMeshDialog::updateMeshList()
{
	
}

void OViSEAddMeshDialog::OnClose( wxCloseEvent& event )
{
	// TODO: Implement OnClose
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
	// TODO: Implement OnCancelClick
}
