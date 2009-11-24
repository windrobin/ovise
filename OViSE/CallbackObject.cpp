#include "CallbackObject.h"

CallbackObject::CallbackObject(std::string name)
{
	mName = name;
}

CallbackObject::~CallbackObject(void)
{
}

std::string CallbackObject::getName()
{
	return mName;
}