#include "OViSEPointcloud.h"

OViSEPointcloud::OViSEPointcloud(const std::string& name, std::string material) : Ogre::ManualObject(name)
{
	mMaterialName = material;
}

void OViSEPointcloud::create(int size, float **points)
{
	mSize = size;
	estimateVertexCount(mSize *4);

	Ogre::Vector3 tmp = Ogre::Vector3::ZERO;
	Ogre::Vector3 a(-0.5, -0.5, -0.5);
	Ogre::Vector3 b(0.5, -0.5, 0);
	Ogre::Vector3 c(0, -0.5, 0.5);
	Ogre::Vector3 o(0, 1, 0);

	for(int i=0; i<mSize; i+=3)
	{
		begin(mMaterialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
		tmp = Ogre::Vector3(points[i][0], points[i][1], points[i][2]);
		position(tmp + o);
		normal(Ogre::Vector3(0,1,0));
		position(tmp + a);
		normal(Ogre::Vector3(-1, -1, -1));
		position(tmp + b);
		normal(Ogre::Vector3(1, 0, 0));
		position(tmp + c);
		normal(Ogre::Vector3(0, 0, 1));

		triangle(i, i+1, i+2);
		triangle(i, i+2, i+3);
		triangle(i, i+3, i+1);
		triangle(i+2, i+3, i+1);
		end();
	}
}

void OViSEPointcloud::update(int size, float **points, int index)
{

}

OViSEPointcloud::~OViSEPointcloud(void)
{
}
