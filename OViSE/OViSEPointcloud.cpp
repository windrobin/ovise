#include "OViSEPointcloud.h"

OViSEPointcloud::OViSEPointcloud(const std::string& name, const std::string& resourcegroup, int numpoints, float *parray)
{
	/// Create the mesh via the MeshManager
	Ogre::MeshPtr msh = Ogre::MeshManager::getSingleton().createManual(name, resourcegroup);

	/// Create one submesh
	Ogre::SubMesh* sub = msh->createSubMesh();
	
	/// Create vertex data structure for vertices shared between submeshes
	msh->sharedVertexData = new Ogre::VertexData();
	msh->sharedVertexData->vertexCount = numpoints;

	/// Create declaration (memory format) of vertex data
	Ogre::VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
	decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	//offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		decl->getVertexSize(0), msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	/// Upload the vertex data to the card
	vbuf->writeData(0, vbuf->getSizeInBytes(), parray, true);

	/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	Ogre::VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
	bind->setBinding(0, vbuf);

	sub->useSharedVertices = true;
	sub->operationType = Ogre::RenderOperation::OT_POINT_LIST;
	

	msh->load();
}

void OViSEPointcloud::update(int size, float *points)
{
	float *pPArray = static_cast<float*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	for(int i=0; i<size*3; i+=3)
	{
		pPArray[i] = points[i];
		pPArray[i+1] = points[i+1];
		pPArray[i+2] = points[i+2];
	}
	vbuf->unlock();
}

OViSEPointcloud::~OViSEPointcloud()
{

}