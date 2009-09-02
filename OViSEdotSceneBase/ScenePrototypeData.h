#pragma once
#ifndef SCENE_PROTOTYPE_DATA_H_
#define SCENE_PROTOTYPE_DATA_H_

// Include Ogre
#include "Ogre.h"

// Include WX
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(Ogre::MeshPtr, Array_OgreMeshPtr);

// IDEA: All data of a scene-prototype without xml-things!
class ScenePrototypeData
{
public:
	wxString			ResourceBaseDir;	// Import-path, if scene has been imported. Default export-path, if not.
	wxArrayString		Files;				// All files
	wxArrayString		MaterialFiles;		// Material-files in "all files"
	wxArrayString		MeshFiles;			// Mesh-files in "all files"
	wxArrayString		XMLFiles;			// XML-files in "all files"
	Array_OgreMeshPtr	MeshDatastructures;	// Poiters to loaded or build meshs in Ogre

	ScenePrototypeData();
	~ScenePrototypeData(void);
	bool IsEmpty();
};

#endif /*OVISE_SCENE_PROTOTYPE_DATA_H_*/