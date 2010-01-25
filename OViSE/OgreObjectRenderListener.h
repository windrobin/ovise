#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"
#include "../OgreMediator/OgreMediator.h"

class OgreObjectRenderListener :
	public OgreObjectListener
{
public:
	OgreObjectRenderListener(void);
	~OgreObjectRenderListener(void);

	// Management of listener, sealed
	void StartListening();
	wxString GetListenerTypeName();

	// Methods of parent events, sealed
	void OnChanged(ImprovedEvent &event);
	void OnConstructed(ImprovedEvent &event);
	void OnDestructed(ImprovedEvent &event);
	void OnRenamed(ImprovedEvent &event);
	void OnSelected(ImprovedEvent &event);
	void OnUnselected(ImprovedEvent &event);
};