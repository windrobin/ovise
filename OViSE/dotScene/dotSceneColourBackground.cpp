#ifndef dotSceneColourBackground_h_
#define dotSceneColourBackground_h_
#include "dotSceneColourBackground.h"
#endif

///region constructors & destructors
dotSceneObjects::dotSceneColourBackground::dotSceneColourBackground() : dotSceneColour(colourBackground) { }
dotSceneObjects::dotSceneColourBackground::dotSceneColourBackground(std::string str_r, std::string str_g, std::string str_b) : dotSceneColour(colourBackground, str_r, str_g, str_b) { }
dotSceneObjects::dotSceneColourBackground::dotSceneColourBackground(double double_r, double double_g, double double_b) : dotSceneColour(colourBackground, double_r, double_g, double_b) { }

