/********************************************************************************
 * Name:      QualifiedName.h													*
 * Purpose:   Code describes a class for qualified names, composed of a	native	*
 *			  and a generic part. It ensures a unique instance for a given		*
 *			  native name, divided from generic part and compareable.			*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-10-29														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Include WX
#include <wx/hashmap.h>
#include <wx/dynarray.h>

// Solution's includes
#include "../OViSEAux/StringConverter.h"

class QualifiedName : public std::pair<wxString,wxString>
{
public:
	// WX container declarations (Attention: use of makros)
	WX_DECLARE_STRING_HASH_MAP(wxString, HashMap_wxString);
	WX_DECLARE_STRING_HASH_MAP(QualifiedName, HashMap_QualifiedName);
	WX_DECLARE_OBJARRAY(QualifiedName, Array_QualifiedName);

private:
	// Attributes, static
	// HashMaps allow access in O(1)
	static HashMap_wxString sUsedGenericNames;
	static HashMap_wxString sGenericHints;

	// Attributes, additional data
	// String will be part of generic name. Users can add an additional part to generic name.
	// For example, if users want to differentiate between special classifications.
	private wxString mGenericHint;

	// Methods, managing generic name
	wxString AllocateGenericName();
	bool DeallocateGenericName();

	// Methods, additional access
	// ...

	// De- & Constructor, standard ctor only for returnvalues
	QualifiedName();

public:
	// De- & Constructors
	QualifiedName(wxString NativeName);
	QualifiedName(wxString NativeName, wxString GenericHint);
	QualifiedName(const QualifiedName& ToCopy);
	~QualifiedName(void);

	// Methods, management
	bool IsValid();
	bool Destroy();

	// Methods, access to names
	wxString GetGenericHint();

	// If you don't know what first and second is: use this human-readable methods ;-)
	wxString GenericName();
	wxString NativeName();

	// Get the unique combination of generic and native name. Format is this: "<native name>_<generic hint>_<generic tail>"
	wxString UniqueName();

	// Static Methods
	// Get a QualifiedName by generic name (that's unique, so only one QualifiedName is returned)
	static Array_QualifiedName GetQualifiedNameByGenericName(wxString GenericName);

	// Get QualifiedName by native name (returns a wxArray of QualifiedNames)
	static Array_QualifiedName GetQualifiedNameByNativeName(wxString NativeName);

	// Get QualifiedName by generic hint (returns a wxArray of QualifiedNames)
	static Array_QualifiedName GetQualifiedNameByGenericHint(wxString GenericHint);

	// Get QualifiedName by hint (returns a wxArray of QualifiedNames)
	static Array_QualifiedName GetQualifiedNameByHint(wxString Hint);

	// Get all QualifiedNames (returns a wxArray of QualifiedNames)
	static Array_QualifiedName GetAllQualifiedNames();

	// Check, if a QualifiedName with a given generic name exists.
	static bool HasQualifiedNameWithGenericName(wxString GenericName);

	// Check, if one or more QualifiedName with a given native name exists...
	static bool HasQualifiedNameWithNativeName(wxString NativeName);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithGenericHint(wxString GenericHint);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithHint(wxString Hint);
};
