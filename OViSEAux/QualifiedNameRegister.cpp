/********************************************************************************
 * Name:      QualifiedNameRegister.h											*
 * Purpose:   Implements a singleton class holding strings as parts of 			*
 *			  qualified names. These parts are: native name, generic name and 	*
 *			  genic hint.The generic name is unique and acts as hash-key.		*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../QualifiedNames/QualifiedNameRegister.h"

QualifiedNameRegister* QualifiedNameRegister::instance = 0;
QualifiedNameRegister::QualifiedNameRegister(void)
{
	this->AllocatedGenericNames = wxArrayString();
	this->StoredNativeNames = HashMap_wxString();
	this->StoredGenericHints = HashMap_wxString();
}

QualifiedNameRegister::~QualifiedNameRegister(void)
{
	this->AllocatedGenericNames.
	this->StoredNativeNames.clear();
	this->StoredGenericHints = HashMap_wxString();
}
QualifiedNameRegister* QualifiedNameRegister::GetSingletonPtr()
{
	if (QualifiedNameRegister::instance == 0) QualifiedNameRegister::instance = new QualifiedNameRegister();
	return QualifiedNameRegister::instance;
}
wxString QualifiedNameRegister::AllocateGenericName(wxString NativeName, wxString GenericHint)
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

bool QualifiedNameRegister::DeallocateGenericName(wxString GenericName)
{
	// Generic name is not allocated. Error.
	if (this->StoredNativeNames.count(GenericName) == 0) return false;

	// Generic name is allocated. Delete it!
	this->AllocatedGenericNames.erase(this->mGenericName);
	this->StoredGenericHints.erase(GenericName);
	this->StoredGenericHints.erase(GenericName);
	return true;
}
