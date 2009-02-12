#ifndef dotSceneOffset_h_
#define dotSceneOffset_h_
#include "dotSceneOffset.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneOffset::dotSceneOffset() : dotSceneObject(dotSceneEnums::offset), dotScene3D(dotSceneEnums::offset) { }
dotSceneObjects::dotSceneOffset::dotSceneOffset(std::string str_x, std::string str_y, std::string str_z) : dotSceneObject(dotSceneEnums::offset), dotScene3D(dotSceneEnums::offset, str_x, str_y, str_z) { }
dotSceneObjects::dotSceneOffset::dotSceneOffset(double double_x, double double_y, double double_z) : dotSceneObject(dotSceneEnums::offset), dotScene3D(dotSceneEnums::offset, double_x, double_y, double_z) { }
