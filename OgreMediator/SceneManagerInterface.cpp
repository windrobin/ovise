#include "../OgreMediator/SceneManagerInterface.h"

// De- & Constructors, individual
SceneManagerInterface::SceneManagerInterface(SceneNodeInterface* iSceneNode, ObjectManager* ObjMgr) : MediatorInterface(ObjMgr) { this->SetSceneNodeInterface(iSceneNode); }
SceneManagerInterface::~SceneManagerInterface(void) { }
// Methods, inherited and overwritten
QualifiedName SceneManagerInterface::Create(wxString Name) { return this->Create(Name, Ogre::ST_GENERIC); }
bool SceneManagerInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::SceneManager
	if ( !this->Exist(qName) ) return false;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qName);

	// Destroy recusive: childnodes
	Ogre::SceneNode* RSN = SM->getRootSceneNode();
	wxString UniqueName = ToWxString(RSN->getName());
	QualifiedName qRootSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	this->iSceneNode->Destroy(qRootSceneNode);

	// Destroy possible RaySceneQuery
	this->DestroyRaySceneQuery(qName);

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveSceneManager(qName);

	// Destroy Ogre::SceneManager
	Ogre::Root::getSingletonPtr()->destroySceneManager(SM);

	//EventDispatcher::Publish(EVT_OGRE_OBJECT_DESTRUCTED, qName);
	//EventDispatcher::Publish(EVT_OGRE_SCENEMANAGER_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::SceneManager
	QualifiedName::Destroy(qName);

	return true;
}
bool SceneManagerInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a SceneManager
	if (this->mObjectAccess->GetSceneManager(qName) == 0) return false;
	
	return true;
}
bool SceneManagerInterface::IsValid()
{
	if( !MediatorInterface::IsValid() ) return false;
	if( this->iSceneNode == 0 ) return false;

	return true;
}
// Methods, individual
QualifiedName SceneManagerInterface::Create(wxString Name, Ogre::SceneType pSceneType)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Create QualifiedName of new Ogre::SceneManager
	QualifiedName qSceneManager = QualifiedName::Create(Name, "SceneManager");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetSceneManager(qSceneManager) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qSceneManager).IsValid()))
	{
		QualifiedName::Destroy(qSceneManager);
		return QualifiedName();
	}

	// Create and validate new Ogre::SceneManager
	Ogre::SceneManager* SM = Ogre::Root::getSingletonPtr()->createSceneManager(pSceneType, ToOgreString(qSceneManager.UniqueName()));

	if (SM == 0)
	{
		QualifiedName::Destroy(qSceneManager);
		return QualifiedName();
	}

	// Add new Ogre::Camera ObjectManager
	this->mObjectAccess->AddSceneManager(qSceneManager, SM);

	// Add new association between Ogre::SceneManager and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(qSceneManager, qSceneManager);

	//EventDispatcher::Publish(EVT_OGRE_OBJECT_CONSTRUCTED, qSceneManager);
	//EventDispatcher::Publish(EVT_OGRE_SCENEMANAGER_CONSTRUCTED, qSceneManager);

	// Return QualifiedName of new Ogre::Camera
	return qSceneManager;
}
QualifiedName SceneManagerInterface::GetName(Ogre::SceneManager* pSceneManager)
{
	wxString UniqueName = ToWxString(pSceneManager->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
Ogre::SceneManager*	SceneManagerInterface::GetPtr(QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return 0;

	// Get SceneManager and return it (or null)
	return this->mObjectAccess->GetSceneManager(qSceneManager);
}
// Methods, individual, active Ogre::SceneManager
bool SceneManagerInterface::SetActiveSceneManager(QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return false;

	// Forward & Return
	return this->mObjectAccess->SetActiveSceneManager(qSceneManager);
}
QualifiedName SceneManagerInterface::GetActiveSceneManager() { return this->mObjectAccess->GetActiveSceneManager(); }
// Methods, individual, configuration
bool SceneManagerInterface::SetSceneNodeInterface(SceneNodeInterface* iSceneNode)
{
	if (iSceneNode == 0) return false;
	else
	{
		this->iSceneNode = iSceneNode;
		return true;
	}
}

// Methods, individual, manage RaySceneQuery
bool SceneManagerInterface::CreateRaySceneQuery(QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return false;
	
	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);
	if ( SM == 0 ) return false;

	// Create RaySceneQuery
	Ogre::RaySceneQuery* RSQ = SM->createRayQuery(Ogre::Ray());

	// Validate new Ogre::RaySceneQuery
	if (RSQ == 0) return false;

	// Add new Ogre::RaySceneQuery ObjectManager
	return this->mObjectAccess->AddRaySceneQuery(qSceneManager, RSQ);
}
bool SceneManagerInterface::DestroyRaySceneQuery(QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return false;
	
	// Add new Ogre::RaySceneQuery ObjectManager
	return this->mObjectAccess->RemoveRaySceneQuery(qSceneManager);
}
Ogre::RaySceneQuery* SceneManagerInterface::GetRaySceneQuery(QualifiedName qSceneManager)
{
	// Validate paramaters
	if ( !qSceneManager.IsValid() ) return false;
	if ( this->mObjectAccess->GetSceneManager(qSceneManager) == 0 ) return false;
	
	// Add new Ogre::RaySceneQuery ObjectManager
	return this->mObjectAccess->GetRaySceneQuery(qSceneManager);
}
// Methods, individual, execute RaySceneQuery
QualifiedNameCollection	SceneManagerInterface::QueryObjectsByRay(Ogre::Ray pRay, QualifiedName qSceneManager)
{
	QualifiedNameCollection QNames;

	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return QNames;

	// Get Ogre::RaySceneQuery
	Ogre::RaySceneQuery* RSQ = this->mObjectAccess->GetRaySceneQuery(qSceneManager);
	
	// Validate Ogre::RaySceneQuery
	if (RSQ == 0) return QNames;

	// Prepare RayScan
	RSQ->setRay(pRay);
	RSQ->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	RSQ->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = RSQ->execute();
	if(RayScanResult.size() != 0)
	{
		for(unsigned long IT = 0; IT < RayScanResult.size(); IT++)
		{
			Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[IT];
			Ogre::MovableObject* MO = RayScanResultEntry.movable;
			QualifiedName qMO = this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
			if (qMO.IsValid()) QNames.Add(qMO);
		}
	}
	
	return QNames;
}
QualifiedName SceneManagerInterface::QueryFrontObjectByRay(Ogre::Ray pRay, QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return QualifiedName();

	// Get Ogre::RaySceneQuery
	Ogre::RaySceneQuery* RSQ = this->mObjectAccess->GetRaySceneQuery(qSceneManager);
	
	// Validate Ogre::RaySceneQuery
	if (RSQ == 0) return QualifiedName();

	// Prepare RayScan
	RSQ->setRay(pRay);
	RSQ->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	RSQ->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = RSQ->execute();
	if(RayScanResult.size() != 0)
	{
		Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[0];
		Ogre::MovableObject* MO = RayScanResultEntry.movable;
		return this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return QualifiedName();
}
QualifiedName SceneManagerInterface::QueryBackObjectByRay(Ogre::Ray pRay, QualifiedName qSceneManager)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return QualifiedName();

	// Get Ogre::RaySceneQuery
	Ogre::RaySceneQuery* RSQ = this->mObjectAccess->GetRaySceneQuery(qSceneManager);
	
	// Validate Ogre::RaySceneQuery
	if (RSQ == 0) return QualifiedName();

	// Prepare RayScan
	RSQ->setRay(pRay);
	RSQ->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	RSQ->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = RSQ->execute();
	if(RayScanResult.size() != 0)
	{
		Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[RayScanResult.size()-1];
		Ogre::MovableObject* MO = RayScanResultEntry.movable;
		return this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return QualifiedName();
}
// Methods, individual, helper-methods
Ogre::Ray SceneManagerInterface::Assist_GetRayForRaySceneQuery(float screenx, float screeny, Ogre::Camera* cam)
{
	if ( cam == 0 ) return Ogre::Ray();
	return cam->getCameraToViewportRay(screenx, screeny);
}
// Methods, individual, manage shadows
void SceneManagerInterface::DynamicShadows(QualifiedName qSceneManager, bool State)
{
	// Validate qSceneManager
	if ( !this->Exist(qSceneManager) ) return;

	if(State) this->GetPtr(qSceneManager)->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	else this->GetPtr(qSceneManager)->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}