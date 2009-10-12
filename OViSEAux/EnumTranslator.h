#pragma once

#ifndef OVISE_OGRE_ENUMS_TRANSLATOR_H_
#define OVISE_OGRE_ENUMS_TRANSLATOR_H_

// Solution's includes
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/StringConverter.h"

// Include Ogre
#include <Ogre.h>

// Include WX
#include <wx/hashmap.h>

namespace OViSEOgreEnums
{
	WX_DECLARE_STRING_HASH_MAP( OViSEOgreEnums::MovableObject::MovableType, HashMap_Enums_MovableType_ByString );
	WX_DECLARE_HASH_MAP( OViSEOgreEnums::MovableObject::MovableType, wxString, wxIntegerHash, wxIntegerEqual, HashMap_Enums_MovableType_ByEnum );

	// COMMENT: This version fits Ogre 1.6.4

	class EnumTranslator
	{
	private:
		HashMap_Enums_MovableType_ByString	Register_MovableTypeByString;
		HashMap_Enums_MovableType_ByEnum	Register_MovableTypeByEnum;
		
		void createStandardAssociations_MovableType();
	public:
		EnumTranslator(void);
		~EnumTranslator(void);

		// Get corresponding wxString of enum
		wxString getEnumAsString(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType);
		
		// Get corresponding enum of wxString
		OViSEOgreEnums::MovableObject::MovableType getStringAsEnum(wxString StringOf_MovableType);

		// Get enum of specialized ogre-class
		OViSEOgreEnums::MovableObject::MovableType getMovableObjectAsEnum(Ogre::MovableObject* SomeMovableObject);

		// Get wxString of specialized ogre-class
		wxString getMovableObjectAsString(Ogre::MovableObject* SomeMovableObject);

		// Add association between a wxString and an enum
		bool addAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType, wxString StringOf_MovableType);

		// Remove association between a wxString and an enum
		bool removeAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType);
		bool removeAssociation_MovableType(wxString StringOf_MovableType);

	};
};

#endif // OVISE_OGRE_ENUMS_TRANSLATOR_H_