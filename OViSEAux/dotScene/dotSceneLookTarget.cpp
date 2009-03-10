#ifndef dotSceneLookTarget_h_
#define dotSceneLookTarget_h_
#include "dotSceneLookTarget.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotSceneLookTarget::get_NodeName() const { return this->_NodeName; }
dotSceneEnums::dotSceneGeneralEnums::RelativeTo dotSceneObjects::dotSceneLookTarget::get_RelativeTo() const { return this->_RelativeTo; }

dotScenePosition dotSceneObjects::dotSceneLookTarget::get_Position() const { return this->_Position; }
dotSceneLocalDirectionVector dotSceneObjects::dotSceneLookTarget::get_LocalDirectionVector() const { return this->_LocalDirectionVector; }

void dotSceneObjects::dotSceneLookTarget::set_NodeName(std::string value) { this->_NodeName = value; }
void dotSceneObjects::dotSceneLookTarget::set_RelativeTo(dotSceneEnums::dotSceneGeneralEnums::RelativeTo value) { this->_RelativeTo = value; }

void dotSceneObjects::dotSceneLookTarget::set_Position(dotScenePosition value) { this->_Position = value; }
void dotSceneObjects::dotSceneLookTarget::set_LocalDirectionVector(dotSceneLocalDirectionVector value) { this->_LocalDirectionVector = value; }

void dotSceneObjects::dotSceneLookTarget::set_RelativeTo(std::string value)
{
	bool match = false;

	if ((value == "local") || (value == "Local") || (value == "RelativeToLocal")) { this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToLocal; match = true; }
	if ((value == "parent") || (value == "Parent") || (value == "RelativeToParent")) { this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToParent; match = true; }
	if ((value == "world") || (value == "World") || (value == "RelativeToWorld")) { this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToWorld; match = true; }

	if (!match) this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeTo_INVALID;
}

bool dotSceneObjects::dotSceneLookTarget::IsValid() const
{
	// basics valid?
	if (this->_RelativeTo == dotSceneEnums::dotSceneGeneralEnums::RelativeTo_INVALID) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneLookTarget::dotSceneLookTarget() : dotSceneObject(dotSceneEnums::lookTarget)
{
	this->set_NodeName("INITIAL_NOT_SET");
	this->set_RelativeTo("INVALID"); //#REQUIRED
}

dotSceneObjects::dotSceneLookTarget::dotSceneLookTarget(std::string str_NodeName, std::string str_RelativeTo, dotScenePosition obj_Position, dotSceneLocalDirectionVector obj_LocalDirectionVector) : dotSceneObject(dotSceneEnums::lookTarget)
{
	this->set_NodeName(str_NodeName);
	this->set_RelativeTo(str_RelativeTo);
	this->set_Position(obj_Position);
	this->set_LocalDirectionVector(obj_LocalDirectionVector);
}

dotSceneObjects::dotSceneLookTarget::dotSceneLookTarget(std::string str_NodeName, dotSceneEnums::dotSceneGeneralEnums::RelativeTo enum_RelativeTo, dotScenePosition obj_Position, dotSceneLocalDirectionVector obj_LocalDirectionVector) : dotSceneObject(dotSceneEnums::lookTarget)
{
	this->set_NodeName(str_NodeName);
	this->set_RelativeTo(enum_RelativeTo);
	this->set_Position(obj_Position);
	this->set_LocalDirectionVector(obj_LocalDirectionVector);
}
