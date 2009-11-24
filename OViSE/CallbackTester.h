#ifndef CALLBACK_TESTER_H
#define CALLBACK_TESTER_H

#include "CallbackObject.h"
#include "Pointcloud.h"

class CallbackTester : public CallbackObject
{
public:
	CallbackTester(std::string name);
	~CallbackTester(void);

	void executeCommands();
};
#endif CALLBACK_TESTER_H