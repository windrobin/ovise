#include "Example4_EventListenerPublisher.h"

MyPublishingListener4::MyPublishingListener4(void)
{
	// STEP 1: Use methods of listener
	this->StartListening();

	// STEP 2: Use methods of publisher
	this->Publish(EVT_DEFAULT);
}

MyPublishingListener4::~MyPublishingListener4(void)
{
	this->StopListening();
}
