#include "EnumTranslator.h"

OViSEOgreEnums::EnumTranslator::EnumTranslator(void)
{
	this->createStandardAssociations_MovableType();
}

OViSEOgreEnums::EnumTranslator::~EnumTranslator(void)
{
	this->Register_MovableTypeByEnum.clear();
	this->Register_MovableTypeByString.clear();
}

void OViSEOgreEnums::EnumTranslator::createStandardAssociations_MovableType()
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

wxString OViSEOgreEnums::EnumTranslator::getEnumAsString(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType) { return this->Register_MovableTypeByEnum[EnumOf_MovableType]; }
OViSEOgreEnums::MovableObject::MovableType OViSEOgreEnums::EnumTranslator::getStringAsEnum(wxString StringOf_MovableType) { return this->Register_MovableTypeByString[StringOf_MovableType]; }
OViSEOgreEnums::MovableObject::MovableType OViSEOgreEnums::EnumTranslator::getMovableObjectAsEnum(Ogre::MovableObject* SomeMovableObject)
{
	if ( SomeMovableObject == 0 ) return OViSEOgreEnums::MovableObject::MOVABLETYPE_Invalid;

	if ( typeid(SomeMovableObject) == typeid(Ogre::MovableObject*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_BaseClass;
	if ( typeid(SomeMovableObject) == typeid(Ogre::BillboardChain*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain;
	if ( typeid(SomeMovableObject) == typeid(Ogre::BillboardSet*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet;
	if ( typeid(SomeMovableObject) == typeid(Ogre::Camera*) )			return OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera;
	if ( typeid(SomeMovableObject) == typeid(Ogre::Entity*) )			return OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity;
	if ( typeid(SomeMovableObject) == typeid(Ogre::Frustum*) )			return OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum;
	if ( typeid(SomeMovableObject) == typeid(Ogre::InstancedGeometry::BatchInstance*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance;
	if ( typeid(SomeMovableObject) == typeid(Ogre::InstancedGeometry::GeometryBucket*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable;
	if ( typeid(SomeMovableObject) == typeid(Ogre::Light*) )			return OViSEOgreEnums::MovableObject::MOVABLETYPE_Light;
	if ( typeid(SomeMovableObject) == typeid(Ogre::ManualObject*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject;
	if ( typeid(SomeMovableObject) == typeid(Ogre::MovablePlane*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane;
	if ( typeid(SomeMovableObject) == typeid(Ogre::ParticleSystem*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem;
	if ( typeid(SomeMovableObject) == typeid(Ogre::Rectangle2D*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable;
	if ( typeid(SomeMovableObject) == typeid(Ogre::RibbonTrail*) )		return OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail;
	if ( typeid(SomeMovableObject) == typeid(Ogre::SimpleRenderable*) ) return OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable;
	if ( typeid(SomeMovableObject) == typeid(Ogre::StaticGeometry::Region*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region;
	if ( typeid(SomeMovableObject) == typeid(Ogre::WireBoundingBox*) )	return OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable;

	// else
	return OViSEOgreEnums::MovableObject::MOVABLETYPE_Invalid;
}
wxString OViSEOgreEnums::EnumTranslator::getMovableObjectAsString(Ogre::MovableObject* SomeMovableObject) { return this->getEnumAsString(this->getMovableObjectAsEnum(SomeMovableObject)); }

bool OViSEOgreEnums::EnumTranslator::addAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType, wxString StringOf_MovableType)
{
	if ( this->Register_MovableTypeByString.count( StringOf_MovableType ) != 0 ) return false;
	if ( this->Register_MovableTypeByEnum.count( EnumOf_MovableType ) != 0 ) return false;

	this->Register_MovableTypeByString[StringOf_MovableType] = EnumOf_MovableType;
	this->Register_MovableTypeByEnum[EnumOf_MovableType] = StringOf_MovableType;

	return true;
}

bool OViSEOgreEnums::EnumTranslator::removeAssociation_MovableType(OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType)
{
	if ( this->Register_MovableTypeByEnum.count( EnumOf_MovableType ) == 0 ) return false;

	wxString StringOf_MovableType = this->Register_MovableTypeByEnum[EnumOf_MovableType];
	this->Register_MovableTypeByEnum.erase(EnumOf_MovableType);
	this->Register_MovableTypeByString.erase(StringOf_MovableType);

	return true;
}

bool OViSEOgreEnums::EnumTranslator::removeAssociation_MovableType(wxString StringOf_MovableType)
{
	if ( this->Register_MovableTypeByString.count( StringOf_MovableType ) == 0 ) return false;

	OViSEOgreEnums::MovableObject::MovableType EnumOf_MovableType = this->Register_MovableTypeByString[StringOf_MovableType];
	this->Register_MovableTypeByString.erase(StringOf_MovableType);
	this->Register_MovableTypeByEnum.erase(EnumOf_MovableType);

	return true;
}