
#include "EntityPool.h"
#include <boost/foreach.hpp>

void RemoveEntityById( EntityPool* Pool, const int Id )
{
	Pool->RemoveEntity( Pool->GetEntityById( Id ) );
}

EntityPoolObserver::EntityPoolObserver()
{}

EntityPoolObserver::~EntityPoolObserver()
{}

EntityPool::EntityPool() : mNextId( 1 )
{}

EntityPool::~EntityPool()
{
	BOOST_FOREACH( Entity * x, mData )
	delete x;
}

Entity* EntityPool::InsertEntity( Entity* Rhs )
{
	// set the ID of the Entity
	Rhs->SetId( mNextId++ );

	// Insert and record the position
	std::size_t Position = mData.size();
	mData.push_back( Rhs );

	// Notify the observers
	BOOST_FOREACH( EntityPoolObserver * x, mObserver )
	x->OnEntityInsert( Rhs,Position );

	return Rhs;
}

void EntityPool::RemoveEntity( Entity* Rhs )
{
	// Ignore NULL
	if ( !Rhs )
		return;

	// Find the entity
	std::vector<Entity*>::iterator Index =
	        std::find( mData.begin(), mData.end(), Rhs );

	BOOST_ASSERT( Index != mData.end() );

	std::size_t Position = Index - mData.begin();
	mData.erase( Index );

	// Notify the observers
	BOOST_FOREACH( EntityPoolObserver * x, mObserver )
	x->OnEntityRemove( Rhs, Position );
	
	delete Rhs;
}

Entity* EntityPool::GetEntityById( int Id )
{
	Entity* E = NULL;

	// find the Entity and return it
	BOOST_FOREACH( E, mData )
	{
		if ( E->GetId() == Id )
			return E;
	}

	return NULL;
}

Entity* EntityPool::GetEntityByName( const std::string& Name )
{
	Entity* E = NULL;

	BOOST_FOREACH( E, mData )
	{
		if( E->GetName() == Name )
			return E;
	}

	return NULL;
}

Entity* EntityPool::GetEntityByOgreEntity( Ogre::Entity* OgreEnt )
{
	if( OgreEnt == NULL )
		return NULL;

	Entity* E = NULL;

	BOOST_FOREACH( E, mData )
	{
		if( E->GetOgreEntity() == OgreEnt )
			return E;
	}

	return NULL;
}

void EntityPool::InsertObserver( EntityPoolObserver* Rhs )
{
	mObserver.insert( Rhs );

	BOOST_FOREACH( Entity * x, mData )
	{
		std::vector<Entity*>::iterator i =
		        std::find( mData.begin(), mData.end(), x );
		Rhs->OnEntityInsert( x,i - mData.begin());
	}
}

void EntityPool::RemoveObserver( EntityPoolObserver* Rhs )
{
	BOOST_FOREACH( Entity * x, mData )
	{
		std::vector<Entity*>::iterator i =
		        std::find( mData.begin(), mData.end(), x );
		Rhs->OnEntityRemove( x,i - mData.begin());
	}

	mObserver.erase( Rhs );
}

std::vector< std::string > EntityPool::GetEntityNames() const
{
	std::vector< std::string > res;
	Entity* E = NULL;

	BOOST_FOREACH(E, mData)
	{
		res.push_back(E->GetName());
	}

	return res;
}

int EntityPool::RemoveEntitiesByAttribute( const std::string& Attribute )
{
	std::vector<int> Ids;
	Entity*          E = NULL;

	BOOST_FOREACH( E, mData )
	{
		const EntityVariantType* A = E->GetAttribute( Attribute );
		if( A )
			Ids.push_back( E->GetId() );
	}

	for( std::vector<int>::iterator i = Ids.begin(); i != Ids.end(); i++ )
		RemoveEntity( GetEntityById( *i ) );

	return int( Ids.size() );
}
