#ifndef dotSceneLocalDirectionVector_h_
#define dotSceneLocalDirectionVector_h_
#include "dotSceneLocalDirectionVector.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneLocalDirectionVector::dotSceneLocalDirectionVector() : dotSceneObject(dotSceneEnums::localDirectionVector), dotScene3D(dotSceneEnums::localDirectionVector) { }
dotSceneObjects::dotSceneLocalDirectionVector::dotSceneLocalDirectionVector(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::localDirectionVector), dotScene3D(dotSceneEnums::localDirectionVector, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneLocalDirectionVector::dotSceneLocalDirectionVector(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::localDirectionVector), dotScene3D(dotSceneEnums::localDirectionVector, double_x, double_y, double_z) { }


