#include "../OgreMediator/OgreMediator.h"

DEFINE_EVENT_TYPE(OViSE_EVT_OGRE_CHANGED)

// Singleton
OgreMediator* OgreMediator::instance = 0;

OgreMediator* OgreMediator::GetSingletonPtr()
{
	if (OgreMediator::instance == 0) OgreMediator::instance = new OgreMediator();
	return OgreMediator::instance;
}
OgreMediator::OgreMediator()
{
	this->Connect(OViSE_EVT_OGRE_CHANGED, wxCommandEventHandler( OgreMediator::OnOgreChanged ), NULL, this);

	this->Valid = true;

	this->mObjectAccess = new ObjectManager();

	this->iCamera = CameraInterface(this->mObjectAccess);
	this->iEntity = EntityInterface(this->mObjectAccess);
	this->iLight = LightInterface(this->mObjectAccess);
	this->iMovableObject = MovableObjectInterface(this->mObjectAccess);
	this->iSceneNode = SceneNodeInterface(&(this->iMovableObject), this->mObjectAccess);
	this->iSceneManager = SceneManagerInterface(&(this->iSceneNode), this->mObjectAccess);

	// Create default SceneManager
	this->mDefaultSceneManager = this->iSceneManager.Create(ToWxString("Default"));

	// Set it as ActiveSceneManager
	this->iSceneManager.SetActiveSceneManager(this->mDefaultSceneManager);

	// Create and store RaySceneQuery
	this->CreateRaySceneQuery(this->mDefaultSceneManager);

	this->mOgreChanged = false;
}
OgreMediator::~OgreMediator(void) { this->iSceneManager.Destroy(this->mDefaultSceneManager); }
// General
bool OgreMediator::IsValid() { return this->Valid; }

void OgreMediator::SendSelectionChanged()
{
	/*
	wxCommandEvent event(OViSE_EVT_SELECTION_CHANGED, this->GetId());
	event.SetEventObject(this);
	this->GetEventHandler();
	*/
}
void OgreMediator::SendOgreChanged()
{
	if ( this->mOgreChanged )
	{
		wxCommandEvent event(OViSE_EVT_OGRE_CHANGED, this->GetId());
		event.SetEventObject(this);
		this->GetEventHandler()->ProcessEvent(event);
	}
}
void OgreMediator::OnOgreChanged(wxCommandEvent& event)
{
	if(this->Valid)
	{
		this->mOgreChanged = false;		
	}
}
Ogre::RaySceneQuery* OgreMediator::CreateRaySceneQuery(QualifiedName qSceneManager)
{
	// Verify OgreMediator
	if (!this->Valid) return 0;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return 0;
	
	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);
	if (SM == 0) return 0;

	// Create RaySceneQuery
	Ogre::RaySceneQuery* RSQ = SM->createRayQuery(Ogre::Ray());
	if (RSQ == 0) return 0;

	// Store RaySceneQuery
	this->mSceneQuerys[qSceneManager.UniqueName()] = RSQ;

	return RSQ;
}
Ogre::RaySceneQuery* OgreMediator::GetRaySceneQuery(QualifiedName qSceneManager)
{
	// Verify OgreMediator
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
QualifiedNameCollection OgreMediator::GetQueryObjects(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	QualifiedNameCollection QNames;
	QNames.Clear();

	// Verify OgreMediator
	if (!this->Valid) return QNames;

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return QNames;

	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);
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
			QualifiedName qMO = this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
			if (qMO.IsValid()) QNames.Add(qMO);
		}
	}
	
	return QNames;
}
QualifiedName OgreMediator::GetQueryFrontObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	// Verify OgreMediator
	if (!this->Valid) return QualifiedName();

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return QualifiedName();

	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);
	if (SM == 0) return QualifiedName();

	// Get Query
	Ogre::RaySceneQuery* Q = this->GetRaySceneQuery(qSceneManager);
	if (Q == 0) return QualifiedName();

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
		return this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return QualifiedName();
}
QualifiedName OgreMediator::GetQueryBackObject(float screenx, float screeny, Ogre::Camera *cam, QualifiedName qSceneManager)
{
	// Verify OgreMediator
	if (!this->Valid) return QualifiedName();

	// Verify qSceneManager
	if (!qSceneManager.IsValid()) return QualifiedName();

	// Get SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);
	if (SM == 0) return QualifiedName();

	// Get Query
	Ogre::RaySceneQuery* Q = this->GetRaySceneQuery(qSceneManager);
	if (Q == 0) return QualifiedName();

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
		return this->mObjectAccess->GetQualifiedNameOfObject(ToWxString(MO->getName()));
	}
	else return QualifiedName();
}

// General
void OgreMediator::DynamicShadows(bool state)
{
	if(state) this->mActiveSceneManagerPtr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	else this->mActiveSceneManagerPtr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
}

