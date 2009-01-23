#pragma once
#include <OgreManualObject.h>

class OViSEPointcloud :	public Ogre::ManualObject
{
public:
	OViSEPointcloud(const std::string& name);

	/// Create a pointcloud with size points.
	void create(int size, float *points, const std::string material, bool dynamic = true);
	/// Update a created pointcloud with size points.
	void update(int size, float *points, const std::string material, int index = -1, int numpoints = 0);

	virtual ~OViSEPointcloud();

private:
	int mSize;
};
