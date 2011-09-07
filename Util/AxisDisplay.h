#ifndef OVISE_AXIS_DISPLAY_H
#define OVISE_AXIS_DISPLAY_H

#include <OGRE/Ogre.h>

class CAxisDisplay
{
public:
	CAxisDisplay( Ogre::SceneManager* SM );
	~CAxisDisplay(void);

	void ShowXAxis( bool enable );
	void ShowYAxis( bool enable );
	void ShowZAxis( bool enable );

	void Disable();

	void SetPosition( const Ogre::Vector3& pos );
	void SetOrientation( const Ogre::Quaternion& quat );

	void Attach( Ogre::SceneNode* node );

private:
	Ogre::SceneNode*		AttachNode;
	Ogre::ManualObject*		xAxis;
	Ogre::ManualObject*		yAxis;
	Ogre::ManualObject*		zAxis;
};

#endif // OVISE_AXIS_DISPLAY_H
