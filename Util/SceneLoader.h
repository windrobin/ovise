#ifndef OVISE_SCENE_LOADER_H
#define OVISE_SCENE_LOADER_H

#include "../rapidxml-1.13/rapidxml.hpp"
#include <boost/filesystem.hpp>

#include <istream>
#include <sstream>

namespace bf = boost::filesystem;

class Entity;
class EntityPool;

using namespace rapidxml;

float ToFloat( char* C )
{
	float F;
	std::stringstream( C ) >> F;
	return F;
}

void LoadSceneFromXML( const std::string& Filename, EntityPool& EntPool )
{
	bf::path FilePath( Filename );
	if( !bf::exists( FilePath ) )
		return;

	std::ifstream Infile( Filename );
	std::string Content( (std::istreambuf_iterator<char>( Infile )), std::istreambuf_iterator<char>() );

	xml_document<> XMLDoc;
	XMLDoc.parse<0>( const_cast<char*>( Content.c_str() ) );
	
	xml_node<>* RootNode = XMLDoc.first_node( "scene" );
	if( !RootNode )
		return;

	xml_node<>* MeshNodes = RootNode->first_node( "nodes" );
	if( !MeshNodes )
		return;

	for( xml_node<>* Node = MeshNodes->first_node( "node" ); Node; Node = Node->next_sibling( "node" ) )
	{
		if( !Node )
			continue;

		xml_attribute<>* NameAttr = Node->first_attribute( "name" );
		if( !NameAttr )
			continue;
		std::string Name( NameAttr->value() );

		xml_node<>* PosNode = Node->first_node( "position" );
		xml_node<>* QuatNode = Node->first_node( "quaternion" );
		xml_node<>* ScaleNode = Node->first_node( "scale" );
		xml_node<>* EntNode = Node->first_node( "entity" );

		if( !( PosNode && QuatNode && ScaleNode && EntNode ) )
			continue;

		float PosX = ToFloat( PosNode->first_attribute( "x" )->value() );
		float PosY = ToFloat( PosNode->first_attribute( "y" )->value() );
		float PosZ = ToFloat( PosNode->first_attribute( "z" )->value() );

		float QuatW = ToFloat( QuatNode->first_attribute( "w" )->value() );
		float QuatX = ToFloat( QuatNode->first_attribute( "x" )->value() );
		float QuatY = ToFloat( QuatNode->first_attribute( "y" )->value() );
		float QuatZ = ToFloat( QuatNode->first_attribute( "z" )->value() );

		float ScaleX = ToFloat( ScaleNode->first_attribute( "x" )->value() );
		float ScaleY = ToFloat( ScaleNode->first_attribute( "y" )->value() );
		float ScaleZ = ToFloat( ScaleNode->first_attribute( "z" )->value() );

		std::string Mesh( EntNode->first_attribute( "meshFile" )->value() );
		// TODO: get more entity properties

		EntPool.CreateEntity( Name ).Set
			( "Type", "Simple" )
			( "Model", Mesh )
			( "Position", vec3( PosX, PosY, PosZ ) )
			( "Orientation", vec4( QuatW, QuatX, QuatY, QuatZ ) )
			( "Scale", vec3( ScaleX, ScaleY, ScaleZ ) )
		;
	}
}

void SaveSceneToXML( const std::string& Filename )
{

}

#endif // OVISE_SCENE_LOADER_H
