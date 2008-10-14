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
#include <wx/propgrid/propgrid.h>
#include <wx/tokenzr.h>

#include "GUIFrame.h"
#include "wxOgreRenderWindow.h"
#include "OViSESceneHandling.h"
#include "OViSELogListener.h"
#include "OViSEAddMeshDialog.h"

enum
{
    WINDOW_MainRender = wxID_HIGHEST + 1,
	PGID
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
		virtual void OnAdditionalViewClose(wxCloseEvent& event);
		virtual void OnSaveScreenToFile(wxCommandEvent& event);
		virtual void OnSceneAddMesh(wxCommandEvent& event);
		virtual void OnAddMeshDialogClose(wxCloseEvent& event);
		virtual void OnViewClick(wxMouseEvent& event);
		virtual void OnPropertyChange(wxPropertyGridEvent& event);

		void finishOgreInitialization();
		void setupObjectProperties();
		void setObjectProperties(Ogre::MovableObject *object);
		void clearObjectProperties();

	protected:
		DECLARE_EVENT_TABLE()

    protected:
		Ogre::Root *mRoot;

        wxOgreRenderWindow *mMainRenderWin;

		wxListBox *logBox;
		wxSplitterWindow *mSplitter;
		wxSplitterWindow *mSecondSplitter;

		wxPropertyGrid *mObjectProperties;
		
		Ogre::SceneManager *mSceneMgr;
        Ogre::Camera *mCam;

		std::map<std::string, Ogre::Camera*> mAdditionalCameras;
		std::map<std::string, wxFrame*> mViewWindows;

        OViSESceneHandling *mSceneHdlr;

		OViSELogListener *mLogBoxListener;

		OViSEAddMeshDialog *mAddMeshDialog;
};

#endif // OVISEWXMAIN_H
