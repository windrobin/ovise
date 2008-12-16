#ifndef dotSceneBillboard_h_
#define dotSceneBillboard_h_
#include "dotSceneBillboard.h"
#endif

// GET-methods
std::string dotSceneObjects::dotSceneBillboard::get_ID() const { return this->_ID; }
double dotSceneObjects::dotSceneBillboard::get_Rotation() const { return this->_Rotation; }
double dotSceneObjects::dotSceneBillboard::get_Width() const { return this->_Width; }
double dotSceneObjects::dotSceneBillboard::get_Height() const { return this->_Height; }
int	dotSceneObjects::dotSceneBillboard::get_TexCoordIndex() const { return this->_TexCoordIndex; }

dotSceneObjects::dotScenePosition dotSceneObjects::dotSceneBillboard::get_Position() const { return this->_Position; }
dotSceneObjects::dotSceneColourDiffuse dotSceneObjects::dotSceneBillboard::get_ColourDiffuse() const { return this->_ColourDiffuse; }
dotSceneObjects::dotSceneTextureCoords dotSceneObjects::dotSceneBillboard::get_TextureCoords() const { return this->_TextureCoords; }

// Set-methods
void dotSceneObjects::dotSceneBillboard::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotSceneBillboard::set_Rotation(double value) { this->_Rotation = value; }
void dotSceneObjects::dotSceneBillboard::set_Width(double value) { this->_Width = value; }
void dotSceneObjects::dotSceneBillboard::set_Height(double value) { this->_Height = value; }
void dotSceneObjects::dotSceneBillboard::set_TexCoordIndex(int value) { this->_TexCoordIndex = value; }

void dotSceneObjects::dotSceneBillboard::set_Position(dotScenePosition value) { this->_Position = value; }
void dotSceneObjects::dotSceneBillboard::set_ColourDiffuse(dotSceneColourDiffuse value) { this->_ColourDiffuse = value; }
void dotSceneObjects::dotSceneBillboard::set_TextureCoords(dotSceneTextureCoords value) { this->_TextureCoords = value; }

void dotSceneObjects::dotSceneBillboard::set_Rotation(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Rotation = tmp;
}

void dotSceneObjects::dotSceneBillboard::set_Width(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Width = tmp;
}

void dotSceneObjects::dotSceneBillboard::set_Height(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Height = tmp;
}

void dotSceneObjects::dotSceneBillboard::set_TexCoordIndex(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_TexCoordIndex = tmp;
}

bool dotSceneObjects::dotSceneBillboard::IsValid() const
{
	// objects all #IMPLIED. Not #REQUIRED. So there is no validation needed.
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneBillboard::dotSceneBillboard() : dotSceneObject(dotSceneEnums::billboard)
{
	this->set_ID("INITIAL_NOT_SET");//#IMPLIED
	this->set_Rotation(0.0);
	this->set_Width(0.0);
	this->set_Height(0.0);
	this->set_TexCoordIndex(0);
	
	this->set_Position(dotScenePosition());
	this->set_ColourDiffuse(dotSceneColourDiffuse());
	this->set_TextureCoords(dotSceneTextureCoords());
}

dotSceneObjects::dotSceneBillboard::dotSceneBillboard(
	std::string str_ID,
	std::string str_Rotation,
	std::string str_Width,
	std::string str_Height,
	std::string str_TexCoordIndex,
	dotScenePosition obj_Position,
	dotSceneColourDiffuse obj_ColourDiffuse,
	dotSceneTextureCoords obj_TextureCoords) : dotSceneObject(dotSceneEnums::billboard)
{
	this->set_ID(str_ID);
	this->set_Rotation(str_Rotation);
	this->set_Width(str_Width);
	this->set_Height(str_Height);
	this->set_TexCoordIndex(str_TexCoordIndex);
	
	this->set_Position(obj_Position);
	this->set_ColourDiffuse(obj_ColourDiffuse);
	this->set_TextureCoords(obj_TextureCoords);
}

dotSceneObjects::dotSceneBillboard::dotSceneBillboard(
	std::string str_ID,
	double double_Rotation,
	double double_Width,
	double double_Height,
	int int_TexCoordIndex,
	dotScenePosition obj_Position,
	dotSceneColourDiffuse obj_ColourDiffuse,
	dotSceneTextureCoords obj_TextureCoords) : dotSceneObject(dotSceneEnums::billboard)
{
	this->set_ID(str_ID);
	this->set_Rotation(double_Rotation);
	this->set_Width(double_Width);
	this->set_Height(double_Height);
	this->set_TexCoordIndex(int_TexCoordIndex);
	
	this->set_Position(obj_Position);
	this->set_ColourDiffuse(obj_ColourDiffuse);
	this->set_TextureCoords(obj_TextureCoords);
}
