#ifndef dotSceneSpecific_h_
#define dotSceneSpecific_h_
#include "dotSceneSpecific.h"
#endif

bool dotSceneObjects::dotSceneSpecific::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}
dotSceneObjects::dotSceneSpecific::dotSceneSpecific() : dotSceneObject(dotSceneEnums::INVALID) { }
dotSceneObjects::dotSceneSpecific::dotSceneSpecific(dotSceneEnums::dotSceneElementTags incomingTag) : dotSceneObject(incomingTag) { }


