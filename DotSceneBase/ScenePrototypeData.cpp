/********************************************************************************
* Name:      ScenePrototypeData.cpp											*
* Purpose:   Code implements a class, where all data of a scene-prototype is    *
*			  stored. Additional, pointers to meshs in Ogre-engine are stord	*
*			  too. Goal is to have everything in right position, when a scene	*
*			  should be exported.												*
* Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
* Created:   2009-11-12														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#include "../OViSEdotSceneBase/ScenePrototypeData.h"
#include <wx/arrimpl.cpp> // the wx-documentation gives adivise to place this inluce in .cpp and not in .h

WX_DEFINE_OBJARRAY( Array_OgreMeshPtr );

ScenePrototypeData::ScenePrototypeData( void )
{
	this->ResourceBaseDir = wxFileName::GetCwd();
	this->MaterialFiles.Clear();
	this->MeshFiles.Clear();
	this->MeshDatastructures.Clear();
}

ScenePrototypeData::~ScenePrototypeData( void )
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
