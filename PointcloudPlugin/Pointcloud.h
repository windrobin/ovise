#ifndef POINTCLOUD_H
#define POINTCLOUD_H

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
 * FIXME: (LTJ) should this rather be called PointcloudMesh/Model ?
 */
class CPointcloud
{
public:
	CPointcloud( const std::string& Name, const std::string& Resourcegroup,
	             const std::size_t VNumber, float* VArray, float* CArray );

	// / Update a created pointcloud with size points.
	void UpdateVertexPositions( std::size_t VNumber, float* Vertices );

	// / Update vertex colours
	void UpdateVertexColours( std::size_t CNumber, float* Colors );

	virtual ~CPointcloud();

private:
	void PrepareBuffers( std::size_t VNumber );

	std::size_t mNumVertices;

	Ogre::HardwareVertexBufferSharedPtr mVertexBuffer;
	Ogre::HardwareVertexBufferSharedPtr mColorBuffer;

	Ogre::VertexDeclaration* mDeclaration;

	Ogre::MeshPtr  mMsh;
	Ogre::SubMesh* mSub;
};
#endif // POINTCLOUD_H
