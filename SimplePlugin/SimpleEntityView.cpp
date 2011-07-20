
#include "SimpleEntityView.h"
#include <boost/lexical_cast.hpp>

#include "../Util/PluginManager.h"

SimpleEntityView::SimpleEntityView( Entity* Object, Ogre::SceneManager* Mgr ) 
	: BasicOgreEntityView( Object,Mgr ), mNode( 0 ), mOgreEntity( 0 )
{
	mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();

	SyncAttribs( this );
}

SimpleEntityView::~SimpleEntityView()
{
	// detach the scene node and delete it
	mNode->detachObject( mOgreEntity );
	GetSceneManager()->getRootSceneNode()->removeChild( mNode );
	GetSceneManager()->destroySceneNode( mNode );

	// entity is now detached - delete it
	GetSceneManager()->destroyEntity( mOgreEntity );
}

void SimpleEntityView::OnEntityAttributeChanged(
        Entity*                  Rhs,
        const std::string&       Name,
        const EntityVariantType* Attribute
        )
{
	if ( Name == "Position" )
	{
		// Set the position, if it is available
		if ( const vec3 * Data = boost::get<vec3>( Attribute ) )
			mNode->setPosition( *Data );
	}
	else if ( Name == "Orientation" )
	{
		// Set the orientation, if it is available
		if ( const quat * Data = boost::get<quat>( Attribute ) )
			mNode->setOrientation( *Data );
		else if( const vec4 * Data = boost::get<vec4>( Attribute ) )
			mNode->setOrientation( Data->w,
			Data->x, Data->y, Data->z );
	}
	else if ( Name == "Scale" )
	{
		// Set the scale, if it is available
		if ( const vec3 * Data = boost::get<vec3>( Attribute ) )
			mNode->setScale( *Data );
	}
	else if ( Name == "Model" )
	{
		// Try to retrieve a model name
		const std::string* ModelName = boost::get<std::string>(
		        GetDataEntity()->GetAttribute( "Model" ) );

		if ( mOgreEntity )
		{
			mNode->detachObject( mOgreEntity );
			GetSceneManager()->destroyEntity( mOgreEntity );
			mOgreEntity = 0;
			Rhs->SetOgreEntity( NULL );
		}

		// Generate a name for the (OViSE) entity pointer
		const std::string EntityName = "Entity:" +
		                               boost::lexical_cast<std::string>(
		        GetDataEntity() );

		if ( ModelName )
		{
			if( Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup( *ModelName ) )
			{
				mOgreEntity = GetSceneManager()->createEntity( EntityName, *ModelName );
			}
			else
			{
				mOgreEntity = GetSceneManager()->createEntity( EntityName, "Unknown.mesh" );
			}
		}
		else
			mOgreEntity = GetSceneManager()->createEntity( EntityName,
			Ogre::SceneManager::PT_CUBE );

		mNode->attachObject( mOgreEntity );
		Rhs->SetOgreEntity( mOgreEntity );
	}
}

/** \note This has to be defined as a C function to prevent name mangling.
 */
extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterVisualPlugin<SimpleEntityView>( "Simple" );
}
