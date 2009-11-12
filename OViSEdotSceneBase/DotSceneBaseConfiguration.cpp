#include "../OViSEdotSceneBase/DotSceneBaseConfiguration.h"

DotSceneBaseConfiguration::DotSceneBaseConfiguration(	Logging *Log,
														UniqueNameManager *PrototypeNameMgr,
														wxString SceneManagerName,
														wxString UniqueNameOfDotSceneManager,
														wxString UniqueNameOfAssociatedResourceGroup )
{
	// Implicit initialisation (no check)
	// DOM -> Ogre
	this->doAttachExternals = true;
	this->doAttachNodes = true;
	this->doAttachEnvironment = true;

	this->LocationOfMeshFiles = wxFileName(wxFileName::GetCwd());
	this->LocationOfMeshFiles.SetName(wxString());
	this->LocationOfMeshFiles.SetEmptyExt();

	// Ogre -> DOM
	this->doExportNotSelectedChildToo = true;
	this->doExportMeshFiles = true;
	this->doOverwriteWhileExport = true;

	// Explicit initialisation // TODO: integrity-check, range-check
	this->Log = Log;
	
	this->PrototypeNameMgr = PrototypeNameMgr;

	this->SceneManagerName = SceneManagerName;
	this->UniqueNameOfDotSceneManager = UniqueNameOfDotSceneManager,
	this->UniqueNameOfAssociatedResourceGroup = UniqueNameOfAssociatedResourceGroup;
}

DotSceneBaseConfiguration::~DotSceneBaseConfiguration(void) { }
