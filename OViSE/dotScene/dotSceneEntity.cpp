#ifndef dotSceneEntity_h_
#define dotSceneEntity_h_
#include "dotSceneEntity.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneEntity::set_name(std::string value) { _name = value; }
void dotSceneObjects::dotSceneEntity::set_meshFile(std::string value) { _meshFile = value; }
void dotSceneObjects::dotSceneEntity::set_static(bool value) { _static = value; }
void dotSceneObjects::dotSceneEntity::set_visible(bool value) { _visible = value; }
void dotSceneObjects::dotSceneEntity::set_castShadows(bool value) { _castShadows = value; }
void dotSceneObjects::dotSceneEntity::set_renderingDistance(double value) { _renderingDistance = value; }

std::string dotSceneObjects::dotSceneEntity::get_name() const { return _name; }
std::string dotSceneObjects::dotSceneEntity::get_meshFile() const { return _meshFile; }
bool dotSceneObjects::dotSceneEntity::get_static() const { return _static; }
bool dotSceneObjects::dotSceneEntity::get_visible() const { return _visible; }
bool dotSceneObjects::dotSceneEntity::get_castShadows() const { return _castShadows; }
double dotSceneObjects::dotSceneEntity::get_renderingDistance() const { return _renderingDistance; }

/// region constructors & destructors
dotSceneObjects::dotSceneEntity::dotSceneEntity() : dotSceneSpecific(entity) { }
dotSceneObjects::dotSceneEntity::dotSceneEntity(std::string str_name, std::string str_meshFile, std::string str_static, std::string str_visible, std::string str_castShadows, std::string str_renderingDistance) : dotSceneSpecific(entity)
{
    this->set_name(str_name);
    this->set_meshFile(str_meshFile);
	
	if(atoi(str_static.c_str()) == 0) this->set_static(false);
    else this->set_static(true);

	if(atoi(str_visible.c_str()) == 0) this->set_visible(false);
	else this->set_visible(true);
		
	if(atoi(str_castShadows.c_str()) == 0) this->set_castShadows(false);
	else this->set_castShadows(true);

    this->set_renderingDistance(atof(str_renderingDistance.c_str()));
}

dotSceneObjects::dotSceneEntity::dotSceneEntity(std::string str_name, std::string str_meshFile, bool bool_static, bool bool_visible, bool bool_castShadows, double double_renderingDistance) : dotSceneSpecific(entity)
{
    this->set_name(str_name);
    this->set_meshFile(str_meshFile);
    this->set_static(bool_static);
    this->set_visible(bool_visible);
    this->set_castShadows(bool_castShadows);
    this->set_renderingDistance(double_renderingDistance);
}

dotSceneObjects::dotSceneEntity::~dotSceneEntity(){ }
