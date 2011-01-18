#include "SocketMessage.h"

#include <xercesc/framework/MemBufInputSource.hpp>

#include <wx/tokenzr.h>
#include <boost/lexical_cast.hpp>

SocketMessage::SocketMessage(void)
{
    XMLPlatformUtils::Initialize();

}

SocketMessage::~SocketMessage(void)
{
    XMLPlatformUtils::Terminate();

}

void SocketMessage::connectEntityPool(EntityPool* Pool) {
    mEntityPool = Pool;
}


int SocketMessage::HandleMessage(const char* Message) {
    //FIXME: check XML data to prevent OViSE crashing when a non valid XML message is recieved!

    XMLCh* TAG_Attributes = XMLString::transcode("Attributes");
    XMLCh* TAG_Action = XMLString::transcode("action");
    XMLCh* TAG_Id = XMLString::transcode("Id");

    mParser = new XercesDOMParser();

    XMLByte* xmlData = (XMLByte*)Message;

    MemBufInputSource source(xmlData, strlen(Message), "dummy");


    mParser->parse( source );


    mDoc = mParser->getDocument();

    DOMElement* root = mDoc->getDocumentElement();

    std::cout << "Socket Message Handling:" << std::endl;


    if (XMLString::equals(root->getAttribute(TAG_Action), XMLString::transcode("insert"))) {
        return HandleInsert(root);
    } else if (XMLString::equals(root->getAttribute(TAG_Action), XMLString::transcode("update"))) {
        DOMNodeList* Id = root->getElementsByTagName(TAG_Id);
        DOMNode* node = Id->item(0);

        HandleUpdate(root->getElementsByTagName(TAG_Attributes)->item(0)->getChildNodes(), mEntityPool->GetEntityById( boost::lexical_cast<int>(XMLString::transcode(node->getTextContent()))));

    } else if (XMLString::equals(root->getAttribute(TAG_Action), XMLString::transcode("delete"))) {
        DOMNodeList* Id = root->getElementsByTagName(TAG_Id);
        DOMNode* node = Id->item(0);

        mEntityPool->RemoveEntityById( boost::lexical_cast<int>(XMLString::transcode(node->getTextContent())));

    }



//    std::cout << "XML Parse Test ende:" << std::endl;



}


/* peform the adding of a new entity to the entity pool
*/
int SocketMessage::HandleInsert(DOMElement* root) {

    Entity* newEntity;

    std::cout << " insert" << std::endl;
    XMLCh* TAG_Name = XMLString::transcode("Name");
    XMLCh* TAG_Attributes = XMLString::transcode("Attributes");
    XMLCh* TAG_Type = XMLString::transcode("type");


    //add the new entity to the pool
    DOMNodeList* Name = root->getElementsByTagName(TAG_Name);
    DOMNode* node = Name->item(0);



    //create the Entity
    newEntity = & (mEntityPool->CreateEntity(XMLString::transcode(node->getTextContent())));





    //extract attributes
    HandleUpdate(root->getElementsByTagName(TAG_Attributes)->item(0)->getChildNodes(), newEntity);


    return newEntity->GetId();

}




/* perform update of an existing entity

*/
void SocketMessage::HandleUpdate(DOMNodeList* AttributeList, Entity* Rhs) {


    XMLCh* TAG_Name = XMLString::transcode("name");
    XMLCh* TAG_Type = XMLString::transcode("type");

    DOMNode* Attribute;



    for (int i = 0; i< AttributeList->getLength(); i++) {
        Attribute = AttributeList->item(i);



        //FIXME: better use a visitor here!
        //TODO: add other attribute types when needed...
        if (XMLString::equals(Attribute->getAttributes()->getNamedItem(TAG_Type)->getNodeValue(), XMLString::transcode("vec3"))) {
        //input of position types
            double pos[3];
            wxStringTokenizer tokenizer(XMLString::transcode(Attribute->getTextContent()), ",");
            //wxString toFormat;
            for (int i = 0; i<3; i++) {
                tokenizer.GetNextToken().ToDouble(&pos[i]);
            }
        Rhs->Set<vec3>(XMLString::transcode(Attribute->getAttributes()->getNamedItem(TAG_Name)->getNodeValue()), vec3( pos[0], pos[1], pos[2] ));

        } else if (XMLString::equals(Attribute->getAttributes()->getNamedItem(TAG_Type)->getNodeValue(), XMLString::transcode("int"))) {
        //input of integers
            Rhs->Set<double>(XMLString::transcode(Attribute->getAttributes()->getNamedItem(TAG_Name)->getNodeValue()), boost::lexical_cast<int>(XMLString::transcode(Attribute->getTextContent()) ));

        } else if (XMLString::equals(Attribute->getAttributes()->getNamedItem(TAG_Type)->getNodeValue(), XMLString::transcode("double"))) {
        //input of floating numbers
            Rhs->Set<double>(XMLString::transcode(Attribute->getAttributes()->getNamedItem(TAG_Name)->getNodeValue()), boost::lexical_cast<double>(XMLString::transcode(Attribute->getTextContent()) ));

        } else {
        //standard is string
            Rhs->Set<std::string>(XMLString::transcode(Attribute->getAttributes()->getNamedItem(TAG_Name)->getNodeValue()), XMLString::transcode(Attribute->getTextContent()));
        }




    }



}


/* perform update of an existing entity
*/
void SocketMessage::HandleDelete() {

}

