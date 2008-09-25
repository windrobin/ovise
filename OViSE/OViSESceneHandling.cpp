#include "OViSESceneHandling.h"

OViSESceneHandling::OViSESceneHandling(Ogre::SceneManager *scnMgr)
{
	mScnMgr = scnMgr;
}

void OViSESceneHandling::createDefaultScene()
{
	// Create default grid
	Ogre::Vector3 gridColor(0.6,0.6,0.6);
	addGrid(1, 100, 100, gridColor);
	addCOS(true);
	
	// Create light
	Ogre::Light *globalLight = mScnMgr->createLight("GlobalLight");
	globalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	globalLight->setCastShadows(true);
	globalLight->setDiffuseColour(0.8, 0.8, 0.8);
	globalLight->setSpecularColour(1, 1, 1);
	globalLight->setPosition(0, 0, 50);
	globalLight->setDirection(0, -1, 0);
}

void OViSESceneHandling::addGrid(int size, int numRows, int numCols, Ogre::Vector3& col, Ogre::SceneNode *node)
{
	Ogre::ManualObject* gridObject = mScnMgr->createManualObject("grid");
	
	Ogre::SceneNode* gridObjectNode;
	if(node == NULL)
	{
		gridObjectNode = mScnMgr->getRootSceneNode()->createChildSceneNode("grid_node");
	}
	else
	{
		gridObjectNode = node->createChildSceneNode("grid_node");
	}
	Ogre::MaterialPtr gridObjectMaterial = Ogre::MaterialManager::getSingleton().create("gridMaterial", "grid");
	gridObjectMaterial->setReceiveShadows(false);
	gridObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	gridObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(col.x,col.y,col.z,0);
	gridObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(col.x,col.y,col.z);
	
	gridObject->begin("gridMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	Ogre::Vector3 currentPos = Ogre::Vector3(numRows*size/-2, 0, numCols*size/-2);
	for(int i=0; i<numRows+1; i++)
	{
		gridObject->position(currentPos);
		gridObject->position(currentPos.x + numCols*size, currentPos.y, currentPos.z);
		currentPos.z += size;
	}
	currentPos.z = numCols*size/-2;
	for(int j=0; j<numCols+1; j++)
	{
		gridObject->position(currentPos);
		gridObject->position(currentPos.x, currentPos.y, currentPos.z + numRows * size);
		currentPos.x += size;
	}			
	gridObject->end();
	
	gridObjectNode->attachObject(gridObject);
}

void OViSESceneHandling::addCOS(bool castShadows, Ogre::SceneNode *node)
{
	Ogre::Entity *xAxisEnt = mScnMgr->createEntity("xAxis", "xAxis.mesh");
	xAxisEnt->setCastShadows(castShadows);
	Ogre::Entity *yAxisEnt = mScnMgr->createEntity("yAxis", "yAxis.mesh");
	yAxisEnt->setCastShadows(castShadows);
	Ogre::Entity *zAxisEnt = mScnMgr->createEntity("zAxis", "zAxis.mesh");
	zAxisEnt->setCastShadows(castShadows);
	if(node == NULL)
	{
		mScnMgr->getRootSceneNode()->attachObject(xAxisEnt);
		mScnMgr->getRootSceneNode()->attachObject(yAxisEnt);
		mScnMgr->getRootSceneNode()->attachObject(zAxisEnt);
	}
	else
	{
		node->attachObject(xAxisEnt);
		node->attachObject(yAxisEnt);
		node->attachObject(zAxisEnt);
	}
}

std::vector<std::string> OViSESceneHandling::getAvailableMeshes(std::string group)
{
	Ogre::StringVectorPtr resources = Ogre::ResourceGroupManager::getSingletonPtr()->listResourceNames(group);
	if(resources->size() == 0)
		throw std::exception("Resource group not found!");
	std::vector<std::string> returnvec;
	for(Ogre::StringVector::iterator it = resources->begin(); it != resources->end(); it++)
		returnvec.push_back(*it);
	return returnvec;
}

std::vector<std::string> OViSESceneHandling::getAvailableResourceGroupNames()
{
	return Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
}

OViSESceneHandling::~OViSESceneHandling()
{
}
