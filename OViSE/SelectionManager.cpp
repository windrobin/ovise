#include "../OViSE/SelectionManager.h"

// Singleton
SelectionManager* SelectionManager::instance = 0;
SelectionManager* SelectionManager::getSingletonPtr()
{
	if (SelectionManager::instance == 0) SelectionManager::instance = new SelectionManager();
	return SelectionManager::instance;
}

SelectionManager::SelectionManager() { this->Valid = true; }
SelectionManager::~SelectionManager(void) { }
// General
// wxPropertyGrid-Handling
bool SelectionManager::IsValid() { return this->Valid; }
bool SelectionManager::IsSelected(QualifiedName qName)
{
	if (this->Selection.IsEmpty()) return false;
	for(unsigned long IT = 0; IT < this->Selection.Count(); IT++)
	{
		if (this->Selection[IT].UniqueName().IsSameAs(qName.UniqueName())) return true;
	}
	return false;
}
bool SelectionManager::AddNOTIMPLEMENTEDToPGCategory(wxPropertyCategory* PC)
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
bool SelectionManager::AddCameraToPGCategory(wxPropertyCategory* PC, Ogre::Camera* C)
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
bool SelectionManager::AddEntityToPGCategory(wxPropertyCategory* PC, Ogre::Entity* E)
{
	// Validate parameters
	if ( PC == 0 ) return false;
	wxPropertyGrid* PG = PC->GetGrid();
	if ( PG == 0 ) return false;
	if ( E == 0 ) return false;

	wxString UniqueName = ToWxString(E->getName());
	QualifiedName qEntity = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetQualifiedNameOfObject(UniqueName);
	if ( !qEntity.IsValid() ) return false;

	wxString EntityNameAndPoint = qEntity.UniqueName() + ToWxString(".");
	wxString Label;

	// Name
	Label = ToWxString("Name");
	wxPGProperty* PName = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PName, qEntity.UniqueName());
	PG->DisableProperty(PName);

	// Native name
	Label = ToWxString("Native");
	wxPGProperty* PNameNative = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PNameNative, qEntity.NativeName());
	PG->DisableProperty(PNameNative);

	// Generic hint
	Label = ToWxString("Hint");
	wxPGProperty* PNameHint = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PNameHint, qEntity.GenericHint());
	PG->DisableProperty(PNameHint);

	// Generic name
	Label = ToWxString("Generic");
	wxPGProperty* PNameGeneric = PG->AppendIn(PC, new wxStringProperty(Label, EntityNameAndPoint + Label));
	PG->SetPropertyValue(PNameGeneric, qEntity.GenericName());
	PG->DisableProperty(PNameGeneric);

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
bool SelectionManager::AddLightToPGCategory(wxPropertyCategory* PC, Ogre::Light* L)
{
	return true;
}
bool SelectionManager::AddSceneNodeToPGCategory(wxPropertyCategory* PC, Ogre::SceneNode* SN, QualifiedName qMovableObject)
{
	// Validate parameters
	if ( PC == 0 ) return false;
	wxPropertyGrid* PG = PC->GetGrid();
	if ( PG == 0 ) return false;
	if ( SN == 0 ) return false;
	if ( !qMovableObject.IsValid() ) return false;

	wxString MONameAndPoint = qMovableObject.UniqueName() + ToWxString(".");
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

	Ogre::Quaternion DEBUG_quaternion = SN->getOrientation();

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
bool SelectionManager::AddMovableObjectToPG(wxPropertyGrid* PG, Ogre::MovableObject* MO)
{
	if ( PG == 0 ) return false;
	if ( MO == 0 ) return false;
	
	// Get QualifiedName
	QualifiedName qMovableObject = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetQualifiedNameOfObject(ToWxString(MO->getName()));
	if ( !qMovableObject.IsValid() ) return false;

	// Get Ogre::MovableObject-Type
	OgreEnums::MovableObject::MovableType MT_Enum = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableType(qMovableObject);

	// Setup category
	wxString CategoryHeadline;
	switch(MT_Enum)
	{
		case OgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:			CategoryHeadline << ToWxString("BillBoardChain : '");		break;
		case OgreEnums::MovableObject::MOVABLETYPE_BillboardSet:			CategoryHeadline << ToWxString("BillboardSet : '");			break;
		case OgreEnums::MovableObject::MOVABLETYPE_Camera:					CategoryHeadline << ToWxString("Camera : '");				break;
		case OgreEnums::MovableObject::MOVABLETYPE_Entity:					CategoryHeadline << ToWxString("Entity : '");				break;
		case OgreEnums::MovableObject::MOVABLETYPE_Frustum:					CategoryHeadline << ToWxString("Frustum : '");				break;
		case OgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance: CategoryHeadline << ToWxString("InstancedGeometry.BatchInstance : '"); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Light:					CategoryHeadline << ToWxString("Light : '");				break;
		case OgreEnums::MovableObject::MOVABLETYPE_ManualObject:			CategoryHeadline << ToWxString("ManualObject : '");			break;
		case OgreEnums::MovableObject::MOVABLETYPE_MovablePlane:			CategoryHeadline << ToWxString("MovablePlane : '");			break;
		case OgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:			CategoryHeadline << ToWxString("ParticleSystem : '");		break;
		case OgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:				CategoryHeadline << ToWxString("RibbonTrail : '");			break;
		case OgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:		CategoryHeadline << ToWxString("SimpleRenderable : '");		break;
		case OgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:	CategoryHeadline << ToWxString("StaticGeometry.Region : '");break;

		default:
			CategoryHeadline << ToWxString("MovableObject : '") << qMovableObject.UniqueName() << ToWxString("'");
			return false;
			break;
	}
	CategoryHeadline << qMovableObject.UniqueName() << ToWxString("'");

	// Setup properties of category
	wxPropertyCategory* PC = new wxPropertyCategory(CategoryHeadline, qMovableObject.UniqueName());
	PG->Append(PC);

	// ...Ogre::MovableObject-part
	switch(MT_Enum)
	{
		case OgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:			this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_BillboardSet:			this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Camera:					this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Entity:					this->AddEntityToPGCategory(PC, (Ogre::Entity*)MO); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Frustum:					this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance: this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Light:					this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_ManualObject:			this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_MovablePlane:			this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:			this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:				this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:		this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		case OgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:	this->AddNOTIMPLEMENTEDToPGCategory(PC); break;
		default: this->AddNOTIMPLEMENTEDToPGCategory(PC); return false; break;
	}

	// ...Ogre::SceneNode-part
	this->AddSceneNodeToPGCategory(PC, MO->getParentSceneNode(), qMovableObject);

	PC->SetExpanded(false);
	return true;
}
bool SelectionManager::GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG) { return this->GeneratePropertyGridContentFromSelection(PG, this->Selection); }
bool SelectionManager::GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG, wxString UniqueNameOfSelection)
{
	/*
	if (UniqueNameOfSelection.IsEmpty())
	{*/
		return this->GeneratePropertyGridContentFromSelection(PG, this->Selection);
	/*}

	if (this->Selections.count(UniqueNameOfSelection) == 1)
	{
		return this->generatePropertyGridContentFromSelection(PG, this->Selections[UniqueNameOfSelection]);
	}
	
	return false;*/
}
bool SelectionManager::GeneratePropertyGridContentFromSelection(wxPropertyGrid* PG, QualifiedNameCollection Selection)
{
	if ( PG == 0 ) return false;

	Ogre::SceneManager* SM = Ogre::Root::getSingletonPtr()->getSceneManager(ToOgreString(OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager().UniqueName()));
	PG->Clear();

	wxPropertyCategory* PCSceneManager = new wxPropertyCategory(ToWxString("SceneManager"));
	PG->Append(PCSceneManager);
	PG->Append(new wxStringProperty(ToWxString("Name"), ToWxString("SceneManagerName")));
	PG->SetPropertyValue(ToWxString("SceneManagerName"), OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager().UniqueName());
	PCSceneManager->SetExpanded(false);

	if (!Selection.IsEmpty())
	{
		for ( unsigned long IT = 0; IT < Selection.Count(); IT++ )
		{
			Ogre::MovableObject* MO = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableObject(Selection[IT]);
			this->AddMovableObjectToPG(PG, MO);
		}
	}
	return true;
}
// Handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
bool SelectionManager::HandlePropertyChanged(wxPGProperty* ChangedProperty)
{
	// It may be NULL
    if ( ChangedProperty == 0 ) return false;

    // Get name of changed property
	wxString PName = ChangedProperty->GetName();//zAxis_Entity_0.Rotation.rz
	wxStringTokenizer StrTok(PName, ToWxString("."));

	// Prepare returnvalue
	bool ReturnValue = false;

	// Handle object id
	if ( StrTok.HasMoreTokens() )
	{
		// STAGE 1: Get UniqueName and rebuild rest of PropertyID
		wxString UniqueName = StrTok.GetNextToken();
		wxString subPGID;
		while(StrTok.HasMoreTokens())
		{
			subPGID << StrTok.GetNextToken();
			if (StrTok.HasMoreTokens()) subPGID << ToWxString(".");
		}
		
		// STAGE 2: Get QualifiedNames by UniqueName
		QualifiedName qName = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetQualifiedNameOfObject(UniqueName);
		if ( !qName.IsValid() ) return false;

		// STAGE 3: Get Type by indentified QualifiedName
		OgreEnums::MovableObject::MovableType Type = OgreAPIMediator::GetSingletonPtr()->QuickObjectAccess.GetMovableType(qName);

		// STAGE 4: Futher calls depend on type...
		bool Match = false;
		switch(Type)
		{
		case OgreEnums::MovableObject::MOVABLETYPE_Invalid:
			// STAGE 4.x: Object is no Ogre::MovableObject. Could be Ogre::SceneManager or Ogre::SceneNode
			
			if ((!Match) && OgreAPIMediator::GetSingletonPtr()->HasSceneManager(qName))
			{
				// Got Ogre::SceneManager
				this->IsValid(); // DEBUG: Handling of that type not implemented yet !!!
				Match = false;
			}
			if ((!Match) && OgreAPIMediator::GetSingletonPtr()->HasSceneNode(qName))
			{
				// Got Ogre::SceneNode
				this->IsValid(); // DEBUG: Handling of that type not implemented yet !!!
				Match = false;
			}	
			break;

		case OgreEnums::MovableObject::MOVABLETYPE_Camera:
			Match = false; // DEBUG: Handling of that type not implemented yet !!!
			break;

		case OgreEnums::MovableObject::MOVABLETYPE_Entity:	ReturnValue = this->HandleEntityChanged(qName, subPGID, ChangedProperty->GetValue()); break;

		case OgreEnums::MovableObject::MOVABLETYPE_Light:
			Match = false; // DEBUG: Handling of that type not implemented yet !!!
			break;

		default:
			// DEBUG: Handling of that type not implemented yet !!!
			Match = false;
			break;
		}
	}

	return ReturnValue;
}
bool SelectionManager::HandleEntityChanged(QualifiedName qEntity, wxString subPGID, wxVariant value)
{
	// Verify qEntity
	if (!OgreAPIMediator::GetSingletonPtr()->HasEntity(qEntity)) return false;
	Ogre::Entity* E = OgreAPIMediator::GetSingletonPtr()->GetEntityPtr(qEntity);
	return this->HandleEntityChanged(E, subPGID, value);
}
bool SelectionManager::HandleEntityChanged(Ogre::Entity* E, wxString subPGID, wxVariant value)
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
		if (StrTok.HasMoreTokens()) Match = this->HandlePositionChanged(SN, StrTok.GetNextToken(), value);
		else
		{
			wxVariant V;
			wxStringTokenizer SemiSeperator(value.GetString(), wxT(";"));
			
			V = SemiSeperator.GetNextToken();
			this->HandlePositionChanged(SN, ToWxString("px"), V);
			V = SemiSeperator.GetNextToken();
			this->HandlePositionChanged(SN, ToWxString("py"), V);
			V = SemiSeperator.GetNextToken();
			this->HandlePositionChanged(SN, ToWxString("pz"), V);

			Match = true;
		}
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Rotation")))
	{
		Ogre::SceneNode* SN = E->getParentSceneNode();
		if (StrTok.HasMoreTokens())
		{
			Match = this->HandleRotationChanged(SN, StrTok.GetNextToken(), value);
		}
		else
		{
			wxVariant V;
			wxStringTokenizer SemiSeperator(value.GetString(), wxT(";"));
			
			V = SemiSeperator.GetNextToken();
			this->HandleRotationChanged(SN, ToWxString("rx"), V);
			V = SemiSeperator.GetNextToken();
			this->HandleRotationChanged(SN, ToWxString("ry"), V);
			V = SemiSeperator.GetNextToken();
			this->HandleRotationChanged(SN, ToWxString("rz"), V);

			Match = true;
		}
	}
	if ((!Match) && AttributeID.IsSameAs(ToWxString("Scale")))
	{
		Ogre::SceneNode* SN = E->getParentSceneNode();
		if (StrTok.HasMoreTokens()) Match = this->HandleScaleChanged(SN, StrTok.GetNextToken(), value);
		else
		{
			wxVariant V;
			wxStringTokenizer SemiSeperator(value.GetString(), wxT(";"));
			
			V = SemiSeperator.GetNextToken();
			this->HandleScaleChanged(SN, ToWxString("sx"), V);
			V = SemiSeperator.GetNextToken();
			this->HandleScaleChanged(SN, ToWxString("sy"), V);
			V = SemiSeperator.GetNextToken();
			this->HandleScaleChanged(SN, ToWxString("sz"), V);

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

bool SelectionManager::HandlePositionChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
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
bool SelectionManager::HandleScaleChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
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
bool SelectionManager::HandleRotationChanged(Ogre::SceneNode* SN, wxString subPGID, wxVariant value)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	// Prepare values
	Ogre::Quaternion Q = SN->getOrientation();

	Ogre::Radian OldP = Q.getPitch();
	Ogre::Radian OldR = Q.getRoll();
	Ogre::Radian OldY = Q.getYaw();

	wxString DEBUG_MSG;
	DEBUG_MSG = "Pitch (old): ";
	DEBUG_MSG << (double)Ogre::Degree(OldP).valueDegrees();
	Logging::GetSingletonPtr()->WriteToOgreLog(DEBUG_MSG, Logging::Normal);

	DEBUG_MSG = "Roll (old): ";
	DEBUG_MSG << (double)Ogre::Degree(OldR).valueDegrees();
	Logging::GetSingletonPtr()->WriteToOgreLog(DEBUG_MSG, Logging::Normal);

	DEBUG_MSG = "Yaw (old): ";
	DEBUG_MSG << (double)Ogre::Degree(OldY).valueDegrees();
	Logging::GetSingletonPtr()->WriteToOgreLog(DEBUG_MSG, Logging::Normal);
	
	Ogre::Radian NewRadian = Ogre::Radian(Ogre::Degree(value.GetDouble()));

	DEBUG_MSG = "New value: ";
	DEBUG_MSG << (double)Ogre::Degree(NewRadian).valueDegrees();
	Logging::GetSingletonPtr()->WriteToOgreLog(DEBUG_MSG, Logging::Normal);

	SN->setOrientation(Ogre::Quaternion::IDENTITY);

	bool Match = false;
	if ((!Match) && subPGID.IsSameAs(ToWxString("rx"))) // X -> Pitch
	{
		SN->pitch(NewRadian, Ogre::Node::TS_PARENT);
		SN->roll(OldR, Ogre::Node::TS_PARENT);
		SN->yaw(OldY, Ogre::Node::TS_PARENT);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("ry"))) // Y -> Roll
	{
		SN->pitch(OldP, Ogre::Node::TS_PARENT);
		SN->roll(NewRadian, Ogre::Node::TS_PARENT);
		SN->yaw(OldY, Ogre::Node::TS_PARENT);
		Match = true;
	}
	if ((!Match) && subPGID.IsSameAs(ToWxString("rz"))) // Z -> Yaw
	{
		SN->pitch(OldP, Ogre::Node::TS_PARENT);
		SN->roll(OldR, Ogre::Node::TS_PARENT);
		SN->yaw(NewRadian, Ogre::Node::TS_PARENT);
		Match = true;
	}

	return Match;
}

// OLD code
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