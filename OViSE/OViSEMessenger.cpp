#include "OViSEMessenger.h"

// Event declarations
DECLARE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT, -1)

DEFINE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT)

OViSEMessenger::OViSEMessenger(void)
{
	evtHandler = new wxEvtHandler();
}

OViSEMessenger::~OViSEMessenger(void)
{
	delete evtHandler;
}

void OViSEMessenger::notifySceneChange()
{
	wxCommandEvent sceneChangedEvent( wxEVT_SCENE_CHANGED_EVENT );
    sceneChangedEvent.SetEventObject( this );
    // Send it
    evtHandler->ProcessEvent( sceneChangedEvent );
}