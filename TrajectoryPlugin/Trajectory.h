#include <OgreVector3.h>
#include <OgreManualObject.h>
#include <OgreSceneManager.h>

#include <boost/shared_ptr.hpp>

typedef std::pair<Ogre::Vector3, Ogre::ColourValue> VertexPair;

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
	void RemovePoint( const int Index );
	void Clear();

	void SetColour( const Ogre::ColourValue& Colour ) { mColour = Colour; Update(); }

	void SetPointSize( float Size ) { mPointSize = Size; Update(); }
	float GetPointSize() const { return mPointSize; }

	Ogre::ManualObject* GetManualObject() { return mMesh; }

private:
	std::vector<Ogre::Vector3> mPoints;
	Ogre::ManualObject* mMesh;
	Ogre::SceneManager* mSceneMgr;
	float mPointSize;
	Ogre::ColourValue mColour;

	std::vector<VertexPair> mLineVertices;
	std::vector<VertexPair> mQuadVertices;

	void Init();
	void Update();

	void BuildLine( const Ogre::Vector3& Start,
		const Ogre::Vector3& End, const Ogre::ColourValue& Colour, float Alpha = 1.f );
	void BuildQuad( const Ogre::Vector3* Vertices,
		const Ogre::ColourValue& Colour, float Alpha = 1.f );
	void BuildFilledQuad( const Ogre::Vector3* Vertices,
		const Ogre::ColourValue& Colour, float Alpha = 1.f );
	void DrawPoint( const Ogre::Vector3& Pos );
};
