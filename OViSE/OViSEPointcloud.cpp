#include "OViSEPointcloud.h"

OViSEPointcloud::OViSEPointcloud(const std::string& name) : Ogre::ManualObject(name)
{
	mSize = 0;
}

void OViSEPointcloud::create(int size, float *points, const std::string material, bool dynamic)
{
	mSize = size;
	this->estimateVertexCount(mSize*4);
	this->setDynamic(dynamic);

	Ogre::Vector3 tmp = Ogre::Vector3::ZERO;
	Ogre::Vector3 a(-0.1, -0.1, -0.1);
	Ogre::Vector3 b(0.1, -0.1, 0);
	Ogre::Vector3 c(0, -0.1, 0.1);
	Ogre::Vector3 o(0, 0.1, 0);

	this->begin(material, Ogre::RenderOperation::OT_TRIANGLE_LIST);

	for(int i=0, j=0; i<mSize*3; i+=3, j+=4)
	{
		tmp = Ogre::Vector3(points[i], points[i+1], points[i+2]);
		this->position(tmp + o);
		this->normal(Ogre::Vector3(0,1,0));
		this->position(tmp + a);
		this->normal(Ogre::Vector3(-1, -1, -1));
		this->position(tmp + b);
		this->normal(Ogre::Vector3(1, 0, 0));
		this->position(tmp + c);
		this->normal(Ogre::Vector3(0, 0, 1));

		this->triangle(j+2, j+1, j);
		this->triangle(j+3, j+2, j);
		this->triangle(j+1, j+3, j);
		this->triangle(j+3, j+1, j+2);
	}
	this->end();
}

void OViSEPointcloud::update(int size, float *points, const std::string material, int index, int numpoints)
{
	if(index == -1)
	{
		// we need to update everything
		this->clear();
		this->create(size, points, material);
	}
	else
	{
		
	}
}

OViSEPointcloud::~OViSEPointcloud()
{
	clear();
}