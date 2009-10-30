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

#include "QualifiedName.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfDirectories); // Attention: using macros!

wxString QualifiedName::AllocateGenericName()
{
	// Prepare basic generic name, including hint
	wxString BasicGenericName = this->mGenericHint;
	BasicGenericName << ToWxString("_");

	// Search for not used generic name
	int Counter = 0;
	wxString FinalGenericName;
	
	do
	{
		FinalGenericName.Clear();
		FinalGenericName << BasicGenericName << wxString::Format(wxT("%i"), Counter);
		Counter++;
	}
	while(QualifiedName::sUsedGenericNames.count(FinalGenericName) != 0);

	// Found unique generic name
	this->first = FinalGenericName;

	// Store unique generic name as key. Using native name as value. So reverse tracking is possible.
	QualifiedName::sUsedGenericNames[this->first] = this->second;
	QualifiedName::sGenericHints[this->first] = this->mGenericHint;

	return FinalGenericName;
}

bool QualifiedName::DeallocateGenericName()
{
	// Generic name is not allocated. Error.
	if (QualifiedName::sUsedGenericNames.count(this->first) == 0) return false;

	// Generic name is allocated. Delete it!
	QualifiedName::sUsedGenericNames.erase(this->first);
	QualifiedName::sGenericHints.erase(this->first);
	return true;
}

QualifiedName::QualifiedName(wxString NativeName) : QualifiedName(NativeName, ToWxString("") { }
QualifiedName::QualifiedName(wxString NativeName, wxString GenericHint)
{
	// Set native name
	this->second = NativeName;

	// Store hint
	this->mGenericHint = GenericHint;

	// Allocate and implicid set generic name
	this->AllocateGenericName(GenericHint);
}

QualifiedName::QualifiedName(const QualifiedName& ToCopy)
{
	this->first = ToCopy.first;
	this->second = ToCopy.second;
	this->mGenericHint = ToCopy.mGenericHint();
}
QualifiedName::~QualifiedName(void) { this->DeallocateGenericName(); }
bool QualifiedName::IsValid() { return this->HasQualifiedNameWithGenericName(this->first); }
bool QualifiedName::Destroy()
{
	// Check, if QName exists
	if (!this->IsValid())
	{
		return false;
	}
	else
	{
		// Deallocate itself
		this->DeallocateGenericName();
		return true;
	}
}
void QualifiedName::GetGenericHint() { return this->mGenericHint; }
wxString QualifiedName::GenericName() { return this->first; }
wxString QualifiedName::NativeName() { return this->second; }
wxString QualifiedName::UniqueName()
{
	wxString QName;
	QName.clear();
	QName << this->second;
	QName << ToWxString("_");
	QName << this->first;
	return QName;
}
static Array_QualifiedName QualifiedName::GetQualifiedNameByGenericName(wxString GenericName)
{
	Array_QualifiedName TempArray;
	TempArray.clear();

	if (QualifiedName::sUsedGenericNames.count(GenericName) == 1)
	{
		QualifiedName QName;
		QName.first = GenericName;
		QName.second = QualifiedName::sUsedGenericNames[GenericName];
		QName.mGenericHint = QualifiedName::sGenericHints[GenericName];

		TempArray.Add(QName);
	}

	return TempArray;
}
static Array_QualifiedName QualifiedName::GetQualifiedNameByNativeName(wxString NativeName)
{
	Array_QualifiedName TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedName::sUsedGenericNames.begin(); IT != QualifiedName::sUsedGenericNames.end(); IT++)
	{
		if (IT->second.IsSameAs(NativeName))
		{
			QualifiedName QName;
			QName.first = IT->first;
			QName.second = IT->second;
			QName.mGenericHint = QualifiedName::sGenericHints[IT->first];

			TempArray.Add(QName);
		}
	}
	
	return TempArray;
}
static Array_QualifiedName QualifiedName::GetQualifiedNameByGenericHint(wxString GenericHint)
{
	Array_QualifiedName TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedName::sUsedGenericNames.begin(); IT != QualifiedName::sUsedGenericNames.end(); IT++)
	{
		if (IT->first.Contains(GenericHint))
		{
			QualifiedName QName;
			QName.first = IT->first;
			QName.second = IT->second;
			QName.mGenericHint = QualifiedName::sGenericHints[IT->first];

			TempArray.Add(QName);
		}
	}
	
	return TempArray;
}
static Array_QualifiedName QualifiedName::GetQualifiedNameByHint(wxString Hint)
{
	Array_QualifiedName TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedName::sUsedGenericNames.begin(); IT != QualifiedName::sUsedGenericNames.end(); IT++)
	{
		QualifiedName QName;
		QName.first = IT->first;
		QName.second = IT->second;
		QName.mGenericHint = QualifiedName::sGenericHints[IT->first];

		if (QName.UniqueName().Contains(Hint)) TempArray.Add(QName);
	}
	
	return TempArray;
}
static Array_QualifiedName QualifiedName::GetAllQualifiedNames()
{
	Array_QualifiedName TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedName::sUsedGenericNames.begin(); IT != QualifiedName::sUsedGenericNames.end(); IT++)
	{
		QualifiedName QName;
		QName.first = IT->first;
		QName.second = IT->second;
		QName.mGenericHint = QualifiedName::sGenericHints[IT->first];

		TempArray.Add(QName);
	}
	
	return TempArray;
}
static bool QualifiedName::HasQualifiedNameWithGenericName(wxString GenericName)
{
	if (QualifiedName::GetQualifiedNameByGenericName(GenericName).Count > 0) return true;
	else return false;
}
static bool QualifiedName::HasQualifiedNameWithNativeName(wxString NativeName)
{
	if (QualifiedName::GetQualifiedNameByNativeName(GenericName).Count > 0) return true;
	else return false;
}
static bool QualifiedName::HasQualifiedNameWithGenericHint(wxString GenericHint)
{
	if (QualifiedName::GetQualifiedNameByGenericHint(GenericName).Count > 0) return true;
	else return false;
}
static bool QualifiedName::HasQualifiedNameWithHint(wxString Hint)
{
	if (QualifiedName::GetQualifiedNameByHint(GenericName).Count > 0) return true;
	else return false;
}