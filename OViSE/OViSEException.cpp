#include "OViSEException.h"

OViSEException::OViSEException(const char* msg)
{
	mMsg = string(msg);
}

const char* OViSEException::what() const throw()
{
	return mMsg.c_str();
}

OViSEException::~OViSEException() throw()
{
}
