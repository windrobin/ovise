#include "MovableTypeTranslator.h"

// Singleton
OgreEnums::MovableTypeTranslator* OgreEnums::MovableTypeTranslator::instance = 0;
OgreEnums::MovableTypeTranslator* OgreEnums::MovableTypeTranslator::GetSingletonPtr()
{
	if (OgreEnums::MovableTypeTranslator::instance == 0) OgreEnums::MovableTypeTranslator::instance = new OgreEnums::MovableTypeTranslator();
	return OgreEnums::MovableTypeTranslator::instance;
}
OgreEnums::MovableTypeTranslator::MovableTypeTranslator(void)
{
	this->InitStandardAssociations();
}
OgreEnums::MovableTypeTranslator::~MovableTypeTranslator(void)
{
	this->mStringByMovableType.clear();
	this->mMovableTypeByStringRegister.clear();
}
void OgreEnums::MovableTypeTranslator::InitStandardAssociations()
{
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_Invalid, ToWxString("MOVABLETYPE_Invalid"));

	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_BaseClass,			ToWxString("MOVABLETYPE_BaseClass"));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_BillBoardChain,		ToWxString(Ogre::BillboardChainFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_BillboardSet,		ToWxString(Ogre::BillboardSetFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_Camera,				ToWxString("Camera"/* Ogre::Camera::msMovableType // -> protected -> inaccessible */));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_Entity,				ToWxString(Ogre::EntityFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_Frustum,				ToWxString("Frustum"/* Ogre::Frustum::msMovableType  // -> protected -> inaccessible */));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_Light,				ToWxString(Ogre::LightFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance,	ToWxString("BatchInstancedGeometry"/* Ogre::InstancedGeometry::BatchInstance::getMovableType() // -> not instanciated -> inaccessible*/));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_ManualObject,		ToWxString(Ogre::ManualObjectFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_MovablePlane,		ToWxString("MovablePlane"/* Ogre::MovablePlane::msMovableType  // -> protected -> inaccessible */));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_ParticleSystem,		ToWxString(Ogre::ParticleSystemFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_RibbonTrail,			ToWxString(Ogre::RibbonTrailFactory::FACTORY_TYPE_NAME));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable,	ToWxString("SimpleRenderable"/* Ogre::SimpleRenderable::getMovableType() // -> not instanciated -> inaccessible*/));
	this->AddAssociation(OgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region, ToWxString("StaticGeometry"/* Ogre::StaticGeometry::Region::getMovableType() // -> not instanciated -> inaccessible*/));
}

wxString OgreEnums::MovableTypeTranslator::GetEnumAsString(OgreEnums::MovableObject::MovableType EnumOfMovableType) { return this->mStringByMovableType[EnumOfMovableType]; }
OgreEnums::MovableObject::MovableType OgreEnums::MovableTypeTranslator::GetStringAsEnum(wxString StringOfMovableType) { return this->mMovableTypeByStringRegister[StringOfMovableType]; }
OgreEnums::MovableObject::MovableType OgreEnums::MovableTypeTranslator::GetMovableObjectAsEnum(Ogre::MovableObject* MO)
{
	if ( MO == 0 ) return OgreEnums::MovableObject::MOVABLETYPE_Invalid;
	return this->GetStringAsEnum(ToWxString(MO->getMovableType()));
}
wxString OgreEnums::MovableTypeTranslator::GetMovableObjectAsString(Ogre::MovableObject* MO) { return this->GetEnumAsString(this->GetMovableObjectAsEnum(MO)); }
bool OgreEnums::MovableTypeTranslator::AddAssociation(OgreEnums::MovableObject::MovableType EnumOfMovableType, wxString StringOfMovableType)
{
	if ( this->mMovableTypeByStringRegister.count( StringOfMovableType ) != 0 ) return false;
	if ( this->mStringByMovableType.count( EnumOfMovableType ) != 0 ) return false;

	this->mMovableTypeByStringRegister[StringOfMovableType] = EnumOfMovableType;
	this->mStringByMovableType[EnumOfMovableType] = StringOfMovableType;

	return true;
}

bool OgreEnums::MovableTypeTranslator::RemoveAssociation(OgreEnums::MovableObject::MovableType EnumOfMovableType)
{
	if ( this->mStringByMovableType.count( EnumOfMovableType ) == 0 ) return false;

	wxString StringOfMovableType = this->mStringByMovableType[EnumOfMovableType];
	this->mStringByMovableType.erase(EnumOfMovableType);
	this->mMovableTypeByStringRegister.erase(StringOfMovableType);

	return true;
}

bool OgreEnums::MovableTypeTranslator::RemoveAssociation(wxString StringOfMovableType)
{
	if ( this->mMovableTypeByStringRegister.count( StringOfMovableType ) == 0 ) return false;

	OgreEnums::MovableObject::MovableType EnumOfMovableType = this->mMovableTypeByStringRegister[StringOfMovableType];
	this->mMovableTypeByStringRegister.erase(StringOfMovableType);
	this->mStringByMovableType.erase(EnumOfMovableType);

	return true;
}