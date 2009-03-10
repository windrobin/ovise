#ifndef dotSceneAngleAxis_h_
#define dotSceneAngleAxis_h_
#include "dotSceneAngleAxis.h"
#endif

double dotSceneObjects::dotSceneAngleAxis::get_Angle() const { return this->_Angle; }
dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits dotSceneObjects::dotSceneAngleAxis::get_AngleUnit() const { return this->_AngleUnit; }
double dotSceneObjects::dotSceneAngleAxis::get_x() const { return this->_x; }
double dotSceneObjects::dotSceneAngleAxis::get_y() const { return this->_y; }
double dotSceneObjects::dotSceneAngleAxis::get_z() const { return this->_z; }

void dotSceneObjects::dotSceneAngleAxis::set_Angle(double value) { this->_Angle = value; }
void dotSceneObjects::dotSceneAngleAxis::set_AngleUnit(dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits value) { this->_AngleUnit = value; }
void dotSceneObjects::dotSceneAngleAxis::set_x(double value) { this->_x = value; }
void dotSceneObjects::dotSceneAngleAxis::set_y(double value) { this->_y = value; }
void dotSceneObjects::dotSceneAngleAxis::set_z(double value) { this->_z = value; }

void dotSceneObjects::dotSceneAngleAxis::set_Angle(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Angle = tmp;
}

void dotSceneObjects::dotSceneAngleAxis::set_AngleUnit(std::string value)
{
	bool match = false;

	if (value == "degree") this->_AngleUnit = dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits_degree;
	if (value == "radian") this->_AngleUnit = dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits_radian;
	
	if (!match) this->_AngleUnit = dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits_INVALID;
}

void dotSceneObjects::dotSceneAngleAxis::set_x(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_x = tmp;
}

void dotSceneObjects::dotSceneAngleAxis::set_y(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_y = tmp;
}

void dotSceneObjects::dotSceneAngleAxis::set_z(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_z = tmp;
}

bool dotSceneObjects::dotSceneAngleAxis::IsValid() const
{
	// double-attributes are no useable for valid-check!
	if (this->_AngleUnit == dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits_INVALID) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// constructors & destructors
dotSceneObjects::dotSceneAngleAxis::dotSceneAngleAxis() : dotSceneObject(dotSceneEnums::angle_axis)
{
	this->set_Angle(0.0);
	this->set_AngleUnit(dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits_INVALID);
	this->set_x(0.0);
	this->set_y(0.0);
	this->set_z(0.0);
}
dotSceneObjects::dotSceneAngleAxis::dotSceneAngleAxis(std::string str_Angle, std::string str_AngleUnit, std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::angle_axis)
{
	this->set_Angle(str_Angle);
	this->set_AngleUnit(str_AngleUnit);
	this->set_x(str_x);
	this->set_y(str_y);
	this->set_z(str_z);
}

dotSceneObjects::dotSceneAngleAxis::dotSceneAngleAxis(double double_Angle, dotSceneEnums::dotSceneAngleAxisEnums::AngleAxisUnits enum_AngleUnit, double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::angle_axis)
{
	this->set_Angle(double_Angle);
	this->set_AngleUnit(enum_AngleUnit);
	this->set_x(double_x);
	this->set_y(double_y);
	this->set_z(double_z);
}