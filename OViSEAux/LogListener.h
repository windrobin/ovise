#pragma once

// Solution's includes
#include "../ImprovedEventHandling/MovableObjectListener.h"
#include "../ImprovedEventHandling/OgreObjectListener.h"
#include "../ImprovedEventHandling/SceneNodeListener.h"

#include "../OViSEAux/Logging.h"

class LogListener :
	public MovableObjectListener,
	public OgreObjectListener,
	public SceneNodeListener
{
public:
					LogListener(void);
					~LogListener(void);

	// Management of listener
	virtual void	StartListening();
	virtual void	StopListening();

	// Methods of events, inherited
	virtual void	OnChanged(ImprovedEvent &event);
	virtual void	OnConstructed(ImprovedEvent &event);
	virtual void	OnDestructed(ImprovedEvent &event);
	virtual void	OnRenamed(ImprovedEvent &event);

	virtual void	OnSelected(ImprovedEvent &event);
	virtual void	OnUnselected(ImprovedEvent &event);

	virtual void	OnTranslated(ImprovedEvent &event);
	virtual void	OnRotated(ImprovedEvent &event);
	virtual void	OnScaled(ImprovedEvent &event);
};
