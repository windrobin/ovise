/********************************************************************************
* Name:      SceneNodeOffset.h													*
* Purpose:   This class defines a offset-collection, which is used, when a      *
*			  prototype is placed into ogre-engine. The collection includes		*
*			  offsets for position (x,y,z), rotation (r,p,y) and scale(x,y,z).	*
*			  Simple global operators on Ogre::SceneNode are supported too.		*
* Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
* Created:   2009-11-13														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#ifndef SCENENODE_OFFSET_H_
#define SCENENODE_OFFSET_H_

// Include Ogre
#include <Ogre.h>

class SceneNodeOffset
{
private:
	// Offset-properties
	Ogre::Vector3              ScaleOffset;
	Ogre::Vector3              PositionOffset;
	Ogre::Degree               RollOffset, PitchOffset, YawOffset;
	Ogre::Node::TransformSpace TS;

public:
	// De- & Constructors
	SceneNodeOffset();
	~SceneNodeOffset( void );

	// Acessors, offset-properies
	Ogre::Vector3 GetScaleOffset() const;
	Ogre::Vector3 GetPositionOffset() const;
	Ogre::Degree GetRollOffset() const;
	Ogre::Degree GetPitchOffset() const;
	Ogre::Degree GetYawOffset() const;

	void SetScaleOffset( Ogre::Vector3 ScaleOffset );
	void SetPositionOffset( Ogre::Vector3 PositionOffset );
	void SetRollOffset( Ogre::Degree value );
	void SetPitchOffset( Ogre::Degree value );
	void SetYawOffset( Ogre::Degree value );

	// Accessors, Transforming Space, default is TS_PARENT
	Ogre::Node::TransformSpace GetTransformSpace();
	void SetTransformSpace( Ogre::Node::TransformSpace TS );
};

// Operators
Ogre::SceneNode* operator+( SceneNodeOffset OS, Ogre::SceneNode* pSN );
Ogre::SceneNode* operator+( Ogre::SceneNode* pSN, SceneNodeOffset OS );
Ogre::SceneNode* operator-( Ogre::SceneNode* pSN, SceneNodeOffset OS );

#endif /*SCENENODE_OFFSET_H_*/
