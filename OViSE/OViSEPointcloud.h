#pragma once
#include <OgreManualObject.h>

class OViSEPointcloud :	public Ogre::ManualObject
{
public:
	OViSEPointcloud(const std::string& name, std::string material);

	void create(int size, float **points);
	void update(int size, float **points, int index = -1);

	~OViSEPointcloud(void);

private:
	int mSize;
	std::string mMaterialName;
};
