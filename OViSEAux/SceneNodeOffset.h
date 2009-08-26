#pragma once
#ifndef SCENENODE_OFFSET_H_
#define SCENENODE_OFFSET_H_

// Include Ogre
#include "Ogre.h"

class SceneNodeOffset
{
private:
	// Offset-properties
	double ScaleOffset;
	Ogre::Vector3 PositionOffset;
	Ogre::Degree RollOffset , PitchOffset, YawOffset;

public:
	// De- & Constructors
	SceneNodeOffset(void);
	~SceneNodeOffset(void);

	// Acessors of offset-properies
	double GetScaleOffset() const;
	Ogre::Vector3 GetPositionOffset() const;
	Ogre::Degree GetRollOffset() const;
	Ogre::Degree GetPitchOffset() const;
	Ogre::Degree GetYawOffset() const;

	void SetScaleOffset(double);
	void SetPositionOffset(Ogre::Vector3);
	void SetRollOffset(Ogre::Degree);
	void SetPitchOffset(Ogre::Degree);
	void SetYawOffset(Ogre::Degree);
};

#endif /*SCENENODE_OFFSET_H_*/