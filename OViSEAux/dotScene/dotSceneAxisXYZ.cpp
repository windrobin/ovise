#ifndef dotSceneAxisXYZ_h_
#define dotSceneAxisXYZ_h_
#include "dotSceneAxisXYZ.h"
#endif

double dotSceneObjects::dotSceneAxisXYZ::get_xAxisX() const { return this->_xAxisX; }
double dotSceneObjects::dotSceneAxisXYZ::get_xAxisY() const { return this->_xAxisY; }
double dotSceneObjects::dotSceneAxisXYZ::get_xAxisZ() const { return this->_xAxisZ; }
double dotSceneObjects::dotSceneAxisXYZ::get_yAxisX() const { return this->_yAxisX; }
double dotSceneObjects::dotSceneAxisXYZ::get_yAxisY() const { return this->_yAxisY; }
double dotSceneObjects::dotSceneAxisXYZ::get_yAxisZ() const { return this->_yAxisZ; }
double dotSceneObjects::dotSceneAxisXYZ::get_zAxisX() const { return this->_zAxisX; }
double dotSceneObjects::dotSceneAxisXYZ::get_zAxisY() const { return this->_zAxisY; }
double dotSceneObjects::dotSceneAxisXYZ::get_zAxisZ() const { return this->_zAxisZ; }

void dotSceneObjects::dotSceneAxisXYZ::set_xAxisX(double value) { this->_xAxisX = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_xAxisY(double value) { this->_xAxisY = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_xAxisZ(double value) { this->_xAxisZ = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_yAxisX(double value) { this->_yAxisX = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_yAxisY(double value) { this->_yAxisY = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_yAxisZ(double value) { this->_yAxisZ = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_zAxisX(double value) { this->_zAxisX = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_zAxisY(double value) { this->_zAxisY = value; }
void dotSceneObjects::dotSceneAxisXYZ::set_zAxisZ(double value) { this->_zAxisZ = value; }

void dotSceneObjects::dotSceneAxisXYZ::set_xAxisX(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_xAxisX = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_xAxisY(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_xAxisY = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_xAxisZ(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_xAxisZ = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_yAxisX(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_yAxisX = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_yAxisY(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_yAxisY = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_yAxisZ(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_yAxisZ = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_zAxisX(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_zAxisX = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_zAxisY(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_zAxisY = tmp;
}

void dotSceneObjects::dotSceneAxisXYZ::set_zAxisZ(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_zAxisZ = tmp;
}

bool dotSceneObjects::dotSceneAxisXYZ::IsValid() const
{
	// attributes are no useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// constructors & destructors
dotSceneObjects::dotSceneAxisXYZ::dotSceneAxisXYZ() : dotSceneObject(dotSceneEnums::axisXYZ)
{
	this->set_xAxisX(0.0);
	this->set_xAxisY(0.0);
	this->set_xAxisZ(0.0);
	this->set_yAxisX(0.0);
	this->set_yAxisY(0.0);
	this->set_yAxisZ(0.0);
	this->set_zAxisX(0.0);
	this->set_zAxisY(0.0);
	this->set_zAxisZ(0.0);
}
dotSceneObjects::dotSceneAxisXYZ::dotSceneAxisXYZ(std::string str_xAxisX, std::string str_xAxisY, std::string str_xAxisZ, std::string str_yAxisX, std::string str_yAxisY, std::string str_yAxisZ, std::string str_zAxisX, std::string str_zAxisY, std::string str_zAxisZ) : dotSceneObject(dotSceneEnums::axisXYZ)
{
	this->set_xAxisX(str_xAxisX);
	this->set_xAxisY(str_xAxisY);
	this->set_xAxisZ(str_xAxisZ);
	this->set_yAxisX(str_yAxisX);
	this->set_yAxisY(str_yAxisY);
	this->set_yAxisZ(str_yAxisZ);
	this->set_zAxisX(str_zAxisX);
	this->set_zAxisY(str_zAxisY);
	this->set_zAxisZ(str_zAxisZ);
}

dotSceneObjects::dotSceneAxisXYZ::dotSceneAxisXYZ(double double_xAxisX, double double_xAxisY, double double_xAxisZ, double double_yAxisX, double double_yAxisY, double double_yAxisZ, double double_zAxisX, double double_zAxisY, double double_zAxisZ) : dotSceneObject(dotSceneEnums::axisXYZ)
{
	this->set_xAxisX(double_xAxisX);
	this->set_xAxisY(double_xAxisY);
	this->set_xAxisZ(double_xAxisZ);
	this->set_yAxisX(double_yAxisX);
	this->set_yAxisY(double_yAxisY);
	this->set_yAxisZ(double_yAxisZ);
	this->set_zAxisX(double_zAxisX);
	this->set_zAxisY(double_zAxisY);
	this->set_zAxisZ(double_zAxisZ);
}
