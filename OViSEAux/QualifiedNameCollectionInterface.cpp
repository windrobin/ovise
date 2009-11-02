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