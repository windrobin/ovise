#pragma once
#ifndef OVISE_LOGGING_H_
#define OVISE_LOGGING_H_

// Solution's includes
#include "./StringConverter.h"

// Include Ogre
#include "Ogre.h"

class OViSELogging
{
public:
	enum Priority { Trivial = 1, Normal = 2, Critical = 3 };

	OViSELogging(void);
	~OViSELogging(void);

	virtual bool WriteToOgreLog(wxString LogMessage, OViSELogging::Priority PriorityLevel);
};

#endif // OVISE_LOGGING_H_