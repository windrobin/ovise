
#ifndef ROBOT_ENTITY_VIEW_H
#define ROBOT_ENTITY_VIEW_H

#include "../Core/SceneView.h"

/**
  Specialized visualization for robots.
*/
class RobotEntityView :
	public BasicOgreEntityView
{
public:
	RobotEntityView( Entity* Object, Ogre::SceneManager* Mgr );
	void Remove( Ogre::SceneManager* Mgr );
	void OnEntityChanged( Entity* Rhs );
	void OnEntityAttributeChanged( Entity* Rhs, const std::string& Name,
		const EntityVariantType* Attribute );

	~RobotEntityView();

private:
	Entity* mDataEntity;

	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode*    mNode;
	Ogre::Entity*       mOgreEntity;
};

#endif
