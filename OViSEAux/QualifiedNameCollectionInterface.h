#pragma once

// Include WX
/********************************************************************************
 * Name:      QualifiedNameCollectionInterface.h								*
 * Purpose:   Code describes a container for QualifiedName-objects and a		*
 *			  interface, describing operations on that collection				*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include <wx/dynarray.h>
#include <wx/arrstr.h>

// Solution's includes
#include "../OViSEAux/QualifiedName.h"

WX_DECLARE_OBJARRAY(QualifiedName, QualifiedNameCollection);

class QualifiedNameCollectionInterface
{
private:
	QualifiedNameCollectionInterface(void);
	~QualifiedNameCollectionInterface(void);

	virtual void abstractDummy() = 0;

	static QualifiedNameCollection CreateQualifiedNameCollectionFromGenericNames(wxArrayString GenericNames);

public:
	// Static Methods
	// Get a QualifiedName by generic name (that's unique, so only one QualifiedName is returned)
	static QualifiedNameCollection GetQualifiedNameByGeneric(wxString GenericName);

	// Get QualifiedName by native name (returns a wxArray of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameByNative(wxString NativeName);

	// Get QualifiedName by generic hint (returns a wxArray of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameByHint(wxString GenericHint);

	// Get QualifiedName by hint (returns a wxArray of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameBySubString(wxString SubString);

	// Get all QualifiedNames (returns a wxArray of QualifiedNames)
	static QualifiedNameCollection GetAllQualifiedNames();

	// Check, if a QualifiedName with a given generic name exists.
	static bool HasQualifiedNameWithGeneric(wxString GenericName);

	// Check, if one or more QualifiedName with a given native name exists...
	static bool HasQualifiedNameWithNative(wxString NativeName);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithHint(wxString GenericHint);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithSubString(wxString SubString);
};
