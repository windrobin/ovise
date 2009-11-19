/********************************************************************************
 * Name:      QualifiedNameCollection.cpp								*
 * Purpose:   Code implements a container for QualifiedName-objects and a		*
 *			  interface, describing operations on that collection				*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../QualifiedNames/QualifiedNameCollection.h"

// De- & Constructors
QualifiedNameCollection::QualifiedNameCollection(void) { this->mQNHashMap = QualifiedNameHashMap(); }
QualifiedNameCollection::QualifiedNameCollection(const QualifiedNameCollection& ToCopy) { this->mQNHashMap = ToCopy.mQNHashMap; }
QualifiedNameCollection::~QualifiedNameCollection(void) { this->Clear(); }
// Management, basic
unsigned long QualifiedNameCollection::Count() { return this->mQNHashMap.size(); }
void QualifiedNameCollection::Clear() { this->mQNHashMap.clear(); }
bool QualifiedNameCollection::IsEmpty() { return this->mQNHashMap.empty(); }
bool QualifiedNameCollection::Contains(QualifiedName qName)
{
	if (!qName.IsValid()) return false;
	if (this->mQNHashMap.count(qName.UniqueName()) == 0) return false;
	else return true;
}
bool QualifiedNameCollection::Add(QualifiedName qName)
{
	if (!qName.IsValid()) return false;
	if (!this->Contains(qName))
	{
		this->mQNHashMap[qName.UniqueName()] = qName;
		return true;
	}
	else return false;
}
bool QualifiedNameCollection::Remove(QualifiedName qName)
{
	if (!qName.IsValid()) return false;
	if (this->Contains(qName))
	{
		this->mQNHashMap.erase(qName.UniqueName());
		return true;
	}
	else return false;
}
QualifiedNameCollection QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(wxArrayString GenericNames)
{
	QualifiedNameCollection QNames;
	QNames.Clear();

	if (!GenericNames.IsEmpty())
	{
		for(unsigned long IT = 0; IT < GenericNames.GetCount(); IT++)
		{
			QualifiedName qName = QualifiedName::GetQualifiedNameByGeneric(GenericNames[IT]);
			QNames.Add(qName);
		}
	}

	return QNames;
}
QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameByGeneric(wxString GenericName)
{
	wxArrayString GenericNames;
	GenericNames.Add(GenericName);
	return QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameByNative(wxString NativeName)
{
	wxArrayString GenericNames = QualifiedNameManager::GetSingletonPtr()->GetGenericByNative(NativeName);
	return QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameByHint(wxString GenericHint)
{
	wxArrayString GenericNames = QualifiedNameManager::GetSingletonPtr()->GetGenericByHint(GenericHint);
	return QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(GenericNames);
}
QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameBySubString(wxString SubString)
{
	return QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(QualifiedNameManager::GetSingletonPtr()->GetGenericBySubString(SubString));
}
QualifiedNameCollection QualifiedNameCollection::GetQualifiedNameByUnique(wxString UniqueName)
{
	QualifiedNameCollection QNames;
	QNames.Add(QualifiedName::GetQualifiedNameByUnique(UniqueName));
	return QNames;
}
QualifiedNameCollection QualifiedNameCollection::GetAllQualifiedNames()
{
	return QualifiedNameCollection::CreateQualifiedNameCollectionFromGenericNames(QualifiedNameManager::GetSingletonPtr()->GetGenericNames());
}
bool QualifiedNameCollection::HasQualifiedNameWithGeneric(wxString GenericName) { return QualifiedName::HasQualifiedNameWithGeneric(GenericName); }
bool QualifiedNameCollection::HasQualifiedNameWithNative(wxString NativeName)
{
	if (QualifiedNameManager::GetSingletonPtr()->GetGenericByNative(NativeName).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollection::HasQualifiedNameWithHint(wxString GenericHint)
{
	if (QualifiedNameManager::GetSingletonPtr()->GetGenericByHint(GenericHint).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollection::HasQualifiedNameWithSubString(wxString SubString)
{
	if (QualifiedNameManager::GetSingletonPtr()->GetGenericBySubString(SubString).GetCount() > 0) return true;
	else return false;
}
bool QualifiedNameCollection::HasQualifiedNameWithUnique(wxString UniqueName) { return QualifiedName::HasQualifiedNameWithUnique(UniqueName); }
QualifiedNameCollection QualifiedNameCollection::CollectionUnion(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	if (!QCollection_1.IsEmpty())
	{
		for (QualifiedNameHashMap::iterator IT = QCollection_1.mQNHashMap.begin(); IT != QCollection_1.mQNHashMap.end(); IT++)
		{
			Result.Add(IT->second);
		}
	}

	if (!QCollection_2.IsEmpty())
	{
		for (QualifiedNameHashMap::iterator IT = QCollection_2.mQNHashMap.begin(); IT != QCollection_2.mQNHashMap.end(); IT++)
		{
			if (!Result.Contains(IT->second)) Result.Add(IT->second);
		}
	}

	return Result;
}
QualifiedNameCollection QualifiedNameCollection::CollectionIntersection(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	if ((!QCollection_1.IsEmpty()) || (!QCollection_2.IsEmpty()))
	{
		for (QualifiedNameHashMap::iterator IT = QCollection_1.mQNHashMap.begin(); IT != QCollection_1.mQNHashMap.end(); IT++)
		{
			if (QCollection_2.Contains(IT->second)) Result.Add(IT->second);
		}
	}

	return Result;
}
QualifiedNameCollection QualifiedNameCollection::CollectionDifference(QualifiedNameCollection& Minuend, QualifiedNameCollection& Subtrahend)
{
	QualifiedNameCollection Difference;

	if (Subtrahend.IsEmpty())
	{
		Difference = Minuend;
		return Difference;
	}
	if (Minuend.IsEmpty())
	{
		return Difference;
	}

	for (QualifiedNameHashMap::iterator IT = Minuend.mQNHashMap.begin(); IT != Minuend.mQNHashMap.end(); IT++)
	{
		if (!Subtrahend.Contains(IT->second)) Difference.Add(IT->second);
	}

	return Difference;
}
QualifiedNameCollection QualifiedNameCollection::CollectionSymmetricDifference(QualifiedNameCollection& QCollection_1, QualifiedNameCollection& QCollection_2)
{
	QualifiedNameCollection Result;

	Result = QualifiedNameCollection::CollectionUnion(
		QualifiedNameCollection::CollectionDifference(QCollection_1, QCollection_2),
		QualifiedNameCollection::CollectionDifference(QCollection_2, QCollection_1));

	return Result;
}