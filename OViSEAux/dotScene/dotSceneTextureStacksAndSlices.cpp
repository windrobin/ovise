#ifndef dotSceneTextureStacksAndSlices_h_
#define dotSceneTextureStacksAndSlices_h_
#include "dotSceneTextureStacksAndSlices.h"
#endif

std::string dotSceneObjects::dotSceneTextureStacksAndSlices::get_Stacks() const { return this->_Stacks; }
std::string dotSceneObjects::dotSceneTextureStacksAndSlices::get_Slices() const { return this->_Slices; }

void dotSceneObjects::dotSceneTextureStacksAndSlices::set_Stacks(std::string value) { this->_Stacks = value; }
void dotSceneObjects::dotSceneTextureStacksAndSlices::set_Slices(std::string value) { this->_Slices = value; }

bool dotSceneObjects::dotSceneTextureStacksAndSlices::IsValid() const
{
	if (this->_Stacks == "INVALID") return false; //#REQUIRED
	if (this->_Slices == "INVALID") return false; //#REQUIRED
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;
	
	return true;
}

/// region constructors & destructors
dotSceneObjects::dotSceneTextureStacksAndSlices::dotSceneTextureStacksAndSlices() : dotSceneObject(dotSceneEnums::textureStacksAndSlices)
{
	this->set_Stacks("INVALID");
	this->set_Slices("INVALID");
} 

dotSceneObjects::dotSceneTextureStacksAndSlices::dotSceneTextureStacksAndSlices(std::string str_Stacks, std::string str_Slices) : dotSceneObject(dotSceneEnums::textureStacksAndSlices)
{
	this->set_Stacks(str_Stacks);
	this->set_Slices(str_Slices);
}
