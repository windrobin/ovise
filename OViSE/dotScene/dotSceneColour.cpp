#ifndef dotSceneColour_h_
#define dotSceneColour_h_
#include "dotSceneColour.h"
#endif

double dotSceneObjects::dotSceneColour::get_r() const { return this->_r; }
double dotSceneObjects::dotSceneColour::get_g() const { return this->_g; }
double dotSceneObjects::dotSceneColour::get_b() const { return this->_b; }

void dotSceneObjects::dotSceneColour::set_r(double value) { this->_r = value; }
void dotSceneObjects::dotSceneColour::set_g(double value) { this->_g = value; }
void dotSceneObjects::dotSceneColour::set_b(double value) { this->_b = value; }

void dotSceneObjects::dotSceneColour::set_r(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_r = tmp;
}

void dotSceneObjects::dotSceneColour::set_g(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_g = tmp;
}

void dotSceneObjects::dotSceneColour::set_b(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_b = tmp;
}


bool dotSceneObjects::dotSceneColour::IsValid() const
{
	// r, g & b are no useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}


///region constructors & destructors
dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneEnums::dotSceneElementTags incomingTag) : dotSceneObject(incomingTag)
{
	this->set_r(0.0);
	this->set_g(0.0);
	this->set_b(0.0);
}

dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneEnums::dotSceneElementTags incomingTag, std::string str_r, std::string str_g, std::string str_b) : dotSceneObject(incomingTag)
{
    this->set_r(str_r);
    this->set_g(str_g);
	this->set_b(str_b);
}

dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneEnums::dotSceneElementTags incomingTag, double double_r, double double_g, double double_b) : dotSceneObject(incomingTag)
{
	this->set_r(double_r);
    this->set_g(double_g);
	this->set_b(double_b);
}
