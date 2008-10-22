#ifndef dotSceneLightAttenuation_h_
#define dotSceneLightAttenuation_h_
#include "dotSceneLightAttenuation.h"
#endif

#include <stdlib.h>

void dotSceneObjects::dotSceneLightAttenuation::set_range(double value){ _range = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_constant(double value){ _constant = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_linear(double value){ _linear = value; }
void dotSceneObjects::dotSceneLightAttenuation::set_quadratic(double value){ _quadratic = value; }

double dotSceneObjects::dotSceneLightAttenuation::get_range() const { return _range; }
double dotSceneObjects::dotSceneLightAttenuation::get_constant() const { return _constant; }
double dotSceneObjects::dotSceneLightAttenuation::get_linear() const { return _linear; }
double dotSceneObjects::dotSceneLightAttenuation::get_quadratic() const { return _quadratic; }

/// region constructors & destructors
dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation() : dotSceneObject(lightAttenuation) { } /// Simple constructor./// It calls the constructor of baseobject
dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation(std::string str_range, std::string str_constant, std::string str_linear, std::string str_quadratic) : dotSceneObject(lightAttenuation) /// Constructor for string-parameters. All strings will be parsed automatically to double-format./// <param name="str_range">range-value in string-format. Will be parsed to double.</param>/// <param name="str_constant">constant-value in string-format. Will be parsed to double.</param>/// <param name="str_linear">linear-value in string-format. Will be parsed to double.</param>/// <param name="str_quadratic">quadratic-value in string-format. Will be parsed to double.</param>
{
    this->set_range(atof(str_range.c_str()));
    this->set_constant(atof(str_constant.c_str()));
    this->set_linear(atof(str_linear.c_str()));
	this->set_quadratic(atof(str_quadratic.c_str()));
}

dotSceneObjects::dotSceneLightAttenuation::dotSceneLightAttenuation(double double_range, double double_constant, double double_linear, double double_quadratic) : dotSceneObject(lightAttenuation) /// Constructor for double-parameters./// <param name="double_range">range-value in double-format.</param>/// <param name="double_constant">constant-value in double-format.</param>/// <param name="double_linear">linear-value in double-format.</param>/// <param name="double_quadratic">quadratic-value in double-format.</param>
{
    this->set_range(double_range);
    this->set_constant(double_constant);
    this->set_linear(double_linear);
    this->set_quadratic(double_quadratic);
}

dotSceneObjects::dotSceneLightAttenuation::~dotSceneLightAttenuation() { }
