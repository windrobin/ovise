#include "Example3_EventPublisher.h"

MyExamplePublisher3::MyExamplePublisher3(void)
{
	// STEP 4: Example calls
	// Something has been changed...
	this->Publish(EVT_OGRE_CHANGED); 
	
	// This object has been changed...
	QualifiedName qName;
	this->Publish(EVT_OGRE_CHANGED, qName); 
	
	// Something has been changed to wxVariant (wxString, wxArrayString, ...etc)
	wxVariant vData;
	this->Publish(EVT_OGRE_CHANGED, vData); 

	// This object has been changed to wxVariant (wxString, wxArrayString, ...etc)
	this->Publish(EVT_OGRE_CHANGED, qName, vData); 
}
MyExamplePublisher3::~MyExamplePublisher3(void) { }
