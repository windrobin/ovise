#ifndef dotSceneNode_h_
#define dotSceneNode_h_
#include "dotSceneNode.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotSceneNode::get_name() const { return this->_name; }
std::string dotSceneObjects::dotSceneNode::get_ID() const { return this->_ID; }
bool dotSceneObjects::dotSceneNode::get_Visible() const { return this->_Visible; }
bool dotSceneObjects::dotSceneNode::get_CascadeVisibility() const { return this->_CascadeVisibility; }
bool dotSceneObjects::dotSceneNode::get_IsTarget() const { return this->_IsTarget; }

dotScenePosition dotSceneObjects::dotSceneNode::get_Position() const { return this->_Position; }
dotSceneOrientation dotSceneObjects::dotSceneNode::get_Orientation() const { return this->_Orientation; }
dotSceneScale dotSceneObjects::dotSceneNode::get_Scale() const { return this->_Scale; }
dotSceneLookTarget dotSceneObjects::dotSceneNode::get_LookTarget() const { return this->_LookTarget; }
dotSceneTrackTarget dotSceneObjects::dotSceneNode::get_TrackTarget() const { return this->_TrackTarget; }
dotSceneUserDataReference dotSceneObjects::dotSceneNode::get_UserDataReference() const { return this->_UserDataReference; }

void dotSceneObjects::dotSceneNode::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotSceneNode::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotSceneNode::set_Visible(bool value) { this->_Visible = value; }
void dotSceneObjects::dotSceneNode::set_CascadeVisibility(bool value) { this->_CascadeVisibility = value; }
void dotSceneObjects::dotSceneNode::set_IsTarget(bool value) { this->_IsTarget = value; }

void dotSceneObjects::dotSceneNode::set_Position(dotScenePosition value) { this->_Position = value; }
void dotSceneObjects::dotSceneNode::set_Orientation(dotSceneOrientation value) { this->_Orientation = value; }
void dotSceneObjects::dotSceneNode::set_Scale(dotSceneScale value) { this->_Scale = value; }
void dotSceneObjects::dotSceneNode::set_LookTarget(dotSceneLookTarget value) { this->_LookTarget = value; }
void dotSceneObjects::dotSceneNode::set_TrackTarget(dotSceneTrackTarget value) { this->_TrackTarget = value; }
void dotSceneObjects::dotSceneNode::set_UserDataReference(dotSceneUserDataReference value) { this->_UserDataReference = value; }

void dotSceneObjects::dotSceneNode::set_Visible(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Visible = true;	match = true; } 
	if (value == "false")	{ this->_Visible = false;	match = true; }

	if (!match) this->_Visible = false;
}

void dotSceneObjects::dotSceneNode::set_CascadeVisibility(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_CascadeVisibility = true;	match = true; } 
	if (value == "false")	{ this->_CascadeVisibility = false;	match = true; }

	if (!match) this->_CascadeVisibility = false;
}

void dotSceneObjects::dotSceneNode::set_IsTarget(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_IsTarget = true;	match = true; } 
	if (value == "false")	{ this->_IsTarget = false;	match = true; }

	if (!match) this->_IsTarget = false;
}


bool dotSceneObjects::dotSceneNode::HasChilds() const
{
	if (this->_ListOfChildNodes.empty() == 0) return false;
	else return true;
}

bool dotSceneObjects::dotSceneNode::HasCamera() const
{
	if (this->_ListOfCameras.empty()) return false;
	else return true;
}

bool dotSceneObjects::dotSceneNode::HasEntity() const
{
	if (this->_ListOfEntities.empty()) return false;
	else return true;
}

bool dotSceneObjects::dotSceneNode::HasLight() const
{
	if (this->_ListOfLights.empty()) return false;
	else return true;
}


bool dotSceneObjects::dotSceneNode::IsValid() const
{
	// basics valid?
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (!this->_Position.IsValid()) return false;
	if (!this->_Orientation.IsValid()) return false;
	if (!this->_Scale.IsValid()) return false;
	if (!this->_LookTarget.IsValid()) return false;
	if (!this->_TrackTarget.IsValid()) return false;
	if (!this->_UserDataReference.IsValid()) return false;

	// child-nodes valid?
	if (!this->_ListOfChildNodes.empty())
	{
		std::list<dotSceneNode>::const_iterator iterChilds = this->_ListOfChildNodes.begin();
		while(iterChilds != this->_ListOfChildNodes.end())
		{
			if (!iterChilds->IsValid()) return false;
			iterChilds++;
		}
		if (!iterChilds->IsValid()) return false;
	}

	// entities valid?
	if (!this->_ListOfEntities.empty())
	{
		std::list<dotSceneEntity>::const_iterator iterEntities = this->_ListOfEntities.begin();
		while(iterEntities != this->_ListOfEntities.end())
		{
			if (!iterEntities->IsValid()) return false;
			iterEntities++;
		}
		if (!iterEntities->IsValid()) return false;
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

	// particle systems valid?
	if (!this->_ListOfParticleSystems.empty())
	{
		std::list<dotSceneParticleSystem>::const_iterator iterParticleSystems = this->_ListOfParticleSystems.begin();
		while(iterParticleSystems != this->_ListOfParticleSystems.end())
		{
			if (!iterParticleSystems->IsValid()) return false;
			iterParticleSystems++;
		}
		if (!iterParticleSystems->IsValid()) return false;
	}

	// billboardsets valid?
	if (!this->_ListOfBillboardSets.empty())
	{
		std::list<dotSceneBillboardSet>::const_iterator iterBillboardSets = this->_ListOfBillboardSets.begin();
		while(iterBillboardSets != this->_ListOfBillboardSets.end())
		{
			if (!iterBillboardSets->IsValid()) return false;
			iterBillboardSets++;
		}
		if (!iterBillboardSets->IsValid()) return false;
	}

	// cameras valid?
	if (!this->_ListOfCameras.empty())
	{
		std::list<dotScenePlane>::const_iterator iterPlanes = this->_ListOfPlanes.begin();
		while(iterPlanes != this->_ListOfPlanes.end())
		{
			if (!iterPlanes->IsValid()) return false;
			iterPlanes++;
		}
		if (!iterPlanes->IsValid()) return false;
	}

	return true;
}

bool dotSceneObjects::dotSceneNode::addChildNode(dotSceneNode someNode)
{
	try
	{
		this->_ListOfChildNodes.push_back(someNode);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addEntity(dotSceneEntity someEntity)
{
	try
	{
		this->_ListOfEntities.push_back(someEntity);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addLight(dotSceneLight someLight)
{
	try
	{
		this->_ListOfLights.push_back(someLight);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addCamera(dotSceneCamera someCamera)
{
	try
	{
		this->_ListOfCameras.push_back(someCamera);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addParticleSystem(dotSceneParticleSystem someParticleSystem)
{
	try
	{
		this->_ListOfParticleSystems.push_back(someParticleSystem);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addBillboardSet(dotSceneBillboardSet someBillboardSet)
{
	try
	{
		this->_ListOfBillboardSets.push_back(someBillboardSet);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

bool dotSceneObjects::dotSceneNode::addPlane(dotScenePlane somePlane)
{
	try
	{
		this->_ListOfPlanes.push_back(somePlane);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

/// region constructors & destructors
dotSceneObjects::dotSceneNode::dotSceneNode() : dotSceneObject(dotSceneEnums::node)
{
	this->set_name("INITIAL_NOT_SET");
	this->set_ID("INITIAL_NOT_SET");
	this->set_CascadeVisibility(true);	// default
	this->set_Visible(true);	// default
	this->set_IsTarget(false);	// default

	this->set_Position(dotScenePosition());
	this->set_Orientation(dotSceneOrientation());
	this->set_Scale(dotSceneScale());
	this->set_LookTarget(dotSceneLookTarget());
	this->set_TrackTarget(dotSceneTrackTarget());
	this->set_UserDataReference(dotSceneUserDataReference());

	this->_ListOfBillboardSets = std::list<dotSceneBillboardSet>();
	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfChildNodes = std::list<dotSceneNode>();
	this->_ListOfEntities = std::list<dotSceneEntity>();
	this->_ListOfLights = std::list<dotSceneLight>();
	this->_ListOfParticleSystems = std::list<dotSceneParticleSystem>();
	this->_ListOfPlanes = std::list<dotScenePlane>();
}

dotSceneObjects::dotSceneNode::dotSceneNode(
	std::string str_name,
	std::string str_ID,
	std::string str_Visible,
	std::string str_CascadeVisibility,
	std::string str_IsTarget,	
	dotScenePosition obj_Position,	
	dotSceneOrientation obj_Orientation,
	dotSceneScale obj_Scale,
	dotSceneLookTarget obj_LookTarget,
	dotSceneTrackTarget obj_TrackTarget,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::node)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_CascadeVisibility(str_Visible);
	this->set_Visible(str_CascadeVisibility);
	this->set_IsTarget(str_IsTarget);

	this->set_Position(obj_Position);
	this->set_Orientation(obj_Orientation);
	this->set_Scale(obj_Scale);
	this->set_LookTarget(obj_LookTarget);
	this->set_TrackTarget(obj_TrackTarget);
	this->set_UserDataReference(obj_UserDataReference);

	this->_ListOfBillboardSets = std::list<dotSceneBillboardSet>();
	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfChildNodes = std::list<dotSceneNode>();
	this->_ListOfEntities = std::list<dotSceneEntity>();
	this->_ListOfLights = std::list<dotSceneLight>();
	this->_ListOfParticleSystems = std::list<dotSceneParticleSystem>();
	this->_ListOfPlanes = std::list<dotScenePlane>();
}

dotSceneObjects::dotSceneNode::dotSceneNode(
	std::string str_name,
	std::string str_ID,
	bool bool_Visible,
	bool bool_CascadeVisibility,
	bool bool_IsTarget,
	dotScenePosition obj_Position,	
	dotSceneOrientation obj_Orientation,
	dotSceneScale obj_Scale,
	dotSceneLookTarget obj_LookTarget,
	dotSceneTrackTarget obj_TrackTarget,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::node)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_CascadeVisibility(bool_Visible);
	this->set_Visible(bool_CascadeVisibility);
	this->set_IsTarget(bool_IsTarget);

	this->set_Position(obj_Position);
	this->set_Orientation(obj_Orientation);
	this->set_Scale(obj_Scale);
	this->set_LookTarget(obj_LookTarget);
	this->set_TrackTarget(obj_TrackTarget);
	this->set_UserDataReference(obj_UserDataReference);

	this->_ListOfBillboardSets = std::list<dotSceneBillboardSet>();
	this->_ListOfCameras = std::list<dotSceneCamera>();
	this->_ListOfChildNodes = std::list<dotSceneNode>();
	this->_ListOfEntities = std::list<dotSceneEntity>();
	this->_ListOfLights = std::list<dotSceneLight>();
	this->_ListOfParticleSystems = std::list<dotSceneParticleSystem>();
	this->_ListOfPlanes = std::list<dotScenePlane>();
}
dotSceneObjects::dotSceneNode::dotSceneNode(const dotSceneNode& CopyObject) : dotSceneObject(dotSceneEnums::node)
{
	this->set_name(CopyObject.get_name());
	this->set_ID(CopyObject.get_ID());
	this->set_CascadeVisibility(CopyObject.get_CascadeVisibility());
	this->set_Visible(CopyObject.get_Visible());
	this->set_IsTarget(CopyObject.get_IsTarget());

	this->set_Position(CopyObject.get_Position());
	this->set_Orientation(CopyObject.get_Orientation());
	this->set_Scale(CopyObject.get_Scale());
	this->set_LookTarget(CopyObject.get_LookTarget());
	this->set_TrackTarget(CopyObject.get_TrackTarget());
	this->set_UserDataReference(CopyObject.get_UserDataReference());

	this->_ListOfBillboardSets = CopyObject._ListOfBillboardSets;
	this->_ListOfCameras = CopyObject._ListOfCameras;
	this->_ListOfChildNodes = CopyObject._ListOfChildNodes;
	this->_ListOfEntities = CopyObject._ListOfEntities;
	this->_ListOfLights = CopyObject._ListOfLights;
	this->_ListOfParticleSystems = CopyObject._ListOfParticleSystems;
	this->_ListOfPlanes = CopyObject._ListOfPlanes;
}