
#ifndef OVISE_ENTITY_H
#define OVISE_ENTITY_H

#include <map>
#include <string>
#include <set>
#include <boost/variant.hpp>
#include <boost/any.hpp>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>

typedef Ogre::Vector2 vec2;
typedef Ogre::Vector3 vec3;
typedef Ogre::Vector4 vec4;
typedef Ogre::Quaternion quat;

#ifdef WIN32
#  define OVISE_DLLAPI __declspec(dllexport)
#else
#  define OVISE_DLLAPI
#endif

class Entity;
typedef boost::variant<int,double,vec2,vec3,vec4,quat,std::string,Entity*,boost::any> EntityVariantType;

/** Abstract observer for the entity type.
	The observer is supposed to be triggered for all attribute changes and a name change.
*/
class EntityObserver
{
public:
	virtual ~EntityObserver() {}

	/** This function is called on name changes.
		The basic implementation does nothing.
		\param Rhs The entity that was modified. Use Entity::GetName() to get the new name.
	*/
	virtual void OnEntityNameChanged( Entity* Rhs )
	{
	}

	/** This function is called on attribute changes.
		\param Rhs Is set to the entity that was changed. Useful when an observer is bound to more that one entity.
		\param Name The name of the attribute that was changed.
		\param Attribute The new value of the attribute that was changed. May be NULL only if the attribute was removed.
	*/
	virtual void OnEntityAttributeChanged(
		Entity* Rhs,
		const std::string& Name,
		const EntityVariantType* Attribute
	)=0;
};

/** Generic class to hold entity data.
	Most likely content types are packed in attributes of a variant data type,
	while other types are still supported via the boost.any member.
	The internal class SetterProxy makes it easy to set multiple attributes in code, for example:
	myEntity->Set(attrib1,value1)(attrib2,value2)(attrib3,value3);
	\fixme maybe Set needs to map more integer types to int (and perform range checks?)
*/
class Entity
{
public:
	typedef EntityVariantType					VariantType;
	typedef std::map<std::string,VariantType>	AttributeType;
	typedef AttributeType::value_type			ValueType;

	/** Proxy to simplify setting multiple attributes.
	*/
	class SetterProxy
	{
	public:
		inline SetterProxy(Entity* Owner) : Owner(Owner) {}

		template <class T> inline
		SetterProxy operator()( const std::string& Id, T Rhs )
		{
			Owner->Set( Id, Rhs );
			return *this;
		}
	private:
		Entity* Owner;
	};

	/** (Default-) construct an entity.
		Leaves the name uninitialized/empty. Hence using name constructor is usually preferable.
	*/
	Entity();

	/** Construct an entity with a given name.
	*/
	explicit Entity( const std::string& Name );

	/** Construct an entity with a given id.
	*/
	explicit Entity( const int id );

	/** Construct an entity with a given name and id.
	*/
	explicit Entity( const::std::string& name, const int id );

	/** Destruct an entity.
	*/
	~Entity();

	void InsertObserver( EntityObserver* Rhs )
	{
		Observer.insert( Rhs );
	}

	void RemoveObserver( EntityObserver* Rhs )
	{
		Observer.erase( Rhs );
	}

	/** Set an attribute value.
	*/
	template<typename T> inline
	SetterProxy Set( const std::string& Id, T Rhs )
	{
		VariantType& x(Attribute[Id]);
		x = Rhs;
		Changed(Id,&x);
		return SetterProxy(this);
	}

	/** Specialized attribute setting function for c-strings.
		Maps a c-string to an std::string.
	*/
	inline
	SetterProxy Set( const std::string& Id, const char* Rhs )
	{
		return Set<std::string>(Id,Rhs);
	}

	/** Get the name of this entity.
	*/
	inline const std::string&			GetName() const { return Name; }

	/** Get the Id of the Entity.
	*/
	inline const int			        GetId() const { return Id; }


	/** Set the ID of this entity.
		The ID should only be modified by the EntityPool. Changing the ID somewhere else could produce problems.
	*/
	void								SetId( int newId );


	/** Set the name of this entity.
		The name should usually be set using the constructor, but can be changed using this.
	*/
	void								SetName( const std::string& Rhs );

	const AttributeType&				GetAttributes() const { return Attribute; }

	/** Retrieve the variant type of an attribute.
	*/
	const VariantType*					GetAttribute( const std::string& Name ) const;

	/** Set the variant type of an attribute.
		\note This is mostly for very specific use - using Set is normally preferable.
	*/
	void								SetAttribute( const std::string& Name, const VariantType& Value );

	/** Remove an attribute from the entity.
		\returns true if the attribute was removed, false if it didn't exist.
	*/
	bool								RemoveAttribute( const std::string& Name );

	/** Notify all observers of a change.
	*/
	void								Changed(const std::string& Name, const VariantType* Attrib);


private:
	std::string							Name;
	int                                 Id;
	AttributeType						Attribute;

	std::set<EntityObserver*>			Observer;

};

#endif
