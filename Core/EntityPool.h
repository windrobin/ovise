
#ifndef OVISE_ENTITY_POOL_H
#define OVISE_ENTITY_POOL_H

#include <vector>
#include <set>
#include "Entity.h"

/** Abstract observer for an entity pool.
*/
class EntityPoolObserver
{
public:
	EntityPoolObserver();
	virtual ~EntityPoolObserver();

	virtual void					OnEntityInsert( Entity* Object, std::size_t Index ) = 0;
	virtual void					OnEntityRemove( Entity* Object, std::size_t Index ) = 0;

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
	Entity*							InsertEntity( Entity* Rhs );

	/** Create an entity.
		This is a convenicence function that uses InsertEntity internally.
	*/
	inline Entity&					CreateEntity( const std::string& Name )
	{
		return *InsertEntity( new Entity(Name) );
	}


	/** Remove an entity from the pool.
		Will also delete the entity.
	*/
	void							RemoveEntity( Entity* Rhs );

	Entity*                         GetEntityById( int id );

	void							InsertObserver( EntityPoolObserver* Rhs );
	void							RemoveObserver( EntityPoolObserver* Rhs );

private:
	std::vector<Entity*>			mData;
	int                             mNextId;
	std::set<EntityPoolObserver*>	mObserver;
};

void RemoveEntityById( EntityPool* Pool, const int Id );

#endif
