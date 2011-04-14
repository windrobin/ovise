/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* INFO: Standard seperator of paths is 'slash' from now on. All 'backslashs' are replaced. (H.R. 07.05.09)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef OVISEPATHPROVIDER_H_
#define OVISEPATHPROVIDER_H_

#include <iostream>
#include <wx/filefn.h>
#include <wx/dir.h>

class OViSEPathProvider
{
private:
	// Default paths
	wxDir DefaultPath_OViSE_WorkingDirectory;
	wxDir DefaultPath_OViSE_BaseDirectory;
	wxDir DefaultPath_OViSE_SolutionDirectory;
	wxDir DefaultPath_OViSE_AuxDirectory;
	wxDir DefaultPath_OViSE_MediaDirectory;
	wxDir DefaultPath_OViSE_SceneExportDirectory;

	// Actual paths
	wxDir Path_OViSE_WorkingDirectory;
	wxDir Path_OViSE_BaseDirectory;
	wxDir Path_OViSE_SolutionDirectory;
	wxDir Path_OViSE_AuxDirectory;
	wxDir Path_OViSE_MediaDirectory;
	wxDir Path_OViSE_SceneExportDirectory;

	static wxString UnifyPathSeperators_Slash( const wxString Path );
public:
	OViSEPathProvider( std::string InitialPath_OViSE_Base,
	                   std::string DefaultSeperator );
	~OViSEPathProvider( void );

	bool setPath_WorkingDirectory( const wxString Path );
	bool setPath_BaseDirectory( const wxString Path );
	bool setPath_SolutionDirectory( const wxString Path );
	bool setPath_AuxDirectory( const wxString Path );
	bool setPath_MediaDirectory( const wxString Path );
	bool setPath_SceneExportDirectory( const wxString Path );

	wxString getPath_WorkingDirectory();
	wxString getPath_BaseDirectory();
	wxString getPath_SolutionDirectory();
	wxString getPath_AuxDirectory();
	wxString getPath_MediaDirectory();
	wxString getPath_SceneExportDirectory();
};

#endif /*OVISEPATHPROVIDER_H_*/
