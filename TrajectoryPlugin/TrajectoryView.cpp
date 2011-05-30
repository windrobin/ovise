#include "TrajectoryView.h"

TrajectoryView::TrajectoryView( Entity* Object, Ogre::SceneManager* Mgr ) :
	BasicOgreEntityView( Object,Mgr ),
	mNode( 0 )
{
	mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();

	SyncAttribs( this );
}

TrajectoryView::~TrajectoryView()
{
	if( mTrajectory )
	{
		mNode->detachAllObjects();
		mTrajectory.reset();
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
	else if ( Name == "Points" )
	{
		const boost::any* PAny = boost::get<boost::any>( Attribute );
		try
		{
			const std::vector<Ogre::Vector3>& Points = 
				boost::any_cast<std::vector<Ogre::Vector3> >( *PAny );

			if( !mTrajectory )
				mTrajectory.reset( new CTrajectory( GetSceneManager(), Points ) );

			mNode->attachObject( mTrajectory->GetManualObject() );
		}
		catch( const boost::bad_any_cast& e )
		{}
	}
}


/** \note This has to be defined as a C function to prevent name mangling.
 */
extern "C" OVISE_DLLAPI
void LoadEntityView( SceneView& View )
{
	View.RegisterView<TrajectoryView>( "Trajectory" );
}
