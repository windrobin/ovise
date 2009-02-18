#pragma once
#include <OgreManualObject.h>

/** Class for visualisation of pointclouds.
 * The class can be intialized with a array of points organized like: [0]=P1x [1]=P1y [2]=P1z
 * [3]=P2x [4]=P2y [5]=P2z ...</br>
 * The class constructs a manual object out of these points where each point is visualized as a
 * tetrahedron.
 */
class OViSEPointcloud :	public Ogre::ManualObject
{
public:
	OViSEPointcloud(const std::string& name);

	/// Create a pointcloud with size points.
	void create(int size, float *points, const std::string material, bool dynamic = true);
	/** Update a created pointcloud with size points.
	  * Updates numpoints points of the pointcloud starting at point # index
	  */
	void update(int size, float *points, const std::string material, int index = -1, int numpoints = 0);

	virtual ~OViSEPointcloud();

private:
	int mSize;
};
