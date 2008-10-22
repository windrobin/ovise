#pragma once

#include <wx/wx.h>
#include <Ogre.h>

class OViSEInputHandler
{
public:
	OViSEInputHandler(Ogre::Camera *cam);
	~OViSEInputHandler(void);

	void handleMouseInput(wxMouseEvent& evt);
	void handleKeyboardInput(wxKeyEvent& evt);

	void setCamera(Ogre::Camera *cam);

private:
	Ogre::Camera *mCamera;

	// Mouse position of last click
	int mX, mY;
	double mRotateSpeed, mMoveSpeed;
	bool mRightMouseDown;

};
