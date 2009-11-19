/********************************************************************************
 * Name:      QualifiedNameManager.h											*
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

class QualifiedNameManager
{
private:
	// De- & Constructors
	QualifiedNameManager(void);

	// Singleton
	static QualifiedNameManager* instance;

	// Attributes
	wxArrayString		AllocatedGenericNames;
	HashMap_wxString	StoredNativeNames;
	HashMap_wxString	StoredGenericHints;

public:
	// De- & Constructors
	~QualifiedNameManager(void);

	// Singleton
	static QualifiedNameManager* GetSingletonPtr();

	// Methods, de- & alloc of generic name
	wxString		AllocateGenericName(wxString NativeName, wxString GenericHint);
	bool			DeallocateGenericName(wxString GenericName);

	// Methods, get generic name
	bool			HasGeneric(wxString GenericName);			// Returns true, if generic name is valid.
	wxString		GetNativeByGeneric(wxString GenericName);	// Get native name by generic name. Returns an empty string, if generic name is not valid!
	wxString		GetHintByGeneric(wxString GenericName);		// Get generic hint by generic name. Returns an empty string, if generic name is not valid!
	wxArrayString	GetGenericByNative(wxString NativeName);	// Get generic names by native names (returns a wxStringArray of generic names)
	wxArrayString	GetGenericByHint(wxString GenericHint);		// Get generic names by generic hint (returns a wxStringArray of generic names)
	wxArrayString	GetGenericBySubString(wxString SubString);	// Get generic names by substring (returns a wxStringArray of generic names)
	wxArrayString	GetGenericNames();							// Get all generic names (returns a wxStringArray of generic names)
	wxString		GetGenericByUnique(wxString UniqueName);	// Get generic name by unique name with a constructive technique. (If it is not a unique name relating to definition, an empty wxString is returned)

};