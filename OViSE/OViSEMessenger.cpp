#include "OViSEMessenger.h"

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