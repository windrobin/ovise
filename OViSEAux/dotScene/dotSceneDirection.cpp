#ifndef dotSceneDirection_h_
#define dotSceneDirection_h_
#include "dotSceneDirection.h"
#endif

double dotSceneObjects::dotSceneDirection::get_x() const { return this->_x; }
double dotSceneObjects::dotSceneDirection::get_y() const { return this->_y; }
double dotSceneObjects::dotSceneDirection::get_z() const { return this->_z; }
dotSceneEnums::dotSceneGeneralEnums::RelativeTo dotSceneObjects::dotSceneDirection::get_RelativeTo() const { return this->_RelativeTo; }
int dotSceneObjects::dotSceneDirection::get_LocalDirX() const { return this->_LocalDirX; }
int dotSceneObjects::dotSceneDirection::get_LocalDirY() const { return this->_LocalDirY; }
int dotSceneObjects::dotSceneDirection::get_LocalDirZ() const { return this->_LocalDirZ; }

void dotSceneObjects::dotSceneDirection::set_x(double value) { this->_x = value; }
void dotSceneObjects::dotSceneDirection::set_y(double value) { this->_y = value; }
void dotSceneObjects::dotSceneDirection::set_z(double value) { this->_z = value; }
void dotSceneObjects::dotSceneDirection::set_RelativeTo(dotSceneEnums::dotSceneGeneralEnums::RelativeTo value) { this->_RelativeTo = value; }
void dotSceneObjects::dotSceneDirection::set_LocalDirX(int value) { this->_LocalDirX = value; }
void dotSceneObjects::dotSceneDirection::set_LocalDirY(int value) { this->_LocalDirY = value; }
void dotSceneObjects::dotSceneDirection::set_LocalDirZ(int value) { this->_LocalDirZ = value; }

void dotSceneObjects::dotSceneDirection::set_x(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_x = tmp;
}

void dotSceneObjects::dotSceneDirection::set_y(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_y = tmp;
}

void dotSceneObjects::dotSceneDirection::set_z(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_z = tmp;
}

void dotSceneObjects::dotSceneDirection::set_RelativeTo(std::string value)
{
	bool match = false;

	if (value == "local") this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToLocal;
	if (value == "parent") this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToParent;
	if (value == "world") this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeToWorld;

	if (!match) this->_RelativeTo = dotSceneEnums::dotSceneGeneralEnums::RelativeTo_INVALID;
}

void dotSceneObjects::dotSceneDirection::set_LocalDirX(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_LocalDirX = tmp;
}

void dotSceneObjects::dotSceneDirection::set_LocalDirY(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_LocalDirY = tmp;
}

void dotSceneObjects::dotSceneDirection::set_LocalDirZ(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_LocalDirZ = tmp;
}

bool dotSceneObjects::dotSceneDirection::IsValid() const
{
	// double-attributes are no useable for valid-check!
	if (this->_RelativeTo == dotSceneEnums::dotSceneGeneralEnums::RelativeTo_INVALID) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// constructors & destructors
dotSceneObjects::dotSceneDirection::dotSceneDirection() : dotSceneObject(dotSceneEnums::direction)
{
	this->set_x(0.0);
	this->set_y(0.0);
	this->set_z(0.0);
	this->set_RelativeTo(dotSceneEnums::dotSceneGeneralEnums::RelativeTo_INVALID);
	this->set_LocalDirX(0);
	this->set_LocalDirY(0);
	this->set_LocalDirZ(-1);
}
dotSceneObjects::dotSceneDirection::dotSceneDirection(std::string str_x, std::string str_y, std::string str_z, std::string str_RelativeTo, std::string str_LocalDirX, std::string str_LocalDirY, std::string str_LocalDirZ) : dotSceneObject(dotSceneEnums::direction)
{
	this->set_x(str_x);
	this->set_y(str_y);
	this->set_z(str_z);
	this->set_RelativeTo(str_RelativeTo);
	this->set_LocalDirX(str_LocalDirX);
	this->set_LocalDirY(str_LocalDirY);
	this->set_LocalDirZ(str_LocalDirZ);
}

dotSceneObjects::dotSceneDirection::dotSceneDirection(double double_x, double double_y, double double_z, dotSceneEnums::dotSceneGeneralEnums::RelativeTo enum_RelativeTo, int int_LocalDirX, int int_LocalDirY, int int_LocalDirZ) : dotSceneObject(dotSceneEnums::direction)
{
	this->set_x(double_x);
	this->set_y(double_y);
	this->set_z(double_z);
	this->set_RelativeTo(enum_RelativeTo);
	this->set_LocalDirX(int_LocalDirX);
	this->set_LocalDirY(int_LocalDirY);
	this->set_LocalDirZ(int_LocalDirZ);
}