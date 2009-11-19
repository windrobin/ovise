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

#include "../QualifiedNames/QualifiedName.h"

QualifiedName::QualifiedName() { this->mGenericName = wxString(); }
QualifiedName::QualifiedName(const QualifiedName& ToCopy) { this->mGenericName = ToCopy.mGenericName; }
QualifiedName::~QualifiedName(void) { }
QualifiedName QualifiedName::Create(wxString NativeName) { return QualifiedName::Create(NativeName, wxT("")); }
QualifiedName QualifiedName::Create(wxString NativeName, wxString GenericHint)
{
	// Create empty QName
	QualifiedName QName;

	// Create QualifiedName
	wxString GenericName = QualifiedNameManager::GetSingletonPtr()->AllocateGenericName(NativeName, GenericHint);

	// Set generic name
	QName.mGenericName = GenericName;

	return QName;
}
bool QualifiedName::Destroy(QualifiedName QName) { return QualifiedName::Destroy(QName.mGenericName); }
bool QualifiedName::Destroy(wxString GenericName) { return QualifiedNameManager::GetSingletonPtr()->DeallocateGenericName(GenericName); }
bool QualifiedName::Destroy() { return QualifiedNameManager::GetSingletonPtr()->DeallocateGenericName(this->mGenericName); }
bool QualifiedName::IsValid() { return QualifiedNameManager::GetSingletonPtr()->HasGeneric(this->mGenericName); }
wxString QualifiedName::GenericHint() { return QualifiedNameManager::GetSingletonPtr()->GetHintByGeneric(this->mGenericName); }
wxString QualifiedName::GenericName() { return this->mGenericName; }
wxString QualifiedName::NativeName() { return QualifiedNameManager::GetSingletonPtr()->GetNativeByGeneric(this->mGenericName); }
wxString QualifiedName::UniqueName() { return (this->NativeName() + this->GenericName()); }
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
bool QualifiedName::ContainsSubString(wxString SubString) { return this->UniqueName().Contains(SubString); }
QualifiedName QualifiedName::GetQualifiedNameByGeneric(wxString GenericName)
{
	QualifiedName QName;
	if (QualifiedNameManager::GetSingletonPtr()->HasGeneric(GenericName)) QName.mGenericName = GenericName;
	return QName;
}

QualifiedName QualifiedName::GetQualifiedNameByUnique(wxString UniqueName)
{
	QualifiedName QName;
	QName.mGenericName = QualifiedNameManager::GetSingletonPtr()->GetGenericByUnique(UniqueName);
	return QName;
}
// Methods, has, static
bool QualifiedName::HasQualifiedNameWithGeneric(wxString GenericName) { return QualifiedName::GetQualifiedNameByGeneric(GenericName).IsValid(); }
bool QualifiedName::HasQualifiedNameWithUnique(wxString UniqueName) { return QualifiedName::GetQualifiedNameByUnique(UniqueName).IsValid(); }
