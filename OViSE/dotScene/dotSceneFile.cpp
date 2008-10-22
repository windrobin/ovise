#ifndef dotSceneFile_h_
#define dotSceneFile_h_
#include "dotSceneFile.h"
#endif

void dotSceneObjects::dotSceneFile::set_name(std::string value) { _name = value; }

std::string dotSceneObjects::dotSceneFile::get_name() { return _name; }

/// region constructors & destructors
dotSceneObjects::dotSceneFile::dotSceneFile() : dotSceneObject(file) { } 
dotSceneObjects::dotSceneFile::dotSceneFile(std::string str_name) : dotSceneObject(file)
{
    this->set_name(str_name);
}
