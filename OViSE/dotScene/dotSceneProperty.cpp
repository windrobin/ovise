#ifndef dotSceneProperty_h_
#define dotSceneProperty_h_
#include "dotSceneProperty.h"
#endif

/// region constructors & destructors
dotSceneObjects::dotSceneProperty::dotSceneProperty(std::string property_string_type, std::string property_string_name, std::string property_string_data) : dotSceneObject(property_tag)
{
    this->type = property_string_type;
    this->name = property_string_name;
    this->data = property_string_data;
}

dotSceneObjects::dotSceneProperty::~dotSceneProperty() { }
