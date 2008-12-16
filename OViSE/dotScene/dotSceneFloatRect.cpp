#ifndef dotSceneFloatRect_h_
#define dotSceneFloatRect_h_
#include "dotSceneFloatRect.h"
#endif

double dotSceneObjects::dotSceneFloatRect::get_Left() const { return this->_Left; }
double dotSceneObjects::dotSceneFloatRect::get_Top() const { return this->_Top; }
double dotSceneObjects::dotSceneFloatRect::get_Right() const { return this->_Right; }
double dotSceneObjects::dotSceneFloatRect::get_Bottom() const { return this->_Bottom; }

void dotSceneObjects::dotSceneFloatRect::set_Left(double value) { this->_Left = value; }
void dotSceneObjects::dotSceneFloatRect::set_Top(double value) { this->_Top = value; }
void dotSceneObjects::dotSceneFloatRect::set_Right(double value) { this->_Right = value; }
void dotSceneObjects::dotSceneFloatRect::set_Bottom(double value) { this->_Bottom = value; }

void dotSceneObjects::dotSceneFloatRect::set_Left(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Left = tmp;
}

void dotSceneObjects::dotSceneFloatRect::set_Top(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Top = tmp;
}

void dotSceneObjects::dotSceneFloatRect::set_Right(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Right = tmp;
}

void dotSceneObjects::dotSceneFloatRect::set_Bottom(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Bottom = tmp;
}

bool dotSceneObjects::dotSceneFloatRect::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

///region constructors & destructors
dotSceneObjects::dotSceneFloatRect::dotSceneFloatRect() : dotSceneObject(dotSceneEnums::floatRect)
{
	this->set_Left(0.0);
	this->set_Top(0.0);
	this->set_Right(0.0);
	this->set_Bottom(0.0);
}

dotSceneObjects::dotSceneFloatRect::dotSceneFloatRect(std::string str_Left, std::string str_Top, std::string str_Right, std::string str_Bottom) : dotSceneObject(dotSceneEnums::floatRect)
{
	this->set_Left(str_Left);
	this->set_Top(str_Top);
	this->set_Right(str_Right);
	this->set_Bottom(str_Bottom);
}

dotSceneObjects::dotSceneFloatRect::dotSceneFloatRect(double double_Left, double double_Top, double double_Right, double double_Bottom) : dotSceneObject(dotSceneEnums::floatRect)
{
	this->set_Left(double_Left);
	this->set_Top(double_Top);
	this->set_Right(double_Right);
	this->set_Bottom(double_Bottom);
}
