#ifndef dotSceneColourAmbient_h_
#define dotSceneColourAmbient_h_
#include "dotSceneColourAmbient.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneColourAmbient::dotSceneColourAmbient() : dotSceneObject(dotSceneEnums::colourAmbient), dotSceneColour(dotSceneEnums::colourAmbient) { } 
dotSceneObjects::dotSceneColourAmbient::dotSceneColourAmbient(std::string str_r, std::string str_g, std::string str_b) : dotSceneObject(dotSceneEnums::colourAmbient), dotSceneColour(dotSceneEnums::colourAmbient, str_r, str_g, str_b) { }
dotSceneObjects::dotSceneColourAmbient::dotSceneColourAmbient(double double_r, double double_g, double double_b) : dotSceneObject(dotSceneEnums::colourAmbient), dotSceneColour(dotSceneEnums::colourAmbient, double_r, double_g, double_b) { }

