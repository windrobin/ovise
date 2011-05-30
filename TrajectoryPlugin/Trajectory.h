#include <OgreVector3.h>
#include <OgreManualObject.h>
#include <OgreSceneManager.h>

#include <boost/scoped_ptr.hpp>

class CTrajectory
{
public:
	CTrajectory( Ogre::SceneManager* Mgr );
	CTrajectory( Ogre::SceneManager* Mgr, std::vector<float> Points );
	CTrajectory( Ogre::SceneManager* Mgr, std::vector<Ogre::Vector3> Points );
	~CTrajectory();

	void AddSinglePoint( const float x, const float y, const float z );
	void AddSinglePoint( const Ogre::Vector3& Point );
	void AddPoints( const std::vector<float>& Points );
	void AddPoints( const std::vector<Ogre::Vector3>& Points );
	void ChangePoint( const int Index, const float x, const float y, const float z );
	void RemovePoint( const int Index );
	void Clear();

	void SetThickness( float Thickness ) { mThickness = Thickness; Update(); }
	float GetThickness() const { return mThickness; }
	void SetPointSize( float Size ) { mPointSize = Size; Update(); }
	float GetPointSize() const { return mPointSize; }

	Ogre::ManualObject* GetManualObject() { return mMesh.get(); }

private:
	std::vector<Ogre::Vector3> mPoints;
	boost::scoped_ptr<Ogre::ManualObject> mMesh;
	Ogre::SceneManager* mSceneMgr;
	float mThickness;
	float mPointSize;

	void Update();
};
