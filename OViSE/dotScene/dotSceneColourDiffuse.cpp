#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse() : dotSceneColour(colourDiffuse) { }
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(std::string str_r, std::string str_g, std::string str_b) : dotSceneColour(colourDiffuse, str_r, str_g, str_b) { }
dotSceneObjects::dotSceneColourDiffuse::dotSceneColourDiffuse(double double_r, double double_g, double double_b) : dotSceneColour(colourDiffuse, double_r, double_g, double_b) { }

