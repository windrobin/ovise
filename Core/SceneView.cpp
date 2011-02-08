#include "SceneView.h"
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#if BOOST_VERSION < 104300
# if BOOST_VERSION < 104200
#  define quick_erase erase
# else
#  define quick_erase erase_return_void
# endif
#endif

namespace
{
	// This is the name of the attribute that is scanned to associated views
	std::string TypeString="Type";
}

SceneView::SceneView( Ogre::SceneManager *    SceneMgr,
                      boost::function<void()> UpdateScreen )
	: mSceneManager( SceneMgr ), mUpdateScreen( UpdateScreen )
{}

SceneView::~SceneView()
{
	typedef ViewHashType::value_type PairType;

	// Delete all entity views
	BOOST_FOREACH( PairType & x, mViews )
	{
		AbstractOgreEntityView* View( x.second.View );

		// View->Remove( mSceneManager );
		delete View;
	}
}

void SceneView::AssociateFactory( const std::string &    Typename,
                                  SceneView::FactoryType Factory )
{
	// FIXME: check whether this is already set and react to it?

	mFactories[Typename] = Factory;
}

void SceneView::OnEntityInsert( Entity* Object, std::size_t Index )
{
	OnTypeChanged( Object,Object->GetAttribute( TypeString ));
	Object->InsertObserver( this );
}

void SceneView::OnEntityRemove( Entity* Object, std::size_t Index )
{
	// Find an entry
	ViewHashType::iterator HashEntry = mViews.find( Object );

	if ( HashEntry != mViews.end() )
	{
		ViewEntry& Ve = HashEntry->second;
		delete Ve.View;

		mViews.quick_erase( HashEntry );
	}

	Object->RemoveObserver( this );
	mUpdateScreen();
}

void SceneView::OnTypeChanged( Entity*                  Object,
                               const EntityVariantType* Attribute )
{
	// lock the entity
	// boost::lock_guard<boost::mutex> lock(Object->mutex);

	// First check whether the 'type' attribute is set
	const std::string* TypeString = boost::get<std::string>( Attribute );

	// Find an entry
	ViewHashType::iterator HashEntry = mViews.find( Object );

	// Check for modifications of the type string tag
	if ( !TypeString )
	{
		if ( HashEntry == mViews.end() )
		{
			// First time and no type string set - do nothing
		}
		else
		{
			// Type string removed - We need to make sure no view is set.
			delete HashEntry->second.View;
			mViews.quick_erase( HashEntry );
		}
	}
	else
	{
		if ( HashEntry == mViews.end() )
		{
			// Add
			ViewEntry& Ve =
			        mViews.insert( std::make_pair( Object,
						ViewEntry() ) ).first->second;
			Ve.CachedType = *TypeString;

			std::map<std::string,
			         FactoryType>::const_iterator FactoryIterator =
			        mFactories.find( *TypeString );

			if ( FactoryIterator != mFactories.end() )
			{
				Ve.View = FactoryIterator->second( Object,
					mSceneManager );
			}
		}
		else
		{
			// Change
			ViewEntry& Ve = HashEntry->second;

			if ( Ve.CachedType == *TypeString )
				// Object->mutex.unlock();
				return;

			// Remove the old view
			delete Ve.View;
			Ve.View = 0;

			// Add a new view
			std::map<std::string,
			         FactoryType>::const_iterator FactoryIterator =
			        mFactories.find( *TypeString );

			if ( FactoryIterator != mFactories.end() )
			{
				Ve.View = FactoryIterator->second( Object,
					mSceneManager );
			}

			Ve.CachedType = *TypeString;
		}
	}
	// unlock the entity
	// Object->mutex.unlock();
}

void SceneView::OnEntityAttributeChanged(
        Entity*                  Rhs,
        const std::string&       Name,
        const EntityVariantType* Attribute
        )
{
	mUpdateScreen();

	// We only care about changes to the 'Type' string from here on
	if ( Name != TypeString )
		return;

	OnTypeChanged( Rhs,Attribute );
}
