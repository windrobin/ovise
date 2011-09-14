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

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include <wx/aui/aui.h>
#include <wx/propgrid/propgrid.h>
#include <wx/tokenzr.h>
#include <wx/aboutdlg.h>
#include <wx/treectrl.h>
#include <wx/toolbar.h>

#include <wx/treebase.h>
#include <wx/imaglist.h>
#include <wx/timer.h>

#include <boost/scoped_ptr.hpp>

#include "MainFrameBase.h"
#include "SceneHandling.h"
#include "SceneTree.h"
#include "LogListener.h"
#include "InputHandler.h"
#include "AppContext.h"
#include "AttributeView.h"
#include "OgreWindow.h"
#include "PluginManager.h"

#include <Logging.h>
#include <SceneView.h>
#include <NetworkInterface.h>
#include <InterfaceManager.h>
#include <SelectionBox.h>

#include <CCSCameraControlSystem.h>
#include <CCSBasicCameraModes.h>
#include <CCSFreeCameraMode.h>
#include <CCSOrbitalCameraMode.h>

using boost::scoped_ptr;

/**
  Small frame listener needed for the camera control system.
  Updates the position and orientation of the camera at the end of
  each frame as is required by the CCS.
*/
class COViSEFrameListener : public Ogre::FrameListener
{
public:
	COViSEFrameListener( CCS::CameraControlSystem* CCS, CSelectionBox* SelBox );

	virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameEnded (const Ogre::FrameEvent &evt);

private:
	CCS::CameraControlSystem* mCCS;
	CSelectionBox*            mSelectionBox;
	Ogre::Entity*             mCurrentSelection;
};

/** 
  Main window of the application.
  Implements the main frame of the viewer. Derived fromt the class created
  by wxFormBuilder. 
*/
class MainFrame :
	public MainFrameBase
{
public:
	explicit MainFrame( wxString  MediaDir,
	                    wxString  PluginDir,
	                    wxWindow* Parent );
	~MainFrame();
	void
	SetStatusMessage( wxString& Msg, int field = 0 );


private:
	void OnQuit( wxCommandEvent& event );

	void OnLoadScene( wxCommandEvent& event );
	void OnLoadPointcloud( wxCommandEvent& event );

	void OnClose( wxCloseEvent& event );

	void OnAbout( wxCommandEvent& event );
	void OnPluginsSummary( wxCommandEvent& event );

	void OnSaveScreenToFile( wxCommandEvent& event );
	
	void OnShowSceneStructure( wxCommandEvent& event );
	void OnDynamicShadowsChange( wxCommandEvent& event );
	void OnDMPoints( wxCommandEvent &event );
	void OnDMWire( wxCommandEvent &event );
	void OnDMSolid( wxCommandEvent &event );
	
	void OnTestStuff( wxCommandEvent& event );
	
	void OnInsertEntity( wxCommandEvent& Event );
	void OnRemoveEntity( wxCommandEvent& Event );
	void OnAddAttribute( wxCommandEvent& Event );
	void OnDeleteAttribute( wxCommandEvent& Event );

	void OnMoveToolClick( wxCommandEvent& evt );
	void OnScaleToolClick( wxCommandEvent& evt );
	void OnRotateToolClick( wxCommandEvent& evt );
	
	void OnMouseEvent( wxMouseEvent& evt );
	void OnKeyboardEvent( wxKeyEvent& evt );
	void OnViewClick( wxMouseEvent& evt );
	void OnTreeSelectionChanged( wxTreeEvent& event );
	
	void OnNetworkInterfaceCheck( wxCommandEvent& Event, std::string& Name );
	void OnNetworkTimer( wxTimerEvent& Event );
	
	void OnIdle( wxIdleEvent& Event );

	void OnSelectionChange( Entity* NewSel, Entity* OldSel );
	void OnDragObject( float Delta );

	void SetupSceneTree();

	bool InitOgre();
	
	EntityPool mEntityPool;

protected:
	wxString                             mMediaPath;
	wxString                             mPluginPath;

	wxAuiToolBar*                           mMainToolBar;

	OgreWindow*                          mOgreWindow;
	scoped_ptr<SceneView>                mSceneView;

	scoped_ptr<InputHandler>             mInputHandler;

	wxListBox*                           mLogBox;
	scoped_ptr<CustomLogListener>        mLogBoxListener;

	wxAuiManager                         mWindowManager;

	SceneTree*                           mSceneTree;

	scoped_ptr<AttributeView>            mAttributeView;
	
	Ogre::Camera*                        mCamera;
	scoped_ptr<CCS::CameraControlSystem> mCCS;
	scoped_ptr<CCS::OrbitalCameraMode>   mOrbitalCamMode;

	scoped_ptr<CSelectionBox>            mSelectionBox;

	scoped_ptr<Ogre::RaySceneQuery>      mRaySceneQuery;

	wxTimer                              mNetworkTimer;

	scoped_ptr<CPluginManager>           mPluginManager;
};

#endif // MAINFRAME_H
