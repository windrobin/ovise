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
QualifiedNameCollection::QualifiedNameCollection(void)
{
	this->mQNHashMap = QualifiedNameHashMap();
	this->mFlag_QNHashMap_modified = false;
}
QualifiedNameCollection::QualifiedNameCollection(const QualifiedNameCollection& ToCopy)
{
	this->mQNHashMap = ToCopy.mQNHashMap;
	this->mFlag_QNHashMap_modified = true;
}
QualifiedNameCollection::~QualifiedNameCollection(void) { this->Clear(); }
// Management, basic
unsigned long QualifiedNameCollection::Count() { return this->mQNHashMap.size(); }
void QualifiedNameCollection::Clear()
{
	this->mQNHashMap.clear();
	this->mFlag_QNHashMap_modified = true;
}
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
		this->mFlag_QNHashMap_modified = true;
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
		this->mFlag_QNHashMap_modified = true;
		return true;
	}
	else return false;
}
QualifiedName QualifiedNameCollection::operator[](unsigned long Index)
{
	if (this->mFlag_QNHashMap_modified)
	{
		this->mQNArray.Clear();
		this->mQNArray = QualifiedNameCollection::HashMapToArray(this->mQNHashMap);
		this->mFlag_QNHashMap_modified = false;
	}
	
	return this->mQNArray[Index];
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
  QualifiedNameCollection Q1 = QualifiedNameCollection::CollectionDifference(QCollection_1, QCollection_2);
  QualifiedNameCollection Q2 = QualifiedNameCollection::CollectionDifference(QCollection_2, QCollection_1);

  Result = QualifiedNameCollection::CollectionUnion(Q1, Q2);

	return Result;
}

QualifiedNameArray QualifiedNameCollection::HashMapToArray(QualifiedNameHashMap QNameHashMap)
{
	QualifiedNameArray QNameArray;

	if (QNameHashMap.size() > 0)
	{
		for (QualifiedNameHashMap::iterator IT = QNameHashMap.begin(); IT != QNameHashMap.end(); IT++)
		{
			QualifiedName qName = IT->second;
			QNameArray.Add(qName);
		}
	}

	return QNameArray;
}
