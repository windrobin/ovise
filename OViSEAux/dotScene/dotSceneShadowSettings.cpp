#ifndef dotSceneShadowSettings_h_
#define dotSceneShadowSettings_h_
#include "dotSceneShadowSettings.h"
#endif

using namespace dotSceneObjects;
using namespace dotSceneEnums::dotSceneShadowConfigEnums;

ShadowTechnique dotSceneObjects::dotSceneShadowSettings::get_ShadowTechnique() const { return this->_ShadowTechnique; }
bool			dotSceneObjects::dotSceneShadowSettings::get_ShowDebugShadows() const { return this->_ShowDebugShadows; }
double			dotSceneObjects::dotSceneShadowSettings::get_ShadowFarDistance() const { return this->_ShadowFarDistance; }
double			dotSceneObjects::dotSceneShadowSettings::get_ShadowDirectionalLightExtrusionDistance() const { return this->_ShadowDirectionalLightExtrusionDistance; }
int				dotSceneObjects::dotSceneShadowSettings::get_ShadowIndexBufferSize() const { return this->_ShadowIndexBufferSize; }
bool			dotSceneObjects::dotSceneShadowSettings::get_ShadowUseInfiniteFarPlane() const { return this->_ShadowUseInfiniteFarPlane; }
int				dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureCount() const { return this->_ShadowTextureCount; }
int				dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureSize() const { return this->_ShadowTextureSize; }
PixelFormat		dotSceneObjects::dotSceneShadowSettings::get_ShadowTexturePixelFormat() const { return this->_ShadowTexturePixelFormat; }
double			dotSceneObjects::dotSceneShadowSettings::get_ShadowDirLightTextureOffset() const { return this->_ShadowDirLightTextureOffset; }
double			dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureFadeStart() const { return this->_ShadowTextureFadeStart; }
double			dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureFadeEnd() const { return this->_ShadowTextureFadeEnd; }
bool			dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureSelfShadow() const { return this->_ShadowTextureSelfShadow; }
std::string		dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureCasterMaterial() const { return this->_ShadowTextureCasterMaterial; }
std::string		dotSceneObjects::dotSceneShadowSettings::get_ShadowTextureReceiverMaterial() const { return this->_ShadowTextureReceiverMaterial; }
bool			dotSceneObjects::dotSceneShadowSettings::get_ShadowCasterRenderBackFaces() const { return this->_ShadowCasterRenderBackFaces; }

dotSceneColourDiffuse dotSceneObjects::dotSceneShadowSettings::get_ColourDiffuse() const { return this->_ColourDiffuse; }

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTechnique(ShadowTechnique value) { this->_ShadowTechnique = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShowDebugShadows(bool value) { this->_ShowDebugShadows = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowFarDistance(double value) { this->_ShadowFarDistance = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowDirectionalLightExtrusionDistance(double value) { this->_ShadowDirectionalLightExtrusionDistance = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowIndexBufferSize(int value) { this->_ShadowIndexBufferSize = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowUseInfiniteFarPlane(bool value) { this->_ShadowUseInfiniteFarPlane = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureCount(int value) { this->_ShadowTextureCount = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureSize(int value) { this->_ShadowTextureSize = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTexturePixelFormat(PixelFormat value) { this->_ShadowTexturePixelFormat = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowDirLightTextureOffset(double value) { this->_ShadowDirLightTextureOffset = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureFadeStart(double value) { this->_ShadowTextureFadeStart = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureFadeEnd(double value) { this->_ShadowTextureFadeEnd = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureSelfShadow(bool value) { this->_ShadowTextureSelfShadow = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureCasterMaterial(std::string value) { this->_ShadowTextureCasterMaterial = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureReceiverMaterial(std::string value) { this->_ShadowTextureReceiverMaterial = value; }
void dotSceneObjects::dotSceneShadowSettings::set_ShadowCasterRenderBackFaces(bool value) { this->_ShadowCasterRenderBackFaces = value; }

void dotSceneObjects::dotSceneShadowSettings::set_ColourDiffuse(dotSceneColourDiffuse value) { this->_ColourDiffuse = value; }

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTechnique(std::string value)
{
	bool match = false; 

	if (value == "none")						{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::none;							match = true; } 
	if (value == "stencilModulative")			{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::stencilModulative;				match = true; } 
	if (value == "stencilAdditive")				{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::stencilAdditive;				match = true; } 
	if (value == "textureModulative")			{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::textureModulative;				match = true; } 
	if (value == "textureAdditive")				{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::textureAdditive;				match = true; }
	if (value == "textureModulativeIntegrated")	{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::textureModulativeIntegrated;	match = true; }
	if (value == "textureAdditiveIntegrated")	{ this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::textureAdditiveIntegrated;		match = true; }

	if (!match) this->_ShadowTechnique = dotSceneEnums::dotSceneShadowConfigEnums::none;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShowDebugShadows(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_ShowDebugShadows = true;	match = true; } 
	if (value == "false")	{ this->_ShowDebugShadows = false;	match = true; }

	if (!match) this->_ShowDebugShadows = false;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowFarDistance(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_ShadowFarDistance = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowDirectionalLightExtrusionDistance(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_ShadowDirectionalLightExtrusionDistance = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowIndexBufferSize(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_ShadowIndexBufferSize = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowUseInfiniteFarPlane(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_ShadowUseInfiniteFarPlane = true;	match = true; } 
	if (value == "false")	{ this->_ShadowUseInfiniteFarPlane = false;	match = true; }

	if (!match) this->_ShadowUseInfiniteFarPlane = false;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureCount(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_ShadowTextureCount = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureSize(std::string value)
{
	int tmp;
	sscanf(value.c_str(), "%d", &tmp);
	this->_ShadowTextureSize = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTexturePixelFormat(std::string value)
{
	bool match = false; 

	if (value == "PF_UNKNOWN")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_UNKNOWN;		match = true; } 
	if (value == "PF_L8")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_L8;		match = true; } 
	if (value == "PF_BYTE_L")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_L;		match = true; } 
	if (value == "PF_L16")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_L16;		match = true; } 
	if (value == "PF_SHORT_L")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_SHORT_L;		match = true; } 
	if (value == "PF_A8")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A8;		match = true; } 
	if (value == "PF_BYTE_A")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_A;		match = true; } 
	if (value == "PF_A4L4")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A4L4;		match = true; } 
	if (value == "PF_BYTE_LA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_LA;		match = true; } 
	if (value == "PF_R5G6B5")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_R5G6B5;		match = true; } 
	if (value == "PF_B5G6R5")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_B5G6R5;		match = true; } 
	if (value == "PF_R3G3B2")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_R3G3B2;		match = true; } 
	if (value == "PF_A4R4G4B4")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A4R4G4B4;		match = true; } 
	if (value == "PF_A1R5G5B5")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A1R5G5B5;		match = true; } 
	if (value == "PF_R8G8B8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_R8G8B8;		match = true; } 
	if (value == "PF_B8G8R8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_B8G8R8;		match = true; } 
	
	if (value == "PF_A8R8G8B8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A8R8G8B8;		match = true; } 
	if (value == "PF_A8B8G8R8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A8B8G8R8;		match = true; } 
	if (value == "PF_B8G8R8A8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_B8G8R8A8;		match = true; } 
	if (value == "PF_R8G8B8A8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_R8G8B8A8;		match = true; } 
	if (value == "PF_X8R8G8B8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_X8R8G8B8;		match = true; } 
	if (value == "PF_X8B8G8R8")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_X8B8G8R8;		match = true; } 
	if (value == "PF_BYTE_RGB")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_RGB;		match = true; } 
	if (value == "PF_BYTE_BGR")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_BGR;		match = true; } 
	if (value == "PF_BYTE_BGRA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_BGRA;		match = true; } 
	if (value == "PF_BYTE_RGBA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_BYTE_RGBA;		match = true; } 
	if (value == "PF_A2R10G10B10")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A2R10G10B10;	match = true; } 
	if (value == "PF_A2B10G10R10")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_A2B10G10R10;	match = true; } 
	if (value == "PF_DXT1")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DXT1;			match = true; } 
	if (value == "PF_DXT2")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DXT2;			match = true; } 
	if (value == "PF_DXT3")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DXT3;			match = true; } 
	if (value == "PF_DXT4")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DXT4;			match = true; } 
	if (value == "PF_DXT5")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DXT5;			match = true; } 

	if (value == "PF_FLOAT16_R")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT16_R;		match = true; } 
	if (value == "PF_FLOAT16_RGB")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT16_RGB;	match = true; }
	if (value == "PF_FLOAT16_RGBA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT16_RGBA;	match = true; }
	if (value == "PF_FLOAT32_R")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT32_R;		match = true; }
	if (value == "PF_FLOAT32_RGB")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT32_RGB;	match = true; }
	if (value == "PF_FLOAT32_RGBA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT32_RGBA;	match = true; }
	if (value == "PF_FLOAT16_GR")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT16_GR;	match = true; }
	if (value == "PF_FLOAT32_GR")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_FLOAT32_GR;	match = true; }
	if (value == "PF_DEPTH")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_DEPTH;			match = true; }
	if (value == "PF_SHORT_RGBA")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_SHORT_RGBA;	match = true; }
	if (value == "PF_SHORT_GR")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_SHORT_GR;		match = true; }
	if (value == "PF_SHORT_RGB")	{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_SHORT_RGB;		match = true; }
	if (value == "PF_COUNT")		{ this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_COUNT;			match = true; }

	if (!match) this->_ShadowTexturePixelFormat = dotSceneEnums::dotSceneShadowConfigEnums::PF_UNKNOWN;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowDirLightTextureOffset(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_ShadowDirLightTextureOffset = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureFadeStart(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_ShadowTextureFadeStart = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureFadeEnd(std::string value)
{
	double tmp;
	sscanf(value.c_str(), "%lf", &tmp);
	this->_ShadowTextureFadeEnd = tmp;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowTextureSelfShadow(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_ShadowTextureSelfShadow = true;		match = true; } 
	if (value == "false")	{ this->_ShadowTextureSelfShadow = false;	match = true; }

	if (!match) this->_ShadowTextureSelfShadow = false;
}

void dotSceneObjects::dotSceneShadowSettings::set_ShadowCasterRenderBackFaces(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_ShadowCasterRenderBackFaces = true;		match = true; } 
	if (value == "false")	{ this->_ShadowCasterRenderBackFaces = false;	match = true; }

	if (!match) this->_ShadowCasterRenderBackFaces = false;
}

bool dotSceneObjects::dotSceneShadowSettings::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

bool dotSceneObjects::dotSceneShadowSettings::addShadowTextureConfig(dotSceneShadowTextureConfig someShadowTextureConfig)
{
	try
	{
		this->_ListOfShadowTextureConfig.push_back(someShadowTextureConfig);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}

/// region constructors & destructors
dotSceneObjects::dotSceneShadowSettings::dotSceneShadowSettings() : dotSceneObject(dotSceneEnums::shadowSettings)
{
	this->set_ShadowTechnique(dotSceneEnums::dotSceneShadowConfigEnums::none);
	this->set_ShowDebugShadows(false);
	this->set_ShadowFarDistance(0);
	this->set_ShadowDirectionalLightExtrusionDistance(10000);
	this->set_ShadowIndexBufferSize(51200);
	this->set_ShadowUseInfiniteFarPlane(true);
	this->set_ShadowTextureCount(0);
	this->set_ShadowTextureSize(0);
	this->set_ShadowTexturePixelFormat(dotSceneEnums::dotSceneShadowConfigEnums::PF_UNKNOWN);
	this->set_ShadowDirLightTextureOffset(0.6);
	this->set_ShadowTextureFadeStart(0.7);
	this->set_ShadowTextureFadeEnd(0.9);
	this->set_ShadowTextureSelfShadow(false);
	this->set_ShadowTextureCasterMaterial("");
	this->set_ShadowTextureReceiverMaterial("");
	this->set_ShadowCasterRenderBackFaces(true);
	this->set_ColourDiffuse(dotSceneColourDiffuse());

	this->_ListOfShadowTextureConfig = std::list<dotSceneShadowTextureConfig>();
}

dotSceneObjects::dotSceneShadowSettings::dotSceneShadowSettings(
	std::string str_ShadowTechnique,
	std::string str_ShowDebugShadows,
	std::string str_ShadowFarDistance,
	std::string str_ShadowDirectionalLightExtrusionDistance,
	std::string	str_ShadowIndexBufferSize,
	std::string str_ShadowUseInfiniteFarPlane,
	std::string	str_ShadowTextureCount,
	std::string	str_ShadowTextureSize,
	std::string str_ShadowTexturePixelFormat,
	std::string str_ShadowDirLightTextureOffset,
	std::string str_ShadowTextureFadeStart,
	std::string str_ShadowTextureFadeEnd,
	std::string str_ShadowTextureSelfShadow,
	std::string	str_ShadowTextureCasterMaterial,
	std::string	str_ShadowTextureReceiverMaterial,
	std::string str_ShadowCasterRenderBackFaces,
	dotSceneColourDiffuse obj_ColourDiffuse) : dotSceneObject(dotSceneEnums::shadowSettings)
{
	this->set_ShadowTechnique(str_ShadowTechnique);
	this->set_ShowDebugShadows(str_ShowDebugShadows);
	this->set_ShadowFarDistance(str_ShadowFarDistance);
	this->set_ShadowDirectionalLightExtrusionDistance(str_ShadowDirectionalLightExtrusionDistance);
	this->set_ShadowIndexBufferSize(str_ShadowIndexBufferSize);
	this->set_ShadowUseInfiniteFarPlane(str_ShadowUseInfiniteFarPlane);
	this->set_ShadowTextureCount(str_ShadowTextureCount);
	this->set_ShadowTextureSize(str_ShadowTextureSize);
	this->set_ShadowTexturePixelFormat(str_ShadowTexturePixelFormat);
	this->set_ShadowDirLightTextureOffset(str_ShadowDirLightTextureOffset);
	this->set_ShadowTextureFadeStart(str_ShadowTextureFadeStart);
	this->set_ShadowTextureFadeEnd(str_ShadowTextureFadeEnd);
	this->set_ShadowTextureSelfShadow(str_ShadowTextureSelfShadow);
	this->set_ShadowTextureCasterMaterial(str_ShadowTextureSelfShadow);
	this->set_ShadowTextureReceiverMaterial(str_ShadowTextureReceiverMaterial);
	this->set_ShadowCasterRenderBackFaces(str_ShadowCasterRenderBackFaces);
	this->set_ColourDiffuse(obj_ColourDiffuse);
	
	this->_ListOfShadowTextureConfig = std::list<dotSceneShadowTextureConfig>();
}

dotSceneObjects::dotSceneShadowSettings::dotSceneShadowSettings(
	ShadowTechnique enum_ShadowTechnique,
	bool bool_ShowDebugShadows,
	double double_ShadowFarDistance,
	double double_ShadowDirectionalLightExtrusionDistance,
	int	int_ShadowIndexBufferSize,
	bool bool_ShadowUseInfiniteFarPlane,
	int	int_ShadowTextureCount,
	int	int_ShadowTextureSize,
	PixelFormat enum_ShadowTexturePixelFormat,
	double double_ShadowDirLightTextureOffset,
	double double_ShadowTextureFadeStart,
	double double_ShadowTextureFadeEnd,
	bool bool_ShadowTextureSelfShadow,
	std::string	str_ShadowTextureCasterMaterial,
	std::string	str_ShadowTextureReceiverMaterial,
	bool bool_ShadowCasterRenderBackFaces,
	dotSceneColourDiffuse obj_ColourDiffuse) : dotSceneObject(dotSceneEnums::shadowSettings)
{
	this->set_ShadowTechnique(enum_ShadowTechnique);
	this->set_ShowDebugShadows(bool_ShowDebugShadows);
	this->set_ShadowFarDistance(double_ShadowFarDistance);
	this->set_ShadowDirectionalLightExtrusionDistance(double_ShadowDirectionalLightExtrusionDistance);
	this->set_ShadowIndexBufferSize(int_ShadowIndexBufferSize);
	this->set_ShadowUseInfiniteFarPlane(bool_ShadowUseInfiniteFarPlane);
	this->set_ShadowTextureCount(int_ShadowTextureCount);
	this->set_ShadowTextureSize(int_ShadowTextureSize);
	this->set_ShadowTexturePixelFormat(enum_ShadowTexturePixelFormat);
	this->set_ShadowDirLightTextureOffset(double_ShadowDirLightTextureOffset);
	this->set_ShadowTextureFadeStart(double_ShadowTextureFadeStart);
	this->set_ShadowTextureFadeEnd(double_ShadowTextureFadeEnd);
	this->set_ShadowTextureSelfShadow(bool_ShadowTextureSelfShadow);
	this->set_ShadowTextureCasterMaterial(str_ShadowTextureCasterMaterial);
	this->set_ShadowTextureReceiverMaterial(str_ShadowTextureReceiverMaterial);
	this->set_ShadowCasterRenderBackFaces(bool_ShadowCasterRenderBackFaces);
	this->set_ColourDiffuse(obj_ColourDiffuse);
	
	this->_ListOfShadowTextureConfig = std::list<dotSceneShadowTextureConfig>();
}