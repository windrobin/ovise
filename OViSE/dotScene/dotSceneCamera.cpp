#ifndef dotSceneCamera_h_
#define dotSceneCamera_h_
#include "dotSceneCamera.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneCamera::set_name(std::string value) { _name = value; }
void dotSceneObjects::dotSceneCamera::set_fov(double value) { _fov = value; }
void dotSceneObjects::dotSceneCamera::set_projectionType(std::string value) { _projectionType = value; }
void dotSceneObjects::dotSceneCamera::set_normal(dotSceneNormal value) { _normal = value; }
void dotSceneObjects::dotSceneCamera::set_clipping(dotSceneClipping value) { _clipping = value; }

std::string dotSceneObjects::dotSceneCamera::get_name() const { return _name; }		
double dotSceneObjects::dotSceneCamera::get_fov() const { return _fov; }
std::string dotSceneObjects::dotSceneCamera::get_projectionType() const { return _projectionType; }
dotSceneNormal dotSceneObjects::dotSceneCamera::get_normal() const { return _normal; }
dotSceneClipping dotSceneObjects::dotSceneCamera::get_clipping() const { return _clipping; }

/// region constructors & destructors
dotSceneObjects::dotSceneCamera::dotSceneCamera() : dotSceneSpecific(camera) { }
dotSceneObjects::dotSceneCamera::dotSceneCamera(std::string str_name, std::string str_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping) : dotSceneSpecific(camera)
{
    this->set_name(str_name);
    double tmp;
    sscanf(str_fov.c_str(), "%lf", &tmp);
    this->set_fov(tmp);
	this->set_projectionType(str_projectionType);
    this->set_normal(obj_normal);
    this->set_clipping(obj_clipping);
}

dotSceneObjects::dotSceneCamera::dotSceneCamera(std::string str_name, double double_fov, std::string str_projectionType, dotSceneNormal obj_normal, dotSceneClipping obj_clipping) : dotSceneSpecific(camera)
{
    this->set_name(str_name);
    this->set_fov(double_fov);
    this->set_projectionType(str_projectionType);
    this->set_normal(obj_normal);
    this->set_clipping(obj_clipping);
}

dotSceneObjects::dotSceneCamera::~dotSceneCamera() { }
