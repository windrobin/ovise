#pragma once

#include <wx/wx.h>
#include <Ogre.h>

#include "OViSESceneHandling.h"

/** Class to handle input from the user for a render widget.
 * This calls handles all the keyboard and mouse input for a render widget. It is
 * mainly used for navigation in 3D and object selection.
 */
class OViSEInputHandler
{
public:
	/** Constructor with camera and camera node.
	 * The class needs at least a camera. If you provide a camera node as well, make sure that
	 * you have a camera focus node which has a childnode. The camera shall then be attached to
	 * the latter. This way you can have a orbiting camera.
	 */
	OViSEInputHandler(Ogre::Camera *cam, Ogre::SceneNode *camnode, wxWindow *parent);
	~OViSEInputHandler(void);

	/// Handles all mouse input and calls appropriate methods.
	void handleMouseInput(wxMouseEvent& evt);
	/// Handles all keyboard input and calls appropriate methods.
	void handleKeyboardInput(wxKeyEvent& evt);

	/// Set the camera manually.
	void setCamera(Ogre::Camera *cam, Ogre::SceneNode *camnode);

protected:
	/// Translate camera.
	void translateCamera(Ogre::Vector3 trans);
	/// Zoom camera (makes most sense when using a focusnode, see constructor documentation).
	void zoomCamera(double amount);
	/// Yaw camera.
	void yawCamera(Ogre::Radian angle);
	/// Pitch camera.
	void pitchCamera(Ogre::Radian angle);

	/** Focuses the camera on the currently selected objects. 
	 * @todo Check that all selected objects are visible
	 * @todo Make smooth animation for camera change?
	 */
	void focusCamera();

private:
	Ogre::Camera *mCamera;
	Ogre::SceneNode *mCameraNode;
	wxWindow *mParent;

	/// Mouse position of last click.
	int mX, mY;
	/// Default move and rotate speeds.
	double mRotateSpeed, mMoveSpeed;
	bool mRightMouseDown, mMouseCaptured;

};
