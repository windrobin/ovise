#ifndef dotSceneTrackTarget_h_
#define dotSceneTrackTarget_h_
#include "dotSceneTrackTarget.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotSceneTrackTarget::get_NodeName() const { return this->_NodeName; }

dotSceneOffset dotSceneObjects::dotSceneTrackTarget::get_Offset() const { return this->_Offset; }
dotSceneLocalDirectionVector dotSceneObjects::dotSceneTrackTarget::get_LocalDirectionVector() const { return this->_LocalDirectionVector; }

void dotSceneObjects::dotSceneTrackTarget::set_NodeName(std::string value) { this->_NodeName = value; }

void dotSceneObjects::dotSceneTrackTarget::set_Offset(dotSceneOffset value) { this->_Offset = value; }
void dotSceneObjects::dotSceneTrackTarget::set_LocalDirectionVector(dotSceneLocalDirectionVector value) { this->_LocalDirectionVector = value; }

bool dotSceneObjects::dotSceneTrackTarget::IsValid() const
{
	// basics valid?
	if (this->_NodeName == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneTrackTarget::dotSceneTrackTarget() : dotSceneObject(dotSceneEnums::trackTarget)
{
	this->set_NodeName("INVALID");
}

dotSceneObjects::dotSceneTrackTarget::dotSceneTrackTarget(std::string str_NodeName, dotSceneOffset obj_Offset, dotSceneLocalDirectionVector obj_LocalDirectionVector) : dotSceneObject(dotSceneEnums::trackTarget)
{
	this->set_NodeName(str_NodeName);
	this->set_Offset(obj_Offset);
	this->set_LocalDirectionVector(obj_LocalDirectionVector);
}
