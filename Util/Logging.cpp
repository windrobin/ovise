/********************************************************************************
* Name:      Logging.cpp														*
* Purpose:   Code implements a class for log information. The class has not	*
*			  written for a special source. Different log-destinations are		*
*			  combined here and can be used.  It is designed as singleton and	*
*			  is useable in entire solution.									*
* Created:   2009-11-12														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#include "Logging.h"

// Singleton
Logging* Logging::instance = 0;

Logging::Logging( void ) { }
Logging::~Logging( void ) { }

Logging* Logging::GetSingletonPtr()
{
	if ( Logging::instance == 0 ) Logging::instance = new Logging();
	return Logging::instance;
}
bool Logging::WriteToOgreLog( wxString          LogMessage,
                              Logging::Priority PriorityLevel )
{
	Ogre::String temp;
	wxString     tempwx;

	switch(PriorityLevel)
	{
	case Trivial:
		Ogre::LogManager::getSingletonPtr()->logMessage( ToOgreString(
				LogMessage ), Ogre::LML_TRIVIAL );
		break;
	case Normal:
		Ogre::LogManager::getSingletonPtr()->logMessage( ToOgreString(
				LogMessage ), Ogre::LML_NORMAL );
		break;
	case Critical:
		Ogre::LogManager::getSingletonPtr()->logMessage( ToOgreString(
				LogMessage ), Ogre::LML_CRITICAL );
		break;

	default:
		Ogre::LogManager::getSingletonPtr()->logMessage( ToOgreString(
				LogMessage ), Ogre::LML_NORMAL );
		break;
	}

	return true;
}
