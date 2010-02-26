#include "SceneHandling.h"

std::vector<std::string> SceneHandling::getAvailableMeshes(std::string group)
{
	Ogre::StringVectorPtr resources = Ogre::ResourceGroupManager::getSingletonPtr()->listResourceNames(group);
	if(resources->size() == 0)
		throw OViSEException("Resource group not found!");
	std::vector<std::string> returnvec;
	for(Ogre::StringVector::iterator it = resources->begin(); it != resources->end(); it++)
		returnvec.push_back(*it);
	return returnvec;
}

//ID#0002//
std::vector<std::string> SceneHandling::getAvailableResourceGroupNames()
{
	return Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
}
