/********************************************************************************
 * Name:      SceneNodeOffset.cpp												*
 * Purpose:   This class implements a offset-collection, which is used, when a 	*
 *			  prototype is placed into ogre-engine. The collection includes		*
 *			  offsets for position (x,y,z), rotation (r,p,y) and scale(x,y,z).	*
 *			  Simple global operators on Ogre::SceneNode are supported too.		*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-13														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../OViSEAux/SceneNodeOffset.h"

// De- & Constructors
SceneNodeOffset::SceneNodeOffset(void)
{
	this->SetScaleOffset(Ogre::Vector3(1.0f, 1.0f, 1.0f));
	this->SetPositionOffset(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	this->SetRollOffset(Ogre::Degree(0.0));
    this->SetPitchOffset(Ogre::Degree(0.0));
    this->SetYawOffset(Ogre::Degree(0.0));
	this->TS = Ogre::Node::TS_PARENT;
}

SceneNodeOffset::~SceneNodeOffset(void) { }
// Acessors of offset properies
Ogre::Vector3 SceneNodeOffset::GetScaleOffset() const { return this->ScaleOffset; }
Ogre::Vector3 SceneNodeOffset::GetPositionOffset() const { return this->PositionOffset; }
Ogre::Degree SceneNodeOffset::GetRollOffset() const { return this->RollOffset; }
Ogre::Degree SceneNodeOffset::GetPitchOffset() const {	return this->PitchOffset; }
Ogre::Degree SceneNodeOffset::GetYawOffset() const { return this->YawOffset; }
void SceneNodeOffset::SetScaleOffset(Ogre::Vector3 ScaleOffset) { this->ScaleOffset = ScaleOffset; } 
void SceneNodeOffset::SetPositionOffset(Ogre::Vector3 PositionOffset) { this->PositionOffset = PositionOffset; }
void SceneNodeOffset::SetRollOffset(Ogre::Degree value) { this->RollOffset = value; }
void SceneNodeOffset::SetPitchOffset(Ogre::Degree value) { this->PitchOffset = value; }
void SceneNodeOffset::SetYawOffset(Ogre::Degree value) { this->YawOffset = value; }
// Accessors, Transforming Space, default is TS_PARENT
Ogre::Node::TransformSpace SceneNodeOffset::GetTransformSpace() { return this->TS; }
void SceneNodeOffset::SetTransformSpace(Ogre::Node::TransformSpace TS) { this->TS = TS; }
// Operators
Ogre::SceneNode* operator+(SceneNodeOffset OS, Ogre::SceneNode* pSN)
{
	return operator+(pSN, OS);
}
Ogre::SceneNode* operator+(Ogre::SceneNode* pSN, SceneNodeOffset OS)
{
	if (( pSN == 0 )) return pSN;

	pSN->translate(OS.GetPositionOffset(), OS.GetTransformSpace());
	pSN->scale(OS.GetScaleOffset());
	pSN->roll(Ogre::Radian(OS.GetRollOffset()));
	pSN->pitch(Ogre::Radian(OS.GetPitchOffset()));
	pSN->yaw(Ogre::Radian(OS.GetYawOffset()));

	return pSN;
}
Ogre::SceneNode* operator-(Ogre::SceneNode* pSN, SceneNodeOffset OS)
{
	if ( pSN == 0 ) return pSN;

	// Get position and negate it!
	Ogre::Vector3 P = OS.GetPositionOffset();
	P.x = P.x * -1.0f;
	P.y = P.y * -1.0f;
	P.z = P.z * -1.0f;

	// Get scale and negate it!
	Ogre::Vector3 S = OS.GetScaleOffset();
	S.x = 1 / S.x;
	S.y = 1 / S.y;
	S.z = 1 / S.z;

	pSN->translate(P, OS.GetTransformSpace());
	pSN->scale(S);

	pSN->roll(Ogre::Radian((Ogre::Degree(360.0) - OS.GetRollOffset())));
	pSN->pitch(Ogre::Radian((Ogre::Degree(360.0) - OS.GetPitchOffset())));
	pSN->yaw(Ogre::Radian((Ogre::Degree(360.0) - OS.GetYawOffset())));

	return pSN;
}