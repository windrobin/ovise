#ifndef dotSceneEnvironment_h_
#define dotSceneEnvironment_h_
#include "dotSceneEnvironment.h"
#endif

using namespace dotSceneObjects;

void dotSceneObjects::dotSceneEnvironment::set_fog(dotSceneFog value) { _fog = value; }
void dotSceneObjects::dotSceneEnvironment::set_colourBackground(dotSceneColourBackground value) { _colourBackground = value; }
void dotSceneObjects::dotSceneEnvironment::set_colourAmbient(dotSceneColourAmbient value) { _colourAmbient = value; }

dotSceneFog dotSceneObjects::dotSceneEnvironment::get_fog() const { return _fog; }
dotSceneColourBackground dotSceneObjects::dotSceneEnvironment::get_colourBackground() const { return _colourBackground; }
dotSceneColourAmbient dotSceneObjects::dotSceneEnvironment::get_colourAmbient() const { return _colourAmbient; }

///region constructors & destructors
dotSceneObjects::dotSceneEnvironment::dotSceneEnvironment() : dotSceneObject(environment) { } /// Simple constructor. It calls the constructor of baseobject   
dotSceneObjects::dotSceneEnvironment::dotSceneEnvironment(dotSceneFog obj_fog, dotSceneColourAmbient obj_colourAmbient, dotSceneColourBackground obj_colourBackground) : dotSceneObject(environment) /// The dotScene-objects have to be constructed before./// <param name="obj_fog">A pre-constrcted dotSceneFog-object.</param>/// <param name="obj_colorAmbient">A pre-constrcted dotSceneColorAmbient-object.</param>/// <param name="obj_colorBackground">A pre-constrcted dotSceneColorBackground-object.</param>
{
    this->_fog = obj_fog;
    this->_colourAmbient = obj_colourAmbient;
    this->_colourBackground = obj_colourBackground;
}

dotSceneObjects::dotSceneEnvironment::~dotSceneEnvironment() { }
