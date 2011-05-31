#include "Trajectory.h"

CTrajectory::CTrajectory( Ogre::SceneManager* Mgr )
	: mSceneMgr( Mgr ), mMesh( NULL ), mPointSize( 0.02f ),
	mColour( Ogre::ColourValue::Red )
{
	Init();
	Update();
}

CTrajectory::CTrajectory( Ogre::SceneManager* Mgr, std::vector<float> Points )
	: mSceneMgr( Mgr ), mMesh( NULL ), mPointSize( 0.02f ),
	mColour( Ogre::ColourValue::Red )
{
	Init();
	for( unsigned int i=0; i<Points.size(); i+=3 )
	{
		if( i+2 < Points.size() )
		{
			Ogre::Vector3 tmp( Points[i], Points[i+1], Points[i+2] );
			mPoints.push_back( tmp );
		}
	}
	Update();
}

CTrajectory::CTrajectory( Ogre::SceneManager* Mgr, std::vector<Ogre::Vector3> Points )
	: mSceneMgr( Mgr ), mMesh( NULL ), mPointSize( 0.02f ),
	mColour( Ogre::ColourValue::Red )
{
	Init();
	mPoints.assign( Points.begin(), Points.end() );
	Update();
}

CTrajectory::~CTrajectory()
{
	if( mMesh )
	{
		mSceneMgr->destroyManualObject( mMesh );
	}
}

void CTrajectory::AddSinglePoint( const float x, const float y, const float z )
{
	mPoints.push_back( Ogre::Vector3( x, y, z ) );
	Update();
}

void CTrajectory::AddSinglePoint( const Ogre::Vector3& Point )
{
	mPoints.push_back( Point );
	Update();
}

void CTrajectory::AddPoints( const std::vector<float>& Points )
{
	for( unsigned int i=0; i<Points.size(); i+=3 )
		if( i+2 < Points.size() )
			mPoints.push_back( Ogre::Vector3( Points[i], Points[i+1], Points[i+2] ) );
	Update();
}

void CTrajectory::AddPoints( const std::vector<Ogre::Vector3>& Points )
{
	for( std::vector<Ogre::Vector3>::const_iterator i = Points.begin(); i != Points.end(); i++ )
		mPoints.push_back( *i );
	Update();
}

void CTrajectory::RemovePoint( const int Index )
{
	if( Index >= int(mPoints.size()) )
		return;
	std::vector<Ogre::Vector3>::iterator Del = mPoints.begin();
	int i = Index;
	while( i > 0 )
	{
		Del++;
		i--;
	}
	mPoints.erase( Del );
	Update();
}

void CTrajectory::Clear()
{
	mPoints.clear();
	mLineVertices.clear();
	mQuadVertices.clear();
	mMesh->clear();
}

void CTrajectory::BuildLine( const Ogre::Vector3& Start, const Ogre::Vector3& End,
	const Ogre::ColourValue& Colour, float Alpha )
{
	mLineVertices.push_back( VertexPair( Start, 
		Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	mLineVertices.push_back( VertexPair( End, 
		Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
}

void CTrajectory::BuildQuad( const Ogre::Vector3* Vertices, const Ogre::ColourValue& Colour,
	float Alpha )
{
	for (int i = 0; i < 4; ++i)
    {
		mLineVertices.push_back(
			VertexPair( Vertices[i], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
		mLineVertices.push_back(
			VertexPair( Vertices[(i + 1) % 4], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	}
}

void CTrajectory::BuildFilledQuad( const Ogre::Vector3* Vertices, const Ogre::ColourValue& Colour,
	float Alpha )
{
	mQuadVertices.push_back(
		VertexPair( Vertices[0], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	mQuadVertices.push_back(
		VertexPair( Vertices[1], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	mQuadVertices.push_back(
		VertexPair( Vertices[2], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
 
	mQuadVertices.push_back(
		VertexPair( Vertices[0], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	mQuadVertices.push_back(
		VertexPair( Vertices[2], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
	mQuadVertices.push_back(
		VertexPair( Vertices[3], Ogre::ColourValue( Colour.r, Colour.g, Colour.b, Alpha ) ) );
}

void CTrajectory::DrawPoint( const Ogre::Vector3& Pos )
{
	Ogre::Vector3 dx = mPointSize/2*Ogre::Vector3::UNIT_X;
	Ogre::Vector3 dy = mPointSize/2*Ogre::Vector3::UNIT_Y;
	Ogre::Vector3 dz = mPointSize/2*Ogre::Vector3::UNIT_Z;

	Ogre::Vector3 Vertices[8];
	Vertices[0] = Pos + dx + dy + dz;
	Vertices[1] = Pos + dx - dy + dz;
	Vertices[2] = Pos + dx - dy - dz;
	Vertices[3] = Pos + dx + dy - dz;
	Vertices[4] = Pos - dx + dy + dz;
	Vertices[5] = Pos - dx + dy - dz;
	Vertices[6] = Pos - dx - dy - dz;
	Vertices[7] = Pos - dx - dy + dz;

	BuildQuad( Vertices, mColour );
	BuildQuad( Vertices + 4, mColour );
 
	BuildLine( Vertices[1], Vertices[7], mColour );
	BuildLine( Vertices[2], Vertices[6], mColour );
 
	BuildLine( Vertices[0], Vertices[4], mColour);
	BuildLine( Vertices[3], Vertices[5], mColour);
 
	
	Ogre::Vector3 Top[4] = { Vertices[0], Vertices[4], Vertices[7], Vertices[1] };
	Ogre::Vector3 Bottom[4] = { Vertices[2], Vertices[6], Vertices[5], Vertices[3] };
 
	Ogre::Vector3 Left[4] = { Vertices[1], Vertices[7], Vertices[6], Vertices[2] };
	Ogre::Vector3 Right[4] = { Vertices[0], Vertices[3], Vertices[5], Vertices[4] };
 
	BuildFilledQuad( Vertices, mColour, 0.5f );
	BuildFilledQuad( Vertices + 4, mColour, 0.5f );
	BuildFilledQuad( Top, mColour, 0.5f );
	BuildFilledQuad( Bottom, mColour, 0.5f );
	BuildFilledQuad( Left, mColour, 0.5f );
	BuildFilledQuad( Right, mColour, 0.5f );
}

void CTrajectory::Init()
{
	if( mMesh )
		mSceneMgr->destroyManualObject( mMesh );

	mMesh = mSceneMgr->createManualObject();

	mMesh->begin( "Trajectory", Ogre::RenderOperation::OT_LINE_LIST );
	mMesh->position( Ogre::Vector3::ZERO );
	mMesh->colour( Ogre::ColourValue::ZERO );
	mMesh->end();
	mMesh->begin( "Trajectory", Ogre::RenderOperation::OT_TRIANGLE_LIST );
	mMesh->position( Ogre::Vector3::ZERO );
	mMesh->colour( Ogre::ColourValue::ZERO );
	mMesh->end();
}

void CTrajectory::Update()
{
	if( mPoints.size() > 0 )
	{
		mLineVertices.clear();
		mQuadVertices.clear();

		for( unsigned int i=0; i<mPoints.size(); i++ )
		{
			if( mPoints.size() > 1 && i > 0 )
				BuildLine( mPoints[i-1], mPoints[i], mColour, 1.f );
			DrawPoint( mPoints[i] );
		}

		mMesh->beginUpdate( 0 );
		mMesh->estimateVertexCount( mLineVertices.size() );
		for( std::vector<VertexPair>::iterator i = mLineVertices.begin(); i != mLineVertices.end(); ++i )
		{
			mMesh->position( i->first );
			mMesh->colour( i->second );
		}
		mMesh->end();
 
		mMesh->beginUpdate( 1 );
		mMesh->estimateVertexCount( mQuadVertices.size() );
		for( std::vector<VertexPair>::iterator i = mQuadVertices.begin(); i != mQuadVertices.end(); ++i )
		{
			mMesh->position(i->first);
			mMesh->colour( i->second.r, i->second.g, i->second.b, 0.5f );
		}
		mMesh->end();
	}
}
