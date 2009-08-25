#pragma once

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

#ifndef OGRE_FONTMANAGER_USED
#define OGRE_FONTMANAGER_USED
#include <OgreFontManager.h>
#endif

/** Class for displaying object titles as 2D text in 3D.
 * @remark This class is taken out of the OgreWiki at http://www.ogre3d.org/wiki/index.php/ObjectTitle
 */
class OViSEObjectTitle
{
private:
	const Ogre::MovableObject* object;
	const Ogre::Camera* camera;
	Ogre::Overlay* overlay;
	Ogre::OverlayElement* textArea;
	Ogre::OverlayContainer* container;
	Ogre::Vector2 textDim;
	Ogre::Font* font;

	Ogre::Vector2 getTextDimensions(Ogre::String text);

public:
	OViSEObjectTitle(const Ogre::String& name, Ogre::MovableObject* object, Ogre::Camera* camera, const Ogre::String& title,
		const Ogre::String& fontName, const Ogre::ColourValue& color = Ogre::ColourValue::White);
	~OViSEObjectTitle(void);

	void setTitle(const Ogre::String& title);

	void update();
};
