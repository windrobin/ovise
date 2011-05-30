#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include "PointcloudEntityView.h"
#include <wx/dir.h>
#include <wx/tokenzr.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>

namespace
{
	template < class T > T* ptr( std::vector<T>& v )
	{
		return &( v[0] );
	}

	bool ParseVector( const wxString& String,double& x,double& y,double& z )
	{
		wxStringTokenizer p( String, wxT( " " ));

		// Line corrupt?
		if ( p.CountTokens() != 3 )
			return false;

		setlocale( LC_ALL, "C" );

		if (!p.GetNextToken().ToDouble( &x ) ||
			!p.GetNextToken().ToDouble( &y ) ||
			!p.GetNextToken().ToDouble( &z ) )
			return false;

		return true;
	}
}

PointcloudEntityView::PointcloudEntityView( Entity* Object,
	Ogre::SceneManager*                         Mgr ) :
	BasicOgreEntityView( Object,Mgr ),
	mNode( 0 ),
	mOgreEntity( 0 )
{
	mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();

	SyncAttribs( this );
}

PointcloudEntityView::~PointcloudEntityView()
{
	if( mOgreEntity )
	{
		mNode->detachAllObjects();
		GetSceneManager()->destroyEntity( mOgreEntity );
	}
	GetSceneManager()->getRootSceneNode()->removeChild( mNode );
}

void PointcloudEntityView::OnEntityAttributeChanged( Entity* Rhs,
	const std::string& Name,const EntityVariantType* Attribute )
{
	if ( Name == "Filename" )
	{
		const std::string* Str=boost::get<std::string>( Attribute );

		if( mNode )
		{
			mNode->detachAllObjects();
			//GetSceneManager()->destroySceneNode( mNode );
		}
		if( mOgreEntity )
			GetSceneManager()->destroyEntity( mOgreEntity );

		if ( Str )
		{
			std::size_t DotPos = Str->find_last_of( '.' );
			std::string Suffix = Str->substr( DotPos + 1 );
			if( Suffix == "off" )
				LoadFromFileOFF( *Str );
			else if( Suffix == "ply" )
			{
				LoadFromFilePLY( *Str );
			}
		}
	}
	else if ( Name == "Points" )
	{
		const boost::any* PAny = boost::get<boost::any>( Attribute );
		try
		{
			const std::vector<float>& Points = boost::any_cast<std::vector<float> >( *PAny );
			if( !mPointCloud )
			{
				const EntityVariantType* ColorsAttr = Rhs->GetAttribute( "Colors" );
				if( !ColorsAttr )
				{
					mPointCloud.reset( new CPointcloud( Rhs->GetName(), "General",
							Points.size() / 3, 
							const_cast<float*>(Points.data()), 0 ) );

					// Insert the model into the scene
					const std::string EntityName = "Entity:" + 
						boost::lexical_cast<std::string>( GetDataEntity() );
					mOgreEntity = GetSceneManager()->createEntity( 
						EntityName.c_str(), Rhs->GetName());
					mOgreEntity->setMaterialName( "Pointcloud" );

					mNode->attachObject( mOgreEntity );
				}
				else
				{
					const boost::any* CAny = boost::get<boost::any>( ColorsAttr );
					try
					{
						const std::vector<float>& Colors = 
							boost::any_cast<std::vector<float> > ( *CAny );
						mPointCloud.reset( new CPointcloud( Rhs->GetName(), 
							"General",
							Points.size() / 3, 
							const_cast<float*>(Points.data()),
							const_cast<float*>(Colors.data()) ) );

						// Insert the model into the scene
						const std::string EntityName = "Entity:" + 
							boost::lexical_cast<std::string>( GetDataEntity() );
						mOgreEntity = GetSceneManager()->createEntity( EntityName.c_str(), 
							Rhs->GetName());
						mOgreEntity->setMaterialName( "Pointcloud" );

						mNode->attachObject( mOgreEntity );
					}
					catch( const boost::bad_any_cast & )
					{}
				}
 			}
			else if( mPointCloud)
			{
				mPointCloud->UpdateVertexPositions( Points.size() / 3, 
					const_cast<float*>(Points.data()) );
			}
		}
		catch( const boost::bad_any_cast & )
		{}
	}
	else if ( Name == "Colors" )
	{
		if( mPointCloud )
		{
			const boost::any* CAny = boost::get<boost::any>( Attribute );
			try
			{
				const std::vector<float>& Colors = 
					boost::any_cast<std::vector<float> > ( *CAny );
				mPointCloud->UpdateVertexColours( Colors.size() / 3, 
					const_cast<float*>(Colors.data()) );
			}
			catch( const boost::bad_any_cast & )
			{}
 		}
 	}
	else if ( Name == "PointSize" )
	{
		const double* PS = boost::get<double>( Attribute );

		if( mOgreEntity && PS )
		{
			// values above 0.05 do not show any difference
			mOgreEntity->getSubEntity( 0 )->getMaterial()->setPointSize( 
				float( *PS ) );
		}
	}
	else if ( Name == "Position" )
	{
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mNode->setPosition( *Data );
	}
	else if ( Name == "Orientation" )
	{
		const quat* Data = boost::get<quat>( Attribute );

		if( Data )
			mNode->setOrientation( *Data );
	}
	else if ( Name == "Scale" )
	{
		const vec3* Data = boost::get<vec3>( Attribute );

		if( Data )
			mNode->setScale( *Data );
	}
}

void PointcloudEntityView::LoadFromFileOFF( const std::string& Filename, 
	float r, float g, float b )
{
	using namespace boost::assign;

	// Strip pathname and extension from the file
	wxString Name;
	wxFileName::SplitPath( Filename,0,0,&Name,0 );

	// Generate an entity name
	wxString PointcloudName = wxT( "Pointcloud:" ) + Name;

	// Open the source file
	wxTextFile PCFile;
	PCFile.Open( Filename );

	// Vectors to hold the data
	std::vector<float> Points;
	std::vector<float> Colors;

	wxString Line = PCFile.GetFirstLine();
	double   x, y, z;
	x = y = z = 0.f;

	float PCmin[] = {1000000.f, 1000000.f, 1000000.f};
	float PCmax[] = {-1000000.f, -1000000.f, -1000000.f};

	// Start parsing the file
	while( !PCFile.Eof() )
	{
		// Ignore comments
		if( Line.StartsWith( wxT( "#" )) )
			continue;

		if( Line.Matches( wxT( "*,*" )) )
		{
			double r=0.0,g=0.0,b=0.0;

			// Try parsing
			if (!ParseVector( Line.BeforeFirst( ',' ),x,y,z ) ||
				!ParseVector( Line.AfterFirst( ',' ),r,g,b ) )
				continue;

			if ( float(x) <= PCmin[0] ) PCmin[0] = float(x);
			if ( float(y) <= PCmin[1] ) PCmin[1] = float(y);
			if ( float(z) <= PCmin[2] ) PCmin[2] = float(z);
			if ( float(x) >= PCmax[0] ) PCmax[0] = float(x);
			if ( float(y) >= PCmax[1] ) PCmax[1] = float(y);
			if ( float(z) >= PCmax[2] ) PCmax[2] = float(z);
			// Commit
			Points += float(x), float(y), float(z);
			Colors += float(r), float(g), float(b);
		}
		else
		{
			// Try parsing
			if (!ParseVector( Line,x,y,z ))
				continue;

			if ( float(x) <= PCmin[0] ) PCmin[0] = float(x);
			if ( float(y) <= PCmin[1] ) PCmin[1] = float(y);
			if ( float(z) <= PCmin[2] ) PCmin[2] = float(z);
			if ( float(x) >= PCmax[0] ) PCmax[0] = float(x);
			if ( float(y) >= PCmax[1] ) PCmax[1] = float(y);
			if ( float(z) >= PCmax[2] ) PCmax[2] = float(z);
			// Commit
			Points += float(x), float(y), float(z);
			Colors += r, g, b;
		}
		Line = PCFile.GetNextLine();
	}

	if ( Colors.size() && ( Colors.size() != Points.size() ) )
		throw std::runtime_error(
				"Colors were read, but a different amount of points was read." );

	// Normalize color ranges
	// FIXME: The conditional is a bit hacky.
	// Don't we want color ranges to be consistent within a file format?
	for (std::size_t i=0,ie=Colors.size(); i<ie; ++i)
		if ( Colors[i] > 1.f ) // Not already in the [0..1) range?
			Colors[i] /= 255.f;

	Ogre::AxisAlignedBox PCBounds( PCmin[0],
								   PCmin[1],
								   PCmin[2],
								   PCmax[0],
								   PCmax[1],
								   PCmax[2] );

	mPointCloud.reset( new CPointcloud( std::string( PointcloudName.mb_str()),
										"General",
										Points.size() / 3, ptr( Points ),
										Colors.size() ? ptr( Colors ) : 0 ) );

	// Insert the model into the scene
	const std::string EntityName = "Entity:" +
								   boost::lexical_cast<std::string>(
			GetDataEntity() );
	mOgreEntity = GetSceneManager()->createEntity(
			EntityName.c_str(), Ogre::String( PointcloudName.mb_str()));
	mOgreEntity->setMaterialName( "Pointcloud" );

	if( !mNode )
		mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject( mOgreEntity );
}

void PointcloudEntityView::LoadFromFilePLY( const std::string& Filename )
{
	using namespace boost::assign;

	// Strip pathname and extension from the file
	wxString Name;
	wxFileName::SplitPath( Filename,0,0,&Name,0 );

	// Generate an entity name
	wxString PointcloudName = wxT( "Pointcloud:" ) + Name;

	// Vectors to hold the data
	std::vector<float> Points;
	std::vector<float> Colors;
	std::vector<float> Normals;

	float PCmin[] = {1000000.f, 1000000.f, 1000000.f};
	float PCmax[] = {-1000000.f, -1000000.f, -1000000.f};

	long NumVertices = 0;

	// important tags
	wxString EndOfHeader = wxT( "end_header" );
	wxString VertexElement = wxT( "element vertex" );

	wxString fn( Filename );
	wxFileInputStream Input( fn );
	wxTextInputStream Text( Input, wxT(" ") );
	wxString Token;
	if( Input.IsOk() && !Input.Eof() )
	{
		Text >> Token;
		
		if( Token != wxT( "ply" ) ) return;
	}

	if( Input.IsOk() && !Input.Eof() )
	{
		Text >> Token;
		while( !Token.StartsWith( EndOfHeader ) && Input.IsOk() && !Input.Eof() )
		{
			if( Token.StartsWith( VertexElement ) )
			{
				wxString NumStr = Token.substr( VertexElement.Length() );
				NumStr.ToLong( &NumVertices );
			}
			Text >> Token;
		}
	}

	double x, y, z;
	x = y = z = 0.f;
	double nx, ny, nz;
	nx = ny = nz = 0.f; 
	double r, g, b;
	r = g = b = 1.f;

	setlocale( LC_ALL, "C" );

	// Start parsing the file
	while( Input.IsOk() && !Input.Eof() )
	{
		Text >> x; Text >> y; Text >> z;
		Text >> r; Text >> g; Text >> b;

		// Commit
		Points += float(x), float(y), float(z);
		Colors += float(r)/255.f, float(g)/255.f, float(b)/255.f;
		
		if ( float(x) <= PCmin[0] ) PCmin[0] = float(x);
		if ( float(y) <= PCmin[1] ) PCmin[1] = float(y);
		if ( float(z) <= PCmin[2] ) PCmin[2] = float(z);
		if ( float(x) >= PCmax[0] ) PCmax[0] = float(x);
		if ( float(y) >= PCmax[1] ) PCmax[1] = float(y);
		if ( float(z) >= PCmax[2] ) PCmax[2] = float(z);
	}

	if ( Colors.size() && ( Colors.size() != Points.size() ) )
		throw std::runtime_error(
				"Colors were read, but a different amount of points was read." );

	Ogre::AxisAlignedBox PCBounds( PCmin[0],
								   PCmin[1],
								   PCmin[2],
								   PCmax[0],
								   PCmax[1],
								   PCmax[2] );

	mPointCloud.reset( new CPointcloud( std::string( PointcloudName.mb_str()),
										"General",
										Points.size() / 3, ptr( Points ),
										Colors.size() ? ptr( Colors ) : 0 ) );

	// Insert the model into the scene
	const std::string EntityName = "Entity:" +
								   boost::lexical_cast<std::string>(
			GetDataEntity() );
	mOgreEntity = GetSceneManager()->createEntity(
			EntityName.c_str(), Ogre::String( PointcloudName.mb_str()));
	mOgreEntity->setMaterialName( "Pointcloud" );

	if( !mNode )
		mNode = GetSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject( mOgreEntity );
}

/** \note This has to be defined as a C function to prevent name mangling.
 */
extern "C" OVISE_DLLAPI
void LoadEntityView( SceneView& View )
{
	View.RegisterView<PointcloudEntityView>( "Pointcloud" );
}
