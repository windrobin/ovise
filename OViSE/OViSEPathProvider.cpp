#include "OViSEPathProvider.h"

OViSEPathProvider::OViSEPathProvider(std::string InitialPath_OViSE_Base, std::string DefaultSeperator)
{
	this->Valid = true;

	// Clear all strings...
	this->DefaultPath_OViSE_Base = "INVALID";
	this->DefaultPath_OViSE_Solution = "INVALID";
	this->DefaultPath_OViSE_Aux = "INVALID";
	this->DefaultPath_OViSE_Media = "INVALID";
	this->DefaultPath_OViSE_SceneExport = "INVALID";
	this->Path_OViSE_Base = "INVALID";
	this->Path_OViSE_Solution = "INVALID";
	this->Path_OViSE_Aux = "INVALID";
	this->Path_OViSE_Media = "INVALID";
	this->Path_OViSE_SceneExport = "INVALID";

	// Initialize seperators...
	// TODO: enum Slash, BackSlash, Auto. Auto:'ll take seperator form InitialPath_OViSE_Base
	this->Seperator_Slash = "/";
	this->Seperator_BackSlash = "\\";

	if (DefaultSeperator.compare(this->Seperator_Slash) != 0) this->Seperator_Active = this->Seperator_Slash;
	else
	{
		if (DefaultSeperator.compare(this->Seperator_BackSlash) != 0) this->Seperator_Active = this->Seperator_BackSlash;
		else
		{
			this->Seperator_Active = "INVALID";
			this->Valid = false;
		}
	}

	// Initialize (default-)paths... //<- TODO: BasePath has to be checked !!!
	if (this->Valid)
	{
		// TODO: trunc PathSeperator at end
		// TODO DONE: use seperaors not in default but in actives? build 'em when accessed and store in some "last" paths, don't touch defaults!
		//            So structure-logic can be used, while acessing none-default paths!
		this->DefaultPath_OViSE_Base = InitialPath_OViSE_Base; // For example "C:/OViSE"
		this->DefaultPath_OViSE_Solution = "OViSE";
		this->DefaultPath_OViSE_Aux = "OViSEAux";
		this->DefaultPath_OViSE_Media = "Media";
		this->DefaultPath_OViSE_SceneExport = "SceneExport";

		this->Path_OViSE_Base = this->DefaultPath_OViSE_Base;

		this->Path_OViSE_Solution = this->DefaultPath_OViSE_Base;
		this->Path_OViSE_Solution += this->Seperator_Active;
		this->Path_OViSE_Solution += this->DefaultPath_OViSE_Solution;

		this->Path_OViSE_Aux = this->DefaultPath_OViSE_Base;
		this->Path_OViSE_Aux += this->Seperator_Active;
		this->Path_OViSE_Aux += this->DefaultPath_OViSE_Aux;

		this->Path_OViSE_Media = this->DefaultPath_OViSE_Base;
		this->Path_OViSE_Media += this->Seperator_Active;
		this->Path_OViSE_Media += this->DefaultPath_OViSE_Media;

		this->Path_OViSE_SceneExport = this->DefaultPath_OViSE_Base;
		this->Path_OViSE_SceneExport += this->Seperator_Active;
		this->Path_OViSE_SceneExport += this->DefaultPath_OViSE_Media;
		this->Path_OViSE_SceneExport += this->Seperator_Active;
		this->Path_OViSE_SceneExport += this->DefaultPath_OViSE_SceneExport;
	}
}

OViSEPathProvider::~OViSEPathProvider(void) { }

std::string OViSEPathProvider::getSeperator_Active() { return this->Seperator_Active; }

std::string OViSEPathProvider::getPath_OViSE_Base(bool SeperatorAtEndOfPath)
{
	std::string BuildPath = this->Path_OViSE_Base;
	if (SeperatorAtEndOfPath) BuildPath += this->Seperator_Active;
	return BuildPath;
}
std::string OViSEPathProvider::getPath_OViSE_Solution(bool SeperatorAtEndOfPath)
{
	std::string BuildPath = this->Path_OViSE_Solution;
	if (SeperatorAtEndOfPath) BuildPath += this->Seperator_Active;
	return BuildPath;
}
std::string OViSEPathProvider::getPath_OViSE_Aux(bool SeperatorAtEndOfPath)
{
	std::string BuildPath = this->Path_OViSE_Aux;
	if (SeperatorAtEndOfPath) BuildPath += this->Seperator_Active;
	return BuildPath;
}
std::string OViSEPathProvider::getPath_OViSE_Media(bool SeperatorAtEndOfPath)
{
	std::string BuildPath = this->Path_OViSE_Media;
	if (SeperatorAtEndOfPath) BuildPath += this->Seperator_Active;
	return BuildPath;
}
std::string OViSEPathProvider::getPath_OViSE_SceneExport(bool SeperatorAtEndOfPath)
{
	std::string BuildPath = this->Path_OViSE_SceneExport;
	if (SeperatorAtEndOfPath) BuildPath += this->Seperator_Active;
	return BuildPath;
}
