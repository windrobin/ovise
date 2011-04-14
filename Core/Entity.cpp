
#include "Entity.h"
#include <boost/foreach.hpp>

Entity::Entity()
	: Id( -1 )
{}

Entity::Entity( const std::string& Name )
	: Name( Name ), Id( -1 )
{}

Entity::Entity( int id )
	: Id( id )
{}

Entity::Entity( const std::string& Name, int id )
	: Name( Name ), Id( id )
{}

Entity::~Entity()
{}

void Entity::SetName( const std::string& Rhs )
{
	if ( this->Name == Rhs )
		return;

	this->Name = Rhs;

	BOOST_FOREACH( EntityObserver * x, Observer )
	x->OnEntityNameChanged( this );
}

void Entity::SetId( int newId )
{
	this->Id = newId;
}

void Entity::SetAttribute( const std::string& Name, const VariantType& Rhs )
{
	VariantType& Attrib=Attribute[Name];
	Attrib=Rhs;
	Changed( Name,&Attrib );
}

const Entity::VariantType* Entity::GetAttribute( const std::string& Name )
const
{
	AttributeType::const_iterator Node = Attribute.find( Name );

	if ( Node == Attribute.end() )
		return 0;
	else
		return &Node->second;
}

void Entity::Changed( const std::string& Name, const VariantType* Attrib )
{
	BOOST_FOREACH( EntityObserver * x, Observer )
	x->OnEntityAttributeChanged( this, Name, Attrib );
}

bool Entity::RemoveAttribute( const std::string& Name )
{
	AttributeType::iterator Node = Attribute.find( Name );

	if ( Node == Attribute.end() )
		return false;

	Attribute.erase( Node );
	this->Changed( Name,0 );
	return true;
}
