#pragma once

// Solution's includes
#include "../ImprovedEventHandling/EventListenerInterface.h"

class MovableObjectListener :
	public EventListenerInterface
{
public:
						MovableObjectListener(void);
						~MovableObjectListener(void);
	
	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();
	
			void		StartListeningSelected();
			void		StopListeningSelected();

			void		StartListeningUnselected();
			void		StopListeningUnselected();

	// Methods of events
	virtual void OnSelected(ImprovedEvent &event);
	virtual void OnUnselected(ImprovedEvent &event);
};
