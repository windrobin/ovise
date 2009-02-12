#ifndef dotScenePlane_h_
#define dotScenePlane_h_
#include "dotScenePlane.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotScenePlane::get_name() const { return this->_name; }
std::string dotSceneObjects::dotScenePlane::get_ID() const { return this->_ID; }
double		dotSceneObjects::dotScenePlane::get_NormalX() const { return this->_NormalX; }
double		dotSceneObjects::dotScenePlane::get_NormalY() const { return this->_NormalY; }
double		dotSceneObjects::dotScenePlane::get_NormalZ() const { return this->_NormalZ; }
double		dotSceneObjects::dotScenePlane::get_Distance() const { return this->_Distance; }
double		dotSceneObjects::dotScenePlane::get_Height() const { return this->_Height; }
double		dotSceneObjects::dotScenePlane::get_Width() const { return this->_Width; }
int			dotSceneObjects::dotScenePlane::get_xSegments() const { return this->_xSegments; }
int			dotSceneObjects::dotScenePlane::get_ySegments() const { return this->_ySegments; }
bool		dotSceneObjects::dotScenePlane::get_Normals() const { return this->_Normals; }
int			dotSceneObjects::dotScenePlane::get_NumTexCoordSets() const { return this->_NumTexCoordSets; }
int			dotSceneObjects::dotScenePlane::get_UTile() const { return this->_UTile; }
int			dotSceneObjects::dotScenePlane::get_VTile() const { return this->_VTile; }

dotSceneUpVector dotSceneObjects::dotScenePlane::get_UpVector() const { return this->_UpVector; }

void dotSceneObjects::dotScenePlane::set_name(std::string value) { this->_name = value; }
void dotSceneObjects::dotScenePlane::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotScenePlane::set_NormalX(double value) { this->_NormalX = value; }
void dotSceneObjects::dotScenePlane::set_NormalY(double value) { this->_NormalY = value; }
void dotSceneObjects::dotScenePlane::set_NormalZ(double value) { this->_NormalZ = value; }
void dotSceneObjects::dotScenePlane::set_Distance(double value) { this->_Distance = value; }
void dotSceneObjects::dotScenePlane::set_Height(double value) { this->_Height = value; }
void dotSceneObjects::dotScenePlane::set_Width(double value) { this->_Width = value; }
void dotSceneObjects::dotScenePlane::set_xSegments(int value) { this->_xSegments = value; }
void dotSceneObjects::dotScenePlane::set_ySegments(int value) { this->_ySegments = value; }
void dotSceneObjects::dotScenePlane::set_Normals(bool value) { this->_Normals = value; }
void dotSceneObjects::dotScenePlane::set_NumTexCoordSets(int value) { this->_NumTexCoordSets = value; }
void dotSceneObjects::dotScenePlane::set_UTile(int value) { this->_UTile = value; }
void dotSceneObjects::dotScenePlane::set_VTile(int value) { this->_VTile = value; }

void dotSceneObjects::dotScenePlane::set_UpVector(dotSceneUpVector value){ this->_UpVector = value; }

void dotSceneObjects::dotScenePlane::set_NormalX(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_NormalX = tmp;
}

void dotSceneObjects::dotScenePlane::set_NormalY(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_NormalY = tmp;
}

void dotSceneObjects::dotScenePlane::set_NormalZ(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_NormalZ = tmp;
}

void dotSceneObjects::dotScenePlane::set_Distance(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Distance = tmp;
}

void dotSceneObjects::dotScenePlane::set_Height(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Height = tmp;
}

void dotSceneObjects::dotScenePlane::set_Width(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Width = tmp;
}

void dotSceneObjects::dotScenePlane::set_xSegments(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_xSegments = tmp;
}

void dotSceneObjects::dotScenePlane::set_ySegments(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_ySegments = tmp;
}

void dotSceneObjects::dotScenePlane::set_Normals(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_Normals = true;	match = true; } 
	if (value == "false")	{ this->_Normals = false;	match = true; }

	if (!match) this->_Normals = false;
}
void dotSceneObjects::dotScenePlane::set_NumTexCoordSets(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_NumTexCoordSets = tmp;
}

void dotSceneObjects::dotScenePlane::set_UTile(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_UTile = tmp;
}

void dotSceneObjects::dotScenePlane::set_VTile(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_VTile = tmp;
}

bool dotSceneObjects::dotScenePlane::IsValid() const
{
	// basics valid?
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	if (this->_name == "INVALID") return false;

	if (!this->_UpVector.IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotScenePlane::dotScenePlane() : dotSceneObject(dotSceneEnums::plane)
{
	this->set_name("INVALID");	// #REQUIRED
	this->set_ID("INITIAL_NOT_SET");
	this->set_NormalX(0.0);		// #REQUIRED
	this->set_NormalY(0.0);		// #REQUIRED
	this->set_NormalZ(0.0);		// #REQUIRED
	this->set_Distance(0.0);	// #REQUIRED
	this->set_Height(0.0);		// #REQUIRED
	this->set_Width(0.0);		// #REQUIRED
	this->set_xSegments(1);
	this->set_ySegments(1);
	this->set_Normals(true);
	this->set_NumTexCoordSets(1);
	this->set_UTile(1);
	this->set_VTile(1);

	this->set_UpVector(dotSceneUpVector());
}

dotSceneObjects::dotScenePlane::dotScenePlane(
	std::string str_name,
	std::string str_ID,
	std::string str_NormalX,
	std::string str_NormalY,
	std::string str_NormalZ,
	std::string str_Distance,
	std::string str_Height,
	std::string str_Width,
	std::string str_xSegments,
	std::string str_ySegments,
	std::string str_Normals,
	std::string str_NumTexCoordSets,
	std::string str_UTile,
	std::string str_VTile,
	dotSceneUpVector obj_UpVector) : dotSceneObject(dotSceneEnums::plane)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_NormalX(str_NormalX);
	this->set_NormalY(str_NormalY);
	this->set_NormalZ(str_NormalZ);
	this->set_Distance(str_Distance);
	this->set_Height(str_Height);
	this->set_Width(str_Width);
	this->set_xSegments(str_xSegments);
	this->set_ySegments(str_ySegments);
	this->set_Normals(str_Normals);
	this->set_NumTexCoordSets(str_NumTexCoordSets);
	this->set_UTile(str_UTile);
	this->set_VTile(str_VTile);

	this->set_UpVector(obj_UpVector);
}

dotSceneObjects::dotScenePlane::dotScenePlane(
	std::string str_name,
	std::string str_ID,
	double double_NormalX,
	double double_NormalY,
	double double_NormalZ,
	double double_Distance,
	double double_Height,
	double double_Width,
	int int_xSegments,
	int int_ySegments,
	bool bool_Normals,
	int int_NumTexCoordSets,
	int int_UTile,
	int int_VTile,
	dotSceneUpVector obj_UpVector) : dotSceneObject(dotSceneEnums::plane)
{
	this->set_name(str_name);
	this->set_ID(str_ID);
	this->set_NormalX(double_NormalX);
	this->set_NormalY(double_NormalY);
	this->set_NormalZ(double_NormalZ);
	this->set_Distance(double_Distance);
	this->set_Height(double_Height);
	this->set_Width(double_Width);
	this->set_xSegments(int_xSegments);
	this->set_ySegments(int_ySegments);
	this->set_Normals(bool_Normals);
	this->set_NumTexCoordSets(int_NumTexCoordSets);
	this->set_UTile(int_UTile);
	this->set_VTile(int_VTile);

	this->set_UpVector(obj_UpVector);
}
dotSceneObjects::dotScenePlane::dotScenePlane(const dotScenePlane& CopyObject) : dotSceneObject(dotSceneEnums::plane)
{
	this->set_name(CopyObject.get_name());
	this->set_ID(CopyObject.get_ID());
	this->set_NormalX(CopyObject.get_NormalX());
	this->set_NormalY(CopyObject.get_NormalY());
	this->set_NormalZ(CopyObject.get_NormalZ());
	this->set_Distance(CopyObject.get_Distance());
	this->set_Height(CopyObject.get_Height());
	this->set_Width(CopyObject.get_Width());
	this->set_xSegments(CopyObject.get_xSegments());
	this->set_ySegments(CopyObject.get_ySegments());
	this->set_Normals(CopyObject.get_Normals());
	this->set_NumTexCoordSets(CopyObject.get_NumTexCoordSets());
	this->set_UTile(CopyObject.get_UTile());
	this->set_VTile(CopyObject.get_VTile());

	this->set_UpVector(CopyObject.get_UpVector());
}