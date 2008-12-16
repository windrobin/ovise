#ifndef dotSceneProperty_h_
#define dotSceneProperty_h_
#include "dotSceneProperty.h"
#endif

std::string dotSceneObjects::dotSceneProperty::get_Type() const { return this->_Type; }
std::string dotSceneObjects::dotSceneProperty::get_Name() const { return this->_Name; }
std::string dotSceneObjects::dotSceneProperty::get_Data() const { return this->_Data; }

void dotSceneObjects::dotSceneProperty::set_Type(std::string value) { this->_Type = value; }
void dotSceneObjects::dotSceneProperty::set_Name(std::string value) { this->_Name = value; }
void dotSceneObjects::dotSceneProperty::set_Data(std::string value) { this->_Data = value; }

bool dotSceneObjects::dotSceneProperty::IsValid() const
{
	if (this->_Type == "INVALID") return false;
    if (this->_Name == "INVALID") return false;
    if (this->_Data == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneProperty::dotSceneProperty() : dotSceneObject(dotSceneEnums::property_tag)
{
	this->_Type = "INVALID";
    this->_Name = "INVALID";
    this->_Data = "INVALID";
}

dotSceneObjects::dotSceneProperty::dotSceneProperty(std::string str_Type, std::string str_Name, std::string str_Data) : dotSceneObject(dotSceneEnums::property_tag)
{
	this->_Type = "INVALID";
    this->_Name = "INVALID";
    this->_Data = "INVALID";

    this->set_Type(str_Type);
    this->set_Name(str_Name);
    this->set_Data(str_Data);
}

dotSceneObjects::dotSceneProperty::~dotSceneProperty() { }
