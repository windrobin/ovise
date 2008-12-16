#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

bool dotSceneObjects::dotSceneObject::set_NameSymbol(dotSceneEnums::dotSceneElementTags value)
{ 	
    this->_NameSymbol = value;

    switch(this->_NameSymbol)
	{	
		case dotSceneEnums::angle_axis :		this->_Name = "angle_axis";			break;
		case dotSceneEnums::axisXYZ :			this->_Name = "axisXYZ";			break;
		case dotSceneEnums::billboard :			this->_Name = "billboard";			break;
		case dotSceneEnums::billboardSet :		this->_Name = "billboardSet";		break;
		case dotSceneEnums::camera :			this->_Name = "camera";				break;
        case dotSceneEnums::colourAmbient :		this->_Name = "colourAmbient";		break;
		case dotSceneEnums::colourBackground :	this->_Name = "colourBackground";	break;
        case dotSceneEnums::colourDiffuse :		this->_Name = "colourDiffuse";		break;
        case dotSceneEnums::colourSpecular :	this->_Name = "colourSpecular";		break;
		case dotSceneEnums::commonDirection :	this->_Name = "commonDirection";		break;
		case dotSceneEnums::commonMovableObjectParams :	this->_Name = "commonMovableObjectParams";		break;
		case dotSceneEnums::commonUpVector :	this->_Name = "commonUpVector";		break;
		case dotSceneEnums::direction :			this->_Name = "direction";			break;
        case dotSceneEnums::entity :			this->_Name = "entity";				break;
        case dotSceneEnums::environment :		this->_Name = "environment";		break;
        case dotSceneEnums::externals :			this->_Name = "externals";			break;
        case dotSceneEnums::file :				this->_Name = "file";				break;
		case dotSceneEnums::floatRect :			this->_Name = "floatRect";			break;
        case dotSceneEnums::fog :				this->_Name = "fog";				break;
        case dotSceneEnums::indexBuffer :		this->_Name = "indexBuffer";		break;
        case dotSceneEnums::item :				this->_Name = "item";				break;
        case dotSceneEnums::light :				this->_Name = "light";				break;
		case dotSceneEnums::lightAttenuation :	this->_Name = "lightAttenuation";	break;
        case dotSceneEnums::localDirection :	this->_Name = "localDirection";		break;
		case dotSceneEnums::localDirectionVector :	this->_Name = "localDirectionVector";		break;
        case dotSceneEnums::lookTarget :		this->_Name = "lookTarget";			break;
		case dotSceneEnums::materialLODBias :		this->_Name = "materialLODBias";		break;
		case dotSceneEnums::meshLODBias :		this->_Name = "meshLODBias";		break;
        case dotSceneEnums::node :				this->_Name = "node";				break;
        case dotSceneEnums::nodes :				this->_Name = "nodes";				break;
        case dotSceneEnums::normal :			this->_Name = "normal";				break;
        case dotSceneEnums::octGeometry :		this->_Name = "octGeometry";		break;
        case dotSceneEnums::octMaterial :		this->_Name = "octMaterial";		break;
        case dotSceneEnums::octMesh :			this->_Name = "octMesh";			break;
        case dotSceneEnums::octNode :			this->_Name = "octNode";			break;
        case dotSceneEnums::octree :			this->_Name = "octree";				break;
        case dotSceneEnums::offset :			this->_Name = "offset";				break;
		case dotSceneEnums::orientation :		this->_Name = "orientation";		break;
        case dotSceneEnums::particleSystem :	this->_Name = "particleSystem";		break;
        case dotSceneEnums::plane :				this->_Name = "plane";				break;
        case dotSceneEnums::position :			this->_Name = "position";			break;
		case dotSceneEnums::quaternion :		this->_Name = "quaternion";			break;
        case dotSceneEnums::scale :				this->_Name = "scale";				break;
        case dotSceneEnums::scene :				this->_Name = "scene";				break;
        case dotSceneEnums::shadowTextureConfig :	this->_Name = "shadowTextureConfig";				break;
		case dotSceneEnums::skyBox :			this->_Name = "skyBox";				break;
        case dotSceneEnums::skyDome :			this->_Name = "skyDome";			break;
        case dotSceneEnums::skyPlane :			this->_Name = "skyPlane";			break;
        case dotSceneEnums::spotLightRange :		this->_Name = "spotLightRange";			break;
        case dotSceneEnums::terrain :			this->_Name = "terrain";			break;
		case dotSceneEnums::textureCoords :		this->_Name = "textureCoords";		break;
		case dotSceneEnums::textureStacksAndSlices :		this->_Name = "textureStacksAndSlices";		break;
        case dotSceneEnums::trackTarget :		this->_Name = "trackTarget";		break;
        case dotSceneEnums::upVector :			this->_Name = "upVector";			break;
		case dotSceneEnums::userDataReference :	this->_Name = "userDataReference";	break;
        case dotSceneEnums::vertexBuffer :		this->_Name = "vertexBuffer";		break;
		case dotSceneEnums::INVALID:			this->_Name = "INVALID";			break;
		default:
			//throw new std::exception("dotSceneObject.set_NameSymbol(dotSceneElementaryTags value): value invalid, because it is not corresponding value in dotSceneElementaryTags.");
			this->_Name = "INVALID";
			this->_NameSymbol = dotSceneEnums::INVALID;
			return false;
			break;
    }

	return true;
}

bool dotSceneObjects::dotSceneObject::set_Name(std::string value)
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * Question:	Why such an horrible construct?																   *
	 * Answer:		In C/C++ it's not possible to compare stings (here std::string) in a SWITCH/CASE-construct.	   *
	 *				The only possible way is, as you can see, a meta-construct of IFs and a additional bool value. *
	 *				That bool allows a possible work-arround for the DEFAULT-statement.							   *
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    this->_Name = value;

	bool match = false;
    
	if (this->_Name == "angle_axis")		{ this->_NameSymbol = dotSceneEnums::angle_axis;		match = true; };
	if (this->_Name == "axisXYZ")			{ this->_NameSymbol = dotSceneEnums::axisXYZ;			match = true; };
	if (this->_Name == "billboard")			{ this->_NameSymbol = dotSceneEnums::billboard;			match = true; };
	if (this->_Name == "billboardSet")		{ this->_NameSymbol = dotSceneEnums::billboardSet;		match = true; };
	if (this->_Name == "camera")			{ this->_NameSymbol = dotSceneEnums::camera;			match = true; };
	if (this->_Name == "colourAmbient")		{ this->_NameSymbol = dotSceneEnums::colourAmbient;		match = true; };
	if (this->_Name == "colourBackground")	{ this->_NameSymbol = dotSceneEnums::colourBackground;	match = true; };
	if (this->_Name == "colourDiffuse")		{ this->_NameSymbol = dotSceneEnums::colourDiffuse;		match = true; };
	if (this->_Name == "colourSpecular")	{ this->_NameSymbol = dotSceneEnums::colourSpecular;	match = true; };
	if (this->_Name == "commonDirection")	{ this->_NameSymbol = dotSceneEnums::commonDirection;	match = true; };
	if (this->_Name == "commonMovableObjectParams")	{ this->_NameSymbol = dotSceneEnums::commonMovableObjectParams;	match = true; };
	if (this->_Name == "commonUpVector")	{ this->_NameSymbol = dotSceneEnums::commonUpVector;	match = true; };
	if (this->_Name == "direction")			{ this->_NameSymbol = dotSceneEnums::direction;			match = true; };
	if (this->_Name == "entity")			{ this->_NameSymbol = dotSceneEnums::entity;			match = true; };
	if (this->_Name == "environment")		{ this->_NameSymbol = dotSceneEnums::environment;		match = true; };
	if (this->_Name == "externals")			{ this->_NameSymbol = dotSceneEnums::externals;			match = true; };
	if (this->_Name == "file")				{ this->_NameSymbol = dotSceneEnums::file;				match = true; };
	if (this->_Name == "floatRect")			{ this->_NameSymbol = dotSceneEnums::floatRect;			match = true; };
	if (this->_Name == "fog")				{ this->_NameSymbol = dotSceneEnums::fog;				match = true; };
	if (this->_Name == "indexBuffer")		{ this->_NameSymbol = dotSceneEnums::indexBuffer;		match = true; };
	if (this->_Name == "item")				{ this->_NameSymbol = dotSceneEnums::item;				match = true; };
	if (this->_Name == "light")				{ this->_NameSymbol = dotSceneEnums::light;				match = true; };
	if (this->_Name == "lightAttenuation")	{ this->_NameSymbol = dotSceneEnums::lightAttenuation;	match = true; };
	if (this->_Name == "localDirection")	{ this->_NameSymbol = dotSceneEnums::localDirection;	match = true; };
	if (this->_Name == "localDirectionVector")	{ this->_NameSymbol = dotSceneEnums::localDirectionVector;	match = true; };
	if (this->_Name == "lookTarget")		{ this->_NameSymbol = dotSceneEnums::lookTarget;		match = true; };
	if (this->_Name == "materialLODBias")		{ this->_NameSymbol = dotSceneEnums::materialLODBias;		match = true; };
	if (this->_Name == "meshLODBias")		{ this->_NameSymbol = dotSceneEnums::meshLODBias;		match = true; };
	if (this->_Name == "node")				{ this->_NameSymbol = dotSceneEnums::node;				match = true; };
	if (this->_Name == "nodes")				{ this->_NameSymbol = dotSceneEnums::nodes;				match = true; };
	if (this->_Name == "normal")			{ this->_NameSymbol = dotSceneEnums::normal;			match = true; };
	if (this->_Name == "octGeometry")		{ this->_NameSymbol = dotSceneEnums::octGeometry;		match = true; };
	if (this->_Name == "octMaterial")		{ this->_NameSymbol = dotSceneEnums::octMaterial;		match = true; };
	if (this->_Name == "octMesh")			{ this->_NameSymbol = dotSceneEnums::octMesh;			match = true; };
	if (this->_Name == "octNode")			{ this->_NameSymbol = dotSceneEnums::octNode;			match = true; };
	if (this->_Name == "octree")			{ this->_NameSymbol = dotSceneEnums::octree;			match = true; };
	if (this->_Name == "offset")			{ this->_NameSymbol = dotSceneEnums::offset;			match = true; };
	if (this->_Name == "orientation")		{ this->_NameSymbol = dotSceneEnums::orientation;		match = true; };
	if (this->_Name == "particleSystem")	{ this->_NameSymbol = dotSceneEnums::particleSystem;	match = true; };
	if (this->_Name == "plane")				{ this->_NameSymbol = dotSceneEnums::plane;				match = true; };
	if (this->_Name == "position")			{ this->_NameSymbol = dotSceneEnums::position;			match = true; };
	if (this->_Name == "quaternion")		{ this->_NameSymbol = dotSceneEnums::quaternion;		match = true; };
	if (this->_Name == "scale")				{ this->_NameSymbol = dotSceneEnums::scale;				match = true; };
	if (this->_Name == "scene")				{ this->_NameSymbol = dotSceneEnums::scene;				match = true; };
	if (this->_Name == "shadowTextureConfig")	{ this->_NameSymbol = dotSceneEnums::shadowTextureConfig;	match = true; };
	if (this->_Name == "skyBox")			{ this->_NameSymbol = dotSceneEnums::skyBox;			match = true; };
	if (this->_Name == "skyDome")			{ this->_NameSymbol = dotSceneEnums::skyDome;			match = true; };
	if (this->_Name == "skyPlane")			{ this->_NameSymbol = dotSceneEnums::skyPlane;			match = true; };
	if (this->_Name == "spotLightRange")		{ this->_NameSymbol = dotSceneEnums::spotLightRange;		match = true; };
	if (this->_Name == "terrain")			{ this->_NameSymbol = dotSceneEnums::terrain;			match = true; };
	if (this->_Name == "textureCoords")		{ this->_NameSymbol = dotSceneEnums::textureCoords;		match = true; };
	if (this->_Name == "textureStacksAndSlices")		{ this->_NameSymbol = dotSceneEnums::textureStacksAndSlices;		match = true; };
	if (this->_Name == "trackTarget")		{ this->_NameSymbol = dotSceneEnums::trackTarget;		match = true; };
	if (this->_Name == "upVector")			{ this->_NameSymbol = dotSceneEnums::upVector;			match = true; };
	if (this->_Name == "userDataReference") { this->_NameSymbol = dotSceneEnums::userDataReference;	match = true; };
	if (this->_Name == "vertexBuffer")		{ this->_NameSymbol = dotSceneEnums::vertexBuffer;		match = true; };
	if (this->_Name == "INVALID")			{ this->_NameSymbol = dotSceneEnums::INVALID;			match = true; };
	if(!match)
	{
		//throw new std::exception("dotSceneObject.set_Name(std::sting value): string invalid, because it is not corresponding value in dotSceneElementaryTags.");
		this->_NameSymbol = dotSceneEnums::INVALID;
		this->_Name = "INVALID";
		return false;
	}
	return true;
}

// Methods
dotSceneEnums::dotSceneElementTags dotSceneObjects::dotSceneObject::get_NameSymbol() const { return _NameSymbol; }
std::string dotSceneObjects::dotSceneObject::get_Name() const { return _Name; }

bool dotSceneObjects::dotSceneObject::IsValid() const
{
	if (this->_Name == "INVALID") return false;
	if (this->_NameSymbol == dotSceneEnums::INVALID) return false;
	
	return true;
}

// Constructors
//dotSceneObjects::dotSceneObject::dotSceneObject() { }
dotSceneObjects::dotSceneObject::dotSceneObject(dotSceneEnums::dotSceneElementTags ElementTag)
{
	this->_Name = "INVALID";
	this->_NameSymbol = dotSceneEnums::INVALID;

    this->set_NameSymbol(ElementTag);
}

dotSceneObjects::dotSceneObject::dotSceneObject(std::string ElementName)
{
	this->_Name = "INVALID";
	this->_NameSymbol = dotSceneEnums::INVALID;

    this->set_Name(ElementName);
}

dotSceneObjects::dotSceneObject::dotSceneObject(const dotSceneObject& obj)
{
	this->_Name = "INVALID";
	this->_NameSymbol = dotSceneEnums::INVALID;

    this->_Name = obj.get_Name();
    this->_NameSymbol = obj.get_NameSymbol();
}
