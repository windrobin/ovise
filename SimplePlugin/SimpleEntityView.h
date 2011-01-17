
#ifndef SIMPLE_ENTITY_VIEW_H
#define SIMPLE_ENTITY_VIEW_H

#include "../Core/SceneView.h"

/** View for a simple entity with a model and a position.
*/
class SimpleEntityView :
	public BasicOgreEntityView
{
public:
	SimpleEntityView( Entity* Object, Ogre::SceneManager* Mgr );
	~SimpleEntityView();

	void				OnEntityAttributeChanged( Entity* Rhs, const std::string& Name,
								const EntityVariantType* Attribute );


private:
	Ogre::SceneNode*	mNode;
	Ogre::Entity*		mOgreEntity;
};


#endif // SIMPLE_ENTITY_VIEW_H
