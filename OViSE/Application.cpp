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

void OViSEApplication::SetupBasicConfiguration()
{
	// Get config
	wxConfig *OviseConfig = new wxConfig();

	// Configuration already done?
	bool ConfigurationDone = OviseConfig->ReadBool("ConfigurationDone", false);

	// If not, get working-directory and open PathConfigDialog...
	if (!ConfigurationDone)
	{
		ConfigurationDone = true;
		OviseConfig->Write("ConfigurationDone", ConfigurationDone);

		// Get working-directory...
		wxString WorkingDirStr = wxFileName::GetCwd();
		wxFileName WorkingDir = wxFileName(WorkingDirStr);
		OviseConfig->Write("WorkingDir", WorkingDirStr);

		// Look for base-path...
		wxString ParentDirStr = WorkingDir.GetPath();
		wxFileName ParentDir = wxFileName(ParentDirStr);
		wxString DirectoryStr = ParentDir.GetName();

		while(!(DirectoryStr.IsSameAs("ovise", true) || DirectoryStr.IsSameAs("", true)))
		{
			ParentDirStr = ParentDir.GetPath();
			ParentDir = wxFileName(ParentDirStr);
			DirectoryStr = ParentDir.GetName();
		}

		// Create base- and media-path
		wxString BaseDirStr, MediaDirStr;
		if(DirectoryStr.IsSameAs("ovise", true))
		{
			BaseDirStr = ParentDirStr;
			MediaDirStr = ParentDir.GetFullPath();
			MediaDirStr.Append(wxFileName::GetPathSeparator());
			MediaDirStr.Append("Media");
		}
		else
		{
			BaseDirStr = WorkingDirStr;
			MediaDirStr = WorkingDirStr;
		}

		OviseConfig->Write("BaseDirStr", BaseDirStr);
		OviseConfig->Write("MediaDirStr", MediaDirStr);

		OViSEPathConfigDialog* PCDlg = new OViSEPathConfigDialog(WorkingDirStr, BaseDirStr, MediaDirStr, NULL);
		PCDlg->ShowModal();
		
		switch(PCDlg->GetReturnCode())
		{
			case wxID_SAVE:
				OviseConfig->Write("BaseDirStr", BaseDirStr);
				OviseConfig->Write("MediaDirStr", MediaDirStr);
				break;
			case wxID_CANCEL:
				break;
			default:
				break;
		}
	}

	delete OviseConfig;
}

bool OViSEApplication::OnInit()
{
	this->SetupBasicConfiguration();

	wxConfig *OviseConfig = new wxConfig();

	wxString MediaPath;
	OviseConfig->Read("MediaDirStr", &MediaPath);

	wxImage::AddHandler( new wxPNGHandler );
	wxBitmap bitmap;
	wxSplashScreen *splash = NULL;

	if (bitmap.LoadFile(MediaPath + wxT("/Splash/OViSESplash.png"), wxBITMAP_TYPE_PNG))
	{
		splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT, 0, NULL, -1, wxDefaultPosition,
			wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP);
	}

	delete OviseConfig;

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
