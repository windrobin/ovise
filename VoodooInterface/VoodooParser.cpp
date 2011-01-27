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
		if( ModelID != mModelID )
			continue;

		int LimbID;
		tmp = std::string( LimbAttr->value() );
		std::istringstream( tmp ) >> LimbID;

		mLimbMap[LimbID].ModelID = ModelID;
		mLimbMap[LimbID].LimbID = LimbID;
		mLimbMap[LimbID].LimbName = mBodyMapping[LimbID];

		double v;
		tmp = std::string( DEntry->value() );
		std::istringstream( tmp ) >> v;

		tmp = std::string( NameAttr->value() );
		if( tmp == "xPos" )
			mLimbMap[LimbID].xPos = v;
		else if( tmp == "yPos" )
			mLimbMap[LimbID].yPos = v;
		else if( tmp == "zPos" )
			mLimbMap[LimbID].zPos = v;
		else if( tmp == "z0" )
			mLimbMap[LimbID].z0 = v;
		else if( tmp == "y1" )
			mLimbMap[LimbID].y1 = v;
		else if( tmp == "z2" )
			mLimbMap[LimbID].z2 = v;
	}
	return true;
}

void CVoodooParser::UpdateEntity( Entity* Ent )
{
	for( LimbMapType::iterator i = mLimbMap.begin(); i != mLimbMap.end(); i++ )
	{
		double c1 = cos(i->second.z0/2);
		double s1 = sin(i->second.z0/2);
		double c2 = cos(i->second.z2/2);
		double s2 = sin(i->second.z2/2);
		double c3 = cos(i->second.y1/2);
		double s3 = sin(i->second.y1/2);
		double c1c2 = c1*c2;
		double s1s2 = s1*s2;
		double w = c1c2*c3 - s1s2*s3;
        double x = c1c2*s3 + s1s2*c3;
        double y = s1*c2*c3 + c1*s2*s3;
        double z = c1*s2*c3 - s1*c2*s3;
		Ent->Set<vec4>( i->second.LimbName, vec4( w, x, y, z ) );
	}
}
