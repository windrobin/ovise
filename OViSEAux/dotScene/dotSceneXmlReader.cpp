#include "dotSceneXmlReader.h"
// Cut out of Projectmap: "$(WX_HOME)\lib\vc_lib";"C:\lib\wxCode\components\propgrid\lib\vc_lib"
// zusätzliche abhängigkeiten: wxbase28ud.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxcode_msw28ud_propgrid.lib
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

dotSceneObjects::dotScene* dotSceneXmlReader::loadDotScene()
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
    if(!xmlRootNode) std::cout << "Empty RootNode\n";
	else
	{
		dotSceneObjects::dotSceneObject* UnidentifiedReturnObj= this->recursiveNodeProcessing(xmlRootNode);

		if (UnidentifiedReturnObj->get_NameSymbol() == dotSceneEnums::scene)
		{
			dotSceneObjects::dotScene* IdentifiedSceneReturnObj = dynamic_cast<dotSceneObjects::dotScene*>(UnidentifiedReturnObj);
			return IdentifiedSceneReturnObj;
		}
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
	std::string TempEnumAsString;

	dotSceneObjects::dotSceneObject* ObjectForPolymorphReturn = 0;

	// Stage 0
	dotSceneObjects::dotScene* someScene;

	// Stage 1
	dotSceneObjects::dotSceneShadowSettings* someShadowSettings;
	dotSceneObjects::dotSceneNodes* someNodes;
	dotSceneObjects::dotSceneEnvironment* someEnvironment;
	dotSceneObjects::dotSceneExternals* someExternals;

	// Stage 2
	dotSceneObjects::dotSceneNode *someNode, *someChildNode;
	dotSceneObjects::dotSceneLight* someLight;
	dotSceneObjects::dotSceneCamera* someCamera;
	dotSceneObjects::dotSceneShadowTextureConfig* someShadowTextureConfig;
	
	// Stage 3+4
	dotSceneObjects::dotSceneOrientation* someOrientation;
	dotSceneObjects::dotSceneEntity* someEntity;
	dotSceneObjects::dotSceneItem* someItem;
	dotSceneObjects::dotSceneLookTarget* someLookTarget;
	dotSceneObjects::dotSceneTrackTarget* someTrackTarget;
	dotSceneObjects::dotSceneParticleSystem* someParticleSystem;
	dotSceneObjects::dotSceneBillboardSet* someBillboardSet;
	dotSceneObjects::dotSceneBillboard* someBillboard;
	dotSceneObjects::dotSceneTextureCoords* someTextureCoords;
	dotSceneObjects::dotScenePlane* somePlane;

	// Leaf Stages
	dotSceneObjects::dotSceneUserDataReference* someUserDataReference;
	dotSceneObjects::dotSceneQuaternion* someQuaternion;
	dotSceneObjects::dotSceneAxisXYZ* someAxisXYZ;
	dotSceneObjects::dotSceneAngleAxis* someAngleAxis;
	dotSceneObjects::dotSceneDirection* someDirection;
	dotSceneObjects::dotSceneCommonMovableObjectParams* someCommonMovableObjectParams;
	dotSceneObjects::dotSceneColourAmbient* someColourAmbient;
	dotSceneObjects::dotSceneColourBackground* someColourBackground;
	dotSceneObjects::dotSceneColourDiffuse* someColourDiffuse;
	dotSceneObjects::dotSceneColourSpecular* someColourSpecular;
	dotSceneObjects::dotScenePosition* somePosition;
	dotSceneObjects::dotSceneNormal* someNormal;
	dotSceneObjects::dotSceneScale* someScale;
	dotSceneObjects::dotSceneFile* someFile;
	dotSceneObjects::dotSceneSpotLightRange* someSpotLightRange;
	dotSceneObjects::dotSceneLightAttenuation* someLightAttenuation;
	dotSceneObjects::dotSceneLocalDirectionVector* someLocalDirectionVector;
	dotSceneObjects::dotSceneOffset* someOffset;
	dotSceneObjects::dotSceneCommonDirection* someCommonDirection;
	dotSceneObjects::dotSceneCommonUpVector* someCommonUpVector;
	dotSceneObjects::dotSceneFloatRect* someFloatRect;
	dotSceneObjects::dotSceneTextureStacksAndSlices* someTextureStacksAndSlices;
	dotSceneObjects::dotSceneMaterialLODBias* someMaterialLODBias;
	dotSceneObjects::dotSceneMeshLODBias* someMeshLODBias;
	dotSceneObjects::dotSceneUpVector* someUpVector;

	// There is noc switch/case for strings in C++ :-(
	// Here a helper-method is used, to find a matching value of a dotSceneElementaryTags-enum.
	StringBuffer2 = XMLString::transcode(ParentElement->getNodeName());
	dotSceneObjects::dotSceneObject ObjectUsedForIdentificationOfEnumValue = dotSceneObjects::dotSceneObject(StringBuffer2);
	dotSceneEnums::dotSceneElementTags TagType = ObjectUsedForIdentificationOfEnumValue.get_NameSymbol();

	// *************************************** Attribute-Handling *************************************************
	switch(TagType)
	{
		// KNOWLEGE: No errors can occure. If an attribute is not included in element, NOT_FOUND_IN_XMLis used here.
		//			 This marks a not existing attribute.
	case dotSceneEnums::angle_axis:
			std::cout << "Element identified: 'dotSceneAngleAxis'\n";

			// Create dotSceneObject
			someAngleAxis = new dotSceneObjects::dotSceneAngleAxis();
			ObjectForPolymorphReturn = someAngleAxis;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("angle")))
			{
				someAngleAxis->set_Angle(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("angle"))));
				std::cout << "Has attribute 'angle': \"" << someAngleAxis->get_Angle() << "\"\n";
			}
			else someAngleAxis->set_Angle(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("angleUnit")))
			{
				someAngleAxis->set_AngleUnit(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("angleUnit"))));
				std::cout << "Has attribute 'angleUnit': \"" << ((std::string) XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("angleUnit")))) << "\"\n";
			}
			else someAngleAxis->set_AngleUnit("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someAngleAxis->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someAngleAxis->get_x() << "\"\n";
			}
			else someAngleAxis->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someAngleAxis->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someAngleAxis->get_y() << "\"\n";
			}
			else someAngleAxis->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someAngleAxis->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someAngleAxis->get_z() << "\"\n";
			}
			else someAngleAxis->set_z(0.0);

			break;
	case dotSceneEnums::axisXYZ:
			std::cout << "Element identified: 'dotSceneAxisXYZ'\n";

			// Create dotSceneObject
			someAxisXYZ = new dotSceneObjects::dotSceneAxisXYZ();
			ObjectForPolymorphReturn = someAxisXYZ;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("xAxisX")))
			{
				someAxisXYZ->set_xAxisX(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("xAxisX"))));
				std::cout << "Has attribute 'xAxisX': \"" << someAxisXYZ->get_xAxisX() << "\"\n";
			}
			else someAxisXYZ->set_xAxisX(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("xAxisY")))
			{
				someAxisXYZ->set_xAxisY(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("xAxisY"))));
				std::cout << "Has attribute 'xAxisY': \"" << someAxisXYZ->get_xAxisY() << "\"\n";
			}
			else someAxisXYZ->set_xAxisY(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("xAxisZ")))
			{
				someAxisXYZ->set_xAxisZ(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("xAxisZ"))));
				std::cout << "Has attribute 'xAxisZ': \"" << someAxisXYZ->get_xAxisZ() << "\"\n";
			}
			else someAxisXYZ->set_xAxisZ(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("yAxisX")))
			{
				someAxisXYZ->set_yAxisX(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("yAxisX"))));
				std::cout << "Has attribute 'yAxisX': \"" << someAxisXYZ->get_yAxisX() << "\"\n";
			}
			else someAxisXYZ->set_yAxisX(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("yAxisY")))
			{
				someAxisXYZ->set_yAxisY(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("yAxisY"))));
				std::cout << "Has attribute 'yAxisY': \"" << someAxisXYZ->get_yAxisY() << "\"\n";
			}
			else someAxisXYZ->set_yAxisY(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("yAxisZ")))
			{
				someAxisXYZ->set_yAxisZ(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("yAxisZ"))));
				std::cout << "Has attribute 'yAxisZ': \"" << someAxisXYZ->get_yAxisZ() << "\"\n";
			}
			else someAxisXYZ->set_yAxisZ(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("zAxisX")))
			{
				someAxisXYZ->set_zAxisX(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("zAxisX"))));
				std::cout << "Has attribute 'zAxisX': \"" << someAxisXYZ->get_zAxisX() << "\"\n";
			}
			else someAxisXYZ->set_zAxisX(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("zAxisY")))
			{
				someAxisXYZ->set_zAxisY(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("zAxisY"))));
				std::cout << "Has attribute 'zAxisY': \"" << someAxisXYZ->get_zAxisY() << "\"\n";
			}
			else someAxisXYZ->set_zAxisY(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("zAxisZ")))
			{
				someAxisXYZ->set_zAxisZ(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("zAxisZ"))));
				std::cout << "Has attribute 'zAxisZ': \"" << someAxisXYZ->get_zAxisZ() << "\"\n";
			}
			else someAxisXYZ->set_zAxisZ(0.0);

			break;
		case dotSceneEnums::billboard:
			std::cout << "Element identified: 'dotSceneBillboard'\n";

			// Create dotSceneObject
			someBillboard = new dotSceneObjects::dotSceneBillboard();
			ObjectForPolymorphReturn = someBillboard;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someBillboard->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someBillboard->get_ID() << "\"\n";
			}
			else someBillboard->set_ID("NOT_FOUND_IN_XML");			
			
			if (ParentElement->hasAttribute(XMLString::transcode("rotation")))
			{
				someBillboard->set_Rotation(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("rotation"))));
				std::cout << "Has attribute 'rotation': \"" << someBillboard->get_Rotation() << "\"\n";
			}
			else someBillboard->set_Rotation("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("width")))
			{
				someBillboard->set_Width(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("width"))));
				std::cout << "Has attribute 'width': \"" << someBillboard->get_Width() << "\"\n";
			}
			else someBillboard->set_Width("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("height")))
			{
				someBillboard->set_Height(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("height"))));
				std::cout << "Has attribute 'height': \"" << someBillboard->get_Height() << "\"\n";
			}
			else someBillboard->set_Height("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("texcoordIndex")))
			{
				someBillboard->set_TexCoordIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("texcoordIndex"))));
				std::cout << "Has attribute 'texcoordIndex': \"" << someBillboard->get_TexCoordIndex() << "\"\n";
			}
			else someBillboard->set_TexCoordIndex("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::billboardSet:
			std::cout << "Element identified: 'dotSceneBillboardSet'\n";

			// Create dotSceneObject
			someBillboardSet = new dotSceneObjects::dotSceneBillboardSet();
			ObjectForPolymorphReturn = someBillboardSet;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someBillboardSet->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someBillboardSet->get_name() << "\"\n";
			}
			else someBillboardSet->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someBillboardSet->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someBillboardSet->get_ID() << "\"\n";
			}
			else someBillboardSet->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("poolSize")))
			{
				someBillboardSet->set_PoolSize(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("poolSize"))));
				std::cout << "Has attribute 'poolSize': \"" << someBillboardSet->get_PoolSize() << "\"\n";
			}
			else someBillboardSet->set_PoolSize("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("autoextend")))
			{
				someBillboardSet->set_Autoextend(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("autoextend"))));
				if (someBillboardSet->get_Autoextend()) std::cout << "Has attribute 'autoextend': \"true\"\n";
				else std::cout << "Has attribute 'autoextend': \"false\"\n";
			}
			else someBillboardSet->set_Autoextend("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("materialName")))
			{
				someBillboardSet->set_MaterialName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("materialName"))));
				std::cout << "Has attribute 'materialName': \"" << someBillboardSet->get_MaterialName() << "\"\n";
			}
			else someBillboardSet->set_MaterialName("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("defaultWidth")))
			{
				someBillboardSet->set_DefaultWidth(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("defaultWidth"))));
				std::cout << "Has attribute 'defaultWidth': \"" << someBillboardSet->get_DefaultWidth() << "\"\n";
			}
			else someBillboardSet->set_DefaultWidth("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("defaultHeight")))
			{
				someBillboardSet->set_DefaultHeight(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("defaultHeight"))));
				std::cout << "Has attribute 'defaultHeight': \"" << someBillboardSet->get_DefaultHeight() << "\"\n";
			}
			else someBillboardSet->set_DefaultHeight("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("billboardType")))
			{
				TempEnumAsString = XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardType")));
				someBillboardSet->set_BillboardType(TempEnumAsString);
				std::cout << "Has attribute 'billboardType': \"" << TempEnumAsString << "\"\n";
			}
			else someBillboardSet->set_BillboardType("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("billboardOrigin")))
			{
				someBillboardSet->set_BillboardOrigin(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardOrigin"))));
				std::cout << "Has attribute 'billboardOrigin': \"" << ((std::string)XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardOrigin")))) << "\"\n";
			}
			else someBillboardSet->set_BillboardOrigin("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("billboardRotationType")))
			{
				someBillboardSet->set_BillboardRotationType(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardRotationType"))));
				std::cout << "Has attribute 'billboardRotationType': \"" << ((std::string) XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardRotationType")))) << "\"\n";
			}
			else someBillboardSet->set_BillboardRotationType("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("sortingEnabled")))
			{
				someBillboardSet->set_SortingEnabled(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("sortingEnabled"))));
				if (someBillboardSet->get_SortingEnabled()) std::cout << "Has attribute 'sortingEnabled': \"true\"\n";
				else std::cout << "Has attribute 'sortingEnabled': \"false\"\n";
			}
			else someBillboardSet->set_SortingEnabled("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("cullIndividually")))
			{
				someBillboardSet->set_CullIndividually(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("cullIndividually"))));
				if (someBillboardSet->get_CullIndividually()) std::cout << "Has attribute 'cullIndividually': \"true\"\n";
				else std::cout << "Has attribute 'cullIndividually': \"false\"\n";
			}
			else someBillboardSet->set_CullIndividually("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("accurateFacing")))
			{
				someBillboardSet->set_AccurateFacing(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("accurateFacing"))));
				if (someBillboardSet->get_AccurateFacing()) std::cout << "Has attribute 'accurateFacing': \"true\"\n";
				else std::cout << "Has attribute 'accurateFacing': \"false\"\n";
			}
			else someBillboardSet->set_AccurateFacing("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("billboardsInWorldSpace")))
			{
				someBillboardSet->set_BillboardsInWorldSpace(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("billboardsInWorldSpace"))));
				if (someBillboardSet->get_BillboardsInWorldSpace()) std::cout << "Has attribute 'billboardsInWorldSpace': \"true\"\n";
				else std::cout << "Has attribute 'billboardsInWorldSpace': \"false\"\n";
			}
			else someBillboardSet->set_BillboardsInWorldSpace("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("pointRenderingEnabled")))
			{
				someBillboardSet->set_PointRenderingEnabled(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("pointRenderingEnabled"))));
				if (someBillboardSet->get_PointRenderingEnabled()) std::cout << "Has attribute 'pointRenderingEnabled': \"true\"\n";
				else std::cout << "Has attribute 'pointRenderingEnabled': \"false\"\n";
			}
			else someBillboardSet->set_PointRenderingEnabled("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::camera:
			// Not implemented yet.
			break;
		/* not used until environment is implemented
		case dotSceneEnums::colourAmbient:
			std::cout << "Element identified: 'dotSceneColourAmbient'\n";

			// Create dotSceneObject
			someColourAmbient = new dotSceneObjects::dotSceneColourAmbient();
			ObjectForPolymorphReturn = someColourAmbient;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("r")))
			{
				someColourAmbient->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
				std::cout << "Has attribute 'r': \"" << someColourAmbient->get_r() << "\"\n";
			}
			else someColourAmbient->set_r(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("g")))
			{
				someColourAmbient->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
				std::cout << "Has attribute 'g': \"" << someColourAmbient->get_g() << "\"\n";
			}
			else someColourAmbient->set_g(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("b")))
			{
				someColourAmbient->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
				std::cout << "Has attribute 'b': \"" << someColourAmbient->get_b() << "\"\n";
			}
			else someColourAmbient->set_b(0.0);

			break;
		case dotSceneEnums::colourBackground:
			std::cout << "Element identified: 'dotSceneColourBackground'\n";

			// Create dotSceneObject
			someColourBackground = new dotSceneObjects::dotSceneColourBackground();
			ObjectForPolymorphReturn = someColourBackground;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("r")))
			{
				someColourBackground->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
				std::cout << "Has attribute 'r': \"" << someColourBackground->get_r() << "\"\n";
			}
			else someColourBackground->set_r(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("g")))
			{
				someColourBackground->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
				std::cout << "Has attribute 'g': \"" << someColourBackground->get_g() << "\"\n";
			}
			else someColourBackground->set_g(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("b")))
			{
				someColourBackground->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
				std::cout << "Has attribute 'b': \"" << someColourBackground->get_b() << "\"\n";
			}
			else someColourBackground->set_b(0.0);

			break;
			*/
		case dotSceneEnums::colourDiffuse:
			std::cout << "Element identified: 'dotSceneColourDiffuse'\n";

			// Create dotSceneObject
			someColourDiffuse = new dotSceneObjects::dotSceneColourDiffuse();
			ObjectForPolymorphReturn = someColourDiffuse;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("r")))
			{
				someColourDiffuse->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
				std::cout << "Has attribute 'r': \"" << someColourDiffuse->get_r() << "\"\n";
			}
			else someColourDiffuse->set_r(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("g")))
			{
				someColourDiffuse->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
				std::cout << "Has attribute 'g': \"" << someColourDiffuse->get_g() << "\"\n";
			}
			else someColourDiffuse->set_g(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("b")))
			{
				someColourDiffuse->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
				std::cout << "Has attribute 'b': \"" << someColourDiffuse->get_b() << "\"\n";
			}
			else someColourDiffuse->set_b(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("a")))
			{
				someColourDiffuse->set_a(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("a"))));
				std::cout << "Has attribute 'a': \"" << someColourDiffuse->get_a() << "\"\n";
			}
			else someColourDiffuse->set_a(0.0);

			break;
		case dotSceneEnums::colourSpecular:
			std::cout << "Element identified: 'dotSceneColourSpecular'\n";

			// Create dotSceneObject
			someColourSpecular = new dotSceneObjects::dotSceneColourSpecular();
			ObjectForPolymorphReturn = someColourSpecular;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("r")))
			{
				someColourSpecular->set_r(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("r"))));
				std::cout << "Has attribute 'r': \"" << someColourSpecular->get_r() << "\"\n";
			}
			else someColourSpecular->set_r(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("g")))
			{
				someColourSpecular->set_g(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("g"))));
				std::cout << "Has attribute 'g': \"" << someColourSpecular->get_g() << "\"\n";
			}
			else someColourSpecular->set_g(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("b")))
			{
				someColourSpecular->set_b(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("b"))));
				std::cout << "Has attribute 'b': \"" << someColourSpecular->get_b() << "\"\n";
			}
			else someColourSpecular->set_b(0.0);

			break;
		case dotSceneEnums::commonDirection:
			std::cout << "Element identified: 'dotSceneDirection'\n";

			// Create dotSceneObject
			someDirection = new dotSceneObjects::dotSceneDirection();
			ObjectForPolymorphReturn = someDirection;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someDirection->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someDirection->get_x() << "\"\n";
			}
			else someDirection->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someDirection->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someDirection->get_y() << "\"\n";
			}
			else someDirection->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someDirection->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someDirection->get_z() << "\"\n";
			}
			else someDirection->set_z(0.0);

			break;
		case dotSceneEnums::commonMovableObjectParams:
			std::cout << "Element identified: 'dotSceneCommonMovableObjectParams'\n";

			// Create dotSceneObject
			someCommonMovableObjectParams = new dotSceneObjects::dotSceneCommonMovableObjectParams();
			ObjectForPolymorphReturn = someCommonMovableObjectParams;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("static")))
			{
				someCommonMovableObjectParams->set_Static(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("static"))));
				if (someCommonMovableObjectParams->get_Static()) std::cout << "Has attribute 'static': \"true\"\n";
				else std::cout << "Has attribute 'static': \"false\"\n";
			}
			else someCommonMovableObjectParams->set_Static("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("visible")))
			{
				someCommonMovableObjectParams->set_Visible(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("visible"))));
				if (someCommonMovableObjectParams->get_Visible()) std::cout << "Has attribute 'visible': \"true\"\n";
				else std::cout << "Has attribute 'visible': \"false\"\n";
			}
			else someCommonMovableObjectParams->set_Visible("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("castShadows")))
			{
				someCommonMovableObjectParams->set_CastShadows(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("castShadows"))));
				if (someCommonMovableObjectParams->get_CastShadows()) std::cout << "Has attribute 'castShadows': \"true\"\n";
				else std::cout << "Has attribute 'castShadows': \"false\"\n";
			}
			else someCommonMovableObjectParams->set_CastShadows("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("renderingDistance")))
			{
				someCommonMovableObjectParams->set_RenderingDistance(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("renderingDistance"))));
				std::cout << "Has attribute 'renderingDistance': \"" << someCommonMovableObjectParams->get_RenderingDistance() << "\"\n";
			}
			else someCommonMovableObjectParams->set_RenderingDistance("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("queryFlags")))
			{
				someCommonMovableObjectParams->set_QueryFlags(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("queryFlags"))));
				std::cout << "Has attribute 'queryFlags': \"" << someCommonMovableObjectParams->get_QueryFlags() << "\"\n";
			}
			else someCommonMovableObjectParams->set_QueryFlags("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("visibilityFlags")))
			{
				someCommonMovableObjectParams->set_VisibilityFlags(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("visibilityFlags"))));
				std::cout << "Has attribute 'visibilityFlags': \"" << someCommonMovableObjectParams->get_VisibilityFlags() << "\"\n";
			}
			else someCommonMovableObjectParams->set_VisibilityFlags("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::commonUpVector:
			std::cout << "Element identified: 'dotSceneCommonUpVector'\n";

			// Create dotSceneObject
			someCommonUpVector = new dotSceneObjects::dotSceneCommonUpVector();
			ObjectForPolymorphReturn = someCommonUpVector;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someCommonUpVector->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someCommonUpVector->get_x() << "\"\n";
			}
			else someCommonUpVector->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someCommonUpVector->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someCommonUpVector->get_y() << "\"\n";
			}
			else someCommonUpVector->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someCommonUpVector->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someCommonUpVector->get_z() << "\"\n";
			}
			else someCommonUpVector->set_z(0.0);

			break;
		case dotSceneEnums::direction:
			std::cout << "Element identified: 'dotSceneDirection'\n";

			// Create dotSceneObject
			someDirection = new dotSceneObjects::dotSceneDirection();
			ObjectForPolymorphReturn = someDirection;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someDirection->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someDirection->get_x() << "\"\n";
			}
			else someDirection->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someDirection->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someDirection->get_y() << "\"\n";
			}
			else someDirection->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someDirection->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someDirection->get_z() << "\"\n";
			}
			else someDirection->set_z(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("relativeTo")))
			{
				someDirection->set_RelativeTo(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("relativeTo"))));
				std::cout << "Has attribute 'relativeTo': \"" << ((std::string) XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("relativeTo")))) << "\"\n";
			}
			else someDirection->set_RelativeTo("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("localDirX")))
			{
				someDirection->set_LocalDirX(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("localDirX"))));
				std::cout << "Has attribute 'localDirX': \"" << someDirection->get_LocalDirX() << "\"\n";
			}
			else someDirection->set_LocalDirX(0);

			if (ParentElement->hasAttribute(XMLString::transcode("localDirY")))
			{
				someDirection->set_LocalDirY(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("localDirY"))));
				std::cout << "Has attribute 'localDirY': \"" << someDirection->get_LocalDirY() << "\"\n";
			}
			else someDirection->set_LocalDirY(0);

			if (ParentElement->hasAttribute(XMLString::transcode("localDirZ")))
			{
				someDirection->set_LocalDirZ(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("localDirZ"))));
				std::cout << "Has attribute 'localDirZ': \"" << someDirection->get_LocalDirZ() << "\"\n";
			}
			else someDirection->set_LocalDirZ(0.0);

			break;
		case dotSceneEnums::entity:
			std::cout << "Element identified: 'dotSceneEntity'\n";

			// Create dotSceneObject
			someEntity = new dotSceneObjects::dotSceneEntity();
			ObjectForPolymorphReturn = someEntity;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someEntity->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someEntity->get_name() << "\"\n";
			}
			else someEntity->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someEntity->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someEntity->get_ID() << "\"\n";
			}
			else someEntity->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("meshFile")))
			{
				someEntity->set_meshFile(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("meshFile"))));
				std::cout << "Has attribute 'meshFile': \"" << someEntity->get_meshFile() << "\"\n";
			}
			else someEntity->set_meshFile("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("materialName")))
			{
				someEntity->set_materialName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("materialName"))));
				std::cout << "Has attribute 'materialName': \"" << someEntity->get_materialName() << "\"\n";
			}
			else someEntity->set_materialName("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("displaySkeleton")))
			{
				someEntity->set_displaySkeleton(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("displaySkeleton"))));
				if (someEntity->get_displaySkeleton()) std::cout << "Has attribute 'displaySkeleton': \"true\"\n";
				else std::cout << "Has attribute 'displaySkeleton': \"false\"\n";
			}
			else someEntity->set_displaySkeleton("NOT_FOUND_IN_XML");


			if (ParentElement->hasAttribute(XMLString::transcode("polygonModeOverrideable")))
			{
				someEntity->set_polygonModeOverrideable(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("polygonModeOverrideable"))));
				if (someEntity->get_polygonModeOverrideable()) std::cout << "Has attribute 'polygonModeOverrideable': \"true\"\n";
				else std::cout << "Has attribute 'polygonModeOverrideable': \"false\"\n";
			}
			else someEntity->set_polygonModeOverrideable("NOT_FOUND_IN_XML");


			if (ParentElement->hasAttribute(XMLString::transcode("softwareAnimationRequests")))
			{
				someEntity->set_softwareAnimationRequests(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("softwareAnimationRequests"))));
				std::cout << "Has attribute 'softwareAnimationRequests': \"" << someEntity->get_softwareAnimationRequests() << "\"\n";
			}
			else someEntity->set_softwareAnimationRequests("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("softwareAnimationRequestsNormalsAlso")))
			{
				someEntity->set_softwareAnimationRequestsNormalsAlso(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("softwareAnimationRequestsNormalsAlso"))));
				std::cout << "Has attribute 'softwareAnimationRequestsNormalsAlso': \"" << someEntity->get_softwareAnimationRequestsNormalsAlso() << "\"\n";
			}
			else someEntity->set_softwareAnimationRequestsNormalsAlso("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("vertexBufferUsage")))
			{
				TempEnumAsString = XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("vertexBufferUsage")));
				someEntity->set_vertexBufferUsage(TempEnumAsString);
				std::cout << "Has attribute 'vertexBufferUsage': \"" << TempEnumAsString << "\"\n";
			}
			else someEntity->set_vertexBufferUsage("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("vertexBufferUseShadow")))
			{
				someEntity->set_vertexBufferUseShadow(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("vertexBufferUseShadow"))));
				if (someEntity->get_vertexBufferUseShadow()) std::cout << "Has attribute 'vertexBufferUseShadow': \"true\"\n";
				else std::cout << "Has attribute 'vertexBufferUseShadow': \"false\"\n";
			}
			else someEntity->set_vertexBufferUseShadow("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("indexBufferUsage")))
			{
				TempEnumAsString = XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("indexBufferUsage")));
				someEntity->set_indexBufferUsage(TempEnumAsString);
				std::cout << "Has attribute 'indexBufferUsage': \"" << TempEnumAsString << "\"\n";
			}
			else someEntity->set_indexBufferUsage("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("indexBufferUseShadow")))
			{
				someEntity->set_indexBufferUseShadow(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("indexBufferUseShadow"))));
				if (someEntity->get_indexBufferUseShadow()) std::cout << "Has attribute 'indexBufferUseShadow': \"true\"\n";
				else std::cout << "Has attribute 'indexBufferUseShadow': \"false\"\n";
			}
			else someEntity->set_indexBufferUseShadow("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::externals:
			std::cout << "Element identified: 'dotSceneShadowTextureConfig'\n";

			// Create dotSceneObject
			someExternals = new dotSceneObjects::dotSceneExternals();
			ObjectForPolymorphReturn = someExternals;
			break;
		case dotSceneEnums::file:
			std::cout << "Element identified: 'dotSceneFile'\n";

			// Create dotSceneObject
			someFile = new dotSceneObjects::dotSceneFile();
			ObjectForPolymorphReturn = someFile;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someFile->set_FileName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someFile->get_FileName() << "\"\n";
			}
			else someFile->set_FileName("NOT_FOUND_IN_XML");
			
			break;
		case dotSceneEnums::floatRect:
			std::cout << "Element identified: 'dotSceneFloatRect'\n";

			// Create dotSceneObject
			someFloatRect = new dotSceneObjects::dotSceneFloatRect();
			ObjectForPolymorphReturn = someFloatRect;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("left")))
			{
				someFloatRect->set_Left(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("left"))));
				std::cout << "Has attribute 'left': \"" << someFloatRect->get_Left() << "\"\n";
			}
			else someFloatRect->set_Left(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("top")))
			{
				someFloatRect->set_Top(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("top"))));
				std::cout << "Has attribute 'top': \"" << someFloatRect->get_Top() << "\"\n";
			}
			else someFloatRect->set_Top(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("right")))
			{
				someFloatRect->set_Right(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("right"))));
				std::cout << "Has attribute 'right': \"" << someFloatRect->get_Right() << "\"\n";
			}
			else someFloatRect->set_Right(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("bottom")))
			{
				someFloatRect->set_Bottom(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("bottom"))));
				std::cout << "Has attribute 'bottom': \"" << someFloatRect->get_Bottom() << "\"\n";
			}
			else someFloatRect->set_Bottom(0.0);
			
			break;
		case dotSceneEnums::fog:
			break;
		case dotSceneEnums::indexBuffer:
			break;
		case dotSceneEnums::item:
			std::cout << "Element identified: 'dotSceneItem'\n";

			// Create dotSceneObject
			someItem = new dotSceneObjects::dotSceneItem();
			ObjectForPolymorphReturn = someItem;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("type")))
			{
				someItem->set_Type(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("type"))));
				std::cout << "Has attribute 'type': \"" << someItem->get_Type() << "\"\n";
			}
			else someItem->set_Type("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::light:
			std::cout << "Element identified: 'dotSceneLight'\n";

			// Create dotSceneObject
			someLight = new dotSceneObjects::dotSceneLight();
			ObjectForPolymorphReturn = someLight;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someLight->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someLight->get_name() << "\"\n";
			}
			else someLight->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someLight->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someLight->get_ID() << "\"\n";
			}
			else someLight->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("type")))
			{
				someLight->set_Type(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("type"))));
				std::cout << "Has attribute 'type': \"" << someLight->get_Type() << "\"\n";
			}
			else someLight->set_Type("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("powerScale")))
			{
				someLight->set_PowerScale(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("powerScale"))));
				std::cout << "Has attribute 'powerScale': \"" << someLight->get_PowerScale() << "\"\n";
			}
			else someLight->set_PowerScale("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::lightAttenuation:
			std::cout << "Element identified: 'dotSceneLightAttenuation'\n";

			// Create dotSceneObject
			someLightAttenuation = new dotSceneObjects::dotSceneLightAttenuation();
			ObjectForPolymorphReturn = someLightAttenuation;
		
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("range")))
			{
				someLightAttenuation->set_Range(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("range"))));
				std::cout << "Has attribute 'range': \"" << someLightAttenuation->get_Range() << "\"\n";
			}
			else someLightAttenuation->set_Range(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("constant")))
			{
				someLightAttenuation->set_Constant(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("constant"))));
				std::cout << "Has attribute 'constant': \"" << someLightAttenuation->get_Constant() << "\"\n";
			}
			else someLightAttenuation->set_Constant(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("linear")))
			{
				someLightAttenuation->set_Linear(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("linear"))));
				std::cout << "Has attribute 'linear': \"" << someLightAttenuation->get_Linear() << "\"\n";
			}
			else someLightAttenuation->set_Linear(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("quadratic")))
			{
				someLightAttenuation->set_Quadratic(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("quadratic"))));
				std::cout << "Has attribute 'quadratic': \"" << someLightAttenuation->get_Quadratic() << "\"\n";
			}
			else someLightAttenuation->set_Quadratic(0.0);

			break;
		case dotSceneEnums::localDirectionVector:
			std::cout << "Element identified: 'dotSceneLocalDirectionVector'\n";

			// Create dotSceneObject
			someLocalDirectionVector = new dotSceneObjects::dotSceneLocalDirectionVector();
			ObjectForPolymorphReturn = someLocalDirectionVector;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someLocalDirectionVector->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someLocalDirectionVector->get_x() << "\"\n";
			}
			else someLocalDirectionVector->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someLocalDirectionVector->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someLocalDirectionVector->get_y() << "\"\n";
			}
			else someLocalDirectionVector->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someLocalDirectionVector->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someLocalDirectionVector->get_z() << "\"\n";
			}
			else someLocalDirectionVector->set_z(0.0);

			break;
		case dotSceneEnums::lookTarget:
			std::cout << "Element identified: 'dotSceneLookTarget'\n";

			// Create dotSceneObject
			someLookTarget = new dotSceneObjects::dotSceneLookTarget();
			ObjectForPolymorphReturn = someLookTarget;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("nodeName")))
			{
				someLookTarget->set_NodeName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("nodeName"))));
				std::cout << "Has attribute 'nodeName': \"" << someLookTarget->get_NodeName() << "\"\n";
			}
			else someLookTarget->set_NodeName("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("relativeTo")))
			{
				someLookTarget->set_RelativeTo(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("relativeTo"))));
				std::cout << "Has attribute 'relativeTo': \"" << ((std::string) XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("relativeTo")))) << "\"\n";
			}
			else someLookTarget->set_RelativeTo("NOT_FOUND_IN_XML");
			
			break;
		case dotSceneEnums::materialLODBias:
			std::cout << "Element identified: 'dotSceneMaterialLODBias'\n";

			// Create dotSceneObject
			someMaterialLODBias = new dotSceneObjects::dotSceneMaterialLODBias();
			ObjectForPolymorphReturn = someMaterialLODBias;
					
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("factor")))
			{
				someMaterialLODBias->set_Factor(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("factor"))));
				std::cout << "Has attribute 'factor': \"" << someMaterialLODBias->get_Factor() << "\"\n";
			}
			else someMaterialLODBias->set_Factor("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("maxDetailIndex")))
			{
				someMaterialLODBias->set_MaxDetailIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("maxDetailIndex"))));
				std::cout << "Has attribute 'maxDetailIndex': \"" << someMaterialLODBias->get_MaxDetailIndex() << "\"\n";
			}
			else someMaterialLODBias->set_MaxDetailIndex("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("minDetailIndex")))
			{
				someMaterialLODBias->set_MinDetailIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("minDetailIndex"))));
				std::cout << "Has attribute 'minDetailIndex': \"" << someMaterialLODBias->get_MinDetailIndex() << "\"\n";
			}
			else someMaterialLODBias->set_MinDetailIndex("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::meshLODBias:
			std::cout << "Element identified: 'dotSceneMeshLODBias'\n";

			// Create dotSceneObject
			someMeshLODBias = new dotSceneObjects::dotSceneMeshLODBias();
			ObjectForPolymorphReturn = someMeshLODBias;
					
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("factor")))
			{
				someMeshLODBias->set_Factor(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("factor"))));
				std::cout << "Has attribute 'factor': \"" << someMeshLODBias->get_Factor() << "\"\n";
			}
			else someMeshLODBias->set_Factor("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("maxDetailIndex")))
			{
				someMeshLODBias->set_MaxDetailIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("maxDetailIndex"))));
				std::cout << "Has attribute 'maxDetailIndex': \"" << someMeshLODBias->get_MaxDetailIndex() << "\"\n";
			}
			else someMeshLODBias->set_MaxDetailIndex("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("minDetailIndex")))
			{
				someMeshLODBias->set_MinDetailIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("minDetailIndex"))));
				std::cout << "Has attribute 'minDetailIndex': \"" << someMeshLODBias->get_MinDetailIndex() << "\"\n";
			}
			else someMeshLODBias->set_MinDetailIndex("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::node:
			std::cout << "Element identified: 'dotSceneNode'\n";

			// Create dotSceneObject
			someNode = new dotSceneObjects::dotSceneNode();
			ObjectForPolymorphReturn = someNode;
					
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someNode->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someNode->get_name() << "\"\n";
			}
			else someNode->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someNode->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someNode->get_ID() << "\"\n";
			}
			else someNode->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("visible")))
			{
				someNode->set_Visible(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("visible"))));
				if (someNode->get_Visible()) std::cout << "Has attribute 'visible': \"true\"\n";
				else std::cout << "Has attribute 'visible': \"false\"\n";
			}
			else someNode->set_Visible("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("cascadeVisibility")))
			{
				someNode->set_CascadeVisibility(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("cascadeVisibility"))));
				if (someNode->get_CascadeVisibility()) std::cout << "Has attribute 'cascadeVisibility': \"true\"\n";
				else std::cout << "Has attribute 'cascadeVisibility': \"false\"\n";
			}
			else someNode->set_CascadeVisibility("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("isTarget")))
			{
				someNode->set_IsTarget(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("isTarget"))));
				if (someNode->get_IsTarget()) std::cout << "Has attribute 'isTarget': \"true\"\n";
				else std::cout << "Has attribute 'isTarget': \"false\"\n";
			}
			else someNode->set_IsTarget("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::nodes:
			std::cout << "Element identified: 'dotSceneNodes'\n";

			// Create dotSceneObject
			someNodes = new dotSceneObjects::dotSceneNodes();
			ObjectForPolymorphReturn = someNodes;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("visible")))
			{
				someNodes->set_Visible(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("visible"))));
				if (someNodes->get_Visible()) std::cout << "Has attribute 'visible': \"true\"\n";
				else std::cout << "Has attribute 'visible': \"false\"\n";
			}
			else someNodes->set_Visible("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("cascadeVisibility")))
			{
				someNodes->set_CascadeVisibility(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("cascadeVisibility"))));
				if (someNodes->get_CascadeVisibility()) std::cout << "Has attribute 'cascadeVisibility': \"true\"\n";
				else std::cout << "Has attribute 'cascadeVisibility': \"false\"\n";

			}
			else someNodes->set_CascadeVisibility("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::normal:
			std::cout << "Element identified: 'dotSceneNormal'\n";

			// Create dotSceneObject
			someNormal = new dotSceneObjects::dotSceneNormal();
			ObjectForPolymorphReturn = someNormal;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someNormal->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someNormal->get_x() << "\"\n";
			}
			else someNormal->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someNormal->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someNormal->get_y() << "\"\n";
			}
			else someNormal->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someNormal->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someNormal->get_z() << "\"\n";
			}
			else someNormal->set_z(0.0);

			break;
		case dotSceneEnums::orientation:
			std::cout << "Element identified: 'dotSceneOrientation'\n";

			// Create dotSceneObject
			someOrientation = new dotSceneObjects::dotSceneOrientation();
			ObjectForPolymorphReturn = someOrientation;
			break;
		case dotSceneEnums::offset:
			std::cout << "Element identified: 'dotSceneOffset'\n";

			// Create dotSceneObject
			someOffset = new dotSceneObjects::dotSceneOffset();
			ObjectForPolymorphReturn = someOffset;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someOffset->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someOffset->get_x() << "\"\n";
			}
			else someOffset->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someOffset->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someOffset->get_y() << "\"\n";
			}
			else someOffset->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someOffset->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someOffset->get_z() << "\"\n";
			}
			else someOffset->set_z(0.0);

			break;
		case dotSceneEnums::particleSystem:
			std::cout << "Element identified: 'dotSceneParticleSystem'\n";

			// Create dotSceneObject
			someParticleSystem = new dotSceneObjects::dotSceneParticleSystem();
			ObjectForPolymorphReturn = someParticleSystem;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				someParticleSystem->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << someParticleSystem->get_name() << "\"\n";
			}
			else someParticleSystem->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someParticleSystem->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someParticleSystem->get_ID() << "\"\n";
			}
			else someParticleSystem->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("templateName")))
			{
				someParticleSystem->set_TemplateName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("templateName"))));
				std::cout << "Has attribute 'templateName': \"" << someParticleSystem->get_TemplateName() << "\"\n";
			}
			else someParticleSystem->set_TemplateName("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("materialName")))
			{
				someParticleSystem->set_MaterialName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("materialName"))));
				std::cout << "Has attribute 'materialName': \"" << someParticleSystem->get_MaterialName() << "\"\n";
			}
			else someParticleSystem->set_MaterialName("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::plane:
			std::cout << "Element identified: 'dotScenePlane'\n";

			// Create dotSceneObject
			somePlane = new dotSceneObjects::dotScenePlane();
			ObjectForPolymorphReturn = somePlane;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("name")))
			{
				somePlane->set_name(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("name"))));
				std::cout << "Has attribute 'name': \"" << somePlane->get_name() << "\"\n";
			}
			else somePlane->set_name("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				somePlane->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << somePlane->get_ID() << "\"\n";
			}
			else somePlane->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("normalX")))
			{
				somePlane->set_NormalX(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("normalX"))));
				std::cout << "Has attribute 'normalX': \"" << somePlane->get_NormalX() << "\"\n";
			}
			else somePlane->set_NormalX("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("normalY")))
			{
				somePlane->set_NormalY(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("normalY"))));
				std::cout << "Has attribute 'normalY': \"" << somePlane->get_NormalY() << "\"\n";
			}
			else somePlane->set_NormalY("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("normalZ")))
			{
				somePlane->set_NormalZ(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("normalZ"))));
				std::cout << "Has attribute 'normalZ': \"" << somePlane->get_NormalZ() << "\"\n";
			}
			else somePlane->set_NormalZ("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("distance")))
			{
				somePlane->set_Distance(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("distance"))));
				std::cout << "Has attribute 'distance': \"" << somePlane->get_Distance() << "\"\n";
			}
			else somePlane->set_Distance("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("width")))
			{
				somePlane->set_Width(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("width"))));
				std::cout << "Has attribute 'width': \"" << somePlane->get_Width() << "\"\n";
			}
			else somePlane->set_Width("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("height")))
			{
				somePlane->set_Height(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("height"))));
				std::cout << "Has attribute 'height': \"" << somePlane->get_Height() << "\"\n";
			}
			else somePlane->set_Height("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("xSegments")))
			{
				somePlane->set_xSegments(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("xSegments"))));
				std::cout << "Has attribute 'xSegments': \"" << somePlane->get_xSegments() << "\"\n";
			}
			else somePlane->set_xSegments("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("ySegments")))
			{
				somePlane->set_ySegments(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("ySegments"))));
				std::cout << "Has attribute 'ySegments': \"" << somePlane->get_ySegments() << "\"\n";
			}
			else somePlane->set_ySegments("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("normals")))
			{
				somePlane->set_Normals(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("normals"))));
				if (somePlane->get_Normals()) std::cout << "Has attribute 'normals': \"true\"\n";
				else std::cout << "Has attribute 'normals': \"false\"\n";
			}
			else somePlane->set_Normals("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("numTexCoordSets")))
			{
				somePlane->set_NumTexCoordSets(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("numTexCoordSets"))));
				std::cout << "Has attribute 'numTexCoordSets': \"" << somePlane->get_NumTexCoordSets() << "\"\n";
			}
			else somePlane->set_NumTexCoordSets("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("uTile")))
			{
				somePlane->set_UTile(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("uTile"))));
				std::cout << "Has attribute 'uTile': \"" << somePlane->get_UTile() << "\"\n";
			}
			else somePlane->set_UTile("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("vTile")))
			{
				somePlane->set_VTile(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("vTile"))));
				std::cout << "Has attribute 'vTile': \"" << somePlane->get_VTile() << "\"\n";
			}
			else somePlane->set_VTile("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::position:
			std::cout << "Element identified: 'dotScenePosition'\n";

			// Create dotSceneObject
			somePosition = new dotSceneObjects::dotScenePosition();
			ObjectForPolymorphReturn = somePosition;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				somePosition->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << somePosition->get_x() << "\"\n";
			}
			else somePosition->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				somePosition->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << somePosition->get_y() << "\"\n";
			}
			else somePosition->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				somePosition->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << somePosition->get_z() << "\"\n";
			}
			else somePosition->set_z(0.0);

			break;
		case dotSceneEnums::quaternion:
			std::cout << "Element identified: 'dotSceneQuaternion'\n";

			// Create dotSceneObject
			someQuaternion = new dotSceneObjects::dotSceneQuaternion();
			ObjectForPolymorphReturn = someQuaternion;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someQuaternion->set_qx(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someQuaternion->get_qx() << "\"\n";
			}
			else someQuaternion->set_qx(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someQuaternion->set_qy(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someQuaternion->get_qy() << "\"\n";
			}
			else someQuaternion->set_qy(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someQuaternion->set_qz(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someQuaternion->get_qz() << "\"\n";
			}
			else someQuaternion->set_qz(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("w")))
			{
				someQuaternion->set_qw(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("w"))));
				std::cout << "Has attribute 'w': \"" << someQuaternion->get_qw() << "\"\n";
			}
			else someQuaternion->set_qw(0.0);

			break;
		case dotSceneEnums::scale:
			std::cout << "Element identified: 'dotSceneScale'\n";

			// Create dotSceneObject
			someScale = new dotSceneObjects::dotSceneScale();
			ObjectForPolymorphReturn = someScale;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someScale->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someScale->get_x() << "\"\n";
			}
			else someScale->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someScale->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someScale->get_y() << "\"\n";
			}
			else someScale->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someScale->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someScale->get_z() << "\"\n";
			}
			else someScale->set_z(0.0);

			break;
		case dotSceneEnums::scene:
			std::cout << "Element identified: 'dotScene'\n";

			// Create dotSceneObject
			someScene = new dotSceneObjects::dotScene();
			ObjectForPolymorphReturn = someScene;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("formatVersion")))
			{
				someScene->set_FormatVersion(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("formatVersion"))));
				std::cout << "Has attribute 'formatVersion': \"" << someScene->get_FormatVersion() << "\"\n";
			}
			else someScene->set_FormatVersion("NOT_FOUND_IN_XML");
			
			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someScene->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someScene->get_ID() << "\"\n";
			}
			else someScene->set_ID("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("sceneManagerType")))
			{
				someScene->set_SceneManagerType(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("sceneManagerType"))));
				std::cout << "Has attribute 'sceneManagerType': \"" << someScene->get_SceneManagerType() << "\"\n";
			}
			else someScene->set_SceneManagerType("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("sceneManagerName")))
			{
				someScene->set_SceneManagerName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("sceneManagerName"))));
				std::cout << "Has attribute 'sceneManagerName': \"" << someScene->get_SceneManagerName() << "\"\n";
			}
			else someScene->set_SceneManagerName("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("minOgreVersion")))
			{
				someScene->set_MinOgreVersion(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("minOgreVersion"))));
				std::cout << "Has attribute 'minOgreVersion': \"" << someScene->get_MinOgreVersion() << "\"\n";
			}
			else someScene->set_MinOgreVersion("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("author")))
			{
				someScene->set_Author(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("author"))));
				std::cout << "Has attribute 'author': \"" << someScene->get_Author() << "\"\n";
			}
			else someScene->set_Author("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("showBoundingBoxes")))
			{
				someScene->set_ShowBoundingBoxes(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("showBoundingBoxes"))));
				if (someScene->get_ShowBoundingBoxes()) std::cout << "Has attribute 'showBoundingBoxes': \"true\"\n";
				else std::cout << "Has attribute 'showBoundingBoxes': \"false\"\n";
			}
			else someScene->set_ShowBoundingBoxes("NOT_FOUND_IN_XML"); // equals to false, because this sting can not parsed to false or true.
			break;
		
		case dotSceneEnums::shadowSettings:
			std::cout << "Element identified: 'dotSceneShadowSettings'\n";

			// Create dotSceneObject
			someShadowSettings = new dotSceneObjects::dotSceneShadowSettings();
			ObjectForPolymorphReturn = someShadowSettings;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("shadowTechnique")))
			{
				someShadowSettings->set_ShadowTechnique(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTechnique"))));
				std::cout << "Has attribute 'shadowTechnique': \"" << someShadowSettings->get_ShadowTechnique() << "\"\n";
			}
			else someShadowSettings->set_ShadowTechnique("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("showDebugShadows")))
			{
				someShadowSettings->set_ShowDebugShadows(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("showDebugShadows"))));
				if (someShadowSettings->get_ShowDebugShadows()) std::cout << "Has attribute 'showDebugShadows': \"true\"\n";
				else std::cout << "Has attribute 'showDebugShadows': \"false\"\n";
			}
			else someShadowSettings->set_ShadowTechnique("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowFarDistance")))
			{
				someShadowSettings->set_ShadowFarDistance(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowFarDistance"))));
				std::cout << "Has attribute 'shadowFarDistance': \"" << someShadowSettings->get_ShadowFarDistance() << "\"\n";
			}
			else someShadowSettings->set_ShadowFarDistance("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowDirectionalLightExtrusionDistance")))
			{
				someShadowSettings->set_ShadowDirectionalLightExtrusionDistance(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowDirectionalLightExtrusionDistance"))));
				std::cout << "Has attribute 'shadowDirectionalLightExtrusionDistance': \"" << someShadowSettings->get_ShadowDirectionalLightExtrusionDistance() << "\"\n";
			}
			else someShadowSettings->set_ShadowDirectionalLightExtrusionDistance("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowDirectionalLightExtrusionDistance")))
			{
				someShadowSettings->set_ShadowIndexBufferSize(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowIndexBufferSize"))));
				std::cout << "Has attribute 'shadowIndexBufferSize': \"" << someShadowSettings->get_ShadowIndexBufferSize() << "\"\n";
			}
			else someShadowSettings->set_ShadowIndexBufferSize("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowUseInfiniteFarPlane")))
			{
				someShadowSettings->set_ShadowUseInfiniteFarPlane(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowUseInfiniteFarPlane"))));
				if (someShadowSettings->get_ShadowUseInfiniteFarPlane()) std::cout << "Has attribute 'shadowUseInfiniteFarPlane': \"true\"\n";
				else std::cout << "Has attribute 'shadowUseInfiniteFarPlane': \"false\"\n";
			}
			else someShadowSettings->set_ShadowUseInfiniteFarPlane("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureCount")))
			{
				someShadowSettings->set_ShadowTextureCount(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureCount"))));
				std::cout << "Has attribute 'shadowTextureCount': \"" << someShadowSettings->get_ShadowTextureCount() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureCount("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureSize")))
			{
				someShadowSettings->set_ShadowTextureSize(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureSize"))));
				std::cout << "Has attribute 'shadowTextureSize': \"" << someShadowSettings->get_ShadowTextureSize() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureSize("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTexturePixelFormat")))
			{
				someShadowSettings->set_ShadowTexturePixelFormat(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTexturePixelFormat"))));
				std::cout << "Has attribute 'shadowTexturePixelFormat': \"" << XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTexturePixelFormat"))) << "\" interprted as \"" << someShadowSettings->get_ShadowTexturePixelFormat() << "\"\n";
			}
			else someShadowSettings->set_ShadowTexturePixelFormat("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowDirLightTextureOffset")))
			{
				someShadowSettings->set_ShadowDirLightTextureOffset(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowDirLightTextureOffset"))));
				std::cout << "Has attribute 'shadowDirLightTextureOffset': \"" << someShadowSettings->get_ShadowDirLightTextureOffset() << "\"\n";
			}
			else someShadowSettings->set_ShadowDirLightTextureOffset("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureFadeStart")))
			{
				someShadowSettings->set_ShadowTextureFadeStart(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureFadeStart"))));
				std::cout << "Has attribute 'shadowTextureFadeStart': \"" << someShadowSettings->get_ShadowTextureFadeStart() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureFadeStart("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureFadeEnd")))
			{
				someShadowSettings->set_ShadowTextureFadeEnd(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureFadeEnd"))));
				std::cout << "Has attribute 'shadowTextureFadeEnd': \"" << someShadowSettings->get_ShadowTextureFadeEnd() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureFadeEnd("NOT_FOUND_IN_XML");
			
			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureSelfShadow")))
			{
				someShadowSettings->set_ShadowTextureSelfShadow(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureSelfShadow"))));
				if (someShadowSettings->get_ShadowTextureSelfShadow()) std::cout << "Has attribute 'shadowTextureSelfShadow': \"true\"\n";
				else std::cout << "Has attribute 'shadowTextureSelfShadow': \"false\"\n";
			}
			else someShadowSettings->set_ShadowTextureSelfShadow("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureCasterMaterial")))
			{
				someShadowSettings->set_ShadowTextureCasterMaterial(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureCasterMaterial"))));
				std::cout << "Has attribute 'shadowTextureCasterMaterial': \"" << someShadowSettings->get_ShadowTextureCasterMaterial() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureCasterMaterial("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowTextureReceiverMaterial")))
			{
				someShadowSettings->set_ShadowTextureReceiverMaterial(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowTextureReceiverMaterial"))));
				std::cout << "Has attribute 'shadowTextureReceiverMaterial': \"" << someShadowSettings->get_ShadowTextureReceiverMaterial() << "\"\n";
			}
			else someShadowSettings->set_ShadowTextureReceiverMaterial("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("shadowCasterRenderBackFaces")))
			{
				someShadowSettings->set_ShadowCasterRenderBackFaces(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowCasterRenderBackFaces"))));
				if (someShadowSettings->get_ShadowCasterRenderBackFaces()) std::cout << "Has attribute 'shadowCasterRenderBackFaces': \"true\"\n";
				else std::cout << "Has attribute 'shadowCasterRenderBackFaces': \"false\"\n";
			}
			else someShadowSettings->set_ShadowCasterRenderBackFaces("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::shadowTextureConfig:
			std::cout << "Element identified: 'dotSceneShadowTextureConfig'\n";

			// Create dotSceneObject
			someShadowTextureConfig = new dotSceneObjects::dotSceneShadowTextureConfig();
			ObjectForPolymorphReturn = someShadowTextureConfig;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("shadowIndex")))
			{
				someShadowTextureConfig->set_ShadowIndex(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("shadowIndex"))));
				std::cout << "Has attribute 'shadowIndex': \"" << someShadowTextureConfig->get_ShadowIndex() << "\"\n";
			}
			else someShadowTextureConfig->set_ShadowIndex("NOT_FOUND_IN_XML");
		
			if (ParentElement->hasAttribute(XMLString::transcode("width")))
			{
				someShadowTextureConfig->set_Width(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("width"))));
				std::cout << "Has attribute 'width': \"" << someShadowTextureConfig->get_Width() << "\"\n";
			}
			else someShadowTextureConfig->set_Width("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("height")))
			{
				someShadowTextureConfig->set_Height(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("height"))));
				std::cout << "Has attribute 'height': \"" << someShadowTextureConfig->get_Height() << "\"\n";
			}
			else someShadowTextureConfig->set_Height("NOT_FOUND_IN_XML");

			if (ParentElement->hasAttribute(XMLString::transcode("pixelFormat")))
			{
				someShadowTextureConfig->set_PixelFormat(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("pixelFormat"))));
				std::cout << "Has attribute 'pixelFormat': \"" << XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("pixelFormat"))) << "\" interprted as \"" << someShadowTextureConfig->get_PixelFormat() << "\"\n";
			}
			else someShadowTextureConfig->set_PixelFormat("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::spotLightRange:
			std::cout << "Element identified: 'dotSceneSpotLightRange'\n";

			// Create dotSceneObject
			someSpotLightRange = new dotSceneObjects::dotSceneSpotLightRange();
			ObjectForPolymorphReturn = someSpotLightRange;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("inner")))
			{
				someSpotLightRange->set_Inner(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("inner"))));
				std::cout << "Has attribute 'inner': \"" << someSpotLightRange->get_Inner() << "\"\n";
			}
			else someSpotLightRange->set_Inner(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("outer")))
			{
				someSpotLightRange->set_Outer(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("outer"))));
				std::cout << "Has attribute 'outer': \"" << someSpotLightRange->get_Outer() << "\"\n";
			}
			else someSpotLightRange->set_Outer(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("falloff")))
			{
				someSpotLightRange->set_Falloff(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("falloff"))));
				std::cout << "Has attribute 'falloff': \"" << someSpotLightRange->get_Falloff() << "\"\n";
			}
			else someSpotLightRange->set_Falloff(0.0);

			break;
		case dotSceneEnums::textureCoords:
			std::cout << "Element identified: 'dotSceneTextureCoords'\n";

			// Create dotSceneObject
			someTextureCoords = new dotSceneObjects::dotSceneTextureCoords();
			ObjectForPolymorphReturn = someTextureCoords;
			break;
		case dotSceneEnums::textureStacksAndSlices:
			std::cout << "Element identified: 'dotSceneTrackTarget'\n";

			// Create dotSceneObject
			someTextureStacksAndSlices = new dotSceneObjects::dotSceneTextureStacksAndSlices();
			ObjectForPolymorphReturn = someTextureStacksAndSlices;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("stacks")))
			{
				someTextureStacksAndSlices->set_Stacks(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("stacks"))));
				std::cout << "Has attribute 'stacks': \"" << someTextureStacksAndSlices->get_Stacks() << "\"\n";
			}
			else someTextureStacksAndSlices->set_Stacks("NOT_FOUND_IN_XML");
			
			if (ParentElement->hasAttribute(XMLString::transcode("slices")))
			{
				someTextureStacksAndSlices->set_Slices(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("slices"))));
				std::cout << "Has attribute 'slices': \"" << someTextureStacksAndSlices->get_Slices() << "\"\n";
			}
			else someTextureStacksAndSlices->set_Slices("NOT_FOUND_IN_XML");

			break;
		case dotSceneEnums::trackTarget:
			std::cout << "Element identified: 'dotSceneTrackTarget'\n";

			// Create dotSceneObject
			someTrackTarget = new dotSceneObjects::dotSceneTrackTarget();
			ObjectForPolymorphReturn = someTrackTarget;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("nodeName")))
			{
				someTrackTarget->set_NodeName(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("nodeName"))));
				std::cout << "Has attribute 'nodeName': \"" << someTrackTarget->get_NodeName() << "\"\n";
			}
			else someTrackTarget->set_NodeName("NOT_FOUND_IN_XML");
			
			break;
		case dotSceneEnums::upVector:
			std::cout << "Element identified: 'dotSceneUpVector'\n";

			// Create dotSceneObject
			someUpVector = new dotSceneObjects::dotSceneUpVector();
			ObjectForPolymorphReturn = someUpVector;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("x")))
			{
				someUpVector->set_x(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("x"))));
				std::cout << "Has attribute 'x': \"" << someUpVector->get_x() << "\"\n";
			}
			else someUpVector->set_x(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("y")))
			{
				someUpVector->set_y(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("y"))));
				std::cout << "Has attribute 'y': \"" << someUpVector->get_y() << "\"\n";
			}
			else someUpVector->set_y(0.0);

			if (ParentElement->hasAttribute(XMLString::transcode("z")))
			{
				someUpVector->set_z(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("z"))));
				std::cout << "Has attribute 'z': \"" << someUpVector->get_z() << "\"\n";
			}
			else someUpVector->set_z(0.0);

			break;
		case dotSceneEnums::userDataReference:
			std::cout << "Element identified: 'dotSceneUserDataReference'\n";

			// Create dotSceneObject
			someUserDataReference = new dotSceneObjects::dotSceneUserDataReference();
			ObjectForPolymorphReturn = someUserDataReference;
			
			// Lookup for specialized attributes
			if (ParentElement->hasAttribute(XMLString::transcode("id")))
			{
				someUserDataReference->set_ID(XMLString::transcode(ParentElement->getAttribute(XMLString::transcode("id"))));
				std::cout << "Has attribute 'id': \"" << someUserDataReference->get_ID() << "\"\n";
			}
			else someUserDataReference->set_ID("NOT_FOUND_IN_XML");

			break;
		// When nothin matches or entire node invalid
		case dotSceneEnums::INVALID:
		default:
			std::cout << "Element not identified: UNKNOWN\n";
			ObjectForPolymorphReturn = 0;
			break;
	}
	// ******************************************************** Attribute-Handling ****************************************
	// ******************************************************** Recursiv Element-Handling *********************************
	// Recursive calls for more detailed dotSceneObjects
	// For all nodes, children of "root" in the XML tree.
	for(XMLSize_t NodeIterator = 0; NodeIterator < ChildCount; ++NodeIterator)
	{
		dotSceneObjects::dotSceneObject* ObjectReturnedFromRecursiveCall = 0;
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
			std::cout << "Found ELEMENT_NODE:\n";
			CurrentElement = dynamic_cast<xercesc::DOMElement*>(CurrentNode);
			ObjectReturnedFromRecursiveCall = this->recursiveNodeProcessing(CurrentElement);
			
			// Identification of dotSceneObject
			// INFORMATION: Other node-types are defined for integrity.
			if (ObjectReturnedFromRecursiveCall != 0)
			{
				// Actions for deeper depend on upper element. That's better to see too...
				switch(TagType)
				{
				case dotSceneEnums::angle_axis:
					break; // Don't occures -> dead end.
				case dotSceneEnums::axisXYZ:
					break; // Don't occures -> dead end.
				case dotSceneEnums::billboard:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::position:
						somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
						someBillboard->set_Position(*somePosition);
						delete somePosition;
						break;
					case dotSceneEnums::colourDiffuse:
						someColourDiffuse = dynamic_cast<dotSceneObjects::dotSceneColourDiffuse*>(ObjectReturnedFromRecursiveCall);
						someBillboard->set_ColourDiffuse(*someColourDiffuse);
						delete someColourDiffuse;
						break;
					case dotSceneEnums::textureCoords:
						someTextureCoords = dynamic_cast<dotSceneObjects::dotSceneTextureCoords*>(ObjectReturnedFromRecursiveCall);
						someBillboard->set_TextureCoords(*someTextureCoords);
						delete someTextureCoords;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
				case dotSceneEnums::billboardSet:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::commonMovableObjectParams:
						someCommonMovableObjectParams = dynamic_cast<dotSceneObjects::dotSceneCommonMovableObjectParams*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->set_CommonMovableObjectParams(*someCommonMovableObjectParams);
						delete someCommonMovableObjectParams;
						break;
					case dotSceneEnums::billboard:
						someBillboard = dynamic_cast<dotSceneObjects::dotSceneBillboard*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->addBillboard(*someBillboard);
						delete someBillboard;
						break;
					case dotSceneEnums::commonDirection:
						someCommonDirection = dynamic_cast<dotSceneObjects::dotSceneCommonDirection*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->set_CommonDirection(*someCommonDirection);
						delete someCommonDirection;
						break;
					case dotSceneEnums::commonUpVector:
						someCommonUpVector = dynamic_cast<dotSceneObjects::dotSceneCommonUpVector*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->set_CommonUpVector(*someCommonUpVector);
						delete someCommonUpVector;
						break;
					case dotSceneEnums::textureCoords:
						someTextureCoords = dynamic_cast<dotSceneObjects::dotSceneTextureCoords*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->set_TextureCoords(*someTextureCoords);
						delete someTextureCoords;
						break;
					case dotSceneEnums::textureStacksAndSlices:
						someTextureStacksAndSlices = dynamic_cast<dotSceneObjects::dotSceneTextureStacksAndSlices*>(ObjectReturnedFromRecursiveCall);
						someBillboardSet->set_TextureStacksAndSlices(*someTextureStacksAndSlices);
						delete someTextureStacksAndSlices;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
				break;
				case dotSceneEnums::camera:
					// Not implemented yet.
					break;
				case dotSceneEnums::colourAmbient:
					break; // Don't occures -> dead end.
				case dotSceneEnums::colourBackground:
					break; // Don't occures -> dead end.
				case dotSceneEnums::colourDiffuse:
					break; // Don't occures -> dead end.
				case dotSceneEnums::colourSpecular:
					break; // Don't occures -> dead end.
				case dotSceneEnums::commonDirection:
					break; // Don't occures -> dead end.
				case dotSceneEnums::commonMovableObjectParams:
					break; // Don't occures -> dead end.
				case dotSceneEnums::commonUpVector:
					break; // Don't occures -> dead end.
				case dotSceneEnums::direction:
					break; // Don't occures -> dead end.
				case dotSceneEnums::entity:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::commonMovableObjectParams:
						someCommonMovableObjectParams = dynamic_cast<dotSceneObjects::dotSceneCommonMovableObjectParams*>(ObjectReturnedFromRecursiveCall);
						someEntity->set_CommonMovableObjectParams(*someCommonMovableObjectParams);
						delete someCommonMovableObjectParams;
						break;
					case dotSceneEnums::meshLODBias:
						someMeshLODBias = dynamic_cast<dotSceneObjects::dotSceneMeshLODBias*>(ObjectReturnedFromRecursiveCall);
						someEntity->set_MeshLODBias(*someMeshLODBias);
						delete someMeshLODBias;
						break;
					case dotSceneEnums::materialLODBias:
						someMaterialLODBias = dynamic_cast<dotSceneObjects::dotSceneMaterialLODBias*>(ObjectReturnedFromRecursiveCall);
						someEntity->set_MaterialLODBias(*someMaterialLODBias);
						delete someMaterialLODBias;
						break;
					case dotSceneEnums::userDataReference:
						someUserDataReference = dynamic_cast<dotSceneObjects::dotSceneUserDataReference*>(ObjectReturnedFromRecursiveCall);
						someEntity->set_UserDataReference(*someUserDataReference);
						delete someUserDataReference;
						break;
					default: break; // Should only occure in case of the following ignored tags: animations, animationStates
					}
					break;
				case dotSceneEnums::externals:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::item:
						someItem = dynamic_cast<dotSceneObjects::dotSceneItem*>(ObjectReturnedFromRecursiveCall);
						someExternals->addItem(*someItem);
						delete someItem;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::file:
					break; // Don't occures -> dead end.
				case dotSceneEnums::floatRect:
					break; // Don't occures -> dead end.
				case dotSceneEnums::item:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::file:
						someFile = dynamic_cast<dotSceneObjects::dotSceneFile*>(ObjectReturnedFromRecursiveCall);
						someItem->set_File(*someFile);
						delete someFile;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::light:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::commonMovableObjectParams:
						someCommonMovableObjectParams = dynamic_cast<dotSceneObjects::dotSceneCommonMovableObjectParams*>(ObjectReturnedFromRecursiveCall);
						someLight->set_CommonMovableObjectParams(*someCommonMovableObjectParams);
						delete someCommonMovableObjectParams;
						break;
					case dotSceneEnums::position:
						somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
						someLight->set_Position(*somePosition);
						delete somePosition;
						break;
					case dotSceneEnums::direction:
						someDirection = dynamic_cast<dotSceneObjects::dotSceneDirection*>(ObjectReturnedFromRecursiveCall);
						someLight->set_Direction(*someDirection);
						delete someDirection;
						break;
					case dotSceneEnums::colourDiffuse:
						someColourDiffuse = dynamic_cast<dotSceneObjects::dotSceneColourDiffuse*>(ObjectReturnedFromRecursiveCall);
						someLight->set_DiffuseColour(*someColourDiffuse);
						delete someColourDiffuse;
						break;
					case dotSceneEnums::colourSpecular:
						someColourSpecular = dynamic_cast<dotSceneObjects::dotSceneColourSpecular*>(ObjectReturnedFromRecursiveCall);
						someLight->set_SpecularColour(*someColourSpecular);
						delete someColourSpecular;
						break;
					case dotSceneEnums::spotLightRange:
						someSpotLightRange = dynamic_cast<dotSceneObjects::dotSceneSpotLightRange*>(ObjectReturnedFromRecursiveCall);
						someLight->set_SpotLightRange(*someSpotLightRange);
						delete someSpotLightRange;
						break;
					case dotSceneEnums::lightAttenuation:
						someLightAttenuation = dynamic_cast<dotSceneObjects::dotSceneLightAttenuation*>(ObjectReturnedFromRecursiveCall);
						someLight->set_LightAttenuation(*someLightAttenuation);
						delete someLightAttenuation;
						break;
					case dotSceneEnums::userDataReference:	
						someUserDataReference = dynamic_cast<dotSceneObjects::dotSceneUserDataReference*>(ObjectReturnedFromRecursiveCall);
						someLight->set_UserDataReference(*someUserDataReference);
						delete someUserDataReference;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::lightAttenuation:
					break; // Don't occures -> dead end.
				case dotSceneEnums::localDirectionVector:
					break; // Don't occures -> dead end.
				case dotSceneEnums::lookTarget:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::position:
						somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
						someLookTarget->set_Position(*somePosition);
						delete somePosition;
						break;
					case dotSceneEnums::localDirectionVector:
						someLocalDirectionVector = dynamic_cast<dotSceneObjects::dotSceneLocalDirectionVector*>(ObjectReturnedFromRecursiveCall);
						someLookTarget->set_LocalDirectionVector(*someLocalDirectionVector);
						delete someLocalDirectionVector;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::materialLODBias:
					break; // Don't occures -> dead end.
				case dotSceneEnums::meshLODBias:
					break; // Don't occures -> dead end.
				case dotSceneEnums::node:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::position:
						somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
						someNode->set_Position(*somePosition);
						delete somePosition;
						break;
					case dotSceneEnums::orientation:
						someOrientation = dynamic_cast<dotSceneObjects::dotSceneOrientation*>(ObjectReturnedFromRecursiveCall);
						someNode->set_Orientation(*someOrientation);
						delete someOrientation;
						break;
					case dotSceneEnums::quaternion:	// dotScene.xsd-work-arround version-conflicts
						someOrientation = new dotSceneOrientation();
						someQuaternion = dynamic_cast<dotSceneObjects::dotSceneQuaternion*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_Quaternion(*someQuaternion);
						delete someQuaternion;
						someNode->set_Orientation(*someOrientation);
						delete someOrientation;
						break;
					case dotSceneEnums::scale:
						someScale = dynamic_cast<dotSceneObjects::dotSceneScale*>(ObjectReturnedFromRecursiveCall);
						someNode->set_Scale(*someScale);
						delete someScale;
						break;
					case dotSceneEnums::lookTarget:
						someLookTarget = dynamic_cast<dotSceneObjects::dotSceneLookTarget*>(ObjectReturnedFromRecursiveCall);
						someNode->set_LookTarget(*someLookTarget);
						delete someLookTarget;
						break;
					case dotSceneEnums::trackTarget:
						someTrackTarget = dynamic_cast<dotSceneObjects::dotSceneTrackTarget*>(ObjectReturnedFromRecursiveCall);
						someNode->set_TrackTarget(*someTrackTarget);
						delete someTrackTarget;
						break;
					case dotSceneEnums::userDataReference:
						someUserDataReference = dynamic_cast<dotSceneObjects::dotSceneUserDataReference*>(ObjectReturnedFromRecursiveCall);
						someNode->set_UserDataReference(*someUserDataReference);
						delete someUserDataReference;
						break;
					case dotSceneEnums::node:
						someChildNode = dynamic_cast<dotSceneObjects::dotSceneNode*>(ObjectReturnedFromRecursiveCall);
						someNode->addChildNode(*someChildNode);
						delete someChildNode;
						break;
					case dotSceneEnums::entity:
						someEntity = dynamic_cast<dotSceneObjects::dotSceneEntity*>(ObjectReturnedFromRecursiveCall);
						someNode->addEntity(*someEntity);
						delete someEntity;
						break;
					case dotSceneEnums::light:
						someLight = dynamic_cast<dotSceneObjects::dotSceneLight*>(ObjectReturnedFromRecursiveCall);
						someNode->addLight(*someLight);
						delete someLight;
						break;
					// case dotSceneEnums::camera:				someNode->addCamera(*(dynamic_cast<dotSceneObjects::dotSceneCamera*>(ObjectReturnedFromRecursiveCall))); break;
					case dotSceneEnums::particleSystem:
						someParticleSystem = dynamic_cast<dotSceneObjects::dotSceneParticleSystem*>(ObjectReturnedFromRecursiveCall);
						someNode->addParticleSystem(*someParticleSystem);
						delete someParticleSystem;
						break;
					case dotSceneEnums::billboardSet:
						someBillboardSet = dynamic_cast<dotSceneObjects::dotSceneBillboardSet*>(ObjectReturnedFromRecursiveCall);
						someNode->addBillboardSet(*someBillboardSet);
						delete someBillboardSet;
						break;
					case dotSceneEnums::plane:
						somePlane = dynamic_cast<dotSceneObjects::dotScenePlane*>(ObjectReturnedFromRecursiveCall);
						someNode->addPlane(*somePlane);
						delete somePlane;
						break;
					default: break; // Should only occure in case of the following ignored tags: camera
					}
					break;
				case dotSceneEnums::nodes:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::node:
						someNode = dynamic_cast<dotSceneObjects::dotSceneNode*>(ObjectReturnedFromRecursiveCall);
						someNodes->addNode(*someNode);
						delete someNode;
						break;
					case dotSceneEnums::light:
						someLight = dynamic_cast<dotSceneObjects::dotSceneLight*>(ObjectReturnedFromRecursiveCall);
						someNodes->addLight(*someLight);
						delete someLight;
						break;
					case dotSceneEnums::camera:
						someCamera = dynamic_cast<dotSceneObjects::dotSceneCamera*>(ObjectReturnedFromRecursiveCall);
						someNodes->addCamera(*someCamera);
						delete someCamera;
						break;
					case dotSceneEnums::position:
						somePosition = dynamic_cast<dotSceneObjects::dotScenePosition*>(ObjectReturnedFromRecursiveCall);
						someNodes->set_Position(*somePosition);
						delete somePosition;
						break;
					case dotSceneEnums::orientation:
						someOrientation = dynamic_cast<dotSceneObjects::dotSceneOrientation*>(ObjectReturnedFromRecursiveCall);
						someNodes->set_Orientation(*someOrientation);
						delete someOrientation;
						break;
					case dotSceneEnums::quaternion:	// dotScene.xsd-work-arround version-conflicts
						someOrientation = new dotSceneOrientation();
						someQuaternion = dynamic_cast<dotSceneObjects::dotSceneQuaternion*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_Quaternion(*someQuaternion);
						delete someQuaternion;
						someNodes->set_Orientation(*someOrientation);
						delete someOrientation;
						break;
					case dotSceneEnums::scale:someScale = dynamic_cast<dotSceneObjects::dotSceneScale*>(ObjectReturnedFromRecursiveCall);
						someNodes->set_Scale(*someScale);
						delete someScale;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::normal:
					break; // Don't occures -> dead end.
				case dotSceneEnums::offset:
					break; // Don't occures -> dead end.
				case dotSceneEnums::orientation:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::quaternion:
						someQuaternion = dynamic_cast<dotSceneObjects::dotSceneQuaternion*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_Quaternion(*someQuaternion);
						delete someQuaternion;
						break;
					case dotSceneEnums::axisXYZ:
						someAxisXYZ = dynamic_cast<dotSceneObjects::dotSceneAxisXYZ*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_AxisXYZ(*someAxisXYZ);
						delete someAxisXYZ;
						break;
					case dotSceneEnums::angle_axis:
						someAngleAxis = dynamic_cast<dotSceneObjects::dotSceneAngleAxis*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_AngleAxis(*someAngleAxis);
						delete someAngleAxis;
						break;
					case dotSceneEnums::direction:
						someDirection = dynamic_cast<dotSceneObjects::dotSceneDirection*>(ObjectReturnedFromRecursiveCall);
						someOrientation->set_Direction(*someDirection);
						delete someDirection;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::particleSystem:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::commonMovableObjectParams:
						someCommonMovableObjectParams = dynamic_cast<dotSceneObjects::dotSceneCommonMovableObjectParams*>(ObjectReturnedFromRecursiveCall);
						someParticleSystem->set_CommonMovableObjectParams(*someCommonMovableObjectParams);
						delete someCommonMovableObjectParams;
						break;
					case dotSceneEnums::userDataReference:
						someUserDataReference = dynamic_cast<dotSceneObjects::dotSceneUserDataReference*>(ObjectReturnedFromRecursiveCall);
						someParticleSystem->set_UserDataReference(*someUserDataReference);
						delete someUserDataReference;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::plane:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::upVector:
						someUpVector = dynamic_cast<dotSceneObjects::dotSceneUpVector*>(ObjectReturnedFromRecursiveCall);
						somePlane->set_UpVector(*someUpVector);
						delete someUpVector;
						break;
					default: break; // Should only occure in case of the following ignored tags: vertexBuffer(INCONSISTENT XSD), indexBuffer(INCONSISTENT XSD)
					}
					break;
				case dotSceneEnums::position:
					break; // Don't occures -> dead end.
				case dotSceneEnums::quaternion:
					break; // Don't occures -> dead end.
				case dotSceneEnums::scale:
					break; // Don't occures -> dead end.
				case dotSceneEnums::scene:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::shadowSettings:
						someShadowSettings = dynamic_cast<dotSceneObjects::dotSceneShadowSettings*>(ObjectReturnedFromRecursiveCall);
						someScene->set_ShadowSettings(*someShadowSettings);
						delete someShadowSettings;
						break;
					case dotSceneEnums::externals:
						someExternals = dynamic_cast<dotSceneObjects::dotSceneExternals*>(ObjectReturnedFromRecursiveCall);
						someScene->set_Externals(*someExternals);
						delete someExternals;
						break;
					case dotSceneEnums::nodes:
						someNodes = dynamic_cast<dotSceneObjects::dotSceneNodes*>(ObjectReturnedFromRecursiveCall);
						someScene->set_Nodes(*someNodes);
						delete someNodes;
						break;
					case dotSceneEnums::userDataReference:
						someUserDataReference = dynamic_cast<dotSceneObjects::dotSceneUserDataReference*>(ObjectReturnedFromRecursiveCall);
						someScene->set_UserDataReference(*someUserDataReference);
						delete someUserDataReference;
						break;
					default: break; // Should only occure in case of the following ignored tags: environment, sceneManagerOption, recourceeGroup, camera, animations, animationStates, terrain, octree
					}
					break;
				case dotSceneEnums::shadowSettings:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::colourDiffuse:
						someColourDiffuse = dynamic_cast<dotSceneObjects::dotSceneColourDiffuse*>(ObjectReturnedFromRecursiveCall);
						someShadowSettings->set_ColourDiffuse(*someColourDiffuse);
						delete someColourDiffuse;
						break;
					case dotSceneEnums::shadowTextureConfig:
						someShadowTextureConfig = dynamic_cast<dotSceneObjects::dotSceneShadowTextureConfig*>(ObjectReturnedFromRecursiveCall);
						someShadowSettings->addShadowTextureConfig(*someShadowTextureConfig);
						delete someShadowTextureConfig;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::shadowTextureConfig:
					break; // Don't occures -> dead end.
				case dotSceneEnums::spotLightRange:
					break; // Don't occures -> dead end.
				case dotSceneEnums::textureCoords:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::floatRect:
						someFloatRect = dynamic_cast<dotSceneObjects::dotSceneFloatRect*>(ObjectReturnedFromRecursiveCall);
						someTextureCoords->addFloatRect(*someFloatRect);
						delete someFloatRect;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::textureStacksAndSlices:
					break; // Don't occures -> dead end.
				case dotSceneEnums::trackTarget:
					switch(ObjectReturnedFromRecursiveCall->get_NameSymbol())
					{
					case dotSceneEnums::localDirectionVector:
						someLocalDirectionVector = dynamic_cast<dotSceneObjects::dotSceneLocalDirectionVector*>(ObjectReturnedFromRecursiveCall);
						someTrackTarget->set_LocalDirectionVector(*someLocalDirectionVector);
						delete someLocalDirectionVector;
						break;
					case dotSceneEnums::offset:
						someOffset = dynamic_cast<dotSceneObjects::dotSceneOffset*>(ObjectReturnedFromRecursiveCall);
						someTrackTarget->set_Offset(*someOffset);
						delete someOffset;
						break;
					default: break; // Should only occure in case of the following ignored tags: -
					}
					break;
				case dotSceneEnums::upVector:
					break; // Don't occures -> dead end.
				case dotSceneEnums::userDataReference:
					break; // Don't occures -> dead end.
					
				// When nothin matches or entire node invalid
				case dotSceneEnums::INVALID:
				default:
					ObjectForPolymorphReturn = 0;
					break;
				}		
			}	
			else std::cout << "Unidentified child-element. Recursive processing returned 'null'.\n";
			break;

		case DOMNode::NodeType::ENTITY_NODE :					break; // not interesting
		case DOMNode::NodeType::ENTITY_REFERENCE_NODE :			break; // not interesting
		case DOMNode::NodeType::NOTATION_NODE :					break; // not interesting
		case DOMNode::NodeType::PROCESSING_INSTRUCTION_NODE :	break; // not interesting
		case DOMNode::NodeType::TEXT_NODE :						break; // not interesting
		default:												break;
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
}

