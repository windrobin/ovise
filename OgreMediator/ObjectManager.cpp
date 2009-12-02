#include "../OgreMediator/ObjectManager.h"

ObjectManager::ObjectManager(void) { }
ObjectManager::~ObjectManager(void)
{
	this->mQNames.clear();

	this->mAssociatedSceneManagers.clear();

	this->mCameras.clear();
	this->mEntities.clear();
	this->mLights.clear();
	this->mSceneManagers.clear();
	this->mSceneNodes.clear();
}
// General
QualifiedName ObjectManager::GetQualifiedNameOfObject(wxString UniqueName)
{
	QualifiedName QName;

	if (this->mQNames.count(UniqueName) != 0)
	{
		QName = this->mQNames[UniqueName];
	}
	return QName;
}

bool ObjectManager::RemoveUnidentifiedObject(QualifiedName QName)
{
	if (this->RemoveMovableObject(QName)) return true;

	if (this->RemoveSceneManager(QName)) return true;
	if (this->RemoveSceneNode(QName)) return true;

	return false;
}
// Accociadted SceneManager
bool ObjectManager::AddAssociatedSceneManager(QualifiedName qSceneManager, QualifiedName qObject)
{
	if (this->mAssociatedSceneManagers.count(qObject.UniqueName()) != 0)
	{
		return false;
	}
	else
	{
		this->mAssociatedSceneManagers[qObject.UniqueName()] = qSceneManager;
		return true;
	}
}
bool ObjectManager::RemoveAssociatedSceneManager(QualifiedName qObject)
{
	if (this->mAssociatedSceneManagers.count(qObject.UniqueName()) == 0)
	{
		return false;
	}
	else
	{
		this->mAssociatedSceneManagers.erase(qObject.UniqueName());
		return true;
	}
}
QualifiedName ObjectManager::GetAssociatedSceneManager(QualifiedName qObject)
{
	if (this->mAssociatedSceneManagers.count(qObject.UniqueName()) == 0) return QualifiedName();
	else return this->mAssociatedSceneManagers[qObject.UniqueName()];
}
// Ogre::Camera
bool ObjectManager::AddCamera(QualifiedName QName, Ogre::Camera* pCamera)
{
	// Verify Ogre::Camera
	if (pCamera == 0) return false;

	// Verify QualifiedName
	if (!QName.IsValid()) return false;

	// Verify QualifiedName is not already used 
	if (this->mQNames.count(QName.UniqueName()) != 0) return false;

	// Everything OK, store QualifiedName and Ogre::Camera
	this->mQNames[QName.UniqueName()] = QName;
	this->mCameras[QName.UniqueName()] = pCamera;
	this->mMovableTypeEnums[QName.UniqueName()] = OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetMovableObjectAsEnum(pCamera);

	return true;
}
bool ObjectManager::RemoveCamera(QualifiedName QName)
{
	// An invalid QualifiedName must be allowed to remove objects anyway!

	// Verify QualifiedName is used, then erase QualifiedName
	if (this->mQNames.count(QName.UniqueName()) != 1) return false;

	// Verify QualifiedName is used, then erase Ogre::Camera
	if (this->mCameras.count(QName.UniqueName()) != 1) return false;	

	// Remove QName from ObjectManager
	this->mQNames.erase(QName.UniqueName());
	this->mCameras.erase(QName.UniqueName());
	this->mMovableTypeEnums.erase(QName.UniqueName());

	return true;
}
Ogre::Camera* ObjectManager::GetCamera(QualifiedName QName)
{
	if (this->mCameras.count(QName.UniqueName()) == 0) return 0;
	else return this->mCameras[QName.UniqueName()];
}
QualifiedNameCollection ObjectManager::GetCameras()
{
	QualifiedNameCollection QNames;

	if (!this->mCameras.empty())
	{
		for (CameraHashMap::iterator IT = this->mCameras.begin(); IT != this->mCameras.end(); IT++)
		{
			wxString UniqueName = IT->first;
			QNames.Add(this->mQNames[UniqueName]);
		}
	}

	return QNames;
}
// Ogre::Entity
bool ObjectManager::AddEntity(QualifiedName QName, Ogre::Entity* pEntity)
{
	// Verify Ogre::Entity
	if (pEntity == 0) return false;

	// Verify QualifiedName
	if (!QName.IsValid()) return false;

	// Verify QualifiedName is not already used 
	if (this->mQNames.count(QName.UniqueName()) != 0) return false;

	// Everything OK, store QualifiedName and Ogre::Entity
	this->mQNames[QName.UniqueName()] = QName;
	this->mEntities[QName.UniqueName()] = pEntity;
	this->mMovableTypeEnums[QName.UniqueName()] = OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetMovableObjectAsEnum(pEntity);

	return true;
}
bool ObjectManager::RemoveEntity(QualifiedName QName)
{
	// An invalid QualifiedName must be allowed to remove objects anyway!

	// Verify QualifiedName is used, then erase QualifiedName
	if (this->mQNames.count(QName.UniqueName()) != 1) return false;

	// Verify QualifiedName is used, then erase Ogre::Entity
	if (this->mEntities.count(QName.UniqueName()) != 1) return false;	

	// Remove QName from ObjectManager
	this->mQNames.erase(QName.UniqueName());
	this->mEntities.erase(QName.UniqueName());
	this->mMovableTypeEnums.erase(QName.UniqueName());

	return true;
}
Ogre::Entity* ObjectManager::GetEntity(QualifiedName QName)
{
	if (this->mEntities.count(QName.UniqueName()) == 0) return 0;
	else return this->mEntities[QName.UniqueName()];
}
QualifiedNameCollection ObjectManager::GetEntities()
{
	QualifiedNameCollection QNames;

	if (!this->mEntities.empty())
	{
		for (EntityHashMap::iterator IT = this->mEntities.begin(); IT != this->mEntities.end(); IT++)
		{
			wxString UniqueName = IT->first;
			QNames.Add(this->mQNames[UniqueName]);
		}
	}

	return QNames;
}
// Ogre::Light
bool ObjectManager::AddLight(QualifiedName QName, Ogre::Light* pLight)
{
	// Verify Ogre::Light
	if (pLight == 0) return false;

	// Verify QualifiedName
	if (!QName.IsValid()) return false;

	// Verify QualifiedName is not already used 
	if (this->mQNames.count(QName.UniqueName()) != 0) return false;

	// Everything OK, store QualifiedName and Ogre::Light
	this->mQNames[QName.UniqueName()] = QName;
	this->mLights[QName.UniqueName()] = pLight;
	this->mMovableTypeEnums[QName.UniqueName()] = OgreEnums::MovableTypeTranslator::GetSingletonPtr()->GetMovableObjectAsEnum(pLight);

	return true;
}
bool ObjectManager::RemoveLight(QualifiedName QName)
{
	// An invalid QualifiedName must be allowed to remove objects anyway!

	// Verify QualifiedName is used, then erase QualifiedName
	if (this->mQNames.count(QName.UniqueName()) != 1) return false;

	// Verify QualifiedName is used, then erase Ogre::Light
	if (this->mLights.count(QName.UniqueName()) != 1) return false;	

	// Remove QName from ObjectManager
	this->mQNames.erase(QName.UniqueName());
	this->mLights.erase(QName.UniqueName());
	this->mMovableTypeEnums.erase(QName.UniqueName());

	return true;
}
Ogre::Light* ObjectManager::GetLight(QualifiedName QName)
{
	if (this->mLights.count(QName.UniqueName()) == 0) return 0;
	else return this->mLights[QName.UniqueName()];
}
QualifiedNameCollection ObjectManager::GetLights()
{
	QualifiedNameCollection QNames;

	if (!this->mLights.empty())
	{
		for (LightHashMap::iterator IT = this->mLights.begin(); IT != this->mLights.end(); IT++)
		{
			wxString UniqueName = IT->first;
			QNames.Add(this->mQNames[UniqueName]);
		}
	}

	return QNames;
}
// Ogre::SceneManager
bool ObjectManager::AddSceneManager(QualifiedName QName, Ogre::SceneManager* pSceneManager)
{
	// Verify Ogre::SceneManager
	if (pSceneManager == 0) return false;

	// Verify QualifiedName
	if (!QName.IsValid()) return false;

	// Verify QualifiedName is not already used 
	if (this->mQNames.count(QName.UniqueName()) != 0) return false;

	// Everything OK, store QualifiedName and Ogre::SceneManager
	this->mQNames[QName.UniqueName()] = QName;
	this->mSceneManagers[QName.UniqueName()] = pSceneManager;
	this->mMovableTypeEnums[QName.UniqueName()] = OgreEnums::MovableObject::MOVABLETYPE_Invalid;

	return true;
}
bool ObjectManager::RemoveSceneManager(QualifiedName QName)
{
	// An invalid QualifiedName must be allowed to remove objects anyway!

	// Verify QualifiedName is used, then erase QualifiedName
	if (this->mQNames.count(QName.UniqueName()) != 1) return false;

	// Verify QualifiedName is used, then erase Ogre::SceneManager
	if (this->mSceneManagers.count(QName.UniqueName()) != 1) return false;	
	
	// Remove QName from ObjectManager
	this->mQNames.erase(QName.UniqueName());
	this->mSceneManagers.erase(QName.UniqueName());
	this->mMovableTypeEnums.erase(QName.UniqueName());

	return true;
}
Ogre::SceneManager*	ObjectManager::GetSceneManager(QualifiedName QName)
{
	if (this->mSceneManagers.count(QName.UniqueName()) == 0) return 0;
	else return this->mSceneManagers[QName.UniqueName()];
}
QualifiedNameCollection ObjectManager::GetSceneManagers()
{
	QualifiedNameCollection QNames;

	if (!this->mSceneManagers.empty())
	{
		for (SceneManagerHashMap::iterator IT = this->mSceneManagers.begin(); IT != this->mSceneManagers.end(); IT++)
		{
			wxString UniqueName = IT->first;
			QNames.Add(this->mQNames[UniqueName]);
		}
	}

	return QNames;
}
// Ogre::SceneNode
bool ObjectManager::AddSceneNode(QualifiedName QName, Ogre::SceneNode* pSceneNode)
{
	// Verify Ogre::SceneNode
	if (pSceneNode == 0) return false;

	// Verify QualifiedName
	if (!QName.IsValid()) return false;

	// Verify QualifiedName is not already used 
	if (this->mQNames.count(QName.UniqueName()) != 0) return false;

	// Everything OK, store QualifiedName and Ogre::SceneNode
	this->mQNames[QName.UniqueName()] = QName;
	this->mSceneNodes[QName.UniqueName()] = pSceneNode;
	this->mMovableTypeEnums[QName.UniqueName()] = OgreEnums::MovableObject::MOVABLETYPE_Invalid;

	return true;
}
bool ObjectManager::RemoveSceneNode(QualifiedName QName)
{
	// An invalid QualifiedName must be allowed to remove objects anyway!

	// Verify QualifiedName is used, then erase QualifiedName
	if (this->mQNames.count(QName.UniqueName()) != 1) return false;

	// Verify QualifiedName is used, then erase Ogre::SceneNode
	if (this->mSceneNodes.count(QName.UniqueName()) != 1) return false;	
	
	// Remove QName from ObjectManager
	this->mQNames.erase(QName.UniqueName());
	this->mSceneNodes.erase(QName.UniqueName());
	this->mMovableTypeEnums.erase(QName.UniqueName());

	return true;
}
Ogre::SceneNode* ObjectManager::GetSceneNode(QualifiedName QName)
{
	if (this->mSceneNodes.count(QName.UniqueName()) == 0) return 0;
	else return this->mSceneNodes[QName.UniqueName()];
}
QualifiedNameCollection ObjectManager::GetSceneNodes()
{
	QualifiedNameCollection QNames;

	if (!this->mSceneNodes.empty())
	{
		for (SceneNodeHashMap::iterator IT = this->mSceneNodes.begin(); IT != this->mSceneNodes.end(); IT++)
		{
			wxString UniqueName = IT->first;
			QNames.Add(this->mQNames[UniqueName]);
		}
	}

	return QNames;
}

// Ogre::MovableObject (abtract)
bool ObjectManager::RemoveMovableObject(QualifiedName QName)
{
	if (this->RemoveCamera(QName)) return true;
	if (this->RemoveEntity(QName)) return true;
	if (this->RemoveLight(QName)) return true;

	return false;
}
Ogre::MovableObject* ObjectManager::GetMovableObject(QualifiedName QName)
{
	if ( !QName.IsValid() ) return 0;

	Ogre::MovableObject* MO = 0;

	switch(this->GetMovableType(QName))
	{
	case OgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:			break;
	case OgreEnums::MovableObject::MOVABLETYPE_BillboardSet:			break;
	case OgreEnums::MovableObject::MOVABLETYPE_Camera:					MO = this->GetCamera(QName); break;
	case OgreEnums::MovableObject::MOVABLETYPE_Entity:					MO = this->GetEntity(QName); break;
	case OgreEnums::MovableObject::MOVABLETYPE_Frustum:					break;
	case OgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance: break;
	case OgreEnums::MovableObject::MOVABLETYPE_Light:					MO = this->GetLight(QName); break;
	case OgreEnums::MovableObject::MOVABLETYPE_ManualObject:			break;
	case OgreEnums::MovableObject::MOVABLETYPE_MovablePlane:			break;
	case OgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:			break;
	case OgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:				break;
	case OgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:		break;
	case OgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:	break;
	default: break;
	}
	return MO;
}
OgreEnums::MovableObject::MovableType ObjectManager::GetMovableType(QualifiedName QName)
{
	if (this->mMovableTypeEnums.count(QName.UniqueName()) == 1) return this->mMovableTypeEnums[QName.UniqueName()];
	else return OgreEnums::MovableObject::MOVABLETYPE_Invalid;
}
// NEW
bool ObjectManager::SetActiveSceneManager(QualifiedName qSceneManager)
{
	if ( !qSceneManager.IsValid() ) return false;
	if ( this->GetSceneManager(qSceneManager) == 0 ) return false;

	this->mActiveSceneManager = qSceneManager;
	return true;
}
QualifiedName ObjectManager::GetActiveSceneManager() { return this->mActiveSceneManager; }