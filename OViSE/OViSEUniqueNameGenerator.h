#ifndef OVISE_UNIQUE_NAME_GENERATOR_H_
#define OVISE_UNIQUE_NAME_GENERATOR_H_

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_HASHMAP_USED
#define WX_HASHMAP_USED
#include <wx/hashmap.h>
#endif

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