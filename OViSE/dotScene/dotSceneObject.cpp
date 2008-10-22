#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

void dotSceneObjects::dotSceneObject::set_NameSymbol(dotSceneElementTags value)
{ 
    _NameSymbol = value;
    switch(_NameSymbol)
	{	
		case billboard :        _Name = "billboard";            break;
		case billboardSet :     _Name = "billboardSet";         break;
		case camera :           _Name = "camera";               break;
        case  colourAmbient :    _Name = "colourAmbient";        break;
        case  colourBackground : _Name = "colourBackground";     break;
        case  colourDiffuse :    _Name = "colourDiffuse";        break;
        case  colourSpecular :   _Name = "colourSpecular";       break;
        case  entity :           _Name = "entity";               break;
        case  environment :      _Name = "environment";          break;
        case  externals :        _Name = "externals";            break;
        case  file :             _Name = "file";                 break;
        case  fog :              _Name = "fog";                  break;
        case  indexBuffer :      _Name = "indexBuffer";          break;
        case  item :             _Name = "item";                 break;
        case  light :            _Name = "light";                break;
        case  lightAttenuation : _Name = "lightAttenuation";     break;
        case  lightRange :       _Name = "lightRange";           break;
        case  localDirection :   _Name = "localDirection";       break;
        case  lookTarget :       _Name = "lookTarget";           break;
        case  node :             _Name = "node";                 break;
        case  nodes :            _Name = "nodes";                break;
        case  normal :           _Name = "normal";               break;
        case  octGeometry :      _Name = "octGeometry";          break;
        case  octMaterial :      _Name = "octMaterial";          break;
        case  octMesh :          _Name = "octMesh";              break;
        case  octNode :          _Name = "octNode";              break;
        case  octree :           _Name = "octree";               break;
        case  offset :           _Name = "offset";               break;
        case  particleSystem :   _Name = "particleSystem";       break;
        case  plane :            _Name = "plane";                break;
        case  position :         _Name = "position";             break;
        case  rotation :         _Name = "rotation";             break;
        case  scale :            _Name = "scale";                break;
        case  scene :            _Name = "scene";                break;
        case  skyBox :           _Name = "skyBox";               break;
        case  skyDome :          _Name = "skyDome";              break;
        case  skyPlane :         _Name = "skyPlane";             break;
        case  terrain :          _Name = "terrain";              break;
        case  trackTarget :      _Name = "trackTarget";          break;
        case  upVector :         _Name = "upVector";             break;
        case  userDataReference :_Name = "userDataReference";    break;
        case  vertexBuffer :     _Name = "vertexBuffer";         break;
    }
}

/* void dotSceneObjects::dotSceneObject::set_Name(std::string value)
{
    INTERNAL_Name = value;
    
    switch(INTERNAL_Name)
    {
		case "billboard" :          INTERNAL_NameSymbol =  billboard;            break;
        case "billboardSet" :       INTERNAL_NameSymbol =  billboardSet;         break;
        case "camera" :             INTERNAL_NameSymbol =  camera;               break;
        case "colourAmbient" :      INTERNAL_NameSymbol =  colourAmbient;        break;
        case "colourBackground" :   INTERNAL_NameSymbol =  colourBackground;     break;
        case "colourDiffuse" :      INTERNAL_NameSymbol =  colourDiffuse;        break;
        case "colourSpecular" :     INTERNAL_NameSymbol =  colourSpecular;       break;
        case "entity" :             INTERNAL_NameSymbol =  entity;               break;
        case "environment" :        INTERNAL_NameSymbol =  environment;          break;
        case "externals" :          INTERNAL_NameSymbol =  externals;            break;
        case "file" :               INTERNAL_NameSymbol =  file;                 break;
        case "fog" :                INTERNAL_NameSymbol =  fog;                  break;
        case "indexBuffer" :        INTERNAL_NameSymbol =  indexBuffer;          break;
        case "item" :               INTERNAL_NameSymbol =  item;                 break;
        case "light" :              INTERNAL_NameSymbol =  light;                break;
        case "lightAttenuation" :   INTERNAL_NameSymbol =  lightAttenuation;     break;
        case "lightRange" :         INTERNAL_NameSymbol =  lightRange;           break;
        case "localDirection" :     INTERNAL_NameSymbol =  localDirection;       break;
        case "lookTarget" :         INTERNAL_NameSymbol =  lookTarget;           break;
        case "node" :               INTERNAL_NameSymbol =  node;                 break;
        case "nodes" :              INTERNAL_NameSymbol =  nodes;                break;
        case "normal" :             INTERNAL_NameSymbol =  normal;               break;
        case "octGeometry" :        INTERNAL_NameSymbol =  octGeometry;          break;
        case "octMaterial" :        INTERNAL_NameSymbol =  octMaterial;          break;
        case "octMesh" :            INTERNAL_NameSymbol =  octMesh;              break;
        case "octNode" :            INTERNAL_NameSymbol =  octNode;              break;
        case "octree" :             INTERNAL_NameSymbol =  octree;               break;
        case "offset" :             INTERNAL_NameSymbol =  offset;               break;
        case "particleSystem" :     INTERNAL_NameSymbol =  particleSystem;       break;
        case "plane" :              INTERNAL_NameSymbol =  plane;                break;
        case "position" :           INTERNAL_NameSymbol =  position;             break;
        case "rotation" :           INTERNAL_NameSymbol =  rotation;             break;
        case "scale" :              INTERNAL_NameSymbol =  scale;                break;
        case "scene" :              INTERNAL_NameSymbol =  scene;                break;
        case "skyBox" :             INTERNAL_NameSymbol =  skyBox;               break;
        case "skyDome" :            INTERNAL_NameSymbol =  skyDome;              break;
        case "skyPlane" :           INTERNAL_NameSymbol =  skyPlane;             break;
        case "terrain" :            INTERNAL_NameSymbol =  terrain;              break;
        case "trackTarget" :        INTERNAL_NameSymbol =  trackTarget;          break;
        case "upVector" :           INTERNAL_NameSymbol =  upVector;             break;
        case "userDataReference" :  INTERNAL_NameSymbol =  userDataReference;    break;
        case "vertexBuffer" :       INTERNAL_NameSymbol =  vertexBuffer;         break;
        default: throw new Exception("dotScene.Name.set(sting): string value invalid, because it's not correspondig to a value of  ");
    }
}
*/

dotSceneElementTags dotSceneObjects::dotSceneObject::get_NameSymbol() const { return _NameSymbol; }
std::string dotSceneObjects::dotSceneObject::get_Name() const { return _Name; }
dotSceneObjects::dotSceneObject::dotSceneObject(dotSceneElementTags ElementTag)
{
    this->set_NameSymbol(ElementTag);
}

/* * * * * siehe oben !!!
dotSceneObjects::dotSceneObject::dotSceneObject(std::string ElementName)
{
    this->set_Name(ElementName);
}   
*/
/*dotSceneObjects::dotSceneObject::dotSceneObject(dotSceneObject obj)
{
    this->INTERNAL_Name = obj.get_Name();
    this->INTERNAL_NameSymbol = obj.get_NameSymbol();
}
*/
