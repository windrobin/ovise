#include "../OViSE/SelectionManager.h"

// Singleton
SelectionManager* SelectionManager::instance = 0;
SelectionManager* SelectionManager::getSingletonPtr()
{
	if (SelectionManager::instance == 0) SelectionManager::instance = new SelectionManager();
	return SelectionManager::instance;
}

SelectionManager::SelectionManager() { }
SelectionManager::~SelectionManager(void) { }
// Get-/Set-Methods of attributes
wxPropertyGrid* SelectionManager::GetPropertyGrid() { return this->PG; }
void SelectionManager::SetPropertyGrid(wxPropertyGrid* PG) { this->PG = PG; }
// General
bool SelectionManager::IsValid()
{
	if (this->PG == 0) return false;
	else return true;
}
bool SelectionManager::IsSelected(QualifiedName qName)
{
	if (this->Selection.IsEmpty()) return false;
	for(unsigned long IT = 0; IT < this->Selection.Count(); IT++)
	{
		if (this->Selection[IT].UniqueName().IsSameAs(qName.UniqueName())) return true;
	}
	return false;
}
bool SelectionManager::AddNOTIMPLEMENTED()
{
	if ( PG == 0 ) return false;

	// Info
	wxPGProperty* PInfo = this->PG->AppendIn(this->PCSelection, new wxStringProperty(wxT("INFO"), wxPG_LABEL));
	this->PG->SetPropertyValue(PInfo, ToWxString("not implemented"));
	this->PG->DisableProperty(PInfo);

	return true;
}
bool SelectionManager::AddCamera(Ogre::Camera* C)
{
	// Validate parameters
	if ( C == 0 ) return false;

	// Validate members
	if ( this->PG == 0 ) return false;
	
	// Get QualifiedName
	QualifiedName qCamera = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(ToWxString(C->getName()));
	if ( !OgreMediator::GetSingletonPtr()->iCamera.Exist(qCamera) ) return false;

	// Handle recusive processing of SceneNode
	wxPropertyCategory* PCParent = this->AddSceneNode((Ogre::SceneNode*)C->getParentNode());
	if (PCParent == 0) return false;

	// Perpare ID and Label
	wxString Label, CategoryID, PropertyID;
	CategoryID = ToWxString(C->getName());

	// Add cathergory to grid
	Label = ToWxString("Camera: '");
	Label << ToWxString(C->getName());
	Label << ToWxString("'");
	
	wxPropertyCategory* PCCamera = new wxPropertyCategory(Label, CategoryID);
	this->PG->AppendIn(PCParent, PCCamera);
	PCCamera->SetExpanded(false);

	// Name
	Label = ToWxString("Name");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qCamera.UniqueName());
	this->PG->DisableProperty(PropertyID);

	// Native name
	Label = ToWxString("Native");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qCamera.NativeName());
	this->PG->DisableProperty(PropertyID);

	// Generic hint
	Label = ToWxString("Hint");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qCamera.GenericHint());
	this->PG->DisableProperty(PropertyID);

	// Generic name
	Label = ToWxString("Generic");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qCamera.GenericName());
	this->PG->DisableProperty(PropertyID);

	// FOVy
	Label = ToWxString("FOVy");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxFloatProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, C->getFOVy().valueDegrees());
	this->PG->SetPropertyValidator(PropertyID, wxTextValidator(wxFILTER_NUMERIC));

	// AspectRatio
	Label = ToWxString("AspectRatio");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxFloatProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, C->getAspectRatio());
	this->PG->SetPropertyValidator(PropertyID, wxTextValidator(wxFILTER_NUMERIC));

	// ClipDistance (near)
	Label = ToWxString("ClipDistance (near)");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxFloatProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, C->getNearClipDistance());
	this->PG->SetPropertyValidator(PropertyID, wxTextValidator(wxFILTER_NUMERIC));

	// ClipDistance (far)
	Label = ToWxString("ClipDistance (far)");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCCamera, new wxFloatProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, C->getFarClipDistance());
	this->PG->SetPropertyValidator(PropertyID, wxTextValidator(wxFILTER_NUMERIC));

	return true;
}
bool SelectionManager::AddEntity(Ogre::Entity* E)
{
	// Validate parameters
	if ( E == 0 ) return false;

	// Validate members
	if ( this->PG == 0 ) return false;
	
	// Get QualifiedName
	QualifiedName qEntity = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(ToWxString(E->getName()));
	if ( !OgreMediator::GetSingletonPtr()->iEntity.Exist(qEntity) ) return false;

	// Handle recusive processing of SceneNode
	wxPropertyCategory* PCParent = this->AddSceneNode((Ogre::SceneNode*)E->getParentNode());
	if (PCParent == 0) return false;

	// Perpare ID and Label
	wxString Label, CategoryID, PropertyID;
	CategoryID = ToWxString(E->getName());

	// Add cathergory to grid
	Label = ToWxString("Entity: '");
	Label << ToWxString(E->getName());
	Label << ToWxString("'");
	
	wxPropertyCategory* PCEntity = new wxPropertyCategory(Label, CategoryID);
	this->PG->AppendIn(PCParent, PCEntity);
	PCEntity->SetExpanded(false);

	// Name
	Label = ToWxString("Name");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qEntity.UniqueName());
	this->PG->DisableProperty(PropertyID);

	// Native name
	Label = ToWxString("Native");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qEntity.NativeName());
	this->PG->DisableProperty(PropertyID);

	// Generic hint
	Label = ToWxString("Hint");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qEntity.GenericHint());
	this->PG->DisableProperty(PropertyID);

	// Generic name
	Label = ToWxString("Generic");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qEntity.GenericName());
	this->PG->DisableProperty(PropertyID);

	// Meshfile
	Label = ToWxString("Mesh");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, E->getMesh()->getName());
	this->PG->DisableProperty(PropertyID);

	// CastShadows
	Label = ToWxString("CastShadows");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxBoolProperty(Label, PropertyID, E->getCastShadows()));

	// DisplaySkeleton
	Label = ToWxString("DisplaySkeleton");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCEntity, new wxBoolProperty(Label, PropertyID, E->getDisplaySkeleton()));

	return true;
}
bool SelectionManager::AddLight(Ogre::Light* L)
{
	// TODO: Presentation should change with specific type of light !!!

	// Validate parameters
	if ( L == 0 ) return false;

	// Validate members
	if ( this->PG == 0 ) return false;
	
	// Get QualifiedName
	QualifiedName qLight = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(ToWxString(L->getName()));
	if ( !OgreMediator::GetSingletonPtr()->iLight.Exist(qLight) ) return false;

	// Handle recusive processing of SceneNode
	wxPropertyCategory* PCParent = this->AddSceneNode((Ogre::SceneNode*)L->getParentNode());
	if (PCParent == 0) return false;

	// Perpare ID and Label
	wxString Label, CategoryID, PropertyID;
	CategoryID = ToWxString(L->getName());

	// Add cathergory to grid
	Label = ToWxString("Light: '");
	Label << ToWxString(L->getName());
	Label << ToWxString("'");
	
	wxPropertyCategory* PCLight = new wxPropertyCategory(Label, CategoryID);
	this->PG->AppendIn(PCParent, PCLight);
	PCLight->SetExpanded(false);

	// Name
	Label = ToWxString("Name");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qLight.UniqueName());
	this->PG->DisableProperty(PropertyID);

	// Native name
	Label = ToWxString("Native");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qLight.NativeName());
	this->PG->DisableProperty(PropertyID);

	// Generic hint
	Label = ToWxString("Hint");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qLight.GenericHint());
	this->PG->DisableProperty(PropertyID);

	// Generic name
	Label = ToWxString("Generic");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, qLight.GenericName());
	this->PG->DisableProperty(PropertyID);

	// Type 
	Label = ToWxString("Type");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxString LightTypeName;
	switch (L->getType())
	{
	case Ogre::Light::LT_DIRECTIONAL:	LightTypeName = ToWxString("LT_DIRECTIONAL");	break;
	case Ogre::Light::LT_POINT:			LightTypeName = ToWxString("LT_POINT");			break;
	case Ogre::Light::LT_SPOTLIGHT:		LightTypeName = ToWxString("LT_SPOTLIGHT");		break;
	default:							LightTypeName = ToWxString("unknown");			break;
	}

	this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, LightTypeName);
	this->PG->SetPropertyValidator(PropertyID, wxTextValidator(wxFILTER_NUMERIC));
	this->PG->DisableProperty(PropertyID);

	// Visible
	Label = ToWxString("Visible");
	PropertyID = CategoryID + ToWxString(".") + Label;
	this->PG->AppendIn(PCLight, new wxBoolProperty(Label, PropertyID, L->getVisible()));

	// Direction
	Label = ToWxString("Direction");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PDirection = this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PDirectionX = this->PG->AppendIn(PDirection, new wxFloatProperty(wxT("x"), wxT("dx")));
	this->PG->SetPropertyValidator(PDirectionX, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PDirectionY = this->PG->AppendIn(PDirection, new wxFloatProperty(wxT("y"), wxT("dy")));
	this->PG->SetPropertyValidator(PDirectionY, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PDirectionZ = this->PG->AppendIn(PDirection, new wxFloatProperty(wxT("z"), wxT("dz")));
	this->PG->SetPropertyValidator(PDirectionZ, wxTextValidator(wxFILTER_NUMERIC));
	PDirection->SetExpanded(false);

	// Set values
	this->PG->SetPropertyValue(PDirectionX, (double)L->getDirection().x);
	this->PG->SetPropertyValue(PDirectionY, (double)L->getDirection().y);
	this->PG->SetPropertyValue(PDirectionZ, (double)L->getDirection().z);

	// DiffuseColour
	Label = ToWxString("Diffuse Colour");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PDiffuseColour = this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PDiffuseColourR = this->PG->AppendIn(PDiffuseColour, new wxFloatProperty(wxT("r"), wxT("dcr")));
	this->PG->SetPropertyValidator(PDiffuseColourR, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PDiffuseColourG = this->PG->AppendIn(PDiffuseColour, new wxFloatProperty(wxT("g"), wxT("dcg")));
	this->PG->SetPropertyValidator(PDiffuseColourG, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PDiffuseColourB = this->PG->AppendIn(PDiffuseColour, new wxFloatProperty(wxT("b"), wxT("dcb")));
	this->PG->SetPropertyValidator(PDiffuseColourB, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PDiffuseColourA = this->PG->AppendIn(PDiffuseColour, new wxFloatProperty(wxT("a"), wxT("dca")));
	this->PG->SetPropertyValidator(PDiffuseColourA, wxTextValidator(wxFILTER_NUMERIC));
	PDiffuseColour->SetExpanded(false);

	// Set values
	this->PG->SetPropertyValue(PDiffuseColourR, (double)L->getDiffuseColour().r);
	this->PG->SetPropertyValue(PDiffuseColourG, (double)L->getDiffuseColour().g);
	this->PG->SetPropertyValue(PDiffuseColourB, (double)L->getDiffuseColour().b);
	this->PG->SetPropertyValue(PDiffuseColourA, (double)L->getDiffuseColour().a);

	// SpecularColour
	Label = ToWxString("Specular Colour");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PSpecularColour = this->PG->AppendIn(PCLight, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PSpecularColourR = this->PG->AppendIn(PSpecularColour, new wxFloatProperty(wxT("r"), wxT("scr")));
	this->PG->SetPropertyValidator(PSpecularColourR, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PSpecularColourG = this->PG->AppendIn(PSpecularColour, new wxFloatProperty(wxT("g"), wxT("scg")));
	this->PG->SetPropertyValidator(PSpecularColourG, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PSpecularColourB = this->PG->AppendIn(PSpecularColour, new wxFloatProperty(wxT("b"), wxT("scb")));
	this->PG->SetPropertyValidator(PSpecularColourB, wxTextValidator(wxFILTER_NUMERIC));
	PSpecularColour->SetExpanded(false);

	// Set values
	this->PG->SetPropertyValue(PSpecularColourR, (double)L->getSpecularColour().r);
	this->PG->SetPropertyValue(PSpecularColourG, (double)L->getSpecularColour().g);
	this->PG->SetPropertyValue(PSpecularColourB, (double)L->getSpecularColour().b);

	return true;
}
wxPropertyCategory* SelectionManager::AddSceneNode(Ogre::SceneNode* SN)
{
	// Validate parameters
	if ( SN == 0 ) return 0;

	// Validate members
	if ( this->PG == 0 ) return false;

	// Get Ogre::SceneManager
	QualifiedName qSceneManager = OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager();
	Ogre::SceneManager* SM = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(qSceneManager);
	if ( SM == 0 ) return 0;

	// Is RSN (RootSceneNode)?
	bool isRoot = (SN == SM->getRootSceneNode());
	
	// Check QualifiedName, if it's no RSN
	if (!isRoot)
	{
		QualifiedName qSceneNode = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(ToWxString(SN->getName()));
		if ( !OgreMediator::GetSingletonPtr()->iSceneNode.Exist(qSceneNode) ) return 0;
	}

	// Perpare ID and Label
	wxString Label, CategoryID, PropertyID;
	CategoryID = ToWxString(SN->getName());
	wxPropertyCategory* PCSceneNode = 0;
	
	// Stop, if category already exists and return it
	PCSceneNode = (wxPropertyCategory*)this->PG->GetProperty(CategoryID);
	if (PCSceneNode != 0) return PCSceneNode;

	// Add cathergory to grid
	Label = ToWxString("SceneNode: '");
	Label << ToWxString(SN->getName());
	Label << ToWxString("'");
	
	PCSceneNode = new wxPropertyCategory(Label, CategoryID);
	this->PG->AppendIn(this->PCSelection, PCSceneNode);

	// Name
	Label = ToWxString("Name");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID));
	this->PG->SetPropertyValue(PropertyID, ToWxString(SN->getName()));
	this->PG->DisableProperty(PropertyID);

	// Native name
	Label = ToWxString("Native");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID));
	if (isRoot) this->PG->SetPropertyValue(PropertyID, ToWxString(""));
	else this->PG->SetPropertyValue(PropertyID, qSceneManager.NativeName());
	this->PG->DisableProperty(PropertyID);

	// Generic hint
	Label = ToWxString("Hint");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID));
	if (isRoot) this->PG->SetPropertyValue(PropertyID, ToWxString(""));
	else this->PG->SetPropertyValue(PropertyID, qSceneManager.GenericHint());
	this->PG->DisableProperty(PropertyID);

	// Generic name
	Label = ToWxString("Generic");
	PropertyID = CategoryID + ToWxString(".") + Label;

	this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID));
	if (isRoot) this->PG->SetPropertyValue(PropertyID, ToWxString(""));
	else this->PG->SetPropertyValue(PropertyID, qSceneManager.GenericName());
	this->PG->DisableProperty(PropertyID);

	// BoundingBox
	Label = ToWxString("Show BoundingBox");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PShowBoundingBox = PG->AppendIn(PCSceneNode, new wxBoolProperty(Label, PropertyID, SN->getShowBoundingBox()));

	// Position
	Label = ToWxString("Position");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PPosition = this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PPositionX = this->PG->AppendIn(PPosition, new wxFloatProperty(wxT("x"), wxT("px")));
	this->PG->SetPropertyValidator(PPositionX, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PPositionY = this->PG->AppendIn(PPosition, new wxFloatProperty(wxT("y"), wxT("py")));
	this->PG->SetPropertyValidator(PPositionY, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PPositionZ = this->PG->AppendIn(PPosition, new wxFloatProperty(wxT("z"), wxT("pz")));
	this->PG->SetPropertyValidator(PPositionZ, wxTextValidator(wxFILTER_NUMERIC));
	PPosition->SetExpanded(false);
	PPosition->SetFlag(wxPG_PROP_NOEDITOR);

	// Set values
	this->PG->SetPropertyValue(PPositionX, (double)SN->getPosition().x);
	this->PG->SetPropertyValue(PPositionY, (double)SN->getPosition().y);
	this->PG->SetPropertyValue(PPositionZ, (double)SN->getPosition().z);

	// Rotation
	Label = ToWxString("Rotation");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PRotation = this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PRotationRoll = this->PG->AppendIn(PRotation, new wxFloatProperty(wxT("(x-Axis) Roll"), wxT("roll")));
	this->PG->SetPropertyValidator(PRotationRoll, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PRotationPitch = this->PG->AppendIn(PRotation, new wxFloatProperty(wxT("(y-Axis) Pitch"), wxT("pitch")));
	this->PG->SetPropertyValidator(PRotationPitch, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PRotationYaw = this->PG->AppendIn(PRotation, new wxFloatProperty(wxT("(z-Axis) Yaw"), wxT("yaw")));
	this->PG->SetPropertyValidator(PRotationYaw, wxTextValidator(wxFILTER_NUMERIC));
	PRotation->SetExpanded(false);
	PRotation->SetFlag(wxPG_PROP_NOEDITOR);

	// Set values
	this->PG->SetPropertyValue(PRotationRoll, (double)SN->getOrientation().getPitch().valueDegrees());
	this->PG->SetPropertyValue(PRotationPitch, (double)SN->getOrientation().getRoll().valueDegrees());
	this->PG->SetPropertyValue(PRotationYaw, (double)SN->getOrientation().getYaw().valueDegrees());

	// Scale
	Label = ToWxString("Scale");
	PropertyID = CategoryID + ToWxString(".") + Label;

	wxPGProperty* PScale = this->PG->AppendIn(PCSceneNode, new wxStringProperty(Label, PropertyID, wxT("<composed>")));
	wxPGProperty* PScaleX = this->PG->AppendIn(PScale, new wxFloatProperty(wxT("x"), wxT("sx")));
	this->PG->SetPropertyValidator(PScaleX, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PScaleY = this->PG->AppendIn(PScale, new wxFloatProperty(wxT("y"), wxT("sy")));
	this->PG->SetPropertyValidator(PScaleY, wxTextValidator(wxFILTER_NUMERIC));
	wxPGProperty* PScaleZ = this->PG->AppendIn(PScale, new wxFloatProperty(wxT("z"), wxT("sz")));
	this->PG->SetPropertyValidator(PScaleZ, wxTextValidator(wxFILTER_NUMERIC));
	PScale->SetExpanded(false);
	PScale->SetFlag(wxPG_PROP_NOEDITOR);

	// Set values
	this->PG->SetPropertyValue(PScaleX, (double)SN->getScale().x);
	this->PG->SetPropertyValue(PScaleY, (double)SN->getScale().y);
	this->PG->SetPropertyValue(PScaleZ, (double)SN->getScale().z);
	
	return PCSceneNode;
}
bool SelectionManager::AddMovableObject(Ogre::MovableObject* MO)
{
	// Validate parameters...
	if ( MO == 0 ) return false;

	// Get QualifiedName
	QualifiedName qMovableObject = QualifiedName::GetQualifiedNameByUnique(ToWxString(MO->getName()));
	if ( !qMovableObject.IsValid() ) return false;

	// Get Ogre::MovableObject-Type
	OgreEnums::MovableObject::MovableType EnumMT = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetMovableType(qMovableObject);

	// Setup category
	wxString CategoryHeadline;
	switch(EnumMT)
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

	switch(EnumMT)
	{
		case OgreEnums::MovableObject::MOVABLETYPE_BillBoardChain:			this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_BillboardSet:			this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_Camera:					this->AddCamera((Ogre::Camera*)MO); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Entity:					this->AddEntity((Ogre::Entity*)MO); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Frustum:					this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_InstancedGeometry_BatchInstance: this->AddNOTIMPLEMENTED();	break;
		case OgreEnums::MovableObject::MOVABLETYPE_Light:					this->AddLight((Ogre::Light*)MO);	break;
		case OgreEnums::MovableObject::MOVABLETYPE_ManualObject:			this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_MovablePlane:			this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_ParticleSystem:			this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_RibbonTrail:				this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_SimpleRenderable:		this->AddNOTIMPLEMENTED();			break;
		case OgreEnums::MovableObject::MOVABLETYPE_StaticGeometry_Region:	this->AddNOTIMPLEMENTED();			break;
		default: this->AddNOTIMPLEMENTED(); return false; break;
	}

	return true;
}
bool SelectionManager::GeneratePropertyGridContentFromSelection() { return this->GeneratePropertyGridContentFromSelection(this->Selection); }
bool SelectionManager::GeneratePropertyGridContentFromSelection(wxString UniqueNameOfSelection)
{
	/*
	if (UniqueNameOfSelection.IsEmpty())
	{*/
		return this->GeneratePropertyGridContentFromSelection(this->Selection);
	/*}

	if (this->Selections.count(UniqueNameOfSelection) == 1)
	{
		return this->generatePropertyGridContentFromSelection(PG, this->Selections[UniqueNameOfSelection]);
	}
	
	return false;*/
}
bool SelectionManager::GeneratePropertyGridContentFromSelection(QualifiedNameCollection Selection)
{
	// Check, if PropertyGrid is set!
	if (!this->IsValid()) return false;

	// Clear wxPropertryGrid
	this->PG->Clear();

	// Get Ogre::SceneManager
	QualifiedName qSM = OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager();
	Ogre::SceneManager* SM = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(qSM);
	
	// Validate Ogre::SceneManager...
	if (SM == 0) return false;

	// Add head-cathegory for Ogre::SceneManeger
	wxPropertyCategory* PCSceneManager = new wxPropertyCategory(ToWxString("SceneManager"));
	this->PG->Append(PCSceneManager);
	this->PG->Append(new wxStringProperty(ToWxString("Name"), ToWxString("SceneManagerName")));
	this->PG->SetPropertyValue(ToWxString("SceneManagerName"), OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager().UniqueName());
	this->PG->DisableProperty(ToWxString("SceneManagerName"));	

	// Add cathegory "Selection"
	this->PCSelection = new wxPropertyCategory(ToWxString("Selection"));
	this->PG->Append(this->PCSelection);
	this->PCSelection->SetExpanded(true);

	// Create (sub-)cathegories for selected objects (recursiv walktrought)
	if (!Selection.IsEmpty())
	{
		for ( unsigned long IT = 0; IT < Selection.Count(); IT++ )
		{
			if (OgreMediator::GetSingletonPtr()->iMovableObject.Exist(Selection[IT]))
			{
				Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(Selection[IT]);
				this->AddMovableObject(MO);
			}
			else if (OgreMediator::GetSingletonPtr()->iSceneNode.Exist(Selection[IT]))
			{
				Ogre::SceneNode* SN = OgreMediator::GetSingletonPtr()->iSceneNode.GetPtr(Selection[IT]);
				this->AddSceneNode(SN);
			}
		}
	}

	return true;
}
// Handle wxMain->OnPropertyChanged(...) wxPropertyGridEvent
bool SelectionManager::HandlePropertyChanged(wxPGProperty* ChangedProperty)
{
	// It may be NULL
    if ( ChangedProperty == 0 ) return false;

    // New property change
	this->ChangedProperty = ChangedProperty;

	// STEP 0: Is property a subproperty? If so, stop processing event without error!
	if (this->ChangedProperty->IsSubProperty()) return true;

	// STEP 1: Get full name of changed property
	wxString FullNameOfChangedProperty = ChangedProperty->GetName();
	wxString FullNameOfChangedLogicalUnit; // Empty

	// STEP 2: Get parent-property's full name
	wxPGProperty* ParentProperty = ChangedProperty->GetParent();
	wxString FullNameOfParentProperty = ParentProperty->GetName();

	wxPGProperty* LastParent = 0;

	// STEP 3: Lookup, until parent's name is not part of property's name any more. 
	while((ParentProperty == 0) || FullNameOfChangedProperty.Contains(FullNameOfParentProperty))
	{
		LastParent = ParentProperty;
		ParentProperty = LastParent->GetParent();
		FullNameOfParentProperty = ParentProperty->GetName();
	}
	
	// Check, if it's valid...
	if (LastParent == 0) return false;
	
	// STEP 4: Take last parent!
	FullNameOfChangedLogicalUnit = LastParent->GetName();

	// STEP 5: Seperate data
	wxString UniqueName = FullNameOfChangedLogicalUnit;
	wxString PurePGID = FullNameOfChangedProperty;
	PurePGID.Replace(UniqueName, ToWxString(""), false);

	// STEP 6: Get QualifiedName
	QualifiedName qName = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(UniqueName);
	if ( !qName.IsValid() ) return false;
	
	// STEP 7: Get MovableType by QualifiedName
	OgreEnums::MovableObject::MovableType Type = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetMovableType(qName);

	// STEP 8: Futher calls depend on MovableType...
	bool ReturnValue = false;
	switch(Type)
	{
	case OgreEnums::MovableObject::MOVABLETYPE_Invalid:
		// STEP 8.x: Object is no Ogre::MovableObject. Could be Ogre::SceneManager or Ogre::SceneNode
		
		if (OgreMediator::GetSingletonPtr()->iSceneManager.Exist(qName))
		{
			// Got Ogre::SceneManager
			this->IsValid(); // DEBUG: Handling of that type not implemented yet !!!
			ReturnValue = false;
		}
		if (OgreMediator::GetSingletonPtr()->iSceneNode.Exist(qName))
		{
			// Got Ogre::SceneNode
			ReturnValue = this->HandleSceneNodeChanged(qName, PurePGID);
		}	
		break;

	case OgreEnums::MovableObject::MOVABLETYPE_Camera:	ReturnValue = this->HandleCameraChanged(qName, PurePGID); break;
	case OgreEnums::MovableObject::MOVABLETYPE_Entity:	ReturnValue = this->HandleEntityChanged(qName, PurePGID); break;
	case OgreEnums::MovableObject::MOVABLETYPE_Light:	ReturnValue = this->HandleLightChanged(qName, PurePGID); break;
	default:	ReturnValue = false;	break; // DEBUG: Handling of that type not implemented yet !!!
	}

	return ReturnValue;
/*
	// old technique
	// Get name of changed property
	//zAxis_Entity_0.Rotation.rz
	wxString PName = ChangedProperty->GetName();
	wxStringTokenizer StrTok(PName, ToWxString("."));

	// Prepare returnvalue
	bool ReturnValue = false;

	// Handle object id
	if ( StrTok.HasMoreTokens() )
	{
		// STAGE 1: Get UniqueName and rebuild rest of PropertyID
		UniqueName = StrTok.GetNextToken();
		wxString subPGID;
		while(StrTok.HasMoreTokens())
		{
			subPGID << StrTok.GetNextToken();
			if (StrTok.HasMoreTokens()) subPGID << ToWxString(".");
		}
		
		// STAGE 2: Get QualifiedNames by UniqueName
		QualifiedName qName = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetQualifiedNameOfObject(UniqueName);
		if ( !qName.IsValid() ) return false;

		// STAGE 3: Get Type by indentified QualifiedName
		OgreEnums::MovableObject::MovableType Type = OgreMediator::GetSingletonPtr()->GetObjectAccess()->GetMovableType(qName);

		// STAGE 4: Futher calls depend on type...
		bool Match = false;
		switch(Type)
		{
		case OgreEnums::MovableObject::MOVABLETYPE_Invalid:
			// STAGE 4.x: Object is no Ogre::MovableObject. Could be Ogre::SceneManager or Ogre::SceneNode
			
			if ((!Match) && OgreMediator::GetSingletonPtr()->iSceneManager.Exist(qName))
			{
				// Got Ogre::SceneManager
				this->IsValid(); // DEBUG: Handling of that type not implemented yet !!!
				Match = false;
			}
			if ((!Match) && OgreMediator::GetSingletonPtr()->iSceneNode.Exist(qName))
			{
				// Got Ogre::SceneNode
				this->HandleSceneNodeChanged(qName, subPGID);
				Match = false;
			}	
			break;

		case OgreEnums::MovableObject::MOVABLETYPE_Camera:	ReturnValue = this->HandleCameraChanged(qName, subPGID); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Entity:	ReturnValue = this->HandleEntityChanged(qName, subPGID); break;
		case OgreEnums::MovableObject::MOVABLETYPE_Light:	ReturnValue = this->HandleLightChanged(qName, subPGID); break;
		default:	Match = false;	break; // DEBUG: Handling of that type not implemented yet !!!
		}
	}

	return ReturnValue;
	*/
}
bool SelectionManager::HandleSceneNodeChanged(QualifiedName qSceneNode, wxString subPGID)
{
	// Verify qSceneNode
	if (!OgreMediator::GetSingletonPtr()->iSceneNode.Exist(qSceneNode)) return false;
	Ogre::SceneNode* SN = OgreMediator::GetSingletonPtr()->iSceneNode.GetPtr(qSceneNode);
	return this->HandleSceneNodeChanged(SN, subPGID);
}
bool SelectionManager::HandleSceneNodeChanged(Ogre::SceneNode* SN, wxString subPGID)
{
	// INFO: Don't worry. Change parts of composed-types will be propagated :-)

	// It may be NULL
	if ( SN == 0 ) return false;

	wxVariant value = this->ChangedProperty->GetValue();  // TODO: obsolete because it's now accessible in object-member

	// Get name of changed property
	wxStringTokenizer StrTok(subPGID, ToWxString("."));
	
	// STAGE 2: Handle attribute
	wxString AttributeID = StrTok.GetNextToken();
	if (AttributeID.IsEmpty())
	{
		AttributeID = StrTok.GetNextToken();
	}

	if (AttributeID.IsSameAs(ToWxString("Position")))
	{
		if (!StrTok.HasMoreTokens()) this->HandlePositionChanged(SN);
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Rotation")))
	{
		if (!StrTok.HasMoreTokens()) this->HandleRotationChanged(SN);
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Scale")))
	{
		if (!StrTok.HasMoreTokens()) this->HandleScaleChanged(SN);
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Name"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Native"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Hint"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Generic"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Show BoundingBox")))
	{
		SN->showBoundingBox(value.GetBool());
		return true;
	}

	return false;
}
bool SelectionManager::HandleCameraChanged(QualifiedName qCamera, wxString subPGID)
{
	// Verify qCamera
	if (!OgreMediator::GetSingletonPtr()->iCamera.Exist(qCamera)) return false;
	Ogre::Camera* C = OgreMediator::GetSingletonPtr()->iCamera.GetPtr(qCamera);
	return this->HandleCameraChanged(C, subPGID);
}
bool SelectionManager::HandleCameraChanged(Ogre::Camera* C, wxString subPGID)
{
	// It may be NULL
	if ( C == 0 ) return false;

	// Get changed value...
	wxVariant V = this->ChangedProperty->GetValue();

	// Get name of changed property
	wxStringTokenizer StrTok(subPGID, ToWxString("."));
	
	// STAGE 2: Handle attribute
	wxString AttributeID = StrTok.GetNextToken();

	if (AttributeID.IsSameAs(ToWxString("Name"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Native"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Hint"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Generic"))) // not editable
	{
		return false;
	}

	if (AttributeID.IsSameAs(ToWxString("FOVy")))
	{
		C->setFOVy(Ogre::Radian(Ogre::Degree(V.GetReal())));
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("AspectRatio")))
	{
		C->setAspectRatio(V.GetReal());
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("ClipDistance (near)")))
	{
		C->setNearClipDistance(V.GetReal());
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("ClipDistance (far)")))
	{
		C->setFarClipDistance(V.GetReal());
		return true;
	}

	return false;
}

bool SelectionManager::HandleEntityChanged(QualifiedName qEntity, wxString subPGID)
{
	// Verify qEntity
	if (!OgreMediator::GetSingletonPtr()->iEntity.Exist(qEntity)) return false;
	Ogre::Entity* E = OgreMediator::GetSingletonPtr()->iEntity.GetPtr(qEntity);
	return this->HandleEntityChanged(E, subPGID);
}
bool SelectionManager::HandleEntityChanged(Ogre::Entity* E, wxString subPGID)
{
	// INFO: Don't worry. Change parts of composed-types will be propagated :-)

	// It may be NULL
	if ( E == 0 ) return false;

	wxVariant value = this->ChangedProperty->GetValue();  // TODO: obsolete because it's now accessible in object-member

	// Get name of changed property
	wxStringTokenizer StrTok(subPGID, ToWxString("."));
	
	// STAGE 2: Handle attribute
	wxString AttributeID = StrTok.GetNextToken();

	if (AttributeID.IsSameAs(ToWxString("Name"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Native"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Hint"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Generic"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Mesh"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("CastShadows")))
	{
		E->setCastShadows(value.GetBool());
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("DisplaySkeleton")))
	{
		E->setDisplaySkeleton(value.GetBool());
		return true;
	}

	return false;
}

bool SelectionManager::HandleLightChanged(QualifiedName qLight, wxString subPGID)
{
	// Verify qLight
	if (!OgreMediator::GetSingletonPtr()->iLight.Exist(qLight)) return false;
	Ogre::Light* L = OgreMediator::GetSingletonPtr()->iLight.GetPtr(qLight);
	return this->HandleLightChanged(L, subPGID);
}
bool SelectionManager::HandleLightChanged(Ogre::Light* L, wxString subPGID)
{
	// INFO: Don't worry. Change parts of composed-types will be propagated :-)

	// It may be NULL
	if ( L == 0 ) return false;

	// Get changed value...
	wxVariant V = this->ChangedProperty->GetValue();

	// Get name of changed property
	wxStringTokenizer StrTok(subPGID, ToWxString("."));
	
	// STAGE 2: Handle attribute
	wxString AttributeID = StrTok.GetNextToken();
	
	if (AttributeID.IsSameAs(ToWxString("Name"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Native"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Hint"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Generic"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Type"))) // not editable
	{
		return false;
	}
	if (AttributeID.IsSameAs(ToWxString("Visible")))
	{
		L->setVisible(V.GetBool());
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Direction")))
	{
		if (!StrTok.HasMoreTokens()) this->HandleLightDirectionChanged(L);
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Diffuse Colour")))
	{
		if (!StrTok.HasMoreTokens()) this->HandleLightDiffuseColourChanged(L);
		return true;
	}
	if (AttributeID.IsSameAs(ToWxString("Specular Colour")))
	{
		if (!StrTok.HasMoreTokens()) this->HandleLightSpecularColourChanged(L);
		return true;
	}

	return false;
}

bool SelectionManager::HandlePositionChanged(Ogre::SceneNode* SN)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing position of Ogre::SceneNode '");
	MSG << ToWxString(SN->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Real(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewX = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewY = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewZ = Ogre::Real(V.GetDouble());

	// Prepare values
	Ogre::Vector3 P = SN->getPosition();
	Ogre::Real X = P.x;
	Ogre::Real Y = P.y;
	Ogre::Real Z = P.z;

	// Log before
	MSG = ToWxString("From: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	SN->setPosition(NewX, NewY, NewZ);
	
	// Reflect values
	P = SN->getPosition();
	X = P.x;
	Y = P.y;
	Z = P.z;

	// Log after
	MSG = ToWxString("To: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("px"));
	this->PG->SetPropertyValue(ChildProperty, (double)X);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("py"));
	this->PG->SetPropertyValue(ChildProperty, (double)Y);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("pz"));
	this->PG->SetPropertyValue(ChildProperty, (double)Z);

	return true;
}
bool SelectionManager::HandleScaleChanged(Ogre::SceneNode* SN)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing scale of Ogre::SceneNode '");
	MSG << ToWxString(SN->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Degree(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewX = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewY = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewZ = Ogre::Real(V.GetDouble());

	// Prepare values
	Ogre::Vector3 P = SN->getScale();
	Ogre::Real X = P.x;
	Ogre::Real Y = P.y;
	Ogre::Real Z = P.z;

	// Log before
	MSG = ToWxString("From: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	SN->setScale(NewX, NewY, NewZ);
	
	// Reflect values
	P = SN->getScale();
	X = P.x;
	Y = P.y;
	Z = P.z;

	// Log after
	MSG = ToWxString("To: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("sx"));
	this->PG->SetPropertyValue(ChildProperty, (double)X);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("sy"));
	this->PG->SetPropertyValue(ChildProperty, (double)Y);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("sz"));
	this->PG->SetPropertyValue(ChildProperty, (double)Z);

	return true;
}
bool SelectionManager::HandleRotationChanged(Ogre::SceneNode* SN)
{
	// It may be NULL
	if ( SN == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing rotation of Ogre::SceneNode '");
	MSG << ToWxString(SN->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Degree(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Degree NewR = Ogre::Degree(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Degree NewP = Ogre::Degree(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Degree NewY = Ogre::Degree(V.GetDouble());

	// Prepare values
	Ogre::Quaternion Q = SN->getOrientation();
	Ogre::Degree R = Ogre::Degree(Q.getRoll(false));
	Ogre::Degree P = Ogre::Degree(Q.getPitch(false));
	Ogre::Degree Y = Ogre::Degree(Q.getYaw(false));

	// Log before
	MSG = ToWxString("From: Roll='");
	MSG << (double)R.valueDegrees() << ToWxString("' | Pitch='");
	MSG << (double)P.valueDegrees() << ToWxString("' | Yaw='");
	MSG << (double)Y.valueDegrees() << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	SN->setOrientation(Ogre::Quaternion::IDENTITY);
	SN->roll(Ogre::Radian(NewR), Ogre::Node::TS_PARENT);
	SN->pitch(Ogre::Radian(NewP), Ogre::Node::TS_PARENT);
	SN->yaw(Ogre::Radian(NewY), Ogre::Node::TS_PARENT);
	
	// Reflect values
	Q = SN->getOrientation();
	R = Ogre::Degree(Q.getRoll(false));
	P = Ogre::Degree(Q.getPitch(false));
	Y = Ogre::Degree(Q.getYaw(false));

	// Log after
	MSG = ToWxString("To: Roll='");
	MSG << (double)R.valueDegrees() << ToWxString("' | Pitch='");
	MSG << (double)P.valueDegrees() << ToWxString("' | Yaw='");
	MSG << (double)Y.valueDegrees() << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("roll"));
	this->PG->SetPropertyValue(ChildProperty, (double)P.valueDegrees());
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("pitch"));
	this->PG->SetPropertyValue(ChildProperty, (double)R.valueDegrees());
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("yaw"));
	this->PG->SetPropertyValue(ChildProperty, (double)Y.valueDegrees());

	return true;
}

bool SelectionManager::HandleLightDirectionChanged(Ogre::Light* L)
{
	// It may be NULL
	if ( L == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing Direction of Ogre::Light '");
	MSG << ToWxString(L->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Real(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewX = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewY = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewZ = Ogre::Real(V.GetDouble());

	// Prepare values
	Ogre::Vector3 N = L->getDirection();
	Ogre::Real X = N.x;
	Ogre::Real Y = N.y;
	Ogre::Real Z = N.z;

	// Log before
	MSG = ToWxString("From: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	L->setDirection(NewX, NewY, NewZ);
	
	// Reflect values
	N = L->getDirection();
	X = N.x;
	Y = N.y;
	Z = N.z;

	// Log after
	MSG = ToWxString("To: X='");
	MSG << (double)X << ToWxString("' | Y='");
	MSG << (double)Y << ToWxString("' | Z='");
	MSG << (double)Z << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dx"));
	this->PG->SetPropertyValue(ChildProperty, (double)X);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dy"));
	this->PG->SetPropertyValue(ChildProperty, (double)Y);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dz"));
	this->PG->SetPropertyValue(ChildProperty, (double)Z);

	return true;
}
bool SelectionManager::HandleLightDiffuseColourChanged(Ogre::Light* L)
{
	// It may be NULL
	if ( L == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing diffuse colour of Ogre::Light '");
	MSG << ToWxString(L->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Real(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewR = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewG = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewB = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewA = Ogre::Real(V.GetDouble());

	// Prepare values
	Ogre::ColourValue CV = L->getDiffuseColour();
	Ogre::Real R = CV.r;
	Ogre::Real G = CV.g;
	Ogre::Real B = CV.b;
	Ogre::Real A = CV.a;

	// Log before
	MSG = ToWxString("From: R='");
	MSG << (double)R << ToWxString("' | G='");
	MSG << (double)G << ToWxString("' | B='");
	MSG << (double)B << ToWxString("' | A='");
	MSG << (double)A << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	L->setDiffuseColour(Ogre::ColourValue(NewR, NewG, NewB, NewA));
	
	// Reflect values
	CV = L->getDiffuseColour();
	R = CV.r;
	G = CV.g;
	B = CV.b;
	A = CV.a;

	// Log after
	MSG = ToWxString("From: R='");
	MSG << (double)R << ToWxString("' | G='");
	MSG << (double)G << ToWxString("' | B='");
	MSG << (double)B << ToWxString("' | A='");
	MSG << (double)A << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dcr"));
	this->PG->SetPropertyValue(ChildProperty, (double)R);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dcg"));
	this->PG->SetPropertyValue(ChildProperty, (double)G);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dcb"));
	this->PG->SetPropertyValue(ChildProperty, (double)B);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("dca"));
	this->PG->SetPropertyValue(ChildProperty, (double)A);

	return true;
}
bool SelectionManager::HandleLightSpecularColourChanged(Ogre::Light* L)
{
	// It may be NULL
	if ( L == 0 ) return false;

	// Perpare logging
	wxString MSG;

	MSG = ToWxString("Changing specular colour of Ogre::Light '");
	MSG << ToWxString(L->getName()) << "':";
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Use variant as string an tokenize it
	wxStringTokenizer SemiSeperator(this->ChangedProperty->GetValue().GetString(), wxT(";"));
	
	// Format subtokens into Ogre::Real(double) via variant
	wxVariant V;
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewR = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewG = Ogre::Real(V.GetDouble());
	V = SemiSeperator.GetNextToken();
	Ogre::Real NewB = Ogre::Real(V.GetDouble());

	// Prepare values
	Ogre::ColourValue CV = L->getDiffuseColour();
	Ogre::Real R = CV.r;
	Ogre::Real G = CV.g;
	Ogre::Real B = CV.b;

	// Log before
	MSG = ToWxString("From: R='");
	MSG << (double)R << ToWxString("' | G='");
	MSG << (double)G << ToWxString("' | B='");
	MSG << (double)B << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Apply change
	L->setDiffuseColour(NewR, NewG, NewB);
	
	// Reflect values
	CV = L->getDiffuseColour();
	R = CV.r;
	G = CV.g;
	B = CV.b;

	// Log after
	MSG = ToWxString("From: R='");
	MSG << (double)R << ToWxString("' | G='");
	MSG << (double)G << ToWxString("' | B='");
	MSG << (double)B << ToWxString("'");
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	// Update related values 
	wxPGProperty* ChildProperty;
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("scr"));
	this->PG->SetPropertyValue(ChildProperty, (double)R);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("scg"));
	this->PG->SetPropertyValue(ChildProperty, (double)G);
	ChildProperty = this->ChangedProperty->GetPropertyByName(ToWxString("scb"));
	this->PG->SetPropertyValue(ChildProperty, (double)B);

	return true;
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