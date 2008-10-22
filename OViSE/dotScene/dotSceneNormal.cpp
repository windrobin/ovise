#ifndef dotSceneNormal_h_
#define dotSceneNormal_h_
#include "dotSceneNormal.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneNormal::set_x(double value) { _x = value; }
void dotSceneObjects::dotSceneNormal::set_y(double value) { _y = value; }
void dotSceneObjects::dotSceneNormal::set_z(double value) { _z = value; }

double dotSceneObjects::dotSceneNormal::get_x() const { return _x; }
double dotSceneObjects::dotSceneNormal::get_y() const { return _y; }
double dotSceneObjects::dotSceneNormal::get_z() const { return _z; }

///region constructors & destructors
dotSceneObjects::dotSceneNormal::dotSceneNormal() : dotSceneObject(normal) { } 
dotSceneObjects::dotSceneNormal::dotSceneNormal(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(normal)
{
	this->set_x(atof(str_x.c_str()));
    this->set_y(atof(str_y.c_str()));
	this->set_z(atof(str_z.c_str()));
}

dotSceneObjects::dotSceneNormal::dotSceneNormal(double double_x, double double_y, double double_z) : dotSceneObject(normal)
{
	this->set_x(double_x);
    this->set_y(double_y);
	this->set_z(double_z);
}

dotSceneObjects::dotSceneNormal::~dotSceneNormal() { }
