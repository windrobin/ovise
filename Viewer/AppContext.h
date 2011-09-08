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

	void SetToolmode( const int& Mode ) { mToolmode = Mode; }
	const int& GetToolmode() { return mToolmode; }

	void SetToolaxis( const int& Axis ) { mToolaxis = Axis; }
	const int& GetToolaxis() { return mToolaxis; }
	
	/**
	  Signal selection change.
	  First parameter is the new selection, last parameter is the old selection.
	*/
	boost::signal<void ( Entity*, Entity* )> SelectionChangedSignal;

	boost::signal<void ( float )> DragObjectSignal;

	bool Dragging;
	std::pair<int, int> MousePos;

private:
	Entity* mSelection;

	int		mToolmode;
	int		mToolaxis;
};


#endif // VIEWER_APPCONTEXT_H
