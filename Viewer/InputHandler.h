#ifndef INPUT_HANLDER_H
#define INPUT_HANDLER_H

// Include Ogre
#ifdef __APPLE__
#include <Ogre/Ogre.h>
#else
#include <Ogre.h>
#endif

// Include WX
#include <wx/wx.h>

#include <CCSCameraControlSystem.h>

#include <OViSEException.h>


/** Class to handle input from the user for a render widget.
 * This calls handles all the keyboard and mouse input for a render widget. It is
 * mainly used for navigation in 3D and object selection.
 */
class InputHandler
{
public:
	/** Constructor with camera control system and parent window.
	 * The received user input is forwarded to the camera control system.
	 */
	InputHandler( CCS::CameraControlSystem* CCS,
	              wxWindow *       parent );
	~InputHandler( void );

	/// Handles all mouse input and calls appropriate methods.
	void handleMouseInput( wxMouseEvent& evt );
	/// Handles all keyboard input and calls appropriate methods.
	void handleKeyboardInput( wxKeyEvent& evt );

protected:
	/// Show the help overlay
	void showHelpOverlay();

	void translateCamera( Ogre::Vector3 trans );
	void translateCameraHorizontal( int Delta );
	void translateCameraVertical( int Delta );

	/// Delete selected OgreObjects (and its childs)
	void DeleteSelectedObjects();

private:
	wxWindow *       mParent;
	CCS::CameraControlSystem* mCCS;

	/// Mouse position of last click.
	int mX, mY;
	/// Default move and rotate speeds.
	double mRotateSpeed, mMoveSpeed;
	bool   mMouseCaptured;
};
#endif // INPUT_HANDLER_H
