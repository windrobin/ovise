#include "../OgreMediator/MediatorInterface.h"

// De- & Constructors
MediatorInterface::MediatorInterface(ObjectManager* pObjMgr) { this->SetObjectManager(pObjMgr); }
MediatorInterface::~MediatorInterface(void) { this->mObjectAccess = 0; }
// General
bool MediatorInterface::IsValid()
{
	if (this->mObjectAccess == 0) return false;

	return true;
}
// ObjectManager
bool MediatorInterface::SetObjectManager(ObjectManager* pObjMgr)
{
	if (pObjMgr == 0) return false;
	else
	{
		this->mObjectAccess = pObjMgr;
		return true;
	}
}