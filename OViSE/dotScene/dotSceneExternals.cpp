#ifndef dotSceneExternals_h_
#define dotSceneExternals_h_
#include "dotSceneExternals.h"
#endif

using namespace dotSceneObjects;

bool dotSceneObjects::dotSceneExternals::addItem(dotSceneItem someItem)
{
	try
	{
		this->items.push_back(someItem);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneExternals::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (!this->items.empty())
	{
		std::list<dotSceneItem>::const_iterator iter = this->items.begin();
		while(iter != this->items.end())
		{
			if (!iter->IsValid()) return false;
			iter++;
		}
		if (!iter->IsValid()) return false;	
	}

	return true;
}

dotSceneObjects::dotSceneExternals::dotSceneExternals() : dotSceneObject(dotSceneEnums::externals) { }
