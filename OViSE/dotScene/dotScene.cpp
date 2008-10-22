#ifndef dotScene_h_
#define dotScene_h_
#include "dotScene.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotScene::set_formatVersion(std::string value) { _formatVersion = value; }
void dotSceneObjects::dotScene::set_nodes(dotSceneNodes value) { _nodes = value; }
void dotSceneObjects::dotScene::set_externals(dotSceneExternals value) { _externals = value; }
void dotSceneObjects::dotScene::set_environment(dotSceneEnvironment value) { _environment = value; }

std::string dotSceneObjects::dotScene::get_formatVersion() const { return _formatVersion; }
dotSceneNodes dotSceneObjects::dotScene::get_nodes() const { return _nodes; }
dotSceneExternals dotSceneObjects::dotScene::get_externals() const { return _externals; }
dotSceneEnvironment dotSceneObjects::dotScene::get_environment() const { return _environment; }

/// region constructors & destructors
dotSceneObjects::dotScene::dotScene() : dotSceneObject(scene) { }
dotSceneObjects::dotScene::dotScene(std::string str_formatVersion, dotSceneNodes obj_nodes,  dotSceneExternals obj_externals, dotSceneEnvironment obj_environment) : dotSceneObject(scene)
{
    this->set_formatVersion(str_formatVersion);
    this->set_nodes(obj_nodes);
    this->set_externals(obj_externals);
    this->set_environment(obj_environment);
}

dotSceneObjects::dotScene::~dotScene() { }
