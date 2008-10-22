#ifndef dotSceneNodes_h_
#define dotSceneNodes_h_
#include "dotSceneNodes.h"
#endif

bool dotSceneObjects::dotSceneNodes::addItem(dotSceneNode node)
{
    try
    {
		this->listOfNodes.push_back(node);
        return true;
    }
	catch (std::exception ex) { }
    return false;
}

dotSceneObjects::dotSceneNodes::dotSceneNodes() : dotSceneObject(nodes) { }
