#include "Pointcloud.h"

#include <boost/algorithm/minmax.hpp>

CPointcloud::CPointcloud( const std::string& Name, const std::string& Resourcegroup, 
	const std::size_t VNumber, float* VArray, float* CArray)
	: mNumVertices( VNumber )
{
	// Create the mesh via the MeshManager
	mMsh = Ogre::MeshManager::getSingleton().createManual( Name, Resourcegroup);

	// Create one submesh
	mSub = mMsh->createSubMesh();

	// Create vertex data structure for vertices shared between submeshes
	mMsh->sharedVertexData = new Ogre::VertexData();
	mMsh->sharedVertexData->vertexCount = mNumVertices;

	// Create declaration (memory format) of vertex data
	mDeclaration = mMsh->sharedVertexData->vertexDeclaration;
	mDeclaration->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	
	mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		mDeclaration->getVertexSize(0), mMsh->sharedVertexData->vertexCount,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	// Upload the vertex data to the card
	mVertexBuffer->writeData(0, mVertexBuffer->getSizeInBytes(), VArray, true);

	if( CArray != NULL )
	{
		// Create 2nd buffer for colors
		mDeclaration->addElement(1, 0, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
		mColorBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR),
			mMsh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

		Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		Ogre::RGBA *colours = new Ogre::RGBA[mNumVertices];
		for( std::size_t i=0, k=0; i < mNumVertices*3 && k < mNumVertices; i+=3, k++)
		{
			// Use render system to convert colour value since colour packing varies
			rs->convertColourValue(Ogre::ColourValue(CArray[i],CArray[i+1],CArray[i+2]), &colours[k]);
		}
		// Upload colour data
		mColorBuffer->writeData(0, mColorBuffer->getSizeInBytes(), colours, true);
		delete[] colours;
	}

	/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	Ogre::VertexBufferBinding* bind = mMsh->sharedVertexData->vertexBufferBinding; 
	bind->setBinding(0, mVertexBuffer);

	if( CArray != NULL )
	{
		// Set colour binding so buffer 1 is bound to colour buffer
		bind->setBinding(1, mColorBuffer);
	}

	mSub->useSharedVertices = true;
	mSub->operationType = Ogre::RenderOperation::OT_POINT_LIST;
	
	float minx, miny, minz;
	minx = miny = minz = 100000000;
	float maxx, maxy, maxz;
	maxx = maxy = maxz = -1000000000;
	for( int i=0; i<mNumVertices; i++ )
	{
		float x = VArray[3*i];
		float y = VArray[3*i+1];
		float z = VArray[3*i+2];

		if( x < minx ) minx = x;
		if( y < miny ) miny = y;
		if( z < minz ) minz = z;
		if( x > maxx ) maxx = x;
		if( y > maxy ) maxy = y;
		if( z > maxz ) maxz = z;
	}
	mMsh->load();
	mMsh->_setBounds( Ogre::AxisAlignedBox( minx, miny, minz, maxx, maxy, maxz ) );
}

void CPointcloud::PrepareBuffers( std::size_t VertexSize )
{
	if( VertexSize != mNumVertices )
	{
		mNumVertices = VertexSize;
		mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			mDeclaration->getVertexSize(0), mNumVertices,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE );
		mMsh->sharedVertexData->vertexCount = mNumVertices;
		mColorBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR),
			mMsh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE );

		mMsh->sharedVertexData->vertexBufferBinding->setBinding( 0, mVertexBuffer );
		mMsh->sharedVertexData->vertexBufferBinding->setBinding( 1, mColorBuffer );
	}
}

void CPointcloud::UpdateVertexPositions( std::size_t VNumber, float* Vertices)
{
	PrepareBuffers( VNumber );
	float minx, miny, minz;
	minx = miny = minz = 100000000;
	float maxx, maxy, maxz;
	maxx = maxy = maxz = -1000000000;
	mVertexBuffer->writeData( 0, mVertexBuffer->getSizeInBytes(), Vertices, true );
	for(int i=0; i<VNumber*3; i+=3)
	{
		if( Vertices[i] < minx ) minx = Vertices[i];
		if( Vertices[i+1] < miny ) miny = Vertices[i+1];
		if( Vertices[i+2] < minz ) minz = Vertices[i+2];
		if( Vertices[i] > maxx ) maxx = Vertices[i];
		if( Vertices[i+1] > maxy ) maxy = Vertices[i+1];
		if( Vertices[i+2] > maxz ) maxz = Vertices[i+2];
	}
	
	mMsh->_setBounds( Ogre::AxisAlignedBox( minx, miny, minz, maxx, maxy, maxz ) );
}

void CPointcloud::UpdateVertexColours( std::size_t CNumber, float* Colors)
{
	if( CNumber <= mNumVertices )
	{
		mColorBuffer->writeData( 0, mColorBuffer->getSizeInBytes(), Colors, true );
	}
	else
	{
		mColorBuffer->writeData( 0, CNumber*3, Colors );
	}
}

CPointcloud::~CPointcloud()
{
	delete mSub->vertexData;
}