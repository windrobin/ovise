#include "OViSELogListener.h"

OViSELogListener::OViSELogListener(void)
{
	mLogBox = NULL;
}

OViSELogListener::OViSELogListener(wxListBox *lBox)
{
	mLogBox = lBox;
}

OViSELogListener::~OViSELogListener(void)
{
}

void OViSELogListener::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel level, bool maskDebug, const Ogre::String& logName)
{
	if(!mLogBox)
		return;

	wxString logLevel, logMessage(message.c_str(), wxConvUTF8);
	wxDateTime now = wxDateTime::Now();
	wxString time = now.Format(wxT("%X"));
	wxString timestr = wxT("(") + time + wxT(")");
	switch(level)
	{
	case Ogre::LML_TRIVIAL:
		{
			logLevel = wxT("TRIVIAL: ");
		} break;
	case Ogre::LML_NORMAL:
		{
			logLevel = wxT("NORMAL: ");
		} break;
	case Ogre::LML_CRITICAL:
		{
			logLevel = wxT("CRITICAL: ");
		} break;
	default: break;
	}
	
	wxString tmp = timestr + logLevel + logMessage;
	
	// Used, when new messages added at first position
	// mLogBox->InsertItems(1, &tmp, 0);

	// Used, when new messages added at los position
	mLogBox->Append(tmp);
	mLogBox->ScrollLines(1); // Scroll (down) to new line, after it is written.
}

