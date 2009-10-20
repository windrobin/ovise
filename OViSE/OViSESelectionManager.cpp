#include "OViSESelectionManager.h"

// Singleton
OViSESelectionManager* OViSESelectionManager::instance = 0;
OViSESelectionManager* OViSESelectionManager::getSingletonPtr()
{
	if (OViSESelectionManager::instance == 0) OViSESelectionManager::instance = new OViSESelectionManager();
	return OViSESelectionManager::instance;
}

OViSESelectionManager::OViSESelectionManager() { this->Valid = true; }
OViSESelectionManager::~OViSESelectionManager(void) { }
// General
// wxPropertyGrid-Handling
bool OViSESelectionManager::isValid() { return this->Valid; }
bool OViSESelectionManager::addNOTIMPLEMENTEDToPGCategory(wxPropertyCategory* PC)
{
	if ( PC == 0 ) return false;

	wxPropertyGrid* PG = PC->GetGrid();
	if ( PG == 0 ) return false;

	// Info
	wxPGProperty* PInfo = PG->AppendIn(PC, new wxStringProperty(wxT("INFO"), wxPG_LABEL));
	PG->SetPropertyValue(PInfo, ToWxString("not implemented"));
	PG->DisableProperty(PInfo);

	return true;
}
bool OViSESelectionManager::addCameraToPGCategory(wxPropertyCategory* PC, Ogre::Camera* C)
{
	/*
	C->setAspectRatio(); //+
	C->setAutoAspectRatio(); //?

	C->setCastShadows();


	C->setDirection(); //+
	C->setFarClipDistance(); //+

	C->setFocalLength();
	C->setFOVy(); //+

	C->setLodBias(); //+

	C->setNearClipDistance();

	C->setPolygonMode(); //+
	C->setPolygonModeOverrideable(); //?

	C->setProjectionType(); //+

	C->setRenderingDistance();

	C->setUseRenderingDistance(); //+

	C->setVisible();
*/

	return true;
}
bool OViSESelectionManager::addEntityToPGCategory(wxPropertyCategory* PC, Ogre::Entity* E)
{
	if ( PC == 0 ) return false;

	wxPropertyGrid* PG = PC->GetGrid();
	if ( PG == 0 ) return false;

	wxString EntityNameAndPoint = ToWxString(E->getName()) + ToWxString(".");
	wxString Label;

	// Name
	Label = ToWxString("Name");
	wxPGProperty* PName = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PName, E->getName());
	PG->DisableProperty(PName);

	// Meshfile
	Label = ToWxString("Mesh");
	wxPGProperty* PMesh = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PMesh, E->getMesh()->getName());
	PG->DisableProperty(PMesh);

	// CastShadows
	Label = ToWxString("CastShadows");
	wxPGProperty* PCastShadows = PG->AppendIn(PC, new wxBoolProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PCastShadows, E->getCastShadows());

	// DisplaySkeleton
	Label = ToWxString("DisplaySkeleton");
	wxPGProperty* PDisplaySkeleton = PG->AppendIn(PC, new wxBoolProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PDisplaySkeleton, E->getDisplaySkeleton());

	return true;
}
bool OViSESelectionManager::addLightToPGCategory(wxPropertyCategory* PC, Ogre::Light* L)
{
	return true;
}
bool OViSESelectionManager::addSceneNodeToPGCategory(wxPropertyCategory* PC, Ogre::SceneNode* SN, wxString MOName)
{
	if ( PC == 0 ) return false;

	wxPropertyGrid* PG = PC->GetGrid();
	if ( PG == 0 ) return false;

	wxString MONameAndPoint = MOName + ToWxString(".");
	wxString Label;

	// Position
	Label = ToWxString("Position");
	wxPGProperty* Pp = PG->AppendIn(PC, new wxStringProperty(Label, MONameAndPoint + Label, wxT("<composed>")));
	wxPGProperty* Ppx = PG->AppendIn(Pp, new wxFloatProperty(wxT("x"), wxT("px")));
	PG->SetPropertyValidator(Ppx, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Ppy = PG->AppendIn(Pp, new wxFloatProperty(wxT("y"), wxT("py")));
	PG->SetPropertyValidator(Ppy, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Ppz = PG->AppendIn(Pp, new wxFloatProperty(wxT("z"), wxT("pz")));
	PG->SetPropertyValidator(Ppz, wxTextValidator(wxFILTER_NUMERIC));
	Pp->SetExpanded(false);

	// Set values
	PG->SetPropertyValue(Ppx, (float)SN->getPosition().x);
	PG->SetPropertyValue(Ppy, (float)SN->getPosition().y);
	PG->SetPropertyValue(Ppz, (float)SN->getPosition().z);

	// Rotation
	Label = ToWxString("Rotation");
	wxPGProperty* Pr = PG->Append(new wxStringProperty(Label, MONameAndPoint + Label, wxT("<composed>")));
	wxPGProperty* Prx = PG->AppendIn(Pr, new wxFloatProperty(wxT("x"), wxT("rx")));
	PG->SetPropertyValidator(Prx, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Pry = PG->AppendIn(Pr, new wxFloatProperty(wxT("y"), wxT("ry")));
	PG->SetPropertyValidator(Pry, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Prz = PG->AppendIn(Pr, new wxFloatProperty(wxT("z"), wxT("rz")));
	PG->SetPropertyValidator(Prz, wxTextValidator(wxFILTER_NUMERIC));
	Pr->SetExpanded(false);

	// Set values
	PG->SetPropertyValue(Prx, (float)SN->getOrientation().getPitch().valueDegrees());
	PG->SetPropertyValue(Pry, (float)SN->getOrientation().getRoll().valueDegrees());
	PG->SetPropertyValue(Prz, (float)SN->getOrientation().getYaw().valueDegrees());

	// Scale
	Label = ToWxString("Scale");
	wxPGProperty* Ps = PG->Append(new wxStringProperty(Label, MONameAndPoint + Label, wxT("<composed>")));
	wxPGProperty* Psx = PG->AppendIn(Ps, new wxFloatProperty(wxT("x"), wxT("sx")));
	PG->SetPropertyValidator(Psx, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Psy = PG->AppendIn(Ps, new wxFloatProperty(wxT("y"), wxT("sy")));
	PG->SetPropertyValidator(Psy, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* Psz = PG->AppendIn(Ps, new wxFloatProperty(wxT("z"), wxT("sz")));
	PG->SetPropertyValidator(Psz, wxTextValidator(wxFILTER_NUMERIC));
	Ps->SetExpanded(false);

	// Set values
	PG->SetPropertyValue(Psx, (float)SN->getScale().x);
	PG->SetPropertyValue(Psy, (float)SN->getScale().y);
	PG->SetPropertyValue(Psz, (float)SN->getScale().z);
	
	return true;
}
bool OViSESelectionManager::addMovableObjectToPG(wxPropertyGrid* PG, Ogre::MovableObject* MO)
{
	if ( PG == 0 ) return false;
	if ( MO == 0 ) return false;
	
	OViSEOgreEnums::MovableObject::MovableType MT_Enum = OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getMovableObjectAsEnum(MO);

	// Setup category
	wxString CategoryHeadline;

	switch(MT_Enum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:
			CategoryHeadline << ToWxString("BillBoardChain : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet:
			CategoryHeadline << ToWxString("BillboardSet : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera:
			CategoryHeadline << ToWxString("Camera : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity:
			CategoryHeadline << ToWxString("Entity : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum:
			CategoryHeadline << ToWxString("Frustum : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance:
			CategoryHeadline << ToWxString("InstancedGeometry.BatchInstance : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light:
			CategoryHeadline << ToWxString("Light : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject:
			CategoryHeadline << ToWxString("ManualObject : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane:
			CategoryHeadline << ToWxString("MovablePlane : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:
			CategoryHeadline << ToWxString("ParticleSystem : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:
			CategoryHeadline << ToWxString("RibbonTrail : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:
			CategoryHeadline << ToWxString("SimpleRenderable : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:
			CategoryHeadline << ToWxString("StaticGeometry.Region : '") << ToWxString(MO->getName()) << ToWxString("'");
			break;

		default:
			CategoryHeadline << ToWxString("MovableObject : '") << ToWxString(MO->getName()) << ToWxString("'");
			return false;
			break;
	}

	wxPropertyCategory* PC = new wxPropertyCategory(CategoryHeadline, ToWxString(MO->getName()));
	PG->Append(PC);

	switch(MT_Enum)
	{
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillBoardChain: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_BillboardSet: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Camera: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Entity: this->addEntityToPGCategory(PC, (Ogre::Entity*) MO); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Frustum: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_Light: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ManualObject: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_MovablePlane: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_ParticleSystem: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_RibbonTrail: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		case OViSEOgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region: this->addNOTIMPLEMENTEDToPGCategory(PC); break;
		default: this->addNOTIMPLEMENTEDToPGCategory(PC); return false; break;
	}

	this->addSceneNodeToPGCategory(PC, MO->getParentSceneNode(), ToWxString(MO->getName()));

	PC->SetExpanded(false);
	return true;
}
bool OViSESelectionManager::generatePropertyGridContentFromSelection(wxPropertyGrid* PG) { return this->generatePropertyGridContentFromSelection(PG, this->Selection); }
bool OViSESelectionManager::generatePropertyGridContentFromSelection(wxPropertyGrid* PG, wxString UniqueNameOfSelection)
{
	if (UniqueNameOfSelection.IsEmpty())
	{
		return this->generatePropertyGridContentFromSelection(PG, this->Selection);
	}

	if (this->Selections.count(UniqueNameOfSelection) == 1)
	{
		return this->generatePropertyGridContentFromSelection(PG, this->Selections[UniqueNameOfSelection]);
	}
	
	return false;
}
bool OViSESelectionManager::generatePropertyGridContentFromSelection(wxPropertyGrid* PG, OViSESelection S)
{
	if ( PG == 0 ) return false;

	Ogre::SceneManager* SM = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(S.getSceneManagerName()));
	PG->Clear();

	wxPropertyCategory* PCSceneManager = new wxPropertyCategory(ToWxString("SceneManager"));
	PG->Append(PCSceneManager);
	PG->Append(new wxStringProperty(ToWxString("Name"), ToWxString("SceneManagerName")));
	PG->SetPropertyValue(ToWxString("SceneManagerName"), S.getSceneManagerName());
	PCSceneManager->SetExpanded(false);

	for ( OViSEOgreEnums::HashMap_Enums_MovableType_ByString::iterator IT = S.SelectedObjects.begin(); IT != S.SelectedObjects.end(); ++IT )
	{
		wxString Name_MovableObject = IT->first;
		OViSEOgreEnums::MovableObject::MovableType Type_MovableObject = IT->second;
		wxString Name_MovableType = OViSEOgreEnums::EnumTranslator_MovableType::GetSingletonPtr()->getEnumAsString(Type_MovableObject);		
		Ogre::MovableObject* MO = SM->getMovableObject(ToOgreString(Name_MovableObject), ToOgreString(Name_MovableType));
		this->addMovableObjectToPG(PG, MO);
	}

	return true;
}
// Handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
bool OViSESelectionManager::handlePropertyChanged(wxPGProperty* ChangedProperty)
{
	// It may be NULL
    if ( ChangedProperty == 0 ) return false;

    // Get name of changed property
	wxString PName = ChangedProperty->GetName();//zAxis_Entity_0.Rotation.rz
	wxStringTokenizer StrTok(PName, ToWxString("."));

	// STAGE 1: Handle object id
	wxString UniqueNameOfObject;
	if (StrTok.HasMoreTokens())
	{
		UniqueNameOfObject = StrTok.GetNextToken();

		bool Match = false;
		if ((!Match) && UniqueNameOfObject.Contains(ToWxString("_Camera_")))
		{
			Match = true;
		}
		if ((!Match) && UniqueNameOfObject.Contains(ToWxString("_Entity_")))
		{
			if (OgreAPIMediator::GetSingletonPtr()->hasEntity(this->Selection.getSceneManagerName(), UniqueNameOfObject))
			{
				Ogre::Entity* E = OgreAPIMediator::GetSingletonPtr()->getEntityPtr(this->Selection.getSceneManagerName(), UniqueNameOfObject);
				wxString subPGID;
				while(StrTok.HasMoreTokens())
				{
					subPGID << StrTok.GetNextToken();
					if (StrTok.HasMoreTokens()) subPGID << ToWxString(".");
				}
				this->handleEntityChanged(E, subPGID, ChangedProperty->GetValue());
			}
			Match = true;
		}
		if ((!Match) && UniqueNameOfObject.Contains(ToWxString("_Light_")))
		{
			Match = true;
		}
		if ((!Match) && UniqueNameOfObject.Contains(ToWxString("_SceneNode_")))
		{
			Match = true;
		}
		if (!Match) // Could be a Ogre::SceneManager too!!!
		{
			Match = true;
		}
	}


	return true;
	/*


	std::string objname = (const char*)mObjectProperties->GetPropertyValueAsString(wxT("MeshName")).ToAscii();

	OViSESelectionMap selObjs = OViSESceneHandling::getSingletonPtr()->getSelectedObjects();
	if(selObjs.empty())
		return;
	Ogre::SceneNode *snode = selObjs[objname]->getParentSceneNode();
	if(!snode)
		return;
	Ogre::Vector3 pos = snode->getPosition();
	Ogre::Vector3 scale = snode->getScale();
	Ogre::Quaternion tmprot = snode->getOrientation();

	wxVariant tmp = prop->GetValue();
	wxString tmpstr = tmp.GetString();

	double vals[3];

	wxStringTokenizer checker(tmpstr, wxT(";"));

	if(name == wxString(wxT("Translation")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		pos = Ogre::Vector3(vals[0], vals[1], vals[2]);
	}
	if(name == wxString(wxT("Translation.tx")))
	{
		float tx = tmp.GetDouble();
		pos.x = tx;
	}
	if(name == wxString(wxT("Translation.ty")))
	{
		float ty = tmp.GetDouble();
		pos.y = ty;
	}
	if(name == wxString(wxT("Translation.tz")))
	{
		float tz = tmp.GetDouble();
		pos.z = tz;
	}

	snode->setPosition(pos);

	if(name == wxString(wxT("Rotation")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		Ogre::Radian p = Ogre::Radian(Ogre::Degree(vals[0])) - tmprot.getPitch();
		Ogre::Radian r = Ogre::Radian(Ogre::Degree(vals[1])) - tmprot.getRoll();
		Ogre::Radian y = Ogre::Radian(Ogre::Degree(vals[2])) - tmprot.getYaw();
		snode->pitch(p);
		snode->roll(r);
		snode->yaw(y);
	}
	if(name == wxString(wxT("Rotation.rx")))
	{
		float rx = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(rx)) - tmprot.getPitch());
	}
	if(name == wxString(wxT("Rotation.ry")))
	{
		float ry = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(ry)) - tmprot.getRoll());
	}
	if(name == wxString(wxT("Rotation.rz")))
	{
		float rz = tmp.GetDouble();
		snode->pitch(Ogre::Radian(Ogre::Degree(rz)) - tmprot.getYaw());
	}

	if(name == wxString(wxT("Scale")))
	{
		for(int i=0; i<3; i++)
		{
			checker.GetNextToken().ToDouble(&vals[i]);
		}
		scale = Ogre::Vector3(vals[0], vals[1], vals[2]);
	}
	if(name == wxString(wxT("Scale.sx")))
	{
		float sx = tmp.GetDouble();
		scale.x = sx;
	}
	if(name == wxString(wxT("Scale.sy")))
	{
		float sy = tmp.GetDouble();
		scale.y = sy;
	}
	if(name == wxString(wxT("Scale.sz")))
	{
		float sz = tmp.GetDouble();
		scale.z = sz;
	}

	snode->setScale(scale);

	// call update for scene structure
	mSceneHdlr->showSceneGraphStructure(true);
*/
}
bool OViSESelectionManager::handleEntityChanged(Ogre::Entity* E, wxString subPGID, wxVariant value)
{
	// It may be NULL
	if ( E == 0 ) return false;

	// Get name of changed property
	wxStringTokenizer StrTok(subPGID, ToWxString("."));
	
	// STAGE 2: Handle attribute

	wxString AttributeID = StrTok.GetNextToken();

	bool Match = false;
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Position")))
	{
		Ogre::SceneNode* SN = E->getParentSceneNode();
		if (StrTok.HasMoreTokens()) Match = this->handlePositionChanged(SN, StrTok.GetNextToken(), value);
		else
		{
			//TODO: go futher here
			Match = true;
		}
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Rotation")))
	{
		Ogre::SceneNode* SN = E->getParentSceneNode();
		if (StrTok.HasMoreTokens()) Match = this->handleRotationChanged(SN, StrTok.GetNextToken(), value);
		else
		{
			//TODO: go futher here
			Match = true;
		}
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Scale")))
	{
		Ogre::SceneNode* SN = E->getParentSceneNode();
		if (StrTok.HasMoreTokens()) Match = this->handleScaleChanged(SN, StrTok.GetNextToken(), value);
		else
		{
			//TODO: go futher here
			Match = true;
		}
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Name"))) // not editable
	{
		Match = true;
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Mesh"))) // not editable
	{
		Match = true;
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("CastShadows")))
	{
		E->setCastShadows(value.GetBool());
		Match = true;
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("DisplaySkeleton")))
	{
		E->setDisplaySkeleton(value.GetBool());
		Match = true;
	}

	return Match;
}

bool OViSESelectionManager::handlePositionChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	Ogre::Vector3 P = SN->getPosition();

	bool Match = false;
	if ((!Match) && subPGID.IsSameAs(ToWxString("px")))
	{
		P.x = value.GetDouble();
		SN->setPosition(P);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("py")))
	{
		P.y = value.GetDouble();
		SN->setPosition(P);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("pz")))
	{
		P.z = value.GetDouble();
		SN->setPosition(P);
		Match = true;
	}

	return Match;
}
bool OViSESelectionManager::handleScaleChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	Ogre::Vector3 S = SN->getScale();

	bool Match = false;
	if ((!Match) && subPGID.IsSameAs(ToWxString("sx")))
	{
		S.x = value.GetDouble();
		SN->setScale(S);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("sy")))
	{
		S.y = value.GetDouble();
		SN->setScale(S);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("sz")))
	{
		S.z = value.GetDouble();
		SN->setScale(S);
		Match = true;
	}

	return Match;
}
bool OViSESelectionManager::handleRotationChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	Ogre::Quaternion Q = SN->getOrientation();
	Ogre::Degree OldP = Q.getPitch();
	Ogre::Degree OldR = Q.getRoll();
	Ogre::Degree OldY = Q.getYaw();

	Ogre::Degree NewDegree = Ogre::Degree(value.GetDouble());

	bool Match = false;
	if ((!Match) && subPGID.IsSameAs(ToWxString("rx"))) // X -> Pitch
	{
		Ogre::Degree NewP = NewDegree - OldP;
		SN->pitch(Ogre::Radian(NewP), Ogre::Node::TS_WORLD);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("ry"))) // Y -> Roll
	{
		Ogre::Degree NewR = NewDegree - OldR;
		SN->roll(Ogre::Radian(NewR), Ogre::Node::TS_WORLD);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("rz"))) // Z -> Yaw
	{
		Ogre::Degree NewY = NewDegree - OldY;
		SN->yaw(Ogre::Radian(NewY), Ogre::Node::TS_WORLD);
		Match = true;
	}

	return Match;
}