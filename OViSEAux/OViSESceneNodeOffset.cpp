#include "OViSESceneNodeOffset.h"

OViSESceneNodeOffset::OViSESceneNodeOffset(void)
{
	this->SetScaleOffset(1.0);
	this->SetPositionOffset(Ogre::Vector3(0.0, 0.0, 0.0));
	this->SetRollOffset(Ogre::Degree(0.0));
    this->SetPitchOffset(Ogre::Degree(0.0));
    this->SetYawOffset(Ogre::Degree(0.0));
}

OViSESceneNodeOffset::~OViSESceneNodeOffset(void)
{
}

// Acessors of offset properies
double OViSESceneNodeOffset::GetScaleOffset() const { return this->ScaleOffset; }
Ogre::Vector3 OViSESceneNodeOffset::GetPositionOffset() const { return this->PositionOffset; }
Ogre::Degree OViSESceneNodeOffset::GetRollOffset() const { return this->RollOffset; }
Ogre::Degree OViSESceneNodeOffset::GetPitchOffset() const {	return this->PitchOffset; }
Ogre::Degree OViSESceneNodeOffset::GetYawOffset() const { return this->YawOffset; }
void OViSESceneNodeOffset::SetScaleOffset(double ScaleOffset) { this->ScaleOffset = ScaleOffset; } 
void OViSESceneNodeOffset::SetPositionOffset(Ogre::Vector3 PositionOffset) { this->PositionOffset = PositionOffset; }
void OViSESceneNodeOffset::SetRollOffset(Ogre::Degree value) { this->RollOffset = value; }
void OViSESceneNodeOffset::SetPitchOffset(Ogre::Degree value) { this->PitchOffset = value; }
void OViSESceneNodeOffset::SetYawOffset(Ogre::Degree value) { this->YawOffset = value; }