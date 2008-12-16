#ifndef dotSceneNormal_h_
#define dotSceneNormal_h_
#include "dotSceneNormal.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneNormal::dotSceneNormal() : dotSceneObject(dotSceneEnums::normal), dotScene3D(dotSceneEnums::normal) { }
dotSceneObjects::dotSceneNormal::dotSceneNormal(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::normal), dotScene3D(dotSceneEnums::normal, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneNormal::dotSceneNormal(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::normal), dotScene3D(dotSceneEnums::normal, double_x, double_y, double_z) { }
