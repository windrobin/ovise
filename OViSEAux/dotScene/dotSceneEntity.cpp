#ifndef dotSceneEntity_h_
#define dotSceneEntity_h_
#include "dotSceneEntity.h"
#endif

using namespace dotSceneEnums::dotSceneEntityEnums;
using namespace dotSceneObjects;

// GET-methods
std::string dotSceneObjects::dotSceneEntity::get_meshFile() const { return this->_meshFile; }
std::string dotSceneObjects::dotSceneEntity::get_name() const { return this->_name; }

std::string dotSceneObjects::dotSceneEntity::get_ID() const { return this->_ID; }
std::string dotSceneObjects::dotSceneEntity::get_materialName() const { return this->_materialName; }
bool		dotSceneObjects::dotSceneEntity::get_displaySkeleton() const { return this->_displaySkeleton; }
bool		dotSceneObjects::dotSceneEntity::get_polygonModeOverrideable() const { return this->_polygonModeOverrideable; }
std::string dotSceneObjects::dotSceneEntity::get_softwareAnimationRequests() const { return this->_softwareAnimationRequests; }
std::string dotSceneObjects::dotSceneEntity::get_softwareAnimationRequestsNormalsAlso() const { return this->_softwareAnimationRequestsNormalsAlso; }
BufferUsage dotSceneObjects::dotSceneEntity::get_vertexBufferUsage() const { return this->_vertexBufferUsage; }
bool		dotSceneObjects::dotSceneEntity::get_vertexBufferUseShadow() const { return this->_vertexBufferUseShadow; }
BufferUsage dotSceneObjects::dotSceneEntity::get_indexBufferUsage() const { return this->_indexBufferUsage; }
bool		dotSceneObjects::dotSceneEntity::get_indexBufferUseShadow() const { return this->_indexBufferUseShadow; }

dotSceneCommonMovableObjectParams	dotSceneObjects::dotSceneEntity::get_CommonMovableObjectParams() const { return this->_CommonMovableObjectParams; }
dotSceneMeshLODBias					dotSceneObjects::dotSceneEntity::get_MeshLODBias() const { return this->_MeshLODBias; }
dotSceneMaterialLODBias				dotSceneObjects::dotSceneEntity::get_MaterialLODBias() const { return this->_MaterialLODBias; }
dotSceneUserDataReference			dotSceneObjects::dotSceneEntity::get_UserDataReference() const { return this->_UserDataReference; }

// Set-methods
void dotSceneObjects::dotSceneEntity::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotSceneEntity::set_meshFile(std::string value) { this->_meshFile = value; }

void dotSceneObjects::dotSceneEntity::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotSceneEntity::set_materialName(std::string value) { this->_materialName = value; }
void dotSceneObjects::dotSceneEntity::set_displaySkeleton(bool value) { this->_displaySkeleton = value; }
void dotSceneObjects::dotSceneEntity::set_polygonModeOverrideable(bool value) { this->_polygonModeOverrideable = value; }
void dotSceneObjects::dotSceneEntity::set_softwareAnimationRequests(std::string value) { this->_softwareAnimationRequests = value; }
void dotSceneObjects::dotSceneEntity::set_softwareAnimationRequestsNormalsAlso(std::string value) { this->_softwareAnimationRequestsNormalsAlso = value; }
void dotSceneObjects::dotSceneEntity::set_vertexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage value) { this->_vertexBufferUsage = value; }
void dotSceneObjects::dotSceneEntity::set_vertexBufferUseShadow(bool value) { this->_vertexBufferUseShadow = value; }
void dotSceneObjects::dotSceneEntity::set_indexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage value) { this->_indexBufferUsage = value; }
void dotSceneObjects::dotSceneEntity::set_indexBufferUseShadow(bool value) { this->_indexBufferUseShadow = value; }

void dotSceneObjects::dotSceneEntity::set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value) { this->_CommonMovableObjectParams = value; }
void dotSceneObjects::dotSceneEntity::set_MeshLODBias(dotSceneMeshLODBias value) { this->_MeshLODBias = value; }
void dotSceneObjects::dotSceneEntity::set_MaterialLODBias(dotSceneMaterialLODBias value) { this->_MaterialLODBias = value; }
void dotSceneObjects::dotSceneEntity::set_UserDataReference(dotSceneUserDataReference value) { this->_UserDataReference = value; }

void dotSceneObjects::dotSceneEntity::set_displaySkeleton(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_displaySkeleton = true;	match = true; } 
	if (value == "false")	{ this->_displaySkeleton = false;	match = true; }

	if (!match) this->_displaySkeleton = false;
}
void dotSceneObjects::dotSceneEntity::set_polygonModeOverrideable(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_polygonModeOverrideable = true;		match = true; } 
	if (value == "false")	{ this->_polygonModeOverrideable = false;	match = true; }

	if (!match) this->_polygonModeOverrideable = false;
}
void dotSceneObjects::dotSceneEntity::set_vertexBufferUsage(std::string value)
{
	bool match = false; 
	
	if (value == "discardable")					{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_discardable;					match = true; } 
	if (value == "dynamic")						{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamic;						match = true; }
	if (value == "dynamicWriteOnly")			{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamicWriteOnly;				match = true; }
	if (value == "dynamicWriteOnlyDiscardable") { this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamicWriteOnlyDiscardable;	match = true; }
	if (value == "static")						{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_static;						match = true; }
	if (value == "staticWriteOnly")				{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_staticWriteOnly;				match = true; }
	if (value == "writeOnly")					{ this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_writeOnly;						match = true; }

	if (!match) this->_vertexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_INVALID;
}
void dotSceneObjects::dotSceneEntity::set_vertexBufferUseShadow(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_vertexBufferUseShadow = true;		match = true; } 
	if (value == "false")	{ this->_vertexBufferUseShadow = false;	match = true; }

	if (!match) this->_vertexBufferUseShadow = false;
}
void dotSceneObjects::dotSceneEntity::set_indexBufferUsage(std::string value)
{
	bool match = false; 
	
	if (value == "discardable")					{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_discardable;					match = true; } 
	if (value == "dynamic")						{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamic;						match = true; }
	if (value == "dynamicWriteOnly")			{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamicWriteOnly;				match = true; }
	if (value == "dynamicWriteOnlyDiscardable") { this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_dynamicWriteOnlyDiscardable;	match = true; }
	if (value == "static")						{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_static;						match = true; }
	if (value == "staticWriteOnly")				{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_staticWriteOnly;				match = true; }
	if (value == "writeOnly")					{ this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_writeOnly;						match = true; }

	if (!match) this->_indexBufferUsage = dotSceneEnums::dotSceneEntityEnums::BufferUsage_INVALID;
}
void dotSceneObjects::dotSceneEntity::set_indexBufferUseShadow(std::string value){
	bool match = false; 
	
	if (value == "true")	{ this->_indexBufferUseShadow = true;		match = true; } 
	if (value == "false")	{ this->_indexBufferUseShadow = false;	match = true; }

	if (!match) this->_indexBufferUseShadow = false;
}

bool dotSceneObjects::dotSceneEntity::IsValid() const
{
	if (this->_name == "INVALID") return false;
	if (this->_meshFile == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneEntity::dotSceneEntity() : dotSceneObject(dotSceneEnums::entity)
{
	this->set_meshFile("INVALID");
	this->set_name("INITIAL_NOT_SET");
	
	this->set_ID("INITIAL_NOT_SET");
	this->set_materialName("INITIAL_NOT_SET");
	this->set_displaySkeleton(false);
	this->set_polygonModeOverrideable(false);
	this->set_softwareAnimationRequests("INITIAL_NOT_SET");
	this->set_softwareAnimationRequestsNormalsAlso("INITIAL_NOT_SET");

	this->set_vertexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage_INVALID);
	this->set_vertexBufferUseShadow(false);
	this->set_indexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage_INVALID);
	this->set_indexBufferUseShadow(false);

	this->set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams());
	this->set_MeshLODBias(dotSceneMeshLODBias());
	this->set_MaterialLODBias(dotSceneMaterialLODBias());
	this->set_UserDataReference(dotSceneUserDataReference());

	// Older implementation:
	//this->set_static(false);
	//this->set_visible(false);
	//this->set_castShadows(false);
	//this->set_renderingDistance(0);
}

dotSceneObjects::dotSceneEntity::dotSceneEntity(
	std::string str_meshFile,
	std::string str_name,
	std::string str_ID,
	std::string str_materialName,
	std::string str_displaySkeleton,
	std::string str_polygonModeOverrideable,
	std::string str_softwareAnimationRequests,
	std::string str_softwareAnimationRequestsNormalsAlso,
	std::string str_vertexBufferUsage,
	std::string str_vertexBufferUseShadow,
	std::string str_indexBufferUsage,
	std::string str_indexBufferUseShadow,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotSceneMeshLODBias obj_MeshLODBias,
	dotSceneMaterialLODBias obj_MaterialLODBias,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::entity)
{
	this->set_meshFile(str_meshFile);
    this->set_name(str_name);

	this->set_ID(str_ID);
	this->set_materialName(str_materialName);
	this->set_displaySkeleton(str_displaySkeleton);
	this->set_polygonModeOverrideable(str_polygonModeOverrideable);
	this->set_softwareAnimationRequests(str_softwareAnimationRequests);
	this->set_softwareAnimationRequestsNormalsAlso(str_softwareAnimationRequestsNormalsAlso);

	this->set_vertexBufferUsage(str_vertexBufferUsage);
	this->set_vertexBufferUseShadow(str_vertexBufferUseShadow);
	this->set_indexBufferUsage(str_indexBufferUsage);
	this->set_indexBufferUseShadow(str_indexBufferUseShadow);
    
	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_MeshLODBias(obj_MeshLODBias);
	this->set_MaterialLODBias(obj_MaterialLODBias);
	this->set_UserDataReference(obj_UserDataReference);

	//this->set_static(str_static);
	//this->set_visible(str_visible);
	//this->set_castShadows(str_castShadows);
	//this->set_renderingDistance(str_renderingDistance);
}

dotSceneObjects::dotSceneEntity::dotSceneEntity(
	std::string str_meshFile,
	std::string str_name,
	std::string str_ID,
	std::string str_materialName,
	bool bool_displaySkeleton,
	bool bool_polygonModeOverrideable,
	std::string str_softwareAnimationRequests,
	std::string str_softwareAnimationRequestsNormalsAlso,
	dotSceneEnums::dotSceneEntityEnums::BufferUsage enum_vertexBufferUsage,
	bool bool_vertexBufferUseShadow,
	dotSceneEnums::dotSceneEntityEnums::BufferUsage enum_indexBufferUsage,
	bool bool_indexBufferUseShadow,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotSceneMeshLODBias obj_MeshLODBias,
	dotSceneMaterialLODBias obj_MaterialLODBias,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::entity)
{
	this->set_meshFile(str_meshFile);
    this->set_name(str_name);

	this->set_ID(str_ID);
	this->set_materialName(str_materialName);
	this->set_displaySkeleton(bool_displaySkeleton);
	this->set_polygonModeOverrideable(bool_polygonModeOverrideable);
	this->set_softwareAnimationRequests(str_softwareAnimationRequests);
	this->set_softwareAnimationRequestsNormalsAlso(str_softwareAnimationRequestsNormalsAlso);

	this->set_vertexBufferUsage(enum_vertexBufferUsage);
	this->set_vertexBufferUseShadow(bool_vertexBufferUseShadow);
	this->set_indexBufferUsage(enum_indexBufferUsage);
	this->set_indexBufferUseShadow(bool_indexBufferUseShadow);
    
	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_MeshLODBias(obj_MeshLODBias);
	this->set_MaterialLODBias(obj_MaterialLODBias);
	this->set_UserDataReference(obj_UserDataReference);

    //this->set_static(bool_static);
    //this->set_visible(bool_visible);
    //this->set_castShadows(bool_castShadows);
    //this->set_renderingDistance(double_renderingDistance);
}

dotSceneObjects::dotSceneEntity::dotSceneEntity(const dotSceneEntity& CopyObject) : dotSceneObject(dotSceneEnums::entity)
{
	this->set_meshFile(CopyObject.get_meshFile());
	this->set_name(CopyObject.get_name());

	this->set_ID(CopyObject.get_ID());
	this->set_materialName(CopyObject.get_materialName());
	this->set_displaySkeleton(CopyObject.get_displaySkeleton());
	this->set_polygonModeOverrideable(CopyObject.get_polygonModeOverrideable());
	this->set_softwareAnimationRequests(CopyObject.get_softwareAnimationRequests());
	this->set_softwareAnimationRequestsNormalsAlso(CopyObject.get_softwareAnimationRequestsNormalsAlso());

	this->set_vertexBufferUsage(CopyObject.get_vertexBufferUsage());
	this->set_vertexBufferUseShadow(CopyObject.get_vertexBufferUseShadow());
	this->set_indexBufferUsage(CopyObject.get_indexBufferUsage());
	this->set_indexBufferUseShadow(CopyObject.get_indexBufferUseShadow());
    
	this->set_CommonMovableObjectParams(CopyObject.get_CommonMovableObjectParams());
	this->set_MeshLODBias(CopyObject.get_MeshLODBias());
	this->set_MaterialLODBias(CopyObject.get_MaterialLODBias());
	this->set_UserDataReference(CopyObject.get_UserDataReference());
}


// OLD methods and attributes of older format versions than 1.0.0
/*
bool dotSceneObjects::dotSceneEntity::get_static() const { return this->_static; }
bool dotSceneObjects::dotSceneEntity::get_visible() const { return this->_visible; }
bool dotSceneObjects::dotSceneEntity::get_castShadows() const { return this->_castShadows; }
double dotSceneObjects::dotSceneEntity::get_renderingDistance() const { return this->_renderingDistance; }

void dotSceneObjects::dotSceneEntity::set_static(bool value) { this->_static = value; }
void dotSceneObjects::dotSceneEntity::set_visible(bool value) { this->_visible = value; }
void dotSceneObjects::dotSceneEntity::set_castShadows(bool value) { this->_castShadows = value; }
void dotSceneObjects::dotSceneEntity::set_renderingDistance(double value) { this->_renderingDistance = value; }

void dotSceneObjects::dotSceneEntity::set_static(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	if ((tmp == 0) || (tmp == 1)) this->_static = (bool) tmp;
	else this->_static = false;
}

void dotSceneObjects::dotSceneEntity::set_visible(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	if ((tmp == 0) || (tmp == 1)) this->_visible = (bool) tmp;
	else this->_visible = false;
}

void dotSceneObjects::dotSceneEntity::set_castShadows(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	if ((tmp == 0) || (tmp == 1)) this->_castShadows = (bool) tmp;
	else this->_castShadows = false;
}

void dotSceneObjects::dotSceneEntity::set_renderingDistance(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_renderingDistance = tmp;
}
*/
