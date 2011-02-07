#include "VoodooParser.hpp"

#include <sstream>
#include <iostream>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <cmath>

CVoodooParser::CVoodooParser()
	: mModelID( 0 ), mMappingLoaded( false )
{
}

CVoodooParser::CVoodooParser( int ModelID )
	: mModelID( ModelID ), mMappingLoaded( false )
{
}

bool CVoodooParser::LoadBodyMapping()
{
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree PropTree;

	try
	{
		// Read the file
		read_xml( "BodyMapping.xml", PropTree );

		BOOST_FOREACH( ptree::value_type& v, PropTree.get_child("BodyMapping.Limbs") )
		{
			int m = v.second.get_value<int>();
			mBodyMapping[m] = v.second.get_child( "<xmlattr>.name" ).data();
		}
	}
	catch( boost::property_tree::xml_parser::xml_parser_error& /*e*/ )
	{
		std::cout << "Parsing error in BodyMapping.xml" << std::endl;
		return false;
	}

	mMappingLoaded = true;
	return true;
}

bool CVoodooParser::ParseDocument( rapidxml::xml_document<>& Document )
{
	if( !mMappingLoaded )
		return false;

	rapidxml::xml_node<>* RootNode = Document.first_node( "VooDooConnectData" );
	if( !RootNode )
		return false;
	
	rapidxml::xml_node<>* DataNode = RootNode->first_node( "humPosDataSet" );
	if( !DataNode )
		return false;

	for( rapidxml::xml_node<>* DEntry = DataNode->first_node( "dataEntry" );
		 DEntry; DEntry = DEntry->next_sibling( "dataEntry" ) )
	{
		rapidxml::xml_attribute<>* LimbAttr = DEntry->first_attribute( "limb" );
		if( !LimbAttr )
			continue;
		rapidxml::xml_attribute<>* NameAttr = DEntry->first_attribute( "name" );
		if( !NameAttr )
			continue;
		rapidxml::xml_attribute<>* IDAttr = DEntry->first_attribute( "id" );
		if( !IDAttr )
			continue;

		std::string tmp;
		tmp = std::string( IDAttr->value() );
		int ModelID;
		std::istringstream( tmp ) >> ModelID;
		mModelID = ModelID;
		//if( ModelID != mModelID )
		//	continue;

		int LimbID;
		tmp = std::string( LimbAttr->value() );
		std::istringstream( tmp ) >> LimbID;

		mLimbMap[LimbID].ModelID = ModelID;
		mLimbMap[LimbID].LimbID = LimbID;
		mLimbMap[LimbID].LimbName = mBodyMapping[LimbID];

		float v;
		tmp = std::string( DEntry->value() );
		std::istringstream( tmp ) >> v;

		tmp = std::string( NameAttr->value() );
		if( tmp == "w" )
			mLimbMap[LimbID].quat[0] = v;
		else if( tmp == "x" )
			mLimbMap[LimbID].quat[1] = v;
		else if( tmp == "y" )
			mLimbMap[LimbID].quat[2] = v;
		else if( tmp == "z" )
			mLimbMap[LimbID].quat[3] = v;
	}
	return true;
}

void CVoodooParser::UpdateEntity( Entity* Ent )
{
	Ent->Set<int>( "ModelID", mLimbMap.begin()->second.ModelID  );
	for( LimbMapType::iterator i = mLimbMap.begin(); i != mLimbMap.end(); i++ )
	{
		Ent->Set<quat>( i->second.LimbName, quat( i->second.quat[0],
												  i->second.quat[1], 
												  i->second.quat[2], 
												  i->second.quat[3] ) );
	}
}
