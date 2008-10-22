#ifndef dotSceneFog_h_
#define dotSceneFog_h_
#include "dotSceneFog.h"
#endif

#include <stdlib.h>

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneFog::set_linearStart(double value) { _linearStart = value; }
void dotSceneObjects::dotSceneFog::set_linearEnd(double value) { _linearEnd = value; }
void dotSceneObjects::dotSceneFog::set_mode(std::string value) { _mode = value; }
void dotSceneObjects::dotSceneFog::set_colourDiffuse(dotSceneColourDiffuse value) { _colourDiffuse = value; }

double dotSceneObjects::dotSceneFog::get_linearStart() const { return _linearStart; }
double dotSceneObjects::dotSceneFog::get_linearEnd() const { return _linearEnd; }
std::string dotSceneObjects::dotSceneFog::get_mode() const { return _mode; }
dotSceneColourDiffuse dotSceneObjects::dotSceneFog::get_colourDiffuse() const { return _colourDiffuse; }

/// region constructors & destructors
dotSceneObjects::dotSceneFog::dotSceneFog() : dotSceneObject(fog) { } 
dotSceneObjects::dotSceneFog::dotSceneFog(std::string str_linearStart, std::string str_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour) : dotSceneObject(fog)
{
    this->set_linearStart(atof(str_linearStart.c_str()));
    this->set_linearEnd(atof(str_linearEnd.c_str()));
    this->set_mode(str_mode.c_str());
    this->set_colourDiffuse(obj_diffuseColour);
}

dotSceneObjects::dotSceneFog::dotSceneFog(double double_linearStart, double double_linearEnd, std::string str_mode, dotSceneColourDiffuse obj_diffuseColour) : dotSceneObject(fog)
{
    this->set_linearStart(double_linearStart);
    this->set_linearEnd(double_linearEnd);
    this->set_mode(str_mode);
    this->set_colourDiffuse(obj_diffuseColour);
}

dotSceneObjects::dotSceneFog::~dotSceneFog() { }
