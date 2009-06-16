#ifndef OVISE_UNIQUE_NAME_GENERATOR_H_
#define OVISE_UNIQUE_NAME_GENERATOR_H_

#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/arrstr.h>
#include <wx/hashmap.h>

class OViSEUniqueNameGenerator
{
private:
	WX_DECLARE_STRING_HASH_MAP(wxString, HashMap_UsedUniqueNames);

	HashMap_UsedUniqueNames mUsedUniqueNames;

	wxString mBasicEndingOfUniqueName;
public:
	OViSEUniqueNameGenerator(wxString BasicEndingOfUniqueName);
	~OViSEUniqueNameGenerator(void);

	wxString AllocateUniqueName(wxString OriginalName);
	bool DeallocateUniqueName(wxString ModifiedOriginalName);
};

#endif /*OVISE_UNIQUE_NAME_GENERATOR_H_*/