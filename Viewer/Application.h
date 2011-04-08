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

class OViSEApplication : public wxApp
{
private:
	bool    SetupBasicConfiguration();
	bool mForceConfig;

public:
	virtual bool OnInit();
	virtual void OnInitCmdLine( wxCmdLineParser& Parser );
	virtual bool OnCmdLineParsed( wxCmdLineParser& Parser );
	virtual ~OViSEApplication();
};

DECLARE_APP( OViSEApplication );

#endif // APPLICATION_H
