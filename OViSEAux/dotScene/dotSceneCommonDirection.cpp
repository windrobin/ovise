#ifndef dotSceneCommonDirection_h_
#define dotSceneCommonDirection_h_
#include "dotSceneCommonDirection.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneCommonDirection::dotSceneCommonDirection() : dotSceneObject(dotSceneEnums::commonDirection), dotScene3D(dotSceneEnums::commonDirection) { }
dotSceneObjects::dotSceneCommonDirection::dotSceneCommonDirection(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::commonDirection), dotScene3D(dotSceneEnums::commonDirection, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneCommonDirection::dotSceneCommonDirection(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::commonDirection), dotScene3D(dotSceneEnums::commonDirection, double_x, double_y, double_z) { }

