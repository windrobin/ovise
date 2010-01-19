#ifndef OGRE_ENUMS_MOVABLETYPE_TRANSLATOR_H_
#define OGRE_ENUMS_MOVABLETYPE_TRANSLATOR_H_

// Include WX
#include <wx/hashmap.h>

// Solution's includes
#include "../OViSEAux/EnumsForABetterWorld.h"
#include "../OViSEAux/StringConverter.h"

// Include Ogre
#include <Ogre.h>

namespace OgreEnums
{
	WX_DECLARE_STRING_HASH_MAP( OgreEnums::MovableObject::MovableType, MovableTypeByStringHashMap );
	WX_DECLARE_HASH_MAP( OgreEnums::MovableObject::MovableType, wxString, wxIntegerHash, wxIntegerEqual, StringByMovableTypeHashMap );

	// COMMENT: This version fits Ogre 1.6.4

	class MovableTypeTranslator
	{
	private:
		// De- & Constructors
		MovableTypeTranslator(void);
		
		// Singleton
		static MovableTypeTranslator* instance;

		// Attributes
		MovableTypeByStringHashMap	mMovableTypeByStringRegister;
		StringByMovableTypeHashMap	mStringByMovableType;

		// Methods
		void InitStandardAssociations();

	public:
		// De- & Constructors
		~MovableTypeTranslator(void);

		// Singleton
		static OgreEnums::MovableTypeTranslator* GetSingletonPtr();

		// Get corresponding wxString of enum
		wxString GetEnumAsString(OgreEnums::MovableObject::MovableType EnumOfMovableType);
		
		// Get corresponding enum of wxString
		OgreEnums::MovableObject::MovableType GetStringAsEnum(wxString StringOfMovableType);

		// Get enum of specialized ogre-class
		OgreEnums::MovableObject::MovableType GetMovableObjectAsEnum(Ogre::MovableObject* MO);

		// Get wxString of specialized ogre-class
		wxString GetMovableObjectAsString(Ogre::MovableObject* MO);

		// Add association between a wxString and an enum
		bool AddAssociation(OgreEnums::MovableObject::MovableType EnumOfMovableType, wxString StringOfMovableType);

		// Remove association between a wxString and an enum
		bool RemoveAssociation(OgreEnums::MovableObject::MovableType EnumOfMovableType);
		bool RemoveAssociation(wxString StringOfMovableType);
	};
};

#endif // OGRE_ENUMS_MOVABLETYPE_TRANSLATOR_H_