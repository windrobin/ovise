#include "OViSEScenePrototypeData.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(Array_OgreMeshPtr);

OViSEScenePrototypeData::OViSEScenePrototypeData(void)
{
	this->ResourceBaseDir = wxFileName::GetCwd();
	this->MaterialFiles.Clear();
	this->MeshFiles.Clear();
	this->MeshDatastructures.Clear();

}

OViSEScenePrototypeData::~OViSEScenePrototypeData(void)
{
	this->ResourceBaseDir.Clear();
	this->MaterialFiles.Clear();
	this->MeshFiles.Clear();
	this->MeshDatastructures.Clear();
}

bool OViSEScenePrototypeData::IsEmpty()
{
	if (!this->ResourceBaseDir.IsEmpty()) return true;
	if (!this->MaterialFiles.IsEmpty()) return true;
	if (!this->MeshFiles.IsEmpty()) return true;
	if (!this->MeshDatastructures.IsEmpty()) return true;
	return false;
}