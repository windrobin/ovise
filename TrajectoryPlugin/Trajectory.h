#include <OgreVector3.h>
#include <OgreManualObject.h>
#include <OgreSceneManager.h>

#include <boost/shared_ptr.hpp>

typedef std::pair<Ogre::Vector3, Ogre::ColourValue> VertexPair;

/**
  Represents a trajectory in 3D space.
  This class is used to draw a trajectory in 3D space given by a series of
  points. Points are drawn as boxes while inbetween the points a line is drawn
  to show the connection. Size of the points as well as the colour of the
  trajectory can be set.
*/
class CTrajectory
{
public:
	/// Empty constructor
	CTrajectory( Ogre::SceneManager* Mgr );
	/**
	  Constructor with list of points.
	  Construct with a series of points given as a float array in the form
	  p1x p1y p1z p2x p2y p2z .... pnx pny pnz
	*/
	CTrajectory( Ogre::SceneManager* Mgr, std::vector<float> Points );
	/// Construct with a list of Ogre-Points.
	CTrajectory( Ogre::SceneManager* Mgr, std::vector<Ogre::Vector3> Points );
	~CTrajectory();

	/// Clear all points in the trajectory.
	void Clear();

	/// Set colour of visualization
	void SetColour( const Ogre::ColourValue& Colour ) { mColour = Colour; Update(); }

	/// Set size of points
	void SetPointSize( float Size ) { mPointSize = Size; Update(); }
	/// Get points size
	float GetPointSize() const { return mPointSize; }

	/// Internal: pointer to the Ogre::ManualObject used for visualization
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
