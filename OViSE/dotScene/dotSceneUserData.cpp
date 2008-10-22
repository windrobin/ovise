#ifndef dotSceneUserData_h_
#define dotSceneUserData_h_
#include "dotSceneUserData.h"
#endif

void dotSceneObjects::dotSceneUserData::addProperty(dotSceneProperty Property) 
{
	this->properties.push_back(Property);
}

dotSceneObjects::dotSceneUserData::dotSceneUserData() : dotSceneObject(userDataReference) { }

