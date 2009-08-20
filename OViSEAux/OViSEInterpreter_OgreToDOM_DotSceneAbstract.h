#ifndef OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_H_
#define OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_H_

// Solution's includes
#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

#ifndef OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#define OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#include "./OViSEDotSceneManagerConfiguration.h"
#endif

#ifndef OVISE_LOGGING_USED
#define OVISE_LOGGING_USED
#include "../OViSE/OViSELogging.h"
#endif

#ifndef OVISE_SCENE_PROTOTYPE_USED
#define OVISE_SCENE_PROTOTYPE_USED
#include "./OViSEScenePrototype.h"
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

#include <deque>
#include <typeinfo>

/// Map containing selected objects.
typedef std::map<std::string, Ogre::MovableObject*> OViSESelectionMap;

WX_DECLARE_STRING_HASH_MAP(Ogre::SceneNode*, HashMap_OgreSceneNodePointer);
WX_DECLARE_STRING_HASH_MAP(DOMElement*, HashMap_DOMPointer);

class OViSEInterpreter_OgreToDOM_DotSceneAbstract
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// Abstract methods
	//virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene) = 0;
	//virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment) = 0;
	virtual xercesc::DOMElement* Interpretation_Node(Ogre::SceneNode* actualSceneNode) = 0;
	virtual xercesc::DOMElement* Interpretation_Camera(Ogre::Camera* actualCamera) = 0;
	virtual xercesc::DOMElement* Interpretation_Entity(Ogre::Entity* actualEntity) = 0;
	virtual xercesc::DOMElement* Interpretation_Light(Ogre::Light* actualLight) = 0;
	virtual xercesc::DOMElement* Interpretation_Position(Ogre::Vector3 NodePosition) = 0;
	virtual xercesc::DOMElement* Interpretation_Quaternion(Ogre::Quaternion NodeQuaternion) = 0;
	virtual xercesc::DOMElement* Interpretation_Scale(Ogre::Vector3 NodeScale) = 0;
	virtual xercesc::DOMElement* Interpretation_DiffuseColour(Ogre::ColourValue DiffuseColour) = 0;
	virtual xercesc::DOMElement* Interpretation_SpecularColour(Ogre::ColourValue SpecularColour) = 0;

protected:
	// Attributes
	OViSEDotSceneManagerConfiguration* Configuration;
	OViSEScenePrototype* Prototype;
	Ogre::SceneManager* SceneMgr;
	DOMImplementation* Implementation;
	OViSESelectionMap Selection;

	wxString VersionString;
	wxString NotUniquePrototypeName;
	wxString UniquePrototypeName;

	// Abstract methods
	virtual void SetVersionString(wxString VersionString) = 0;

	// Non-abstract methods
	wxString GetVersionString();
	virtual void Interpretation_Nodes(xercesc::DOMElement* SceneElement);
	void RecursiveNodeTreeWalkthrough(	Ogre::Node* actualSceneNode,
										HashMap_OgreSceneNodePointer& WhiteList_STAGE1,
										HashMap_DOMPointer& WhiteList_STAGE2,
										HashMap_DOMPointer& BlackList);
	bool Interpretation_OgreScene(	wxString NotUniquePrototypeName,
									OViSESelectionMap Selection,
									OViSEDotSceneManagerConfiguration* Configuration);
public:
	~OViSEInterpreter_OgreToDOM_DotSceneAbstract(void);

	// Inheritable methods
	virtual OViSEScenePrototype* Interpretation(	wxString NotUniquePrototypeName,
													OViSESelectionMap Selection,
													OViSEDotSceneManagerConfiguration* Configuration) = 0;
};

#endif /*OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_H_*/