#ifndef dotSceneQuaternion_h_
#define dotSceneQuaternion_h_
#include "dotSceneQuaternion.h"
#endif

double dotSceneObjects::dotSceneQuaternion::get_qx() const { return this->_qx; }
double dotSceneObjects::dotSceneQuaternion::get_qy() const { return this->_qy; }
double dotSceneObjects::dotSceneQuaternion::get_qz() const { return this->_qz; }
double dotSceneObjects::dotSceneQuaternion::get_qw() const { return this->_qw; }

void dotSceneObjects::dotSceneQuaternion::set_qx(double value) { this->_qx = value; }
void dotSceneObjects::dotSceneQuaternion::set_qy(double value) { this->_qy = value; }
void dotSceneObjects::dotSceneQuaternion::set_qz(double value) { this->_qz = value; }
void dotSceneObjects::dotSceneQuaternion::set_qw(double value) { this->_qw = value; }

void dotSceneObjects::dotSceneQuaternion::set_qx(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_qx = tmp;
}

void dotSceneObjects::dotSceneQuaternion::set_qy(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_qy = tmp;
}

void dotSceneObjects::dotSceneQuaternion::set_qz(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_qz = tmp;
}

void dotSceneObjects::dotSceneQuaternion::set_qw(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_qw = tmp;
}


bool dotSceneObjects::dotSceneQuaternion::IsValid() const
{
	// qx, qy, qz & qw are no useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// constructors & destructors
dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion() : dotSceneObject(dotSceneEnums::quaternion)
{
	this->set_qx(0.0);
	this->set_qy(0.0);
	this->set_qz(0.0);
	this->set_qw(0.0);
}
dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion(std::string str_qx, std::string str_qy, std::string str_qz, std::string str_qw) : dotSceneObject(dotSceneEnums::quaternion)
{
	this->set_qx(str_qx);
    this->set_qy(str_qy);
    this->set_qz(str_qz);
	this->set_qw(str_qw);
}

dotSceneObjects::dotSceneQuaternion::dotSceneQuaternion(double double_qx, double double_qy, double double_qz, double double_qw) : dotSceneObject(dotSceneEnums::quaternion)
{
    this->set_qx(double_qx);
    this->set_qy(double_qy);
    this->set_qz(double_qz);
    this->set_qw(double_qw);
}
