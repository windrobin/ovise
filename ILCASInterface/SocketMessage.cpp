#include "SocketMessage.h"

#include <wx/tokenzr.h>
#include <boost/lexical_cast.hpp>

SocketMessage::SocketMessage( EntityPool* EntPool )
	: mEntityPool( EntPool )
{}

SocketMessage::~SocketMessage( void )
{}

int SocketMessage::HandleMessage( const char* Message )
{
        std::cout << Message <<std::endl;
        mDocument.parse<0>( const_cast<char*>( Message ) );
	std::cout << "Socket Message Handling:" << std::endl;

	rapidxml::xml_node<>* RootNode = mDocument.first_node();
	if( !RootNode )
		return -1;

	rapidxml::xml_attribute<>* Operation = RootNode->first_attribute(
		"action" );
	if( !Operation )
		return -1;

	std::string OpStr( Operation->value() );
	if ( OpStr == "insert" )
	{
		return HandleInsert( RootNode );
	}
	else if ( OpStr == "update" )
	{
		rapidxml::xml_node<>* EntityNode = RootNode->first_node( "Id" );
		rapidxml::xml_node<>* NameNode = RootNode->first_node( "Name" );
		
		if( EntityNode )
		  HandleUpdate( EntityNode, mEntityPool->GetEntityById(
								       boost::lexical_cast<int>( EntityNode->value() ) ) );
		else if ( NameNode ) 
		  {
		    HandleUpdate( EntityNode, mEntityPool->GetEntityByName( NameNode->value() ) );
		    std::cout << "Updating ent by name" << std::endl;
		  }
	}
	else if ( OpStr == "delete" )
	{
		rapidxml::xml_node<>* IdNode = RootNode->first_node( "Id" );
		rapidxml::xml_node<>* NameNode = RootNode->first_node( "Name" );
		if( IdNode )
		  RemoveEntityById( mEntityPool,
				    boost::lexical_cast<int>( IdNode->value() ) );
		else if ( NameNode ) {

		  mEntityPool->RemoveEntity( mEntityPool->GetEntityByName( NameNode->value() )  );
		  std::cout << "Removing ent by name" << std::endl;
		}
	}
}


/* peform the adding of a new entity to the entity pool
 */
int SocketMessage::HandleInsert( rapidxml::xml_node<>* Node )
{
	// add the new entity to the pool
	rapidxml::xml_node<>* NameNode = Node->first_node( "Name" );
	if( !NameNode )
		return -1;

	// extract attributes
	rapidxml::xml_node<>* AttributesNode = Node->first_node( "Attributes" );
	if( !AttributesNode )
		return -1;

	// create the Entity
	Entity& NewEntity =
	        mEntityPool->CreateEntity( std::string( NameNode->value() ) );


	if( !HandleUpdate( AttributesNode, &NewEntity ) )
	{
	  //qmEntityPool->RemoveEntity( &NewEntity );
		return -1;
	}

	return NewEntity.GetId();
}

// perform update of an existing entity
bool SocketMessage::HandleUpdate( rapidxml::xml_node<>* AttributeList,
                                  Entity*               Rhs )
{
  for( rapidxml::xml_node<>* Child = AttributeList->first_node();
       ;
       Child = Child->next_sibling() )
    {
      if (Child) {
	
	std::cout << "looping" << std::endl;
	rapidxml::xml_attribute<>* Name = Child->first_attribute(
								 "name" );
	rapidxml::xml_attribute<>* Type = Child->first_attribute(
								 "type" );
	if( Name && Type )
	  {
	    std::string NameStr( Name->value() );
	    std::string TypeStr( Type->value() );
	    std::string ValueStr( Child->value() );
	    std::cout << TypeStr << std::endl;
	    if( TypeStr == "vec3" )
	      {
		// input of position types
		double            pos[3];
		std::cout << "attempting to tokenize str" << std::endl;
		wxStringTokenizer Tokenizer( ValueStr, "," );
		std::cout << "tokenized strgin" << std::endl;
		for (int i = 0; i < 3; i++)
		  {
		    pos[i] = boost::lexical_cast<double>(Tokenizer.GetNextToken().ToAscii());
		    std::cout << "Token was " << pos[i] << std::endl;
		    //Tokenizer.GetNextToken().ToDouble(
		    //				      &pos[i] );
		  }
		Rhs->Set<vec3>( NameStr,
				vec3( pos[0], pos[1], pos[2] ));
	      }
	    else if( TypeStr == "quat" )
	      {
		// input of position types
		double            pos[4];
		wxStringTokenizer Tokenizer( ValueStr, "," );
		for (int i = 0; i < 4; i++)
		  {
		    //Tokenizer.GetNextToken().ToDouble(
		    //		    &pos[i] );
		    pos[i] = boost::lexical_cast<double>(Tokenizer.GetNextToken().ToAscii());
		  }
		Rhs->Set<quat>( NameStr,
				quat( pos[0], pos[1], pos[2], pos[3] ));
	      }
	    else if( TypeStr == "vector_f" )
	      {

				
		std::vector<float> vector;
		wxStringTokenizer Tokenizer( ValueStr, "," );
		while (Tokenizer.HasMoreTokens()) {
		  float item;
		  //if (Tokenizer.GetNextToken().ToDouble( &item ))
		  //  std::cout << "Conversion okay" << std::endl;
		  //std::cout << "Value is: " << item << std::endl;
		  //surprisingly the wxString::ToDouble doesnt work
		  //item = atof(Tokenizer.GetNextToken().ToStdString().c_str());
		  item = boost::lexical_cast<float>(Tokenizer.GetNextToken().ToAscii());
		  //std::cout << "Value is: " << item << std::endl;
		  vector.push_back(item);
		  }
		Rhs->Set<std::vector<float> >( NameStr, vector );

	      }
 else if( TypeStr == "vector_p" )
	      {

				
		std::vector<Ogre::Vector3> points;
		wxStringTokenizer Tokenizer( ValueStr, "," );
		while (Tokenizer.HasMoreTokens()) {
		  

		  //item = boost::lexical_cast<float>(Tokenizer.GetNextToken().ToStdString());
		  //std::cout << "Value is: " << item << std::endl;
		  points.push_back( vec3(
					 boost::lexical_cast<float>( Tokenizer.GetNextToken().ToAscii() ),
					 boost::lexical_cast<float>( Tokenizer.GetNextToken().ToAscii() ),
					 boost::lexical_cast<float>( Tokenizer.GetNextToken().ToAscii() )
					 ) );
		  }
		Rhs->Set<std::vector<Ogre::Vector3> >( NameStr, points );

	      }
	    else if ( TypeStr == "int" )
	      {
		// input of integers
		Rhs->Set<int>( NameStr,
			       boost::lexical_cast<int>(
							ValueStr ) );
	      }
	    else if( TypeStr == "double" )
	      {
		// input of floating numbers
		Rhs->Set<double>( NameStr,
				  boost::lexical_cast<double>(
							      ValueStr ) );
	      }
	    else
	      {
		// standard is string
		Rhs->Set<std::string>( NameStr, ValueStr );
	      }
	   
	  } 
      } else break;
      
    }
  return true;
}

// perform update of an existing entity
void SocketMessage::HandleDelete()
{}
