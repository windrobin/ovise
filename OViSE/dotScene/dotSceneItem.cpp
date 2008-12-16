#ifndef dotSceneItem_h_
#define dotSceneItem_h_
#include "dotSceneItem.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneItem::set_Type(std::string value) { this->_Type = value; }
void dotSceneObjects::dotSceneItem::set_File(dotSceneFile value) { this->_File = value; }

std::string dotSceneObjects::dotSceneItem::get_Type() const { return this->_Type; }
dotSceneFile dotSceneObjects::dotSceneItem::get_File() const { return this->_File; }

bool dotSceneObjects::dotSceneItem::IsValid() const
{
	if (this->_Type == "INVALID") return false;
	if (!this->_File.IsValid()) return false;
	
	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneItem::dotSceneItem() : dotSceneObject(dotSceneEnums::item)
{
	this->_Type = "INVALID";
	this->_File = dotSceneFile();
}

dotSceneObjects::dotSceneItem::dotSceneItem(std::string str_Type, dotSceneFile obj_File) : dotSceneObject(dotSceneEnums::item)
{
	this->_Type = "INVALID";
	this->_File = dotSceneFile();

    this->_Type = str_Type;
    this->_File = obj_File;
}

dotSceneObjects::dotSceneItem::~dotSceneItem() { }
