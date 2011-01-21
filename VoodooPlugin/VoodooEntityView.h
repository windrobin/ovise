
#ifndef ROBOT_ENTITY_VIEW_H
#define ROBOT_ENTITY_VIEW_H

#include "../Core/SceneView.h"

class VoodooEntityView :
	public BasicOgreEntityView
{
public:
						VoodooEntityView( Entity* Object, Ogre::SceneManager* Mgr );
	void				Remove( Ogre::SceneManager* Mgr );
	void				OnEntityChanged( Entity* Rhs );
	void				OnEntityAttributeChanged( Entity* Rhs,	const std::string& Name, const EntityVariantType* Attribute );

						~VoodooEntityView();

private:
	Entity*				mDataEntity;

	Ogre::SceneManager*	mSceneManager;
	Ogre::SceneNode*	mNode;
	Ogre::Entity*		mOgreEntity;
};

#endif
