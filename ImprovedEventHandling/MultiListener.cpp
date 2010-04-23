#include "MultiListener.h"

MultiListener::MultiListener(void) { EventListenerInterface::SetListenerTypeName(ToWxString("MultiListener")); }
MultiListener::~MultiListener(void) { }
void MultiListener::StartListening()
{
	// Start listening events
	// 1st way to start
	OgreObjectListener::StartListening();
	MovableObjectListener::StartListening();
	SceneNodeListener::StartListening();

	// 2nd way to start
	/*
	this->StartListeningChanged();
	this->StartListeningConstructed();
	this->StartListeningDestructed();
	this->StartListeningRenamed();

	this->StartListeningSelected();
	this->StartListeningUnselected();
	
	this->StartListeningRotated();
	this->StartListeningScaled();
	this->StartListeningTranslated();
	*/
}
void MultiListener::StopListening()
{
	// Stop listening events
	// 1st way to stop
	OgreObjectListener::StopListening();
	MovableObjectListener::StopListening();
	SceneNodeListener::StopListening();

	// 2nd way to stop
	/*
	this->StopListeningChanged();
	this->StopListeningConstructed();
	this->StopListeningDestructed();
	this->StopListeningRenamed();

	this->StopListeningSelected();
	this->StopListeningUnselected();

	this->StopListeningRotated();
	this->StopListeningScaled();
	this->StopListeningTranslated();
	*/
}