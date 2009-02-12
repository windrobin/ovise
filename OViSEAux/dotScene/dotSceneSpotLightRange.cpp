#ifndef dotSceneSpotLightRange_h_
#define dotSceneSpotLightRange_h_
#include "dotSceneSpotLightRange.h"
#endif

double dotSceneObjects::dotSceneSpotLightRange::get_Inner() const { return this->_Inner; }
double dotSceneObjects::dotSceneSpotLightRange::get_Outer() const { return this->_Outer; }
double dotSceneObjects::dotSceneSpotLightRange::get_Falloff() const { return this->_Falloff; }

void dotSceneObjects::dotSceneSpotLightRange::set_Inner(double value) { this->_Inner = value; }
void dotSceneObjects::dotSceneSpotLightRange::set_Outer(double value) { this->_Outer = value; }
void dotSceneObjects::dotSceneSpotLightRange::set_Falloff(double value) { this->_Falloff = value; }

void dotSceneObjects::dotSceneSpotLightRange::set_Inner(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Inner = tmp;
}

void dotSceneObjects::dotSceneSpotLightRange::set_Outer(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Outer = tmp;
}

void dotSceneObjects::dotSceneSpotLightRange::set_Falloff(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Falloff = tmp;
}

bool dotSceneObjects::dotSceneSpotLightRange::IsValid() const
{
	// inner, outer & falloff are not useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneSpotLightRange::dotSceneSpotLightRange() : dotSceneObject(dotSceneEnums::spotLightRange) { }
dotSceneObjects::dotSceneSpotLightRange::dotSceneSpotLightRange(std::string str_Inner, std::string str_Outer, std::string str_Falloff) : dotSceneObject(dotSceneEnums::spotLightRange)
{
    this->set_Inner(str_Inner);
    this->set_Outer(str_Outer);
    this->set_Falloff(str_Falloff);
}

dotSceneObjects::dotSceneSpotLightRange::dotSceneSpotLightRange(double double_Inner, double double_Outer, double double_Falloff) : dotSceneObject(dotSceneEnums::spotLightRange)
{
    this->set_Inner(double_Inner);
    this->set_Outer(double_Outer);
    this->set_Falloff(double_Falloff);
}

