#pragma once
#ifndef __PrototypeManagementDialog__
#define __PrototypeManagementDialog__

/**
@file
Subclass of AttachSceneDialog, which is generated by wxFormBuilder.
*/

// Include WX
#include <wx/string.h>
#include <wx/aui/aui.h>
#include <wx/propgrid/propgrid.h>
#include <wx/arrstr.h>
#include <wx/valtext.h>
#include <wx/filename.h>
#include <wx/filedlg.h>
#include <wx/config.h>

// Solution's includes
#include "MainFrameBase.h"

#include "../OViSEAux/StringConverter.h"
#include "../OViSE/SelectionManager.h"
#include "DotSceneManager.h"

enum
{
	PROTOPGID = wxID_HIGHEST + 4
};

/** Implementing PrototypeManagementDialog */
class PrototypeManagementDialog : public _PrototypeManagementDialog
{
private:
	bool mValid;
	wxString mResultingUniqueNameOfPrototype;

	QualifiedName qSelectedPrototype;

	void setPrototypeProperties(QualifiedName qPrototype);
	void clearPrototypeProperties();

protected:
	wxPropertyGrid* mPrototypeProperties;

	//OViSESceneHandling* mSceneHdlr;
	OViSEDotSceneManager* mDotSceneMgr;

	void setupPrototypeProperties();

	// Eventhandlers
	virtual void OnClickRemove( wxCommandEvent& event );
	virtual void OnClickImport( wxCommandEvent& event );
	virtual void OnClickExport( wxCommandEvent& event );
	virtual void OnClickBuild( wxCommandEvent& event );
	virtual void OnClickAttach( wxCommandEvent& event );
	virtual void OnClickClose( wxCommandEvent& event );
	virtual void OnCloseDialog( wxCloseEvent& event );
	virtual void OnProtoTypeListSelect( wxCommandEvent& event );
	virtual void OnPropertyChange(wxPropertyGridEvent& event);
	/*
	void OnClickCancel( wxCommandEvent& event );
	void OnClickOk( wxCommandEvent& event );
	*/
	
public:
	/** Constructor */
	PrototypeManagementDialog( wxWindow* parent, OViSEDotSceneManager* DotSceneMgr );

	/*
	void SetAvailablePrototypes(wxArrayString ListOfAvailablePrototypes);
	wxString GetResultingUniqueNameOfPrototype();
	*/
};

#endif // __PrototypeManagementDialog__
