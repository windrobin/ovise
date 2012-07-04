#ifndef OVISE_XMLRPC_WRONG_EXCEPTION_H
#define OVISE_XMLRPC_WRONG_EXCEPTION_H

#include <exception>

/** Exception class which is used in the template functions
*/
class WrongDataTypeException : public std::exception
{
public:
	WrongDataTypeException() {}

	virtual const char* what() const throw()
	{
		return "WrongDataTypeException: Wrong datatype used; only 'int', 'double', 'boolean', 'std::string', 'vec2', 'vec3' and 'quat' are allowed";
	}
};

/**
*/
class WrongParameterNumberException : public std::exception
{
public:
	WrongParameterNumberException() {}

	virtual const char* what() const throw()
	{
		return "WrongParameterNumberException: Wrong number parameter number";
	}
};

#endif   // OVISE_XMLRPC_WRONG_EXCEPTION_H
