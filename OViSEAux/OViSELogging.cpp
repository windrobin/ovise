#include "OViSELogging.h"

OViSELogging::OViSELogging(void) { }
OViSELogging::~OViSELogging(void) { }

bool OViSELogging::WriteToOgreLog(wxString LogMessage, OViSELogging::Priority PriorityLevel)
{
	switch(PriorityLevel)
	{
	case this->Trivial:
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(LogMessage), Ogre::LML_TRIVIAL);
		break;
	case this->Normal:
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(LogMessage), Ogre::LML_NORMAL);
		break;
	case this->Critical:
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(LogMessage), Ogre::LML_CRITICAL);
		break;

	default:
		Ogre::LogManager::getSingletonPtr()->logMessage(ToOgreString(LogMessage), Ogre::LML_NORMAL);
		break;
	}

	return true;
}