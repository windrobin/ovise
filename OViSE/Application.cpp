/***************************************************************
 * Name:      Application.cpp
 * Purpose:   Code for Application Class
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include <wx/splash.h>

#include "Application.h"
#include "MainFrame.h"

#include <wx/file.h>
#include <wx/string.h>
#include <wx/config.h>
#include "PathConfigDialog.h"


IMPLEMENT_APP(OViSEApplication);

/** Setup the path configuration, if it does not exist yet.
	\returns false if the user canceled the process, true otherwise.
	\todo Rename? The name is somewhat misleading.
*/
bool OViSEApplication::SetupBasicConfiguration()
{
	// FIXME: move this info out of the root config?

	// Get config
	wxConfig OviseConfig;

	// Configuration already done?
	if ( OviseConfig.ReadBool("ConfigurationDone", false) )
		return true;

	// The names of the tags in the config
	const wxString BasePathKey = wxT("BaseDirStr");
	const wxString MediaPathKey = wxT("MediaDirStr");
	const wxString WorkPathKey = wxT("WorkingDir");


	// Try to guess values based on the working directory
	wxString	WorkingDirectory = wxFileName::GetCwd();

	// Look for base-path...
	wxFileName	BasePath = wxFileName::DirName(WorkingDirectory);
	BasePath.RemoveLastDir();

	// Assume that the working directory is a subdir of our base path.
	// Also, assume that the base path starts with "ovise"
	wxArrayString BasePathFolders = BasePath.GetDirs();
	for ( size_t i=0,ei=BasePathFolders.GetCount();i<ei;++i )
	{
		wxString& CurrentDir(BasePathFolders[ei-1-i]);
		CurrentDir.MakeLower(); // Do this case insensitive

		if ( CurrentDir.StartsWith("ovise") )
			break;

		BasePath.RemoveLastDir();
	}

	// Append the media path
	wxFileName	MediaPath = BasePath;
	MediaPath.AppendDir("Media");
	
	// Read values from the config, using the guessed values as a default
	wxString BasePathValue = OviseConfig.Read(BasePathKey,BasePath.GetPath());
	wxString MediaPathValue = OviseConfig.Read(MediaPathKey,MediaPath.GetPath());
	WorkingDirectory = OviseConfig.Read(WorkPathKey,WorkingDirectory);

	// Run the dialog..
	OViSEPathConfigDialog ConfigDialog(WorkingDirectory, BasePathValue, MediaPathValue, NULL);

	switch( ConfigDialog.ShowModal() )
	{
		case wxID_OK:
			// Save if the user wants this
			OviseConfig.Write(WorkPathKey, ConfigDialog.GetCmdPath());
			OviseConfig.Write(BasePathKey, ConfigDialog.GetBasePath());
			OviseConfig.Write(MediaPathKey, ConfigDialog.GetMediaPath());

			OviseConfig.Write("ConfigurationDone", true);
			return true;

		default:
		case wxID_CANCEL:
			// Do not save
			return false;
	}

}

bool OViSEApplication::OnInit()
{
	// Bump out if configuration fails
	if ( !this->SetupBasicConfiguration() )
		return false;

	// Retrieve the media path
	wxConfig OviseConfig;
	wxString MediaPath=OviseConfig.Read(wxT("MediaDirStr"));
	wxFileName::SetCwd( OviseConfig.Read(wxT("WorkingDir")));

	wxImage::AddHandler( new wxPNGHandler );
	wxBitmap Bitmap;
	wxSplashScreen *splash = NULL;

	// Check whether the the Splash image can be loaded
	// This works also as a test to check whether path configuration was successful
	if (Bitmap.LoadFile(MediaPath + wxT("/Splash/OViSESplash.png"), wxBITMAP_TYPE_PNG))
	{
		splash = new wxSplashScreen(Bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT, 0, NULL, -1, wxDefaultPosition,
			wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP);
	}
	else
	{
		// Exit gracefully if loading failed - and allow reconfiguration
		OviseConfig.Write("ConfigurationDone",false);
		return false;
	}


    MainFrame* frame = new MainFrame(NULL);

    frame->Show();
	SetTopWindow(frame);
	if(!frame->InitOgre())
		return false;
	frame->InitSocketInterface();

	splash->Destroy();

    return true;
}

OViSEApplication::~OViSEApplication() { }
