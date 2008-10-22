#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotScenePosition::set_x(double value) { _x = value; }
void dotSceneObjects::dotScenePosition::set_y(double value) { _y = value; }
void dotSceneObjects::dotScenePosition::set_z(double value) { _z = value; }

double dotSceneObjects::dotScenePosition::get_x() const { return _x; }
double dotSceneObjects::dotScenePosition::get_y() const { return _y; }
double dotSceneObjects::dotScenePosition::get_z() const { return _z; }

///region constructors & destructors
dotSceneObjects::dotScenePosition::dotScenePosition() : dotSceneObject(position) { }
dotSceneObjects::dotScenePosition::dotScenePosition(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(position)
{
	this->set_x(atof(str_x.c_str()));
    this->set_y(atof(str_y.c_str()));
	this->set_z(atof(str_z.c_str()));
}

dotSceneObjects::dotScenePosition::dotScenePosition(double double_x, double double_y, double double_z) : dotSceneObject(position)
{
	this->set_x(double_x);
    this->set_y(double_y);
	this->set_z(double_z);
}

dotSceneObjects::dotScenePosition::~dotScenePosition() { }


