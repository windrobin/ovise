#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

double dotSceneObjects::dotSceneColourDiffuse::get_a() const
{
	return this->_a;
}

void dotSceneObjects::dotSceneColourDiffuse::set_a(double value)
{
	this->_a = value;
	this->_UseAlpha = true; 
}

void dotSceneObjects::dotSceneColourDiffuse::set_a(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_a = tmp;
	this->_UseAlpha = true; 
}

bool dotSceneObjects::dotSceneColourDiffuse::HasAlpha() const
{
	return this->_UseAlpha;
}

///region constructors & destructors
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse() : dotSceneObject(dotSceneEnums::colourDiffuse), dotSceneColour(dotSceneEnums::colourDiffuse) { this->_UseAlpha = false; }
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(std::string str_r, std::string str_g, std::string str_b) : dotSceneObject(dotSceneEnums::colourDiffuse), dotSceneColour(dotSceneEnums::colourDiffuse, str_r, str_g, str_b) { this->_UseAlpha = false; }
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(double double_r, double double_g, double double_b) : dotSceneObject(dotSceneEnums::colourDiffuse), dotSceneColour(dotSceneEnums::colourDiffuse, double_r, double_g, double_b) { this->_UseAlpha = false; }
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(std::string str_r, std::string str_g, std::string str_b, std::string str_a) : dotSceneObject(dotSceneEnums::colourDiffuse), dotSceneColour(dotSceneEnums::colourDiffuse, str_r, str_g, str_b)
{
	this->set_a(str_a);
}

dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(double double_r, double double_g, double double_b, double double_a) : dotSceneObject(dotSceneEnums::colourDiffuse), dotSceneColour(dotSceneEnums::colourDiffuse, double_r, double_g, double_b)
{
	this->set_a(double_a);
}

