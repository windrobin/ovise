#pragma once
#include <OgreSceneManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreMeshManager.h>
#include <OgreHardwareBufferManager.h>

/** Class for visualisation of pointclouds.
 * The class can be intialized with a array of points organized like: [0]=P1x [1]=P1y [2]=P1z
 * [3]=P2x [4]=P2y [5]=P2z ...</br>
 * The class constructs a manual object out of these points where each point is visualized as a
 * tetrahedron.
 */
class OViSEPointcloud
{
public:
	OViSEPointcloud(const std::string& name, const std::string& resourcegroup, int numpoints, float *parray);

	/// Update a created pointcloud with size points.
	void update(int size, float *points);

	virtual ~OViSEPointcloud();

private:
	int mSize;
	Ogre::HardwareVertexBufferSharedPtr vbuf;
};
