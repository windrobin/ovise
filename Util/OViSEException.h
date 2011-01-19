#pragma once
#ifndef OVISEEXCEPTION_H_
#define OVISEEXCEPTION_H_

// Include STD
#include <string>
#include <exception>

class OViSEException : std::exception
{
public:
	OViSEException(const char* msg);
	
	virtual const char* what() const throw();
	
	virtual ~OViSEException() throw();
	
private:
	std::string mMsg;	
};

#endif /*OVISEEXCEPTION_H_*/
