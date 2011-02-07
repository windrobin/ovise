
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include "VoodooEntityView.h"

VoodooEntityView::VoodooEntityView( Entity* Object, Ogre::SceneManager* Mgr )
	: BasicOgreEntityView( Object,Mgr ), mNode( 0 ), mOgreEntity( 0 )
{
	mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();

	// only if Model is set yet...
	if (Object->GetAttribute( "Model" ) != 0)
		OnEntityAttributeChanged( Object,"Model",
			Object->GetAttribute( "Model" ));
}

VoodooEntityView::~VoodooEntityView()
{
	// Remove entity (if we got one)
	if ( mOgreEntity )
	{
		mNode->detachObject( mOgreEntity );
		GetSceneManager()->destroyEntity( mOgreEntity );
		mOgreEntity=0;
	}
}

void VoodooEntityView::OnEntityAttributeChanged(
        Entity*                  Rhs,
        const std::string&       Name,
        const EntityVariantType* Attribute
        )
{
	if ( Name == "Position" )
	{
		// Set the position, if it is available
		const vec3* Data = boost::get<vec3>( Attribute );

		if ( Data )
			mNode->setPosition( *Data );
	}
	else if( Name == "Scale" )
	{
		// Set the scale, if it is available
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mNode->setScale( *Data );
	}
	else if ( Name == "Model" )
	{
		// Delete all old bone names
		if ( mOgreEntity )
		{
			typedef Ogre::SkeletonInstance::BoneIterator iterator;
			Ogre::SkeletonInstance* Skeleton=
			        mOgreEntity->getSkeleton();
			for ( iterator i=Skeleton->getBoneIterator();
			      i.hasMoreElements();
			      )
			{
				Ogre::Bone* Bone=i.getNext();
				GetDataEntity()->RemoveAttribute( Bone->getName());
			}

			mNode->detachObject( mOgreEntity );
			GetSceneManager()->destroyEntity( mOgreEntity );
			mOgreEntity=0;
		}



		const std::string* Data=boost::get<std::string>( Attribute );

		if (!Data)
			return;

		// Create and attach the model entity
		const std::string EntityName = "Entity:" +
		                               boost::lexical_cast<std::string>(
		        GetDataEntity() );
		mOgreEntity = GetSceneManager()->createEntity( EntityName,
			*Data );
		mNode->attachObject( mOgreEntity );

		// Get all bones as properties
		typedef Ogre::SkeletonInstance::BoneIterator iterator;
		Ogre::SkeletonInstance* Skeleton=mOgreEntity->getSkeleton();
		Skeleton->setBindingPose();
		for ( iterator i=Skeleton->getBoneIterator(); i.hasMoreElements(); )
		{
			Ogre::Bone* Bone=i.getNext();
			Bone->setManuallyControlled( true );
			const std::string Name=Bone->getName();

			const quat Val = Bone->getOrientation();

			// if this attribute has already a attribute, do not overwrite it and inform observers (to  get visualize the orientation here)
			if ( GetDataEntity()->GetAttribute( Name ) == 0 )
			{
				GetDataEntity()->Set<quat>( Name, Val );
			}
			else
			{
				GetDataEntity()->Changed( Name,
					GetDataEntity()->GetAttribute( Name ));
			}
		}
	}
	else if (Rhs->GetAttribute( "Model" ) != 0)
	{
		const Entity::AttributeType& Attributes=Rhs->GetAttributes();
		typedef Entity::AttributeType::value_type ValueType;

		// Check if this is an angle value and a bone of this name exists
		Ogre::SkeletonInstance* Skeleton=mOgreEntity->getSkeleton();
		const quat*             Val = boost::get<quat>( Attribute );

		if ( Val && Skeleton->hasBone( Name ) )
		{
			Ogre::Bone* Bone=Skeleton->getBone( Name );

			Ogre::Quaternion CorrectorX;
			CorrectorX.FromAngleAxis( Ogre::Radian( Ogre::Degree( -
						90 ) ), vec3( 1.f, 0.f, 0.f ) );
			Ogre::Quaternion CorrectorZ;
			CorrectorZ.FromAngleAxis( Ogre::Radian( Ogre::Degree(
						90 ) ), vec3( 0.f, 0.f, 1.f ) );

			Ogre::Quaternion Corrector = CorrectorX * CorrectorZ;

			Bone->setOrientation(
				Bone->getInitialOrientation() * Corrector *
				( *Val ) *
				Corrector.UnitInverse() );

			// FIXME: is this really needed?
			mOgreEntity->getAllAnimationStates()->_notifyDirty();
		}
	}
}

/** \note This has to be defined as a C function to prevent name mangling.
 */
extern "C" OVISE_DLLAPI
void LoadEntityView( SceneView& View )
{
	View.RegisterView<VoodooEntityView>( "VoodooDoll" );
}
