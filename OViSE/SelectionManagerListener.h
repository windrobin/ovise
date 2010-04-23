#pragma once

// Solution's includes
#include "../ImprovedEventHandling/MovableObjectListener.h"
#include "../ImprovedEventHandling/OgreObjectListener.h"
#include "../ImprovedEventHandling/SceneNodeListener.h"
#include "../OViSE/SelectionManager.h"

#include "../OViSE/InputSourceInterface.h"

class SelectionManagerListener :
	public MovableObjectListener,
	public OgreObjectListener,
	public SceneNodeListener
{
public:
			SelectionManagerListener(void);
			~SelectionManagerListener(void);

	// Management of listener, sealed
	void	StartListening();
	void	StopListening();

	// Methods of parent events, sealed
	void	OnChanged(ImprovedEvent &event);
	void	OnConstructed(ImprovedEvent &event);
	void	OnDestructed(ImprovedEvent &event);
	void	OnRenamed(ImprovedEvent &event);

	void	OnSelected(ImprovedEvent &event);
	void	OnUnselected(ImprovedEvent &event);

	void	OnTranslated(ImprovedEvent &event);
	void	OnRotated(ImprovedEvent &event);
	void	OnScaled(ImprovedEvent &event);
};