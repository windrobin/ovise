#include "OViSECallbackObject.h"

OViSECallbackObject::OViSECallbackObject(std::string name)
{
	mName = name;
}

OViSECallbackObject::~OViSECallbackObject(void)
{
}

std::string OViSECallbackObject::getName()
{
	return mName;
}