#ifndef OVISE_SCENENODE_OFFSET_H_
#define OVISE_SCENENODE_OFFSET_H_

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

class OViSESceneNodeOffset
{
private:
	// Offset-properties
	double ScaleOffset;
	Ogre::Vector3 PositionOffset;
	Ogre::Degree RollOffset , PitchOffset, YawOffset;

public:
	// De- & Constructors
	OViSESceneNodeOffset(void);
	~OViSESceneNodeOffset(void);

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

#endif /*OVISE_SCENENODE_OFFSET_H_*/