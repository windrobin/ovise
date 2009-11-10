/********************************************************************************
 * Name:      QualifiedName.cpp													*
 * Purpose:   Code implements a class for qualified names, composed of a native	*
 *			  and a generic part. It ensures a unique instance for a given		*
 *			  native name, divided from generic part and compareable.			*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../OViSEAux/QualifiedName.h"

wxString QualifiedName::AllocateGenericName()
{
	// Prepare basic generic name, including hint
	wxString BasicGenericName = this->mGenericHint;
	BasicGenericName << ToWxString("_");

	// Search for not used generic name
	unsigned long Counter = 0;
	wxString FinalGenericName;

	do
	{
		if (Counter > 4000000000)
		{
			// When ever 4.000.000.000 generic names are used: modifiy generic hint in a way,
			// that allows searching final QualifiedName by hint sucessfully - and reset counter.
			Counter = 0;
			BasicGenericName << this->mGenericHint;
			this->mGenericHint = BasicGenericName;
			BasicGenericName << ToWxString("_");
		}
		FinalGenericName.Clear();
		FinalGenericName << BasicGenericName << wxString::Format(wxT("%i"), Counter);
		Counter++;
	}
	while(QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.count(FinalGenericName) != 0);

	// Found unique generic name
	this->mGenericName = FinalGenericName;

	// Store unique generic name as key. Using native name as value. So reverse tracking is possible.
	QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames[this->mGenericName] = this->mNativeName;
	QualifiedNameRegister::GetSingletonPtr()->StoredGenericHints[this->mGenericName] = this->mGenericHint;

	return FinalGenericName;
}

bool QualifiedName::DeallocateGenericName()
{
	// Generic name is not allocated. Error.
	if (!this->IsValid()) return false;

	// Generic name is allocated. Delete it!
	QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.erase(this->mGenericName);
	QualifiedNameRegister::GetSingletonPtr()->StoredGenericHints.erase(this->mGenericName);
	return true;
}

QualifiedName::QualifiedName() { }
QualifiedName::QualifiedName(const QualifiedName& ToCopy)
{
	this->mGenericName = ToCopy.mGenericName;
	this->mNativeName = ToCopy.mNativeName;
	this->mGenericHint = ToCopy.mGenericHint;
}
QualifiedName::~QualifiedName(void) { }
QualifiedName QualifiedName::Create(wxString NativeName) { return QualifiedName::Create(NativeName, ToWxString("")); }
QualifiedName QualifiedName::Create(wxString NativeName, wxString GenericHint)
{
	// Create empty QName
	QualifiedName QName;

	// Set native name
	QName.mNativeName = NativeName;

	// Store hint
	QName.mGenericHint = GenericHint;

	// Allocate and implicid set generic name
	QName.AllocateGenericName();

	return QName;
}
bool QualifiedName::Destroy(QualifiedName QName) { return QName.DeallocateGenericName(); }
bool QualifiedName::Destroy(wxString GenericName)
{
	QualifiedName* pQName = QualifiedName::GetQualifiedNameByGeneric(GenericName);
	
	if (pQName == 0) return false;
	else return QualifiedName::Destroy(*pQName);
}
bool QualifiedName::Destroy() { return QualifiedName::Destroy(*this); }
bool QualifiedName::IsValid() { return QualifiedName::HasQualifiedNameWithGenericName(this->mGenericName); }
wxString QualifiedName::GenericHint() { return this->mGenericHint; }
wxString QualifiedName::GenericName() { return this->mGenericName; }
wxString QualifiedName::NativeName() { return this->mNativeName; }
wxString QualifiedName::UniqueName()
{
	wxString QName;
	QName.clear();
	QName << this->mNativeName;
	QName << ToWxString("_");
	QName << this->mGenericName;
	return QName;
}
bool QualifiedName::Equals(QualifiedName QName)
{
	bool NativeMatch = this->NativeName().IsSameAs(QName.NativeName());
	bool GenericMatch = this->GenericName().IsSameAs(QName.GenericName());

	return (this->EqualsNative(QName) && this->EqualsGeneric(QName));
}
bool QualifiedName::EqualsNative(QualifiedName QName) { return this->NativeName().IsSameAs(QName.NativeName()); }
bool QualifiedName::EqualsGeneric(QualifiedName QName) { return this->GenericName().IsSameAs(QName.GenericName()); }
bool QualifiedName::EqualsHint(QualifiedName QName) { return this->GenericHint().IsSameAs(QName.GenericHint()); }
bool QualifiedName::operator==(QualifiedName QName) { return this->Equals(QName); }
bool QualifiedName::operator!=(QualifiedName QName) { return !(this->Equals(QName)); }
QualifiedName* QualifiedName::GetQualifiedNameByGeneric(wxString GenericName)
{
	if (QualifiedName::HasQualifiedNameWithGenericName(GenericName))
	{
		QualifiedName* pQName = new QualifiedName();
		pQName->mGenericName = GenericName;
		pQName->mNativeName = QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames[GenericName];
		pQName->mGenericHint = QualifiedNameRegister::GetSingletonPtr()->StoredGenericHints[GenericName];
	}
	else return 0;
}
wxArrayString QualifiedName::GetGenericByNative(wxString NativeName)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.begin(); IT != QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.end(); IT++)
	{
		if (IT->second.IsSameAs(NativeName)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedName::GetGenericByHint(wxString GenericHint)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.begin(); IT != QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.end(); IT++)
	{
		if (QualifiedNameRegister::GetSingletonPtr()->StoredGenericHints[IT->first].Contains(GenericHint)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedName::GetGenericBySubString(wxString SubString)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.begin(); IT != QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.end(); IT++)
	{
		if (QualifiedName::GetQualifiedNameByGeneric(IT->first)->UniqueName().Contains(SubString)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedName::GetGenericNames()
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.begin(); IT != QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.end(); IT++)
	{
		TempArray.Add(IT->first);
	}
	
	return TempArray;
}
bool QualifiedName::HasQualifiedNameWithGenericName(wxString GenericName)
{
	if (QualifiedNameRegister::GetSingletonPtr()->AllocatedGenericNames.count(GenericName) > 0) return true;
	else return false;
}
