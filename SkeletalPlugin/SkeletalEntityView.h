
#ifndef SKELETAL_ENTITY_VIEW_H
#define SKELETAL_ENTITY_VIEW_H

#include "../Core/SceneView.h"

/**
  Specialized visualization for robots.
*/
class SkeletalEntityView :
	public BasicOgreEntityView
{
public:
	SkeletalEntityView( Entity* Object, Ogre::SceneManager* Mgr );
	void Remove( Ogre::SceneManager* Mgr );
	void OnEntityChanged( Entity* Rhs );
	void OnEntityAttributeChanged( Entity* Rhs, const std::string& Name,
		const EntityVariantType* Attribute );

	~SkeletalEntityView();

private:
	Entity* mDataEntity;

	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode*    mNode;
	Ogre::Entity*       mOgreEntity;
};

#endif
