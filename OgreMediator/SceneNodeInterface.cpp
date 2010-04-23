#include "../OgreMediator/SceneNodeInterface.h"

// De- & Constructors, individual
SceneNodeInterface::SceneNodeInterface(MovableObjectInterface* iMovableObject, ObjectManager* ObjMgr) : MediatorInterface(ObjMgr) { this->SetMovableObjectInterface(iMovableObject); }
SceneNodeInterface::~SceneNodeInterface(void) { }
// Methods, inherited and overwritten
QualifiedName SceneNodeInterface::Create(wxString Name)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();
	
	// Get RootSceneNode
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());
	Ogre::SceneNode* RSN = SM->getRootSceneNode();

	// Forward & Return
	return this->Create(Name, RSN);
}
bool SceneNodeInterface::Destroy(QualifiedName qName)
{
	// Validate given QualifiedName of Ogre::SceneNode
	if ( !this->Exist(qName) ) return false;

	// Get SceneManager
	QualifiedName qSceneManager = this->mObjectAccess->GetAssociatedSceneManager(qName);

	// Validate qSceneManager
	if ( !qSceneManager.IsValid() ) return false;

	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(qSceneManager);

	// Get SceneNode
	Ogre::SceneNode* SN = this->mObjectAccess->GetSceneNode(qName);

	// Destroy recusive: childnodes
	Ogre::SceneNode::ChildNodeIterator IT_ChildSN = SN->getChildIterator();
	while(IT_ChildSN.hasMoreElements())
	{
		Ogre::SceneNode* SN_Child = (Ogre::SceneNode*)IT_ChildSN.getNext();
		wxString UniqueName = ToWxString(SN_Child->getName());
		QualifiedName qChildSceneNode = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		this->Destroy(qChildSceneNode);
	}

	// Destroy recusive: movable objects
	Ogre::SceneNode::ObjectIterator IT_MovObj = SN->getAttachedObjectIterator();
	while(IT_MovObj.hasMoreElements())
	{
		// Get Ogre::MovableObject
		Ogre::MovableObject* MO = IT_MovObj.getNext();
		wxString UniqueName = ToWxString(MO->getName());
		QualifiedName qMovableObject = QualifiedName::GetQualifiedNameByUnique(UniqueName);
		
		// Remove it with interface
		if (this->iMovableObject->Destroy(qMovableObject))
		{
			// Iterator is corrupted, because MovableObject is deleted. Reinitialize it! 
			// "fix" for GCC (obviously can't cast the return value of getAttachedObjectIterator() to a reference
			Ogre::SceneNode::ObjectIterator TmpIt = SN->getAttachedObjectIterator();
			IT_MovObj = TmpIt;
		}
		// else // MovableObject was not registered = was not placed with interface. So don't remove it that way!
	}

	// Remove QualifiedName from ObjectManager
	this->mObjectAccess->RemoveAssociatedSceneManager(qName);
	this->mObjectAccess->RemoveSceneNode(qName);

	// Destroy Ogre::SceneNode
	SM->destroySceneNode(SN);

	// Publish event
	this->Publish(EVT_OGRE_DESTRUCTED, qName);

	// Destroy QualifiedName of Ogre::SceneNode
	QualifiedName::Destroy(qName);

	return true;
}
bool SceneNodeInterface::Exist(QualifiedName qName)
{
	// Interface valid?
	if ( !this->IsValid() ) return false;

	// Validate given QualifiedName
	if ( !qName.IsValid() ) return false;

	// Validate if it is a SceneNode
	if ( this->mObjectAccess->GetSceneNode(qName) == 0 ) return false;

	return true;
}
bool SceneNodeInterface::IsValid()
{
	if( !MediatorInterface::IsValid() ) return false;
	if( !this->mObjectAccess->GetActiveSceneManager().IsValid() ) return false;
	if( this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager()) == 0 ) return false;
	if( this->iMovableObject == 0 ) return false;

	return true;
}
// Methods, individual
QualifiedName SceneNodeInterface::Create(wxString Name, QualifiedName qParentSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Validate parameters
	if ( !qParentSceneNode.IsValid() )  return QualifiedName();

	// Get Ogre::SceneNode
	Ogre::SceneNode* PSN = this->mObjectAccess->GetSceneNode(qParentSceneNode);
	
	// Validate Ogre::SceneNode
	if ( PSN == 0 ) return QualifiedName();

	// Forward & Return
	return this->Create(Name, PSN);
}
QualifiedName SceneNodeInterface::Create(wxString Name, Ogre::SceneNode* pParentSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return QualifiedName();

	// Get Ogre::SceneManager
	Ogre::SceneManager* SM = this->mObjectAccess->GetSceneManager(this->mObjectAccess->GetActiveSceneManager());

	// Create QualifiedName of new Ogre::SceneNode
	QualifiedName qSceneNode = QualifiedName::Create(Name, "SceneNode");

	// Check Collections and abort, if unexpected entries are found.
	if (	(this->mObjectAccess->GetSceneNode(qSceneNode) != 0)
		||	(this->mObjectAccess->GetAssociatedSceneManager(qSceneNode).IsValid()))
	{
		QualifiedName::Destroy(qSceneNode);
		return QualifiedName();
	}

	// Create new Ogre::SceneNode by validating given pParentSceneNode
	Ogre::SceneNode* SN;

	// Check, if SceneNode is RootSceneNode itself (!)
	if (ToWxString(SM->getRootSceneNode()->getName()).IsSameAs(Name))
	{
		SN = SM->getRootSceneNode();
	}
	else
	{
		if (pParentSceneNode == 0) SN = SM->getRootSceneNode()->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));
		else SN = pParentSceneNode->createChildSceneNode(ToOgreString(qSceneNode.UniqueName()));
	}

	// Validate new Ogre::SceneNode
	if (SN == 0)
	{
		QualifiedName::Destroy(qSceneNode);
		return QualifiedName();
	}

	// Add new Ogre::SceneNode ObjectManager
	this->mObjectAccess->AddSceneNode(qSceneNode, SN);

	// Add new association between Ogre::SceneNode and Ogre::SceneManager
	this->mObjectAccess->AddAssociatedSceneManager(this->mObjectAccess->GetActiveSceneManager(), qSceneNode);

	// Publish event
	this->Publish(EVT_OGRE_CONSTRUCTED, qSceneNode);
	
	// Return QualifiedName of new Ogre::SceneNode
	return qSceneNode;
}
QualifiedName SceneNodeInterface::GetName(Ogre::SceneNode* pSceneNode)
{
	wxString UniqueName = ToWxString(pSceneNode->getName());
	QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(UniqueName);
	return qName;
}
Ogre::SceneNode* SceneNodeInterface::GetPtr(QualifiedName qSceneNode)
{
	// Interface valid?
	if ( !this->IsValid() ) return 0;

	// Verify qSceneNode
	if ( !qSceneNode.IsValid() ) return 0;

	// Get Ogre::SceneNode and return it (or null)
	return this->mObjectAccess->GetSceneNode(qSceneNode);
}

// Methods, individual, configuration
bool SceneNodeInterface::SetMovableObjectInterface(MovableObjectInterface* iMovableObject)
{
	if (iMovableObject == 0) return false;
	else
	{
		this->iMovableObject = iMovableObject;
		return true;
	}
}

// Methods, individual wrapper of Ogre-methods
Ogre::Vector3 SceneNodeInterface::GetPosition(QualifiedName qName)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return Ogre::Vector3::ZERO;
	Ogre::Vector3 P = SN->getPosition();
	return P;
}
bool SceneNodeInterface::SetPosition(QualifiedName qName, Ogre::Vector3 &P) 
{
	return this->SetPosition(qName, P.x, P.y, P.z);
}
bool SceneNodeInterface::SetPosition(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false; 

	// Get old position and create string for message
	Ogre::Vector3 OldP = SN->getPosition();

	// Prepare old values
	wxString sOldValueWithSemicolons;
	sOldValueWithSemicolons << (double) OldP.x << ToWxString(";");
	sOldValueWithSemicolons << (double) OldP.y << ToWxString(";");
	sOldValueWithSemicolons << (double) OldP.z;

	// Set position
	SN->setPosition(X, Y, Z);

	// Prepare values
	wxString sValueWithSemicolons;
	sValueWithSemicolons << (double) X << ToWxString(";");
	sValueWithSemicolons << (double) Y << ToWxString(";");
	sValueWithSemicolons << (double) Z;

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("Position"));
	asContextData.Add(sOldValueWithSemicolons);
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;

	// Publish event
	this->Publish(EVT_OGRE_SCENENODE_TRANSLATED, qName, vContextData);

	return true;
}
bool SceneNodeInterface::TranslateRelative(QualifiedName qName, Ogre::Vector3 &T)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;

	Ogre::Vector3 OldP = this->GetPosition(qName);
	Ogre::Vector3 NewP = OldP + T;

	return this->SetPosition(qName, NewP);
}
bool SceneNodeInterface::TranslateRelative(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z)
{
	Ogre::Vector3 T(X, Y, Z);
	return this->TranslateRelative(qName, T);
}
Ogre::Quaternion SceneNodeInterface::GetOrientation(QualifiedName qName)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return Ogre::Quaternion::ZERO;
	Ogre::Quaternion Q = SN->getOrientation();
	return Q;
}
bool SceneNodeInterface::SetOrientation(QualifiedName qName, Ogre::Quaternion &Q)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;
	
	// Get old orientation and create string for message
	Ogre::Quaternion OldQ = SN->getOrientation();

	// Prepare old values
	wxString sOldValueWithSemicolons;
	sOldValueWithSemicolons << (double)OldQ.getRoll(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getPitch(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getYaw(false).valueDegrees();

	// Apply change
	SN->setOrientation(Q);
	
	// Prepare values
	wxString sValueWithSemicolons;
	sValueWithSemicolons << (double)Q.getRoll(false).valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double)Q.getPitch(false).valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double)Q.getYaw(false).valueDegrees();

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("Orientation"));
	asContextData.Add(sOldValueWithSemicolons);
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;

	// Publish event
	this->Publish(EVT_OGRE_SCENENODE_ROTATED, qName, vContextData);

	return true;
}
bool SceneNodeInterface::SetOrientation(QualifiedName qName, Ogre::Real W, Ogre::Real X, Ogre::Real Y, Ogre::Real Z)
{
	Ogre::Quaternion Q = Ogre::Quaternion(W, X, Y, Z);
	return this->SetOrientation(qName, Q);
}
bool SceneNodeInterface::SetOrientation(QualifiedName qName, Ogre::Degree Roll, Ogre::Degree Pitch, Ogre::Degree Yaw)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;
	
	// Get old orientation and create string for message
	Ogre::Quaternion OldQ = SN->getOrientation();

	// Prepare old values
	wxString sOldValueWithSemicolons;
	sOldValueWithSemicolons << (double)OldQ.getRoll(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getPitch(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getYaw(false).valueDegrees();

	// Apply change
	SN->setOrientation(Ogre::Quaternion::IDENTITY);
	SN->roll(Ogre::Radian(Roll));
	SN->pitch(Ogre::Radian(Pitch));
	SN->yaw(Ogre::Radian(Yaw));

	// Reflect effect
	Ogre::Quaternion Q = SN->getOrientation();
	
	// Prepare values
	wxString sValueWithSemicolons;
	sValueWithSemicolons << (double)Q.getRoll(false).valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double)Q.getPitch(false).valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double)Q.getYaw(false).valueDegrees();

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("Orientation"));
	asContextData.Add(sOldValueWithSemicolons);
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;

	// Publish event
	this->Publish(EVT_OGRE_SCENENODE_ROTATED, qName, vContextData);

	return true;
}
bool SceneNodeInterface::RotateRelative(QualifiedName qName, Ogre::Quaternion &Qrelative)
{
	return this->RotateRelative(	qName,
									Ogre::Degree(Qrelative.getRoll(false)),
									Ogre::Degree(Qrelative.getPitch(false)),
									Ogre::Degree(Qrelative.getYaw(false)));
}
bool SceneNodeInterface::RotateRelative(QualifiedName qName, Ogre::Degree Roll, Ogre::Degree Pitch, Ogre::Degree Yaw)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;
	
	// Get old orientation and create string for message
	Ogre::Quaternion OldQ = SN->getOrientation();

	// Prepare old values
	wxString sOldValueWithSemicolons;
	sOldValueWithSemicolons << (double)OldQ.getRoll(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getPitch(false).valueDegrees() << ToWxString(";");
	sOldValueWithSemicolons << (double)OldQ.getYaw(false).valueDegrees();

	// Apply change
	SN->roll(Ogre::Radian(Roll), Ogre::Node::TS_PARENT);
	SN->pitch(Ogre::Radian(Pitch), Ogre::Node::TS_PARENT);
	SN->yaw(Ogre::Radian(Yaw), Ogre::Node::TS_PARENT);

	// Prepare values
	wxString sValueWithSemicolons;
	sValueWithSemicolons << (double) Roll.valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double) Pitch.valueDegrees() << ToWxString(";");
	sValueWithSemicolons << (double) Yaw.valueDegrees();

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("Orientation"));
	asContextData.Add(sOldValueWithSemicolons);
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;

	// Publish event
	this->Publish(EVT_OGRE_SCENENODE_ROTATED, qName, vContextData);

	return true;	
}
Ogre::Vector3 SceneNodeInterface::GetScale(QualifiedName qName)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return Ogre::Vector3::ZERO;
	Ogre::Vector3 S = SN->getScale();
	return S;
}
bool SceneNodeInterface::SetScale(QualifiedName qName, Ogre::Vector3 &S)
{
	return this->SetScale(qName, S.x, S.y, S.z);
}
bool SceneNodeInterface::SetScale(QualifiedName qName, Ogre::Real X, Ogre::Real Y, Ogre::Real Z)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;

	// Get old position and create string for message
	Ogre::Vector3 OldS = SN->getScale();

	// Prepare old values
	wxString sOldValueWithSemicolons;
	sOldValueWithSemicolons << (double) OldS.x << ToWxString(";");
	sOldValueWithSemicolons << (double) OldS.y << ToWxString(";");
	sOldValueWithSemicolons << (double) OldS.z;
	
	// Set scale
	SN->setScale(X, Y, Z);

	// Prepare values
	wxString sValueWithSemicolons = "";
	sValueWithSemicolons << (double) X << ToWxString(";");
	sValueWithSemicolons << (double) Y << ToWxString(";");
	sValueWithSemicolons << (double) Z;

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("Scale"));
	asContextData.Add(sOldValueWithSemicolons);
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;

	// Publish event
	this->Publish(EVT_OGRE_SCENENODE_SCALED, qName, vContextData);

	return true;
}
bool SceneNodeInterface::ScaleRelative(QualifiedName qName, Ogre::Vector3 &Srelative)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;

	Ogre::Vector3 OldS = this->GetScale(qName);
	Ogre::Vector3 NewS = OldS + Srelative;

	return this->SetScale(qName, NewS);
}
bool SceneNodeInterface::ScaleRelative(QualifiedName qName, Ogre::Real Xrelative, Ogre::Real Yrelative, Ogre::Real Zrelative)
{
	Ogre::Vector3 Srelative(Xrelative, Yrelative, Zrelative);
	return this->ScaleRelative(qName, Srelative);
}

bool SceneNodeInterface::GetShowBoundingBox(QualifiedName qName)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;
	return SN->getShowBoundingBox();
}
bool SceneNodeInterface::SetShowBoundingBox(QualifiedName qName, bool ShowBoundingBox)
{
	Ogre::SceneNode* SN = this->GetPtr(qName);
	if (!SN) return false;

	// Apply change
	SN->showBoundingBox(ShowBoundingBox);
	
	// Prepare values
	wxString sValueWithSemicolons;
	if (ShowBoundingBox) sValueWithSemicolons = ToWxString("TRUE");
	else sValueWithSemicolons = ToWxString("FALSE");

	// Prepare Variant
	wxArrayString asContextData;
	asContextData.Add(ToWxString("ShowBoundingBox"));
	asContextData.Add(sValueWithSemicolons);
	wxVariant vContextData = asContextData;
	
	// Publish event
	this->Publish(EVT_OGRE_CHANGED, qName, vContextData);

	return true;
}