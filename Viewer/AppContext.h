#ifndef VIEWER_APPCONTEXT_H
#define VIEWER_APPCONTEXT_H

#include <Entity.h>
#include <Singleton.hpp>

#include <boost/signals.hpp>

class CAppContext : public Singleton<CAppContext>
{
public:
	CAppContext();
	~CAppContext();

	/// Set selected entity (single selection only for now)
	void SetSelection( Entity* Ent );
	void ClearSelection();
	Entity* GetSelected() { return mSelection; }
	bool HasSelection() { return mSelection != NULL; }
	
	/**
	  Signal selection change.
	  First parameter is the new selection, last parameter is the old selection.
	*/
	boost::signal<void ( Entity*, Entity* )> SelectionChangedSignal;

private:
	Entity* mSelection;
};


#endif // VIEWER_APPCONTEXT_H
