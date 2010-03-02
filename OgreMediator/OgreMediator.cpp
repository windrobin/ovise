#include "../OgreMediator/OgreMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreMediator* OgreMediator::instance = 0;
OgreMediator* OgreMediator::GetSingletonPtr()
{
	if (OgreMediator::instance == 0){
		OgreMediator::instance = new OgreMediator();
		// Create default SceneManager
	OgreMediator::instance->mDefaultSceneManager = OgreMediator::instance->iSceneManager.Create(ToWxString("Default"));

	// Set it as ActiveSceneManager
	OgreMediator::instance->iSceneManager.SetActiveSceneManager(OgreMediator::instance->mDefaultSceneManager);

	// Create and store RaySceneQuery
	OgreMediator::instance->iSceneManager.CreateRaySceneQuery(OgreMediator::instance->mDefaultSceneManager);

	// Create and store RootSceneNode
	OgreMediator::instance->iSceneNode.Create(ToWxString(OgreMediator::instance->iSceneManager.GetPtr(OgreMediator::instance->mDefaultSceneManager)->getRootSceneNode()->getName()));
	}
	return OgreMediator::instance;
}
OgreMediator::OgreMediator()
{
	this->Valid = true;

	this->mObjectAccess = new ObjectManager();

	this->iCamera = CameraInterface(this->mObjectAccess);
	this->iEntity = EntityInterface(this->mObjectAccess);
	this->iLight = LightInterface(this->mObjectAccess);
	this->iMovableObject = MovableObjectInterface(this->mObjectAccess);
	this->iSceneNode = SceneNodeInterface(&(this->iMovableObject), this->mObjectAccess);
	this->iSceneManager = SceneManagerInterface(&(this->iSceneNode), this->mObjectAccess);
}
OgreMediator::~OgreMediator(void) { this->iSceneManager.Destroy(this->mDefaultSceneManager); }
// General
bool OgreMediator::IsValid() { return this->Valid; }
ObjectManager* OgreMediator::GetObjectAccess() { return this->mObjectAccess; }

void OgreMediator::AddGrid(int size, int numRows, int numCols, Ogre::Vector3 col, QualifiedName qSceneManager, QualifiedName qSceneNode)
{
	Ogre::SceneManager *tmp = iSceneManager.GetPtr( qSceneManager );
	Ogre::ManualObject* gridObject = tmp->createManualObject("grid");

	Ogre::SceneNode* node = mObjectAccess->GetSceneNode( qSceneNode );
	
	Ogre::SceneNode* gridObjectNode;
	if(node == NULL)
	{
		gridObjectNode = tmp->getRootSceneNode()->createChildSceneNode("grid_node");
	}
	else
	{
		gridObjectNode = node->createChildSceneNode("grid_node");
	}
	mObjectAccess->AddSceneNode( QualifiedName::Create( wxT("grid_node") ), gridObjectNode );

	Ogre::MaterialPtr gridObjectMaterial = Ogre::MaterialManager::getSingleton().create("gridMaterial", "grid");
	gridObjectMaterial->setReceiveShadows(false);
	gridObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	gridObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(col.x,col.y,col.z,0);
	gridObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(col.x,col.y,col.z);
	
	gridObject->begin("gridMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	Ogre::Vector3 currentPos = Ogre::Vector3(numRows*size/-2, numCols*size/-2, 0);
	for(int i=0; i<numRows+1; i++)
	{
		gridObject->position(currentPos);
		gridObject->position(currentPos.x + numCols*size, currentPos.y, currentPos.z);
		currentPos.y += size;
	}
	currentPos.y = numCols*size/-2;
	for(int j=0; j<numCols+1; j++)
	{
		gridObject->position(currentPos);
		gridObject->position(currentPos.x, currentPos.y + numRows * size, currentPos.z);
		currentPos.x += size;
	}			
	gridObject->end();
	
	gridObjectNode->attachObject(gridObject);
}

void OgreMediator::AddCOS(QualifiedName qSceneManager, QualifiedName qSceneNode, float scale, bool castShadows)
{
	/*try
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
	catch (...) {}*/
}