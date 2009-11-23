/********************************************************************************
 * Name:      QualifiedNameCollection.h											*
 * Purpose:   Code describes a container for QualifiedName-objects and			*
 *			  operations on that collection. Addition math. set-operations,		*
 *			  whose imporve handlich with collections.							*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

// Solution's includes
#include "../QualifiedNames/QualifiedName.h"

class QualifiedNameCollection
{
private:
	//static QualifiedNameCollection CreateQualifiedNameCollectionFromGenericNames(wxArrayString GenericNames);
	QualifiedNameHashMap mQNHashMap;
	QualifiedNameArray mQNArray;
	bool mFlag_QNHashMap_modified;

public:
	// De- & Constructors
	QualifiedNameCollection(void);
	QualifiedNameCollection(const QualifiedNameCollection& ToCopy);
	~QualifiedNameCollection(void);

	// Management, basic
	unsigned long	Count();
	void			Clear();
	bool			IsEmpty();
	
	// Management, basic has, add & remove of QualifiedName
	bool			Contains(QualifiedName qName);
	bool			Add(QualifiedName qName);
	bool			Remove(QualifiedName qName);
	
	// Methods, indexed access
	QualifiedName	operator[](unsigned long Index);

	// Static Methods
	// Get QualifiedNameCollection by wxArray of generic names
	static QualifiedNameCollection QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(wxArrayString GenericNames);

	// Get QualifiedName by generic name (returns a collection of QualifiedNames, which contains only one QualifiedName)
	static QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameByGeneric(wxString GenericName);

	// Get QualifiedName by native name (returns a collection of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameByNative(wxString NativeName);

	// Get QualifiedName by hint ((returns a collection of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameByHint(wxString GenericHint);

	// Get QualifiedName by substring (returns a collection of QualifiedNames)
	static QualifiedNameCollection GetQualifiedNameBySubString(wxString SubString);

	// Get QualifiedName by unique (returns a collection of QualifiedNames, which contains only one QualifiedName)
	static QualifiedNameCollection GetQualifiedNameByUnique(wxString UniqueName);

	// Get all QualifiedNames (returns a collection of QualifiedNames)
	static QualifiedNameCollection GetAllQualifiedNames();

	// Check, if a QualifiedName with a given generic name exists.
	static bool HasQualifiedNameWithGeneric(wxString GenericName);

	// Check, if one or more QualifiedName with a given native name exists...
	static bool HasQualifiedNameWithNative(wxString NativeName);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithHint(wxString GenericHint);

	// Check, if one or more QualifiedName contain a given generic hint exists...
	static bool HasQualifiedNameWithSubString(wxString SubString);

	// Check, if a QualifiedName exists, equal to given unique name...
	static bool HasQualifiedNameWithUnique(wxString UniqueName);

	// Methods, implement mathematical operations of set-theory.
	// Actually these methods are expencive ( from O (m) to O(n+m) up to O(n*m) )
	// When the QualifiedNameCollection-class must be upgraded with a additional wxHashMap, to limit complexity to O(n)
	static QualifiedNameCollection CollectionUnion(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2);
	static QualifiedNameCollection CollectionIntersection(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2);
	static QualifiedNameCollection CollectionDifference(QualifiedNameCollection& Minuend, QualifiedNameCollection& Subtrahend);
	static QualifiedNameCollection CollectionSymmetricDifference(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2);

	static QualifiedNameArray ArrayToHashMap(QualifiedNameHashMap QNameHashMap);
};
