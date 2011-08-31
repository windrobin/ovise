#include "AppContext.h"


CAppContext::CAppContext()
	: mSelection( NULL )
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
