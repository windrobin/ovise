#ifndef dotScene3D_h_
#define dotScene3D_h_
#include "dotScene3D.h"
#endif

double dotSceneObjects::dotScene3D::get_x() const { return this->_x; }
double dotSceneObjects::dotScene3D::get_y() const { return this->_y; }
double dotSceneObjects::dotScene3D::get_z() const { return this->_z; }

void dotSceneObjects::dotScene3D::set_x(double value) { this->_x = value; }
void dotSceneObjects::dotScene3D::set_y(double value) { this->_y = value; }
void dotSceneObjects::dotScene3D::set_z(double value) { this->_z = value; }

void dotSceneObjects::dotScene3D::set_x(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_x = tmp;
}

void dotSceneObjects::dotScene3D::set_y(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_y = tmp;
}

void dotSceneObjects::dotScene3D::set_z(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_z = tmp;
}

bool dotSceneObjects::dotScene3D::IsValid() const
{
	// x, y & z are not useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

///region constructors & destructors
dotSceneObjects::dotScene3D::dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag) : dotSceneObject(incomingTag)
{
	this->set_x(0.0);
	this->set_y(0.0);
	this->set_z(0.0);
}

dotSceneObjects::dotScene3D::dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag, std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(incomingTag)
{
    this->set_x(str_x);
    this->set_y(str_y);
	this->set_z(str_z);
}

dotSceneObjects::dotScene3D::dotScene3D(dotSceneEnums::dotSceneElementTags incomingTag, double double_x, double double_y, double double_z) : dotSceneObject(incomingTag)
{
	this->set_x(double_x);
    this->set_y(double_y);
	this->set_z(double_z);
}
