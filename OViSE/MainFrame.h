/***************************************************************
 * Name:      MainFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/aui/aui.h>
#include <wx/propgrid/propgrid.h>
#include <wx/tokenzr.h>
#include <wx/aboutdlg.h>
#include <wx/treectrl.h>

#include <wx/treebase.h>

#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/imaglist.h>

#include "MainFrameBase.h"
#include "SceneHandling.h"
#include "LogListener.h"
#include "SceneTree.h"
#include "InputHandler.h"

#include "../QualifiedNames/QualifiedName.h"
#include "../QualifiedNames/QualifiedNameCollection.h"
#include "../OViSEAux/OgreAPIMediator.h"
#include "../OViSE/SelectionManager.h"
#include "../OViSEAux/MovableTypeTranslator.h"
#include "../OViSEAux/Logging.h"

//#include "AddMeshDialog.h"
#include "ExportMeshesDialog.h"
#include "PrototypeManagementDialog.h"

enum
{
    WINDOW_MainRender = wxID_HIGHEST + 1,
	PGID,
	SCENETREE
};

/** Mainwindow of the application.
 * @todo Documentation!
 */
class MainFrame: public MainFrameBase
{
    public:
		MainFrame(wxWindow* parent);
        ~MainFrame();

		bool InitOgre();

    private:
        virtual void OnQuit(wxCommandEvent& event);
		virtual void OnClose( wxCloseEvent& event );
        virtual void OnAbout(wxCommandEvent& event);
		virtual void OnSaveScreenToFile(wxCommandEvent& event);
		virtual void OnSceneAddMesh(wxCommandEvent& event);
		virtual void OnAddMeshDialogClose(wxCloseEvent& event);
		virtual void OnPropertyChange(wxPropertyGridEvent& event);
		virtual void OnMenuDeleteMeshes( wxCommandEvent& event );
		virtual void OnOpenPrototypeManagement( wxCommandEvent& event );
		virtual void OnLoadPointCloud( wxCommandEvent& event );
		virtual void OnShowSceneStructure( wxCommandEvent& event);
		virtual void OnDynamicShadowsChange(wxCommandEvent& event);
		virtual void OnTestStuff( wxCommandEvent& event );

		void OnMouseEvent( wxMouseEvent& evt );
		void OnKeyboardEvent( wxKeyEvent& evt );
		void OnViewClick( wxMouseEvent& evt );
		
		void setObjectProperties(Ogre::MovableObject *object);
		void clearObjectProperties();
		void deleteMeshes();

		void OnTreeSelectionChanged( wxTreeEvent& event );

		void AddSelectedObject(QualifiedName qSelectedObject);
		void RemoveSelectedObject(QualifiedName qSelectedObject);
		void RemoveAllSelectedObjects();

		void OnIdle( wxIdleEvent& evt );
		void OnRenderWindowResize(wxSizeEvent& evt);
		void UpdateRenderWindow();

		Ogre::String GetOgreHandle();

		// NEW // DotSceneManager
		/// Standard factory for dotScene loading
		OViSEDotSceneManager *mDotSceneMgr;

    protected:
		void setupObjectProperties();

		void loadSceneTreeImageList(wxImageList *list);

        wxWindow* mMainRenderWin;
		Ogre::RenderWindow* mRenderWin;
		InputHandler* mInputHandler;
		
		wxListBox* mLogBox;
		CustomLogListener *mLogBoxListener;
		
		wxAuiManager mWindowManager;

		SceneTree* mSceneTree;

		wxPropertyGrid* mObjectProperties;
		
		Ogre::Root* mRoot;
		Ogre::SceneManager* mSceneMgr;
        Ogre::Camera* mCam;

		bool mOgreInitialized;

		//OViSEAddMeshDialog *mAddMeshDialog;
};

#endif // MAINFRAME_H
