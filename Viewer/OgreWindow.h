
#ifndef OGRE_WINDOW_H
#define OGRE_WINDOW_H

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <wx/config.h>
#include <wx/window.h>
#include <OgrePrerequisites.h>


class OgreWindow :
	public wxWindow,
	public boost::noncopyable
{
public:
	OgreWindow( const wxString& MediaPath, wxWindow* Parent, wxWindowID id,
	            const wxPoint& pos,
	            const wxSize& size,
	            long style,
	            const wxString& name );

	~OgreWindow();

	void                                                    SetGraphicsInit(
	        boost::function<void()> Func ) {
		mInitFunc = Func;
	}

	Ogre::SceneManager*                             GetSceneManager() {
		return mSceneMgr;
	}
	Ogre::RenderWindow*                             GetRenderWindow() {
		return mRenderWindow;
	}
	Ogre::Root*                                             GetRoot() {
		return mRoot.get();
	}

	void UpdateOgre();

private:
	void OnResize( wxSizeEvent& Event );
	void OnPaint( wxPaintEvent& Event );
	void OnCreate( wxWindowCreateEvent& Event );

	void LoadResources();

	wxString mMediaDir;

	boost::scoped_ptr<Ogre::Root> mRoot;
	Ogre::RenderWindow*           mRenderWindow;
	Ogre::SceneManager*           mSceneMgr;

	boost::function<void()> mInitFunc;

	bool mContextCreated;

	DECLARE_EVENT_TABLE()
};

#endif // OGRE_WINDOW_H
