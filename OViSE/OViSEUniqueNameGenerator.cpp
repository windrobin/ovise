#include "OViSEUniqueNameGenerator.h"

OViSEUniqueNameGenerator::OViSEUniqueNameGenerator(wxString BasicEndingOfUniqueName)
{
	this->mBasicEndingOfUniqueName = wxString(BasicEndingOfUniqueName);
	this->mUsedUniqueNames.clear();
}
OViSEUniqueNameGenerator::~OViSEUniqueNameGenerator(void)
{
	this->mUsedUniqueNames.clear();
}
wxString OViSEUniqueNameGenerator::AllocateUniqueName(wxString OriginalName)
{
	wxString BasicUniqueName = OriginalName;
	BasicUniqueName.append(wxString(wxT("_")));
	BasicUniqueName.append(this->mBasicEndingOfUniqueName);
	BasicUniqueName.append(wxString(wxT("_")));

	int Counter = 0;
	wxString FinalUniqueName;
	
	do
	{
		FinalUniqueName.Clear();
		FinalUniqueName << BasicUniqueName << wxString::Format(wxT("%i"), Counter);
		Counter++;
	}
	while(this->mUsedUniqueNames.find(FinalUniqueName) != this->mUsedUniqueNames.end());

	this->mUsedUniqueNames[FinalUniqueName] = wxString();

	return FinalUniqueName;
}

bool OViSEUniqueNameGenerator::DeallocateUniqueName(wxString ModifiedOriginalName)
{
	// ModifiedOriginalName is not allocated. Error.
	if (this->mUsedUniqueNames.find(ModifiedOriginalName) == this->mUsedUniqueNames.end()) return false;

	// ModifiedOriginalName is allocated.
	this->mUsedUniqueNames.erase(ModifiedOriginalName);
	return true;
}