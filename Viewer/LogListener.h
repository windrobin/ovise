#ifndef LOG_LISTENER_H
#define LOG_LISTENER_H

#ifdef __APPLE__
#include <Ogre/OgreLog.h>
#else
#include "OgreLog.h"
#endif
#include <wx/wx.h>
#include <wx/datetime.h>

class CustomLogListener :
	public Ogre::LogListener
{
public:
	CustomLogListener( void );
	CustomLogListener( wxListBox *lBox );
	~CustomLogListener( void );

	void messageLogged( const Ogre::String&   message,
	                    Ogre::LogMessageLevel level,
	                    bool                  maskDebug,
	                    const Ogre::String&   logName );

private:
	wxListBox *mLogBox;
};
#endif // LOG_LISTENER_H
