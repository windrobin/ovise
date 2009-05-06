#ifndef OVISEPATHPROVIDER_H_
#define OVISEPATHPROVIDER_H_

#include <iostream>

class OViSEPathProvider
{
private:
	// Metadata
	bool Valid;

	// Sperators
	std::string Seperator_Slash;
	std::string Seperator_BackSlash;
	std::string Seperator_Active;

	// Default paths
	std::string DefaultPath_OViSE_Base;
	std::string DefaultPath_OViSE_Solution;
	std::string DefaultPath_OViSE_Aux;
	std::string DefaultPath_OViSE_Media;
	std::string DefaultPath_OViSE_SceneExport;

	// Actual Paths
	std::string Path_OViSE_Base;
	std::string Path_OViSE_Solution;
	std::string Path_OViSE_Aux;
	std::string Path_OViSE_Media;
	std::string Path_OViSE_SceneExport;
public:
	OViSEPathProvider(std::string InitialPath_OViSE_Base, std::string DefaultSeperator);
	~OViSEPathProvider(void);

	std::string getSeperator_Active();

	std::string getPath_OViSE_Base(bool SeperatorAtEndOfPath = true);
	std::string getPath_OViSE_Solution(bool SeperatorAtEndOfPath = true);
	std::string getPath_OViSE_Aux(bool SeperatorAtEndOfPath = true);
	std::string getPath_OViSE_Media(bool SeperatorAtEndOfPath = true);
	std::string getPath_OViSE_SceneExport(bool SeperatorAtEndOfPath = true);
};

#endif /*OVISEPATHPROVIDER_H_*/