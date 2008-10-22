#ifndef dotSceneQuaternion_h_
#define dotSceneQuaternion_h_
#include "dotSceneQuaternion.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneQuaternion::set_qx(double value) { _qx = value; }
void dotSceneObjects::dotSceneQuaternion::set_qy(double value) { _qy = value; }
void dotSceneObjects::dotSceneQuaternion::set_qz(double value) { _qz = value; }
void dotSceneObjects::dotSceneQuaternion::set_qw(double value) { _qw = value; }

double dotSceneObjects::dotSceneQuaternion::get_qx() const { return _qx; }
double dotSceneObjects::dotSceneQuaternion::get_qy() const { return _qy; }
double dotSceneObjects::dotSceneQuaternion::get_qz() const { return _qz; }
double dotSceneObjects::dotSceneQuaternion::get_qw() const { return _qw; }

/// constructors & destructors
dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion() : dotSceneObject(rotation) { }
dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion(std::string str_qx, std::string str_qy, std::string str_qz, std::string str_qw) : dotSceneObject(rotation)
{
	this->set_qx(atof(str_qx.c_str()));
    this->set_qy(atof(str_qy.c_str()));
    this->set_qz(atof(str_qz.c_str()));
	this->set_qw(atof(str_qw.c_str()));
}

dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion(double double_qx, double double_qy, double double_qz, double double_qw) : dotSceneObject(rotation)
{
    this->set_qx(double_qx);
    this->set_qy(double_qy);
    this->set_qz(double_qz);
    this->set_qw(double_qw);
}

dotSceneObjects::dotSceneQuaternion::~dotSceneQuaternion() { }
