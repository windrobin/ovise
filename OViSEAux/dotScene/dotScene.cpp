#ifndef dotScene_h_
#define dotScene_h_
#include "dotScene.h"
#endif

using namespace dotSceneObjects;

std::string dotSceneObjects::dotScene::get_FormatVersion() const { return this->_FormatVersion; }
std::string dotSceneObjects::dotScene::get_ID() const { return this->_ID; }
std::string dotSceneObjects::dotScene::get_SceneManagerType() const { return this->_SceneManagerType; }
std::string dotSceneObjects::dotScene::get_SceneManagerName() const { return this->_SceneManagerName; }
std::string dotSceneObjects::dotScene::get_MinOgreVersion() const { return this->_MinOgreVersion; }
std::string dotSceneObjects::dotScene::get_Author() const { return this->_Author; }
bool		dotSceneObjects::dotScene::get_ShowBoundingBoxes() const { return this->_ShowBoundingBoxes; }

dotSceneShadowSettings		dotSceneObjects::dotScene::get_ShadowSettings() const { return this->_ShadowSettings; }
dotSceneExternals			dotSceneObjects::dotScene::get_Externals() const { return this->_Externals; }
dotSceneNodes				dotSceneObjects::dotScene::get_Nodes() const { return this->_Nodes; }
dotSceneUserDataReference	dotSceneObjects::dotScene::get_UserDataReference() const { return this->_UserDataReference; }

void dotSceneObjects::dotScene::set_FormatVersion(std::string value) { this->_FormatVersion = value; }
void dotSceneObjects::dotScene::set_ID(std::string value) { this->_ID = value; }
void dotSceneObjects::dotScene::set_SceneManagerType(std::string value) { this->_SceneManagerType = value; }
void dotSceneObjects::dotScene::set_SceneManagerName(std::string value) { this->_SceneManagerName = value; }
void dotSceneObjects::dotScene::set_MinOgreVersion(std::string value) { this->_MinOgreVersion = value; }
void dotSceneObjects::dotScene::set_Author(std::string value) { this->_Author = value; }
void dotSceneObjects::dotScene::set_ShowBoundingBoxes(bool value) { this->_ShowBoundingBoxes = value; }

void dotSceneObjects::dotScene::set_ShadowSettings(dotSceneShadowSettings value) { this->_ShadowSettings = value; }
void dotSceneObjects::dotScene::set_Externals(dotSceneExternals value) { this->_Externals = value; }
void dotSceneObjects::dotScene::set_Nodes(dotSceneNodes value) { this->_Nodes = value; }
void dotSceneObjects::dotScene::set_UserDataReference(dotSceneUserDataReference value) { this->_UserDataReference = value; }

void dotSceneObjects::dotScene::set_ShowBoundingBoxes(std::string value)
{
	bool match = false; 
	
	if (value == "true")	{ this->_ShowBoundingBoxes = true;	match = true; } 
	if (value == "false")	{ this->_ShowBoundingBoxes = false;	match = true; }

	if (!match) this->_ShowBoundingBoxes = false;
}



bool dotSceneObjects::dotScene::IsValid() const
{
	if (this->_FormatVersion == "INVALID") return false;
	if (!this->_Nodes.IsValid()) return false;
	if (!this->_Externals.IsValid()) return false;
	if (!this->_ShadowSettings.IsValid()) return false;
	if (!this->_UserDataReference.IsValid()) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

bool dotSceneObjects::dotScene::addLight(dotSceneLight someLight)
{
	try
	{
		this->_ListOfLights.push_back(someLight);
		return true;
	}
	catch (std::exception ex) { }
	return false;
}


/// region constructors & destructors
dotSceneObjects::dotScene::dotScene() : dotSceneObject(dotSceneEnums::scene)
{
	this->set_FormatVersion("INVALID");
	this->set_ID("INITIAL_NOT_SET");
	this->set_SceneManagerType("INITIAL_NOT_SET");
	this->set_SceneManagerName("INITIAL_NOT_SET");
	this->set_MinOgreVersion("INITIAL_NOT_SET");
	this->set_Author("INITIAL_NOT_SET");
	this->set_ShowBoundingBoxes(false);

	this->set_ShadowSettings(dotSceneShadowSettings());
	this->set_Externals(dotSceneExternals());
	this->set_Nodes(dotSceneNodes());
	this->set_UserDataReference(dotSceneUserDataReference());
}

dotSceneObjects::dotScene::dotScene(
	std::string str_FormatVersion,
	std::string str_ID,
	std::string str_SceneManagerType,
	std::string str_SceneManagerName,
	std::string str_MinOgreVersion,
	std::string str_Author,
	std::string str_ShowBoundingBoxes,
	dotSceneShadowSettings obj_ShadowSettings,
	dotSceneExternals obj_Externals,
	dotSceneNodes obj_Nodes,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::scene)
{
	this->set_FormatVersion(str_FormatVersion);
	this->set_ID(str_ID);
	this->set_SceneManagerType(str_SceneManagerType);
	this->set_SceneManagerName(str_SceneManagerName);
	this->set_MinOgreVersion(str_MinOgreVersion);
	this->set_Author(str_Author);
	this->set_ShowBoundingBoxes(str_ShowBoundingBoxes);

	this->set_ShadowSettings(obj_ShadowSettings);
	this->set_Externals(obj_Externals);
	this->set_Nodes(obj_Nodes);
	this->set_UserDataReference(obj_UserDataReference);
}

dotSceneObjects::dotScene::dotScene(
	std::string str_FormatVersion,
	std::string str_ID,
	std::string str_SceneManagerType,
	std::string str_SceneManagerName,
	std::string str_MinOgreVersion,
	std::string str_Author,
	bool bool_ShowBoundingBoxes,
	dotSceneShadowSettings obj_ShadowSettings,
	dotSceneExternals obj_Externals,
	dotSceneNodes obj_Nodes,
	dotSceneUserDataReference obj_UserDataReference) : dotSceneObject(dotSceneEnums::scene)
{
	this->set_FormatVersion(str_FormatVersion);
	this->set_ID(str_ID);
	this->set_SceneManagerType(str_SceneManagerType);
	this->set_SceneManagerName(str_SceneManagerName);
	this->set_MinOgreVersion(str_MinOgreVersion);
	this->set_Author(str_Author);
	this->set_ShowBoundingBoxes(bool_ShowBoundingBoxes);

	this->set_ShadowSettings(obj_ShadowSettings);
	this->set_Externals(obj_Externals);
	this->set_Nodes(obj_Nodes);
	this->set_UserDataReference(obj_UserDataReference);
}

