#ifndef dotSceneNode_h_
#define dotSceneNode_h_
#include "dotSceneNode.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneNode::set_name(std::string value) { _name = value; }
void dotSceneObjects::dotSceneNode::set_position(dotScenePosition value) { _position = value; }
void dotSceneObjects::dotSceneNode::set_quaternion(dotSceneQuaternion value) { _quaternion = value; }
void dotSceneObjects::dotSceneNode::set_scale(dotSceneScale value) { _scale = value; }
void dotSceneObjects::dotSceneNode::set_specific(dotSceneSpecific* value) { _specific = value; }
void dotSceneObjects::dotSceneNode::set_NodeTypeTag(dotSceneElementTags value) { _NodeTypeTag = value; }
void dotSceneObjects::dotSceneNode::set_NodeTypeName(std::string value) { _NodeTypeName = value; }

std::string dotSceneObjects::dotSceneNode::get_name() const { return _name; }
dotScenePosition dotSceneObjects::dotSceneNode::get_position() const { return _position; }
dotSceneQuaternion dotSceneObjects::dotSceneNode::get_quaternion() const { return _quaternion; }
dotSceneScale dotSceneObjects::dotSceneNode::get_scale() const { return _scale; }
dotSceneSpecific* dotSceneObjects::dotSceneNode::get_specific() const { return _specific; }
dotSceneElementTags dotSceneObjects::dotSceneNode::get_NodeTypeTag() const { return _NodeTypeTag; }
std::string dotSceneObjects::dotSceneNode::get_NodeTypeName() const { return _NodeTypeName; }
bool dotSceneObjects::dotSceneNode::addChildNode(dotSceneNode node)
{
	try
	{
		this->childNodes.push_back(node);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

/// region constructors & destructors
dotSceneObjects::dotSceneNode::dotSceneNode() : dotSceneObject(node) { }
dotSceneObjects::dotSceneNode::dotSceneNode(std::string str_name, dotScenePosition obj_position, dotSceneQuaternion obj_quaternion, dotSceneScale obj_scale, /*const dotSceneSpecific&*/dotSceneSpecific* obj_specific) : dotSceneObject(node)
{
    this->_name = str_name;
    this->_position = obj_position;
    this->_quaternion = obj_quaternion;
    this->_scale = obj_scale;
    this->_specific = obj_specific;
    this->_NodeTypeTag = obj_specific->get_NameSymbol();
    this->_NodeTypeName = obj_specific->get_Name();
}

dotSceneObjects::dotSceneNode::~dotSceneNode()
{
	delete(this->_specific);
}