#pragma once

#ifdef __APPLE__
#include <Ogre/OgreLog.h>
#else
#include "OgreLog.h"
#endif
#include <wx/wx.h>
#include <wx/datetime.h>

class OViSELogListener :
	public Ogre::LogListener
{
public:
	OViSELogListener(void);
	OViSELogListener(wxListBox *lBox);
	~OViSELogListener(void);

	void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel level, bool maskDebug, const Ogre::String& logName);

private:
	wxListBox *mLogBox;
};
