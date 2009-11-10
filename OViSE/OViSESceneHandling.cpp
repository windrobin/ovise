#include "OViSESceneHandling.h"
#include <wx/dir.h>

// REFACTORING:		IN PROGRESS
// REFACTOR-ID:		ID#0000 = outdated
// REFACTOR-ID:		ID#0001 = reviewed
// REFACTOR-ID:		ID#0002 = observe
// REFACTOR-ID:		ID#0003 = refactoting done
// AUTHOR:			H.R.

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
		//ID#0003//Ogre::SceneManager *mainSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "BaseSceneManager"); //ID#0001//move to OgreAPIMediator
		//ID#0003//mSceneManagers["BaseSceneManager"] = mainSceneManager;
		//ID#0003//mObjectSelectionQuerys["BaseSceneManager"] = mainSceneManager->createRayQuery(Ogre::Ray());
		//ID#0000//mObjectSelectionsMap["BaseSceneManager"] = OViSESelectionMap();

		mFrameListener = new OViSEFrameListener();//ID#0002 = observe//
		Ogre::Root::getSingletonPtr()->addFrameListener(mFrameListener);//ID#0002 = observe//
		
		//ID#0003//OgreAPIMediator::GetSingletonPtr()->SetSceneManagerByRef(mainSceneManager); //ID#0001//delete
		//ID#0003//this->mDotSceneMgr = new OViSEDotSceneManager(OViSEDotSceneManager::CreateDefaultConfiguration(ToWxString("StandardFactory"), ToWxString(mainSceneManager->getName()))); //ID#0001//move to OgreAPIMediator
	}
}

//ID#0002//
void OViSESceneHandling::createDefaultScene(wxString sceneManagerName)
{
	// Create default grid
	Ogre::Entity* NewEntity = OgreAPIMediator::GetSingletonPtr()->addEntity(ToWxString("BasePlane"), ToWxString("Plane.mesh"));

	// Create KOS-scene
	wxString UniqueNameoOfKOS = this->mDotSceneMgr->ImportScenePrototype(wxFileName(ToWxString("C:/Dokumente und Einstellungen/renartz.ITEC/Eigene Dateien/OViSE Checkout/KOS/KOS.xml")));
	this->mDotSceneMgr->MakeOgreSceneFromPrototype(UniqueNameoOfKOS, ToWxString(this->mSceneManagers[ToStdString(sceneManagerName)]->getRootSceneNode()->getName()));
	
	// Create light
	Ogre::Light *globalLight = OgreAPIMediator::GetSingletonPtr()->addLight(ToWxString("GlobalLight"));
	globalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	globalLight->setCastShadows(true);
	globalLight->setDiffuseColour(0.8, 0.8, 0.8);
	globalLight->setSpecularColour(1, 1, 1);
	globalLight->setPosition(0, 0, 50);
	globalLight->setDirection(0, -1, 0);

	OgreAPIMediator::GetSingletonPtr()->SendOgreChanged();
}

//ID#0001//already implemented in OgreAPIMediator
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

//ID#0001//already implemented in OgreAPIMediator
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

//ID#0001//already implemented in OgreAPIMediator
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

//ID#0001//move to OgreAPIMediator
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

//ID#0001//move to OgreAPIMediator
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

//ID#0001//outdated
Ogre::MovableObject* OViSESceneHandling::getSelectedObject(wxString ObjectName, Ogre::SceneManager* ScnMgr)
{
	try
	{
		Ogre::SceneManager *scnMgr = ScnMgr;

		bool Match = false;

		if ((!Match) && (scnMgr->hasCamera(ToOgreString(ObjectName))))
		{
			return scnMgr->getCamera(ToOgreString(ObjectName));
		}

		if ((!Match) && (scnMgr->hasEntity(ToOgreString(ObjectName))))
		{
			return scnMgr->getEntity(ToOgreString(ObjectName));
		}

		if ((!Match) && (scnMgr->hasLight(ToOgreString(ObjectName))))
		{
			return scnMgr->getLight(ToOgreString(ObjectName));
		}

		if ((!Match) && (scnMgr->hasSceneNode(ToOgreString(ObjectName))))
		{
			return NULL;// TODO: Incompatible. Find a better way soon. // scnMgr->getSceneNode(ToOgreString(ObjectName());
		}

		return NULL;
	}
	catch (Ogre::Exception e)
	{
		Ogre::String logMsg = "[SceneHandling] Couldn't get object of TreeView in scene (" + e.getFullDescription() + ")";
		Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
		return NULL;
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String(e.what()));
		return NULL;
	}
}

//ID#0001//outdated
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

//ID#0001//outdated
void OViSESceneHandling::addObjectToSelection(Ogre::MovableObject *movObj, bool showSelection, std::string sceneManagerName)
{
	try
	{
		mObjectSelectionsMap[sceneManagerName][movObj->getName()] = movObj;
		
		if(showSelection)
			movObj->getParentSceneNode()->showBoundingBox(true);

		OViSELogging* TempLog = new OViSELogging();
		wxString LogMsg;
		LogMsg << ToWxString("USER selected MovableObject: '");
		LogMsg << ToWxString(movObj->getName());
		LogMsg << ToWxString("'. It belongs to SceneNode: '");
		LogMsg << ToWxString(movObj->getParentSceneNode()->getName());
		LogMsg << ToWxString("'.");
		TempLog->WriteToOgreLog(LogMsg, OViSELogging::Normal);
		delete TempLog;
	}
	catch (...)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Warning: Couldn't add object to object selection!");
	}
}

//ID#0001//outdated
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

//ID#0001//outdated
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

//ID#0001//outdated
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

//ID#0001//outdated
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

//ID#0001//move to OgreAPIMediator
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

//ID#0001//move to OgreAPIMediator
void OViSESceneHandling::addCOS(float scale, bool castShadows, wxString sceneManagerName, Ogre::SceneNode *node)
{
	try
	{
		Ogre::SceneManager* tmp = this->getSceneManager(ToOgreString(sceneManagerName));
		if(node == NULL) node = tmp->getRootSceneNode();

		//Ogre::SceneNode *NewSceneNode = this->mDotSceneMgr->attachSceneNode(ToWxString("KOSNode"), Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Vector3(scale, scale, scale), Ogre::Quaternion::IDENTITY);
		Ogre::SceneNode *NewSceneNode = tmp->getRootSceneNode()->createChildSceneNode(ToOgreString("KOSNode"));
		NewSceneNode->scale(scale, scale, scale);

		Ogre::Entity *AxisEnt;
		//AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("xAxis"), ToWxString("xAxis.mesh"), NewSceneNode);
		AxisEnt = tmp->createEntity(ToOgreString("xAxis"), ToOgreString("xAxis.mesh"));
		NewSceneNode->attachObject(AxisEnt);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
		//AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("yAxis"), ToWxString("yAxis.mesh"), NewSceneNode);
		AxisEnt = tmp->createEntity(ToOgreString("zAxis"), ToOgreString("yAxis.mesh"));
		NewSceneNode->attachObject(AxisEnt);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
		//AxisEnt = this->mDotSceneMgr->attachEntity(ToWxString("zAxis"), ToWxString("zAxis.mesh"), NewSceneNode);
		AxisEnt = tmp->createEntity(ToOgreString("yAxis"), ToOgreString("zAxis.mesh"));
		NewSceneNode->attachObject(AxisEnt);
		if (AxisEnt != NULL) AxisEnt->setCastShadows(castShadows);
	}
	catch (OViSEException e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(e.what());
	}
	catch (...) {}
}

//ID#0002//
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

//ID#0002//
std::vector<std::string> OViSESceneHandling::getAvailableResourceGroupNames()
{
	return Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
}

//ID#0002//
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

//ID#0002//
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


//ID#0002//
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

//ID#0002//
void OViSESceneHandling::updateObjectTitles()
{
	for(OViSEObjectTitleVector::iterator iter = mObjectTitlesVector.begin(); iter != mObjectTitlesVector.end(); iter++)
	{
		(*iter)->update();
	}
}

//ID#0002//
void OViSESceneHandling::dynamicShadows(bool state)
{
	Ogre::SceneManager *scnMgr = mSceneManagers["BaseSceneManager"];
	if(state) scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	else scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}

//ID#0001//outdated
void OViSESceneHandling::testStuff()
{
	Ogre::SceneManager *scnMgr = mSceneManagers["BaseSceneManager"];
}

//ID#0001//outdated
void OViSESceneHandling::startStopFrameListeners(bool on)
{
	/*
	if(on)
		mFrameListener->setFrameEventsProcessed(true);
	else
		mFrameListener->setFrameEventsProcessed(false);
		*/
}

//ID#0001//outdated
OViSESceneHandling::~OViSESceneHandling()
{
	//delete this->mDotSceneMgr;
}

//ID#0001//outdated
void OViSESceneHandling::ImportPrototypeFromXML(wxString URLofXML)
{
	/*this->mDotSceneMgr->ImportPrototype(URLofXML);*/
}

//ID#0001//outdated
void OViSESceneHandling::ExportPrototypeToXML(wxString DestinationFileName, wxString NameOfHostingSceneManager, Ogre::SceneNode *node, bool doExportMeshFiles)
{
	/* Export depending on selection */
	if (this->hasSelectedObjects())
	{
		;/*this->mDotSceneMgr->ExportPrototype(this->getSelectedObjects(), DestinationFileName, true, doExportMeshFiles); // TODO: modify "doExportNotSelectedChildNodesToo" = true*/
	}
	else
	{
		// Use RootSceneNode and export everything!
		OViSESelectionMap tempSimpleSelection;
		tempSimpleSelection[this->getSceneManager()->getRootSceneNode()->getName()] = (Ogre::MovableObject*)this->getSceneManager()->getRootSceneNode();
		/*this->mDotSceneMgr->ExportPrototype(tempSimpleSelection, DestinationFileName, true, doExportMeshFiles); // TODO: modify "doExportNotSelectedChildNodesToo" = true*/
	}
}

//ID#0001//outdated
void OViSESceneHandling::AttachNewScene(wxString UniqueNameOfPrototype)
{
	if (!UniqueNameOfPrototype.IsEmpty())
	{
		;/*this->mDotSceneMgr->AttachSceneFromPrototype(UniqueNameOfPrototype, wxString());*/
	}
}

//ID#0002//
void OViSESceneHandling::release()
{
	delete OViSESceneHandling::getSingletonPtr();
}

//ID#0001//outdated
wxArrayString OViSESceneHandling::GetAvailablePrototypesOfDotSceneManager()
{
	return wxArrayString(); //this->mDotSceneMgr->GetImportedScenePrototypes();
}


