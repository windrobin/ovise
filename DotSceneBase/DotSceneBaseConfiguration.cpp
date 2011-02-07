/********************************************************************************
* Name:      DotSceneBaseConfiguration.cpp										*
* Purpose:   This class holds parameters, which are neccessary for im- & export*
*			  dotScene-files(prototypes.										*
* Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
* Created:   2009-11-13														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#include "../OViSEdotSceneBase/DotSceneBaseConfiguration.h"

DotSceneBaseConfiguration::DotSceneBaseConfiguration()
{
	// Attributes, import (DOM -> Ogre)
	this->doAttachExternals = true;
	this->doAttachNodes = true;
	this->doAttachEnvironment = true;
	SceneNodeOffset SceneOffset;

	// Attributes, export (Ogre -> DOM)
	this->doExportNotSelectedChildToo = true;
	this->doExportMeshFiles = true;
	this->doOverwriteWhileExport = true;

	// Attributes, both

	this->LocationOfMeshFiles = wxFileName( wxFileName::GetCwd());
	this->LocationOfMeshFiles.SetName( wxString());
	this->LocationOfMeshFiles.SetEmptyExt();
}

DotSceneBaseConfiguration::~DotSceneBaseConfiguration()
{}
