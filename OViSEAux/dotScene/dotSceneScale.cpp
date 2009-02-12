#ifndef dotSceneScale_h_
#define dotSceneScale_h_
#include "dotSceneScale.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneScale::dotSceneScale() : dotSceneObject(dotSceneEnums::scale), dotScene3D(dotSceneEnums::scale) { }
dotSceneObjects::dotSceneScale::dotSceneScale(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::scale), dotScene3D(dotSceneEnums::scale, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneScale::dotSceneScale(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::scale), dotScene3D(dotSceneEnums::scale, double_x, double_y, double_z) { }
