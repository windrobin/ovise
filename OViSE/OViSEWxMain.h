/***************************************************************
 * Name:      OViSEWxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifndef OVISEWXMAIN_H
#define OVISEWXMAIN_H



#include "OViSEWxApp.h"

#include <wx/splitter.h>

#include "GUIFrame.h"
#include "wxOgreRenderWindow.h"
#include "OViSESceneHandling.h"
#include "OViSELogListener.h"

enum
{
    WINDOW_MainRender = wxID_HIGHEST + 1
};

class OViSEWxFrame: public GUIFrame
{
    public:
		OViSEWxFrame(wxFrame *frame, Ogre::Root *ogreRoot);
        ~OViSEWxFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
		virtual void OnAddView(wxCommandEvent& event);
		virtual void OnSaveScreenToFile(wxCommandEvent& event);
		virtual void OnSceneAddMesh(wxCommandEvent& event);

		void finishOgreInitialization();

    protected:
		Ogre::Root *mRoot;

        wxOgreRenderWindow *mMainRenderWin;

		wxListBox *logBox;
		wxSplitterWindow *mSplitter;

        Ogre::SceneManager *mSceneMgr;
        Ogre::Camera *mCam;

		std::map<std::string, Ogre::Camera*> mAdditionalCameras;
		std::map<std::string, wxFrame*> mViewWindows;

        OViSESceneHandling *mSceneHdlr;

		OViSELogListener *mLogBoxListener;
};

#endif // OVISEWXMAIN_H
