/********************************************************************************
 * Name:      QualifiedNameManager.h											*
 * Purpose:   Implements a singleton class holding strings as parts of 			*
 *			  qualified names. These parts are: native name, generic name and 	*
 *			  genic hint.The generic name is unique and acts as hash-key.		*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "QualifiedNameManager.h"

QualifiedNameManager* QualifiedNameManager::instance = 0;
QualifiedNameManager::QualifiedNameManager(void)
{
	this->AllocatedGenericNames = wxArrayString();
	this->StoredNativeNames = HashMap_wxString();
	this->StoredGenericHints = HashMap_wxString();
}

QualifiedNameManager::~QualifiedNameManager(void)
{
	this->AllocatedGenericNames.Clear();
	this->StoredNativeNames.clear();
	this->StoredGenericHints.clear();
}
QualifiedNameManager* QualifiedNameManager::GetSingletonPtr()
{
	if (QualifiedNameManager::instance == 0) QualifiedNameManager::instance = new QualifiedNameManager();
	return QualifiedNameManager::instance;
}
wxString QualifiedNameManager::AllocateGenericName(wxString NativeName, wxString GenericHint)
{
	// Prepare basic generic name, including hint
	wxString BasicGenericName = wxT("_");
	BasicGenericName << GenericHint << wxT("_");

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
			BasicGenericName << GenericHint << wxT("_");
		}
		FinalGenericName.Clear();
		FinalGenericName << BasicGenericName << wxString::Format(wxT("%i"), Counter);
		Counter++;
	}
	while(this->StoredNativeNames.count(FinalGenericName) != 0);

	// Found unique generic name

	// Store unique generic name as key. Using native name as value. So reverse tracking is possible.
	this->AllocatedGenericNames.Add(FinalGenericName);
	this->StoredNativeNames[FinalGenericName] = NativeName;
	this->StoredGenericHints[FinalGenericName] = GenericHint;

	return FinalGenericName;
}

bool QualifiedNameManager::DeallocateGenericName(wxString GenericName)
{
	// Generic name is not allocated. Error.
	if (this->StoredNativeNames.count(GenericName) == 0) return false;

	// Generic name is allocated. Delete it!
	this->AllocatedGenericNames.Remove(GenericName);
	this->StoredGenericHints.erase(GenericName);
	this->StoredGenericHints.erase(GenericName);
	return true;
}
bool QualifiedNameManager::HasGeneric(wxString GenericName)
{
	if (this->StoredNativeNames.count(GenericName) == 0) return false;
	else return true;
}
wxString QualifiedNameManager::GetNativeByGeneric(wxString GenericName)
{
	if (this->StoredNativeNames.count(GenericName) == 0) return wxString();
	else return this->StoredNativeNames[GenericName];
}
wxString QualifiedNameManager::GetHintByGeneric(wxString GenericName)
{
	if (this->StoredGenericHints.count(GenericName) == 0) return wxString();
	else return this->StoredGenericHints[GenericName];
}
wxArrayString QualifiedNameManager::GetGenericByNative(wxString NativeName)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = this->StoredNativeNames.begin(); IT != this->StoredNativeNames.end(); IT++)
	{
		if (IT->second.IsSameAs(NativeName)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedNameManager::GetGenericByHint(wxString GenericHint)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = this->StoredGenericHints.begin(); IT != this->StoredGenericHints.end(); IT++)
	{
		if (IT->second.IsSameAs(GenericHint)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedNameManager::GetGenericBySubString(wxString SubString)
{
	wxArrayString TempArray;
	TempArray.clear();
	
	for(HashMap_wxString::iterator IT = this->StoredNativeNames.begin(); IT != this->StoredNativeNames.end(); IT++)
	{
		wxString UniqueName = (IT->second) + (IT->first);
		if (UniqueName.Contains(SubString)) TempArray.Add(IT->first);
	}
	
	return TempArray;
}
wxArrayString QualifiedNameManager::GetGenericNames() { return this->AllocatedGenericNames; }
wxString QualifiedNameManager::GetGenericByUnique(wxString UniqueName)
{
	wxString GenericName;
	GenericName.clear();

	for(HashMap_wxString::iterator IT = this->StoredNativeNames.begin(); IT != this->StoredNativeNames.end(); IT++)
	{
		wxString CompareUniqueName = (IT->second) + (IT->first);
		if (CompareUniqueName.IsSameAs(UniqueName)) GenericName = IT->first;
	}

	return GenericName;
}