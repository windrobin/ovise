#ifndef OVISE_DOTSCENE_MANAGER_H_
#define OVISE_DOTSCENE_MANAGER_H_

// Solution's includes
#ifndef OVISE_XML_MANAGER_USED
#define OVISE_XML_MANAGER_USED
#include "./OViSEXmlManager.h"
#endif

#ifndef OVISE_UNIQUENAME_GENERATOR_USED
#define OVISE_UNIQUENAME_GENERATOR_USED
#include "../OViSE/OViSEUniqueNameGenerator.h"
#endif

#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include Xerces
#ifndef XERCESC_UTIL_XMLSTRING_USED
#define XERCESC_UTIL_XMLSTRING_USED
#include <xercesc/util/XMLString.hpp>
#endif

#ifndef XERCESC_SAX_HANDLERBASE_USED
#define XERCESC_SAX_HANDLERBASE_USED
#include <xercesc/sax/HandlerBase.hpp>
#endif

#ifndef XERCES_PARSERS_XERCESDOMPARSER_USED
#define XERCES_PARSERS_XERCESDOMPARSER_USED
#include <xercesc/parsers/XercesDOMParser.hpp>
#endif

#ifndef XERCES_DOM_DOM_USED
#define XERCES_DOM_DOM_USED
#include <xercesc/dom/DOM.hpp>
#endif

#ifndef XERCES_UTIL_XMLFLOAT_USED
#define XERCES_UTIL_XMLFLOAT_USED
#include <xercesc/util/XMLFloat.hpp>
#endif

#ifndef XERCES_CPP_NAMESPACE_USE_USED
#define XERCES_CPP_NAMESPACE_USE_USED
XERCES_CPP_NAMESPACE_USE
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_FILENAME_USED
#define WX_FILENAME_USED
#include <wx/filename.h>
#endif

#ifndef WX_ARRAYSTRING_USED
#define WX_ARRAYSTRING_USED
#include <wx/arrstr.h>
#endif

#ifndef WX_HASHMAP_USED
#define WX_HASHMAP_USED
#include <wx/hashmap.h>
#endif

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

// Special defines for debugging or mode-activations
#define ATTACH_FACTORY__ALLOW_INTERPRETATION_ASSUMPTIONS

class OViSEDotSceneManager
{
private:
	wxString mUniqueFactoryName;
	wxString mNameOfFactoryOwnedResourceGroup;

	double mScaleOffset;
	Ogre::Vector3 mPositionOffset;
	Ogre::Degree mRollOfEntireScene , mPitchOfEntireScene, mYawOfEntireScene;
	Ogre::SceneNode *mSceneRootNode; //<- Green List: rename to "SceneRootNode"
	
	// HashMaps manage to blueprints and their locations
	WX_DECLARE_STRING_HASH_MAP(xercesc::DOMDocument*, HashMap_DOMDocuments);
	WX_DECLARE_STRING_HASH_MAP(wxFileName, HashMap_FileNames);

	HashMap_DOMDocuments DOMScenes;
	HashMap_FileNames LocationsOfMaterialFiles;
	HashMap_FileNames LocationsOfMeshFiles;

	// Attributes for interpretation
	Ogre::String _UniqueManagerName;
	Ogre::SceneManager *Mgr;
	Ogre::SceneNode *mAnchorNode;

	void v1_0_0_Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene);
	void v1_0_0_Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes);
	void v1_0_0_Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode);
	void v1_0_0_Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode);
	void v1_0_0_Interpretation_Camera(xercesc::DOMElement* DOMElement_camera);

	Ogre::Vector3 v1_0_0_Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3);
	Ogre::Vector4 v1_0_0_Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4);

	// Newest implementations...
	OViSEUniqueNameGenerator *SceneNameMgr;
	OViSEUniqueNameGenerator *SceneNodeNameMgr, *EntityNameMgr;

	OViSEXmlManager *mXmlMgr;

	wxArrayString mAvailableScenes;

public:
	OViSEDotSceneManager(wxString UniqueFactoryName, Ogre::SceneManager* sceneMgr, wxFileName URLofDotSceneXSD, wxFileName ExportPath);
    ~OViSEDotSceneManager();

	wxFileName mExportPath;

	void set_UniqueFactoryName(Ogre::String UniqueFactoryName);
	void set_UniqueFactoryName(wxString UniqueFactoryName);
	wxString get_UniqueFactoryName() const;
	void set_UniqueNameOfFactoryOwnedResourceGroup(Ogre::String UniqueNameOfFactoryOwnedResourceGroup);
	void set_UniqueNameOfFactoryOwnedResourceGroup(wxString UniqueNameOfFactoryOwnedResourceGroup);
	wxString get_UniqueNameOfFactoryOwnedResourceGroup() const;

	double get_ScaleOffset() const;
	void set_ScaleOffset(double);
	Ogre::Vector3 get_PositionOffset() const;
	void set_PositionOffset(Ogre::Vector3);

	void set_RollOfEntireScene(Ogre::Degree);
	Ogre::Degree get_RollOfEntireScene() const;
	void set_PitchOfEntireScene(Ogre::Degree);
	Ogre::Degree get_PitchOfEntireScene() const;
	void set_YawOfEntireScene(Ogre::Degree);
	Ogre::Degree get_YawOfEntireScene() const;

	Ogre::SceneNode* get_LastSceneRootNode() const;

	bool doAttachNodes;
	bool doAttachExternals;
	bool doAttachEnvironment;

	

	wxString addSceneBluePrint(wxFileName URLofXML); 

	bool attachScene(wxString UniqueSceneName, wxString AttachToNodeWithThisName, bool doAttachNodes, bool doAttachExternals, bool doAttachEnvironment);
	bool attachScene(wxString UniqueSceneName, wxString AttachToNodeWithThisName);

	wxArrayString GetAvailableScenes();

	Ogre::SceneNode* attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative); // Implicit: attach to root node
	Ogre::SceneNode* attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, wxString ParentNode);
	Ogre::SceneNode* attachSceneNode(wxString NotUniqueName, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, Ogre::SceneNode* ParentNode);
	
	Ogre::Entity* attachEntity(wxString NotUniqueEntityName, wxString MeshFile, wxString AttachToThisNode);
	Ogre::Entity* attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::SceneNode* AttachToThisNode);
	Ogre::Entity* attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative);
	Ogre::Entity* attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, wxString AttachToThisNode);
	Ogre::Entity* attachEntity(wxString NotUniqueEntityName, wxString MeshFile, Ogre::Vector3 Translation_Relative, Ogre::Vector3 Scale_Relative, Ogre::Quaternion Rotation_Relative, Ogre::SceneNode* AttachToThisNode);	


	// New Exportstuff

};


#endif /*OVISE_DOTSCENE_MANAGER_H_*/