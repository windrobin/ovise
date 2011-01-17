#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H


#include "../Core/EntityPool.h"



/* Class for the Network Interface. To solve dependencies the implementation is hidden in a nested class. */
class NetworkInterface
{
public:

	NetworkInterface(void);
	~NetworkInterface(void);


	void disconnect(void);
	void connectEntityPool(EntityPool* pool);
	void StartListening(void);
	void StopListening(void);

private:
	class NetworkImplementation;
	boost::scoped_ptr<NetworkImplementation>		nImpl;

};


#endif
