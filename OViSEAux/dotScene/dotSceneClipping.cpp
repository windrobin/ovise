#ifndef dotSceneClipping_h_
#define dotSceneClipping_h_
#include "dotSceneClipping.h"
#endif

double dotSceneObjects::dotSceneClipping::get_NearPlaneDist() const { return this->_NearPlaneDist; }
double dotSceneObjects::dotSceneClipping::get_FarPlaneDist() const { return this->_FarPlaneDist; }

void dotSceneObjects::dotSceneClipping::set_NearPlaneDist(double value) { this->_NearPlaneDist = value; }
void dotSceneObjects::dotSceneClipping::set_FarPlaneDist(double value) { this->_FarPlaneDist = value; }

void dotSceneObjects::dotSceneClipping::set_NearPlaneDist(std::string value)
{
	double tmp;
	sscanf_s(value.c_str(), "%lf", &tmp);
	this->set_NearPlaneDist(tmp);
}

void dotSceneObjects::dotSceneClipping::set_FarPlaneDist(std::string value)
{
	double tmp;
	sscanf_s(value.c_str(), "%lf", &tmp);
	this->set_FarPlaneDist(tmp);
}


bool dotSceneObjects::dotSceneClipping::IsValid() const
{
	// NearPlaneDist & FarPlaneDist are no useable for valid-check!
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneClipping::dotSceneClipping() : dotSceneObject(dotSceneEnums::clipping)
{
	double dummy = 0;
	this->set_NearPlaneDist(dummy);
	this->set_FarPlaneDist(dummy);
}

dotSceneObjects::dotSceneClipping::dotSceneClipping(std::string str_NearPlaneDist, std::string str_FarPlaneDist) : dotSceneObject(dotSceneEnums::clipping)
{
	this->set_NearPlaneDist(str_NearPlaneDist);
    this->set_FarPlaneDist(str_FarPlaneDist);
}

dotSceneObjects::dotSceneClipping::dotSceneClipping(double double_NearPlaneDist, double double_FarPlaneDist) : dotSceneObject(dotSceneEnums::clipping)
{
    this->set_NearPlaneDist(double_NearPlaneDist);
    this->set_FarPlaneDist(double_FarPlaneDist);
}

dotSceneObjects::dotSceneClipping::~dotSceneClipping() { }
