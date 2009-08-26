#include "SceneNodeOffset.h"

SceneNodeOffset::SceneNodeOffset(void)
{
	this->SetScaleOffset(1.0);
	this->SetPositionOffset(Ogre::Vector3(0.0, 0.0, 0.0));
	this->SetRollOffset(Ogre::Degree(0.0));
    this->SetPitchOffset(Ogre::Degree(0.0));
    this->SetYawOffset(Ogre::Degree(0.0));
}

SceneNodeOffset::~SceneNodeOffset(void) { }

// Acessors of offset properies
double SceneNodeOffset::GetScaleOffset() const { return this->ScaleOffset; }
Ogre::Vector3 SceneNodeOffset::GetPositionOffset() const { return this->PositionOffset; }
Ogre::Degree SceneNodeOffset::GetRollOffset() const { return this->RollOffset; }
Ogre::Degree SceneNodeOffset::GetPitchOffset() const {	return this->PitchOffset; }
Ogre::Degree SceneNodeOffset::GetYawOffset() const { return this->YawOffset; }
void SceneNodeOffset::SetScaleOffset(double ScaleOffset) { this->ScaleOffset = ScaleOffset; } 
void SceneNodeOffset::SetPositionOffset(Ogre::Vector3 PositionOffset) { this->PositionOffset = PositionOffset; }
void SceneNodeOffset::SetRollOffset(Ogre::Degree value) { this->RollOffset = value; }
void SceneNodeOffset::SetPitchOffset(Ogre::Degree value) { this->PitchOffset = value; }
void SceneNodeOffset::SetYawOffset(Ogre::Degree value) { this->YawOffset = value; }