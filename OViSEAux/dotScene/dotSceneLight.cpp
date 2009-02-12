#ifndef dotSceneLight_h_
#define dotSceneLight_h_
#include "dotSceneLight.h"
#endif

using namespace dotSceneObjects;
using namespace dotSceneEnums::dotSceneLightEnums;

std::string dotSceneLight::get_name() const { return this->_name; }
std::string dotSceneLight::get_ID() const { return this->_ID; }
LightTypes	dotSceneLight::get_Type() const { return this->_Type; }
double		dotSceneLight::get_PowerScale() const { return this->_PowerScale; }

dotSceneCommonMovableObjectParams dotSceneLight::get_CommonMovableObjectParams() const { return this->_CommonMovableObjectParams; }
dotScenePosition			dotSceneLight::get_Position() const { return this->_Position; }
dotSceneDirection			dotSceneLight::get_Direction() const { return this->_Direction; }
dotSceneColourDiffuse		dotSceneLight::get_DiffuseColour() const { return this->_DiffuseColour; }
dotSceneColourSpecular		dotSceneLight::get_SpecularColour() const { return this->_SpecularColour; }
dotSceneSpotLightRange		dotSceneLight::get_SpotLightRange() const { return this->_SpotLightRange; }
dotSceneLightAttenuation	dotSceneLight::get_LightAttenuation() const { return this->_LightAttentuation; }
dotSceneUserDataReference	dotSceneLight::get_UserDataReference() const { return this->_UserDataReference; }

void dotSceneLight::set_name(std::string value) { this->_name = value; }
void dotSceneLight::set_ID(std::string value) { this->_ID = value; }
void dotSceneLight::set_Type(LightTypes value) { this->_Type = value; }
void dotSceneLight::set_PowerScale(double value) { this->_PowerScale = value; }

void dotSceneLight::set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value) { this->_CommonMovableObjectParams = value; }
void dotSceneLight::set_Position(dotScenePosition value) { this->_Position = value; }
void dotSceneLight::set_Direction(dotSceneDirection value) { this->_Direction = value; }
void dotSceneLight::set_DiffuseColour(dotSceneColourDiffuse value) { this->_DiffuseColour = value; }
void dotSceneLight::set_SpecularColour(dotSceneColourSpecular value) { this->_SpecularColour = value; }
void dotSceneLight::set_SpotLightRange(dotSceneSpotLightRange value) { this->_SpotLightRange = value; }
void dotSceneLight::set_LightAttenuation(dotSceneLightAttenuation value) { this->_LightAttentuation = value; }
void dotSceneLight::set_UserDataReference(dotSceneUserDataReference value) { this->_UserDataReference = value; }

void dotSceneLight::set_Type(std::string value)
{
	bool match = false; 

	if (value == "Light_Point")			{ this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_Point;			match = true; } 
	if (value == "Light_Directional")	{ this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_Directional;	match = true; } 
	if (value == "Light_SpotLight")		{ this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_SpotLight;		match = true; } 
	if (value == "Light_RadPoint")		{ this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_RadPoint;		match = true; } 
	if (value == "Light_INVALID")		{ this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_INVALID;		match = true; } 

	if (!match) this->_Type = dotSceneEnums::dotSceneLightEnums::LightTypes::Light_INVALID;
}

void dotSceneLight::set_PowerScale(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_PowerScale = tmp;
}

bool dotSceneObjects::dotSceneLight::IsValid() const
{
	if (!dotSceneObjects::dotSceneSpecific::IsValid()) return false;
	if (!this->_CommonMovableObjectParams.IsValid()) return false;
	if (!this->_Position.IsValid()) return false;
	if (!this->_Direction.IsValid()) return false;
	if (!this->_DiffuseColour.IsValid()) return false;
	if (!this->_SpecularColour.IsValid()) return false;
	if (!this->_SpotLightRange.IsValid()) return false;
	if (!this->_LightAttentuation.IsValid()) return false;
	if (!this->_UserDataReference.IsValid()) return false;

	return true;
}


/// region constructors & destructors
dotSceneObjects::dotSceneLight::dotSceneLight() : dotSceneObject(dotSceneEnums::light), dotSceneSpecific(dotSceneEnums::light)
{
	this->set_name("INITIAL_NOT_SET");
	this->set_ID("INITIAL_NOT_SET");
	this->set_Type(dotSceneEnums::dotSceneLightEnums::LightTypes::Light_Point); // default is "point"
	this->set_PowerScale(1.0); // default is 1.0

	this->set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams());
	this->set_Position(dotScenePosition());
	this->set_Direction(dotSceneDirection());
	this->set_DiffuseColour(dotSceneColourDiffuse());
	this->set_SpecularColour(dotSceneColourSpecular());
	this->set_SpotLightRange(dotSceneSpotLightRange());
	this->set_LightAttenuation(dotSceneLightAttenuation());
	this->set_UserDataReference(dotSceneUserDataReference());
}

dotSceneObjects::dotSceneLight::dotSceneLight(
	std::string str_name,
	std::string str_ID,
	std::string str_Type,
	std::string str_PowerScale,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotScenePosition obj_Position,
	dotSceneDirection obj_Direction,
	dotSceneColourDiffuse obj_ColourDiffuse,
	dotSceneColourSpecular obj_ColourSpecular,
	dotSceneSpotLightRange obj_SpotLightRange,
	dotSceneLightAttenuation obj_LightAttenuation,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::light), dotSceneSpecific(dotSceneEnums::light)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_Type(str_Type);
	this->set_PowerScale(str_PowerScale);

	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_Position(obj_Position);
	this->set_Direction(obj_Direction);
	this->set_DiffuseColour(obj_ColourDiffuse);
	this->set_SpecularColour(obj_ColourSpecular);
	this->set_SpotLightRange(obj_SpotLightRange);
	this->set_LightAttenuation(obj_LightAttenuation);
	this->set_UserDataReference(obj_UserDataReference);
}

dotSceneObjects::dotSceneLight::dotSceneLight(
	std::string str_name,
	std::string str_ID,
	LightTypes enum_Type,
	double double_PowerScale,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotScenePosition obj_Position,
	dotSceneDirection obj_Direction,
	dotSceneColourDiffuse obj_ColourDiffuse,
	dotSceneColourSpecular obj_ColourSpecular,
	dotSceneSpotLightRange obj_SpotLightRange,
	dotSceneLightAttenuation obj_LightAttenuation,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::light), dotSceneSpecific(dotSceneEnums::light)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_Type(enum_Type);
	this->set_PowerScale(double_PowerScale);

	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_Position(obj_Position);
	this->set_Direction(obj_Direction);
	this->set_DiffuseColour(obj_ColourDiffuse);
	this->set_SpecularColour(obj_ColourSpecular);
	this->set_SpotLightRange(obj_SpotLightRange);
	this->set_LightAttenuation(obj_LightAttenuation);
	this->set_UserDataReference(obj_UserDataReference);
}