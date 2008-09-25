/***************************************************************
 * Name:      OViSEWxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

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

	mSplitter = new wxSplitterWindow(this, wxID_ANY);
    wxOgreRenderWindow::SetOgreRoot(ogreRoot);
	mRoot = ogreRoot;
	mMainRenderWin = new wxOgreRenderWindow(mSplitter, WINDOW_MainRender);
	mMainRenderWin->SetStatusBar(statusBar);
	
    finishOgreInitialization();

	logBox = new wxListBox(mSplitter, wxID_ANY);
	mSplitter->SplitHorizontally(mMainRenderWin, logBox, this->GetSize().GetHeight()*0.85);
	mLogBoxListener = new OViSELogListener(logBox);

	mAddMeshDialog = NULL;

	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(mLogBoxListener);
}

OViSEWxFrame::~OViSEWxFrame()
{
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(mLogBoxListener);
}

void OViSEWxFrame::finishOgreInitialization()
{
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "ExampleSMInstance");

    mCam = mSceneMgr->createCamera("MainCam");

	// Position it at 500 in Z direction
    mCam->setPosition(Ogre::Vector3(0,10,20));
	// Look back along -Z
    mCam->setDirection(Ogre::Vector3(-1, 0, 0));
    mCam->setNearClipDistance(5);

    mCam->setFixedYawAxis(true);

    Ogre::Viewport *mVp = mMainRenderWin->GetRenderWindow()->addViewport(mCam);
	mMainRenderWin->SetCamera(mCam);

    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

    mSceneHdlr = new OViSESceneHandling(mSceneMgr);
	mSceneHdlr->createDefaultScene();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    //mCam->setAspectRatio(Ogre::Real(mVp->getActualWidth()) / Ogre::Real(mVp->getActualHeight()));
	mCam->setAutoAspectRatio(true);
}

void OViSEWxFrame::OnClose(wxCloseEvent &event)
{
	for(std::map<std::string, wxFrame*>::iterator i = mViewWindows.begin(); i != mViewWindows.end(); i++)
	{
		(*i).second->Destroy();
	}
    Destroy();
}

void OViSEWxFrame::OnQuit(wxCommandEvent &event)
{
	for(std::map<std::string, wxFrame*>::iterator i = mViewWindows.begin(); i != mViewWindows.end(); i++)
	{
		(*i).second->Destroy();
	}
    Destroy();
}

void OViSEWxFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
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
	newCam->setPosition(Ogre::Vector3(0,10,20));
	// Look back along -Z
    newCam->setDirection(Ogre::Vector3(-1, 0, 0));
    newCam->setNearClipDistance(5);

	// Need to create a new Frame to display the new renderwindow in
	wxFrame *newFrame = new wxFrame(this, wxID_ANY, wxCamName);
	wxOgreRenderWindow *newRenderWin = new wxOgreRenderWindow(newFrame, wxID_ANY);
	newRenderWin->SetCamera(newCam);
	newRenderWin->SetOgreRoot(mRoot);
	mViewWindows[std::string(wxCamName.ToAscii())] = newFrame;

	newRenderWin->GetRenderWindow()->addViewport(newCam);
	newCam->setAutoAspectRatio(true);

	newFrame->SetSize(50, 50, 640, 480);
	newFrame->Show();
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
	if(mAddMeshDialog == NULL)
	{
		mAddMeshDialog = new OViSEAddMeshDialog(this);
	}
	mAddMeshDialog->Show();
}