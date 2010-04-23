#pragma once

// Solution's includes
#include "../ImprovedEventHandling/EventListenerInterface.h"
#include "../OgreMediator/OgreMediator.h"

class OgreObjectListener :
	public EventListenerInterface
{
public:
	OgreObjectListener(void);
	~OgreObjectListener(void);

	// Management of listener
	virtual void		StartListening();
	virtual void		StopListening();
	
			void		StartListeningChanged();
			void		StopListeningChanged();

			void		StartListeningConstructed();
			void		StopListeningConstructed();

			void		StartListeningDestructed();
			void		StopListeningDestructed();

			void		StartListeningRenamed();
			void		StopListeningRenamed();

	// Methods of events
	virtual void OnChanged(ImprovedEvent &event);
	virtual void OnConstructed(ImprovedEvent &event);
	virtual void OnDestructed(ImprovedEvent &event);
	virtual void OnRenamed(ImprovedEvent &event);

};
