/********************************************************************************
 * Name:      DotSceneBaseConfiguration.h										*
 * Purpose:   This class holds parameters, which are neccessary for im- & export*
 *			  dotScene-files(prototypes.										*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef DOTSCENE_BASE_CONFIGURATION_H_
#define DOTSCENE_BASE_CONFIGURATION_H_

// Include WX
#include <wx/string.h>
#include <wx/filename.h>

// Solution's includes
#include "../OViSEAux/QualifiedName.h"
#include "../OViSEAux/SceneNodeOffset.h"

// Include Ogre
#include "Ogre.h"

class DotSceneBaseConfiguration
{
public:
	DotSceneBaseConfiguration(	QualifiedName qSceneManager,
								QualifiedName qDotSceneManager,
								QualifiedName qResourceGroup);
	~DotSceneBaseConfiguration(void);

	// Attributes, import
	bool doAttachNodes;
	bool doAttachExternals;
	bool doAttachEnvironment;
	SceneNodeOffset SceneOffset;

	// Attributes, export
	bool doExportNotSelectedChildToo;
	bool doExportMeshFiles;
	bool doOverwriteWhileExport;

	// Attributes, both
	QualifiedName qSceneManager;
	QualifiedName qDotSceneManager;
	QualifiedName qResourceGroup;
	wxFileName LocationOfMeshFiles;
};

#endif /*DOTSCENE_BASE_CONFIGURATION_H_*/