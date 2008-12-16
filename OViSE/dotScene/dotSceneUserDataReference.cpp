#ifndef dotSceneUserDataReference_h_
#define dotSceneUserDataReference_h_
#include "dotSceneUserDataReference.h"
#endif

std::string dotSceneObjects::dotSceneUserDataReference::get_ID() const { return this->_ID; }
void		dotSceneObjects::dotSceneUserDataReference::set_ID(std::string value) { this->_ID = value; }
bool		dotSceneObjects::dotSceneUserDataReference::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	
	return true;
}


dotSceneObjects::dotSceneUserDataReference::dotSceneUserDataReference() : dotSceneObject(dotSceneEnums::userDataReference)
{
	this->set_ID("INITIAL_NOT_SET");
}

dotSceneObjects::dotSceneUserDataReference::dotSceneUserDataReference(std::string str_ID) : dotSceneObject(dotSceneEnums::userDataReference)
{
	this->set_ID(str_ID);
}


