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


IMPLEMENT_APP( OViSEApplication );

/** Setup the path configuration, if it does not exist yet.
        \returns false if the user canceled the process, true otherwise.
        \todo Rename? The name is somewhat misleading.
 */
bool OViSEApplication::SetupBasicConfiguration()
{
	// FIXME: move this info out of the root config?

	// Get config
	wxConfig OviseConfig( "OViSE" );

	// Configuration already done?
	if ( OviseConfig.ReadBool( "ConfigurationDone",
		     false ) && !mForceConfig )
		return true;

	// The names of the tags in the config
	const wxString PluginPathKey = wxT( "PluginDirStr" );
	const wxString MediaPathKey = wxT( "MediaDirStr" );

	wxString MediaDir =  OviseConfig.Read( MediaPathKey, "Media" );
	wxString PluginDir =  OviseConfig.Read( PluginPathKey, "Plugins" );

	// Run the dialog..
	OViSEPathConfigDialog ConfigDialog( PluginDir, MediaDir, NULL );

	switch( ConfigDialog.ShowModal() )
	{
	case wxID_OK:
		// Save if the user wants this
		std::cout << "PluginPath: " << ConfigDialog.GetPluginPath() <<
		std::endl;
		std::cout << "MediaPath: " << ConfigDialog.GetMediaPath() <<
		std::endl;
		OviseConfig.Write( PluginPathKey, ConfigDialog.GetPluginPath() );
		OviseConfig.Write( MediaPathKey, ConfigDialog.GetMediaPath() );

		OviseConfig.Write( "ConfigurationDone", true );
		std::cout << "Configuration written." << std::endl;
		return true;

	default:
	case wxID_CANCEL:
		// Do not save
		return false;
	}
}

bool OViSEApplication::OnInit()
{
	if( !wxApp::OnInit() )
		return false;

	// Bump out if configuration fails
	if( !SetupBasicConfiguration() )
		return false;

	// Retrieve the media path
	wxConfig OviseConfig( "OViSE" );
	wxString MediaPath = OviseConfig.Read( wxT( "MediaDirStr" ) );
	wxString PluginPath = OviseConfig.Read( wxT( "PluginDirStr" ) );

        wxInitAllImageHandlers();
        wxBitmap        Bitmap;
	wxSplashScreen* Splash = NULL;

	// Check whether the the Splash image can be loaded
	// This works also as a test to check whether path configuration was successful
        if( Bitmap.LoadFile( MediaPath + wxT( "/Splash/OViSESplash.png" ),
                    wxBITMAP_TYPE_PNG ) )
	{
#ifndef _DEBUG
		Splash = new wxSplashScreen( Bitmap,
			wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_NO_TIMEOUT,
			0,
			NULL,
			-1,
			wxDefaultPosition,
			wxDefaultSize,
			wxBORDER_NONE | wxSTAY_ON_TOP );
#endif
	}
	else
	{
		// Exit gracefully if loading failed - and allow reconfiguration
		OviseConfig.Write( "ConfigurationDone", false );
		return false;
        }

	MainFrame* frame = new MainFrame( MediaPath, PluginPath, NULL );

	frame->Show();
	SetTopWindow( frame );


	// Remove and delete the spash window
	if ( Splash != 0 )
                Splash->Destroy();

	return true;
}

void OViSEApplication::OnInitCmdLine( wxCmdLineParser& Parser )
{
	Parser.AddSwitch( wxT( "h" ), wxT( "help" ),
                wxT("displays help on the command line parameters" ), wxCMD_LINE_OPTION_HELP );
        Parser.AddSwitch( wxT( "c" ), wxT( "configure" ),
                wxT( "forces configuration dialog" ) );
	// must refuse '/' as parameter starter or cannot use "/path" style paths
	Parser.SetSwitchChars( wxT( "-" ) );
}

bool OViSEApplication::OnCmdLineParsed( wxCmdLineParser& Parser )
{
	mForceConfig = Parser.Found( wxT( "c" ) );

	return true;
}

OViSEApplication::~OViSEApplication()
{}
