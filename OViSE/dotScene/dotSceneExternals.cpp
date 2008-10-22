#ifndef dotSceneExternals_h_
#define dotSceneExternals_h_
#include "dotSceneExternals.h"
#endif

using namespace dotSceneObjects;

bool dotSceneObjects::dotSceneExternals::addItem(dotSceneItem item)
{
	try
	{
		this->items.push_back(item);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

dotSceneObjects::dotSceneExternals::dotSceneExternals() : dotSceneObject(externals) { }
