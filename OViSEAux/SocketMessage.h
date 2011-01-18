#ifndef OVISE_SOCKET_MESSAGE_H
#define OVISE_SOCKET_MESSAGE_H

#include "../Core/EntityPool.h"

#include "../rapidxml-1.13/rapidxml.hpp"

/** Class that processes a network message.
	Parses a message recieved by the Socket, and updates the EntityPool with the socket Information. 
*/
class SocketMessage
{
public:
	SocketMessage();
	virtual ~SocketMessage();

	/** Handles the message.
		\param Message Socket message in XML format
		\returns ID of the entity 
	*/
	int HandleMessage( const char* Message );

	int     HandleInsert( rapidxml::xml_node<>* Node );
	bool    HandleUpdate( rapidxml::xml_node<>* AttributeList, Entity* Rhs);
	void    HandleDelete();

	void	ConnectEntityPool( EntityPool* Pool );


private:
	rapidxml::xml_document<> mDocument;
	EntityPool*				 mEntityPool;
};




#endif // OVISE_SOCKET_MESSAGE_H
