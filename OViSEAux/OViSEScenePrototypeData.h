#ifndef OVISE_SCENE_PROTOTYPE_DATA_H_
#define OVISE_SCENE_PROTOTYPE_DATA_H_

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_FILENAME_USED
#define WX_FILENAME_USED
#include <wx/filename.h>
#endif

#ifndef WX_ARRAYSTRING_USED
#define WX_ARRAYSTRING_USED
#include <wx/arrstr.h>
#endif

#ifndef WX_ARRAY_USED
#define WX_ARRAY_USED
#include <wx/dynarray.h>
#endif

WX_DECLARE_OBJARRAY(Ogre::MeshPtr, Array_OgreMeshPtr);

// IDEA: All data of a scene-prototype without xml-things!
class OViSEScenePrototypeData
{
public:
	wxString			ResourceBaseDir;	// Import-path, if scene has been imported. Default export-path, if not.
	wxArrayString		Files;				// All files
	wxArrayString		MaterialFiles;		// Material-files in "all files"
	wxArrayString		MeshFiles;			// Mesh-files in "all files"
	wxArrayString		XMLFiles;			// XML-files in "all files"
	Array_OgreMeshPtr	MeshDatastructures;	// Poiters to loaded or build meshs in Ogre

	OViSEScenePrototypeData();
	~OViSEScenePrototypeData(void);
	bool IsEmpty();
};

#endif /*OVISE_SCENE_PROTOTYPE_DATA_H_*/
