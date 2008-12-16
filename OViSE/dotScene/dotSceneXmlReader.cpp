#include "dotSceneXmlReader.h"

/*
 * *********** Implementierung dotSceneXMLReader ********************
 */

dotSceneXmlReader::dotSceneXmlReader(std::string URLofDotSceneXSD, bool DbgMode)
{
	this->mURLofDotSceneXSD = URLofDotSceneXSD;
	this->mDebugMode = DbgMode;
	
	try
	{
		XMLPlatformUtils::Initialize();
		cout << "*** Xerces initialised. ***\n";
	}
	catch (const XMLException& toCatch) 
	{
        char* message = XMLString::transcode(toCatch.getMessage());
        string errmsg = "XERCES: Error during initialization! :\n" + (string)message + "\n";
        Ogre::LogManager::getSingletonPtr()->logMessage(errmsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
    }
	
	TAG_scene             = XMLString::transcode("scene");
	ATTR_formatVersion    = XMLString::transcode("formatVersion");
   	TAG_nodes             = XMLString::transcode("nodes");
   	TAG_node              = XMLString::transcode("node");
   	TAG_environment       = XMLString::transcode("environment");
   	ATTR_name             = XMLString::transcode("name");
	TAG_position          = XMLString::transcode("position");
	ATTR_x                = XMLString::transcode("x");
	ATTR_y                = XMLString::transcode("y");
	ATTR_z                = XMLString::transcode("z");
	TAG_quaternion        = XMLString::transcode("quaternion");
	ATTR_w                = XMLString::transcode("w");
	TAG_scale             = XMLString::transcode("scale");
	TAG_entity            = XMLString::transcode("entity");
	ATTR_meshFile         = XMLString::transcode("meshFile");
	TAG_light             = XMLString::transcode("light");
	TAG_lightRange        = XMLString::transcode("lightRange");
	TAG_normal            = XMLString::transcode("normal");
	TAG_colourDiffuse     = XMLString::transcode("colourDiffuse");
	ATTR_r                = XMLString::transcode("r");
	ATTR_g				  = XMLString::transcode("g");
	ATTR_b                = XMLString::transcode("b");
	TAG_colourSpecular    = XMLString::transcode("colourSpecular");
	TAG_colourAmbient     = XMLString::transcode("colourAmbient");
	TAG_colourBackground  = XMLString::transcode("colourBackground");
	TAG_fog               = XMLString::transcode("fog");
	TAG_lightAttenuation  = XMLString::transcode("lightAttenuation");
	ATTR_range            = XMLString::transcode("range");
	ATTR_constant         = XMLString::transcode("constant");
	ATTR_linear           = XMLString::transcode("linear");
	ATTR_quadratic        = XMLString::transcode("quadratic");
	TAG_camera            = XMLString::transcode("camera");
	ATTR_fov              = XMLString::transcode("fov");
	ATTR_projectionType   = XMLString::transcode("projectionType");
	TAG_clipping          = XMLString::transcode("clipping");
	ATTR_nearPlaneDist    = XMLString::transcode("nearPlaneDist");
	ATTR_farPlaneDist     = XMLString::transcode("farPlaneDist");
	TAG_externals         = XMLString::transcode("externals");
	TAG_item              = XMLString::transcode("item");
	ATTR_type             = XMLString::transcode("type");
	TAG_file              = XMLString::transcode("file");
	ATTR_static           = XMLString::transcode("static");
	ATTR_visible          = XMLString::transcode("visible");
	ATTR_castShadows      = XMLString::transcode("castShadows");
	ATTR_renderingDistance= XMLString::transcode("renderingDistance");
}

bool dotSceneXmlReader::parseDotSceneXML(string URLofXML) // validation only
{
	mParser = new XercesDOMParser();
    mParser->setValidationScheme(XercesDOMParser::Val_Always);    
    mParser->setDoNamespaces(true);    // optional
    mParser->setExternalNoNamespaceSchemaLocation(mURLofDotSceneXSD.c_str());

    mErrHandler = (ErrorHandler*) new HandlerBase();
    mParser->setErrorHandler(mErrHandler);

    try 
    {
		std::cout << "Parsing file " + URLofXML + " ...";
        mParser->parse(URLofXML.c_str());
        std::cout << "success!\n";
    }
    catch (const XMLException& toCatch) 
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        string errmsg = "XERCES: Exception message is: \n" + (string)message + "\n";
        Ogre::LogManager::getSingletonPtr()->logMessage(errmsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
        return false;
    }
    catch (const DOMException& toCatch) 
    {
        char* message = XMLString::transcode(toCatch.msg);
        string errmsg = "XERCES: Exception message is: \n" + (string)message + "\n";
        Ogre::LogManager::getSingletonPtr()->logMessage(errmsg, Ogre::LML_CRITICAL);
        XMLString::release(&message);
        return false;
    }
    catch (...) 
    {
        std::cout << "Unexpected Exception";
        return false;
    }
    
    return true;
}

bool dotSceneXmlReader::importDotScene(/*dotSceneObjects::dotScene Scene*/) 
{
	DOMDocument	*xmlDocument;
	DOMElement	*xmlRootNode;
	DOMNodeList *xmlChildNodeList;
	XMLSize_t	 xmlChildNodeCount = 0;
	DOMNode		*xmlCurrentNode;
	DOMElement	*xmlCurrentElement;
	DOMAttr     *xmlCurrentAttribute;





	// no need to free this pointer - owned by the parent parser object
    xmlDocument = this->mParser->getDocument();

    // Get the top-level element: Name is "root". No attributes for "root"
    xmlRootNode = xmlDocument->getDocumentElement();
    if(!xmlRootNode)
    {
    	std::cout << "Empty RootNode\n";
    }
	else
	{
		std::cout << "No empty RootNode\n";
		
		DOMNamedNodeMap *test = xmlRootNode->getAttributes();

		// Parse XML file for tags of interest: "nodes"/"externals"
		// Look one level nested within "root". (child of root)
		xmlChildNodeList = xmlRootNode->getChildNodes();
		xmlChildNodeCount = xmlChildNodeList->getLength();

		// For all nodes, children of "root" in the XML tree.
		for(XMLSize_t NodeIterator = 0; NodeIterator < xmlChildNodeCount; ++NodeIterator)
		{
			xmlCurrentNode = xmlChildNodeList->item(NodeIterator);
			//xmlCurrentElement = dynamic_cast<xercesc::DOMElement*>(xmlCurrentNode);
			//const XMLCh* dummy = xmlCurrentElement->getNodeName();
			std::string s1;
			switch(xmlCurrentNode->getNodeType())
			{
				case DOMNode::NodeType::ATTRIBUTE_NODE :
					s1 = "ATTRIBUTE_NODE";
					break;
				case DOMNode::NodeType::CDATA_SECTION_NODE :
					s1 = "CDATA_SECTION_NODE";
					break;
				case DOMNode::NodeType::COMMENT_NODE :
					s1 = "COMMENT_NODE";
					break;
				case DOMNode::NodeType::DOCUMENT_FRAGMENT_NODE :
					s1 = "DOCUMENT_FRAGMENT_NODE";
					break;
				case DOMNode::NodeType::DOCUMENT_NODE :
					s1 = "DOCUMENT_NODE";
					break;
				case DOMNode::NodeType::DOCUMENT_TYPE_NODE :
					s1 = "DOCUMENT_TYPE_NODE";
					break;
				case DOMNode::NodeType::ELEMENT_NODE :
					s1 = "ELEMENT_NODE";
					break;
				case DOMNode::NodeType::ENTITY_NODE :
					s1 = "ENTITY_NODE";
					break;
				case DOMNode::NodeType::ENTITY_REFERENCE_NODE :
					s1 = "ENTITY_REFERENCE_NODE";
					break;
				case DOMNode::NodeType::NOTATION_NODE :
					s1 = "NOTATION_NODE";
					break;
				case DOMNode::NodeType::PROCESSING_INSTRUCTION_NODE :
					s1 = "PROCESSING_INSTRUCTION_NODE";
					break;
				case DOMNode::NodeType::TEXT_NODE :
					s1 = "TEXT_NODE";
					break;
				default:
					s1 = "Should not occure!";
					break;
			}
			const XMLCh* dummy2 = xmlCurrentNode->getNodeName();
			const XMLCh* dummy3 = xmlCurrentNode->getNodeValue();
			std::string s2 = XMLString::transcode(dummy2);
			std::string s3;
			if (dummy3 == 0) s3 = "null";
			else s3 = XMLString::transcode(dummy3);
			std::cout << NodeIterator << ": " << s1 << " , " <<  s2 << " , " <<  s3 << "\n";
		}
	}
  	return true;
}



dotSceneObjects::dotSceneObject* dotSceneXmlReader::loadDotScene()
{
	DOMDocument	*xmlDocument;
	DOMElement	*xmlRootNode;

	DOMNodeList *xmlChildNodeList;
	XMLSize_t	 xmlChildNodeCount = 0;
	DOMNode		*xmlCurrentNode;
	DOMElement	*xmlCurrentElement;
	DOMAttr     *xmlCurrentAttribute;

	// no need to free this pointer - owned by the parent parser object
    xmlDocument = this->mParser->getDocument();

    // Get the top-level element: Name is "root". No attributes for "root"
    xmlRootNode = xmlDocument->getDocumentElement();
    if(!xmlRootNode)
    {
    	std::cout << "Empty RootNode\n";
		return 0;
    }
	else
	{
		return this->recursiveNodeProcessing(xmlRootNode);
	}
	return 0;
}

dotSceneObjects::dotSceneObject* dotSceneXmlReader::recursiveNodeProcessing(DOMElement* ParentElement)
{
	DOMNodeList *ChildNodes = ParentElement->getChildNodes();
	XMLSize_t	 ChildCount = ChildNodes->getLength();
	DOMNode		*CurrentNode = 0;
	DOMElement	*CurrentElement = 0;
	const XMLCh* StringBuffer;
	std::string StringBuffer2;

	dotSceneObjects::dotSceneObject* ObjectReturnedFromRecursiveCall = 0;
	dotSceneObjects::dotSceneObject* ObjectForPolymorphReturn = 0;

	// Stage 0
	dotSceneObjects::dotScene* someScene;

	// Stage 1
	dotSceneObjects::dotSceneNodes* someNodes;
	dotSceneObjects::dotSceneEnvironment* someEnvironment;
	dotSceneObjects::dotSceneExternals* someExternals;

	// Stage 2
	dotSceneObjects::dotSceneNode* someNode;
//	dotSceneObjects::dotSceneNode NodeBuffer;
	
	// Stage 3+4
	dotSceneObjects::dotScenePosition* somePosition;
	dotSceneObjects::dotSceneNormal* someNormal;

	dotSceneObjects::dotSceneQuaternion* someQuaternion;
	dotSceneObjects::dotSceneScale* someScale;
	dotSceneObjects::dotSceneCamera* someCamera;
	dotSceneObjects::dotSceneEntity* someEntity;
	dotSceneObjects::dotSceneLight* someLight;
	dotSceneObjects::dotSceneColourAmbient* someColourAmbient;
	dotSceneObjects::dotSceneColourBackground* someColourBackground;
	dotSceneObjects::dotSceneColourDiffuse* someColourDiffuse;
	dotSceneObjects::dotSceneColourSpecular* someColourSpecular;
	dotSceneObjects::dotSceneItem* someItem;
	dotSceneObjects::dotSceneFile* someFile;

	// There is noc switch/case for strings in C+ :-(
	// Here a helper-method is used, to find a matching value of a dotSceneElementaryTags-enum.
	StringBuffer2 = XMLString::transcode(ParentElement->getNodeName());
	dotSceneObjects::dotSceneObject ObjectUsedForIdentificationOfEnumValue = dotSceneObjects::dotSceneObject(StringBuffer2);
	dotSceneEnums::dotSceneElementTags TagType = ObjectUsedForIdentificationOfEnumValue.get_NameSymbol();

	// *************************************** Attribute-Handling *************************************************
	switch(TagType)
	{
		case dotSceneEnums::billboard:
			break;
		case dotSceneEnums::billboardSet:
			break;
		case dotSceneEnums::camera: // not ready!!!
			/*std::cout << " element-identification: 'dotSceneCamera'\n";

			// Create dotSceneObject
			someCamera = new dotSceneObjects::dotSceneCamera();
			ObjectForPolymorphReturn = someCamera;
			
			// Lookup for specialized attributes
			// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
			//			 That marks a not existing attribute.
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someEntity->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			}
			else
			{
				someEntity->set_name("NOT_FOUND_IN_XML");
			}
			std::cout << "Has attribute 'name': \"" << someEntity->get_name() << "\"\n";

			if (ParentElement->hasAttribute(XMLString::transcode("meshFile")))
			{
				someEntity->set_meshFile(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("meshFile"))));
			}
			else
			{
				someEntity->set_meshFile("NOT_FOUND_IN_XML");
			}
			std::cout << "Has attribute 'meshFile': \"" << someEntity->get_meshFile() << "\"\n";
*/
			break;

		case dotSceneEnums::clipping:
			break;
		case dotSceneEnums::colourAmbient:
			// Create dotSceneObject
			someColourAmbient = new dotSceneObjects::dotSceneColourAmbient();
			ObjectForPolymorphReturn = someColourAmbient;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("r"))) someColourAmbient->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
			else someColourAmbient->set_r(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("g")))	someColourAmbient->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
			else someColourAmbient->set_g(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("b")))	someColourAmbient->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
			else someColourAmbient->set_b(0.0);

			std::cout << " element-identification: 'dotSceneColourAmbient'\n";
			std::cout << "Has attribute 'r': \"" << someColourAmbient->get_r() << "\"\n";
			std::cout << "Has attribute 'g': \"" << someColourAmbient->get_g() << "\"\n";
			std::cout << "Has attribute 'b': \"" << someColourAmbient->get_b() << "\"\n";

			break;

		case dotSceneEnums::colourBackground:
			// Create dotSceneObject
			someColourBackground = new dotSceneObjects::dotSceneColourBackground();
			ObjectForPolymorphReturn = someColourBackground;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("r"))) someColourBackground->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
			else someColourBackground->set_r(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("g")))	someColourBackground->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
			else someColourBackground->set_g(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("b")))	someColourBackground->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
			else someColourBackground->set_b(0.0);

			std::cout << " element-identification: 'dotSceneColourBackground'\n";
			std::cout << "Has attribute 'r': \"" << someColourBackground->get_r() << "\"\n";
			std::cout << "Has attribute 'g': \"" << someColourBackground->get_g() << "\"\n";
			std::cout << "Has attribute 'b': \"" << someColourBackground->get_b() << "\"\n";

			break;

		case dotSceneEnums::colourDiffuse:
			// Create dotSceneObject
			someColourDiffuse = new dotSceneObjects::dotSceneColourDiffuse();
			ObjectForPolymorphReturn = someColourDiffuse;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("r"))) someColourDiffuse->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
			else someColourDiffuse->set_r(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("g")))	someColourDiffuse->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
			else someColourDiffuse->set_g(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("b")))	someColourDiffuse->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
			else someColourDiffuse->set_b(0.0);

			//#IMPLIED
			if (ParentElement->hasAttribute(XMLString::transcode("a")))	someColourDiffuse->set_a(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("a"))));

			std::cout << " element-identification: 'dotSceneColourDiffuse'\n";
			std::cout << "Has attribute 'r': \"" << someColourDiffuse->get_r() << "\"\n";
			std::cout << "Has attribute 'g': \"" << someColourDiffuse->get_g() << "\"\n";
			std::cout << "Has attribute 'b': \"" << someColourDiffuse->get_b() << "\"\n";
			std::cout << "Has attribute 'a': \"" << someColourDiffuse->get_a() << "\"\n";

			break;

		case dotSceneEnums::colourSpecular:
			// Create dotSceneObject
			someColourSpecular = new dotSceneObjects::dotSceneColourSpecular();
			ObjectForPolymorphReturn = someColourSpecular;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("r"))) someColourSpecular->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
			else someColourSpecular->set_r(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("g")))	someColourSpecular->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
			else someColourSpecular->set_g(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("b")))	someColourSpecular->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
			else someColourSpecular->set_b(0.0);

			std::cout << " element-identification: 'dotSceneColourSpecular'\n";
			std::cout << "Has attribute 'r': \"" << someColourSpecular->get_r() << "\"\n";
			std::cout << "Has attribute 'g': \"" << someColourSpecular->get_g() << "\"\n";
			std::cout << "Has attribute 'b': \"" << someColourSpecular->get_b() << "\"\n";

			break;

		case dotSceneEnums::entity: // not ready
			// Create dotSceneObject
			someEntity = new dotSceneObjects::dotSceneEntity();
			ObjectForPolymorphReturn = someEntity;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("meshFile"))) someEntity->set_meshFile(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("meshFile"))));
			else someEntity->set_meshFile("NOT_FOUND_IN_XML");

			//#IMPLIED
			if (ParentElement->hasAttribute(XMLString::transcode("name"))) someEntity->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			else someEntity->set_name("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("id"))) someEntity->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
			else someEntity->set_ID("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("materialName"))) someEntity->set_materialName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("materialName"))));
			else someEntity->set_materialName("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("displaySkeleton"))) someEntity->set_displaySkeleton(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("displaySkeleton"))));
			else someEntity->set_displaySkeleton(false);
			if (ParentElement->hasAttribute(XMLString::transcode("polygonModeOverrideable"))) someEntity->set_polygonModeOverrideable(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("polygonModeOverrideable"))));
			else someEntity->set_polygonModeOverrideable(false);
			if (ParentElement->hasAttribute(XMLString::transcode("vertexBufferUsage"))) someEntity->set_vertexBufferUsage(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			else someEntity->set_vertexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage::BufferUsage_staticWriteOnly);
			if (ParentElement->hasAttribute(XMLString::transcode("vertexBufferUseShadow"))) someEntity->set_vertexBufferUseShadow(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			else someEntity->set_vertexBufferUseShadow(false);
			if (ParentElement->hasAttribute(XMLString::transcode("indexBufferUsage"))) someEntity->set_indexBufferUsage(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			else someEntity->set_indexBufferUsage(dotSceneEnums::dotSceneEntityEnums::BufferUsage::BufferUsage_staticWriteOnly);
			if (ParentElement->hasAttribute(XMLString::transcode("indexBufferUseShadow"))) someEntity->set_indexBufferUseShadow(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			else someEntity->set_indexBufferUseShadow(false);

			std::cout << " element-identification: 'dotSceneEntity'\n";
			std::cout << "Has attribute 'meshFile': \"" << someEntity->get_meshFile() << "\"\n";
			std::cout << "Has attribute 'name': \"" << someEntity->get_name() << "\"\n";
			std::cout << "Has attribute 'ID': \"" << someEntity->get_ID() << "\"\n";
			std::cout << "Has attribute 'materialName': \"" << someEntity->get_materialName() << "\"\n";
			std::cout << "Has attribute 'displaySkeleton': \"" << someEntity->get_displaySkeleton() << "\"\n";
			std::cout << "Has attribute 'polygonModeOverrideable': \"" << someEntity->get_polygonModeOverrideable() << "\"\n";
			std::cout << "Has attribute 'vertexBufferUsage': \"" << someEntity->get_vertexBufferUsage() << "\"\n";
			std::cout << "Has attribute 'vertexBufferUseShadow': \"" << someEntity->get_vertexBufferUseShadow() << "\"\n";
			std::cout << "Has attribute 'indexBufferUsage': \"" << someEntity->get_indexBufferUsage() << "\"\n";
			std::cout << "Has attribute 'indexBufferUseShadow': \"" << someEntity->get_indexBufferUseShadow() << "\"\n";

			break;

		case dotSceneEnums::environment:
			std::cout << " element-identification: 'dotSceneEnvironment'\n";

			// Create dotSceneObject
			someEnvironment = new dotSceneObjects::dotSceneEnvironment();
			ObjectForPolymorphReturn = someEnvironment;
			
			// Lookup for specialized attributes
			// HAS NOT POSSIBLE ATRIBUTES (not sure, check that!)
			break;

		case dotSceneEnums::externals:
			std::cout << " element-identification: 'dotSceneExternals'\n";

			// Create dotSceneObject
			someExternals = new dotSceneObjects::dotSceneExternals();
			
			// Lookup for specialized attributes
			// HAS NOT POSSIBLE ATRIBUTES (not sure, check that!)
			break;
		case dotSceneEnums::file:
			std::cout << " element-identification: 'dotSceneFile'\n";

			// Create dotSceneObject
			someFile = new dotSceneObjects::dotSceneFile();
			ObjectForPolymorphReturn = someFile;
			
			// Lookup for specialized attributes
			// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
			//			 That marks a not existing attribute.
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someFile->set_FileName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			}
			else
			{
				someFile->set_FileName("NOT_FOUND_IN_XML");
			}
			std::cout << "Has attribute 'name': \"" << someFile->get_FileName() << "\"\n";
			break;

		case dotSceneEnums::fog:
			break;
		case dotSceneEnums::indexBuffer:
			break;
		case dotSceneEnums::item:
			std::cout << " element-identification: 'dotSceneItem'\n";

			// Create dotSceneObject
			someItem = new dotSceneObjects::dotSceneItem();
			ObjectForPolymorphReturn = someItem;
			
			// Lookup for specialized attributes
			// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
			//			 That marks a not existing attribute.
			if (ParentElement->hasAttribute(XMLString::transcode("type")))
			{
				someItem->set_Type(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("type"))));
			}
			else
			{
				someItem->set_Type("NOT_FOUND_IN_XML");
			}
			std::cout << "Has attribute 'type': \"" << someItem->get_Type() << "\"\n";
			break;

		case dotSceneEnums::light:
			break;
		case dotSceneEnums::lightAttenuation:
			break;
		case dotSceneEnums::lightRange:
			break;
		case dotSceneEnums::localDirection:
			break;
		case dotSceneEnums::lookTarget:
			break;
		case dotSceneEnums::node:
			std::cout << " element-identification: 'dotSceneNode'\n";

			// Create dotSceneObject
			someNode = new dotSceneObjects::dotSceneNode();
			ObjectForPolymorphReturn = someNode;
			
			// Lookup for specialized attributes
			// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
			//			 That marks a not existing attribute.
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someNode->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
			}
			else
			{
				someNode->set_name("NOT_FOUND_IN_XML");
			}

			std::cout << "Has attribute 'name': \"" << someNode->get_name() << "\"\n";
			break;

		case dotSceneEnums::nodes:
			std::cout << " element-identification: 'dotSceneNodes'\n";

			// Create dotSceneObject
			someNodes = new dotSceneObjects::dotSceneNodes();
			ObjectForPolymorphReturn = someNodes;
			
			// Lookup for specialized attributes
			// HAS NOT POSSIBLE ATRIBUTES (not sure, check that!)
			break;

		case dotSceneEnums::normal:
			// Create dotSceneObject
			someNormal = new dotSceneObjects::dotSceneNormal();
			ObjectForPolymorphReturn = someNormal;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("x")))	someNormal->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
			else someNormal->set_x(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("y"))) someNormal->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
			else someNormal->set_y(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("z"))) someNormal->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
			else someNormal->set_z(0.0);
			
			std::cout << " element-identification: 'dotSceneNormal'\n";
			std::cout << "Has attribute 'x': \"" << someNormal->get_x() << "\"\n";
			std::cout << "Has attribute 'y': \"" << someNormal->get_y() << "\"\n";
			std::cout << "Has attribute 'z': \"" << someNormal->get_z() << "\"\n";

			break;

		case dotSceneEnums::octGeometry:
			break;
		case dotSceneEnums::octMaterial:
			break;
		case dotSceneEnums::octMesh:
			break;
		case dotSceneEnums::octNode:
			break;
		case dotSceneEnums::octree:
			break;
		case dotSceneEnums::offset:
			break;
		case dotSceneEnums::particleSystem:
			break;
		case dotSceneEnums::plane:
			break;
		case dotSceneEnums::position:
			// Create dotSceneObject
			somePosition = new dotSceneObjects::dotScenePosition();
			ObjectForPolymorphReturn = somePosition;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("x")))	somePosition->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
			else somePosition->set_x(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("y"))) somePosition->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
			else somePosition->set_y(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("z"))) somePosition->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
			else somePosition->set_z(0.0);
			
			std::cout << " element-identification: 'dotScenePosition'\n";
			std::cout << "Has attribute 'x': \"" << somePosition->get_x() << "\"\n";
			std::cout << "Has attribute 'y': \"" << somePosition->get_y() << "\"\n";
			std::cout << "Has attribute 'z': \"" << somePosition->get_z() << "\"\n";

			break;

		case dotSceneEnums::property_tag:
			break;
		case dotSceneEnums::quaternion:
			// Create dotSceneObject
			someQuaternion = new dotSceneObjects::dotSceneQuaternion();
			ObjectForPolymorphReturn = someQuaternion;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("x"))) someQuaternion->set_qx(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
			else someQuaternion->set_qx("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("y"))) someQuaternion->set_qy(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
			else someQuaternion->set_qy("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("z"))) someQuaternion->set_qz(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
			else someQuaternion->set_qz("NOT_FOUND_IN_XML");
			if (ParentElement->hasAttribute(XMLString::transcode("w"))) someQuaternion->set_qw(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("w"))));
			else someQuaternion->set_qw("NOT_FOUND_IN_XML");

			std::cout << " element-identification: 'dotSceneQuaternion'\n";
			std::cout << "Has attribute 'x': \"" << someQuaternion->get_qx() << "\"\n";
			std::cout << "Has attribute 'y': \"" << someQuaternion->get_qy() << "\"\n";
			std::cout << "Has attribute 'z': \"" << someQuaternion->get_qz() << "\"\n";
			std::cout << "Has attribute 'w': \"" << someQuaternion->get_qw() << "\"\n";

			break;

		case dotSceneEnums::scale:
			// Create dotSceneObject
			someScale = new dotSceneObjects::dotSceneScale();
			ObjectForPolymorphReturn = someScale;
			
			// Lookup for specialized attributes
			//#REQUIRED
			if (ParentElement->hasAttribute(XMLString::transcode("x")))	someScale->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
			else someScale->set_x(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("y"))) someScale->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
			else someScale->set_y(0.0);
			if (ParentElement->hasAttribute(XMLString::transcode("z"))) someScale->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
			else someScale->set_z(0.0);
			
			std::cout << " element-identification: 'dotSceneScale'\n";
			std::cout << "Has attribute 'x': \"" << someScale->get_x() << "\"\n";
			std::cout << "Has attribute 'y': \"" << someScale->get_y() << "\"\n";
			std::cout << "Has attribute 'z': \"" << someScale->get_z() << "\"\n";

			break;

		case dotSceneEnums::scene:
			std::cout << " element-identification: 'dotScene'\n";

			// Create dotSceneObject
			someScene = new dotSceneObjects::dotScene();
			ObjectForPolymorphReturn = someScene;
			
			// Lookup for specialized attributes
			// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
			//			 That marks a not existing attribute.
			if (ParentElement->hasAttribute(XMLString::transcode("formatVersion")))
			{
				someScene->set_formatVersion(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("formatVersion"))));
			}
			else
			{
				someScene->set_formatVersion("NOT_FOUND_IN_XML");
			}

			std::cout << "Has attribute 'formatVersion': \"" << someScene->get_formatVersion() << "\"\n";
			break;

		case dotSceneEnums::skyBox:
			break;
		case dotSceneEnums::skyDome:
			break;
		case dotSceneEnums::skyPlane:
			break;
		case dotSceneEnums::terrain:
			break;
		case dotSceneEnums::trackTarget:
			break;
		case dotSceneEnums::upVector:
			break;
		case dotSceneEnums::userDataReference:
			break;
		case dotSceneEnums::vertexBuffer:
			break;

		// When nothin matches or entire node invalid
		case dotSceneEnums::INVALID:
		default:
			ObjectForPolymorphReturn = 0;
			break;
	}
	// ******************************************************** Attribute-Handling ****************************************
	// ******************************************************** Recursiv Element-Handling *********************************
	// Recursive calls for more detailed dotSceneObjects
	// For all nodes, children of "root" in the XML tree.
	for(XMLSize_t NodeIterator = 0; NodeIterator < ChildCount; ++NodeIterator)
	{
		CurrentNode = ChildNodes->item(NodeIterator);

		// Lookup for ELEMENT_NODE only. If found: recurssive call!
		// INFORMATION: Other node-types are defined for integrity.
		switch(CurrentNode->getNodeType())
		{
			case DOMNode::NodeType::ATTRIBUTE_NODE :				break; // not interesting
			case DOMNode::NodeType::CDATA_SECTION_NODE :			break; // not interesting
			case DOMNode::NodeType::COMMENT_NODE :					break; // not interesting
			case DOMNode::NodeType::DOCUMENT_FRAGMENT_NODE :		break; // not interesting
			case DOMNode::NodeType::DOCUMENT_NODE :					break; // not interesting
			case DOMNode::NodeType::DOCUMENT_TYPE_NODE :			break; // not interesting
			case DOMNode::NodeType::ELEMENT_NODE : 
				// Found node which is an Element. Re-cast node as element
				std::cout << "Found ELEMENT_NODE: ";
    			CurrentElement = dynamic_cast<xercesc::DOMElement*>(CurrentNode);
				ObjectReturnedFromRecursiveCall = this->recursiveNodeProcessing(CurrentElement);
				
				// Identification of dotSceneObject
				// INFORMATION: Other node-types are defined for integrity.
				if (ObjectReturnedFromRecursiveCall != 0)
				{
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
						case dotSceneEnums::billboard:			break; // can not occure
						case dotSceneEnums::billboardSet:		break; // can not occure
						case dotSceneEnums::camera:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									someCamera = dynamic_cast<dotSceneObjects::dotSceneCamera*>(ObjectReturnedFromRecursiveCall);
									someNode->set_camera(*someCamera);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneEntity found! Until now looking for it in: 'dotSceneEnums::node'\n";
									break;
							}
							break;

						case dotSceneEnums::clipping:			break; // can not occure
						case dotSceneEnums::colourAmbient:
							switch(TagType) // look for 
							{
								case dotSceneEnums::environment:
									someColourAmbient = dynamic_cast<dotSceneObjects::dotSceneColourAmbient*>(ObjectReturnedFromRecursiveCall);
									someEnvironment->set_colourAmbient(*someColourAmbient);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneColourAmbient found! Until now looking for it in: 'dotSceneEnums::environment'\n";
									break;
							}
							break;

						case dotSceneEnums::colourBackground:
							switch(TagType) // look for 
							{
								case dotSceneEnums::environment:
									someColourBackground = dynamic_cast<dotSceneObjects::dotSceneColourBackground*>(ObjectReturnedFromRecursiveCall);
									someEnvironment->set_colourBackground(*someColourBackground);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneColourBackground found! Until now looking for it in: 'dotSceneEnums::environment'\n";
									break;
							}
							break;

						case dotSceneEnums::colourDiffuse:		break; // can not occure
						case dotSceneEnums::colourSpecular:		break; // can not occure
						case dotSceneEnums::entity:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									someEntity = dynamic_cast<dotSceneObjects::dotSceneEntity*>(ObjectReturnedFromRecursiveCall);
									someNode->set_entity(*someEntity);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneEntity found! Until now looking for it in: 'dotSceneEnums::node'\n";
									break;
							}
							break;

						case dotSceneEnums::environment:
							switch(TagType) // look for 
							{
								case dotSceneEnums::scene:
									someEnvironment = dynamic_cast<dotSceneObjects::dotSceneEnvironment*>(ObjectReturnedFromRecursiveCall);
									someScene->set_environment(*someEnvironment);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneEntity found! Until now looking for it in: 'dotSceneEnums::scene'\n";
									break;
							}
							break; 

						case dotSceneEnums::externals:
							switch(TagType) // look for 
							{
								case dotSceneEnums::scene:
									someExternals = dynamic_cast<dotSceneObjects::dotSceneExternals*>(ObjectReturnedFromRecursiveCall);
									someScene->set_externals(*someExternals);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneEntity found! Until now looking for it in: 'dotSceneEnums::scene'\n";
									break;
							}
							break;

						case dotSceneEnums::file:
							switch(TagType) // look for 
							{
								case dotSceneEnums::item:
									someFile = dynamic_cast<dotSceneObjects::dotSceneFile*>(ObjectReturnedFromRecursiveCall);
									someItem->set_File(*someFile);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneFile found! Until now looking for it in: 'dotSceneEnums::item'\n";
									break;
							}
							break; 

						case dotSceneEnums::fog:				break; // can not occure
						case dotSceneEnums::indexBuffer:		break; // can not occure
						case dotSceneEnums::item:
							switch(TagType) // look for 
							{
								case dotSceneEnums::externals:
									someItem = dynamic_cast<dotSceneObjects::dotSceneItem*>(ObjectReturnedFromRecursiveCall);
									someExternals->addItem(*someItem);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneItem found! Until now looking for it in: 'dotSceneEnums::externals'\n";
									break;
							}
							break; 

						case dotSceneEnums::light:				break; // can not occure
						case dotSceneEnums::lightAttenuation:	break; // can not occure
						case dotSceneEnums::lightRange:			break; // can not occure
						case dotSceneEnums::localDirection:		break; // can not occure
						case dotSceneEnums::lookTarget:			break; // can not occure
						case dotSceneEnums::node:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									someNode->addChildNode(*(dynamic_cast<dotSceneObjects::dotSceneNode*>(ObjectReturnedFromRecursiveCall)));
									break;
								
								case dotSceneEnums::nodes:
									someNode = dynamic_cast<dotSceneObjects::dotSceneNode*>(ObjectReturnedFromRecursiveCall);
									//NodeBuffer = *someNode;
									//someNodes->addNode(NodeBuffer);
									someNodes->addNode(*someNode);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneNode found! Until now looking for it in: 'dotSceneEnums::node' and 'dotSceneEnums::nodes'\n";
									break;
							}
							break; 

						case dotSceneEnums::nodes:
							switch(TagType) // look for 
							{
								case dotSceneEnums::scene:
									someNodes = dynamic_cast<dotSceneObjects::dotSceneNodes*>(ObjectReturnedFromRecursiveCall);
									someScene->set_nodes(*someNodes);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneNodes found! Until now looking for it in: 'dotSceneEnums::scene'\n";
									break;
							}
							break; 

						case dotSceneEnums::normal:				break; // can not occure
						case dotSceneEnums::octGeometry:		break; // can not occure
						case dotSceneEnums::octMaterial:		break; // can not occure
						case dotSceneEnums::octMesh:			break; // can not occure
						case dotSceneEnums::octNode:			break; // can not occure
						case dotSceneEnums::octree:				break; // can not occure
						case dotSceneEnums::offset:				break; // can not occure
						case dotSceneEnums::particleSystem:		break; // can not occure
						case dotSceneEnums::plane:				break; // can not occure
						case dotSceneEnums::position:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
									someNode->set_position(*somePosition);
									break;

								default: // should not occure
									cerr << "Not assigned dotScenePosition found! Until now looking for it in: 'dotSceneEnums::node'\n";
									break;
							}
							break; 

						case dotSceneEnums::property_tag:		break; // can not occure
						case dotSceneEnums::quaternion:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									someQuaternion = dynamic_cast<dotSceneObjects::dotSceneQuaternion*>(ObjectReturnedFromRecursiveCall);
									someNode->set_quaternion(*someQuaternion);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneQuaternion found! Until now looking for it in: 'dotSceneEnums::node'\n";
									break;
							}
							break; 

						case dotSceneEnums::scale:
							switch(TagType) // look for 
							{
								case dotSceneEnums::node:
									someScale = dynamic_cast<dotSceneObjects::dotSceneScale*>(ObjectReturnedFromRecursiveCall);
									someNode->set_scale(*someScale);
									break;

								default: // should not occure
									cerr << "Not assigned dotSceneScale found! Until now looking for it in: 'dotSceneEnums::node'\n";
									break;
							}
							break; 

						case dotSceneEnums::scene: // should not occure

							break;

						case dotSceneEnums::skyBox:				break; // can not occure
						case dotSceneEnums::skyDome:			break; // can not occure
						case dotSceneEnums::skyPlane:			break; // can not occure
						case dotSceneEnums::terrain:			break; // can not occure
						case dotSceneEnums::trackTarget:		break; // can not occure
						case dotSceneEnums::upVector:			break; // can not occure
						case dotSceneEnums::userDataReference:	break; // can not occure
						case dotSceneEnums::vertexBuffer:		break; // can not occure
						case dotSceneEnums::INVALID:			break; // should not occure
						default:								break; // should not occure
					}
				}
				else std::cout << "Recursive call returned null!\n";
				break;

			case DOMNode::NodeType::ENTITY_NODE :					break; // not interesting
			case DOMNode::NodeType::ENTITY_REFERENCE_NODE :			break; // not interesting
			case DOMNode::NodeType::NOTATION_NODE :					break; // not interesting
			case DOMNode::NodeType::PROCESSING_INSTRUCTION_NODE :	break; // not interesting
			case DOMNode::NodeType::TEXT_NODE :						break; // not interesting
			default:
				// For integrity.
				ObjectReturnedFromRecursiveCall = new dotSceneObjects::dotSceneObject(dotSceneEnums::INVALID);
				break;
		}
	}
	// ******************************************************** Recursiv Element-Handling *********************************

	// Prepare polymorph return
	return ObjectForPolymorphReturn;
}




dotSceneXmlReader::~dotSceneXmlReader()
{
	delete mParser;
    delete mErrHandler;
    try
   	{
    	XMLPlatformUtils::Terminate();  // Terminate Xerces
   	}
   	catch( xercesc::XMLException& e )
   	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		string lgMsg = "Xerces: " + (string)message;
		Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg.c_str(), Ogre::LML_CRITICAL);
		XMLString::release( &message );
	}	   
	
	try
	{
		XMLString::release( &TAG_scene );
		XMLString::release( &TAG_nodes );
		XMLString::release( &TAG_node );
		XMLString::release( &TAG_position );
		XMLString::release( &TAG_quaternion );
		XMLString::release( &TAG_scale );
		XMLString::release( &TAG_entity );
		XMLString::release( &TAG_externals );
		XMLString::release( &TAG_item );
		XMLString::release( &TAG_file );
		XMLString::release( &TAG_light);
		XMLString::release( &TAG_colourDiffuse);
		XMLString::release( &TAG_colourSpecular);
		XMLString::release( &TAG_lightAttenuation);
		XMLString::release( &TAG_camera);
		XMLString::release( &TAG_clipping);
		XMLString::release( &ATTR_name );
		XMLString::release( &ATTR_x );
		XMLString::release( &ATTR_y );
		XMLString::release( &ATTR_z );
		XMLString::release( &ATTR_w );
		XMLString::release( &ATTR_meshFile );
		XMLString::release( &ATTR_type );
		XMLString::release( &ATTR_r);
		XMLString::release( &ATTR_g);
		XMLString::release( &ATTR_b);
		XMLString::release( &ATTR_range);
		XMLString::release( &ATTR_constant);
		XMLString::release( &ATTR_linear);
		XMLString::release( &ATTR_quadratic);
		XMLString::release( &ATTR_fov);
		XMLString::release( &ATTR_projectionType);
		XMLString::release( &ATTR_nearPlaneDist);
		XMLString::release( &ATTR_farPlaneDist);
		XMLString::release( &ATTR_formatVersion );
	}
	catch( ... )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Unknown exception encountered in TAG-release", Ogre::LML_CRITICAL);
	}
}

void main(void)
{
	dotSceneXmlReader *reader = new dotSceneXmlReader("z:/dotScene.xsd", true);
	reader->parseDotSceneXML("Z:/KOS/KOS.xml");
	//reader->importDotScene();
	reader->loadDotScene();

	int dummy;
	std::cin >> dummy;
}