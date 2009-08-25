#pragma once

#ifndef OVISE_DOTSCENE_MANAGER_CONFIGURATION_H_
#define OVISE_DOTSCENE_MANAGER_CONFIGURATION_H_

// Solution's includes
#ifndef OVISE_UNIQUENAME_GENERATOR_USED
#define OVISE_UNIQUENAME_GENERATOR_USED
#include "../OViSE/OViSEUniqueNameGenerator.h"
#endif

#ifndef OVISE_LOGGING_USED
#define OVISE_LOGGING_USED
#include "../OViSE/OViSELogging.h"
#endif

#ifndef OVISE_SCENENODE_OFFSET_USED
#define OVISE_SCENENODE_OFFSET_USED
#include "./OViSESceneNodeOffset.h"
#endif


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

class OViSEDotSceneManagerConfiguration // TODO: Parameters -> integrity-check, range-check
{
public:
	OViSEDotSceneManagerConfiguration(	OViSELogging *Log,
										OViSEUniqueNameGenerator *SceneNameMgr,
										OViSEUniqueNameGenerator *SceneNodeNameMgr,
										OViSEUniqueNameGenerator *EntityNameMgr,
										wxString SceneManagerName,
										wxString UniqueNameOfDotSceneManager,
										wxString UniqueNameOfAssociatedResourceGroup);
	~OViSEDotSceneManagerConfiguration(void);

	bool doAttachNodes;
	bool doAttachExternals;
	bool doAttachEnvironment;

	wxFileName LocationOfMeshFiles;

	bool doExportNotSelectedChildToo;
	bool doExportMeshFiles;
	bool doOverwriteWhileExport;

	OViSELogging *Log;

	OViSEUniqueNameGenerator *ScenePrototypeNameMgr;
	OViSEUniqueNameGenerator *SceneNodeNameMgr;
	OViSEUniqueNameGenerator *EntityNameMgr;

	wxString SceneManagerName;
	wxString UniqueNameOfDotSceneManager;
	wxString UniqueNameOfAssociatedResourceGroup;

	OViSESceneNodeOffset SceneOffset;

	void SetUniqueName(wxString UniqueNameOfDotSceneManager);
	void SetUniqueNameOfOwnedResourceGroup(wxString UniqueNameOfOwnedResourceGroup);
};

#endif // OVISE_DOTSCENE_MANAGER_CONFIGURATION_H_