#pragma once
#include <OgreSceneManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreMeshManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreRenderSystem.h>
#include <OgreRoot.h>

/** Class for visualisation of pointclouds.
 * The class can be intialized with a array of points organized like: [0]=P1x [1]=P1y [2]=P1z
 * [3]=P2x [4]=P2y [5]=P2z ...
 */
class OViSEPointcloud
{
public:
	OViSEPointcloud(const std::string& name, const std::string& resourcegroup, const int numpoints, float *parray, float *carray);

	/// Update a created pointcloud with size points.
	void updateVertexPositions(int size, float *points);

	/// Update vertex colours
	void updateVertexColours(int size, float *colours);

	virtual ~OViSEPointcloud();

private:
	int mSize;
	Ogre::HardwareVertexBufferSharedPtr vbuf;
	Ogre::HardwareVertexBufferSharedPtr cbuf;
};
