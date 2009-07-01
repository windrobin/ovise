#pragma once

#include <wx/event.h>

// Event declarations
DECLARE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT, -1)

DEFINE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT)

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
