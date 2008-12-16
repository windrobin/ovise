#ifndef dotSceneEnvironment_h_
#define dotSceneEnvironment_h_
#include "dotSceneEnvironment.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneEnvironment::set_fog(dotSceneFog value) { this->_fog = value; }
void dotSceneObjects::dotSceneEnvironment::set_colourBackground(dotSceneColourBackground value) { this->_colourBackground = value; }
void dotSceneObjects::dotSceneEnvironment::set_colourAmbient(dotSceneColourAmbient value) { this->_colourAmbient = value; }

dotSceneFog dotSceneObjects::dotSceneEnvironment::get_fog() const { return this->_fog; }
dotSceneColourBackground dotSceneObjects::dotSceneEnvironment::get_colourBackground() const { return this->_colourBackground; }
dotSceneColourAmbient dotSceneObjects::dotSceneEnvironment::get_colourAmbient() const { return this->_colourAmbient; }

bool dotSceneObjects::dotSceneEnvironment::IsValid() const
{
	if (!this->_fog.IsValid()) return false;
	if (!this->_colourAmbient.IsValid()) return false;
	if (!this->_colourBackground.IsValid()) return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}
///region constructors & destructors
dotSceneObjects::dotSceneEnvironment::dotSceneEnvironment() : dotSceneObject(dotSceneEnums::environment) { }
dotSceneObjects::dotSceneEnvironment::dotSceneEnvironment(dotSceneFog obj_fog, dotSceneColourAmbient obj_colourAmbient, dotSceneColourBackground obj_colourBackground) : dotSceneObject(dotSceneEnums::environment)
{
    this->set_fog(obj_fog);
    this->set_colourAmbient(obj_colourAmbient);
    this->set_colourBackground(obj_colourBackground);
}

