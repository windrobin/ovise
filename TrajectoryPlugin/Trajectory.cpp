#include "Trajectory.h"

namespace {
void BuildPoint( Ogre::ManualObject* Msh, const Ogre::Vector3& P, float S )
{
	Msh->position( P + S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P + S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );

	Msh->position( P + S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X + S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P + S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Z );

	Msh->position( P + S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X + S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );

	Msh->position( P + S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X + S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );
	Msh->position( P - S/2*Ogre::Vector3::UNIT_X - S/2*Ogre::Vector3::UNIT_Y - S/2*Ogre::Vector3::UNIT_Z );
}
}

CTrajectory::CTrajectory( Ogre::SceneManager* Mgr )
	: mSceneMgr( Mgr ), mMesh( 0 ), mThickness( 1.f ), mPointSize( 2.f )
{
	Update();
}

CTrajectory::CTrajectory( Ogre::SceneManager* Mgr, std::vector<float> Points )
	: mSceneMgr( Mgr ), mMesh( 0 ), mThickness( 1.f ), mPointSize( 2.f )
{
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
	: mSceneMgr( Mgr ), mMesh( 0 ), mThickness( 1.f ), mPointSize( 2.f )
{
	mPoints.assign( Points.begin(), Points.end() );
	Update();
}

CTrajectory::~CTrajectory()
{
	if( mSceneMgr && mMesh )
		mSceneMgr->destroyManualObject( mMesh.get() );
}

void CTrajectory::AddSinglePoint( const float x, const float y, const float z )
{
	
}

void CTrajectory::AddSinglePoint( const Ogre::Vector3& Point )
{

}

void CTrajectory::AddPoints( const std::vector<float>& Points )
{

}

void CTrajectory::AddPoints( const std::vector<Ogre::Vector3>& Points )
{

}

void CTrajectory::ChangePoint( const int Index, const float x, const float y, const float z )
{

}

void CTrajectory::RemovePoint( const int Index )
{

}

void CTrajectory::Clear()
{

}

void CTrajectory::Update()
{
	if( mPoints.size() == 0 )
	{
		if( mMesh )
			mSceneMgr->destroyManualObject( mMesh.get() );

		mMesh.reset( mSceneMgr->createManualObject() );

		mMesh->begin( "Trajectory", Ogre::RenderOperation::OT_TRIANGLE_LIST );
		mMesh->position( Ogre::Vector3::ZERO );
		mMesh->end();
	}
	else
	{
		mMesh->clear();
		mMesh->estimateVertexCount( mPoints.size() );
		for( unsigned int i=0; i<mPoints.size(); i++ )
		{
			mMesh->begin( "Trajectory" );
			BuildPoint( mMesh.get(), mPoints[i], mPointSize );
			mMesh->end();
		}
	}
}
