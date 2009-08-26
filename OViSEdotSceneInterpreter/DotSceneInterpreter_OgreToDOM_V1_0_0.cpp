#include "DotSceneInterpreter_OgreToDOM_V1_0_0.h"

void DotSceneInterpreter_OgreToDOM_V1_0_0::SetVersionString(wxString VersionString) { this->VersionString = VersionString; }
DotSceneInterpreter_OgreToDOM_V1_0_0::DotSceneInterpreter_OgreToDOM_V1_0_0(void)
{
}

DotSceneInterpreter_OgreToDOM_V1_0_0::~DotSceneInterpreter_OgreToDOM_V1_0_0(void)
{
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Node(Ogre::SceneNode* actualSceneNode)
{
	// STEP 1: Create element "node"
	DOMElement* NodeElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("node"));
	NodeElement->setAttribute(XMLString::transcode("name"), ToXMLString(actualSceneNode->getName()));

	// STEP 2: Create and attach general child-elements: "position", "quaternion" & "scale"
	NodeElement->appendChild(this->Interpretation_Position(actualSceneNode->getPosition()));
	NodeElement->appendChild(this->Interpretation_Quaternion(actualSceneNode->getOrientation()));
	NodeElement->appendChild(this->Interpretation_Scale(actualSceneNode->getScale()));

	// STEP 3: Create and attach special child-elements: "camera", "light" & "entity"
	Ogre::SceneNode::ObjectIterator ObjIter = actualSceneNode->getAttachedObjectIterator();
	Ogre::MovableObject* MovObj;

	while(ObjIter.hasMoreElements())
	{
		MovObj = ObjIter.getNext();
		bool match = false;
		
		if (MovObj->getMovableType() == "Camera")  // Not implemented yet.
		{
			match = false;
			NodeElement->appendChild(this->Interpretation_Camera(static_cast<Ogre::Camera*>(MovObj)));
		}

		if (MovObj->getMovableType() == "Entity") // TODO: simplify processing of relacing.
		{
			match = true;
			NodeElement->appendChild(this->Interpretation_Entity(static_cast<Ogre::Entity*>(MovObj)));
		}

		if (MovObj->getMovableType() == "Light") // Not full implemented -> not all types of light handled.
		{
			match = true;
			NodeElement->appendChild(this->Interpretation_Light(static_cast<Ogre::Light*>(MovObj))); 
		}	
		if (!match)
		{
			break;
		}
	}

	// STEP 4: Return resulting DOMElement for "node"
	return NodeElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Camera(Ogre::Camera* SomeCamera)
{
	// Create DOM-element "camera"
	DOMElement* CameraElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("camera"));
	CameraElement->setAttribute(XMLString::transcode("name"), ToXMLString(SomeCamera->getName()));

	// TODO: finalize implementation
	
	return CameraElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Entity(Ogre::Entity* SomeEntity)
{
	// STEP 1: Get full path of meshfile
	wxFileName MeshFullPath(ToWxString(SomeEntity->getMesh()->getName()));

	// STEP 2: Create DOM-element "entity"
	DOMElement* EntityElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("entity"));	
	EntityElement->setAttribute(ToXMLString("name"), ToXMLString(SomeEntity->getName()));
	EntityElement->setAttribute(ToXMLString("meshFile"), ToXMLString(MeshFullPath.GetFullName()));

	// STEP 3: Prepare copy/export of meshfile: Can the used *.mesh be located in filesystem?
	if(wxFileExists(MeshFullPath.GetFullPath()))
	{
		// Yes: prepare to copy it, place list of used meshfiles
		this->Prototype->Data.MeshFiles.Add(MeshFullPath.GetFullPath());
	}
	else
	{
		// No: prepare to export from memory to filesystem, place it into the export-list!
		this->Prototype->Data.MeshDatastructures.Add(SomeEntity->getMesh());
	}

	// STEP 4 : Prepare copy/export of materialfiles
	unsigned int NumSubEntities = SomeEntity->getNumSubEntities();
	if(NumSubEntities > 0)
	{
		for (unsigned int iter = 0; iter < NumSubEntities; iter++)
		{
			Ogre::SubEntity* SubEnt = SomeEntity->getSubEntity(iter);
			Ogre::MaterialPtr MatPtr = SubEnt->getMaterial();
			wxString MatName;
			MatName << ToWxString("ENTITY-MATERIAL-NAME (FILE?)") << ToWxString(MatPtr->getName());
			this->Configuration->Log->WriteToOgreLog(MatName, OViSELogging::Normal);

		}
	}


	return EntityElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Light(Ogre::Light* SomeLight)
{
	// STEP 1: Create DOM-element "entity"
	DOMElement* LightElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("light"));
	LightElement->setAttribute(ToXMLString("name"), ToXMLString(SomeLight->getName()));

	// STEP 2: Handling depends on enum Ogre::Light::LightTypes
	if (SomeLight->getType() == Ogre::Light::LT_DIRECTIONAL) // Not fully implemented -> not all types of light handled!	
	{
		LightElement->setAttribute(ToXMLString("type"), ToXMLString("directional"));
	}

	if (SomeLight->getType() == Ogre::Light::LT_POINT)
	{			
		// Set attributes
		LightElement->setAttribute(ToXMLString("type"), ToXMLString("point"));

		// Attach detail-elements
		LightElement->appendChild(this->Interpretation_DiffuseColour(SomeLight->getDiffuseColour()));
		LightElement->appendChild(this->Interpretation_SpecularColour(SomeLight->getSpecularColour()));
	}

	if (SomeLight->getType() == Ogre::Light::LT_SPOTLIGHT) // Not fully implemented -> not all types of light handled!
	{
		LightElement->setAttribute(ToXMLString("type"), ToXMLString("spotLight"));
	}

	return LightElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Position(Ogre::Vector3 NodePosition)
{
	DOMElement* PositionElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("position"));
	PositionElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(NodePosition.x)));
	PositionElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(NodePosition.y)));
	PositionElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(NodePosition.z)));
	return PositionElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Quaternion(Ogre::Quaternion NodeQuaternion)
{
	DOMElement* QuaternionElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("quaternion"));	
	QuaternionElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(NodeQuaternion.x)));
	QuaternionElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(NodeQuaternion.y)));
	QuaternionElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(NodeQuaternion.z)));
	QuaternionElement->setAttribute(ToXMLString("w"), ToXMLString(Ogre::StringConverter::toString(NodeQuaternion.w)));
	return QuaternionElement;
}

xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_Scale(Ogre::Vector3 NodeScale)
{
	DOMElement* ScaleElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("scale"));
	ScaleElement->setAttribute(ToXMLString("x"), ToXMLString(Ogre::StringConverter::toString(NodeScale.x)));
	ScaleElement->setAttribute(ToXMLString("y"), ToXMLString(Ogre::StringConverter::toString(NodeScale.y)));
	ScaleElement->setAttribute(ToXMLString("z"), ToXMLString(Ogre::StringConverter::toString(NodeScale.z)));
	return ScaleElement;
}
xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_DiffuseColour(Ogre::ColourValue DiffuseColour)
{
	DOMElement* DiffuseColourElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("colourDiffuse"));			
	DiffuseColourElement->setAttribute(ToXMLString("r"), ToXMLString(Ogre::StringConverter::toString(DiffuseColour.r)));
	DiffuseColourElement->setAttribute(ToXMLString("g"), ToXMLString(Ogre::StringConverter::toString(DiffuseColour.g)));
	DiffuseColourElement->setAttribute(ToXMLString("b"), ToXMLString(Ogre::StringConverter::toString(DiffuseColour.b)));
	return DiffuseColourElement;
}
xercesc::DOMElement* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation_SpecularColour(Ogre::ColourValue SpecularColour)
{
	DOMElement* SpecularColourElement = this->Prototype->GetDOMRepresentation()->createElement(ToXMLString("colourSpecular"));	
	SpecularColourElement->setAttribute(ToXMLString("r"), ToXMLString(Ogre::StringConverter::toString(SpecularColour.r)));
	SpecularColourElement->setAttribute(ToXMLString("g"), ToXMLString(Ogre::StringConverter::toString(SpecularColour.g)));
	SpecularColourElement->setAttribute(ToXMLString("b"), ToXMLString(Ogre::StringConverter::toString(SpecularColour.b)));
	return SpecularColourElement;
}

bool DotSceneInterpreter_OgreToDOM_V1_0_0::IsValidFormatVersion(wxString VersionStringForExport)
{
	return VersionStringForExport.IsSameAs(ToWxString("1.0.0"));
}
ScenePrototype* DotSceneInterpreter_OgreToDOM_V1_0_0::Interpretation(	wxString NotUniquePrototypeName,
																		OViSESelectionMap Selection,
																		DotSceneBaseConfiguration* Configuration)
{
	if (this->Interpretation_OgreScene(NotUniquePrototypeName, Selection, Configuration)) return this->Prototype;
	else return 0;
}
