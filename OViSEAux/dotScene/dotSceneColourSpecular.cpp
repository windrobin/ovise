#ifndef dotSceneColourSpecular_h_
#define dotSceneColourSpecular_h_
#include "dotSceneColourSpecular.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneColourSpecular::dotSceneColourSpecular() : dotSceneObject(dotSceneEnums::colourSpecular), dotSceneColour(dotSceneEnums::colourSpecular) { } 
dotSceneObjects::dotSceneColourSpecular::dotSceneColourSpecular(std::string str_r, std::string str_g, std::string str_b) : dotSceneObject(dotSceneEnums::colourSpecular), dotSceneColour(dotSceneEnums::colourSpecular, str_r, str_g, str_b) { }
dotSceneObjects::dotSceneColourSpecular::dotSceneColourSpecular(double double_r, double double_g, double double_b) : dotSceneObject(dotSceneEnums::colourSpecular), dotSceneColour(dotSceneEnums::colourSpecular, double_r, double_g, double_b) { }
