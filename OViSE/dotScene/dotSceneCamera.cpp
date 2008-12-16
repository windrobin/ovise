#ifndef dotSceneCamera_h_
#define dotSceneCamera_h_
#include "dotSceneCamera.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotSceneCamera::get_name() const { return this->_name; }		
double dotSceneObjects::dotSceneCamera::get_fov() const { return this->_fov; }
std::string dotSceneObjects::dotSceneCamera::get_projectionType() const { return this->_projectionType; }
dotSceneNormal dotSceneObjects::dotSceneCamera::get_normal() const { return _normal; }
dotSceneClipping dotSceneObjects::dotSceneCamera::get_clipping() const { return this->_clipping; }

void dotSceneObjects::dotSceneCamera::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotSceneCamera::set_fov(double value) { this->_fov = value; }
void dotSceneObjects::dotSceneCamera::set_projectionType(std::string value) { this->_projectionType = value; }
void dotSceneObjects::dotSceneCamera::set_normal(dotSceneNormal value) { this->_normal = value; }
void dotSceneObjects::dotSceneCamera::set_clipping(dotSceneClipping value) { this->_clipping = value; }

void dotSceneObjects::dotSceneCamera::set_fov(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_fov = tmp;
}

bool dotSceneObjects::dotSceneCamera::IsValid() const
{
	if (this->_name == "INVALID") return false;
	if (this->_projectionType == "INVALID") return false;
	if (!this->_normal.IsValid()) return false;
	if (!this->_clipping.IsValid()) return false;
	if (!dotSceneObjects::dotSceneSpecific::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneCamera::dotSceneCamera() : dotSceneObject(dotSceneEnums::camera)
{
	this->set_name("INVALID");
	this->set_projectionType("INVALID");
	this->set_fov(0.0);
}

dotSceneObjects::dotSceneCamera::dotSceneCamera(std::string str_name, std::string str_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping) : dotSceneObject(dotSceneEnums::camera)
{
    this->set_name(str_name);
    this->set_fov(str_fov);
	this->set_projectionType(str_projectionType);
    this->set_normal(obj_normal);
    this->set_clipping(obj_clipping);
}

dotSceneObjects::dotSceneCamera::dotSceneCamera(std::string str_name, double double_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping) : dotSceneObject(dotSceneEnums::camera)
{
    this->set_name(str_name);
    this->set_fov(double_fov);
    this->set_projectionType(str_projectionType);
    this->set_normal(obj_normal);
    this->set_clipping(obj_clipping);
}

