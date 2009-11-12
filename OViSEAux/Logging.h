/********************************************************************************
 * Name:      Logging.h															*
 * Purpose:   Code describes a class for log information. The class has not		*
 *			  written for a special source. Different log-destinations are		*
 *			  combined here and can be used. It is designed as singleton and	*
 *			  is useable in entire solution.									*
 * Created:   2009-11-12														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef LOGGING_H_
#define LOGGING_H_

// Solution's includes
#include "../OViSEAux/StringConverter.h"

// Include Ogre
#include "Ogre.h"

class Logging
{
private:
	Logging(void);

	// Singleton
	static Logging* instance;

public:
	enum Priority { Trivial = 1, Normal = 2, Critical = 3 };

	~Logging(void);

	static Logging* GetSingletonPtr();

	virtual bool WriteToOgreLog(wxString LogMessage, Logging::Priority PriorityLevel);
};

#endif // LOGGING_H_