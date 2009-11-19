#include "OgreAPIMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreAPIMediator* OgreAPIMediator::instance = 0;

OgreAPIMediator* OgreAPIMediator::GetSingletonPtr()
{
	if (OgreAPIMediator::instance == 0) OgreAPIMediator::instance = new OgreAPIMediator();
	return OgreAPIMediator::instance;
}
OgreAPIMediator::OgreAPIMediator()
{
	this->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OgreAPIMediator::OnOgreChanged ), NULL, this);

	this->Valid = true;

	// Create default SceneManager
	QualifiedName qDefaultSceneManager = *(this->CreateSceneManager(ToWxString("Default")));

	// Set it as ActiveSceneManager
	this->SetActiveSceneManager(qDefaultSceneManager);

	// Create and store RaySceneQuery
	this->CreateRaySceneQuery(qDefaultSceneManager);

	this->OgreChanged = false;
}
OgreAPIMediator::~OgreAPIMediator(void) { this->DestroySceneManager(); }
// General
bool OgreAPIMediator::IsValid() { return this->Valid; }
// Get & Set properies
/*
Ogre::SceneManager* OgreAPIMediator::GetSceneManagerByRef() { return this->SceneMgr; }
wxString OgreAPIMediator::GetSceneManagerByName() { return this->SceneMgrName; }
bool OgreAPIMediator::SetSceneManagerByRef(Ogre::SceneManager* SceneMgr)
{
	this->SceneMgr = SceneMgr;

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(this->SceneMgr->getName());
	}
	if (SceneMgr == 0)
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}
bool OgreAPIMediator::SetSceneManagerByName(wxString SceneMgrName)
{
	this->SceneMgr = 0;
	this->SceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(SceneMgrName));

	if (this->SceneMgr)
	{
		this->Valid = true;
		this->SceneMgrName = ToWxString(SceneMgrName);
	}
	else
	{
		this->Valid = false;
		this->SceneMgrName = wxString();
	}

	return this->Valid;
}
*/
void OgreAPIMediator::SendSelectionChanged()
{
	/*
	wxCommandEvent event(OViSE_EVT_SELECTION_CHANGED, this->GetId());
	event.SetEventObject(this);
	this->GetEventHandler();
	*/
}
void OgreAPIMediator::SendOgreChanged()
{
	if ( this->OgreChanged )
	{
		wxCommandEvent event(OViSE_EVT_OGRE_CHANGED, this->GetId());
		event.SetEventObject(this);
		this->GetEventHandler()->ProcessEvent(event);
	}
}
void OgreAPIMediator::OnOgreChanged(wxCommandEvent& event)
{
	if(this->Valid)
	{
		this->OgreChanged = false;		
	}
}
// API to Ogre
// Get names of...
/*
wxArrayString OgreAPIMediator::getSceneManagerNames()
{
	wxArrayString AS;
	Ogre::SceneManagerEnumerator::SceneManagerIterator SI = Ogre::Root::getSingletonPtr()->getSceneManagerIterator();
	while(SI.hasMoreElements()) { AS.Add(ToWxString(SI.getNext()->getName())); }
	return AS;
}
// Get pointer
Ogre::Camera* OgreAPIMediator::getCameraPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getCamera(ToOgreString(UniqueNameOfCamera));
}
Ogre::Entity* OgreAPIMediator::getEntityPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getEntity(ToOgreString(UniqueNameOfEntity));
}
Ogre::Light* OgreAPIMediator::getLightPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getLight(ToOgreString(UniqueNameOfLight));
}
Ogre::MovableObject* OgreAPIMediator::getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	if (this->MovableObjectVsTypeRegister.count(UniqueNameOfMovableObject) == 0) return 0;
	else
	{
		OgreEnums::MovableObject::MovableType Type = this->MovableObjectVsTypeRegister[UniqueNameOfMovableObject];
		if (Type < 1) return 0; // Baseclass (0) is absract. It doesn't exits, like Type == Invalid (-1). So Type has to be greather than 1 !
		return SM->getMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetEnumAsString(Type)));
	}
}
Ogre::MovableObject* OgreAPIMediator::getMovableObjectPtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OgreEnums::MovableObject::MovableType Type)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	if (Type < 1) return 0; // Baseclass (0) is absract. It doesn't exits, like Type == Invalid (-1). So Type has to be greather than 1 !
	return SM->getMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetEnumAsString(Type)));
}
Ogre::SceneNode* OgreAPIMediator::getSceneNodePtr(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode)
{
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if (SM == 0) return 0;
	return SM->getSceneNode(ToOgreString(UniqueNameOfSceneNode));
}
Ogre::SceneManager*	OgreAPIMediator::getSceneManagerPtr(wxString UniqueNameOfSceneManager) { return Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(UniqueNameOfSceneManager)); }
// Has objects
bool OgreAPIMediator::hasCamera(wxString UniqueNameOfSceneManager, wxString UniqueNameOfCamera)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isCameraName(UniqueNameOfCamera)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasCamera(ToOgreString(UniqueNameOfCamera));
}
bool OgreAPIMediator::hasEntity(wxString UniqueNameOfSceneManager, wxString UniqueNameOfEntity)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isEntityName(UniqueNameOfEntity)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasEntity(ToOgreString(UniqueNameOfEntity));
}
bool OgreAPIMediator::hasLight(wxString UniqueNameOfSceneManager, wxString UniqueNameOfLight)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isLightName(UniqueNameOfLight)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasLight(ToOgreString(UniqueNameOfLight));
}
bool OgreAPIMediator::hasMovableObject(wxString UniqueNameOfSceneManager, wxString UniqueNameOfMovableObject, OgreEnums::MovableObject::MovableType Type)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	// check name? //TODO
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	
	switch(Type)
	{
		case OgreEnums::MovableObject::MOVABLETYPE_Camera:
			if (!this->hasCamera(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		case OgreEnums::MovableObject::MOVABLETYPE_Entity:
			if (!this->hasEntity(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		case OgreEnums::MovableObject::MOVABLETYPE_Light:
			if (!this->hasLight(UniqueNameOfSceneManager, UniqueNameOfMovableObject)) return false;
			break;

		default: break; // all types not implemented // TODO
	}

	// Now, ever return true ;-)
	return SM->hasMovableObject(ToOgreString(UniqueNameOfMovableObject), ToOgreString(OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetEnumAsString(Type)));
}
bool OgreAPIMediator::hasSceneNode(wxString UniqueNameOfSceneManager, wxString UniqueNameOfSceneNode)
{
	if (!this->hasSceneManager(UniqueNameOfSceneManager)) return false;
	if (!UniqueNameManagerCollection::getSingletonPtr()->isSceneNodeName(UniqueNameOfSceneNode)) return false;
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	return SM->hasSceneNode(ToOgreString(UniqueNameOfSceneNode));
}
bool OgreAPIMediator::hasSceneManager(wxString UniqueNameOfSceneManager)
{
	//if (!UniqueNameManagerCollection::getSingletonPtr()->isEntityName(UniqueNameOfEntity)) return false; // check scene manager // NOT IMPLEMENTED
	Ogre::SceneManager* SM = this->getSceneManagerPtr(UniqueNameOfSceneManager);
	if ( SM == 0 ) return false;
	else return true;
}
// Add objects
Ogre::Camera* OgreAPIMediator::addCamera(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateCameraName(NotUniqueName);

	Ogre::Camera* C = this->SceneMgr->createCamera(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(C);
	else AttachToThisNode->attachObject(C);
	this->MovableObjectVsTypeRegister[UniqueName] = OgreEnums::MovableObject::MOVABLETYPE_Camera;
	this->OgreChanged = true;
	return C;
}
Ogre::Entity* OgreAPIMediator::addEntity(wxString NotUniqueName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateEntityName(NotUniqueName);

	Ogre::Entity* E = this->SceneMgr->createEntity(ToOgreString(UniqueName), ToOgreString(MeshFile));
	if (AttachToThisNode == 0) this->SceneMgr->getRootSceneNode()->attachObject(E);
	else AttachToThisNode->attachObject(E);
	this->MovableObjectVsTypeRegister[UniqueName] = OgreEnums::MovableObject::MOVABLETYPE_Entity;
	this->OgreChanged = true;
	return E;
}
Ogre::Light* OgreAPIMediator::addLight(wxString NotUniqueName, Ogre::SceneNode* AttachToThisNode)
{
	if (!this->Valid) return 0;
	
	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateLightName(NotUniqueName);

	Ogre::Light* L = this->SceneMgr->createLight(ToOgreString(UniqueName));
	if (AttachToThisNode == 0)  this->SceneMgr->getRootSceneNode()->attachObject(L);
	else AttachToThisNode->attachObject(L);
	this->MovableObjectVsTypeRegister[UniqueName] = OgreEnums::MovableObject::MOVABLETYPE_Light;
	this->OgreChanged = true;
	return L;
}
Ogre::SceneNode* OgreAPIMediator::addSceneNode(wxString NotUniqueName, Ogre::SceneNode* ParentNode)
{
	if (!this->Valid) return 0;

	wxString UniqueName = UniqueNameManagerCollection::getSingletonPtr()->AllocateSceneNodeName(NotUniqueName);

	Ogre::SceneNode* NewSN = 0;
	if (ParentNode == 0) NewSN = this->SceneMgr->getRootSceneNode()->createChildSceneNode(ToOgreString(UniqueName));
	else NewSN = ParentNode->createChildSceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return NewSN;
}
*/
// Handling
bool OgreAPIMediator::SetActiveSceneManager(QualifiedName qSceneManager)
{
	if (this->HasSceneManager(qSceneManager))
	{
		this->mActiveSceneManagerPtr = this->GetSceneManagerPtr(qSceneManager);
		this->mActiveSceneManager = qSceneManager;
		return true;
	}
	else return false;
}
QualifiedName OgreAPIMediator::GetActiveSceneManager() { return this->mActiveSceneManager; }
Ogre::RaySceneQuery* OgreAPIMediator::CreateRaySceneQuery(QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create RaySceneQuery
	Ogre::RaySceneQuery* RSQ = SM->createRayQuery(Ogre::Ray());
	if (RSQ == 0) return 0;

	// Store RaySceneQuery
	this->mSceneQuerys[qSceneManager.UniqueName()] = RSQ;

	return RSQ;
}
Ogre::RaySceneQuery* OgreAPIMediator::GetRaySceneQuery(QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;

	// Prepare RaySceneQuery
	Ogre::RaySceneQuery* RSQ = 0;

	// Get RaySceneQuery
	if (this->mSceneQuerys.count(qSceneManager.UniqueName()) != 0)
	{
		RSQ = this->mSceneQuerys[qSceneManager.UniqueName()];
	}

	return RSQ;
}
QualifiedNameCollection OgreAPIMediator::GetQueryObjects(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	QualifiedNameCollection QNames;
	QNames.Clear();

	// Verify OgreAPIMediator
	if (!this->Valid) return QNames;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return QNames;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return QNames;

	// Get Query
	Ogre::RaySceneQuery* Q = this->GetRaySceneQuery(qSceneManager);
	if (Q == 0) return QNames;

	// Prepare RayScan
	Q->setRay(cam->getCameraToViewportRay(screenx, screeny));
	Q->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	Q->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = Q->execute();
	if(RayScanResult.size() != 0)
	{
		for(unsigned long IT = 0; IT < RayScanResult.size(); IT++)
		{
			Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[IT];
			Ogre::MovableObject* MO = RayScanResultEntry.movable;
			QualifiedName*	qMO = this->QuickObjectAccess.GetQualifiedNameOfObject(ToWxString(MO->getName()));
			if (qMO != 0) QNames.Add(*qMO);
		}
	}
	
	return QNames;
}


QualifiedName* OgreAPIMediator::GetQueryFrontObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Get Query
	Ogre::RaySceneQuery* Q = this->GetRaySceneQuery(qSceneManager);
	if (Q == 0) return 0;

	// Prepare RayScan
	Q->setRay(cam->getCameraToViewportRay(screenx, screeny));
	Q->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	Q->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = Q->execute();
	if(RayScanResult.size() != 0)
	{
		Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[0];
		Ogre::MovableObject* MO = RayScanResultEntry.movable;
		return this->QuickObjectAccess.GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return 0;
}
QualifiedName* OgreAPIMediator::GetQueryBackObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Get Query
	Ogre::RaySceneQuery* Q = this->GetRaySceneQuery(qSceneManager);
	if (Q == 0) return 0;

	// Prepare RayScan
	Q->setRay(cam->getCameraToViewportRay(screenx, screeny));
	Q->setQueryMask(~0x01); // Exclude cameras and scene structure mesh
	Q->setSortByDistance(true); // Sort

	// Excecute RayScan
	Ogre::RaySceneQueryResult &RayScanResult = Q->execute();
	if(RayScanResult.size() != 0)
	{
		Ogre::RaySceneQueryResultEntry RayScanResultEntry = RayScanResult[RayScanResult.size()-1];
		Ogre::MovableObject* MO = RayScanResultEntry.movable;
		return this->QuickObjectAccess.GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return 0;
}
// Has objects?
bool OgreAPIMediator::HasCamera(QualifiedName qCamera)
{
	if (this->GetCameraPtr(qCamera) != 0) return true;
	else return false;
}
bool OgreAPIMediator::HasEntity(QualifiedName qEntity)
{
	if (this->GetEntityPtr(qEntity) != 0) return true;
	else return false;
}
bool OgreAPIMediator::HasLight(QualifiedName qLight)
{
	if (this->GetLightPtr(qLight) != 0) return true;
	else return false;
}
bool OgreAPIMediator::HasSceneManager(QualifiedName qSceneManager)
{
	if (this->GetSceneManagerPtr(qSceneManager) != 0) return true;
	else return false;
}
bool OgreAPIMediator::HasSceneNode(QualifiedName qSceneNode)
{
	if (this->GetSceneNodePtr(qSceneNode) != 0) return true;
	else return false;
}
// Get QualifiedName by pointer
QualifiedName OgreAPIMediator::GetQualifiedName(Ogre::Camera* pCamera)
{
	wxString UniqueName = ToWxString(pCamera->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
QualifiedName OgreAPIMediator::GetQualifiedName(Ogre::Entity* pEntity)
{
	wxString UniqueName = ToWxString(pEntity->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
QualifiedName OgreAPIMediator::GetQualifiedName(Ogre::Light* pLight)
{
	wxString UniqueName = ToWxString(pLight->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
QualifiedName OgreAPIMediator::GetQualifiedName(Ogre::SceneManager* pSceneManager)
{
	wxString UniqueName = ToWxString(pSceneManager->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
QualifiedName OgreAPIMediator::GetQualifiedName(Ogre::SceneNode* pSceneNode)
{
	wxString UniqueName = ToWxString(pSceneNode->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
// Get pointer by QualifiedName
Ogre::Camera*		OgreAPIMediator::GetCameraPtr(QualifiedName qCamera)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qCamera
	if (!qCamera.IsValid()) return false;

	// Get Camera and return it (or null)
	return this->QuickObjectAccess.GetCamera(qCamera);
}
Ogre::Entity*		OgreAPIMediator::GetEntityPtr(QualifiedName qEntity)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qEntity
	if (!qEntity.IsValid()) return false;

	// Get Entity and return it (or null)
	return this->QuickObjectAccess.GetEntity(qEntity);
}
Ogre::Light*		OgreAPIMediator::GetLightPtr(QualifiedName qLight)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qLight
	if (!qLight.IsValid()) return false;
	
	// Get Light and return it (or null)
	return this->QuickObjectAccess.GetLight(qLight);
}
Ogre::SceneManager*	OgreAPIMediator::GetSceneManagerPtr(QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return false;

	// Get SceneManager and return it (or null)
	return this->QuickObjectAccess.GetSceneManager(qSceneManager);
}
Ogre::SceneNode*	OgreAPIMediator::GetSceneNodePtr(QualifiedName qSceneNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qSceneNode
	if (!qSceneNode.IsValid()) return false;
	
	// Get SceneNode and return it (or null)
	return this->QuickObjectAccess.GetSceneNode(qSceneNode);
}
// Create objects
QualifiedName* OgreAPIMediator::CreateCamera(wxString Name, Ogre::SceneNode* AttachToThisNode)
{
	return this->CreateCamera(this->mActiveSceneManager, Name, AttachToThisNode);
}
QualifiedName* OgreAPIMediator::CreateEntity(wxString Name, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	return this->CreateEntity(this->mActiveSceneManager, Name, MeshFile, AttachToThisNode);
}
QualifiedName* OgreAPIMediator::CreateLight(wxString Name, Ogre::SceneNode* AttachToThisNode)
{
	return this->CreateLight(this->mActiveSceneManager, Name, AttachToThisNode);
}
QualifiedName* OgreAPIMediator::CreateSceneManager(wxString Name)
{
	return this->CreateSceneManager(Name, Ogre::ST_GENERIC);
}
QualifiedName* OgreAPIMediator::CreateSceneNode(wxString Name, Ogre::SceneNode* ParentNode)
{
	return this->CreateSceneNode(this->mActiveSceneManager, Name, ParentNode);
}
QualifiedName* OgreAPIMediator::CreateCamera(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* AttachToThisNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create QualifiedName of new Ogre::Camera
	QualifiedName qCamera = QualifiedName::Create(Name, "Camera");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->QuickObjectAccess.GetCamera(qCamera) != 0)
		||	(this->QuickObjectAccess.GetAssociatedSceneManager(qCamera) != 0))
	{
		QualifiedName::Destroy(qCamera);
		return 0;
	}

	// Create new Ogre::Camera
	Ogre::Camera* C = SM->createCamera(ToOgreString(qCamera.UniqueName()));

	// Abort if Ogre::Camera is null
	if (C == 0)
	{
		QualifiedName::Destroy(qCamera);
		return 0;
	}

	// Add new Ogre::Camera ObjectManager
	this->QuickObjectAccess.AddCamera(qCamera, C);

	// Add new association between Ogre::Camera and Ogre::SceneManager
	this->QuickObjectAccess.AddAssociatedSceneManager(qSceneManager, qCamera);

	// Attach new Ogre::Camera
	if (AttachToThisNode == 0)  SM->getRootSceneNode()->attachObject(C);
	else AttachToThisNode->attachObject(C);
	
	// Flag Ogre-engine as chanced
	this->OgreChanged = true;
	
	// Return QualifiedName of new Ogre::Camera
	return new QualifiedName(qCamera);
}
QualifiedName* OgreAPIMediator::CreateEntity(QualifiedName qSceneManager, wxString Name, wxString MeshFile, Ogre::SceneNode* AttachToThisNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create QualifiedName of new Ogre::Entity
	QualifiedName qEntity = QualifiedName::Create(Name, "Entity");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->QuickObjectAccess.GetEntity(qEntity) != 0)
		||	(this->QuickObjectAccess.GetAssociatedSceneManager(qEntity) != 0))
	{
		QualifiedName::Destroy(qEntity);
		return 0;
	}

	// Create new Ogre::Entity
	Ogre::Entity* E = SM->createEntity(ToOgreString(qEntity.UniqueName()), ToOgreString(MeshFile));

	// Abort if Ogre::Entity is null
	if (E == 0)
	{
		QualifiedName::Destroy(qEntity);
		return 0;
	}

	// Add new Ogre::Entity ObjectManager
	this->QuickObjectAccess.AddEntity(qEntity, E);

	// Add new association between Ogre::Entity and Ogre::SceneManager
	this->QuickObjectAccess.AddAssociatedSceneManager(qSceneManager, qEntity);

	// Attach new Ogre::Entity
	if (AttachToThisNode == 0)  SM->getRootSceneNode()->attachObject(E);
	else AttachToThisNode->attachObject(E);
	
	// Flag Ogre-engine as chanced
	this->OgreChanged = true;
	
	// Return QualifiedName of new Ogre::Entity
	return new QualifiedName(qEntity);
}
QualifiedName* OgreAPIMediator::CreateLight(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* AttachToThisNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create QualifiedName of new Ogre::Light
	QualifiedName qLight = QualifiedName::Create(Name, "Light");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->QuickObjectAccess.GetLight(qLight) != 0)
		||	(this->QuickObjectAccess.GetAssociatedSceneManager(qLight) != 0))
	{
		QualifiedName::Destroy(qLight);
		return 0;
	}

	// Create new Ogre::Light
	Ogre::Light* L = SM->createLight(ToOgreString(qLight.UniqueName()));

	// Abort if Ogre::Light is null
	if (L == 0)
	{
		QualifiedName::Destroy(qLight);
		return 0;
	}

	// Add new Ogre::Light ObjectManager
	this->QuickObjectAccess.AddLight(qLight, L);

	// Add new association between Ogre::Light and Ogre::SceneManager
	this->QuickObjectAccess.AddAssociatedSceneManager(qSceneManager, qLight);

	// Attach new Ogre::Light
	if (AttachToThisNode == 0)  SM->getRootSceneNode()->attachObject(L);
	else AttachToThisNode->attachObject(L);
	
	// Flag Ogre-engine as chanced
	this->OgreChanged = true;
	
	// Return QualifiedName of new Ogre::Light
	return new QualifiedName(qLight);
}
QualifiedName* OgreAPIMediator::CreateSceneManager(wxString Name, Ogre::SceneType pSceneType)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Create QualifiedName of new Ogre::SceneManager
	QualifiedName qSceneManager = QualifiedName::Create(Name, "SceneManager");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->QuickObjectAccess.GetSceneManager(qSceneManager) != 0)
		||	(this->QuickObjectAccess.GetAssociatedSceneManager(qSceneManager) != 0))
	{
		QualifiedName::Destroy(qSceneManager);
		return 0;
	}

	// Create new Ogre::SceneManager
	Ogre::SceneManager* SM = Ogre::Root::getSingletonPtr()->createSceneManager(pSceneType, ToOgreString(qSceneManager.UniqueName()));

	if (SM == 0)
	{
		QualifiedName::Destroy(qSceneManager);
		return 0;
	}

	// Add new Ogre::Camera ObjectManager
	this->QuickObjectAccess.AddSceneManager(qSceneManager, SM);

	// Add new association between Ogre::SceneManager and Ogre::SceneManager
	this->QuickObjectAccess.AddAssociatedSceneManager(qSceneManager, qSceneManager);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;
	
	// Return QualifiedName of new Ogre::Camera
	return new QualifiedName(qSceneManager);
}
QualifiedName* OgreAPIMediator::CreateSceneNode(QualifiedName qSceneManager, wxString Name, Ogre::SceneNode* ParentNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create QualifiedName of new Ogre::SceneNode
	QualifiedName qSceneNode = QualifiedName::Create(Name, "SceneNode");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->QuickObjectAccess.GetSceneNode(qSceneNode) != 0)
		||	(this->QuickObjectAccess.GetAssociatedSceneManager(qSceneNode) != 0))
	{
		QualifiedName::Destroy(qSceneNode);
		return 0;
	}

	// Create new Ogre::SceneNode
	Ogre::SceneNode* SN;
	if (ParentNode == 0) SN = SM->getRootSceneNode()->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));
	else SN = ParentNode->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));

	// Abort if Ogre::SceneNode is null
	if (SN == 0)
	{
		QualifiedName::Destroy(qSceneNode);
		return 0;
	}

	// Add new Ogre::SceneNode ObjectManager
	this->QuickObjectAccess.AddSceneNode(qSceneNode, SN);

	// Add new association between Ogre::SceneNode and Ogre::SceneManager
	this->QuickObjectAccess.AddAssociatedSceneManager(qSceneManager, qSceneNode);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;
	
	// Return QualifiedName of new Ogre::SceneNode
	return new QualifiedName(qSceneNode);
}
// Destroy objects
bool OgreAPIMediator::DestroySceneManager()
{
	return this->DestroySceneManager(this->mActiveSceneManager);
}
bool OgreAPIMediator::DestroyCamera(QualifiedName qCamera)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qCamera
	if (!qCamera.IsValid()) return false;

	// Get associated qSceneManager
	QualifiedName* qSceneManager = this->QuickObjectAccess.GetAssociatedSceneManager(qCamera);
	if (qSceneManager == 0) return false;

	// Verify qSceneManager
	if (!qSceneManager->IsValid()) return false;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(*qSceneManager);
	if (SM == 0) return false;

	// Get Camera
	Ogre::Camera* C = this->QuickObjectAccess.GetCamera(qCamera);
	if (C == 0) return false;
	
	// Get SceneNode
	Ogre::SceneNode* SN = C->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->QuickObjectAccess.RemoveAssociatedSceneManager(qCamera);
	this->QuickObjectAccess.RemoveCamera(qCamera);

	// Destroy Ogre::Camera
	SN->detachObject(ToOgreString(qCamera.UniqueName()));
	SM->destroyCamera(C);

	// Destroy QualifiedName of Ogre::Camera
	QualifiedName::Destroy(qCamera);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;

	return true;
}
bool OgreAPIMediator::DestroyEntity(QualifiedName qEntity)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qEntity
	if (!qEntity.IsValid()) return false;

	// Get associated qSceneManager
	QualifiedName* qSceneManager = this->QuickObjectAccess.GetAssociatedSceneManager(qEntity);
	if (qSceneManager == 0) return false;

	// Verify qSceneManager
	if (!qSceneManager->IsValid()) return false;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(*qSceneManager);
	if (SM == 0) return false;

	// Get Entity
	Ogre::Entity* C = this->QuickObjectAccess.GetEntity(qEntity);
	if (C == 0) return false;
	
	// Get SceneNode
	Ogre::SceneNode* SN = C->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->QuickObjectAccess.RemoveAssociatedSceneManager(qEntity);
	this->QuickObjectAccess.RemoveEntity(qEntity);

	// Destroy Ogre::Entity
	SN->detachObject(ToOgreString(qEntity.UniqueName()));
	SM->destroyEntity(C);

	// Destroy QualifiedName of Ogre::Entity
	QualifiedName::Destroy(qEntity);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;

	return true;
}
bool OgreAPIMediator::DestroyLight(QualifiedName qLight)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qLight
	if (!qLight.IsValid()) return false;

	// Get associated qSceneManager
	QualifiedName* qSceneManager = this->QuickObjectAccess.GetAssociatedSceneManager(qLight);
	if (qSceneManager == 0) return false;

	// Verify qSceneManager
	if (!qSceneManager->IsValid()) return false;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(*qSceneManager);
	if (SM == 0) return false;

	// Get Light
	Ogre::Light* C = this->QuickObjectAccess.GetLight(qLight);
	if (C == 0) return false;
	
	// Get SceneNode
	Ogre::SceneNode* SN = C->getParentSceneNode();
	if (SN == 0) return false;

	// Remove QualifiedName from ObjectManager
	this->QuickObjectAccess.RemoveAssociatedSceneManager(qLight);
	this->QuickObjectAccess.RemoveLight(qLight);

	// Destroy Ogre::Light
	SN->detachObject(ToOgreString(qLight.UniqueName()));
	SM->destroyLight(C);

	// Destroy QualifiedName of Ogre::Light
	QualifiedName::Destroy(qLight);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;

	return true;
}
bool OgreAPIMediator::DestroySceneManager(QualifiedName qSceneManager)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return false;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(qSceneManager);
	if (SM == 0) return false;

	// Destroy recusive: childnodes
	Ogre::SceneNode* RSN = SM->getRootSceneNode();
	wxString UniqueName = ToWxString(RSN->getName());
	QualifiedName qRootSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	if (qRootSceneNode.IsValid()) this->DestroySceneNode(qRootSceneNode);

	// Movable objects are destroy implicit!

	// Remove QualifiedName from ObjectManager
	this->QuickObjectAccess.RemoveAssociatedSceneManager(qSceneManager);
	this->QuickObjectAccess.RemoveSceneManager(qSceneManager);

	// Destroy Ogre::Camera
	Ogre::Root::getSingletonPtr()->destroySceneManager(SM);

	// Destroy QualifiedName of Ogre::Camera
	QualifiedName::Destroy(qSceneManager);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;

	return true;
}
bool OgreAPIMediator::DestroySceneNode(QualifiedName qSceneNode)
{
	// Verify OgreAPIMediator
	if (!this->Valid) return false;

	// Verify qSceneNode
	if (!qSceneNode.IsValid()) return false;

	// Get associated qSceneManager
	QualifiedName* qSceneManager = this->QuickObjectAccess.GetAssociatedSceneManager(qSceneNode);
	if (qSceneManager == 0) return false;

	// Verify qSceneManager
	if (!qSceneManager->IsValid()) return false;

	// Get SceneManager
	Ogre::SceneManager* SM = this->QuickObjectAccess.GetSceneManager(*qSceneManager);
	if (SM == 0) return false;

	// Get SceneNode
	Ogre::SceneNode* SN = this->QuickObjectAccess.GetSceneNode(qSceneNode);
	if (SN == 0) return false;

	// Destroy recusive: childnodes
	Ogre::SceneNode::ChildNodeIterator IT_ChildSN = SN->getChildIterator();
	while(IT_ChildSN.hasMoreElements())
	{
		Ogre::SceneNode* SN_Child = (Ogre::SceneNode*)IT_ChildSN.getNext();
		wxString UniqueName = ToWxString(SN_Child->getName());
		QualifiedName qChildSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		if (qChildSceneNode.IsValid()) this->DestroySceneNode(qChildSceneNode);
	}

	// Destroy recusive: movable objects
	Ogre::SceneNode::ObjectIterator IT_MobObj = SN->getAttachedObjectIterator();
	while(IT_MobObj.hasMoreElements())
	{
		Ogre::MovableObject* MO = IT_MobObj.getNext();
		wxString UniqueName = ToWxString(MO->getName());
		QualifiedName qMovableObject = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		if (qMovableObject.IsValid())
		{
			SM->destroyMovableObject(MO);

			// Remove QualifiedName from ObjectManager
			this->QuickObjectAccess.RemoveAssociatedSceneManager(qMovableObject);
			this->QuickObjectAccess.RemoveMovableObject(qSceneNode);

			QualifiedName::Destroy(qMovableObject);
		}
	}

	// Remove QualifiedName from ObjectManager
	this->QuickObjectAccess.RemoveAssociatedSceneManager(qSceneNode);
	this->QuickObjectAccess.RemoveSceneNode(qSceneNode);

	// Destroy Ogre::Camera
	SM->destroySceneNode(SN);

	// Destroy QualifiedName of Ogre::Camera
	QualifiedName::Destroy(qSceneNode);

	// Flag Ogre-engine as chanced
	this->OgreChanged = true;

	return true;
}

// General
void OgreAPIMediator::DynamicShadows(bool state)
{
	if(state) this->mActiveSceneManagerPtr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	else this->mActiveSceneManagerPtr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}

// Remove objects
/*
bool OgreAPIMediator::removeCamera(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasCamera(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateCameraName(UniqueName);

	Ogre::Camera* C = this->SceneMgr->getCamera(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = C->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyCamera(C);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeEntity(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasEntity(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateEntityName(UniqueName);
	Ogre::Entity* E = this->SceneMgr->getEntity(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = E->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyEntity(E);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeLight(wxString UniqueName)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasLight(ToOgreString(UniqueName))) return false;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateLightName(UniqueName);

	Ogre::Light* L = this->SceneMgr->getLight(ToOgreString(UniqueName));
	Ogre::SceneNode* SN = L->getParentSceneNode();
	SN->detachObject(ToOgreString(UniqueName));
	this->SceneMgr->destroyLight(L);
	this->MovableObjectVsTypeRegister.erase(UniqueName);
	this->OgreChanged = true;
	return true;
}
bool OgreAPIMediator::removeSceneNode(wxString UniqueName, bool RemoveRecursive)
{
	if (!this->Valid) return false;
	if (!this->SceneMgr->hasSceneNode(ToOgreString(UniqueName))) return false;

	if (RemoveRecursive) ; // Not implemented yet. // TODO
	else ;

	UniqueNameManagerCollection::getSingletonPtr()->DeallocateSceneNodeName(UniqueName);

	this->SceneMgr->destroySceneNode(ToOgreString(UniqueName));
	this->OgreChanged = true;
	return true;
}
*/
/*
bool OViSESelection::AddMovableObject(Ogre::MovableObject* pMovableObject)
{
	// Stop, if pMovableObject is null
	if ( pMovableObject == 0 ) return false;

	// Get SceneManager by name
	Ogre::SceneManager* TempSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->SceneManagerName));

	// Stop, if no SceneManager has been found
	if (TempSceneMgr == 0) return false;

	// Get characteristics of pMovableObject
	wxString TempMovableObjectName = ToWxString(pMovableObject->getName());
	wxString TempMovableTypeName = this->mEnumTranslator.getMovableObjectAsString(pMovableObject);
	OViSEOgreEnums::MovableObject::MovableType TempMovableTypeEnum = this->mEnumTranslator.getMovableObjectAsEnum(pMovableObject);
	
	// Stop, if SceneManager doesn't contain pMovableObject
	if (!TempSceneMgr->hasMovableObject(ToOgreString(TempMovableObjectName), ToOgreString(TempMovableTypeName))) return false;

	bool FlagBad = false;

	// Add pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject can not indentified or is already in selection
	switch(TempMovableTypeEnum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:
			if ( this->SelectedBillboardChains.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedBillboardChains[TempMovableObjectName] = (Ogre::BillboardChain*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet:
			if ( this->SelectedBillboardSets.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedBillboardSets[TempMovableObjectName] = (Ogre::BillboardSet*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			if ( this->SelectedCameras.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedCameras[TempMovableObjectName] = (Ogre::Camera*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			if ( this->SelectedEntities.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedEntities[TempMovableObjectName] = (Ogre::Entity*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum:
			if ( this->SelectedFrustums.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedFrustums[TempMovableObjectName] = (Ogre::Frustum*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance:
			if ( this->SelectedInstancedGeometryBatchInstances.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedInstancedGeometryBatchInstances[TempMovableObjectName] = (Ogre::InstancedGeometry::BatchInstance*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			if ( this->SelectedLights.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedLights[TempMovableObjectName] = (Ogre::Light*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject:
			if ( this->SelectedManualObjects.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedManualObjects[TempMovableObjectName] = (Ogre::ManualObject*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane:
			if ( this->SelectedMovablePlanes.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedMovablePlanes[TempMovableObjectName] = (Ogre::MovablePlane*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:
			if ( this->SelectedParticleSystems.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedParticleSystems[TempMovableObjectName] = (Ogre::ParticleSystem*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:
			if ( this->SelectedRibbonTrails.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedRibbonTrails[TempMovableObjectName] = (Ogre::RibbonTrail*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:
			if ( this->SelectedSimpleRenderables.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedSimpleRenderables[TempMovableObjectName] = (Ogre::SimpleRenderable*) pMovableObject;
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:
			if ( this->SelectedStaticGeometryRegions.count( TempMovableObjectName ) == 1 ) FlagBad = true;
			else this->SelectedStaticGeometryRegions[TempMovableObjectName] = (Ogre::StaticGeometry::Region*) pMovableObject;
			break;

		default: // Stop, if MovableType of pMovableObject can not indetified/is not valid (important)
			FlagBad = true;
			break;
	}

	// Add pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject is already in Selection
	if ( this->SelectedMovableObjects.count(TempMovableObjectName) == 1 ) FlagBad = true;
	else this->SelectedMovableObjects[TempMovableObjectName] = pMovableObject;

	// Result of activities: return false, but inhomogen container-contents are repaired automatically.
	if ( FlagBad ) return false; 
	else return true;
}
bool OViSESelection::RemoveMovableObject(Ogre::MovableObject* pMovableObject)
{
	// Stop, if pMovableObject is null
	if ( pMovableObject == 0 ) return false;

	// Get SceneManager by name
	Ogre::SceneManager* TempSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(this->SceneManagerName));

	// Stop, if no SceneManager has been found
	if (TempSceneMgr == 0) return false;

	// Get characteristics of pMovableObject
	wxString TempMovableObjectName = ToWxString(pMovableObject->getName());
	wxString TempMovableTypeName = this->mEnumTranslator.getMovableObjectAsString(pMovableObject);
	OViSEOgreEnums::MovableObject::MovableType TempMovableTypeEnum = this->mEnumTranslator.getMovableObjectAsEnum(pMovableObject);
	
	// Stop, if SceneManager doesn't contain pMovableObject
	if (!TempSceneMgr->hasMovableObject(ToOgreString(TempMovableObjectName), ToOgreString(TempMovableTypeName))) return false;

	bool FlagBad = false;

	// Remove pMovableObject from SelectedMovableObjects. Move forward, if pMovableObject is not in Selection
	if ( this->SelectedMovableObjects.count(TempMovableObjectName) == 1) this->SelectedMovableObjects.erase(TempMovableObjectName);
	else FlagBad = true;

	// Remove pMovableObject to SelectedMovableObjects. Flag bad activity, if pMovableObject can not indentified 
	switch(TempMovableTypeEnum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:
			if ( this->SelectedBillboardChains.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedBillboardChains.erase(TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet:
			if ( this->SelectedBillboardSets.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedBillboardSets.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			if ( this->SelectedCameras.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedCameras.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			if ( this->SelectedEntities.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedEntities.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum:
			if ( this->SelectedFrustums.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedFrustums.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance:
			if ( this->SelectedInstancedGeometryBatchInstances.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedInstancedGeometryBatchInstances.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			if ( this->SelectedLights.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedLights.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject:
			if ( this->SelectedManualObjects.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedManualObjects.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane:
			if ( this->SelectedMovablePlanes.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedMovablePlanes.erase(TempMovableObjectName);
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:
			if ( this->SelectedParticleSystems.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedParticleSystems.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:
			if ( this->SelectedRibbonTrails.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedRibbonTrails.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:
			if ( this->SelectedSimpleRenderables.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedSimpleRenderables.erase( TempMovableObjectName );
			break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:
			if ( this->SelectedStaticGeometryRegions.count( TempMovableObjectName ) == 0 ) FlagBad = true;
			else this->SelectedStaticGeometryRegions.erase( TempMovableObjectName );
			break;

		default: // Stop, if MovableType of pMovableObject can not indetified/is not valid (important)
			FlagBad = true;
			break;
	}
	
	if ( FlagBad ) return false;
	else return true;
}
void OViSESelection::RemoveAll()
{
	this->SelectedMovableObjects.clear();

	this->SelectedBillboardChains.clear();
	this->SelectedBillboardSets.clear();
	this->SelectedCameras.clear();
	this->SelectedEntities.clear();
	this->SelectedFrustums.clear();
	this->SelectedInstancedGeometryBatchInstances.clear();
	this->SelectedLights.clear();
	this->SelectedManualObjects.clear();
	this->SelectedMovablePlanes.clear();
	this->SelectedParticleSystems.clear();
	this->SelectedRibbonTrails.clear();
	this->SelectedSimpleRenderables.clear();
	this->SelectedStaticGeometryRegions.clear();
}

OViSESelection::OViSESelection(wxString SceneManagerName)
{
	this->UniqueName = ToWxString("INVALID");
	this->SceneManagerName = SceneManagerName;
}
OViSESelection::OViSESelection(Ogre::SceneManager* pSceneManager)
{
	this->UniqueName = ToWxString("INVALID");
	this->SceneManagerName = ToWxString(pSceneManager->getName());
}
OViSESelection::~OViSESelection(void) { this->SelectedMovableObjects.clear(); }
*/