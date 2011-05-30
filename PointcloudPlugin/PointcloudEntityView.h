
#ifndef POINTCLOUD_ENTITY_VIEW_H
#define POINTCLOUD_ENTITY_VIEW_H

#include <boost/scoped_ptr.hpp>
#include "../Core/SceneView.h"
#include "Pointcloud.h"

class PointcloudEntityView :
	public BasicOgreEntityView
{
public:
	PointcloudEntityView( Entity* Object, Ogre::SceneManager* Mgr );
	~PointcloudEntityView();

	void OnEntityAttributeChanged( Entity* Rhs, const std::string& Name, 
		const EntityVariantType* Attribute );

private:
	Ogre::SceneNode* mNode;
	Ogre::Entity*    mOgreEntity;

	boost::scoped_ptr<CPointcloud> mPointCloud;

	void LoadFromFileOFF( const std::string& Filename, 
		float r = 1.f, float g = 1.f, float b = 1.f );
	void LoadFromFilePLY( const std::string& Filename );
};

#endif
