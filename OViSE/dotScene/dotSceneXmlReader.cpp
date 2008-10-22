#include "dotSceneXmlReader.h"

/*
 * *********** Implementierung XMLSceneNode**************************
 */
void XMLSceneNode::deleteChildren()
{
	for(vector<XMLSceneNode*>::iterator it = children.begin(); it != children.end(); it++)
	{
		XMLSceneNode *tmp = *it;
		if(tmp->children.size() == 0)
			delete tmp;
		else
			tmp->deleteChildren();
	}
}
/*
 * *********** Implementierung Scene ********************************
 */
Scene::Scene(string name)
{
	mName = name;
}

string Scene::getName()
{
	return mName;
}

int Scene::getNumberOfNodes()
{
	return mNodes.size();
}

XMLSceneNode* Scene::getNodeByName(string name)
{
	for(vector<XMLSceneNode*>::iterator it = mNodes.begin(); it != mNodes.end(); it++)
	{
		if(name.compare((*it)->mName) == 0)
			return *it;
	}
	return NULL;
}

XMLSceneNode* Scene::getNode(int index)
{
	if(index < (int)mNodes.size())
	{
		return mNodes[index];
	}
	return NULL;		
}

bool Scene::addNode(XMLSceneNode *node)
{
	if(node != NULL)
	{
		mNodes.push_back(node);
		return true;
	}
	else return false;
}

Scene::~Scene()
{
	for(vector<XMLSceneNode*>::iterator iter = mNodes.begin(); iter != mNodes.end(); iter++)
	{
		(*iter)->deleteChildren();
	}
}

/*
 * *********** Implementierung DotSceneXMLReader ********************
 */

DotSceneXmlReader::DotSceneXmlReader(std::string URLofDotSceneXSD, bool DbgMode)
{
	mURLofDotSceneXSD = URLofDotSceneXSD;
	mDebugMode = DbgMode;
	
	try
	{
		XMLPlatformUtils::Initialize();
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Xerces initialised. ***");
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

bool DotSceneXmlReader::parseDotSceneXML(string URLofXML)
{
	mParser = new XercesDOMParser();
    mParser->setValidationScheme(XercesDOMParser::Val_Always);    
    mParser->setDoNamespaces(true);    // optional
    mParser->setExternalNoNamespaceSchemaLocation(mURLofDotSceneXSD.c_str());

    mErrHandler = (ErrorHandler*) new HandlerBase();
    mParser->setErrorHandler(mErrHandler);

    try 
    {
    	string logMsg = "Parsing file " + URLofXML + " ...";
    	Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
        mParser->parse(URLofXML.c_str());
        Ogre::LogManager::getSingletonPtr()->logMessage("success!");
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
        Ogre::LogManager::getSingletonPtr()->logMessage("Unexpected Exception", Ogre::LML_CRITICAL);
        return false;
    }
    
    return true;
}

bool DotSceneXmlReader::importDotScene(dotSceneObjects::dotScene *pScene)
{
	try
    {
    	Ogre::LogManager::getSingletonPtr()->logMessage("Processing dotScene...");
    	// no need to free this pointer - owned by the parent parser object
        DOMDocument* xmlDoc = mParser->getDocument();

        // Get the top-level element: Name is "root". No attributes for "root"
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if( !elementRoot )
        {
        	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Empty XML File", Ogre::LML_CRITICAL);
        }
		
		// Parse XML file for tags of interest: "nodes"/"externals"
        // Look one level nested within "root". (child of root)
        DOMNodeList*      children = elementRoot->getChildNodes();
        const  XMLSize_t nodeCount = children->getLength();

        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
        {
    	    DOMNode* currentNode = children->item(xx);
            if( currentNode->getNodeType() &&  // true is not NULL
                currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
         	{
            	// Found node which is an Element. Re-cast node as element
            	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	            // See if we can find the <nodes>-tag and process it
	            if( XMLString::equals(currentElement->getTagName(), TAG_nodes))
	            {
	            	dotSceneObjects::dotSceneNodes currNodes;
	            	// Search for the first <node>-tag and send it to the recursive parseNode() for processing
	            	DOMNodeList* currentNodeChildren = currentNode->getChildNodes();
	            	for(XMLSize_t i = 0; i < currentNodeChildren->getLength(); i++)
	            	{
	            		// Check if current child is a ELEMENT_NODE
	            		DOMNode *hlp = currentNodeChildren->item(i);
	            		if(hlp->getNodeType() == DOMNode::ELEMENT_NODE)
	            		{
	            			DOMElement *hlpElement = dynamic_cast<xercesc::DOMElement*>(hlp);
	            			// Check if it is a <node>-element
	            			if(XMLString::equals(hlpElement->getTagName(), TAG_node))
	            			{
	            				//currNodes.addItem(parseNodeItems(hlp, NULL));
	            			}
	            		}
	            	}
	            	//pScene->set_nodes(currNodes);
	            }
	            if( XMLString::equals(currentElement->getTagName(), TAG_externals))
	            {
	            	dotSceneObjects::dotSceneExternals currExternals;
	            	
	            	//pScene->set_externals(currExternals);
	            }
	         }
      	}
      	Ogre::LogManager::getSingletonPtr()->logMessage("done.");
      	return true;
   	}
   	catch( xercesc::XMLException& e )
   	{
    	char* message = xercesc::XMLString::transcode( e.getMessage() );
      	string logMsg = "Error parsing file: " + (string)message;
      	Ogre::LogManager::getSingletonPtr()->logMessage(logMsg, Ogre::LML_CRITICAL);
      	XMLString::release( &message );
      	return false;
   	}
}

bool DotSceneXmlReader::processDotScene(Scene *newScene)
{
	try
    {
    	Ogre::LogManager::getSingletonPtr()->logMessage("Processing dotScene...");
    	// no need to free this pointer - owned by the parent parser object
        DOMDocument* xmlDoc = mParser->getDocument();

        // Get the top-level element: Name is "root". No attributes for "root"
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if( !elementRoot )
        {
        	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Empty XML File", Ogre::LML_CRITICAL);
        }
		
		// Parse XML file for tags of interest: "nodes"/"externals"
        // Look one level nested within "root". (child of root)
        DOMNodeList*      children = elementRoot->getChildNodes();
        const  XMLSize_t nodeCount = children->getLength();

        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
        {
    	    DOMNode* currentNode = children->item(xx);
            if( currentNode->getNodeType() &&  // true is not NULL
                currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
         	{
            	// Found node which is an Element. Re-cast node as element
            	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	            // See if we can find the <nodes>-tag and process it
	            if( XMLString::equals(currentElement->getTagName(), TAG_nodes))
	            {
	            	// Search for the first <node>-tag and send it to the recursive parseNode() for processing
	            	DOMNodeList* currentNodeChildren = currentNode->getChildNodes();
	            	char logMsg[256];
		        	sprintf(logMsg, "Found %i nodes.", (int)currentNodeChildren->getLength());
			      	Ogre::LogManager::getSingletonPtr()->logMessage(logMsg);
	            	for(XMLSize_t i = 0; i < currentNodeChildren->getLength(); i++)
	            	{
	            		// Check if current child is a ELEMENT_NODE
	            		DOMNode *hlp = currentNodeChildren->item(i);
	            		if(hlp->getNodeType() == DOMNode::ELEMENT_NODE)
	            		{
	            			DOMElement *hlpElement = dynamic_cast<xercesc::DOMElement*>(hlp);
	            			// Check if it is a <node>-element
	            			if(XMLString::equals(hlpElement->getTagName(), TAG_node))
	            			{
	            				newScene->addNode(parseNode(hlp, NULL));
	            				Ogre::LogManager::getSingletonPtr()->logMessage("Added new node to scene.");
	            			}
	            		}
	            	}	            		
	            }
	            if( XMLString::equals(currentElement->getTagName(), TAG_externals))
	            {
	            	
	            }
	         }
      	}
      	Ogre::LogManager::getSingletonPtr()->logMessage("done.");
      	return true;
   	}
   	catch( xercesc::XMLException& e )
   	{
    	char* message = xercesc::XMLString::transcode( e.getMessage() );
      	string logMsg = "Error parsing file: " + (string)message;
      	Ogre::LogManager::getSingletonPtr()->logMessage(logMsg, Ogre::LML_CRITICAL);
      	XMLString::release( &message );
      	return false;
   	}		
}

XMLSceneNode* DotSceneXmlReader::parseNode(DOMNode *node, XMLSceneNode *parent)
{
	DOMNodeList*      children = node->getChildNodes();
    const  XMLSize_t nodeCount = children->getLength();
    XMLSceneNode *currNode = new XMLSceneNode();
    if(parent != NULL)
    	currNode->parent = parent;
    if(node->getNodeType() && node->getNodeType() == DOMNode::ELEMENT_NODE)
    {
    	DOMElement *nodeElement = dynamic_cast<xercesc::DOMElement*>(node);
    	const XMLCh* xmlch_name = nodeElement->getAttribute(ATTR_name);
    	currNode->mName = XMLString::transcode(xmlch_name);
    	string lgMsg = "Xerces: Found Node with name " + currNode->mName;
    	Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg.c_str());
    }
    else
    {
    	char lgMsg[255];
    	sprintf(lgMsg, "Xerces: Found node with type %i. Aborting.", node->getNodeType());
    	Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg);
    	return NULL;
    }
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
    {
	    DOMNode* currentNode = children->item(xx);
        if( currentNode->getNodeType() &&  // true is not NULL
            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
        {
        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
        	if( XMLString::equals(currentElement->getTagName(), TAG_position))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_position");
            	const XMLCh* xmlch_positionx = currentElement->getAttribute(ATTR_x);
                char* poshelperx = XMLString::transcode(xmlch_positionx);
                sscanf(poshelperx, "%lf", &(currNode->mPosition[0]));
                XMLString::release(&poshelperx);
                
                const XMLCh* xmlch_positiony = currentElement->getAttribute(ATTR_y);
                char* poshelpery = XMLString::transcode(xmlch_positiony);
                sscanf(poshelpery, "%lf", &(currNode->mPosition[1]));
                XMLString::release(&poshelpery);
                
                const XMLCh* xmlch_positionz = currentElement->getAttribute(ATTR_z);
                char* poshelperz = XMLString::transcode(xmlch_positionz);
                sscanf(poshelperz, "%lf", &(currNode->mPosition[2]));
                XMLString::release(&poshelperz);
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_quaternion))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_quaternion");
            	const XMLCh* xmlch_quaternionx = currentElement->getAttribute(ATTR_x);
                char* quathelperx = XMLString::transcode(xmlch_quaternionx);
                sscanf(quathelperx, "%lf", &(currNode->mQuaternion[0]));
                XMLString::release(&quathelperx);
                
                const XMLCh* xmlch_quaterniony = currentElement->getAttribute(ATTR_y);
                char* quathelpery = XMLString::transcode(xmlch_quaterniony);
                sscanf(quathelpery, "%lf", &(currNode->mQuaternion[1]));
                XMLString::release(&quathelpery);
                
                const XMLCh* xmlch_quaternionz = currentElement->getAttribute(ATTR_z);
                char* quathelperz = XMLString::transcode(xmlch_quaternionz);
                sscanf(quathelperz, "%lf", &(currNode->mQuaternion[2]));
                XMLString::release(&quathelperz);
                
                const XMLCh* xmlch_quaternionw = currentElement->getAttribute(ATTR_w);
                char* quathelperw = XMLString::transcode(xmlch_quaternionw);
                sscanf(quathelperw, "%lf", &(currNode->mQuaternion[3]));
                XMLString::release(&quathelperw);
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_scale))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_scale");
            	const XMLCh* xmlch_scalex = currentElement->getAttribute(ATTR_x);
                char* scalehelperx = XMLString::transcode(xmlch_scalex);
                sscanf(scalehelperx, "%lf", &(currNode->mScale[0]));
                XMLString::release(&scalehelperx);
                
                const XMLCh* xmlch_scaley = currentElement->getAttribute(ATTR_y);
                char* scalehelpery = XMLString::transcode(xmlch_scaley);
                sscanf(scalehelpery, "%lf", &(currNode->mScale[1]));
                XMLString::release(&scalehelpery);
                
                const XMLCh* xmlch_scalez = currentElement->getAttribute(ATTR_z);
                char* scalehelperz = XMLString::transcode(xmlch_scalez);
                sscanf(scalehelperz, "%lf", &(currNode->mScale[2]));
                XMLString::release(&scalehelperz);
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_entity))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_entity");
            	currNode->mType = XMLSceneNode::ENTITY;
            	const XMLCh* xmlch_entName = currentElement->getAttribute(ATTR_name);
            	currNode->mEntityName = XMLString::transcode(xmlch_entName);
            	const XMLCh* xmlch_entMshFileName = currentElement->getAttribute(ATTR_meshFile);
            	currNode->mEntityMeshFile = XMLString::transcode(xmlch_entMshFileName);
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_light))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_light");
            	currNode->mType = XMLSceneNode::LIGHT;
            	const XMLCh* xmlch_lightName = currentElement->getAttribute(ATTR_name);
            	currNode->mLight.mName = XMLString::transcode(xmlch_lightName);
            	const XMLCh* xmlch_lightType = currentElement->getAttribute(ATTR_type);
            	currNode->mLight.mType = XMLString::transcode(xmlch_lightType);
            	DOMNodeList *lightChilds = currentNode->getChildNodes();
            	const  XMLSize_t l = lightChilds->getLength();
            	for(XMLSize_t i = 0; i < l; i++)
            	{
            		DOMNode *lightChild = lightChilds->item(i);
            		if(lightChild && lightChild->getNodeType() == DOMNode::ELEMENT_NODE)
            		{
            			DOMElement* lightElement = dynamic_cast< xercesc::DOMElement* >( lightChild );
            			if(XMLString::equals(lightElement->getTagName(), TAG_colourDiffuse))
            			{
            				Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_colourDiffuse");
            				const XMLCh* xmlch_colDiffr = lightElement->getAttribute(ATTR_r);
            				char* colhelperr = XMLString::transcode(xmlch_colDiffr);
            				sscanf(colhelperr, "%lf", &(currNode->mLight.mColourDiffuse[0]));
            				XMLString::release(&colhelperr);
            				const XMLCh* xmlch_colDiffg = lightElement->getAttribute(ATTR_g);
            				char* colhelperg = XMLString::transcode(xmlch_colDiffg);
            				sscanf(colhelperg, "%lf", &(currNode->mLight.mColourDiffuse[1]));
            				XMLString::release(&colhelperg);
            				const XMLCh* xmlch_colDiffb = lightElement->getAttribute(ATTR_b);
            				char* colhelperb = XMLString::transcode(xmlch_colDiffb);
            				sscanf(colhelperb, "%lf", &(currNode->mLight.mColourDiffuse[2]));
            				XMLString::release(&colhelperb);
            			}
            			if(XMLString::equals(lightElement->getTagName(), TAG_colourSpecular))
            			{
            				Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_colourSpecular");
            				const XMLCh* xmlch_colSpecr = lightElement->getAttribute(ATTR_r);
            				char* colhelperr = XMLString::transcode(xmlch_colSpecr);
            				sscanf(colhelperr, "%lf", &(currNode->mLight.mColourSpecular[0]));
            				XMLString::release(&colhelperr);
            				const XMLCh* xmlch_colSpecg = lightElement->getAttribute(ATTR_g);
            				char* colhelperg = XMLString::transcode(xmlch_colSpecg);
            				sscanf(colhelperg, "%lf", &(currNode->mLight.mColourSpecular[1]));
            				XMLString::release(&colhelperg);
            				const XMLCh* xmlch_colSpecb = lightElement->getAttribute(ATTR_b);
            				char* colhelperb = XMLString::transcode(xmlch_colSpecb);
            				sscanf(colhelperb, "%lf", &(currNode->mLight.mColourSpecular[2]));
            				XMLString::release(&colhelperb);
            			}
            			if(XMLString::equals(lightElement->getTagName(), TAG_lightAttenuation))
            			{
            				Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_lightAttenuation");
            				const XMLCh* xmlch_range = lightElement->getAttribute(ATTR_range);
            				char* rangehelper = XMLString::transcode(xmlch_range);
            				sscanf(rangehelper, "%lf", &(currNode->mLight.mLightAttenuationRange));
            				XMLString::release(&rangehelper);
            				const XMLCh* xmlch_const = lightElement->getAttribute(ATTR_constant);
            				char* consthelper = XMLString::transcode(xmlch_const);
            				sscanf(consthelper, "%lf", &(currNode->mLight.mLightAttenuationConst));
            				XMLString::release(&consthelper);
            				const XMLCh* xmlch_linear = lightElement->getAttribute(ATTR_linear);
            				char* linearhelper = XMLString::transcode(xmlch_linear);
            				sscanf(linearhelper, "%lf", &(currNode->mLight.mLightAttenuationLinear));
            				XMLString::release(&linearhelper);
            				const XMLCh* xmlch_quad = lightElement->getAttribute(ATTR_quadratic);
            				char* quadhelper = XMLString::transcode(xmlch_quad);
            				sscanf(quadhelper, "%lf", &(currNode->mLight.mLightAttenuationQuad));
            				XMLString::release(&quadhelper);
            			}
            		}
            	}
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_camera))
            {
            	Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_camera");
            	currNode->mType = XMLSceneNode::CAMERA;
            	const XMLCh* xmlch_camName = currentElement->getAttribute(ATTR_name);
            	currNode->mCamera.mName = XMLString::transcode(xmlch_camName);
            	const XMLCh* xmlch_camProjType = currentElement->getAttribute(ATTR_projectionType);
            	currNode->mCamera.mProjectionType = XMLString::transcode(xmlch_camProjType);
            	const XMLCh* xmlch_camFov = currentElement->getAttribute(ATTR_fov);
            	char *fovhelper = XMLString::transcode(xmlch_camFov);
            	sscanf(fovhelper, "%lf", &(currNode->mCamera.mFOV));
            	XMLString::release(&fovhelper);
            	DOMNodeList *camChilds = currentNode->getChildNodes();
            	const  XMLSize_t l = camChilds->getLength();
            	for(XMLSize_t i = 0; i < l; i++)
            	{
            		DOMNode *camChild = camChilds->item(i);
            		if(camChild && camChild->getNodeType() == DOMNode::ELEMENT_NODE)
            		{
            			DOMElement* camElement = dynamic_cast< xercesc::DOMElement* >( camChild );
            			if(XMLString::equals(camElement->getTagName(), TAG_clipping))
            			{
            				Ogre::LogManager::getSingletonPtr()->logMessage("Xerces: Found TAG_clipping");
            				const XMLCh* xmlch_clipNPDist = camElement->getAttribute(ATTR_nearPlaneDist);
            				char* clipNPDhelper = XMLString::transcode(xmlch_clipNPDist);
            				sscanf(clipNPDhelper, "%lf", &(currNode->mCamera.mClippingNearPlaneDist));
            				XMLString::release(&clipNPDhelper);
            				const XMLCh* xmlch_clipFPDist = camElement->getAttribute(ATTR_farPlaneDist);
            				char* clipFPDhelper = XMLString::transcode(xmlch_clipFPDist);
            				sscanf(clipFPDhelper, "%lf", &(currNode->mCamera.mClippingFarPlaneDist));
            				XMLString::release(&clipFPDhelper);
            			}
            		}
            	}
            }
            if( XMLString::equals(currentElement->getTagName(), TAG_node))
            {
            	XMLSceneNode *XMLChildNode = parseNode(currentNode, currNode);
            	currNode->children.push_back(XMLChildNode);
            }
        }
    }
    
    return currNode;           
}

dotSceneObjects::dotSceneObject* DotSceneXmlReader::parseNodeItem(DOMNode *node)
{
	DOMNodeList*      children = node->getChildNodes();
    const  XMLSize_t nodeCount = children->getLength();
    string nodeName = "";
    
    if(node->getNodeType() && node->getNodeType() == DOMNode::ELEMENT_NODE)
    {
    	DOMElement *nodeElement = dynamic_cast<xercesc::DOMElement*>(node);
    	const XMLCh* xmlch_name = nodeElement->getAttribute(ATTR_name);
    	nodeName = XMLString::transcode(xmlch_name);
    	string lgMsg = "Xerces: Found Node with name " + nodeName;
    	Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg.c_str());
    }
    else
    {
    	char lgMsg[255];
    	sprintf(lgMsg, "Xerces: Found node with type %i. Aborting.", node->getNodeType());
    	Ogre::LogManager::getSingletonPtr()->logMessage(lgMsg);
    	return NULL;
    }
    
    // If current Tag is "scene"
    if(strcmp(nodeName.c_str(), "scene") == 0)
    {
    	DOMElement *sceneElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string formatVersion = "";
    	if(sceneElement->hasAttribute(ATTR_formatVersion))
    		formatVersion = XMLString::transcode(sceneElement->getAttribute(ATTR_formatVersion));
    	
    	dotSceneObjects::dotSceneNodes *scene_nodes = NULL;
    	dotSceneObjects::dotSceneExternals *scene_externals = NULL;
    	dotSceneObjects::dotSceneEnvironment *scene_environment = NULL;
    	
    	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_nodes))
	        	{
	        		scene_nodes = (dotSceneObjects::dotSceneNodes*)parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_externals))
	        	{
	        		scene_externals = (dotSceneObjects::dotSceneExternals*)parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_environment))
	        	{
	        		scene_environment = (dotSceneObjects::dotSceneEnvironment*)parseNodeItem(currentNode);
	        	}
	        }
	    }
    	if(scene_nodes == NULL)
    		scene_nodes = new dotSceneObjects::dotSceneNodes();
    	if(scene_externals == NULL)
    		scene_externals = new dotSceneObjects::dotSceneExternals();
    	if(scene_environment == NULL)
    		scene_environment = new dotSceneObjects::dotSceneEnvironment();
    	
    	dotSceneObjects::dotScene *newScene = new dotSceneObjects::dotScene(formatVersion, *scene_nodes, *scene_externals, *scene_environment);
    	return newScene;
    }
    
    // If current Tag is "nodes"
    if(strcmp(nodeName.c_str(), "nodes") == 0)
    {
    	dotSceneObjects::dotSceneNodes *nodes = new dotSceneObjects::dotSceneNodes();
    	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_node))
	        	{
	        		dotSceneObjects::dotSceneNode *tmp = (dotSceneObjects::dotSceneNode*) parseNodeItem(currentNode);
	        		nodes->addItem(*tmp);
	        	}
	        }
	    }
    	return nodes;
    }
    
    // If current Tag is "node"
    if(strcmp(nodeName.c_str(), "node") == 0)
    {
    	DOMElement *nodeElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string name = "";
    	if(nodeElement->hasAttribute(ATTR_name))
    		name = XMLString::transcode(nodeElement->getAttribute(ATTR_name));
    	
    	dotSceneObjects::dotScenePosition *pos = NULL;
    	dotSceneObjects::dotSceneQuaternion *quat = NULL;
    	dotSceneObjects::dotSceneScale *scale = NULL;
    	dotSceneObjects::dotSceneSpecific *specific = NULL;
    	dotSceneObjects::dotSceneNode *tmpNode = new dotSceneObjects::dotSceneNode();
    	
    	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_position))
	        	{
	        		pos = (dotSceneObjects::dotScenePosition*)parseNodeItem(currentNode);
	        		tmpNode->set_position(*pos);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_quaternion))
	        	{
	        		quat = (dotSceneObjects::dotSceneQuaternion*)parseNodeItem(currentNode);
	        		tmpNode->set_quaternion(*quat);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_scale))
	        	{
	        		scale = (dotSceneObjects::dotSceneScale*)parseNodeItem(currentNode);
	        		tmpNode->set_scale(*scale);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_light))
	        	{
	        		specific = (dotSceneObjects::dotSceneSpecific*)parseNodeItem(currentNode);
	        		tmpNode->set_specific(specific);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_camera))
	        	{
	        		specific = (dotSceneObjects::dotSceneSpecific*)parseNodeItem(currentNode);
	        		tmpNode->set_specific(specific);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_entity))
	        	{
	        		specific = (dotSceneObjects::dotSceneSpecific*)parseNodeItem(currentNode);
	        		tmpNode->set_specific(specific);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_node))
	        	{
	        		dotSceneObjects::dotSceneNode *helper = (dotSceneObjects::dotSceneNode*)parseNodeItem(currentNode);
	        		tmpNode->addChildNode(*helper);
	        	}
	        }
	    }
    	return tmpNode;
    }
    
    // If current Tag is "position"
    if(strcmp(nodeName.c_str(), "position") == 0)
    {
    	DOMElement *posElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string x = XMLString::transcode(posElement->getAttribute(ATTR_x));
    	string y = XMLString::transcode(posElement->getAttribute(ATTR_y));
    	string z = XMLString::transcode(posElement->getAttribute(ATTR_z));
    	dotSceneObjects::dotScenePosition *pos = new dotSceneObjects::dotScenePosition(x, y, z);
    	return pos;
    }
    // If current Tag is "quaternion"
    if(strcmp(nodeName.c_str(), "quaternion") == 0)
    {
    	DOMElement *quatElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string x = XMLString::transcode(quatElement->getAttribute(ATTR_x));
    	string y = XMLString::transcode(quatElement->getAttribute(ATTR_y));
    	string z = XMLString::transcode(quatElement->getAttribute(ATTR_z));
    	string w = XMLString::transcode(quatElement->getAttribute(ATTR_w));
    	dotSceneObjects::dotSceneQuaternion *quat = new dotSceneObjects::dotSceneQuaternion(x, y, z, w);
    	return quat;
    }
    // If current Tag is "scale"
    if(strcmp(nodeName.c_str(), "scale") == 0)
    {
    	DOMElement *scaleElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string x = XMLString::transcode(scaleElement->getAttribute(ATTR_x));
    	string y = XMLString::transcode(scaleElement->getAttribute(ATTR_y));
    	string z = XMLString::transcode(scaleElement->getAttribute(ATTR_z));
    	dotSceneObjects::dotSceneScale *scale = new dotSceneObjects::dotSceneScale(x, y, z);
    	return scale;
    }
    
    // If current Tag is "entity"
    if(strcmp(nodeName.c_str(), "entity") == 0)
    {
    	DOMElement *entityElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string entName = XMLString::transcode(entityElement->getAttribute(ATTR_name));
    	string meshFile = XMLString::transcode(entityElement->getAttribute(ATTR_meshFile));
    	string str_static = "0";
    	if(entityElement->hasAttribute(ATTR_static))
    		str_static = XMLString::transcode(entityElement->getAttribute(ATTR_static));
    	string str_visible = "1";
    	if(entityElement->hasAttribute(ATTR_visible))
    		str_visible = XMLString::transcode(entityElement->getAttribute(ATTR_visible));
    	string str_castShadows = "1";
    	if(entityElement->hasAttribute(ATTR_castShadows))
    		str_castShadows = XMLString::transcode(entityElement->getAttribute(ATTR_castShadows));
    	string str_renderingDistance = "1000";
    	if(entityElement->hasAttribute(ATTR_renderingDistance))
    		str_renderingDistance = XMLString::transcode(entityElement->getAttribute(ATTR_renderingDistance));
    	
    	dotSceneObjects::dotSceneEntity *ent = new dotSceneObjects::dotSceneEntity(entName,
    																			   meshFile,
    																			   str_static,
    																			   str_visible,
    																			   str_castShadows,
    																			   str_renderingDistance);
    	return ent;
    }
    
    // If current Tag is "camera"
    if(strcmp(nodeName.c_str(), "camera") == 0)
    {
    	DOMElement *camElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string camName = XMLString::transcode(camElement->getAttribute(ATTR_name));
    	string camFOV = XMLString::transcode(camElement->getAttribute(ATTR_fov));
    	string camProjType = XMLString::transcode(camElement->getAttribute(ATTR_projectionType));
    	
    	dotSceneObjects::dotSceneClipping *clip = NULL;
    	dotSceneObjects::dotSceneNormal *normal = NULL;
    	
    	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_clipping))
	        	{
	        		clip = (dotSceneObjects::dotSceneClipping*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_clipping))
	        	{
	        		normal = (dotSceneObjects::dotSceneNormal*) parseNodeItem(currentNode);
	        	}
	        }
	    }
    	if(clip == NULL)
    		clip = new dotSceneObjects::dotSceneClipping();
    	if(normal == NULL)
    		normal = new dotSceneObjects::dotSceneNormal();
    	dotSceneObjects::dotSceneCamera *cam = new dotSceneObjects::dotSceneCamera(camName,
    																			   camFOV,
    																			   camProjType,
    																			   *normal,
    																			   *clip);
    	return cam;
    }
    
    // If current Tag is "clipping"
    if(strcmp(nodeName.c_str(), "clipping") == 0)
    {
    	DOMElement *clipElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string nearDist = XMLString::transcode(clipElement->getAttribute(ATTR_nearPlaneDist));
    	string farDist = XMLString::transcode(clipElement->getAttribute(ATTR_farPlaneDist));
    	dotSceneObjects::dotSceneClipping *clip = new dotSceneObjects::dotSceneClipping(nearDist, farDist);
    	return clip;
    }
    
    // If current Tag is "light"
    if(strcmp(nodeName.c_str(), "light") == 0)
    {
    	DOMElement* lightElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string lightName = XMLString::transcode(lightElement->getAttribute(ATTR_name));
    	string lightType = XMLString::transcode(lightElement->getAttribute(ATTR_type));
    	
    	dotSceneObjects::dotSceneColourDiffuse *colDiff = NULL;
    	dotSceneObjects::dotSceneColourSpecular *colSpec = NULL;
    	dotSceneObjects::dotSceneNormal *lightNor = NULL;
    	dotSceneObjects::dotSceneLightRange *lRange = NULL;
    	dotSceneObjects::dotSceneLightAttenuation *lightAtt = NULL;
    	
    	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_colourDiffuse))
	        	{
	        		colDiff = (dotSceneObjects::dotSceneColourDiffuse*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_colourSpecular))
	        	{
	        		colSpec = (dotSceneObjects::dotSceneColourSpecular*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_lightAttenuation))
	        	{
	        		lightAtt = (dotSceneObjects::dotSceneLightAttenuation*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_lightRange))
	        	{
	        		lRange = (dotSceneObjects::dotSceneLightRange*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_normal))
	        	{
	        		lightNor = (dotSceneObjects::dotSceneNormal*) parseNodeItem(currentNode);
	        	}
	        }
	    }
    	if(colDiff == NULL)
    		colDiff = new dotSceneObjects::dotSceneColourDiffuse();
    	if(colSpec == NULL)
    		colSpec = new dotSceneObjects::dotSceneColourSpecular();
    	if(lightAtt == NULL)
    		lightAtt = new dotSceneObjects::dotSceneLightAttenuation();
    	if(lightNor == NULL)
    		lightNor = new dotSceneObjects::dotSceneNormal();
    	if(lRange == NULL)
    		lRange = new dotSceneObjects::dotSceneLightRange();
    	dotSceneObjects::dotSceneLight *light = new dotSceneObjects::dotSceneLight(lightName,
    																			   lightType,
    																			   *colDiff,
    																			   *colSpec,
    																			   *lightNor,
    																			   *lRange,
    																			   *lightAtt);
    	return light;
    }
    
    // If current Tag is "colourDiffuse"
    if(strcmp(nodeName.c_str(), "colourDiffuse") == 0)
    {
    	DOMElement *colDiffElement = dynamic_cast<xercesc::DOMElement*>(node);
    	string r = XMLString::transcode(colDiffElement->getAttribute(ATTR_r));
    	string g = XMLString::transcode(colDiffElement->getAttribute(ATTR_g));
    	string b = XMLString::transcode(colDiffElement->getAttribute(ATTR_b));
    	
    	dotSceneObjects::dotSceneColourDiffuse *diff = new dotSceneObjects::dotSceneColourDiffuse(r, g, b);
    	return diff;
    }
    
    // If current Tag is "colourDiffuse"
	if(strcmp(nodeName.c_str(), "colourSpecular") == 0)
	{
		DOMElement *colSpecElement = dynamic_cast<xercesc::DOMElement*>(node);
		string r = XMLString::transcode(colSpecElement->getAttribute(ATTR_r));
		string g = XMLString::transcode(colSpecElement->getAttribute(ATTR_g));
		string b = XMLString::transcode(colSpecElement->getAttribute(ATTR_b));
		
		dotSceneObjects::dotSceneColourSpecular *spec = new dotSceneObjects::dotSceneColourSpecular(r, g, b);
		return spec;
	}
	
	// If current Tag is "lightAttenuation"
	if(strcmp(nodeName.c_str(), "lightAttenuation") == 0)
	{
		DOMElement* lAttElement = dynamic_cast<xercesc::DOMElement*>(node);
		string lrange = XMLString::transcode(lAttElement->getAttribute(ATTR_range));
		string lconst = XMLString::transcode(lAttElement->getAttribute(ATTR_constant));
		string llin = XMLString::transcode(lAttElement->getAttribute(ATTR_linear));
		string lquad = XMLString::transcode(lAttElement->getAttribute(ATTR_quadratic));
		
		dotSceneObjects::dotSceneLightAttenuation *lAtt = new dotSceneObjects::dotSceneLightAttenuation(lrange,
																									    lconst,
																									    llin,
																									    lquad);
		return lAtt;
	}
	
	// If current Tag is "externals"
	if(strcmp(nodeName.c_str(), "externals") == 0)
	{
		dotSceneObjects::dotSceneExternals *ext = new dotSceneObjects::dotSceneExternals();
		
		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_item))
	        	{
	        		string itemtype = XMLString::transcode(currentElement->getAttribute(ATTR_type));
	        		DOMNode *fileNode = currentNode->getFirstChild();
	        		dotSceneObjects::dotSceneFile *f = NULL;
	        		if(fileNode->getNodeType() && fileNode->getNodeType() == DOMNode::ELEMENT_NODE)
	        		{
	        			DOMElement* fileElement = dynamic_cast<xercesc::DOMElement*>(fileNode);
	        			if(XMLString::equals(fileElement->getTagName(), TAG_file))
	        			{
	        				string fname = XMLString::transcode(fileElement->getAttribute(ATTR_name));
	        				f = new dotSceneObjects::dotSceneFile(fname);
	        			}
	        		}
	        		dotSceneObjects::dotSceneItem *i = new dotSceneObjects::dotSceneItem(itemtype, *f);
	        		ext->addItem(*i);
	        	}
	        }
	    }
		return ext;
	}
	
	// If current tag is "environment"
	if(strcmp(nodeName.c_str(), "environment") == 0)
	{
		dotSceneObjects::dotSceneColourAmbient *amb = NULL;
		dotSceneObjects::dotSceneColourBackground *bg = NULL;
		dotSceneObjects::dotSceneFog *fog = NULL;
		
		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	    {
		    DOMNode* currentNode = children->item(xx);
	        if( currentNode->getNodeType() &&  // true is not NULL
	            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	        {
	        	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	        	if(XMLString::equals(currentElement->getTagName(), TAG_colourAmbient))
	        	{
	        		amb = (dotSceneObjects::dotSceneColourAmbient*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_colourBackground))
	        	{
	        		bg = (dotSceneObjects::dotSceneColourBackground*) parseNodeItem(currentNode);
	        	}
	        	if(XMLString::equals(currentElement->getTagName(), TAG_fog))
	        	{
	        		fog = (dotSceneObjects::dotSceneFog*) parseNodeItem(currentNode);
	        	}
	        }
	    }
		if(amb == NULL)
			amb = new dotSceneObjects::dotSceneColourAmbient();
		if(bg == NULL)
			bg = new dotSceneObjects::dotSceneColourBackground();
		if(fog == NULL)
			fog = new dotSceneObjects::dotSceneFog();
		dotSceneObjects::dotSceneEnvironment *env = new dotSceneObjects::dotSceneEnvironment(*fog, *amb, *bg);
		return env;
	}
	
	// If current Tag is "colourAmbient"
	if(strcmp(nodeName.c_str(), "colourAmbient") == 0)
	{
		DOMElement *ambElement = dynamic_cast<xercesc::DOMElement*>(node);
		string r = XMLString::transcode(ambElement->getAttribute(ATTR_r));
		string g = XMLString::transcode(ambElement->getAttribute(ATTR_g));
		string b = XMLString::transcode(ambElement->getAttribute(ATTR_b));
		
		dotSceneObjects::dotSceneColourAmbient *amb = new dotSceneObjects::dotSceneColourAmbient(r, g, b);
		return amb;
	}
	
	// If current Tag is "colourBackground"
	if(strcmp(nodeName.c_str(), "colourBackground") == 0)
	{
		DOMElement *bgElement = dynamic_cast<xercesc::DOMElement*>(node);
		string r = XMLString::transcode(bgElement->getAttribute(ATTR_r));
		string g = XMLString::transcode(bgElement->getAttribute(ATTR_g));
		string b = XMLString::transcode(bgElement->getAttribute(ATTR_b));
		
		dotSceneObjects::dotSceneColourBackground *bg = new dotSceneObjects::dotSceneColourBackground(r, g, b);
		return bg;
	}
	
	// If current Tag is "fog"
	if(strcmp(nodeName.c_str(), "fog") == 0)
	{
		// the xsd says the fog tag is build differently then dotSceneFog.h suggests. needs some fixing here
		dotSceneObjects::dotSceneFog *fog = new dotSceneObjects::dotSceneFog();
		return fog;
	}
    
    return NULL;
}

DotSceneXmlReader::~DotSceneXmlReader()
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
