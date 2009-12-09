/********************************************************************************
 * Name:      DotSceneInterpreter_DOMToOgre_V1_0_0.cpp							*
 * Purpose:   This interpreter inherits from abstract class						*
 *			  DotSceneInterpreter_DOMToOgre. It implements all redefined		*
 *			  abstract methods of its partent, according to the (modified 		*
 *			  and repaired) dotScene1.0.0 standard.								*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-16														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "../OViSEdotSceneInterpreter/DotSceneInterpreter_DOMToOgre_V1_0_0.h"

DotSceneInterpreter_DOMToOgre_V1_0_0::DotSceneInterpreter_DOMToOgre_V1_0_0() { }
DotSceneInterpreter_DOMToOgre_V1_0_0::~DotSceneInterpreter_DOMToOgre_V1_0_0() { }
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, QualifiedName qResourceGroup)
{

}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes)
{
	xercesc::DOMNodeList *NodeElements = 0, *CamElements = 0, *LightElements = 0;
	xercesc::DOMElement *DOMElement_position = 0, *DOMElement_orientation = 0, *DOMElement_quaternion = 0, *DOMElement_scale = 0;

	// "nodes" is a abstract logic structure. So elements beyond "node"-elements must be "global"
	// transitions and rotations for scene's root node. Attribute too.
	
	// Handle cams... TODO


	// Handle lights... TODO

	/// STEP 4.1: Handle childnodes...
	NodeElements = DOMElement_nodes->getElementsByTagName(ToXMLString("node"));

	/*
	if (NodeElements->getLength() > 0)
	{
		for(XMLSize_t ChildNodeIterator = 0; ChildNodeIterator < NodeElements->getLength(); ChildNodeIterator++)
		{
			this->Interpretation_Node((xercesc::DOMElement*) NodeElements->item(ChildNodeIterator), this->AnchorNode);
		}
	}
	*/

	if (DOMElement_nodes != 0)
	{
		for(xercesc::DOMNode* ChildNode = DOMElement_nodes->getFirstChild(); ChildNode != 0; ChildNode = ChildNode->getNextSibling())
		{
			switch(ChildNode->getNodeType())
			{
			case xercesc::DOMNode::ELEMENT_NODE:
				this->Interpretation_Node((xercesc::DOMElement*) ChildNode, this->AnchorNode);
				break;
			default:
				// Else ignore it!
				break;

			}
		}
	}

	
	/* REMEMBER: Change part! Must be applied to each node, light or cam, because a "SceneRootNode" won't be implemented any more! *
	// Handle attributes...
	bool Visible = true;
	bool CascadeVisibility = true;

	if (DOMElement_nodes->hasAttribute(ToXMLString("visible")))
	{
		std::string buff = ToStdString(DOMElement_nodes->getAttribute(ToXMLString("visible")));
		if (buff == "true") Visible = true;
		if (buff == "false") Visible = false;
		else
		{
			; // Attention: DEBUG-Trap. When this line is reached, something goes wrong. More testing is needed!!!
		}
	}

	if (DOMElement_nodes->hasAttribute(ToXMLString("cascadeVisibility")))
	{
		std::string buff = ToStdString(DOMElement_nodes->getAttribute(ToXMLString("cascadeVisibility")));
		if (buff == "true") Visible = true;
		if (buff == "false") Visible = false;
		else
		{
			; // Attention: DEBUG-Trap. When this line is reached, something goes wrong. More testing is needed!!!
		}
	}

	this->mSceneRootNode->setVisible(Visible, CascadeVisibility);*/
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Node(	xercesc::DOMElement* DOMElement_node,
																Ogre::SceneNode* ParentNode)
{
	// STEP 1: Declare all possible XML-elements...
	//xercesc::DOMElement *DOMElement_position = 0, *DOMElement_orientation = 0, *DOMElement_quaternion = 0, *DOMElement_scale = 0;
	// Not implemented here: ++ looktarget ++ tracktarget ++ userdatareference

	// ...and necessary objects for Ogre
	Ogre::Vector3 TempPositionOffset, TempScaleOffset = Ogre::Vector3::ZERO;
	Ogre::Quaternion TempRotationOffset;

	// STEP 2: Create necessary objects for all possible XML-attributes... 
	wxString NewNode_name, NewNode_id;
	bool NewNode_visible = true, NewNode_cascadeVisibility = true, NewNode_isTarget = false;

	// STEP 2: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_node->hasAttribute(ToXMLString("name")))
	{
		NewNode_name = ToWxString(DOMElement_node->getAttribute(ToXMLString("name")));
	}
	if (DOMElement_node->hasAttribute(ToXMLString("id")))
	{
		NewNode_id = ToWxString(DOMElement_node->getAttribute(ToXMLString("id")));
	}
	if (DOMElement_node->hasAttribute(ToXMLString("visible")))
	{
		wxString temp = ToWxString(DOMElement_node->getAttribute(ToXMLString("visible")));
		if (temp.IsSameAs(wxT("true"))) NewNode_visible = true;
		else NewNode_visible = false;
	}
	if (DOMElement_node->hasAttribute(ToXMLString("cascadeVisibility")))
	{
		wxString temp = ToWxString(DOMElement_node->getAttribute(ToXMLString("cascadeVisibility")));
		if (temp.IsSameAs(wxT("true"))) NewNode_cascadeVisibility = true;
		else NewNode_cascadeVisibility = false;
	}
	if (DOMElement_node->hasAttribute(ToXMLString("isTarget")))
	{
		wxString temp = ToWxString(DOMElement_node->getAttribute(ToXMLString("isTarget")));
		if (temp.IsSameAs(wxT("true"))) NewNode_isTarget = true;
		else NewNode_isTarget = false;
	}

	// STEP 3: Get complex attribute data (relative Transition (relative position), Rotation (Quaternion- or Orientation-element), Scale )
	xercesc::DOMNodeList *tempList;

	// STEP 3.1: Handle position...
	tempList = DOMElement_node->getElementsByTagName(ToXMLString("position"));
	if (tempList->getLength() > 0)
	{
		TempPositionOffset = this->Interpretation_Vector3((xercesc::DOMElement*) tempList->item(0));
	}
	else TempPositionOffset = Ogre::Vector3::ZERO;
	
	// STEP 3.2: Handle scale...
	tempList = DOMElement_node->getElementsByTagName(ToXMLString("scale"));
	if (tempList->getLength() > 0)
	{
		TempScaleOffset = this->Interpretation_Vector3((xercesc::DOMElement*) tempList->item(0));
	}
	else TempScaleOffset = Ogre::Vector3::ZERO;

	// STEP 3.3: Handle orientation/quaternion... // Prefering "quaternion" instead of orientation at moment. Exactly mathematical conversions not available yet.
	tempList = DOMElement_node->getElementsByTagName(ToXMLString("quaternion"));
	if (tempList->getLength() > 0)
	{
		TempRotationOffset = this->Interpretation_Quaternion((xercesc::DOMElement*) tempList->item(0));
	}
	else
	{
		tempList = DOMElement_node->getElementsByTagName(ToXMLString("orientation"));
		if (tempList->getLength() > 0)
		{
			// Do nothing. Complex analysis skipped.
			; // DEBUG-Trap
		}
		else TempRotationOffset = Ogre::Quaternion::IDENTITY;
	}

	// STEP 4: Create unique new SceneNode
	QualifiedName qSN = OgreMediator::GetSingletonPtr()->iSceneNode.Create(NewNode_name, ParentNode);
	Ogre::SceneNode* NewNode = OgreMediator::GetSingletonPtr()->iSceneNode.GetPtr(qSN);

	if (NewNode != 0)
	{
		NewNode->translate(TempPositionOffset, Ogre::Node::TS_PARENT);
		NewNode->scale(TempScaleOffset);
		NewNode->rotate(TempRotationOffset, Ogre::Node::TS_PARENT);

		// STEP 4.1: Set rest of attributes...
		NewNode->setVisible(NewNode_visible, NewNode_cascadeVisibility);

		// STEP 4.2: Apply attributes, which are not commented. These assumptions are highly speculative!!!
		#ifdef __ALLOW_INTERPRETATION_ASSUMPTIONS__
			NewNode->setAutoTracking(NewNode_isTarget); // <- ATTENTION: There is no information about how "isTarget" has to be used. This is an assumption.
		#endif

		// STEP 5: Look for existing elements, leading to deeper recusivity (!)
		if (DOMElement_node != 0)
		{
			for(xercesc::DOMNode* ChildNode = DOMElement_node->getFirstChild(); ChildNode != 0; ChildNode = ChildNode->getNextSibling())
			{
				switch(ChildNode->getNodeType())
				{
				case xercesc::DOMNode::ELEMENT_NODE:
					// STEP 5.1: Handle childnodes...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("node")))
					{
						this->Interpretation_Node((xercesc::DOMElement*) ChildNode, NewNode);
					}
					// STEP 5.2: Handle cameras...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("camera")))
					{
						this->Interpretation_Camera((xercesc::DOMElement*) ChildNode, NewNode);
					}
					// STEP 5.3: Handle entities...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("entity")))
					{
						this->Interpretation_Entity((xercesc::DOMElement*) ChildNode, NewNode);
					}
					// STEP 5.4: Handle lights...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("light")))
					{
						this->Interpretation_Light((xercesc::DOMElement*) ChildNode, NewNode);
					}
					
					// STEP 5.5: Handle particleSystems... TODO
					// STEP 5.6: Handle billboardSets... TODO
					// STEP 5.7: Handle planes... TODO
					// STEP 5.8: Handle lookTarget... TODO
					// STEP 5.9: Handle trackTarget... TODO
					// STEP 5.10: Handle userDataReference... TODO
					break;
				default:
					// Else ignore it!
					break;

				}
			}
		}
	}
	else
	{
		// Log error-message!!!
	}
}

void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Camera(	xercesc::DOMElement* DOMElement_camera,
																	Ogre::SceneNode* AssociateNode)
{
	wxString LogMsg;

	// STEP 1: Declare all possible elements...
	//xercesc::DOMElement *DOMElement_commonMovableObjectParams = 0, *DOMElement_clipping = 0, *DOMElement_position = 0, *DOMElement_orientation = 0;
	//xercesc::DOMElement *DOMElement_quaternion = 0, *DOMElement_lookTarget = 0, *DOMElement_trackTarget = 0, *DOMElement_userDataReference = 0;

	// STEP 2: Create all possible attributes...
	wxString NewCamera_name, NewCamera_id, NewCamera_lodBiasFactor = ToWxString("1.0"); // <- string
	float NewCamera_fov = 45.0, NewCamera_aspectRatio = 1.3333333f; //<- float
	Ogre::ProjectionType NewCamera_projectionType = Ogre::PT_PERSPECTIVE;
	Ogre::PolygonMode NewCamera_polygonMode = Ogre::PM_SOLID;
	bool NewCamera_useRenderingDistance = true; //<- bool

	// STEP 3: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_camera->hasAttribute(ToXMLString("name")))
	{
		NewCamera_name = ToWxString(DOMElement_camera->getAttribute(ToXMLString("name")));
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("id")))
	{
		NewCamera_id = ToWxString(DOMElement_camera->getAttribute(ToXMLString("id")));
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("lodBiasFactor")))
	{
		NewCamera_lodBiasFactor = ToWxString(DOMElement_camera->getAttribute(ToXMLString("lodBiasFactor")));
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("fov")))
	{
		NewCamera_fov = (float)xercesc::XMLFloat(DOMElement_camera->getAttribute(ToXMLString("fov"))).getValue();
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("aspectRatio")))
	{
		NewCamera_aspectRatio = (float)xercesc::XMLFloat(DOMElement_camera->getAttribute(ToXMLString("aspectRatio"))).getValue();
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("projectionType")))
	{
		wxString tPT = ToWxString(DOMElement_camera->getAttribute(ToXMLString("projectionType")));

		if (tPT.IsSameAs(ToWxString("orthographic"))) NewCamera_projectionType = Ogre::PT_ORTHOGRAPHIC;
		else if (tPT.IsSameAs(ToWxString("perspective"))) NewCamera_projectionType = Ogre::PT_PERSPECTIVE;
		else NewCamera_projectionType = Ogre::PT_PERSPECTIVE;
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("polygonMode")))
	{
		wxString tPM = ToWxString(DOMElement_camera->getAttribute(ToXMLString("polygonMode")));
		
		if (tPM.IsSameAs(ToWxString("points"))) NewCamera_polygonMode = Ogre::PM_POINTS;
		else if (tPM.IsSameAs(ToWxString("wireframe"))) NewCamera_polygonMode = Ogre::PM_WIREFRAME;
		else if (tPM.IsSameAs(ToWxString("solid"))) NewCamera_polygonMode = Ogre::PM_SOLID;
		else NewCamera_polygonMode = Ogre::PM_SOLID;
	}
	if (DOMElement_camera->hasAttribute(ToXMLString("useRenderingDistance")))
	{
		wxString temp = ToWxString(DOMElement_camera->getAttribute(ToXMLString("useRenderingDistance")));
		if (temp.IsSameAs(wxT("true"))) NewCamera_useRenderingDistance = true;
		else NewCamera_useRenderingDistance = false;
	}
	
	// STEP 4: Create unique new Ogre::Camera
	LogMsg.Clear();
	LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Creating new Ogre::Camera \"") << NewCamera_name << ToWxString("\"");
	Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

	QualifiedName qC = OgreMediator::GetSingletonPtr()->iCamera.Create(NewCamera_name, AssociateNode);
	Ogre::Camera* NewCamera = OgreMediator::GetSingletonPtr()->iCamera.GetPtr(qC);

	if (NewCamera != 0)
	{
		LogMsg.Clear();
		LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Done. Attached new Ogre::Camera \"") << qC.UniqueName() << ToWxString("\" to Ogre::SceneNode \"") << ToWxString(AssociateNode->getName()) << ToWxString("\"");
		Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

		// STEP 4.1: Set rest of attributes...
		NewCamera->setFOVy(Ogre::Degree(NewCamera_fov));
		NewCamera->setProjectionType(NewCamera_projectionType);
		NewCamera->setPolygonMode(NewCamera_polygonMode);

		// STEP 4.2: Apply attributes, which are not commented. These assumptions are highly speculative!!!
		#ifdef __ALLOW_INTERPRETATION_ASSUMPTIONS__
			//NewCamera->
		#endif

		// STEP 5: Look for existing elements, leading to deeper recusivity (!)
		if (DOMElement_camera != 0)
		{
			for(xercesc::DOMNode* ChildNode = DOMElement_camera->getFirstChild(); ChildNode != 0; ChildNode = ChildNode->getNextSibling())
			{
				switch(ChildNode->getNodeType())
				{
				case xercesc::DOMNode::ELEMENT_NODE:
					// STEP 5.1: Handle clipping...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("clipping")))
					{
						Ogre::Real nearPlaneDist = NewCamera->getNearClipDistance();
						Ogre::Real farPlaneDist = NewCamera->getFarClipDistance();
						this->Interpretation_Clipping((xercesc::DOMElement*) ChildNode, nearPlaneDist, farPlaneDist);
						NewCamera->setNearClipDistance(nearPlaneDist);
						NewCamera->setFarClipDistance(farPlaneDist);
					}
					// Step 5.2: Handle...
					break;
				default:
					// Else ignore it!
					break;
				}
			}
		}
	}
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Entity(	xercesc::DOMElement* DOMElement_entity,
																	Ogre::SceneNode* AssociateNode)
{
	wxString LogMsg;

	// STEP 1: Declare all possible elements...
	xercesc::DOMNodeList *AnimationsElements = 0, *animationStatesElements = 0;
	xercesc::DOMElement *DOMElement_commonMovableObjectParams = 0, *DOMElement_meshLODBias = 0, *DOMElement_materialLODBias = 0, *DOMElement_userDataReference = 0;

	// STEP 2: Create all possible attributes... // "robot.mesh" as dummy ;-)
	wxString NewEntity_name, NewEntity_id, NewEntity_meshFile = ToWxString("robot.mesh") , NewEntity_materialName, NewEntity_softwareAnimationRequests, NewEntity_softwareAnimationRequestsNormalsAlso;
	bool NewEntity_displaySkeleton = false, NewEntity_polygonModeOverrideable = false, NewEntity_vertexBufferUseShadow = false, NewEntity_indexBufferUseShadow = false;
	wxString NewEntity_vertexBufferUsage = ToWxString("staticWriteOnly"), NewEntity_indexBufferUsage = ToWxString("staticWriteOnly"); // <- enum

	// STEP 3: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_entity->hasAttribute(ToXMLString("name")))
	{
		NewEntity_name = ToWxString(DOMElement_entity->getAttribute(ToXMLString("name")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("id")))
	{
		NewEntity_id = ToWxString(DOMElement_entity->getAttribute(ToXMLString("id")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("meshFile")))
	{
		NewEntity_meshFile = ToWxString(DOMElement_entity->getAttribute(ToXMLString("meshFile")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("materialName")))
	{
		NewEntity_materialName = ToWxString(DOMElement_entity->getAttribute(ToXMLString("materialName")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("softwareAnimationRequests")))
	{
		NewEntity_softwareAnimationRequests = ToWxString(DOMElement_entity->getAttribute(ToXMLString("softwareAnimationRequests")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("softwareAnimationRequestsNormalsAlso")))
	{
		NewEntity_softwareAnimationRequestsNormalsAlso = ToWxString(DOMElement_entity->getAttribute(ToXMLString("softwareAnimationRequestsNormalsAlso")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("displaySkeleton")))
	{
		wxString temp = ToWxString(DOMElement_entity->getAttribute(ToXMLString("displaySkeleton")));
		if (temp.IsSameAs(wxT("true"))) NewEntity_displaySkeleton = true;
		else NewEntity_displaySkeleton = false;
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("polygonModeOverrideable")))
	{
		wxString temp = ToWxString(DOMElement_entity->getAttribute(ToXMLString("polygonModeOverrideable")));
		if (temp.IsSameAs(wxT("true"))) NewEntity_polygonModeOverrideable = true;
		else NewEntity_polygonModeOverrideable = false;
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("vertexBufferUseShadow")))
	{
		wxString temp = ToWxString(DOMElement_entity->getAttribute(ToXMLString("vertexBufferUseShadow")));
		if (temp.IsSameAs(wxT("true"))) NewEntity_vertexBufferUseShadow = true;
		else NewEntity_vertexBufferUseShadow = false;
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("indexBufferUseShadow")))
	{
		wxString temp = ToWxString(DOMElement_entity->getAttribute(ToXMLString("indexBufferUseShadow")));
		if (temp.IsSameAs(wxT("true"))) NewEntity_indexBufferUseShadow = true;
		else NewEntity_indexBufferUseShadow = false;
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("vertexBufferUsage")))
	{
		NewEntity_vertexBufferUsage = ToWxString(DOMElement_entity->getAttribute(ToXMLString("vertexBufferUsage")));
	}
	if (DOMElement_entity->hasAttribute(ToXMLString("indexBufferUsage")))
	{
		NewEntity_indexBufferUsage = ToWxString(DOMElement_entity->getAttribute(ToXMLString("indexBufferUsage")));
	}

	// STEP 4: Create unique new Ogre::Entity
	LogMsg.Clear();
	LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Creating new Ogre::Entity \"") << NewEntity_name << ToWxString("\" using .mesh \"") << NewEntity_meshFile << ToWxString("\"");
	Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

	QualifiedName qE = OgreMediator::GetSingletonPtr()->iEntity.Create(NewEntity_name, NewEntity_meshFile, AssociateNode);
	Ogre::Entity* NewEntity = OgreMediator::GetSingletonPtr()->iEntity.GetPtr(qE);

	LogMsg.Clear();
	LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Done. Attached new Ogre::Entity \"") << qE.UniqueName() << ToWxString("\" to Ogre::SceneNode \"") << ToWxString(AssociateNode->getName()) << ToWxString("\"");
	Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);
}

void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Light(	xercesc::DOMElement* DOMElement_light,
																	Ogre::SceneNode* AssociateNode)
{
	wxString LogMsg;

	// STEP 1: Declare all possible elements...
	/* xercesc::DOMElement* 
		normal,
		commonMovableObjectParams,
		position,
		direction,
		colourDiffuse,
		colourSpecular,
		lightRange,
		lightAttenuation,
		userDataReference*/

	// STEP 2: Create all possible attributes...
	wxString NewLight_name, NewLight_id; // <- string
	float NewLight_powerScale = 1.0, NewCamera_aspectRatio = 1.3333333f; //<- float
	Ogre::Light::LightTypes NewLight_type = Ogre::Light::LightTypes::LT_POINT;
	bool NewLight_castShadows = false; //<- bool

	// STEP 3: Get attribute data. If attribute is not used in XML, use default value from XSD...
	if (DOMElement_light->hasAttribute(ToXMLString("name")))
	{
		NewLight_name = ToWxString(DOMElement_light->getAttribute(ToXMLString("name")));
	}
	if (DOMElement_light->hasAttribute(ToXMLString("id")))
	{
		NewLight_id = ToWxString(DOMElement_light->getAttribute(ToXMLString("id")));
	}
	if (DOMElement_light->hasAttribute(ToXMLString("type")))
	{
		wxString tLT = ToWxString(DOMElement_light->getAttribute(ToXMLString("type")));
		if (tLT.IsSameAs(ToWxString("directional"))) NewLight_type = Ogre::Light::LT_DIRECTIONAL;
		else if (tLT.IsSameAs(ToWxString("spotLight"))) NewLight_type = Ogre::Light::LT_SPOTLIGHT;
		else NewLight_type = Ogre::Light::LT_POINT;
		// The entry of dotScene.xsd "radPoint" doesn't exist in Ogre, so it's ignored and LT_POINT takes affekt.
	}
	if (DOMElement_light->hasAttribute(ToXMLString("powerScale")))
	{
		NewLight_powerScale = (float)xercesc::XMLFloat(DOMElement_light->getAttribute(ToXMLString("powerScale"))).getValue();
	}
	if (DOMElement_light->hasAttribute(ToXMLString("castShadows")))
	{
		wxString temp = ToWxString(DOMElement_light->getAttribute(ToXMLString("castShadows")));
		if (temp.IsSameAs(wxT("true"))) NewLight_castShadows = true;
		else NewLight_castShadows = false;
	}
	
	// STEP 4: Create unique new Ogre::Light
	LogMsg.Clear();
	LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Creating new Ogre::Light \"") << NewLight_name << ToWxString("\"");
	Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

	QualifiedName qL = OgreMediator::GetSingletonPtr()->iLight.Create(NewLight_name, AssociateNode);
	Ogre::Light* NewLight = OgreMediator::GetSingletonPtr()->iLight.GetPtr(qL);

	if (NewLight != 0)
	{
		LogMsg.Clear();
		LogMsg << ToWxString("OViSE DOM-Interpreter dotSceneV1.0.0: Done. Attached new Ogre::Light \"") << qL.UniqueName() << ToWxString("\" to Ogre::SceneNode \"") << ToWxString(AssociateNode->getName()) << ToWxString("\"");
		Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Normal);

		// STEP 4.1: Set rest of attributes...
		NewLight->setType(NewLight_type);
		NewLight->setPowerScale(NewLight_powerScale);

		// STEP 4.2: Apply attributes, which are not commented. These assumptions are highly speculative!!!
		#ifdef __ALLOW_INTERPRETATION_ASSUMPTIONS__
			//NewLight->
		#endif

		// STEP 5: Look for existing elements, leading to deeper recusivity (!)
		if (DOMElement_light != 0)
		{
			for(xercesc::DOMNode* ChildNode = DOMElement_light->getFirstChild(); ChildNode != 0; ChildNode = ChildNode->getNextSibling())
			{
				switch(ChildNode->getNodeType())
				{
				case xercesc::DOMNode::ELEMENT_NODE:
					// STEP 5.1: Handle lightAttenuation...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("lightAttenuation")))
					{
						Ogre::Real attenuationRange = NewLight->getAttenuationRange();
						Ogre::Real attenuationConstant = NewLight->getAttenuationConstant();
						Ogre::Real attenuationLinear = NewLight->getAttenuationLinear();
						Ogre::Real attenuationQuadric = NewLight->getAttenuationQuadric();
						
						this->Interpretation_LightAttentuation((xercesc::DOMElement*) ChildNode, attenuationRange, attenuationConstant, attenuationLinear, attenuationQuadric);
						
						NewLight->setAttenuation(attenuationRange, attenuationConstant, attenuationLinear, attenuationQuadric);
					}
					// STEP 5.2: Handle lightRange...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("lightRange")))
					{
						Ogre::Radian radSpotlightInnerAngle = NewLight->getSpotlightInnerAngle();
						Ogre::Radian radSpotlightOuterAngle = NewLight->getSpotlightOuterAngle();
						Ogre::Real spotlightInnerAngle = radSpotlightInnerAngle.valueDegrees();
						Ogre::Real spotlightOuterAngle = radSpotlightOuterAngle.valueDegrees();
						Ogre::Real spotlightFalloff = NewLight->getSpotlightFalloff();
						
						this->Interpretation_LightRange((xercesc::DOMElement*) ChildNode, spotlightInnerAngle, spotlightOuterAngle, spotlightFalloff);
						
						radSpotlightInnerAngle = Ogre::Radian(Ogre::Degree(spotlightInnerAngle));
						radSpotlightOuterAngle = Ogre::Radian(Ogre::Degree(spotlightOuterAngle));
						try
						{
							NewLight->setSpotlightRange(radSpotlightInnerAngle, radSpotlightOuterAngle, spotlightFalloff);
						}
						catch(std::exception e)
						{
							wxString LogMsg = ToWxString(e.what());
							Logging::GetSingletonPtr()->WriteToOgreLog(LogMsg, Logging::Critical);
						}
					}
					// Step 5.3: Handle colourDiffuse...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("colourDiffuse")))
					{
						NewLight->setDiffuseColour(this->Interpretation_ColourValue((xercesc::DOMElement*) ChildNode));
					}
					// Step 5.4: Handle colourSpecular...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("colourSpecular")))
					{
						NewLight->setSpecularColour(this->Interpretation_ColourValue((xercesc::DOMElement*) ChildNode));
					}
					// Step 5.5: Handle normal...
					if (ToWxString(ChildNode->getNodeName()).IsSameAs(ToWxString("normal")))
					{
						NewLight->setDirection(this->Interpretation_Vector3((xercesc::DOMElement*) ChildNode));
					}
					// Step 5.6: Handle...
					break;
				default:
					// Else ignore it!
					break;
				}
			}
		}
	}
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Environment(xercesc::DOMElement* DOMElement_environment)
{

}
Ogre::Vector3 DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector3 * * * * * * * * *
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f;

	if (DOMElement_Vector3->hasAttribute(ToXMLString("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("x"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(ToXMLString("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("y"))).getValue();
	}
	if (DOMElement_Vector3->hasAttribute(ToXMLString("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector3->getAttribute(ToXMLString("z"))).getValue();
	}

	return Ogre::Vector3(fX, fY, fZ);
}
Ogre::Vector4 DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4)
{
	// * * * * * * * * Interpretation of different elements, representing a Ogre::Vector4 * * * * * * * * *
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f, fW = 0.0f;

	if (DOMElement_Vector4->hasAttribute(ToXMLString("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("x"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("y"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("z"))).getValue();
	}
	if (DOMElement_Vector4->hasAttribute(ToXMLString("w")))
	{
		fW = (float)xercesc::XMLFloat(DOMElement_Vector4->getAttribute(ToXMLString("w"))).getValue();
	}

	return Ogre::Vector4(fX, fY, fZ, fW);
}
Ogre::Quaternion DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Quaternion(xercesc::DOMElement* DOMElement_Quaternion)
{
	// * * * * * * * * Interpretation of  a Ogre::Quaternion * * * * * * * * *
	Ogre::Real fX = 0.0f, fY  = 0.0f, fZ = 0.0f, fW = 0.0f;

	if (DOMElement_Quaternion->hasAttribute(ToXMLString("x")))
	{
		fX = (float)xercesc::XMLFloat(DOMElement_Quaternion->getAttribute(ToXMLString("x"))).getValue();
	}
	if (DOMElement_Quaternion->hasAttribute(ToXMLString("y")))
	{
		fY = (float)xercesc::XMLFloat(DOMElement_Quaternion->getAttribute(ToXMLString("y"))).getValue();
	}
	if (DOMElement_Quaternion->hasAttribute(ToXMLString("z")))
	{
		fZ = (float)xercesc::XMLFloat(DOMElement_Quaternion->getAttribute(ToXMLString("z"))).getValue();
	}
	if (DOMElement_Quaternion->hasAttribute(ToXMLString("w")))
	{
		fW = (float)xercesc::XMLFloat(DOMElement_Quaternion->getAttribute(ToXMLString("w"))).getValue();
	}

	return Ogre::Quaternion(fW, fX, fY, fZ);
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_Clipping(	xercesc::DOMElement* DOMElement_Clipping,
																	Ogre::Real& nearPlaneDist,
																	Ogre::Real& farPlaneDist)
{
	// * * * * * * * * Interpretation of clipping-parametes for Ogre::Camera * * * * * * * * *
	if (DOMElement_Clipping->hasAttribute(ToXMLString("nearPlaneDist")))
	{
		nearPlaneDist = (float)xercesc::XMLFloat(DOMElement_Clipping->getAttribute(ToXMLString("nearPlaneDist"))).getValue();
	}
	if (DOMElement_Clipping->hasAttribute(ToXMLString("farPlaneDist")))
	{
		farPlaneDist = (float)xercesc::XMLFloat(DOMElement_Clipping->getAttribute(ToXMLString("farPlaneDist"))).getValue();
	}
}
Ogre::ColourValue DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_ColourValue(xercesc::DOMElement* DOMElement_colourValue)
{
	Ogre::ColourValue NewColour = Ogre::ColourValue();

	if (DOMElement_colourValue->hasAttribute(ToXMLString("r")))
	{
		NewColour.r = (float)xercesc::XMLFloat(DOMElement_colourValue->getAttribute(ToXMLString("r"))).getValue();
	}
	if (DOMElement_colourValue->hasAttribute(ToXMLString("g")))
	{
		NewColour.g = (float)xercesc::XMLFloat(DOMElement_colourValue->getAttribute(ToXMLString("g"))).getValue();
	}
	if (DOMElement_colourValue->hasAttribute(ToXMLString("b")))
	{
		NewColour.b = (float)xercesc::XMLFloat(DOMElement_colourValue->getAttribute(ToXMLString("b"))).getValue();
	}
	if (DOMElement_colourValue->hasAttribute(ToXMLString("a")))
	{
		NewColour.a = (float)xercesc::XMLFloat(DOMElement_colourValue->getAttribute(ToXMLString("a"))).getValue();
	}

	return NewColour;
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_LightAttentuation(xercesc::DOMElement* DOMElement_lightAttentuation, Ogre::Real& range, Ogre::Real& constant, Ogre::Real& linear, Ogre::Real& quadratic)
{
	// * * * * * * * * Interpretation of attentuation-parametes for Ogre::Light * * * * * * * * *
	if (DOMElement_lightAttentuation->hasAttribute(ToXMLString("range")))
	{
		range = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightAttentuation->getAttribute(ToXMLString("range"))).getValue());
	}
	if (DOMElement_lightAttentuation->hasAttribute(ToXMLString("constant")))
	{
		constant = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightAttentuation->getAttribute(ToXMLString("constant"))).getValue());
	}
	if (DOMElement_lightAttentuation->hasAttribute(ToXMLString("linear")))
	{
		linear = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightAttentuation->getAttribute(ToXMLString("linear"))).getValue());
	}
	if (DOMElement_lightAttentuation->hasAttribute(ToXMLString("quadratic")))
	{
		quadratic = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightAttentuation->getAttribute(ToXMLString("quadratic"))).getValue());
	}
}
void DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation_LightRange(xercesc::DOMElement* DOMElement_lightRange, Ogre::Real& inner, Ogre::Real& outer, Ogre::Real& falloff)
{
	// * * * * * * * * Interpretation of range-parametes for Ogre::Light * * * * * * * * *
	if (DOMElement_lightRange->hasAttribute(ToXMLString("inner")))
	{
		inner = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightRange->getAttribute(ToXMLString("inner"))).getValue());
	}
	if (DOMElement_lightRange->hasAttribute(ToXMLString("outer")))
	{
		outer = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightRange->getAttribute(ToXMLString("outer"))).getValue());
	}
	if (DOMElement_lightRange->hasAttribute(ToXMLString("falloff")))
	{
		falloff = Ogre::Real((float)xercesc::XMLFloat(DOMElement_lightRange->getAttribute(ToXMLString("falloff"))).getValue());
	}
}
bool DotSceneInterpreter_DOMToOgre_V1_0_0::IsValidFormatVersion(xercesc::DOMDocument* DOMRepresentationOfScene)
{
	return DotSceneInterpreter_DOMToOgre::GetVersionString(DOMRepresentationOfScene).IsSameAs(ToWxString("1.0.0"));
}
bool DotSceneInterpreter_DOMToOgre_V1_0_0::Interpretation(	xercesc::DOMDocument* DOMRepresentationOfScene,
															QualifiedName qAnchorNodeName,
															DotSceneBaseConfiguration* Configuration)
{
	// Check format version (!)
	if ( !this->IsValidFormatVersion(DOMRepresentationOfScene) ) return false;
	
	// Call of inherided method. Provides a basic setup and calls inplicid sub-methods for necessary interpretations...
	bool ReturnValue =  this->Interpretation_DOMScene(DOMRepresentationOfScene, qAnchorNodeName, Configuration);

	if ( ReturnValue ) OgreMediator::GetSingletonPtr()->SendOgreChanged();
	return ReturnValue;

	// More individual calls. Not necessary for a correct an full interpretation!
}
