#pragma once
#ifndef UNIQUE_NAME_MANAGER_H_
#define UNIQUE_NAME_MANAGER_H_

// Include WX
#include <wx/string.h>
#include <wx/hashmap.h>

class UniqueNameManager
{
private:
	WX_DECLARE_STRING_HASH_MAP(wxString, HashMap_UsedUniqueNames);

	HashMap_UsedUniqueNames mUsedUniqueNames;

	wxString mBasicEndingOfUniqueName;
public:
	UniqueNameManager(wxString BasicEndingOfUniqueName);
	~UniqueNameManager(void);

	wxString AllocateUniqueName(wxString OriginalName);
	bool DeallocateUniqueName(wxString ModifiedOriginalName);
};

#endif /*_UNIQUE_NAME_GENERATOR_H_*/