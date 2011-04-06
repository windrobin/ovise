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

#include <wx/treebase.h>
#include <wx/imaglist.h>
#include <wx/timer.h>

#include "MainFrameBase.h"
#include "SceneHandling.h"
#include "SceneTree.h"
#include "LogListener.h"
#include "InputHandler.h"
#include "InterfaceManager.h"

#include <boost/scoped_ptr.hpp>

#include <Logging.h>

#include "OgreWindow.h"

#include "AttributeView.h"
#include <SceneView.h>
#include <NetworkInterface.h>

#include <CCSCameraControlSystem.h>
#include <CCSBasicCameraModes.h>
#include <CCSFreeCameraMode.h>
#include <CCSOrbitalCameraMode.h>

using boost::scoped_ptr;

class COViSEFrameListener : public Ogre::FrameListener
{
public:
	COViSEFrameListener( CCS::CameraControlSystem* CCS );

	virtual bool frameEnded (const Ogre::FrameEvent &evt);

private:
	CCS::CameraControlSystem* mCCS;
};

/** Main window of the application.
 * @todo Documentation!
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
	void OnMouseEvent( wxMouseEvent& evt );
	void OnKeyboardEvent( wxKeyEvent& evt );
	void OnViewClick( wxMouseEvent& evt );
	void OnTreeSelectionChanged( wxTreeEvent& event );
	void OnNetworkInterfaceCheck( wxCommandEvent& Event, std::string& Name );
	void OnNetworkTimer( wxTimerEvent& Event );
	void OnIdle( wxIdleEvent& Event );

	void SetupSceneTree();

	bool InitOgre();
	
	EntityPool mEntityPool;

protected:
	void LoadVisPlugins();
	void LoadNWPlugins();
	void LoadVisualizationPlugin( wxString Filename );
	void LoadNetworkPlugin( wxString Filename );

	wxString mMediaPath;
	wxString mPluginPath;

	OgreWindow*           mOgreWindow;
	scoped_ptr<SceneView> mSceneView;

	scoped_ptr<InputHandler> mInputHandler;

	wxListBox*                    mLogBox;
	scoped_ptr<CustomLogListener> mLogBoxListener;

	wxAuiManager mWindowManager;

	SceneTree* mSceneTree;

	scoped_ptr<AttributeView> mAttributeView;
	Entity*                   mCurrentEntity;
	Ogre::Camera*             mCamera;
	scoped_ptr<CCS::CameraControlSystem> mCCS;
	scoped_ptr<CCS::OrbitalCameraMode> mOrbitalCamMode;

	wxTimer mNetworkTimer;

	scoped_ptr<CInterfaceManager> mInterfaceManager;
};

#endif // MAINFRAME_H
