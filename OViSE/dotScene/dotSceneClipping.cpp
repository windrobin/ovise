#ifndef dotSceneClipping_h_
#define dotSceneClipping_h_
#include "dotSceneClipping.h"
#endif

void dotSceneObjects::dotSceneClipping::set_nearPlaneDist(double value) { _nearPlaneDist = value; }
void dotSceneObjects::dotSceneClipping::set_farPlaneDist(double value) { _farPlaneDist = value; }

double dotSceneObjects::dotSceneClipping::get_nearPlaneDist() const { return _nearPlaneDist; }
double dotSceneObjects::dotSceneClipping::get_farPlaneDist() const { return _farPlaneDist; }

/// region constructors & destructors
dotSceneObjects::dotSceneClipping::dotSceneClipping() : dotSceneObject(clipping) { }
dotSceneObjects::dotSceneClipping::dotSceneClipping(std::string str_nearPlaneDist, std::string str_farPlaneDist) : dotSceneObject(clipping)
{
	double tmp1, tmp2;
	sscanf(str_nearPlaneDist.c_str(), "%lf", &tmp1);
	this->set_nearPlaneDist(tmp1);
	sscanf(str_farPlaneDist.c_str(), "%lf", &tmp2);
    this->set_farPlaneDist(tmp2);
}

dotSceneObjects::dotSceneClipping::dotSceneClipping(double double_nearPlaneDist, double double_farPlaneDist) : dotSceneObject(clipping)
{
    this->set_nearPlaneDist(double_nearPlaneDist);
    this->set_farPlaneDist(double_farPlaneDist);
}

dotSceneObjects::dotSceneClipping::~dotSceneClipping() { }
