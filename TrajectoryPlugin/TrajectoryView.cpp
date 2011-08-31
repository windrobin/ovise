#include "TrajectoryView.h"

#include "../Util/PluginManager.h"

TrajectoryView::TrajectoryView( Entity* Object, Ogre::SceneManager* Mgr ) :
	BasicOgreEntityView( Object,Mgr ),
	mNode( 0 )
{
	mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();

	mTrajectory.reset( new CTrajectory( GetSceneManager() ) );

	SyncAttribs( this );
}

TrajectoryView::~TrajectoryView()
{
	if( mTrajectory )
	{
		mNode->detachAllObjects();
	}
	GetSceneManager()->getRootSceneNode()->removeChild( mNode );
}

void TrajectoryView::OnEntityAttributeChanged( Entity* Rhs,
	const std::string& Name,const EntityVariantType* Attribute )
{
	if ( Name == "Position" )
	{
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mNode->setPosition( *Data );
	}
	else if ( Name == "Orientation" )
	{
		const quat* Data = boost::get<quat>( Attribute );

		if( Data )
			mNode->setOrientation( *Data );
	}
	else if ( Name == "Scale" )
	{
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mNode->setScale( *Data );
	}
	else if ( Name == "Color" )
	{
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mTrajectory->SetColour( Ogre::ColourValue( Data->x, Data->y, Data->z ) );
	}
	else if ( Name == "PointSize" )
	{
		const double* Data = boost::get<double>( Attribute );

		if ( Data )
			mTrajectory->SetPointSize( float(*Data) );
	}
	else if ( Name == "Points" )
	{
		const boost::any* PAny = boost::get<boost::any>( Attribute );
		try
		{
			const std::vector<Ogre::Vector3>& Points = 
				boost::any_cast<std::vector<Ogre::Vector3> >( *PAny );

			if( mTrajectory )
				mNode->detachObject( mTrajectory->GetManualObject() );

			mTrajectory.reset( new CTrajectory( GetSceneManager(), Points ) );

			mNode->attachObject( mTrajectory->GetManualObject() );
		}
		catch( const boost::bad_any_cast & )
		{}
	}
}


/** \note This has to be defined as a C function to prevent name mangling.
 */
extern "C" OVISE_PLUGIN_API
void InitPlugin( CPluginManager& PluginManager )
{
	PluginManager.RegisterVisualPlugin<TrajectoryView>( "Trajectory" );
}
