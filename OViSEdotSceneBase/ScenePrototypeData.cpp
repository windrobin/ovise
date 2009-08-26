#include "ScenePrototypeData.h"
#include <wx/arrimpl.cpp> // the wx-documentation gives adivise to place this inluce in .cpp and not in .h

WX_DEFINE_OBJARRAY(Array_OgreMeshPtr);

ScenePrototypeData::ScenePrototypeData(void)
{
	this->ResourceBaseDir = wxFileName::GetCwd();
	this->MaterialFiles.Clear();
	this->MeshFiles.Clear();
	this->MeshDatastructures.Clear();

}

ScenePrototypeData::~ScenePrototypeData(void)
{
	this->ResourceBaseDir.Clear();
	this->MaterialFiles.Clear();
	this->MeshFiles.Clear();
	this->MeshDatastructures.Clear();
}

bool ScenePrototypeData::IsEmpty()
{
	if (!this->ResourceBaseDir.IsEmpty()) return true;
	if (!this->MaterialFiles.IsEmpty()) return true;
	if (!this->MeshFiles.IsEmpty()) return true;
	if (!this->MeshDatastructures.IsEmpty()) return true;
	return false;
}