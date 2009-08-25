#pragma once

#ifndef OVISE_CALLBACKOBJECT_USED
#define OVISE_CALLBACKOBJECT_USED
#include "OViSECallbackObject.h"
#endif

#ifndef OVISE_POINTCLOUD_USED
#define OVISE_POINTCLOUD_USED
#include "OViSEPointcloud.h"
#endif

class OViSECallbackTester :
	public OViSECallbackObject
{
public:
	OViSECallbackTester(std::string name);
	~OViSECallbackTester(void);

	void executeCommands();
};
