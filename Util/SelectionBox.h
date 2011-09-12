#ifndef OVISE_SELECTIONBOX_H
#define OVISE_SELECTIONBOX_H

#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "AxisDisplay.h"
#include "Definitions.h"

const std::string OVISE_SelectionBoxName = "__SelectionBox";

class CSelectionBox : private boost::noncopyable
{
public:
	CSelectionBox( Ogre::SceneManager* SceneMgr );
	virtual ~CSelectionBox();

	/// Show selection around target object
	void Show( Ogre::Entity* Target );
	/// Hide selection box
	void Hide();

	/** Get the axis of the manipulator tool.
	    Given an area of screen space, this checks if (and which)
		axis of the manipulator tool is below the cursor.
	*/
	const int GetToolAxis( Ogre::Camera* Cam, 
		const Ogre::Real& ScreenLeft, const Ogre::Real& ScreenTop,
		const Ogre::Real& ScreenRight, const Ogre::Real& ScreenBottom );

	int mCurrentToolAxis;
	int mCurrentToolMode;

	const Ogre::SceneNode* GetSceneNode() { return mParent; }

private:
	Ogre::Vector3					mSize;
	Ogre::SceneNode*				mParent;

	Ogre::SceneNode*                mMoveNode;
	Ogre::SceneNode*                mScaleNode;

	Ogre::ManualObject*				mVisual;

	Ogre::Entity*					mMoveManip;
	Ogre::Entity*                   mScaleManip;

	boost::scoped_ptr<CAxisDisplay> mAxisDisplay;

	void Resize( const Ogre::Vector3& Size );
	void ColorManipAxis( Ogre::Entity* Manip, const int& Axis );
};

#endif // OVISE_SELECTIONBOX_H
