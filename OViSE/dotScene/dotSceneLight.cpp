#ifndef dotSceneLight_h_
#define dotSceneLight_h_
#include "dotSceneLight.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneLight::set_name(std::string value) { _name = value; }
void dotSceneObjects::dotSceneLight::set_type(std::string value) { _type = value; }
void dotSceneObjects::dotSceneLight::set_colourDiffuse(dotSceneColourDiffuse value) { _colourDiffuse = value; }
void dotSceneObjects::dotSceneLight::set_colourSpecular(dotSceneColourSpecular value) { _colourSpecular = value; }
void dotSceneObjects::dotSceneLight::set_normal(dotSceneNormal value) { _normal = value; }
void dotSceneObjects::dotSceneLight::set_lightRange(dotSceneLightRange value) { _lightRange = value; }
void dotSceneObjects::dotSceneLight::set_lightAttenuation(dotSceneLightAttenuation value) { _lightAttenuation = value; }

std::string dotSceneObjects::dotSceneLight::get_name() const { return _name; }
std::string dotSceneObjects::dotSceneLight::get_type() const { return _type; }
dotSceneColourDiffuse dotSceneObjects::dotSceneLight::get_colourDiffuse() const { return _colourDiffuse; }
dotSceneColourSpecular dotSceneObjects::dotSceneLight::get_colourSpecular() const { return _colourSpecular; }
dotSceneNormal dotSceneObjects::dotSceneLight::get_normal() const { return _normal; }
dotSceneLightRange dotSceneObjects::dotSceneLight::get_lightRange() const { return _lightRange; }
dotSceneLightAttenuation dotSceneObjects::dotSceneLight::get_lightAttenuation() const { return _lightAttenuation; }

/// region constructors & destructors
dotSceneObjects::dotSceneLight::dotSceneLight() : dotSceneSpecific(light) { } /// Simple constructor. It calls the constructor of baseobject
dotSceneObjects::dotSceneLight::dotSceneLight(std::string str_name, std::string str_type, dotSceneColourDiffuse obj_colourDiffuse, dotSceneColourSpecular obj_colourSpecular, dotSceneNormal obj_normal, dotSceneLightRange obj_lightRange, dotSceneLightAttenuation obj_lightAttenuation) : dotSceneSpecific(light) /// The dotScene-objects have to be constructed before./// <param name="str_name">name-value in string-format.</param>/// <param name="str_type">type-value in string-format.</param>/// <param name="obj_colourDiffuse">A pre-constrcted dotSceneColourDiffuse-object.</param>/// <param name="obj_colourSpecular">A pre-constrcted dotSceneColourSpecular-object.</param>/// <param name="obj_normal">A pre-constrcted dotSceneNormal-object.</param>/// <param name="obj_lightRange">A pre-constrcted dotSceneLightRange-object.</param>/// <param name="obj_lightAttenuation">A pre-constrcted dotSceneLightAttenuation-object.</param>
{
    this->set_name(str_name);
    this->set_type(str_type);
    this->set_colourDiffuse(obj_colourDiffuse);
    this->set_colourSpecular(obj_colourSpecular);
    this->set_normal(obj_normal);
    this->set_lightRange(obj_lightRange);
    this->set_lightAttenuation(obj_lightAttenuation);
}
dotSceneObjects::dotSceneLight::~dotSceneLight() { }
