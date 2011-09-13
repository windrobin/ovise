#include "AppContext.h"
#include "Definitions.h"

CAppContext::CAppContext()
	: mSelection( NULL ), Dragging( false ), MousePos(0,0),
	mToolmode( OVISE::TOOLMODE_NONE ), mToolaxis( OVISE::TOOLAXIS_NONE )
{
}

CAppContext::~CAppContext()
{
	// TODO: save app context to config?
}

void CAppContext::SetSelection( Entity* Ent )
{
	Entity* Old = mSelection;
	mSelection = Ent;
	SelectionChangedSignal( mSelection, Old );
}

void CAppContext::ClearSelection()
{
	Entity* Old = mSelection;
	mSelection = NULL;
	SelectionChangedSignal( NULL, Old );
}
