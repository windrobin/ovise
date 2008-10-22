#ifndef dotSceneScale_h_
#define dotSceneScale_h_
#include "dotSceneScale.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneScale::set_x(double value) { _x = value; }
void dotSceneObjects::dotSceneScale::set_y(double value) { _y = value; }
void dotSceneObjects::dotSceneScale::set_z(double value) { _z = value; }

double dotSceneObjects::dotSceneScale::get_x() const { return _x; }
double dotSceneObjects::dotSceneScale::get_y() const { return _y; }
double dotSceneObjects::dotSceneScale::get_z() const { return _z; }

///region constructors & destructors
dotSceneObjects::dotSceneScale::dotSceneScale() : dotSceneObject(scale) { } 
dotSceneObjects::dotSceneScale::dotSceneScale(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(scale)
{
	this->set_x(atof(str_x.c_str()));
    this->set_y(atof(str_y.c_str()));
	this->set_z(atof(str_z.c_str()));
}

dotSceneObjects::dotSceneScale::dotSceneScale(double double_x, double double_y, double double_z) : dotSceneObject(scale)
{
	this->set_x(double_x);
    this->set_y(double_y);
	this->set_z(double_z);
}

dotSceneObjects::dotSceneScale::~dotSceneScale() { }
