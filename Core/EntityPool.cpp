
#include "EntityPool.h"
#include <boost/foreach.hpp>

EntityPoolObserver::EntityPoolObserver()
{
}

EntityPoolObserver::~EntityPoolObserver()
{
}

EntityPool::EntityPool() : nextId(1)
{
}

EntityPool::~EntityPool()
{
	BOOST_FOREACH( Entity* x, mData )
		delete x;
}

Entity* EntityPool::InsertEntity( Entity* Rhs )
{

	mutex.lock();

	//set the ID of the Entity
	Rhs->SetId(nextId++);

	// Insert and record the position
	std::size_t Position = mData.size();
	mData.push_back(Rhs);

	// Notify the observers
	BOOST_FOREACH( EntityPoolObserver* x, mObserver )
		x->OnEntityInsert(Rhs,Position);

	mutex.unlock();

	return Rhs;
}

void EntityPool::RemoveEntity( Entity* Rhs )
{
	// Ignore NULL
	if ( !Rhs )
		return;

	mutex.lock();

	// Find the entity
	std::vector<Entity*>::iterator Index =
		std::find( mData.begin(), mData.end(), Rhs );

	BOOST_ASSERT( Index != mData.end() );

	std::size_t Position = Index-mData.begin();
	mData.erase( Index );

	// Notify the observers
	BOOST_FOREACH( EntityPoolObserver* x, mObserver )
		x->OnEntityRemove( Rhs, Position );


	delete Rhs;

	mutex.unlock();
}

void EntityPool::RemoveEntityById( int id )
{
    this->RemoveEntity(this->GetEntityById(id));
}

Entity* EntityPool::GetEntityById( int id ) {
    mutex.lock();
    Entity* cEntity;

    //find the Entity and return it
    BOOST_FOREACH( cEntity, mData ) {
        if (cEntity->GetId() == id) {
            mutex.unlock();
            std::cout << "Found the entity with given id" << std::endl;
            return cEntity;
        }
        std::cout << cEntity->GetId() << std::endl;

    }
    std::cout << "Entity with given ID not found!" << std::endl;
    //if not found, return a empty entity
    //TODO: think about semantics of this entity (adding it to the pool, setting the id, ...)
    cEntity = new Entity();
    mutex.unlock();
    return cEntity;





}

void EntityPool::InsertObserver( EntityPoolObserver* Rhs )
{
	mObserver.insert( Rhs );

	BOOST_FOREACH( Entity* x, mData )
	{
		std::vector<Entity*>::iterator i =
			std::find( mData.begin(), mData.end(), x );
		Rhs->OnEntityInsert(x,i-mData.begin());
	}
}

void EntityPool::RemoveObserver( EntityPoolObserver* Rhs )
{
	BOOST_FOREACH( Entity* x, mData )
	{
		std::vector<Entity*>::iterator i =
			std::find( mData.begin(), mData.end(), x );
		Rhs->OnEntityRemove(x,i-mData.begin());
	}

	mObserver.erase( Rhs );
}
