#pragma once

#include <wx/event.h>

/** Class that mediates messages between the Ogre scene and wx.
 *  If anything happens in the Ogre scene tree that the GUI should be notified of, this class can
 *  be used to generate an apropriate wxEvent which is then propagated to all wxWidgets using
 *  the wx event handling.
 */
class OViSEMessenger : public wxObject
{
public:
	OViSEMessenger(void);
	~OViSEMessenger(void);

	void notifySceneChange();

private:
	wxEvtHandler *evtHandler;
};
