#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"

class SceneNodeListener :
	public OgreObjectListener
{
public:
	SceneNodeListener(void);
	~SceneNodeListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();
	virtual wxString	GetListenerTypeName();

	// Methods of parent events
	virtual void OnSelected(ImprovedEvent &event);
	virtual void OnUnselected(ImprovedEvent &event);

	// Methods of events
	virtual void OnChanged(ImprovedEvent &event);
	virtual void OnConstructed(ImprovedEvent &event);
	virtual void OnDestructed(ImprovedEvent &event);
	virtual void OnRenamed(ImprovedEvent &event);
	virtual void OnMoved(ImprovedEvent &event);
	virtual void OnRotated(ImprovedEvent &event);
	virtual void OnScaled(ImprovedEvent &event);
};
