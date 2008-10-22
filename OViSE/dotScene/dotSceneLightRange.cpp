#ifndef dotSceneLightRange_h_
#define dotSceneLightRange_h_
#include "dotSceneLightRange.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneLightRange::set_inner(double value) { _inner = value; }
void dotSceneObjects::dotSceneLightRange::set_outer(double value) { _outer = value; }
void dotSceneObjects::dotSceneLightRange::set_falloff(double value) { _falloff = value; }

double dotSceneObjects::dotSceneLightRange::get_inner() const { return _inner; }
double dotSceneObjects::dotSceneLightRange::get_outer() const { return _outer; }
double dotSceneObjects::dotSceneLightRange::get_falloff() const { return _falloff; }

/// region constructors & destructors
dotSceneObjects::dotSceneLightRange::dotSceneLightRange() : dotSceneObject(lightRange) { }
dotSceneObjects::dotSceneLightRange::dotSceneLightRange(std::string str_inner, std::string str_outer, std::string str_falloff) : dotSceneObject(lightRange)
{
    this->set_inner(atof(str_inner.c_str()));
    this->set_outer(atof(str_outer.c_str()));
    this->set_falloff(atof(str_falloff.c_str()));
}

dotSceneObjects::dotSceneLightRange::dotSceneLightRange(double double_inner, double double_outer, double double_falloff) : dotSceneObject(lightRange)
{
    this->set_inner(double_inner);
    this->set_outer(double_outer);
    this->set_falloff(double_falloff);
}

dotSceneObjects::dotSceneLightRange::~dotSceneLightRange() { }
