#include "Messenger.h"

// Event declarations
DECLARE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT, -1)

DEFINE_EVENT_TYPE(wxEVT_SCENE_CHANGED_EVENT)

Messenger::Messenger(void)
{
	evtHandler = new wxEvtHandler();
}

Messenger::~Messenger(void)
{
	delete evtHandler;
}

void Messenger::notifySceneChange()
{
	wxCommandEvent sceneChangedEvent( wxEVT_SCENE_CHANGED_EVENT );
    sceneChangedEvent.SetEventObject( this );
    // Send it
    evtHandler->ProcessEvent( sceneChangedEvent );
}