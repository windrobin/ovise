/***************************************************************
 * Name:      Application.h
 * Purpose:   Defines Application Class
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include <wx/app.h>
#include <wx/cmdline.h>

/**
  Main application class of the OViSE Viewer.
  This class is the backbone of the OViSE Viewer as required by
  wxWidgets.
*/
class OViSEApplication : public wxApp
{
private:
	bool SetupBasicConfiguration();
	bool mForceConfig;

public:
	/// Stuff to be done on initialization.
	virtual bool OnInit();
	/// Command line parsing
	virtual void OnInitCmdLine( wxCmdLineParser& Parser );
	/// Stuff to do when the command line has been parsed.
	virtual bool OnCmdLineParsed( wxCmdLineParser& Parser );
	virtual ~OViSEApplication();
};

DECLARE_APP( OViSEApplication );

#endif // APPLICATION_H
