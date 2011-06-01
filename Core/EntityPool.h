
#ifndef OVISE_ENTITY_POOL_H
#define OVISE_ENTITY_POOL_H

#include <vector>
#include <set>

#include <boost/foreach.hpp>

#include "Entity.h"

/** Abstract observer for an entity pool.
 */
class EntityPoolObserver
{
public:
	EntityPoolObserver();
	virtual ~EntityPoolObserver();

	virtual void OnEntityInsert( Entity* Object, std::size_t Index ) = 0;
	virtual void OnEntityRemove( Entity* Object, std::size_t Index ) = 0;

private:
};

/** A sequence of entities.
 */
class EntityPool
{
public:
	EntityPool();
	~EntityPool();

	/** Insert an entity into the pool.
	        The pool takes memory ownership of the entity.
	        The next free ID is assigned to this Entity.
	        \returns The entity that was passed in.
	 */
	Entity* InsertEntity( Entity* Rhs );

	/** Create an entity.
	        This is a convenicence function that uses InsertEntity internally.
	 */
	inline Entity& CreateEntity( const std::string& Name )
	{
		return *InsertEntity( new Entity( Name ) );
	}


	/** Remove an entity from the pool.
	        Will also delete the entity.
	 */
	void RemoveEntity( Entity* Rhs );

	Entity* GetEntityById( int id );

	/// Returns first enitity with the given name
	Entity* GetEntityByName( const std::string& Name );

	template< typename T >
	Entity*	GetEntityByAttribute( std::string Attribute, const T& Value );

	template< typename T >
	int	RemoveEntitiesByAttributeValue( const std::string& Attribute, T& Value );

	int	RemoveEntitiesByAttribute( const std::string& Attribute );

	void InsertObserver( EntityPoolObserver* Rhs );
	void RemoveObserver( EntityPoolObserver* Rhs );

private:
	std::vector<Entity*>          mData;
	int                           mNextId;
	std::set<EntityPoolObserver*> mObserver;
};

template< typename T> inline
Entity* EntityPool::GetEntityByAttribute( std::string Attribute, const T& Value )
{
	Entity* E = NULL;

	BOOST_FOREACH( E, mData )
	{
		const EntityVariantType* A = E->GetAttribute( Attribute );
		if( A )
		{
			const T* V = boost::get<T>( A );
			if( V )
			{
				if( *V == Value )
					return E;
			}
		}
	}

	return NULL;
}

template< typename T > inline
int EntityPool::RemoveEntitiesByAttributeValue( const std::string& Attribute,
                                                T&                 Value )
{
	std::vector<int> Ids;
	Entity*          E = NULL;

	BOOST_FOREACH( E, mData )
	{
		const EntityVariantType* A = E->GetAttribute( Attribute );
		if( A )
		{
			const T* V = boost::get<T>( A );
			if( V )
			{
				if( *V == Value )
					Ids.push_back( E->GetId() );
			}
		}
	}

	for( std::vector<int>::iterator i = Ids.begin(); i != Ids.end(); i++ )
		RemoveEntity( GetEntityById( *i ) );

	return int( Ids.size() );
}

void RemoveEntityById( EntityPool* Pool, const int Id );

#endif
