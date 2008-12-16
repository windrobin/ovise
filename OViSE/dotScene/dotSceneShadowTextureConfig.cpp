#ifndef dotSceneShadowTextureConfig_h_
#define dotSceneShadowTextureConfig_h_
#include "dotSceneShadowTextureConfig.h"
#endif

using namespace dotSceneObjects;
using namespace dotSceneEnums::dotSceneShadowConfigEnums;

int			dotSceneObjects::dotSceneShadowTextureConfig::get_ShadowIndex() const { return this->_ShadowIndex; }
double		dotSceneObjects::dotSceneShadowTextureConfig::get_Width() const { return this->_Width; }
double		dotSceneObjects::dotSceneShadowTextureConfig::get_Height() const { return this->_Height; }
PixelFormat dotSceneObjects::dotSceneShadowTextureConfig::get_PixelFormat() const { return this->_PixelFormat; }

void dotSceneObjects::dotSceneShadowTextureConfig::set_ShadowIndex(int value) { this->_ShadowIndex = value; }
void dotSceneObjects::dotSceneShadowTextureConfig::set_Width(double value) { this->_Width = value; }
void dotSceneObjects::dotSceneShadowTextureConfig::set_Height(double value) { this->_Height = value; }
void dotSceneObjects::dotSceneShadowTextureConfig::set_PixelFormat(PixelFormat value) { this->_PixelFormat = value; }

void dotSceneObjects::dotSceneShadowTextureConfig::set_ShadowIndex(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_ShadowIndex = tmp;
}

void dotSceneObjects::dotSceneShadowTextureConfig::set_Width(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Width = tmp;
}

void dotSceneObjects::dotSceneShadowTextureConfig::set_Height(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_Height = tmp;
}

void dotSceneObjects::dotSceneShadowTextureConfig::set_PixelFormat(std::string value)
{
	bool match = false; 
	
	if (value == "PF_UNKNOWN")		{ this->_PixelFormat = PixelFormat::PF_UNKNOWN;		match = true; }
    if (value == "PF_L8")			{ this->_PixelFormat = PixelFormat::PF_L8;			match = true; }
    if (value == "PF_BYTE_L")		{ this->_PixelFormat = PixelFormat::PF_BYTE_L;		match = true; }
    if (value == "PF_L16")			{ this->_PixelFormat = PixelFormat::PF_L16;			match = true; }
    if (value == "PF_SHORT_L")		{ this->_PixelFormat = PixelFormat::PF_SHORT_L;		match = true; }
    if (value == "PF_A8")			{ this->_PixelFormat = PixelFormat::PF_A8;			match = true; }
    if (value == "PF_BYTE_A")		{ this->_PixelFormat = PixelFormat::PF_BYTE_A;		match = true; }
    if (value == "PF_A4L4")			{ this->_PixelFormat = PixelFormat::PF_A4L4;		match = true; }
    if (value == "PF_BYTE_LA")		{ this->_PixelFormat = PixelFormat::PF_BYTE_LA;		match = true; }
    if (value == "PF_R5G6B5")		{ this->_PixelFormat = PixelFormat::PF_R5G6B5;		match = true; }
    if (value == "PF_B5G6R5")		{ this->_PixelFormat = PixelFormat::PF_B5G6R5;		match = true; }
    if (value == "PF_R3G3B2")		{ this->_PixelFormat = PixelFormat::PF_R3G3B2;		match = true; }
    if (value == "PF_A4R4G4B4")		{ this->_PixelFormat = PixelFormat::PF_A4R4G4B4;	match = true; }
    if (value == "PF_A1R5G5B5")		{ this->_PixelFormat = PixelFormat::PF_A1R5G5B5;	match = true; }
    if (value == "PF_R8G8B8")		{ this->_PixelFormat = PixelFormat::PF_R8G8B8;		match = true; }
    if (value == "PF_B8G8R8")		{ this->_PixelFormat = PixelFormat::PF_B8G8R8;		match = true; }
    if (value == "PF_A8R8G8B8")		{ this->_PixelFormat = PixelFormat::PF_A8R8G8B8;	match = true; }
    if (value == "PF_A8B8G8R8")		{ this->_PixelFormat = PixelFormat::PF_A8B8G8R8;	match = true; }
    if (value == "PF_B8G8R8A8")		{ this->_PixelFormat = PixelFormat::PF_B8G8R8A8;	match = true; }
    if (value == "PF_R8G8B8A8")		{ this->_PixelFormat = PixelFormat::PF_R8G8B8A8;	match = true; }
    if (value == "PF_X8R8G8B8")		{ this->_PixelFormat = PixelFormat::PF_X8R8G8B8;	match = true; }
    if (value == "PF_X8B8G8R8")		{ this->_PixelFormat = PixelFormat::PF_X8B8G8R8;	match = true; }
    if (value == "PF_BYTE_RGB")		{ this->_PixelFormat = PixelFormat::PF_BYTE_RGB;	match = true; }
    if (value == "PF_BYTE_BGR")		{ this->_PixelFormat = PixelFormat::PF_BYTE_BGR;	match = true; }
    if (value == "PF_BYTE_BGRA")	{ this->_PixelFormat = PixelFormat::PF_BYTE_BGRA;	match = true; }
    if (value == "PF_BYTE_RGBA")	{ this->_PixelFormat = PixelFormat::PF_BYTE_RGBA;	match = true; }
    if (value == "PF_A2R10G10B10")	{ this->_PixelFormat = PixelFormat::PF_A2R10G10B10;	match = true; }
    if (value == "PF_A2B10G10R10")	{ this->_PixelFormat = PixelFormat::PF_A2B10G10R10;	match = true; }
    if (value == "PF_DXT1")			{ this->_PixelFormat = PixelFormat::PF_DXT1;		match = true; }
    if (value == "PF_DXT2")			{ this->_PixelFormat = PixelFormat::PF_DXT2;		match = true; }
    if (value == "PF_DXT3")			{ this->_PixelFormat = PixelFormat::PF_DXT3;		match = true; }
    if (value == "PF_DXT4")			{ this->_PixelFormat = PixelFormat::PF_DXT4;		match = true; }
    if (value == "PF_DXT5")			{ this->_PixelFormat = PixelFormat::PF_DXT5;		match = true; }
    if (value == "PF_FLOAT16_R")	{ this->_PixelFormat = PixelFormat::PF_FLOAT16_R;	match = true; }
    if (value == "PF_FLOAT16_RGB")	{ this->_PixelFormat = PixelFormat::PF_FLOAT16_RGB;	match = true; }
    if (value == "PF_FLOAT16_RGBA")	{ this->_PixelFormat = PixelFormat::PF_FLOAT16_RGBA;match = true; }
    if (value == "PF_FLOAT32_R")	{ this->_PixelFormat = PixelFormat::PF_FLOAT32_R;	match = true; }
    if (value == "PF_FLOAT32_RGB")	{ this->_PixelFormat = PixelFormat::PF_FLOAT32_RGB;	match = true; }
    if (value == "PF_FLOAT32_RGBA")	{ this->_PixelFormat = PixelFormat::PF_FLOAT32_RGBA;match = true; }
    if (value == "PF_FLOAT16_GR")	{ this->_PixelFormat = PixelFormat::PF_FLOAT16_GR;	match = true; }
    if (value == "PF_FLOAT32_GR")	{ this->_PixelFormat = PixelFormat::PF_FLOAT32_GR;	match = true; }
    if (value == "PF_DEPTH")		{ this->_PixelFormat = PixelFormat::PF_DEPTH;		match = true; }
    if (value == "PF_SHORT_RGBA")	{ this->_PixelFormat = PixelFormat::PF_SHORT_RGBA;	match = true; }
    if (value == "PF_SHORT_GR")		{ this->_PixelFormat = PixelFormat::PF_SHORT_GR;	match = true; }
    if (value == "PF_SHORT_RGB")	{ this->_PixelFormat = PixelFormat::PF_SHORT_RGB;	match = true; }
    if (value == "PF_COUNT")		{ this->_PixelFormat = PixelFormat::PF_COUNT;		match = true; }

	if (!match) this->_PixelFormat = PixelFormat::PF_UNKNOWN;
}

bool dotSceneObjects::dotSceneShadowTextureConfig::IsValid() const
{
	// all #REQUIRED values can't be checked.
	// basics valid?
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneShadowTextureConfig::dotSceneShadowTextureConfig() : dotSceneObject(dotSceneEnums::shadowTextureConfig)
{
	this->set_ShadowIndex(0);
	this->set_Width(0.0);
	this->set_Height(0.0);
	this->set_ShadowIndex(PixelFormat::PF_UNKNOWN);
}

dotSceneObjects::dotSceneShadowTextureConfig::dotSceneShadowTextureConfig(
	std::string str_ShadowIndex,
	std::string str_Width,
	std::string str_Height,
	std::string str_PixelFormat) : dotSceneObject(dotSceneEnums::shadowTextureConfig)
{
	this->set_ShadowIndex(str_ShadowIndex);
	this->set_Width(str_Width);
	this->set_Height(str_Height);
	this->set_ShadowIndex(str_PixelFormat);
}

dotSceneObjects::dotSceneShadowTextureConfig::dotSceneShadowTextureConfig(
	int int_ShadowIndex,
	double double_Width,
	double double_Height,
	PixelFormat enum_PixelFormat) : dotSceneObject(dotSceneEnums::shadowTextureConfig)
{
	this->set_ShadowIndex(int_ShadowIndex);
	this->set_Width(double_Width);
	this->set_Height(double_Height);
	this->set_ShadowIndex(enum_PixelFormat);
}