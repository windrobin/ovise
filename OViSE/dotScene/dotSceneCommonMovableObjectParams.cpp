#ifndef dotSceneCommonMovableObjectParams_h_
#define dotSceneCommonMovableObjectParams_h_
#include "dotSceneCommonMovableObjectParams.h"
#endif

// GET-methods
bool		dotSceneObjects::dotSceneCommonMovableObjectParams::get_Static() const { return this->_Static; }
bool		dotSceneObjects::dotSceneCommonMovableObjectParams::get_Visible() const { return this->_Visible; }
bool		dotSceneObjects::dotSceneCommonMovableObjectParams::get_CastShadows() const { return this->_CastShadows; }
double		dotSceneObjects::dotSceneCommonMovableObjectParams::get_RenderingDistance() const { return this->_RenderingDistance; }
std::string	dotSceneObjects::dotSceneCommonMovableObjectParams::get_QueryFlags() const { return this->_QueryFlags; }
std::string	dotSceneObjects::dotSceneCommonMovableObjectParams::get_VisibilityFlags() const { return this->_VisibilityFlags; }

// Set-methods
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_Static(bool value) { this->_Static = value; }
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_Visible(bool value) { this->_Visible = value; }
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_CastShadows(bool value) { this->_CastShadows = value; }
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_RenderingDistance(double value) { this->_RenderingDistance = value; }
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_QueryFlags(std::string value) { this->_QueryFlags = value; }
void dotSceneObjects::dotSceneCommonMovableObjectParams::set_VisibilityFlags(std::string value) { this->_VisibilityFlags = value; }

void dotSceneObjects::dotSceneCommonMovableObjectParams::set_Static(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Static = true;		match = true; } 
	if (value == "false")	{ this->_Static = false;	match = true; }

	if (!match) this->_Static = false;
}

void dotSceneObjects::dotSceneCommonMovableObjectParams::set_Visible(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Static = true;		match = true; } 
	if (value == "false")	{ this->_Static = false;	match = true; }

	if (!match) this->_Visible = false;
}

void dotSceneObjects::dotSceneCommonMovableObjectParams::set_CastShadows(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Static = true;		match = true; } 
	if (value == "false")	{ this->_Static = false;	match = true; }

	if (!match) this->_CastShadows = false;
}

void dotSceneObjects::dotSceneCommonMovableObjectParams::set_RenderingDistance(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_RenderingDistance = tmp;
}

bool dotSceneObjects::dotSceneCommonMovableObjectParams::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneCommonMovableObjectParams::dotSceneCommonMovableObjectParams() : dotSceneObject(dotSceneEnums::commonMovableObjectParams)
{
	this->set_Static(false);
	this->set_Visible(true);
	this->set_CastShadows(true);
	this->set_RenderingDistance(0.0);
	this->set_QueryFlags("INITIAL_NOT_SET");
	this->set_VisibilityFlags("INITIAL_NOT_SET");
}

dotSceneObjects::dotSceneCommonMovableObjectParams::dotSceneCommonMovableObjectParams(std::string str_Static, std::string str_Visible, std::string str_CastShadows, std::string str_RenderingDistance, std::string str_QueryFlags, std::string str_VisibilityFlags) : dotSceneObject(dotSceneEnums::commonMovableObjectParams)
{
	this->set_Static(str_Static);
	this->set_Visible(str_Visible);
	this->set_CastShadows(str_CastShadows);
	this->set_RenderingDistance(str_RenderingDistance);
	this->set_QueryFlags(str_QueryFlags);
	this->set_VisibilityFlags(str_VisibilityFlags);
}

dotSceneObjects::dotSceneCommonMovableObjectParams::dotSceneCommonMovableObjectParams(bool bool_Static, bool bool_Visible, bool bool_CastShadows, double double_RenderingDistance, std::string str_QueryFlags, std::string str_VisibilityFlags) : dotSceneObject(dotSceneEnums::commonMovableObjectParams)
{
	this->set_Static(bool_Static);
	this->set_Visible(bool_Visible);
	this->set_CastShadows(bool_CastShadows);
	this->set_RenderingDistance(double_RenderingDistance);
	this->set_QueryFlags(str_QueryFlags);
	this->set_VisibilityFlags(str_VisibilityFlags);
}
