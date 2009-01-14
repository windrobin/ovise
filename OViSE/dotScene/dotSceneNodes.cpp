#ifndef dotSceneNodes_h_
#define dotSceneNodes_h_
#include "dotSceneNodes.h"
#endif

using namespace dotSceneObjects;

bool dotSceneObjects::dotSceneNodes::get_Visible() const { return this->_Visible; }
bool dotSceneObjects::dotSceneNodes::get_CascadeVisibility() const { return this->_CascadeVisibility; }
dotScenePosition dotSceneObjects::dotSceneNodes::get_Position() const { return this->_Position; }
dotSceneOrientation dotSceneObjects::dotSceneNodes::get_Orientation() const { return this->_Orientation; }
dotSceneScale dotSceneObjects::dotSceneNodes::get_Scale() const { return this->_Scale; }

void dotSceneObjects::dotSceneNodes::set_Visible(bool value) { this->_Visible = value; }
void dotSceneObjects::dotSceneNodes::set_CascadeVisibility(bool value) { this->_CascadeVisibility = value; }
void dotSceneObjects::dotSceneNodes::set_Position(dotScenePosition value) { this->_Position = value; }
void dotSceneObjects::dotSceneNodes::set_Orientation(dotSceneOrientation value) { this->_Orientation = value; }
void dotSceneObjects::dotSceneNodes::set_Scale(dotSceneScale value) { this->_Scale = value; }

void dotSceneObjects::dotSceneNodes::set_Visible(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Visible = true;	match = true; } 
	if (value == "false")	{ this->_Visible = false;	match = true; }

	if (!match) this->_Visible = false;
}

void dotSceneObjects::dotSceneNodes::set_CascadeVisibility(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_CascadeVisibility = true;	match = true; } 
	if (value == "false")	{ this->_CascadeVisibility = false;	match = true; }

	if (!match) this->_CascadeVisibility = false;
}




bool dotSceneObjects::dotSceneNodes::IsValid() const
{
	// basics valid?
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (!this->_Position.IsValid()) return false;
	if (!this->_Orientation.IsValid()) return false;
	if (!this->_Scale.IsValid()) return false;

	// child-nodes valid?
	if (!this->_ListOfNodes.empty())
	{
		std::list<dotSceneNode>::const_iterator iterNodes = this->_ListOfNodes.begin();
		while(iterNodes != this->_ListOfNodes.end())
		{
			if (!iterNodes->IsValid()) return false;
			iterNodes++;
		}
		if (!iterNodes->IsValid()) return false;
	}

		// lights valid?
	if (!this->_ListOfLights.empty())
	{
		std::list<dotSceneLight>::const_iterator iterLights = this->_ListOfLights.begin();
		while(iterLights != this->_ListOfLights.end())
		{
			if (!iterLights->IsValid()) return false;
			iterLights++;
		}
		if (!iterLights->IsValid()) return false;
	}

	// cameras valid?
	if (!this->_ListOfCameras.empty())
	{
		std::list<dotSceneCamera>::const_iterator iterCameras = this->_ListOfCameras.begin();
		while(iterCameras != this->_ListOfCameras.end())
		{
			if (!iterCameras->IsValid()) return false;
			iterCameras++;
		}
		if (!iterCameras->IsValid()) return false;
	}

	return true;
}

bool dotSceneObjects::dotSceneNodes::addNode(dotSceneNode someNode)
{
	try
	{
		this->_ListOfNodes.push_back(someNode);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNodes::addLight(dotSceneLight someLight)
{
	try
	{
		this->_ListOfLights.push_back(someLight);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNodes::addCamera(dotSceneCamera someCamera)
{
	try
	{
		this->_ListOfCameras.push_back(someCamera);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

/// region constructors & destructors
dotSceneObjects::dotSceneNodes::dotSceneNodes() : dotSceneObject(dotSceneEnums::nodes)
{
	this->set_CascadeVisibility(true);	// default
	this->set_Visible(true);	// default
	this->set_Position(dotScenePosition());
	this->set_Orientation(dotSceneOrientation());
	this->set_Scale(dotSceneScale());

	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfNodes = std::list<dotSceneNode>();
	this->_ListOfLights = std::list<dotSceneLight>();
}

dotSceneObjects::dotSceneNodes::dotSceneNodes(
	std::string str_Visible,
	std::string str_CascadeVisibility,	
	dotScenePosition obj_Position,	
	dotSceneOrientation obj_Orientation,
	dotSceneScale obj_Scale) : dotSceneObject(dotSceneEnums::nodes)
{
	this->set_CascadeVisibility(str_Visible);
	this->set_Visible(str_CascadeVisibility);
	this->set_Position(obj_Position);
	this->set_Orientation(obj_Orientation);
	this->set_Scale(obj_Scale);

	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfNodes = std::list<dotSceneNode>();
	this->_ListOfLights = std::list<dotSceneLight>();
}

dotSceneObjects::dotSceneNodes::dotSceneNodes(
	bool bool_Visible,
	bool bool_CascadeVisibility,
	dotScenePosition obj_Position,	
	dotSceneOrientation obj_Orientation,
	dotSceneScale obj_Scale) : dotSceneObject(dotSceneEnums::nodes)
{
	this->set_CascadeVisibility(bool_Visible);
	this->set_Visible(bool_CascadeVisibility);
	this->set_Position(obj_Position);
	this->set_Orientation(obj_Orientation);
	this->set_Scale(obj_Scale);

	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfNodes = std::list<dotSceneNode>();
	this->_ListOfLights = std::list<dotSceneLight>();
}
dotSceneObjects::dotSceneNodes::dotSceneNodes(const dotSceneNodes& CopyObject) : dotSceneObject(dotSceneEnums::nodes)
{
	this->set_CascadeVisibility(CopyObject.get_CascadeVisibility());
	this->set_Visible(CopyObject.get_Visible());

	this->set_Position(CopyObject.get_Position());
	this->set_Orientation(CopyObject.get_Orientation());
	this->set_Scale(CopyObject.get_Scale());

	this->_ListOfCameras = CopyObject._ListOfCameras;
	this->_ListOfNodes = CopyObject._ListOfNodes;
	this->_ListOfLights = CopyObject._ListOfLights;
}
