#include "OViSESceneHandling.h"

OViSESceneHandling* OViSESceneHandling::mInstance = NULL;

OViSESceneHandling* OViSESceneHandling::getSingletonPtr()
{
	if(mInstance == NULL)
	{
		mInstance = new OViSESceneHandling();
	}
	return mInstance;
}

OViSESceneHandling::OViSESceneHandling()
{
	if(mInstance == NULL)
	{
		Ogre::SceneManager *mainSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "BaseSceneManager");
		mSceneManagers["BaseSceneManager"] = mainSceneManager;
		mObjectSelectionQuerys["BaseSceneManager"] = mainSceneManager->createRayQuery(Ogre::Ray());
		mObjectSelectionsMap["BaseSceneManager"] = OViSESelectionMap();

		mFrameListener = new OViSEFrameListener();
		Ogre::Root::getSingletonPtr()->addFrameListener(mFrameListener);
		
		this->mDotSceneMgr = new OViSEDotSceneManager(ToWxString("StandardFactory"), mainSceneManager);


	}
}

void OViSESceneHandling::createDefaultScene(wxString sceneManagerName)
{
	// Create default grid
	this->mDotSceneMgr->attachEntity(ToWxString("BasePlane"), ToWxString("Plane.mesh"), this->getSceneManager(ToStdString(sceneManagerName))->getRootSceneNode());

	addCOS(0.1, true, sceneManagerName);

	Ogre::SceneManager *tmp = mSceneManagers[ToStdString(sceneManagerName)];
	
	// Create light
	Ogre::Light *globalLight = tmp->createLight("GlobalLight");
	globalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	globalLight->setCastShadows(true);
	globalLight->setDiffuseColour(0.8, 0.8, 0.8);
	globalLight->setSpecularColour(1, 1, 1);
	globalLight->setPosition(0, 0, 50);
	globalLight->setDirection(0, -1, 0);
	tmp->getRootSceneNode()->attachObject(globalLight);
}

void OViSESceneHandling::addSceneManager(std::string sceneManagerName)
{
	for(OViSEScnMgrMap::iterator it = mSceneManagers.begin(); it != mSceneManagers.end(); it++)
	{
		if(it->first.compare(sceneManagerName) == 0)
		{
			std::string logMsg = "Scene Manager with name: " + sceneManagerName + " already exists!";
			throw OViSEException(logMsg.c_str());
		}
	}

	Ogre::SceneManager *tmp = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, sceneManagerName);
	mSceneManagers[sceneManagerName] = tmp;
	mObjectSelectionQuerys[sceneManagerName] = tmp->createRayQuery(Ogre::Ray());
	mObjectSelectionsMap[sceneManagerName] = OViSESelectionMap();
}

Ogre::SceneManager* OViSESceneHandling::getSceneManager(std::string sceneManagerName)
{
	OViSEScnMgrMap::iterator it = mSceneManagers.find(sceneManagerName);
	if(it == mSceneManagers.end())
	{
		std::string logMsg = "Couldn't find scene manager with name " + sceneManagerName;
		throw OViSEException(logMsg.c_str());
	}
	else return it->second;
}

void OViSESceneHandling::removeSceneManager(std::string sceneManagerName)
{
	OViSEScnMgrMap::iterator it = mSceneManagers.find(sceneManagerName);
	if(it == mSceneManagers.end())
	{
		std::string logMsg = "Couldn't find scene manager with name " + sceneManagerName;
		Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
		return;
	}
	Ogre::Root::getSingletonPtr()->destroySceneManager(it->second);
	mSceneManagers.erase(sceneManagerName);
	mObjectSelectionQuerys.erase(sceneManagerName);
	mObjectSelectionsMap[sceneManagerName].clear();
	mObjectSelectionsMap.erase(sceneManagerName);
}

Ogre::RaySceneQuery* OViSESceneHandling::getObjectSelectionQuery(std::string sceneManagerName)
{
	OViSERayQueryMap::iterator it = mObjectSelectionQuerys.find(sceneManagerName);
	if(it == mObjectSelectionQuerys.end())
	{
		std::string logMsg = "Couldn't find object selection query for scene manager with name " + sceneManagerName;
		throw OViSEException(logMsg.c_str());
	}
	return it->second;
}

Ogre::MovableObject* OViSESceneHandling::getSelectedObject(float screenx, float screeny, float& dist, Ogre::Camera *cam, std::string sceneManagerName)
{
	try
	{
		Ogre::SceneManager *scnMgr = getSceneManager(sceneManagerName);
		Ogre::RaySceneQuery *query = getObjectSelectionQuery(sceneManagerName);
		query->setRay(cam->getCameraToViewportRay(screenx, screeny));
		// exclude cameras and scene structure mesh
		query->setQueryMask(~0x01);
		query->setSortByDistance(true);
		Ogre::RaySceneQueryResult &result = query->execute();
		if(result.size() != 0)
		{
			Ogre::RaySceneQueryResultEntry ent = result[0];
			dist = ent.distance;
			return ent.movable;
		}
		else
		{
			dist = -1;
			return NULL;
		}
	}
	catch (Ogre::Exception e)
	{
		Ogre::String logMsg = "[SceneHandling] Couldn't make ray scene query (" + e.getFullDescription() + ")";
		Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
		return NULL;
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
		return NULL;
	}
}

void OViSESceneHandling::clearObjectSelection(std::string sceneManagerName)
{
	try
	{
		OViSESelectionMap map = mObjectSelectionsMap[sceneManagerName];
		for(OViSESelectionMap::iterator it = map.begin(); it != map.end(); it++)
		{
			it->second->getParentSceneNode()->showBoundingBox(false);
		}
		mObjectSelectionsMap[sceneManagerName].clear();
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't clear object selection!");
	}
}

void OViSESceneHandling::addObjectToSelection(Ogre::MovableObject *movObj, bool showSelection, std::string sceneManagerName)
{
	try
	{
		mObjectSelectionsMap[sceneManagerName][movObj->getName()] = movObj;
		
		if(showSelection)
			movObj->getParentSceneNode()->showBoundingBox(true);
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't add object to object selection!");
	}
}

void OViSESceneHandling::removeObjectFromSelection(Ogre::MovableObject *movObj, bool hideSelection, std::string sceneManagerName)
{
	try
	{
		if(movObj)
			mObjectSelectionsMap[sceneManagerName].erase(movObj->getName());
		if(movObj && hideSelection)
			movObj->getParentSceneNode()->showBoundingBox(false);
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't remove object from object selection!");
	}
}

void OViSESceneHandling::removeObjectFromSelection(std::string name, bool hideSelection, std::string sceneManagerName)
{
	try
	{
		Ogre::MovableObject *tmp = mObjectSelectionsMap[sceneManagerName][name];
		if(tmp && hideSelection)
			tmp->getParentSceneNode()->showBoundingBox(false);
		mObjectSelectionsMap[sceneManagerName].erase(name);
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't remove object from object selection!");
	}
}

OViSESelectionMap OViSESceneHandling::getSelectedObjects(std::string sceneManagerName)
{
	try
	{
		return mObjectSelectionsMap[sceneManagerName];
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't get object selection!");
		return OViSESelectionMap();
	}
}

bool OViSESceneHandling::hasSelectedObjects(std::string sceneManagerName)
{
	try
	{
		OViSESelectionMap tmp = mObjectSelectionsMap[sceneManagerName];
		if(tmp.size() > 0)
			return true;
		else return false;
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't get object selection!");
		return false;
	}
}

void OViSESceneHandling::addGrid(int size, int numRows, int numCols, Ogre::Vector3 col, std::string sceneManagerName, Ogre::SceneNode *node)
{
	try
	{
		Ogre::SceneManager *tmp = getSceneManager(sceneManagerName);
		Ogre::ManualObject* gridObject = tmp->createManualObject("grid");
		
		Ogre::SceneNode* gridObjectNode;
		if(node == NULL)
		{
			gridObjectNode = tmp->getRootSceneNode()->createChildSceneNode("grid_node");
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
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
	}
}

void OViSESceneHandling::addCOS(float scale, bool castShadows, wxString sceneManagerName, Ogre::SceneNode *node)
{
	try
	{
		if(node == NULL) node = this->getSceneManager(ToOgreString(sceneManagerName))->getRootSceneNode();

		Ogre::SceneNode *NewSceneNode = this->mDotSceneMgr->attachSceneNode(ToWxString("KOSNode"), Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Vector3(scale, scale, scale), Ogre::Quaternion::IDENTITY);
		Ogre::Entity *AxisEnt;
		AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("xAxis"), ToWxString("xAxis.mesh"), NewSceneNode);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
		AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("yAxis"), ToWxString("yAxis.mesh"), NewSceneNode);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
		AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("zAxis"), ToWxString("zAxis.mesh"), NewSceneNode);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.what());
	}
	catch (...) {}
}

std::vector<std::string> OViSESceneHandling::getAvailableMeshes(std::string group)
{
	Ogre::StringVectorPtr resources = Ogre::ResourceGroupManager::getSingletonPtr()->listResourceNames(group);
	if(resources->size() == 0)
		throw OViSEException("Resource group not found!");
	std::vector<std::string> returnvec;
	for(Ogre::StringVector::iterator it = resources->begin(); it != resources->end(); it++)
		returnvec.push_back(*it);
	return returnvec;
}

std::vector<std::string> OViSESceneHandling::getAvailableResourceGroupNames()
{
	return Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
}

void OViSESceneHandling::addMesh(std::string meshName, std::string meshFileName, std::string sceneManagerName, Ogre::SceneNode *node)
{
	try
	{
		Ogre::SceneManager *scnMgr = getSceneManager(sceneManagerName);
		Ogre::Entity *ent = scnMgr->createEntity(meshName, meshFileName);
		if(node)
		{
			node->attachObject(ent);
		}
		else
		{
			scnMgr->getRootSceneNode()->createChildSceneNode(meshName)->attachObject(ent);
		}
		std::string logMsg = "[OViSE] Added mesh " + meshFileName;
		Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
	}
	catch (Ogre::Exception &e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.getFullDescription());
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
	}
}

void OViSESceneHandling::deleteMesh(std::string meshName, std::string sceneManagerName)
{
	try
	{
		Ogre::SceneManager *scnMgr = getSceneManager(sceneManagerName);
		if(scnMgr->hasEntity(meshName))
		{
			OViSESceneHandling::getSingletonPtr()->removeObjectFromSelection(meshName);
			Ogre::Entity *tmp = scnMgr->getEntity(meshName);
			Ogre::SceneNode *tmpnode = tmp->getParentSceneNode();
			tmpnode->detachObject(tmp);
			if(tmpnode->numAttachedObjects() == 0 && tmpnode->numChildren() == 0 && tmpnode != scnMgr->getRootSceneNode())
				scnMgr->destroySceneNode(tmpnode);
			scnMgr->destroyEntity(tmp);
		}
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
	}
}


void OViSESceneHandling::showSceneGraphStructure(bool update, std::string sceneManagerName)
{
	Ogre::SceneManager *scnMgr = mSceneManagers[sceneManagerName];
	if(!scnMgr) throw OViSEException("Scene manager not found!");

	// Let's see if we're already displaying a structure
	if(scnMgr->hasManualObject("SceneGraphStructure"))
	{
		// yes, delete old structure
		scnMgr->destroyManualObject("SceneGraphStructure");
		// kill all object titles
		for(OViSEObjectTitleVector::iterator iter = mObjectTitlesVector.begin(); iter != mObjectTitlesVector.end(); iter++)
			delete *iter;
		mObjectTitlesVector.clear();
		// if we're not requesting an update, return
		if(!update)	return;
	}
	else  // no structure found
	{
		if(update) return;
			// misguided update request, there's nothing to update so don't do anything
	}

	// either we need to update an existing structure or show a new one

	Ogre::ManualObject *sgs = scnMgr->createManualObject("SceneGraphStructure");
	// set flags, so it cannot be selected
	sgs->setQueryFlags(0x01);

	if(!Ogre::MaterialManager::getSingletonPtr()->resourceExists("SceneStructureMaterial"))
	{
		Ogre::MaterialPtr sgsMaterial = Ogre::MaterialManager::getSingleton().create("SceneStructureMaterial", "General");
		sgsMaterial->setReceiveShadows(false);
		sgsMaterial->getTechnique(0)->setLightingEnabled(true);
		sgsMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0);
		sgsMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0);
	}

	Ogre::SceneManager::MovableObjectIterator iter = scnMgr->getMovableObjectIterator("Entity");
	while(iter.hasMoreElements())
	{
		Ogre::MovableObject *mobj = iter.getNext();
		OViSEObjectTitle *tmp = new OViSEObjectTitle(mobj->getName(), mobj, scnMgr->getCurrentViewport()->getCamera(), mobj->getName(), "BlueHighway");
		mObjectTitlesVector.push_back(tmp);
	}

	sgs->begin("SceneStructureMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	std::list<Ogre::Node*> nodeQueue;
	nodeQueue.push_back(scnMgr->getRootSceneNode());
	for(std::list<Ogre::Node*>::iterator it = nodeQueue.begin(); it != nodeQueue.end(); it++)
	{
		if((*it)->getName() == Ogre::String("mainCamFocusNode")) continue;
		Ogre::Node::ChildNodeIterator iter = (*it)->getChildIterator();
		while(iter.hasMoreElements())
		{
			Ogre::Node *tmp = iter.getNext();
			if(tmp->getName() == Ogre::String("mainCamFocusNode")) continue;
			sgs->position((*it)->_getDerivedPosition());
			sgs->position(tmp->_getDerivedPosition());
			nodeQueue.push_back(tmp);
		}
	}
	sgs->end();
	nodeQueue.clear();
	scnMgr->getRootSceneNode()->attachObject(sgs);
}

void OViSESceneHandling::updateObjectTitles()
{
	for(OViSEObjectTitleVector::iterator iter = mObjectTitlesVector.begin(); iter != mObjectTitlesVector.end(); iter++)
	{
		(*iter)->update();
	}
}

void OViSESceneHandling::dynamicShadows(bool state)
{
	Ogre::SceneManager *scnMgr = mSceneManagers["BaseSceneManager"];
	if(state) scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	else scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}

void OViSESceneHandling::testStuff()
{
	Ogre::SceneManager *scnMgr = mSceneManagers["BaseSceneManager"];
}

void OViSESceneHandling::startStopFrameListeners(bool on)
{
	if(on)
		mFrameListener->setFrameEventsProcessed(true);
	else
		mFrameListener->setFrameEventsProcessed(false);
}

OViSESceneHandling::~OViSESceneHandling()
{
	delete this->mDotSceneMgr;
}

void OViSESceneHandling::ImportPrototypeFromXML(wxString URLofXML) { this->mDotSceneMgr->ImportPrototype(URLofXML); }
void OViSESceneHandling::ExportPrototypeToXML(wxString DestinationFileName, wxString NameOfHostingSceneManager, Ogre::SceneNode *node, bool doExportMeshFiles)
{
	/* Export depending on selection */
	if (this->hasSelectedObjects())
	{
		this->mDotSceneMgr->ExportPrototype(this->getSelectedObjects(), DestinationFileName, true, doExportMeshFiles); // TODO: modify "doExportNotSelectedChildNodesToo" = true
	}
	else
	{
		// Use RootSceneNode and export everything!
		OViSESelectionMap tempSimpleSelection;
		tempSimpleSelection[this->getSceneManager()->getRootSceneNode()->getName()] = (Ogre::MovableObject*)this->getSceneManager()->getRootSceneNode();
		this->mDotSceneMgr->ExportPrototype(tempSimpleSelection, DestinationFileName, true, doExportMeshFiles); // TODO: modify "doExportNotSelectedChildNodesToo" = true
	}
}

void OViSESceneHandling::AttachNewScene(wxString UniqueNameOfPrototype)
{
	if (!UniqueNameOfPrototype.IsEmpty())
	{
		this->mDotSceneMgr->AttachSceneFromPrototype(UniqueNameOfPrototype, wxString());
	}
}

void OViSESceneHandling::release()
{
	delete OViSESceneHandling::getSingletonPtr();
}

wxArrayString OViSESceneHandling::GetAvailablePrototypesOfDotSceneManager()
{
	return this->mDotSceneMgr->GetImportedScenePrototypes();
}