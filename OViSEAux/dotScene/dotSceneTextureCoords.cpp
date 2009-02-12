#ifndef dotSceneTextureCoords_h_
#define dotSceneTextureCoords_h_
#include "dotSceneTextureCoords.h"
#endif

bool dotSceneObjects::dotSceneTextureCoords::IsValid() const
{
	// basics valid?
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	// child-nodes valid?
	if (!this->listOfFloatRect.empty())
	{
		std::list<dotSceneFloatRect>::const_iterator iter = this->listOfFloatRect.begin();
		while(iter != this->listOfFloatRect.end())
		{
			if (!iter->IsValid()) return false;
			iter++;
		}
		if (!iter->IsValid()) return false;
	}

	return true;
}

bool dotSceneObjects::dotSceneTextureCoords::addFloatRect(dotSceneFloatRect someFloatRect)
{
    try
    {
		this->listOfFloatRect.push_back(someFloatRect);
        return true;
    }
	catch (std::exception ex) { }
    return false;
}

dotSceneObjects::dotSceneTextureCoords::dotSceneTextureCoords() : dotSceneObject(dotSceneEnums::textureCoords)
{
	this->listOfFloatRect = std::list<dotSceneFloatRect>();
}
