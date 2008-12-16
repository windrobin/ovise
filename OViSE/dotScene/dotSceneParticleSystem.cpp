#ifndef dotSceneParticleSystem_h_
#define dotSceneParticleSystem_h_
#include "dotSceneParticleSystem.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotSceneParticleSystem::get_name() const { return this->_name; }
std::string dotSceneObjects::dotSceneParticleSystem::get_ID() const { return this->_ID; }
std::string dotSceneObjects::dotSceneParticleSystem::get_TemplateName() const { return this->_TemplateName; }
std::string dotSceneObjects::dotSceneParticleSystem::get_MaterialName() const { return this->_MaterialName; }

dotSceneCommonMovableObjectParams dotSceneObjects::dotSceneParticleSystem::get_CommonMovableObjectParams() const { return this->_CommonMovableObjectParams; }
dotSceneUserDataReference dotSceneObjects::dotSceneParticleSystem::get_UserDataReference() const { return this->_UserDataReference; }

void dotSceneObjects::dotSceneParticleSystem::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotSceneParticleSystem::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotSceneParticleSystem::set_TemplateName(std::string value) { this->_TemplateName = value; }
void dotSceneObjects::dotSceneParticleSystem::set_MaterialName(std::string value) { this->_MaterialName = value; }

void dotSceneObjects::dotSceneParticleSystem::set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value) { this->_CommonMovableObjectParams = value; }
void dotSceneObjects::dotSceneParticleSystem::set_UserDataReference(dotSceneUserDataReference value) { this->_UserDataReference = value; }

bool dotSceneObjects::dotSceneParticleSystem::IsValid() const
{
	if (this->_TemplateName == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneParticleSystem::dotSceneParticleSystem() : dotSceneObject(dotSceneEnums::particleSystem)
{
	this->set_name("INITIAL_NOT_SET");
	this->set_ID("INITIAL_NOT_SET");
	this->set_TemplateName("INVALID"); //#REQUIERED
	this->set_MaterialName("INITIAL_NOT_SET");
	this->set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams());
	this->set_UserDataReference(dotSceneUserDataReference());
}

dotSceneObjects::dotSceneParticleSystem::dotSceneParticleSystem(std::string str_name, std::string str_ID, std::string str_TemplateName, std::string str_MaterialName, dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams, dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::particleSystem)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_TemplateName(str_TemplateName); //#REQUIERED
	this->set_MaterialName(str_MaterialName);
	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_UserDataReference(obj_UserDataReference);
}
