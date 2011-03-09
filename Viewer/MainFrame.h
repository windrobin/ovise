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
// #include "XMLRPCServer.h"

using boost::scoped_ptr;

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
	virtual void                                    OnQuit(
	        wxCommandEvent& event );
	virtual void                                    OnLoadScene(
	        wxCommandEvent& event );
	virtual void                                    OnLoadPointcloud(
	        wxCommandEvent& event );
	virtual void                                    OnClose(
	        wxCloseEvent& event );
	virtual void                                    OnAbout(
	        wxCommandEvent& event );
	virtual void                                    OnSaveScreenToFile(
	        wxCommandEvent& event );
	virtual void                                    OnShowSceneStructure(
	        wxCommandEvent& event );
	virtual void                                    OnDynamicShadowsChange(
	        wxCommandEvent& event );
	virtual void                                    OnDMPoints(
	        wxCommandEvent &event );
	virtual void                                    OnDMWire(
	        wxCommandEvent &event );
	virtual void                                    OnDMSolid(
	        wxCommandEvent &event );
	virtual void                                    OnTestStuff(
	        wxCommandEvent& event );
	void                                                    OnInsertEntity(
	        wxCommandEvent& Event );
	void                                                    OnRemoveEntity(
	        wxCommandEvent& Event );
	void                                                    OnAddAttribute(
	        wxCommandEvent& Event );
	void
	OnDeleteAttribute( wxCommandEvent& Event );
	void                                                    OnMouseEvent(
	        wxMouseEvent& evt );
	void                                                    OnKeyboardEvent(
	        wxKeyEvent& evt );
	void                                                    OnViewClick(
	        wxMouseEvent& evt );
	void
	OnTreeSelectionChanged( wxTreeEvent& event );
	void                                                    OnIdle(
	        wxIdleEvent& evt );
	void
	OnNetworkInterfaceCheck( wxCommandEvent& Event, std::string& Name );
	void                                                    OnNetworkTimer(
	        wxTimerEvent& Event );
	void                                                    OnRenderTimer(
	        wxTimerEvent& Event );

	void                                                    SetupSceneTree();


	bool                                                    InitOgre();
	EntityPool mEntityPool;

protected:
	void                                                    LoadVisPlugins();
	void                                                    LoadNWPlugins();
	void
	LoadVisualizationPlugin( wxString Filename );
	void
	LoadNetworkPlugin( wxString Filename );

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

	// boost::asio::io_service			mIOService;
	wxTimer mNetworkTimer;
	wxTimer mRenderTimer;

	scoped_ptr<CInterfaceManager> mInterfaceManager;
};

#endif // MAINFRAME_H
