#pragma once
#ifndef DOTSCENE_BASE_CONFIGURATION_H_
#define DOTSCENE_BASE_CONFIGURATION_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>

// Solution's includes
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/Logging.h"
#include "../OViSEAux/SceneNodeOffset.h"

// Include Ogre
#include "Ogre.h"

class DotSceneBaseConfiguration
{
public:
	DotSceneBaseConfiguration(	wxString SceneManagerName,
								wxString UniqueNameOfDotSceneManager,
								wxString UniqueNameOfAssociatedResourceGroup);
	~DotSceneBaseConfiguration(void);

	bool doAttachNodes; // <--
	bool doAttachExternals; // <--
	bool doAttachEnvironment; // <--

	wxFileName LocationOfMeshFiles; // <--

	bool doExportNotSelectedChildToo; // <--
	bool doExportMeshFiles; // <--
	bool doOverwriteWhileExport; // <--

	wxString SceneManagerName; // <--
	wxString UniqueNameOfDotSceneManager; // <--
	wxString UniqueNameOfAssociatedResourceGroup; // <--

	SceneNodeOffset SceneOffset; // <--

	void SetUniqueName(wxString UniqueNameOfDotSceneManager); // <--
	void SetUniqueNameOfOwnedResourceGroup(wxString UniqueNameOfOwnedResourceGroup); // <--
};

#endif /*DOTSCENE_BASE_CONFIGURATION_H_*/