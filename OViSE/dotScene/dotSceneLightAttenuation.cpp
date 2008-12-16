#ifndef dotSceneLightAttenuation_h_
#define dotSceneLightAttenuation_h_
#include "dotSceneLightAttenuation.h"
#endif

double dotSceneObjects::dotSceneLightAttenuation::get_Range() const { return this->_Range; }
double dotSceneObjects::dotSceneLightAttenuation::get_Constant() const { return this->_Constant; }
double dotSceneObjects::dotSceneLightAttenuation::get_Linear() const { return this->_Linear; }
double dotSceneObjects::dotSceneLightAttenuation::get_Quadratic() const { return this->_Quadratic; }

void dotSceneObjects::dotSceneLightAttenuation::set_Range(double value){ this->_Range = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_Constant(double value){ this->_Constant = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_Linear(double value){ this->_Linear = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_Quadratic(double value){ this->_Quadratic = value; }

void dotSceneObjects::dotSceneLightAttenuation::set_Range(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Range = tmp;
}

void dotSceneObjects::dotSceneLightAttenuation::set_Constant(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Constant = tmp;
}

void dotSceneObjects::dotSceneLightAttenuation::set_Linear(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Linear = tmp;
}

void dotSceneObjects::dotSceneLightAttenuation::set_Quadratic(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Quadratic = tmp;
}


bool dotSceneObjects::dotSceneLightAttenuation::IsValid() const
{
	// Range, Constant, Linear & Quadratic are not useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation() : dotSceneObject(dotSceneEnums::lightAttenuation) { }
dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation(std::string str_Range, std::string str_Constant, std::string str_Linear, std::string str_Quadratic) : dotSceneObject(dotSceneEnums::lightAttenuation)
{
    this->set_Range(str_Range);
    this->set_Constant(str_Constant);
    this->set_Linear(str_Linear);
	this->set_Quadratic(str_Quadratic);
}

dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation(double double_Range, double double_Constant, double double_Linear, double double_Quadratic) : dotSceneObject(dotSceneEnums::lightAttenuation)
{
    this->set_Range(double_Range);
    this->set_Constant(double_Constant);
    this->set_Linear(double_Linear);
    this->set_Quadratic(double_Quadratic);
}
