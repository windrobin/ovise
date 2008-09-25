/***************************************************************
 * Name:      OViSEWxApp.cpp
 * Purpose:   Code for Application Class
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

#include "OViSEWxApp.h"
#include "OViSEWxMain.h"

IMPLEMENT_APP(OViSEWxApp);

bool OViSEWxApp::OnInit()
{
	wxImage::AddHandler( new wxPNGHandler );
	wxBitmap bitmap;
	wxSplashScreen *splash = NULL;
	if (bitmap.LoadFile(wxT("../OViSESplash.png"), wxBITMAP_TYPE_PNG))
	{
		splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT, 0, NULL, -1, wxDefaultPosition, 
			wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP);
	}
	Yield(true);

	Ogre::LogManager *logMgr = new Ogre::LogManager;
	Ogre::Log *log = Ogre::LogManager::getSingleton().createLog("OViSE.log", true, true, false);

	mRoot = new Ogre::Root("", "");

	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i=settings->begin(); i!=settings->end(); ++i){
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	try
	{
#ifdef _WIN32
#ifdef _DEBUG
		mRoot->loadPlugin("Plugin_ParticleFX_d");
		mRoot->loadPlugin("Plugin_BSPSceneManager_d");
		mRoot->loadPlugin("Plugin_OctreeSceneManager_d");
		mRoot->loadPlugin("Plugin_CgProgramManager_d");
		mRoot->loadPlugin("RenderSystem_Direct3D9_d");
#else
		mRoot->loadPlugin("RenderSystem_Direct3D9");
		mRoot->loadPlugin("Plugin_ParticleFX");
		mRoot->loadPlugin("Plugin_BSPSceneManager");
		mRoot->loadPlugin("Plugin_OctreeSceneManager");
		mRoot->loadPlugin("Plugin_CgProgramManager");
#endif
#endif
	}
	catch (Ogre::InternalErrorException e)
	{
		std::cerr << e.getFullDescription() << std::endl;
		exit(-1);
	}


	Ogre::RenderSystemList *rsList = mRoot->getAvailableRenderers();
	Ogre::RenderSystemList::iterator it = rsList->begin();
	Ogre::RenderSystem *selectedRenderSystem;
	while(it != rsList->end())
	{
		selectedRenderSystem = *(it++);
		Ogre::String lMsg = "Found rendersystem: " + selectedRenderSystem->getName();
		Ogre::LogManager::getSingletonPtr()->logMessage(lMsg);
#ifdef _WIN32
		if(selectedRenderSystem->getName().find("Direct3D9") != std::string::npos)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("******* Setting Direct3D9 rendersystem. ***********");
#else
		if(selectedRenderSystem->getName().find("GL") != std::string::npos)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("******* Setting OpenGL rendersystem. ***********");
#endif
			mRoot->setRenderSystem(selectedRenderSystem);
			break;
		}
	}
	if(mRoot->getRenderSystem() == NULL)
	{
		delete mRoot;
#ifdef _WIN32
		Ogre::LogManager::getSingletonPtr()->logMessage("Direct3D9 render system not found!");
#else
		Ogre::LogManager::getSingletonPtr()->logMessage("OpenGL render system not found!");
#endif
		return false;
	}

	//we found it, we might as well use it
	selectedRenderSystem->setConfigOption("Full Screen","No");
#ifndef _WIN32
	selectedRenderSystem->setConfigOption("RTT Preferred Mode", "FBO");
#endif
	//selectedRenderSystem->setConfigOption("Video Mode","800 x 600 @ 32-bit colour");

	mRoot->initialise(false);

    OViSEWxFrame* frame = new OViSEWxFrame(0L, mRoot);

    frame->Show();

	splash->Destroy();

    return true;
}

OViSEWxApp::~OViSEWxApp()
{
	delete mRoot;
}
