#include "EnumTranslator_MovableType.h"

// Singleton
OViSEOgreEnums::EnumTranslator_MovableType* OViSEOgreEnums::EnumTranslator_MovableType::instance = 0;

OViSEOgreEnums::EnumTranslator_MovableType* OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()
{
	if (OViSEOgreEnums::EnumTranslator_MovableType::instance == 0) OViSEOgreEnums::EnumTranslator_MovableType::instance = new OViSEOgreEnums::EnumTranslator_MovableType();
	return OViSEOgreEnums::EnumTranslator_MovableType::instance;
}

OViSEOgreEnums::EnumTranslator_MovableType::EnumTranslator_MovableType(void)
{
	this->createStandardAssociations_MovableType();
}

OViSEOgreEnums::EnumTranslator_MovableType::~EnumTranslator_MovableType(void)
{
	this->Register_MovableTypeByEnum.clear();
	this->Register_MovableTypeByString.clear();
}

void OViSEOgreEnums::EnumTranslator_MovableType::createStandardAssociations_MovableType()
{
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_Invalid, ToWxString("MOVABLETYPE_Invalid"));

	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_BaseClass,			ToWxString("MOVABLETYPE_BaseClass"));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain,		ToWxString(Ogre::BillboardChainFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet,		ToWxString(Ogre::BillboardSetFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera,				ToWxString("Camera"/* Ogre::Camera::msMovableType // -> protected -> inaccessible */));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity,				ToWxString(Ogre::EntityFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum,			ToWxString("Frustum"/* Ogre::Frustum::msMovableType  // -> protected -> inaccessible */));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance,	ToWxString("InstancedGeometry"/* Ogre::InstancedGeometry::BatchInstance::getMovableType() // -> not instanciated -> inaccessible*/));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject,		ToWxString(Ogre::ManualObjectFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane,		ToWxString("MovablePlane"/* Ogre::MovablePlane::msMovableType  // -> protected -> inaccessible */));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem,		ToWxString(Ogre::ParticleSystemFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail,		ToWxString(Ogre::RibbonTrailFactory::FACTORY_TYPE_NAME));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable,	ToWxString("SimpleRenderable"/* Ogre::SimpleRenderable::getMovableType() // -> not instanciated -> inaccessible*/));
	this->addAssociation_MovableType(OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region, ToWxString("StaticGeometry"/* Ogre::StaticGeometry::Region::getMovableType() // -> not instanciated -> inaccessible*/));
}

wxString OViSEOgreEnums::EnumTranslator_MovableType::getEnumAsString(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType) { return this->Register_MovableTypeByEnum[EnumOf_MovableType]; }
OViSEOgreEnums::MovableObject::MovableType OViSEOgreEnums::EnumTranslator_MovableType::getStringAsEnum(wxString StringOf_MovableType) { return this->Register_MovableTypeByString[StringOf_MovableType]; }
OViSEOgreEnums::MovableObject::MovableType OViSEOgreEnums::EnumTranslator_MovableType::getMovableObjectAsEnum(Ogre::MovableObject* SomeMovableObject)
{
	if ( SomeMovableObject == 0 ) return OViSEOgreEnums::MovableObject::MOVABLETYPE_Invalid;
	return this->getStringAsEnum(ToWxString(SomeMovableObject->getMovableType()));
}
wxString OViSEOgreEnums::EnumTranslator_MovableType::getMovableObjectAsString(Ogre::MovableObject* SomeMovableObject) { return this->getEnumAsString(this->getMovableObjectAsEnum(SomeMovableObject)); }

bool OViSEOgreEnums::EnumTranslator_MovableType::addAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType, wxString StringOf_MovableType)
{
	if ( this->Register_MovableTypeByString.count( StringOf_MovableType ) != 0 ) return false;
	if ( this->Register_MovableTypeByEnum.count( EnumOf_MovableType ) != 0 ) return false;

	this->Register_MovableTypeByString[StringOf_MovableType] = EnumOf_MovableType;
	this->Register_MovableTypeByEnum[EnumOf_MovableType] = StringOf_MovableType;

	return true;
}

bool OViSEOgreEnums::EnumTranslator_MovableType::removeAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType)
{
	if ( this->Register_MovableTypeByEnum.count( EnumOf_MovableType ) == 0 ) return false;

	wxString StringOf_MovableType = this->Register_MovableTypeByEnum[EnumOf_MovableType];
	this->Register_MovableTypeByEnum.erase(EnumOf_MovableType);
	this->Register_MovableTypeByString.erase(StringOf_MovableType);

	return true;
}

bool OViSEOgreEnums::EnumTranslator_MovableType::removeAssociation_MovableType(wxString StringOf_MovableType)
{
	if ( this->Register_MovableTypeByString.count( StringOf_MovableType ) == 0 ) return false;

	OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType = this->Register_MovableTypeByString[StringOf_MovableType];
	this->Register_MovableTypeByString.erase(StringOf_MovableType);
	this->Register_MovableTypeByEnum.erase(EnumOf_MovableType);

	return true;
}