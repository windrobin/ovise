#ifndef dotSceneCommonUpVector_h_
#define dotSceneCommonUpVector_h_
#include "dotSceneCommonUpVector.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneCommonUpVector::dotSceneCommonUpVector() : dotSceneObject(dotSceneEnums::commonUpVector), dotScene3D(dotSceneEnums::commonUpVector) { }
dotSceneObjects::dotSceneCommonUpVector::dotSceneCommonUpVector(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::commonUpVector), dotScene3D(dotSceneEnums::commonUpVector, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneCommonUpVector::dotSceneCommonUpVector(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::commonUpVector), dotScene3D(dotSceneEnums::commonUpVector, double_x, double_y, double_z) { }

