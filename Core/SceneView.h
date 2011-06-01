
#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>

#include <Ogre.h>
#include "../Core/EntityPool.h"

/** 
  Interface to handle specific types of entities.
  Is set according to the 'Type' variable.

  Derived classes are instanciated by a factory:
  their constructor must take the Entity and the Ogre::SceneManager.
  \see SceneView::FactoryType
  \see BasicOgreEntityView
*/
class AbstractOgreEntityView :
	public boost::noncopyable
{
public:
	AbstractOgreEntityView() {}
	virtual ~AbstractOgreEntityView() {}
};

/** Abstract convenience class that implements some basic bootstrapping for an entity view.
        It is generally preferable to implement views using this instead of AbstractOgreEntityView.
        It derives from EntityObserver, but keeps its interface unimplemented.
 */
class BasicOgreEntityView :
	public AbstractOgreEntityView,
	public EntityObserver
{
public:
	/** This constructor will automatically observe the DataEntity given in the constructor.
	        The DataEntity is stored and can be accessed using GetDataEntity().
	        Also, it will store the SceneManager given in the constructor, which is accessible through GetSceneManager().
	        \param DataEntity The entity to be stored and observed.
	        \param SceneManager The scene manager associated with this view.
	 */
	BasicOgreEntityView( Entity* DataEntity, Ogre::SceneManager* SceneManager )
		: mSceneManager( SceneManager ), mDataEntity( DataEntity )
	{
		mDataEntity->InsertObserver( this );
	}

	~BasicOgreEntityView() { mDataEntity->RemoveObserver( this ); }

	Ogre::SceneManager* GetSceneManager() {	return mSceneManager; }
	Entity* GetDataEntity() { return mDataEntity; }

private:
	Ogre::SceneManager* mSceneManager;
	Entity*             mDataEntity;
};

/** 
  Convenience function that calls the attribute change handler for all attributes in the entity.
  This is useful after insertion of the view.
*/
template < class T >
void SyncAttribs( T* BasicEntityView )
{
	// FIXME: check that this is actually convertible to a basic entity view?

	const Entity::AttributeType& Table=
	        BasicEntityView->GetDataEntity()->GetAttributes();
	typedef Entity::AttributeType::const_iterator iterator;

	// Sync all attributes
	for (iterator i=Table.begin(); i!=Table.end(); ++i )
	{
		BasicEntityView->OnEntityAttributeChanged(
			BasicEntityView->GetDataEntity(),
			i->first,
			&i->second );
	}
}

/** Observes the entity pool and contructs an Ogre3D scene from it.
 */
class SceneView :
	public EntityPoolObserver,
	public EntityObserver
{
public:
	typedef AbstractOgreEntityView Node;
	typedef boost::function<Node*( Entity* Object, Ogre::SceneManager* Mgr )> FactoryType;

	template <typename T>
	struct SimpleFactoryType
	{
		T* operator()( Entity* Object, Ogre::SceneManager* Mgr ) 
		{
			return new T( Object,Mgr );
		}
	};

	SceneView( Ogre::SceneManager* SceneMgr, boost::function<void()> UpdateFunction );
	~SceneView();

	/** Associates a factory with a specific type string.
	        Entities with that type string are associated with an entity view generated from that factory.
	 */
	void AssociateFactory( const std::string& Typename, FactoryType Factory );

	/** Register an entity view type for a specific type string.
	        This uses AssociateFactory internally, but automatically constructs a factory for the given type.
	 */
	template < class EntityViewType > inline
	void RegisterView( const std::string& Typename )
	{
		AssociateFactory( Typename, SimpleFactoryType<EntityViewType>() );
	}

private:
	Ogre::SceneManager* mSceneManager;
	std::map<std::string, FactoryType>
	mFactories;

	struct ViewEntry
	{
		Node* View;
		std::string CachedType;

		ViewEntry() : View( 0 ) {}
	};
	typedef boost::unordered_map<Entity*,ViewEntry> ViewHashType;

	ViewHashType mViews;

	boost::function<void()> mUpdateScreen;

	virtual void OnEntityInsert( Entity* Object, std::size_t Index );
	virtual void OnEntityRemove( Entity* Object, std::size_t Index );

	virtual void OnEntityAttributeChanged( Entity* Rhs, 
		const std::string& Name, const EntityVariantType* Attribute );

	void OnTypeChanged( Entity* Rhs, const EntityVariantType* Attribute );
};

#endif // SCENEVIEW_H
