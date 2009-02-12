#ifndef dotSceneUpVector_h_
#define dotSceneUpVector_h_
#include "dotSceneUpVector.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneUpVector::dotSceneUpVector() : dotSceneObject(dotSceneEnums::upVector), dotScene3D(dotSceneEnums::upVector) { }
dotSceneObjects::dotSceneUpVector::dotSceneUpVector(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::upVector), dotScene3D(dotSceneEnums::upVector, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneUpVector::dotSceneUpVector(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::upVector), dotScene3D(dotSceneEnums::upVector, double_x, double_y, double_z) { }

