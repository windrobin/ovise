#include "SocketMessage.h"

#include <wx/tokenzr.h>
#include <boost/lexical_cast.hpp>

SocketMessage::SocketMessage(void)
{
}

SocketMessage::~SocketMessage(void)
{
}

void SocketMessage::ConnectEntityPool(EntityPool* Pool) 
{
	mEntityPool = Pool;
}


int SocketMessage::HandleMessage(const char* Message) 
{
	mDocument.parse<0>( const_cast<char*>( Message ) );
	std::cout << "Socket Message Handling:" << std::endl;

	rapidxml::xml_node<>* RootNode = mDocument.first_node();
	if( !RootNode )
		return -1;
	rapidxml::xml_attribute<>* Operation = RootNode->first_attribute( "action" );
	if( !Operation )
		return -1;
	std::string OpStr( Operation->value() );
	if ( OpStr == "insert" ) 
	{
		return HandleInsert(root);
	} 
	else if ( OpStr == "update" ) 
	{
		rapidxml::xml_node<>* EntityNode = RootNode->first_node( "Id" );
		if( !EntityNode )
			return -1;

		HandleUpdate( EntityNode, mEntityPool->GetEntityById( 
			boost::lexical_cast<int>( EntityNode->value() ) ) );
	} 
	else if ( OpStr == "delete" ) 
	{
		rapidxml::xml_node<>* EntityNode = RootNode->first_node( "Id" );
		if( !EntityNode )
			return -1;
		
		RemoveEntityById( mEntityPool, 
			boost::lexical_cast<int>( EntityNode->value() ) );
	}
}


/* peform the adding of a new entity to the entity pool
*/
int SocketMessage::HandleInsert( rapidxml::xml_node<>* Node ) 
{
	//add the new entity to the pool
	rapidxml::xml_node<>* NameNode = Node->first_node( "Name" );
	if( !NameNode )
		return -1;

	//extract attributes
	rapidxml::xml_node<>* AttributesNode = Node->first_node( "Attributes" );
	if( !AttributesNode )
		return -1;
	
	//create the Entity
	Entity& NewEntity = mEntityPool->CreateEntity( std::string( NameNode->value() ) );

	
	if( !HandleUpdate( AttributesNode, &NewEntity ) )
	{
		mEntityPool->RemoveEntity( &NewEntity );
		return -1;
	}

	return NewEntity.GetId();
}

// perform update of an existing entity
bool SocketMessage::HandleUpdate( rapidxml::xml_node<>* AttributeList, Entity* Rhs) 
{
	for( rapidxml::xml_node<>* Child = AttributeList->first_node(); ; Child = Child->next_sibling() ) 
	{
		rapidxml::xml_attribute<>* Name = Child->first_attribute( "name" );
		rapidxml::xml_attribute<>* Type = Child->first_attribute( "type" );
		if( Name && Type ) 
		{
			std::string NameStr( Name->value() );
			std::string TypeStr( Type->value() );
			std::string ValueStr( Child->value() );
			if( TypeStr == "vec3" )
			{
				//input of position types
				double pos[3];
				wxStringTokenizer Tokenizer( ValueStr, "," );
				for (int i = 0; i < 3; i++) 
				{
					Tokenizer.GetNextToken().ToDouble( &pos[i] );
				}
				Rhs->Set<vec3>( NameStr, vec3( pos[0], pos[1], pos[2] ));
			} 
			else if ( TypeStr == "int" ) 
			{
				//input of integers
				Rhs->Set<int>( NameStr, boost::lexical_cast<int>( ValueStr ) );
			} 
			else if( TypeStr == "double" ) 
			{
				//input of floating numbers
				Rhs->Set<double>( NameStr, boost::lexical_cast<double>( ValueStr ) );
			} 
			else 
			{
				//standard is string
				Rhs->Set<std::string>( NameStr, ValueStr );
			}
		}
		else
			return false;
	}
	return true;
}

// perform update of an existing entity
void SocketMessage::HandleDelete() 
{
}

