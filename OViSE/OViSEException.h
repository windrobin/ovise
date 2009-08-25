#ifndef OVISEEXCEPTION_H_
#define OVISEEXCEPTION_H_

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

#ifndef STD_EXCEPTION_USED
#define STD_EXCEPTION_USED
#include <exception>
#endif

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
