#ifndef dotSceneFile_h_
#define dotSceneFile_h_
#include "dotSceneFile.h"
#endif

void dotSceneObjects::dotSceneFile::set_FileName(std::string value)
{
	this->_FileName = value;
}

std::string dotSceneObjects::dotSceneFile::get_FileName() const
{
	return this->_FileName;
}

bool dotSceneObjects::dotSceneFile::IsValid() const
{
	if (this->_FileName == "INVALID") return false;
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	
	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneFile::dotSceneFile() : dotSceneObject(dotSceneEnums::file)
{
	this->_FileName = "INVALID";
} 

dotSceneObjects::dotSceneFile::dotSceneFile(std::string FileName) : dotSceneObject(dotSceneEnums::file)
{
	this->_FileName = "INVALID";

    this->set_FileName(FileName);
}
