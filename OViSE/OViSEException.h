#ifndef OVISEEXCEPTION_H_
#define OVISEEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

class OViSEException : exception
{
public:
	OViSEException(const char* msg);
	
	virtual const char* what() const throw();
	
	virtual ~OViSEException() throw();
	
private:
	string mMsg;	
};

#endif /*OVISEEXCEPTION_H_*/
