/********************************************************************************
 * Name:      QualifiedName.h													*
 * Purpose:   Code describes a class for qualified names, composed of a	native	*
 *			  and a generic part. It ensures a unique instance for a given		*
 *			  native name, divided from generic part and compareable.			*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

// INTRODUCTION / FAQ:
// Q = Question, A = Answer, E = Example

// Q:	What is "native" or "native name"?
// A:	That's the "native" part of a QualifiedName. It's naturally given.
//		<native>
// E:	For example the name of a file.
//		MyFile.txt

// Q:	What is "hint" or "generic hint"?
// A:	The "hint" is a string, that will be part of the generic name. So you can mark
//		different classes of QualifiedNames in the string.
//		TIP: hint can be empty. That's doesn't matter.
//		<hint>
// E:	For example you choose "file" for as generic hint for files.
//		file

// Q:	What is "generic" or "generic name"?
// A:	That's the "not native" ( = not natural) part of a QualifiedName,
//		automatically generated when Create(...) calls AllocateGenericName().
//		The native name is extended with the generic part and so the code can
//		differentiate between those instances. For this the hint and a counter
//		is used.
//		_<hint>_<counter-value>
// E:	For example a file should be imported multible times. Together that looks like this:
//		_file_123

// Q:	What is "unique name"?
// A:	That's the combination of native name and generic name, which includes the genic hint.
//		<native>_<hint>_<counter-value>
// E:	For example the unique name of our file looks like this:
//		MyFile.txt_file_123  // That's really unique ;-)

// Q:	What is it about "SubSting"?
// A:	Methods, including "SubString" means, that a substring is searched in the ->unique name<-.
//		In contrast, you can use the "Hint" to search only for a substring in ->generic name<-

#pragma once

// Solution's includes
#include "../QualifiedNames/QualifiedNameManager.h"

class QualifiedName
{
private:
	// Attributes, data
	// String will be part of generic name. Users can add an additional part to generic name.
	// For example, if users want to differentiate between special classifications.
	wxString mGenericName;

public:
	// De- & Constructors, standard and copy ctor only for handling qualified names
	QualifiedName();
	QualifiedName(const QualifiedName& ToCopy);
	~QualifiedName(void);

	// Methods, management, static
	// Explicit static Create()- Constructors for clear management of qualified names
	static QualifiedName Create(wxString NativeName);
	static QualifiedName Create(wxString NativeName, wxString GenericHint);
	static bool Destroy(QualifiedName QName);
	static bool Destroy(wxString GenericName);

	// Methods, management
	bool Destroy();
	bool IsValid();

	// Methods, access to names // If you don't know what first and second is: use this human-readable methods ;-)
	wxString GenericHint();	// Get generic hint
	wxString GenericName(); // Get generic name. Format is like this: "_<generic hint>_<generic tail>"
	wxString NativeName();	// Get native name
	wxString UniqueName();	// Get the unique combination of generic and native name. Format is like this: "<native name>_<generic hint>_<generic tail>"

	// Methods, comparision
	bool Equals(QualifiedName QName);			// Check, if QualifiedName-objects are equal in native and generic part
	bool EqualsNative(QualifiedName QName);		// Check, if QualifiedName-objects are equal in native part
	bool EqualsGeneric(QualifiedName QName);	// Check, if QualifiedName-objects are equal in generic part
	bool EqualsHint(QualifiedName QName);		// Check, if QualifiedName-objects have same generic hint
	bool operator==(QualifiedName QName);		// Overload operator== , behavior like bool Equals(QualifiedName QName)
	bool operator!=(QualifiedName QName);		// Overload operator!= , behavior like NOT(bool Equals(QualifiedName QName))
	bool ContainsSubString(wxString SubString); // Check, if QualifiedName.Unique() contains substring

	// Methods, get, static
	static QualifiedName GetQualifiedNameByGeneric(wxString GenericName);	// Get QualifiedName by generic name
	static QualifiedName GetQualifiedNameByUnique(wxString UniqueName);		// Get QualifiedName by unique name

	// Methods, has, static
	static bool HasQualifiedNameWithGeneric(wxString GenericName);	// Get QualifiedName by generic name
	static bool HasQualifiedNameWithUnique(wxString UniqueName);		// Get QualifiedName by unique name
};

// Container declarations
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(QualifiedName, QualifiedNameArray);
WX_DECLARE_STRING_HASH_MAP(QualifiedName, QualifiedNameHashMap);
