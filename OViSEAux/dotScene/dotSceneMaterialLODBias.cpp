#ifndef dotSceneMaterialLODBias_h_
#define dotSceneMaterialLODBias_h_
#include "dotSceneMaterialLODBias.h"
#endif

std::string dotSceneObjects::dotSceneMaterialLODBias::get_Factor() const { return this->_Factor; }
double		dotSceneObjects::dotSceneMaterialLODBias::get_MaxDetailIndex() const { return this->_MaxDetailIndex; }
double		dotSceneObjects::dotSceneMaterialLODBias::get_MinDetailIndex() const { return this->_MinDetailIndex; }

void dotSceneObjects::dotSceneMaterialLODBias::set_Factor(std::string value) { this->_Factor = value; }
void dotSceneObjects::dotSceneMaterialLODBias::set_MaxDetailIndex(double value) { this->_MaxDetailIndex = value; }
void dotSceneObjects::dotSceneMaterialLODBias::set_MinDetailIndex(double value) { this->_MinDetailIndex = value; }

void dotSceneObjects::dotSceneMaterialLODBias::set_MaxDetailIndex(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_MaxDetailIndex = tmp;
}

void dotSceneObjects::dotSceneMaterialLODBias::set_MinDetailIndex(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_MinDetailIndex = tmp;
}

bool dotSceneObjects::dotSceneMaterialLODBias::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (this->_Factor == "INVALID") return false;

	return true;
}

///region constructors & destructors
dotSceneObjects::dotSceneMaterialLODBias::dotSceneMaterialLODBias() : dotSceneObject(dotSceneEnums::materialLODBias)
{
	this->set_Factor("INVALID");	// #REQUIRED
	this->set_MaxDetailIndex(0.0);	// default: 0
	this->set_MinDetailIndex(99.0);	// default: 99
}

dotSceneObjects::dotSceneMaterialLODBias::dotSceneMaterialLODBias(std::string str_Factor, std::string  str_MaxDetailIndex, std::string str_MinDetailIndex) : dotSceneObject(dotSceneEnums::materialLODBias)
{
	this->set_Factor(str_Factor);
	this->set_MaxDetailIndex(str_MaxDetailIndex);
	this->set_MinDetailIndex(str_MinDetailIndex);
}

dotSceneObjects::dotSceneMaterialLODBias::dotSceneMaterialLODBias(std::string str_Factor, double double_MaxDetailIndex, double double_MinDetailIndex) : dotSceneObject(dotSceneEnums::materialLODBias)
{
	this->set_Factor(str_Factor);
	this->set_MaxDetailIndex(double_MaxDetailIndex);
	this->set_MinDetailIndex(double_MinDetailIndex);
}
