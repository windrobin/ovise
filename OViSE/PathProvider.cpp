#include "PathProvider.h"

wxString OViSEPathProvider::UnifyPathSeperators_Slash(const wxString Path)
{
	wxString UnifiedPath(Path);
	UnifiedPath.Replace(wxT("\\"), wxT("/"), true);
	return UnifiedPath;
}

OViSEPathProvider::OViSEPathProvider(std::string InitialPath_OViSE_Base, std::string DefaultSeperator)
{
	// Get WorkingDirectory...
	wxString temp = ::wxGetCwd();
	::wxString tempInitialWorkingDirectory = OViSEPathProvider::UnifyPathSeperators_Slash(temp);
	this->DefaultPath_OViSE_WorkingDirectory.Open(tempInitialWorkingDirectory);
	if (this->DefaultPath_OViSE_WorkingDirectory.IsOpened()) this->setPath_WorkingDirectory(this->DefaultPath_OViSE_WorkingDirectory.GetName());
	else this->Path_OViSE_WorkingDirectory.Open(wxString(wxT("INVALID")));

	// Look for BaseDir... TODO: Later take configuration from XML-file!
	if (this->DefaultPath_OViSE_WorkingDirectory.IsOpened())
	{
		wxString tempInitialBaseDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_WorkingDirectory.GetName()));
		tempInitialBaseDirectory = tempInitialBaseDirectory.BeforeLast(wxT('/'));

		if (tempInitialBaseDirectory.IsEmpty() || (tempInitialBaseDirectory.Last() == wxT(':')))
		{
			this->DefaultPath_OViSE_BaseDirectory.Open(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_WorkingDirectory.GetName()));
		}
		else this->DefaultPath_OViSE_BaseDirectory.Open(tempInitialBaseDirectory);
		if (this->DefaultPath_OViSE_BaseDirectory.IsOpened())
		{
			this->setPath_BaseDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_BaseDirectory.GetName()));
		}
		else this->Path_OViSE_BaseDirectory.Open(wxString(wxT("INVALID")));
	}
	else
	{
		this->DefaultPath_OViSE_BaseDirectory.Open(wxString(wxT("INVALID")));
		this->Path_OViSE_BaseDirectory.Open(wxString(wxT("INVALID")));
	}

	// Look for special subdirectories... TODO: Later take configuration from XML-file!
	if (this->DefaultPath_OViSE_BaseDirectory.IsOpened())
	{
		// Solution...
		if (this->DefaultPath_OViSE_BaseDirectory.Exists(this->DefaultPath_OViSE_BaseDirectory.GetName() + wxT("/OViSE")))
		{
			this->DefaultPath_OViSE_SolutionDirectory.Open(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_BaseDirectory.GetName()) + wxT("/OViSE"));
			if(this->DefaultPath_OViSE_SolutionDirectory.IsOpened()) this->setPath_SolutionDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_SolutionDirectory.GetName()));
			else this->Path_OViSE_SolutionDirectory.Open(wxString(wxT("INVALID")));
		}
		else
		{
			this->DefaultPath_OViSE_SolutionDirectory.Open(wxString(wxT("INVALID")));
			this->Path_OViSE_SolutionDirectory.Open(wxString(wxT("INVALID")));
		}

		// Aux...
		if (this->DefaultPath_OViSE_BaseDirectory.Exists(this->DefaultPath_OViSE_BaseDirectory.GetName() + wxT("/OViSEAux")))
		{
			this->DefaultPath_OViSE_AuxDirectory.Open(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_BaseDirectory.GetName()) + wxT("/OViSEAux"));
			if(this->DefaultPath_OViSE_AuxDirectory.IsOpened()) this->setPath_AuxDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_AuxDirectory.GetName()));
			else this->Path_OViSE_AuxDirectory.Open(wxString(wxT("INVALID")));
		}
		else
		{
			this->DefaultPath_OViSE_AuxDirectory.Open(wxString(wxT("INVALID")));
			this->Path_OViSE_AuxDirectory.Open(wxString(wxT("INVALID")));
		}

		// Media...
		if (this->DefaultPath_OViSE_BaseDirectory.Exists(this->DefaultPath_OViSE_BaseDirectory.GetName() + wxT("/Media")))
		{
			this->DefaultPath_OViSE_MediaDirectory.Open(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_BaseDirectory.GetName()) + wxT("/Media"));
			if(this->DefaultPath_OViSE_MediaDirectory.IsOpened()) this->setPath_MediaDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_MediaDirectory.GetName()));
			else this->Path_OViSE_MediaDirectory.Open(wxString(wxT("INVALID")));
		}
		else
		{
			this->DefaultPath_OViSE_MediaDirectory.Open(wxString(wxT("INVALID")));
			this->Path_OViSE_MediaDirectory.Open(wxString(wxT("INVALID")));
		}

		// SceneExport...
		if (this->DefaultPath_OViSE_MediaDirectory.Exists(this->DefaultPath_OViSE_MediaDirectory.GetName() + wxT("/SceneExport")))
		{
			this->DefaultPath_OViSE_SceneExportDirectory.Open(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_MediaDirectory.GetName()) + wxT("/SceneExport"));
			if(this->DefaultPath_OViSE_SceneExportDirectory.IsOpened()) this->setPath_SceneExportDirectory(OViSEPathProvider::UnifyPathSeperators_Slash(this->DefaultPath_OViSE_SceneExportDirectory.GetName()));
			else this->Path_OViSE_SceneExportDirectory.Open(wxString(wxT("INVALID")));
		}
		else
		{
			this->DefaultPath_OViSE_SceneExportDirectory.Open(wxString(wxT("INVALID")));
			this->Path_OViSE_SceneExportDirectory.Open(wxString(wxT("INVALID")));
		}
	}
}

OViSEPathProvider::~OViSEPathProvider(void) { }

bool OViSEPathProvider::setPath_WorkingDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_WorkingDirectory.Open(Path);
		return this->Path_OViSE_WorkingDirectory.IsOpened();	
	}
	else return false;
}

bool OViSEPathProvider::setPath_BaseDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_BaseDirectory.Open(Path);
		return this->Path_OViSE_BaseDirectory.IsOpened();	
	}
	else return false;
}

bool OViSEPathProvider::setPath_SolutionDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_SolutionDirectory.Open(Path);
		return this->Path_OViSE_SolutionDirectory.IsOpened();	
	}
	else return false;
}

bool OViSEPathProvider::setPath_AuxDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_AuxDirectory.Open(Path);
		return this->Path_OViSE_AuxDirectory.IsOpened();	
	}
	else return false;
}

bool OViSEPathProvider::setPath_MediaDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_MediaDirectory.Open(Path);
		return this->Path_OViSE_MediaDirectory.IsOpened();	
	}
	else return false;
}
bool OViSEPathProvider::setPath_SceneExportDirectory(const wxString Path)
{
	if (wxDir::Exists(Path))
	{
		this->Path_OViSE_SceneExportDirectory.Open(Path);
		return this->Path_OViSE_SceneExportDirectory.IsOpened();	
	}
	else return false;
}
wxString OViSEPathProvider::getPath_WorkingDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_WorkingDirectory.GetName()); }
wxString OViSEPathProvider::getPath_BaseDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_BaseDirectory.GetName()); }
wxString OViSEPathProvider::getPath_SolutionDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_SolutionDirectory.GetName()); }
wxString OViSEPathProvider::getPath_AuxDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_AuxDirectory.GetName()); }
wxString OViSEPathProvider::getPath_MediaDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_MediaDirectory.GetName()); }
wxString OViSEPathProvider::getPath_SceneExportDirectory() { return OViSEPathProvider::UnifyPathSeperators_Slash(this->Path_OViSE_SceneExportDirectory.GetName()); }