#ifndef dotSceneFog_h_
#define dotSceneFog_h_
#include "dotSceneFog.h"
#endif

using namespace dotSceneObjects;

double dotSceneObjects::dotSceneFog::get_linearStart() const { return this->_linearStart; }
double dotSceneObjects::dotSceneFog::get_linearEnd() const { return this->_linearEnd; }
std::string dotSceneObjects::dotSceneFog::get_mode() const { return this->_mode; }
dotSceneColourDiffuse dotSceneObjects::dotSceneFog::get_colourDiffuse() const { return this->_colourDiffuse; }

void dotSceneObjects::dotSceneFog::set_linearStart(double value) { this->_linearStart = value; }
void dotSceneObjects::dotSceneFog::set_linearEnd(double value) { this->_linearEnd = value; }
void dotSceneObjects::dotSceneFog::set_linearStart(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_linearStart = tmp;
}

void dotSceneObjects::dotSceneFog::set_linearEnd(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_linearEnd = tmp;
}

void dotSceneObjects::dotSceneFog::set_mode(std::string value) { this->_mode = value; }
void dotSceneObjects::dotSceneFog::set_colourDiffuse(dotSceneColourDiffuse value) { this->_colourDiffuse = value; }

bool dotSceneObjects::dotSceneFog::IsValid() const
{
	if (this->_mode == "INVALID") return false;
	if (!this->_colourDiffuse.IsValid()) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	
	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneFog::dotSceneFog() : dotSceneObject(dotSceneEnums::fog)
{
	double dummy = 0;
	this->set_linearStart(dummy);
	this->set_linearEnd(dummy);
	this->set_mode("INVALID");
	this->_colourDiffuse = dotSceneColourDiffuse(0.0, 0.0, 0.0);
} 
dotSceneObjects::dotSceneFog::dotSceneFog(std::string str_linearStart, std::string str_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour) : dotSceneObject(dotSceneEnums::fog)
{
    this->set_linearStart(str_linearStart);
    this->set_linearEnd(str_linearEnd);
    this->set_mode(str_mode);
    this->set_colourDiffuse(obj_diffuseColour);
}

dotSceneObjects::dotSceneFog::dotSceneFog(double double_linearStart, double double_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour) : dotSceneObject(dotSceneEnums::fog)
{
    this->set_linearStart(double_linearStart);
    this->set_linearEnd(double_linearEnd);
    this->set_mode(str_mode);
    this->set_colourDiffuse(obj_diffuseColour);
}

