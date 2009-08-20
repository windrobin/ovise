#ifndef OVISE_LOGGING_H_
#define OVISE_LOGGING_H_

// Solution's includes
#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

class OViSELogging
{
public:
	enum Priority { Trivial = 1, Normal = 2, Critical = 3 };

	OViSELogging(void);
	~OViSELogging(void);

	virtual bool WriteToOgreLog(wxString LogMessage, OViSELogging::Priority PriorityLevel);
};

#endif // OVISE_LOGGING_H_