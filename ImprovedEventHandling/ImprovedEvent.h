/********************************************************************************
 * Name:      ImprovedEvent.h													*
 * Purpose:   Class "ImprovedEvent" is designed as a wxCommandEvent, which		*
 *			  carry additional data. Especially QualifiedNames. The idea behind	*
 *			  to beliver information about a special source or context,			*
 *			  described by QualifiedNames. That's a great advantage for Ogre3D,	*
 *			  handled by OgreMediator.											*
 * Created:   2009-12-18														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Include WX
#include <wx/event.h>
#include <wx/variant.h>

// Solution's includes
#include "../QualifiedNames/QualifiedNameCollection.h"

class ImprovedEvent :
	public wxCommandEvent
{
private:
	QualifiedName	qContextInfo;
	wxVariant		vContextData;

public:
	ImprovedEvent(wxEventType CommandType, int ID);
	ImprovedEvent(const ImprovedEvent& EventToCopy);
	~ImprovedEvent(void);

	wxEvent* Clone() const;

	void SetContextInfo(QualifiedName qContextInfo);
	QualifiedName GetContextInfo() const;

	void SetContextData(wxVariant vContextData);
	wxVariant GetContextData() const;
};

// Simplify macros
typedef void (wxEvtHandler::*ImprovedEventFunction)(ImprovedEvent &);

// Prepare use of event
#define ImprovedEventHandler(func)\
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ImprovedEventFunction, &func)


// Attention: code-conservation // Not neccessary // See: http://wiki.wxwidgets.org/Custom_Events, creating a custom cvent, method 4
/* 
#define EVT_SCENENODE_ROTATION(id, fn)\
	DECLARE_EVENT_TABLE_ENTRY( OgreChangedEvent, id, wxID_ANY,\
	(wxObjectEventFunction)(wxEventFunction)\
	(wxCommandEventFunction) wxStaticCastEvent( OgreChangedEventFunction, &fn ),\
	(wxObject*) NULL ),
*/