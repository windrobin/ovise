/********************************************************************************
 * Name:      QualifiedNameCollectionInterface.cpp								*
 * Purpose:   Code implements a container for QualifiedName-objects and a		*
 *			  interface, describing operations on that collection				*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "QualifiedNameCollectionInterface.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(QualifiedNameCollection);

QualifiedNameCollectionInterface::QualifiedNameCollectionInterface(void) { }
QualifiedNameCollectionInterface::~QualifiedNameCollectionInterface(void) { }
QualifiedNameCollection QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(wxArrayString GenericNames)
{
	QualifiedNameCollection TempArray;
	TempArray.Clear();

	if (!GenericNames.IsEmpty())
	{
		for(unsigned long IT = 0; IT < GenericNames.GetCount(); IT++)
		{
			QualifiedName* pQName = QualifiedName::GetQualifiedNameByGeneric(GenericNames[IT]);
			if (pQName != 0) TempArray.Add(*pQName);
		}
	}

	return TempArray;
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetQualifiedNameByGeneric(wxString GenericName)
{
	wxArrayString GenericNames;
	GenericNames.Add(GenericName);

	return QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetQualifiedNameByNative(wxString NativeName)
{
	wxArrayString GenericNames = QualifiedName::GetGenericByNative(NativeName);
	return QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetQualifiedNameByHint(wxString GenericHint)
{
	wxArrayString GenericNames = QualifiedName::GetGenericByHint(GenericHint);
	return QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetQualifiedNameBySubString(wxString SubString)
{
	wxArrayString GenericNames = QualifiedName::GetGenericBySubString(SubString);
	return QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetQualifiedNameByUnique(wxString UniqueName)
{
	QualifiedNameCollection QNameMatch;
	QualifiedNameCollection QNColl = QualifiedNameCollectionInterface::GetQualifiedNameBySubString(UniqueName);
	if (QNColl.GetCount() > 0)
	{
		for(unsigned long IT = 0; IT < QNColl.GetCount(); IT++)
		{
			if (QNColl[IT].UniqueName().IsSameAs(UniqueName))
			{
				QNameMatch.Add(QNColl[IT]);
			}
		}
	}

	return QNameMatch;
}
QualifiedNameCollection QualifiedNameCollectionInterface::GetAllQualifiedNames()
{
	wxArrayString GenericNames = QualifiedName::GetGenericNames();
	return QualifiedNameCollectionInterface::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}

bool QualifiedNameCollectionInterface::HasQualifiedNameWithGeneric(wxString GenericName) { return QualifiedName::HasQualifiedNameWithGenericName(GenericName); }
bool QualifiedNameCollectionInterface::HasQualifiedNameWithNative(wxString NativeName)
{
	if (QualifiedName::GetGenericByNative(NativeName).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollectionInterface::HasQualifiedNameWithHint(wxString GenericHint)
{
	if (QualifiedName::GetGenericByHint(GenericHint).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollectionInterface::HasQualifiedNameWithSubString(wxString SubString)
{
	if (QualifiedName::GetGenericBySubString(SubString).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollectionInterface::CollectionContains(QualifiedNameCollection& QCollection, QualifiedName qName)
{
	if ( !qName.IsValid() ) return false;
	
	if ( QCollection.GetCount() > 0 )
	{
		for (unsigned long IT = 0; IT < QCollection.GetCount(); IT++)
		{
			if ( QCollection[IT] == qName ) return true;
		}
	}

	return false;
}
unsigned long QualifiedNameCollectionInterface::CollectionCount(QualifiedNameCollection& QCollection, QualifiedName qName)
{
	unsigned long ReturnValue = 0;

	if ( !qName.IsValid() ) return 0;
	
	if ( QCollection.GetCount() > 0 )
	{
		for (unsigned long IT = 0; IT < QCollection.GetCount(); IT++)
		{
			if ( QCollection[IT] == qName ) ReturnValue++;
		}
	}

	return ReturnValue;
}
bool QualifiedNameCollectionInterface::CollectionRemove(QualifiedNameCollection& QCollection, QualifiedName qName, bool OnlyOne)
{
	if ( !qName.IsValid() ) return false;
	
	if ( QCollection.GetCount() > 0 )
	{
		for (unsigned long IT = 0; IT < QCollection.GetCount(); IT++)
		{
			if ( QCollection[IT] == qName )
			{
				QCollection.RemoveAt(IT);
				if ( OnlyOne ) return true;
			}
		}
	}

	return true;
}
QualifiedNameCollection QualifiedNameCollectionInterface::CollectionUnion(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	if ( QCollection_1.GetCount() > 0 )
	{
		for (unsigned long IT = 0; IT < QCollection_1.GetCount(); IT++)
		{
			Result.Add(QCollection_1[IT]);
		}
	}

	if ( QCollection_2.GetCount() > 0 )
	{
		for (unsigned long IT = 0; IT < QCollection_2.GetCount(); IT++)
		{
			if ( !QualifiedNameCollectionInterface::CollectionContains(Result, QCollection_2[IT]) )
			{
				Result.Add(QCollection_2[IT]);
			}
		}
	}

	return Result;
}
QualifiedNameCollection QualifiedNameCollectionInterface::CollectionIntersection(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	if (( QCollection_1.GetCount() > 0 ) || ( QCollection_2.GetCount() > 0 ))
	{
		for (unsigned long IT = 0; IT < QCollection_1.GetCount(); IT++)
		{
			if (QualifiedNameCollectionInterface::CollectionContains(QCollection_2, QCollection_1[IT]))
			{
				Result.Add(QCollection_1[IT]);
			}
		}
	}

	return Result;
}
QualifiedNameCollection QualifiedNameCollectionInterface::CollectionDifference(QualifiedNameCollection& Minuend, QualifiedNameCollection& Subtrahend)
{
	QualifiedNameCollection Difference;

	if (( Subtrahend.GetCount() ==  0 ))
	{
		Difference = Minuend;
		return Difference;
	}
	if (( Minuend.GetCount() == 0 ))
	{
		return Difference;
	}

	for (unsigned long IT = 0; IT < Minuend.GetCount(); IT++)
	{
		if (!QualifiedNameCollectionInterface::CollectionContains(Subtrahend, Minuend[IT]))
		{
			Difference.Add(Minuend[IT]);
		}
	}

	return Difference;
}
QualifiedNameCollection QualifiedNameCollectionInterface::CollectionSymmetricDifference(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	if (( QCollection_1.GetCount() > 0 ) || ( QCollection_2.GetCount() > 0 ))
	{
		
		Result = QualifiedNameCollectionInterface::CollectionUnion(
			QualifiedNameCollectionInterface::CollectionDifference(QCollection_1, QCollection_2),
			QualifiedNameCollectionInterface::CollectionDifference(QCollection_2, QCollection_1));
	}

	return Result;
}