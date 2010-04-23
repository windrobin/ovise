#pragma once

// Solution's includes
#include "../ImprovedEventHandling/EventListenerInterface.h"

class SceneNodeListener :
	public EventListenerInterface
{
public:
						SceneNodeListener(void);
						~SceneNodeListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();

			void		StartListeningTranslated();
			void		StopListeningTranslated();

			void		StartListeningRotated();
			void		StopListeningRotated();

			void		StartListeningScaled();
			void		StopListeningScaled();

	// Methods of events
	virtual void OnTranslated(ImprovedEvent &event);
	virtual void OnRotated(ImprovedEvent &event);
	virtual void OnScaled(ImprovedEvent &event);
};
