#pragma once

#include "../OgreMediator/MediatorInterface.h"
#include "../OgreMediator/MovableObjectInterface.h"
#include "../ImprovedEventHandling/EventPublisherInterface.h"

class SceneNodeInterface :
	public MediatorInterface,
	public EventPublisherInterface
{
private:
	MovableObjectInterface*	iMovableObject;

public:
	// De- & Constructors, individual
	SceneNodeInterface(MovableObjectInterface* iMovableObject = 0, ObjectManager* ObjMgr = 0);
	virtual ~SceneNodeInterface(void);

	// Methods, inherited and overwritten
	QualifiedName		Create(wxString Name);
	bool				Destroy(QualifiedName qName);
	bool				Exist(QualifiedName qName);
	bool				IsValid();

	// Methods, individual
	QualifiedName		Create(wxString Name, QualifiedName qParentSceneNode);
	QualifiedName		Create(wxString Name, Ogre::SceneNode* pParentSceneNode);
	QualifiedName		GetName(Ogre::SceneNode* pSceneNode);
	Ogre::SceneNode*	GetPtr(QualifiedName qSceneNode);

	// Methods, individual, configuration
	bool				SetMovableObjectInterface(MovableObjectInterface* iMovableObject);

	// Methods, individual wrapper of Ogre-methods
	Ogre::Vector3		GetPosition(QualifiedName qName);
	bool				SetPosition(QualifiedName qName, Ogre::Vector3 &P);
	bool				SetPosition(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z);
	bool				TranslateRelative(QualifiedName qName, Ogre::Vector3 &T);
	bool				TranslateRelative(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z);

	Ogre::Quaternion	GetOrientation(QualifiedName qName);
	bool				SetOrientation(QualifiedName qName, Ogre::Quaternion &Q);
	bool				SetOrientation(QualifiedName qName, Ogre::Real W, Ogre::Real X, Ogre::Real Y, Ogre::Real Z);
	bool				SetOrientation(QualifiedName qName, Ogre::Degree Roll, Ogre::Degree Pitch, Ogre::Degree Yaw);
	bool				RotateRelative(QualifiedName qName, Ogre::Quaternion &Qrelative);
	bool				RotateRelative(QualifiedName qName, Ogre::Degree Roll, Ogre::Degree Pitch, Ogre::Degree Yaw);

	Ogre::Vector3		GetScale(QualifiedName qName);
	bool				SetScale(QualifiedName qName, Ogre::Vector3 &S);
	bool				SetScale(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z);
	bool				ScaleRelative(QualifiedName qName, Ogre::Vector3 &Srelative);
	bool				ScaleRelative(QualifiedName qName, Ogre::Real Xrelative, Ogre::Real Yrelative, Ogre::Real Zrelative);

	bool				GetShowBoundingBox(QualifiedName qName);
	bool				SetShowBoundingBox(QualifiedName qName, bool ShowBoundingBox);
};
