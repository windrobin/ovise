#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

///region constructors & destructors
dotSceneObjects::dotScenePosition::dotScenePosition() : dotSceneObject(dotSceneEnums::position), dotScene3D(dotSceneEnums::position) { }
dotSceneObjects::dotScenePosition::dotScenePosition(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::position), dotScene3D(dotSceneEnums::position, str_x, str_y, str_z) { }
dotSceneObjects::dotScenePosition::dotScenePosition(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::position), dotScene3D(dotSceneEnums::position, double_x, double_y, double_z) { }


