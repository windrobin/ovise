#ifndef dotSceneMeshLODBias_h_
#define dotSceneMeshLODBias_h_
#include "dotSceneMeshLODBias.h"
#endif

std::string dotSceneObjects::dotSceneMeshLODBias::get_Factor() const { return this->_Factor; }
double		dotSceneObjects::dotSceneMeshLODBias::get_MaxDetailIndex() const { return this->_MaxDetailIndex; }
double		dotSceneObjects::dotSceneMeshLODBias::get_MinDetailIndex() const { return this->_MinDetailIndex; }

void dotSceneObjects::dotSceneMeshLODBias::set_Factor(std::string value) { this->_Factor = value; }
void dotSceneObjects::dotSceneMeshLODBias::set_MaxDetailIndex(double value) { this->_MaxDetailIndex = value; }
void dotSceneObjects::dotSceneMeshLODBias::set_MinDetailIndex(double value) { this->_MinDetailIndex = value; }

void dotSceneObjects::dotSceneMeshLODBias::set_MaxDetailIndex(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_MaxDetailIndex = tmp;
}

void dotSceneObjects::dotSceneMeshLODBias::set_MinDetailIndex(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_MinDetailIndex = tmp;
}

bool dotSceneObjects::dotSceneMeshLODBias::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (this->_Factor == "INVALID") return false;

	return true;
}

///region constructors & destructors
dotSceneObjects::dotSceneMeshLODBias::dotSceneMeshLODBias() : dotSceneObject(dotSceneEnums::meshLODBias)
{
	this->set_Factor("INVALID");	// #REQUIRED
	this->set_MaxDetailIndex(0.0);	// default: 0
	this->set_MinDetailIndex(99.0);	// default: 99
}

dotSceneObjects::dotSceneMeshLODBias::dotSceneMeshLODBias(std::string str_Factor, std::string  str_MaxDetailIndex, std::string str_MinDetailIndex) : dotSceneObject(dotSceneEnums::meshLODBias)
{
	this->set_Factor(str_Factor);
	this->set_MaxDetailIndex(str_MaxDetailIndex);
	this->set_MinDetailIndex(str_MinDetailIndex);
}

dotSceneObjects::dotSceneMeshLODBias::dotSceneMeshLODBias(std::string str_Factor, double double_MaxDetailIndex, double double_MinDetailIndex) : dotSceneObject(dotSceneEnums::meshLODBias)
{
	this->set_Factor(str_Factor);
	this->set_MaxDetailIndex(double_MaxDetailIndex);
	this->set_MinDetailIndex(double_MinDetailIndex);
}
