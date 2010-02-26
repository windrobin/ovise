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

IMPLEMENT_APP(OViSEApplication);

bool OViSEApplication::OnInit()
{
	wxImage::AddHandler( new wxPNGHandler );
	wxBitmap bitmap;
	wxSplashScreen *splash = NULL;
	if (bitmap.LoadFile(wxT("../OViSESplash.png"), wxBITMAP_TYPE_PNG))
	{
		splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT, 0, NULL, -1, wxDefaultPosition,
			wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP);
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

OViSEApplication::~OViSEApplication()
{
}
