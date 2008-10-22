#ifndef dotSceneItem_h_
#define dotSceneItem_h_
#include "dotSceneItem.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneItem::set_type(std::string value) { _type = value; }
void dotSceneObjects::dotSceneItem::set_file(dotSceneFile value) { _file = value; }

std::string dotSceneObjects::dotSceneItem::get_type() const { return _type; }
dotSceneFile dotSceneObjects::dotSceneItem::get_file() const { return _file; }

/// region constructors & destructors
dotSceneObjects::dotSceneItem::dotSceneItem() : dotSceneObject(item) { }
dotSceneObjects::dotSceneItem::dotSceneItem(std::string str_type, dotSceneFile obj_file) : dotSceneObject(item)
{
    this->_type = str_type;
    this->_file = obj_file;
}

dotSceneObjects::dotSceneItem::~dotSceneItem() { }
