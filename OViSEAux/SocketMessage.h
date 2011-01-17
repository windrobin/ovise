#ifndef OVISE_SOCKET_MESSAGE_H
#define OVISE_SOCKET_MESSAGE_H

#include "../Core/EntityPool.h"



#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>


#include <xercesc/util/XMLString.hpp>


XERCES_CPP_NAMESPACE_USE
//using namespace xercesc;

/* Class to parse a message recieved by the Socket, and update the EntityPool with the socket Information */
class SocketMessage
{
public:
    SocketMessage();
    ~SocketMessage();

    /* takes the XML definition of an entity. Returns the ID of this Entity. */
    int HandleMessage(const char*);

    int     HandleInsert(DOMElement* root);
    void    HandleUpdate(DOMNodeList* AttributeList, Entity* Rhs);
    void    HandleDelete();

    void connectEntityPool(EntityPool* Pool);


private:
    XercesDOMParser*     mParser;
    DOMDocument*         mDoc;
    EntityPool*          mEntityPool;



};




#endif // OVISE_SOCKET_MESSAGE_H
