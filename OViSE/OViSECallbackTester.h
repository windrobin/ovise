#pragma once
#include "OViSECallbackObject.h"
#include "OViSEPointcloud.h"

class OViSECallbackTester :
	public OViSECallbackObject
{
public:
	OViSECallbackTester(std::string name);
	~OViSECallbackTester(void);

	void executeCommands();
};
