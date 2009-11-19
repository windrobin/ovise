/********************************************************************************
 * Name:      QualifiedNameRegister.h											*
 * Purpose:   Code describes a singleton class holding strings as parts of 		*
 *			  qualified names. These parts are: native name, generic name and 	*
 *			  genic hint.The generic name is unique and acts as hash-key.		*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Include WX
#include <wx/string.h>
#include <wx/hashmap.h>
#include <wx/arrstr.h> 

// WX container declarations (Attention: use of makros)
WX_DECLARE_STRING_HASH_MAP(wxString, HashMap_wxString);

class QualifiedNameRegister
{
private:
	// De- & Constructors
	QualifiedNameRegister(void);

	// Singleton
	static QualifiedNameRegister* instance;

	// Attributes // HashMaps allow access in O(1)
	wxArrayString AllocatedGenericNames;
	HashMap_wxString StoredNativeNames;
	HashMap_wxString StoredGenericHints;

public:
	// De- & Constructors
	~QualifiedNameRegister(void);

	// Singleton
	static QualifiedNameRegister* GetSingletonPtr();

	// Methods, generic name
	wxString	AllocateQualifiedName(wxString NativeName, wxString GenericHint);
	bool		DeallocateQualifiedName(wxString GenericName);	
};
