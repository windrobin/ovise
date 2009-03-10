#ifndef dotSceneBillboardSet_h_
#define dotSceneBillboardSet_h_
#include "dotSceneBillboardSet.h"
#endif

using namespace dotSceneObjects;
using namespace dotSceneEnums::dotSceneBillboradSetEnums;

std::string dotSceneObjects::dotSceneBillboardSet::get_name() const { return this->_name; }
std::string dotSceneObjects::dotSceneBillboardSet::get_ID() const { return this->_ID; }
int			dotSceneObjects::dotSceneBillboardSet::get_PoolSize() const { return this->_PoolSize; }
bool		dotSceneObjects::dotSceneBillboardSet::get_Autoextend() const { return this->_Autoextend; }
std::string dotSceneObjects::dotSceneBillboardSet::get_MaterialName() const { return this->_MaterialName; }
double		dotSceneObjects::dotSceneBillboardSet::get_DefaultWidth() const { return this->_DefaultWidth; }
double		dotSceneObjects::dotSceneBillboardSet::get_DefaultHeight() const { return this->_DefaultHeight; }
BillboardType			dotSceneObjects::dotSceneBillboardSet::get_BillboardType() const { return this->_BillboardType; }
BillboardOrigin			dotSceneObjects::dotSceneBillboardSet::get_BillboardOrigin() const { return this->_BillboardOrigin; }
BillboardRotationType	dotSceneObjects::dotSceneBillboardSet::get_BillboardRotationType() const { return this->_BillboardRotationType; }
bool		dotSceneObjects::dotSceneBillboardSet::get_SortingEnabled() const { return this->_SortingEnabled; }
bool		dotSceneObjects::dotSceneBillboardSet::get_CullIndividually() const { return this->_CullIndividually; }
bool		dotSceneObjects::dotSceneBillboardSet::get_AccurateFacing() const { return this->_AccurateFacing; }
bool		dotSceneObjects::dotSceneBillboardSet::get_BillboardsInWorldSpace() const { return this->_BillboardsInWorldSpace; }
bool		dotSceneObjects::dotSceneBillboardSet::get_PointRenderingEnabled() const { return this->_PointRenderingEnabled; }

dotSceneCommonMovableObjectParams	dotSceneObjects::dotSceneBillboardSet::get_CommonMovableObjectParams() const { return this->_CommonMovableObjectParams; }
dotSceneCommonDirection				dotSceneObjects::dotSceneBillboardSet::get_CommonDirection() const { return this->_CommonDirection; }
dotSceneCommonUpVector				dotSceneObjects::dotSceneBillboardSet::get_CommonUpVector() const { return this->_CommonUpVector; }
dotSceneTextureCoords				dotSceneObjects::dotSceneBillboardSet::get_TextureCoords() const { return this->_TextureCoords; }
dotSceneTextureStacksAndSlices		dotSceneObjects::dotSceneBillboardSet::get_TextureStacksAndSlices() const { return this->_TextureStacksAndSlices; }

void dotSceneObjects::dotSceneBillboardSet::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotSceneBillboardSet::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotSceneBillboardSet::set_PoolSize(int value) { this->_PoolSize = value; }
void dotSceneObjects::dotSceneBillboardSet::set_Autoextend(bool value) { this->_Autoextend = value; }
void dotSceneObjects::dotSceneBillboardSet::set_MaterialName(std::string value) { this->_MaterialName = value; }
void dotSceneObjects::dotSceneBillboardSet::set_DefaultWidth(double value) { this->_DefaultWidth = value; }
void dotSceneObjects::dotSceneBillboardSet::set_DefaultHeight(double value) { this->_DefaultHeight = value; }
void dotSceneObjects::dotSceneBillboardSet::set_BillboardType(BillboardType value) { this->_BillboardType = value; }
void dotSceneObjects::dotSceneBillboardSet::set_BillboardOrigin(BillboardOrigin value) { this->_BillboardOrigin = value; }
void dotSceneObjects::dotSceneBillboardSet::set_BillboardRotationType(BillboardRotationType value) { this->_BillboardRotationType = value; }
void dotSceneObjects::dotSceneBillboardSet::set_SortingEnabled(bool value) { this->_SortingEnabled = value; }
void dotSceneObjects::dotSceneBillboardSet::set_CullIndividually(bool value) { this->_CullIndividually = value; }
void dotSceneObjects::dotSceneBillboardSet::set_AccurateFacing(bool value) { this->_AccurateFacing = value; }
void dotSceneObjects::dotSceneBillboardSet::set_BillboardsInWorldSpace(bool value) { this->_BillboardsInWorldSpace = value; }
void dotSceneObjects::dotSceneBillboardSet::set_PointRenderingEnabled(bool value) { this->_PointRenderingEnabled = value; }

void dotSceneObjects::dotSceneBillboardSet::set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value) { this->_CommonMovableObjectParams = value; }
void dotSceneObjects::dotSceneBillboardSet::set_CommonDirection(dotSceneCommonDirection value) { this->_CommonDirection = value; }
void dotSceneObjects::dotSceneBillboardSet::set_CommonUpVector(dotSceneCommonUpVector value) { this->_CommonUpVector = value; }
void dotSceneObjects::dotSceneBillboardSet::set_TextureCoords(dotSceneTextureCoords value) { this->_TextureCoords = value; }
void dotSceneObjects::dotSceneBillboardSet::set_TextureStacksAndSlices(dotSceneTextureStacksAndSlices value) { this->_TextureStacksAndSlices = value; }

void dotSceneObjects::dotSceneBillboardSet::set_PoolSize(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_PoolSize = tmp;
}

void dotSceneObjects::dotSceneBillboardSet::set_Autoextend(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Autoextend = true;		match = true; } 
	if (value == "false")	{ this->_Autoextend = false;	match = true; }

	if (!match) this->_Autoextend = false;
}

void dotSceneObjects::dotSceneBillboardSet::set_DefaultWidth(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_DefaultWidth = tmp;
}

void dotSceneObjects::dotSceneBillboardSet::set_DefaultHeight(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_DefaultHeight = tmp;
}

void dotSceneObjects::dotSceneBillboardSet::set_BillboardType(std::string value)
{
	bool match = false;
	if ((!match) && (value == "point"))					{ this->_BillboardType = BillboardType_Point;				match = true; }
	if ((!match) && (value == "orientedCommon"))		{ this->_BillboardType = BillboardType_OrientedCommon;		match = true; }
	if ((!match) && (value == "orientedSelf"))			{ this->_BillboardType = BillboardType_OrientedSelf;			match = true; }
	if ((!match) && (value == "perpendicularCommon"))	{ this->_BillboardType = BillboardType_PerpendicularCommon;	match = true; }
	if ((!match) && (value == "perpendicularSelf"))		{ this->_BillboardType = BillboardType_PerpendicularSelf;	match = true; }
	
	if (!match) { this->_BillboardType = BillboardType_INVALID; }
}

void dotSceneObjects::dotSceneBillboardSet::set_BillboardOrigin(std::string value)
{
	bool match = false;

	if ((!match) && (value == "topLeft"))		{ this->_BillboardOrigin = BillboardOrigin_TopLeft;		match = true; }
	if ((!match) && (value == "topCenter"))		{ this->_BillboardOrigin = BillboardOrigin_TopCenter;		match = true; }
	if ((!match) && (value == "topRight"))		{ this->_BillboardOrigin = BillboardOrigin_TopRight;		match = true; }
	if ((!match) && (value == "centerLeft"))	{ this->_BillboardOrigin = BillboardOrigin_CenterLeft;		match = true; }
	if ((!match) && (value == "center"))		{ this->_BillboardOrigin = BillboardOrigin_Center;			match = true; }
	if ((!match) && (value == "centerRight"))	{ this->_BillboardOrigin = BillboardOrigin_CenterRight;	match = true; }
	if ((!match) && (value == "bottomLeft"))	{ this->_BillboardOrigin = BillboardOrigin_BottomLeft;		match = true; }
	if ((!match) && (value == "bottomCenter"))	{ this->_BillboardOrigin = BillboardOrigin_BottomCenter;	match = true; }
	if ((!match) && (value == "bottomRight"))	{ this->_BillboardOrigin = BillboardOrigin_BottomRight;	match = true; }
	
	if (!match) { this->_BillboardOrigin = BillboardOrigin_INVALID; }
}

void dotSceneObjects::dotSceneBillboardSet::set_BillboardRotationType(std::string value)
{
	bool match = false;

	if ((!match) && (value == "vertex"))	{ this->_BillboardRotationType = BillboardRotationType_Vertex;	match = true; }
	if ((!match) && (value == "texcoord"))	{ this->_BillboardRotationType = BillboardRotationType_Texcoord;	match = true; }
	
	if (!match) { this->_BillboardRotationType = BillboardRotationType_INVALID; }
}

void dotSceneObjects::dotSceneBillboardSet::set_SortingEnabled(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_SortingEnabled = true;		match = true; } 
	if (value == "false")	{ this->_SortingEnabled = false;	match = true; }

	if (!match) this->_SortingEnabled = false;
}

void dotSceneObjects::dotSceneBillboardSet::set_CullIndividually(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_CullIndividually = true;	match = true; } 
	if (value == "false")	{ this->_CullIndividually = false;	match = true; }

	if (!match) this->_CullIndividually = false;
}

void dotSceneObjects::dotSceneBillboardSet::set_AccurateFacing(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_AccurateFacing = true;		match = true; } 
	if (value == "false")	{ this->_AccurateFacing = false;	match = true; }

	if (!match) this->_AccurateFacing = false;
}

void dotSceneObjects::dotSceneBillboardSet::set_BillboardsInWorldSpace(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_BillboardsInWorldSpace = true;		match = true; } 
	if (value == "false")	{ this->_BillboardsInWorldSpace = false;	match = true; }

	if (!match) this->_BillboardsInWorldSpace = false;
}

void dotSceneObjects::dotSceneBillboardSet::set_PointRenderingEnabled(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_PointRenderingEnabled = true;		match = true; } 
	if (value == "false")	{ this->_PointRenderingEnabled = false;	match = true; }

	if (!match) this->_PointRenderingEnabled = false;
}

bool dotSceneObjects::dotSceneBillboardSet::IsValid() const
{
	// basics valid?
	if (this->_MaterialName == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}
bool dotSceneObjects::dotSceneBillboardSet::addBillboard(dotSceneBillboard someBillboard)
{
	try
	{
		this->_BillboardList.push_back(someBillboard);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

/// region constructors & destructors
dotSceneObjects::dotSceneBillboardSet::dotSceneBillboardSet() : dotSceneObject(dotSceneEnums::billboardSet)
{
	this->set_name("INITIAL_NOT_SET");
	this->set_ID("INITIAL_NOT_SET");
	this->set_PoolSize(20);
	this->set_Autoextend(true);
	this->set_MaterialName("INVALID"); // #REQUIRED
	this->set_DefaultWidth(10);
	this->set_DefaultHeight(10);
	this->set_BillboardType(BillboardType_Point);
	this->set_BillboardOrigin(BillboardOrigin_Center);
	this->set_BillboardRotationType(BillboardRotationType_Texcoord);

	this->set_SortingEnabled(false);
	this->set_CullIndividually(false);
	this->set_AccurateFacing(false);
	this->set_BillboardsInWorldSpace(false);
	this->set_PointRenderingEnabled(false);

	this->set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams());
	this->set_CommonDirection(dotSceneCommonDirection());
	this->set_CommonUpVector(dotSceneCommonUpVector());

	this->_BillboardList = std::list<dotSceneObjects::dotSceneBillboard>();
}

dotSceneObjects::dotSceneBillboardSet::dotSceneBillboardSet(
	std::string str_name,
	std::string str_ID,
	std::string str_PoolSize,
	std::string str_Autoextend,
	std::string str_MaterialName,
	std::string str_DefaultWidth,
	std::string str_DefaultHeight,
	std::string str_BillboardType,
	std::string str_BillboardOrigin,
	std::string str_BillboardRotationType,
	std::string str_SortingEnabled,
	std::string str_CullIndividually,
	std::string str_AccurateFacing,
	std::string str_BillboardsInWorldSpace,
	std::string str_PointRenderingEnabled,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotSceneCommonDirection obj_CommonDirection,
	dotSceneCommonUpVector obj_CommonUpVector) : dotSceneObject(dotSceneEnums::billboardSet)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_PoolSize(str_PoolSize);
	this->set_Autoextend(str_Autoextend);
	this->set_MaterialName(str_MaterialName); // #REQUIRED
	this->set_DefaultWidth(str_DefaultWidth);
	this->set_DefaultHeight(str_DefaultHeight);
	this->set_BillboardType(str_BillboardType);
	this->set_BillboardOrigin(str_BillboardOrigin);
	this->set_BillboardRotationType(str_BillboardRotationType);

	this->set_SortingEnabled(str_SortingEnabled);
	this->set_CullIndividually(str_CullIndividually);
	this->set_AccurateFacing(str_AccurateFacing);
	this->set_BillboardsInWorldSpace(str_BillboardsInWorldSpace);
	this->set_PointRenderingEnabled(str_PointRenderingEnabled);

	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_CommonDirection(obj_CommonDirection);
	this->set_CommonUpVector(obj_CommonUpVector);

	this->_BillboardList = std::list<dotSceneObjects::dotSceneBillboard>();
}

dotSceneObjects::dotSceneBillboardSet::dotSceneBillboardSet(
	std::string str_name,
	std::string str_ID,
	int int_PoolSize,
	bool bool_Autoextend,
	std::string str_MaterialName,
	double bool_DefaultWidth,
	double bool_DefaultHeight,
	BillboardType enum_BillboardType,
	BillboardOrigin enum_BillboardOrigin,
	BillboardRotationType enum_BillboardRotationType,
	bool bool_SortingEnabled,
	bool bool_CullIndividually,
	bool bool_AccurateFacing,
	bool bool_BillboardsInWorldSpace,
	bool bool_PointRenderingEnabled,
	dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
	dotSceneCommonDirection obj_CommonDirection,
	dotSceneCommonUpVector obj_CommonUpVector) : dotSceneObject(dotSceneEnums::billboardSet)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_PoolSize(int_PoolSize);
	this->set_Autoextend(bool_Autoextend);
	this->set_MaterialName(str_MaterialName); // #REQUIRED
	this->set_DefaultWidth(bool_DefaultWidth);
	this->set_DefaultHeight(bool_DefaultHeight);
	this->set_BillboardType(enum_BillboardType);
	this->set_BillboardOrigin(enum_BillboardOrigin);
	this->set_BillboardRotationType(enum_BillboardRotationType);

	this->set_SortingEnabled(bool_SortingEnabled);
	this->set_CullIndividually(bool_CullIndividually);
	this->set_AccurateFacing(bool_AccurateFacing);
	this->set_BillboardsInWorldSpace(bool_BillboardsInWorldSpace);
	this->set_PointRenderingEnabled(bool_PointRenderingEnabled);

	this->set_CommonMovableObjectParams(obj_CommonMovableObjectParams);
	this->set_CommonDirection(obj_CommonDirection);
	this->set_CommonUpVector(obj_CommonUpVector);

	this->_BillboardList = std::list<dotSceneObjects::dotSceneBillboard>();
}
dotSceneObjects::dotSceneBillboardSet::dotSceneBillboardSet(const dotSceneBillboardSet& CopyObject) : dotSceneObject(dotSceneEnums::billboardSet)
{
	this->set_name(CopyObject.get_name());
	this->set_ID(CopyObject.get_ID());
	this->set_PoolSize(CopyObject.get_PoolSize());
	this->set_Autoextend(CopyObject.get_Autoextend());
	this->set_MaterialName(CopyObject.get_MaterialName()); // #REQUIRED
	this->set_DefaultWidth(CopyObject.get_DefaultWidth());
	this->set_DefaultHeight(CopyObject.get_DefaultHeight());
	this->set_BillboardType(CopyObject.get_BillboardType());
	this->set_BillboardOrigin(CopyObject.get_BillboardOrigin());
	this->set_BillboardRotationType(CopyObject.get_BillboardRotationType());

	this->set_SortingEnabled(CopyObject.get_SortingEnabled());
	this->set_CullIndividually(CopyObject.get_CullIndividually());
	this->set_AccurateFacing(CopyObject.get_AccurateFacing());
	this->set_BillboardsInWorldSpace(CopyObject.get_BillboardsInWorldSpace());
	this->set_PointRenderingEnabled(CopyObject.get_PointRenderingEnabled());

	this->set_CommonMovableObjectParams(CopyObject.get_CommonMovableObjectParams());
	this->set_CommonDirection(CopyObject.get_CommonDirection());
	this->set_CommonUpVector(CopyObject.get_CommonUpVector());

	this->_BillboardList = CopyObject._BillboardList;
}