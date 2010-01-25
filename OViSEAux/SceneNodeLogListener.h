#pragma once

// Solution's includes
#include "../ImprovedEventHandling/SceneNodeListener.h"
#include "../OViSEAux/Logging.h"

class SceneNodeLogListener :
	public SceneNodeListener
{
public:
	SceneNodeLogListener(void);
	~SceneNodeLogListener(void);

	// Management of listener, sealed
	wxString GetListenerTypeName();

	// Methods of parent events, sealed
	void OnChanged(ImprovedEvent &event);
	void OnConstructed(ImprovedEvent &event);
	void OnDestructed(ImprovedEvent &event);
	void OnRenamed(ImprovedEvent &event);
	void OnSelected(ImprovedEvent &event);
	void OnUnselected(ImprovedEvent &event);
};
